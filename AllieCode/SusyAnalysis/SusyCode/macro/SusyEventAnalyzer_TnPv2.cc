//
//  Susyeventanalyzer.cc
//
//
//  Created by Allie Reinsvold on 8/4/14.
//
//This version creates the trigger efficiency plots that were used for the 2015 version of the analysis.

#define SusyEventAnalyzer_cxx

#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TProfile.h>
#include <TGraphAsymmErrors.h>
#include <TRandom.h>
#include <TLegend.h>

#include <TEfficiency.h>

//#include "ggEventTree.h"

#include <map>
#include <set>
#include <cmath>
//#include <algorithm>
#include <utility>
#include <fstream>
//#include <vector>

#include "SusyEventAnalyzer.h"
using namespace std;

void SusyEventAnalyzer::Loop() {
    cout<<"Inside Loop()"<<endl;
    
    if (fChain == 0) {
        cout << "fChain ==0"<< endl;
        return;
    }
    Long64_t nentries = fChain->GetEntries();
    new ggEventTree(fChain);
    event = new ggEventTree(fChain);
    cout << "total events in files  : " << nentries << endl;
    if(processNEvents <= 0 || processNEvents > nentries) processNEvents = nentries;
    
    cout << "events to be processed : " << processNEvents << endl;
    //array to keep track of cut flow of events 
    const int NCNT = 20;
    int nCnt[NCNT];
    for(int i=0; i<NCNT; i++) nCnt[i] = 0;
    
    if(printLevel>0) cout<<"Open hist file" << endl;
    TFile* fout = new TFile("hist_"+ds+".root","RECREATE");
    if(printLevel>0) cout<<"Hist file opened" << endl;
    
    fout->cd();
    //Define histograms here
    TEfficiency* h_trigEff_Lead_Trail = new TEfficiency("trigEff_Lead_Trail", "Trailing Filter Efficiency vs Photon PT; Leading Photon Pt (GeV);Efficiency",120,0.,120.);
    TEfficiency* h_trigEff_Lead_Lead = new TEfficiency("trigEff_Lead_Lead", "Leading Filter Efficiency vs Photon PT; Leading Photon Pt (GeV);Efficiency",120,0.,120.);

    TEfficiency* h_trigEff_SubLead_Trail = new TEfficiency("trigEff_SubLead_Trail", "Trailing Filter Efficiency vs Photon PT; Trailing Photon Pt (GeV);Efficiency",120,0.,120.);
    TEfficiency* h_trigEff_SubLead_Lead = new TEfficiency("trigEff_SubLead_Lead", "Leading Filter Efficiency vs Photon PT; Trailing Photon Pt (GeV);Efficiency",120,0.,120.);

    TEfficiency* h_trigEff_TotalInvMass = new TEfficiency("trigEff_TotalInvMass", "Trigger Efficiency vs Invariant Mass;Invariant Mass (GeV);Efficiency",60.,60.,120.);

    TH2F* h_2D_Pass = new TH2F("h_2D_Pass","Event efficiency as a function of leading and trailing PT;Trailing PT; Leading PT",40,0.,80.,40,0.,80.);
    TH2F* h_2D_All = new TH2F("h_2D_All","Event efficiency as a function of leading and trailing PT;Trailing PT; Leading PT",40.,0.,80.,40.,0.,80.);
    TH2F* h_2D_Efficiency = new TH2F("h_2D_Efficiency","Event efficiency as a function of leading and trailing PT;Trailing PT; Leading PT",40.,0.,80.,40.,0.,80.);

    TH1F* h_ProbePt = new TH1F("ProbePt", "Good Photon PT Spectrum", 150,0.,150.);
    TH1F* h_InvariantMass = new TH1F("InvariantMass","Invariant Mass of Tag and Probe System,Events,InvariantMass (GeV)",150, 0., 150.);
    TH1F* h_ProbeCuts = new TH1F("ProbeCuts", "ProbeCuts", 10, 0.5, 10.5);


    //Define job wide variables
    int numTagProbePairs  = 0;
    float lowInvMassCut = 75, highInvMassCut =105;
    int trailR9Filter = 17, trailIsoFilter = 1;
    int leadR9Filter  = 15, leadIsoFilter  = 16;
    bool requirePixelSeed = false;
    bool vetoPixelSeed = false;
    int numPassHiggs95 = 0, numPass1L2T =0, numPass1L0T =0, numPass0L2T =0,numPass0L0T =0 , numFail1L2T =0; 

    // to check duplicated events
    std::map<int, std::set<int> > allEvents;

    // start event looping
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
        if(jentry%10000==0){
            cout<<"Processing event number " << jentry << " of " << processNEvents <<" events." <<endl;
        }

        nb = event->GetEntry(jentry);   nbytes += nb;
        if(event->run_>=0){
            nCnt[0]++; // total number of events
            
            if(printLevel>0) cout << "Apply good run list." << endl;
            if(printLevel>0) cout<<"runNumber="<<event->run_<<"  lumiNumber="<<event->lumis_<<endl;
            if(!event->isData_)useJSON=false;
            if(useJSON){
	      if(!isInJson(event->run_,event->lumis_)) continue;
            }
        }
        
        nCnt[1]++; // total number of events that pass Json
        
        if(printLevel>0) cout << "Check duplicated events for data only." << endl;
        
        if(event->isData_){
            bool duplicateEvent = ! (allEvents[event->run_].insert(event->event_)).second;
            if(duplicateEvent){
                continue;
            }
        }
        
        nCnt[2]++;//number of events that pass duplicate check

	std::vector<int>             phoIndices;

	if(event->HLTPho_>>14&1) numPassHiggs95++;

	int nTotPhotons = event->nPho_;
	//loop over the photons, make a list of potential tag and probe objects. 
	for(int it_Pho = 0; it_Pho<nTotPhotons; it_Pho++){
	  h_ProbeCuts->Fill(1);
	  if(event->phoIDbit_->at(it_Pho)>>1&1 && abs(event->phoEta_->at(it_Pho)) < 1.4442 && event->phoR9_->at(it_Pho) > 0.8){ //photons must pass medium ID and be in the barrel
	    if(  (!requirePixelSeed || (event->phohasPixelSeed_->at(it_Pho)) ) && 
		 (!vetoPixelSeed    || !(event->phohasPixelSeed_->at(it_Pho)) ) ){  //apply pixel seed requirement/vetoes
	      h_ProbeCuts->Fill(2);
	      phoIndices.push_back(it_Pho);
	    }
	  } //end of photon passing medium ID
	} //end of looping over photons

	int leadPhoIndex = -1; 
	int trailPhoIndex = -1;
	float leadPT = 0;
	float trailPT = 0;	  
    
	//Find leading and sub-leading photons in event:
	for(unsigned int it  = 0; it < phoIndices.size(); it++){ 
	  float itET = event->phoEt_->at(phoIndices.at(it));
	  if(itET > leadPT){
	    leadPT = itET;
	    leadPhoIndex = phoIndices.at(it);
	  }
	  else if(itET > trailPT){
	    trailPT = itET;
	    trailPhoIndex = phoIndices.at(it);
	  }
	}

	if(trailPhoIndex != -1){
	  if( trailPhoIndex == leadPhoIndex) cout <<"ERROR! You messed up somewhere!"<<endl;
	  TLorentzVector leadPhoVec = PhoLorentzVector(event->phoEt_->at(leadPhoIndex), event->phoEta_->at(leadPhoIndex), event->phoPhi_->at(leadPhoIndex),event->phoE_->at(leadPhoIndex));
	  TLorentzVector trailPhoVec = PhoLorentzVector(event->phoEt_->at(trailPhoIndex), event->phoEta_->at(trailPhoIndex), event->phoPhi_->at(trailPhoIndex),event->phoE_->at(trailPhoIndex));
	  if(!(isSameObject(leadPhoVec, trailPhoVec,0.3) ) ){
	    float invMass = InvariantMass( trailPhoVec,leadPhoVec);
	    bool passHiggs = (event->HLTPho_>>14&1);
	   
	    if(leadPT > 40 && trailPT > 40){
	      h_trigEff_TotalInvMass->Fill( passHiggs , invMass );
	    }
	    if(invMass > 110){
              h_2D_All->Fill(trailPT, leadPT);
              if(passHiggs){
                h_2D_Pass->Fill(trailPT, leadPT);
              }
	    }
	    if(invMass <  highInvMassCut && invMass > lowInvMassCut){ 
	      numTagProbePairs++;
	      h_InvariantMass->Fill(invMass);

	      //First consider trailing photon, first requiring the leading photon to have PT > 40 GeV
	      if(leadPT > 40){
		bool passTrail = (event->phoFiredDoubleTrgs_->at(trailPhoIndex)>>trailR9Filter&1  ||  event->phoFiredDoubleTrgs_->at(trailPhoIndex)>>trailIsoFilter&1);
		bool passLead = (event->phoFiredDoubleTrgs_->at(trailPhoIndex)>>leadR9Filter&1  ||  event->phoFiredDoubleTrgs_->at(trailPhoIndex)>>leadIsoFilter&1);
		h_trigEff_SubLead_Trail->Fill(passTrail, event->phoEt_->at(trailPhoIndex));
		h_trigEff_SubLead_Lead->Fill(passLead,  event->phoEt_->at(trailPhoIndex));
	      }
	      //For leading photon, require the trailing photon to have PT > 25 GeV
	      if(trailPT > 25){
		bool passLead = (event->phoFiredDoubleTrgs_->at(leadPhoIndex)>>leadR9Filter&1  ||  event->phoFiredDoubleTrgs_->at(leadPhoIndex)>>leadIsoFilter&1);
                bool passTrail = (event->phoFiredDoubleTrgs_->at(leadPhoIndex)>>trailR9Filter&1  ||  event->phoFiredDoubleTrgs_->at(leadPhoIndex)>>trailIsoFilter&1);
		h_trigEff_Lead_Lead->Fill(passLead, event->phoEt_->at(leadPhoIndex));
                h_trigEff_Lead_Trail->Fill(passTrail, event->phoEt_->at(leadPhoIndex));
	      }
	    }
	  }
	}
	

    }//end of looping over the events
    cout<<"Total number of tag and probe pairs is "<<numTagProbePairs<<endl;
    cout << "Number of events passing Higgs 95 trigger is "<< numPassHiggs95<< endl;
    cout<<"Of those, "<<numPass1L2T << " have one lead and two trail, "<< numPass0L2T<<" have no lead but two trail photons, "<< numPass1L0T<<" have a lead photon but less than two trail photons, and "<<numPass0L0T<<" have no lead photon and less than two trail photons."<<endl;
    cout << "There are also "<< numFail1L2T<<" events with one lead and two trail photons that fail the trigger"<<endl;
    cout<<"Writing analysis root output to: hist_"<<ds<<".root"<<endl;
    // close the output file
    fout->cd();
    fout->Write();
    fout->Close();
    delete fout;
    
    
}//end of Loop() function





//---------------------------------------------------------------






void SusyEventAnalyzer::CategorizeEvents(int pho1, int pho2, int pho3, float Rho, bool &gogg, bool &goee, bool &goeg, bool &goff, bool &gogammafake, bool &gogf, bool &gofg, bool &use13, bool &use23){
  return;
}



void SusyEventAnalyzer::CategorizeEvents(int pho1, int pho2, float Rho, bool &gogg, bool &goee, bool &goeg, bool &goff, bool &gogammafake, bool &gogf, bool &gofg){
    //All of the photon candidates have had to pass cuts on H over E, photon isolation, and neutral hadron isolation
    //electrons and photons must also pass sigma ieta ieta and charged hadron isolation cuts. Photons must not have a pixel seed.
    //initialize all booleans to false
    bool g1=false, g2=false, f1=false, f2=false, e1=false, e2=false;
    gogg=false;goee=false;goeg=false;goff=false;gogammafake=false;gogf=false;gofg=false;
    
    if((pho1>=event->nPho_)||(pho2>+event->nPho_)){
        cout << "Photon index higher than the number of photons in the event!! Error!!"<<endl;
        cout<< "PhoOne= " <<pho1<< "  PhoTwo= "<<pho2<<"  nPho= "<<event->nPho_<<endl;
        return;
    }
    
    float maxSihih = 0.0107; //.03; //.0106;
    float maxChHadIso = 2.67;
    
    //Define the effective area for pho1 (see https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2 )
    
    float pho1Eta = event->phoEta_->at(pho1);
    float chIsoEA1=0;
    
    if(pho1Eta<1.0){
        chIsoEA1 = .0234;
    }
    else if (pho1Eta <1.479 && pho1Eta >=1.0){
        chIsoEA1 = .0189;
    }
    else if (pho1Eta <2.0 && pho1Eta >=1.479){
        chIsoEA1 = .0171;
    }
    else if (pho1Eta <2.2 && pho1Eta >=2.0){
        chIsoEA1 = .0129;
    }
    else if (pho1Eta <2.3 && pho1Eta >=2.2){
        chIsoEA1 = .0110;
    }
    else if (pho1Eta <2.4 && pho1Eta >=2.3){
        chIsoEA1 = .0074;
    }
    else if (pho1Eta >=2.4){
        chIsoEA1 = .0035;
    }
    
    //Define EA for pho 2
    
    float pho2Eta = event->phoEta_->at(pho2);
    float chIsoEA2=0;
    
    if(pho2Eta<1.0){
        chIsoEA2 = .0234;
    }
    else if (pho2Eta <1.479 && pho2Eta >=1.0){
        chIsoEA2 = .0189;
    }
    else if (pho2Eta <2.0 && pho2Eta >=1.479){
        chIsoEA2 = .0171;
    }
    else if (pho2Eta <2.2 && pho2Eta >=2.0){
        chIsoEA2 = .0129;
    }
    else if (pho2Eta <2.3 && pho2Eta >=2.2){
        chIsoEA2 = .0110;
    }
    else if (pho2Eta <2.4 && pho2Eta >=2.3){
        chIsoEA2 = .0074;
    }
    else if (pho2Eta >=2.4){
        chIsoEA2 = .0035;
    }
    
    //Sort pho1
    float pho1iso  = (event->phoPFChIso_->at(pho1) - Rho*chIsoEA1) > 0.00 ? (event->phoPFChIso_->at(pho1) - Rho*chIsoEA1) : 0.00;
    if(event->phoSigmaIEtaIEta_->at(pho1) < maxSihih && pho1iso < maxChHadIso){
        if(event->phohasPixelSeed_->at(pho1)){
            e1 = true;
        }
        else{
            g1 = true;
        }
    }
    else{  //since all the photon candidates are either electrons, photons, or fakes, if it failed the sigma ieta ieta or the charged hadron isolation cut, it must be a fake
        f1 = true;
    }
    
    //Sort pho2
    float pho2iso  = (event->phoPFChIso_->at(pho2) - Rho*chIsoEA2) > 0.00 ? (event->phoPFChIso_->at(pho2) - Rho*chIsoEA2) : 0.00;
    if(event->phoSigmaIEtaIEta_->at(pho2) < maxSihih && pho2iso < maxChHadIso){
        if(event->phohasPixelSeed_->at(pho2)){
            e2 = true;
        }
        else{
            g2 = true;
        }
    }
    else{  //since all the photon candidates are either electrons, photons, or fakes, if it failed the sigma ieta ieta or the charged hadron isolation cut, it must be a fake
        f2 = true;
    }
    
    
    //    if(fabs(event->phoEta_->at(pho1))<1.0){
    //        if( (event->phoPFNeuIso_->at(pho1)<3.5+event->phoEt_->at(pho1)*0.04+0.03*Rho) && (event->phoPFPhoIso_->at(pho1)<1.3+event->phoEt_->at(pho1)*0.005+.148*Rho) ){
    //            if( (event->phoPFChIso_->at(pho1)<2.6+0.012*Rho) &&  event->phoSigmaIEtaIEta_->at(pho1)<0.012 ){
    //                if(!(event->phohasPixelSeed_->at(pho1)))g1=true;
    //                else e1=true;
    //            }
    //            if( (event->phoPFChIso_->at(pho1)<15.+0.012*Rho) ){
    //                if((event->phoPFChIso_->at(pho1)>2.6+0.012*Rho) || event->phoSigmaIEtaIEta_->at(pho1)>0.012)f1=true;
    //            }
    //        }
    //    }//pho1 eta<1.0
    //    else{
    //        if( (event->phoPFNeuIso_->at(pho1)<3.5+event->phoEt_->at(pho1)*0.04+0.057*Rho) && (event->phoPFPhoIso_->at(pho1)<1.3+event->phoEt_->at(pho1)*0.005+.130*Rho) ){
    //            if( (event->phoPFChIso_->at(pho1)<2.6+0.010*Rho) &&  event->phoSigmaIEtaIEta_->at(pho1)<0.012 ){
    //                if(!(event->phohasPixelSeed_->at(pho1)))g1=true;
    //                else e1=true;
    //            }
    //            if( (event->phoPFChIso_->at(pho1)<15.+0.010*Rho) ){
    //                if((event->phoPFChIso_->at(pho1)>2.6+0.010*Rho) || event->phoSigmaIEtaIEta_->at(pho1)>0.012)f1=true;
    //            }
    //        }
    //    }//pho1 eta>1.0
    //    if(fabs(event->phoEta_->at(pho2)) < 1.0){
    //        if( (event->phoPFNeuIso_->at(pho2)<3.5+event->phoEt_->at(pho2)*0.04+0.03*Rho) && (event->phoPFPhoIso_->at(pho2)<1.3+event->phoEt_->at(pho2)*0.005+.148*Rho) ){
    //            if( (event->phoPFChIso_->at(pho2)<2.6+0.012*Rho) &&  event->phoSigmaIEtaIEta_->at(pho2)<0.012 ){
    //                if(!(event->phohasPixelSeed_->at(pho2)))g2=true;
    //                else e2=true;
    //            }
    //            if( (event->phoPFChIso_->at(pho2)<15.+0.012*Rho) ){
    //                if((event->phoPFChIso_->at(pho2)>2.6+0.012*Rho) || event->phoSigmaIEtaIEta_->at(pho2)>0.012)f2=true;
    //            }
    //        }
    //    }//pho2 eta<1.0
    //    else{
    //        if( (event->phoPFNeuIso_->at(pho2)<3.5+event->phoEt_->at(pho2)*0.04+0.057*Rho) && (event->phoPFPhoIso_->at(pho2)<1.3+event->phoEt_->at(pho2)*0.005+.130*Rho) ){
    //            if( (event->phoPFChIso_->at(pho2)<2.6+0.010*Rho) &&  event->phoSigmaIEtaIEta_->at(pho2)<0.012 ){
    //                if(!(event->phohasPixelSeed_->at(pho2)))g2=true;
    //                else e2=true;
    //            }
    //            if( (event->phoPFChIso_->at(pho2)<15.+0.010*Rho) ){
    //                if((event->phoPFChIso_->at(pho2)>2.6+0.010*Rho) || event->phoSigmaIEtaIEta_->at(pho2)>0.012)f2=true;
    //            }
    //        }
    //    }//pho2 eta>1.0
    
    if(g1 && g2)    gogg=true;
    if( (g1 && e2) || (e1 && g2) )  goeg=true;
    if(e1 && e2)    goee=true;
    if(f1 && f2)    goff=true;
    if( (g1 && f2) || (f1 && g2) ){
        gogammafake=true;
        if(g1 && f2)    gogf=true;
        else if(f1 && g2)   gofg=true;
    }
    
    if(gogg&&goeg)cout<<"gg AND eg event!!!!! ------- PROBLEM!"<<endl;
    if(gogg&&goee)cout<<"gg AND ee event!!!!! ------- PROBLEM!"<<endl;
    if(gogg&&goff)cout<<"gg AND ff event!!!!! ------- PROBLEM!"<<endl;
    if(gogg&&gogammafake)cout<<"gg AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(goeg&&goee)cout<<"eg AND ee event!!!!! ------- PROBLEM!"<<endl;
    if(goeg&&goff)cout<<"eg AND ff event!!!!! ------- PROBLEM!"<<endl;
    if(goeg&&gogammafake)cout<<"eg AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(goee&&goff)cout<<"ee AND ff event!!!!! ------- PROBLEM!"<<endl;
    if(goee&&gogammafake)cout<<"ee AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(goff&&gogammafake)cout<<"ff AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(gogf&&gofg)cout<<"gf AND fg event!!!!! ------- PROBLEM!"<<endl;
    if((gogammafake && !gogf) && (gogammafake && !gofg))cout<<"gammafake BUT NOT gf OR fg event!!!!! ------- PROBLEM!"<<endl;
    //if(!( gogg || goeg || goee || goff || gogammafake)) cout<<"No category made in the event!!!!! ------- "<<endl;
    return;
} //end of Categorize Event function



void SusyEventAnalyzer::MatchPhosToJets(TLorentzVector pOne, TLorentzVector pTwo, std::vector<TLorentzVector*> jetvecs, TLorentzVector &jet1, TLorentzVector &jet2, bool &hasdijetpt, float dR){
    hasdijetpt=false;
    for(std::vector<TLorentzVector*>::iterator jet_it1 = jetvecs.begin(); jet_it1 != jetvecs.end(); jet_it1++){
        if(isSameObject(pOne,*(*jet_it1),dR)){
            for(std::vector<TLorentzVector*>::iterator jet_it2 = jetvecs.begin(); jet_it2 != jetvecs.end(); jet_it2++){
                //jet2vec = ?
                if(/*jet_it2!=jet_it1*/ !isSameObject(*(*jet_it1), *(*jet_it2),0.1) ){
                    if(isSameObject(pTwo, *(*jet_it2), dR)){
                        jet1=**jet_it1;
                        jet2=**jet_it2;
                        hasdijetpt=true;
                        break;
                    }//end jet2 match
                }//end jet2!=jet1
            }//end jet2 iterator
            if(hasdijetpt){break;}
        }//end jet1 match
    }//end jet1 iterator
    return;
}//end of MatchPhosToJets function


//void SusyEventAnalyzer::MatchPhosToJets(TLorentzVector pOne, TLorentzVector pTwo, std::vector<TLorentzVector*> jetvecs, int &jet1, int &jet2, bool &hasdijetpt, float dR){
//    hasdijetpt=false;
//    TLorentzVector jet1vec, jet2vec;
//    for(std::vector<int>::iterator jet_it1 = jets.begin(); jet_it1 != jets.end(); jet_it1++){
//        //... Figure out how to make a TLorentz vector from the jet momentum here...
//        //jet1vec= ?
//        if(isSameObject(pOne,jet1vec,dR)){
//            for(std::vector<int>::iterator jet_it2 = jets.begin(); jet_it2 != jets.end(); jet_it2++){
//                //jet2vec = ?
//                if(/*jet_it2!=jet_it1*/ !isSameObject(jet1vec, jet2vec,0.1)){
//                    if(isSameObject(pTwo, jet2vec, dR)){
//                        jet1=*jet_it1;
//                        jet2=*jet_it2;
//                        hasdijetpt=true;
//                        break;
//                    }//end jet2 match
//                }//end jet2!=jet1
//            }//end jet2 iterator
//            if(hasdijetpt){break;}
//        }//end jet1 match
//    }//end jet1 iterator
//    return;
//}//end of MatchPhosToJets function



Double_t DiEMPtBins[]={0.,5.,10.,15.,20.,25.,30.,35.,40.,45.,50.,55.,60.,65.,70.,75.,80.,85.,90.,95.,100.,110.,120.,130.,140.,150.,200.,300.,400.,600.,1000.};
int numBins=sizeof(DiEMPtBins)/sizeof(Double_t)-1;

pair<float,float> SusyEventAnalyzer::GetMetReweight(float diEMPT,string type,vector< pair<float,float> > binEE[4],vector< pair<float,float> > binFF[4],vector< pair<float,float> > binFG[4],vector< pair<float,float> > binGF[4],vector< pair<float,float> > binGammaFake[4],vector< pair<float,float> > binEEsidebandLowJet[4],vector< pair<float,float> > binEEsidebandHighJet[4],int numJets){
    //if(printLevel>0)cout<<"inside GetMetReweight"<<endl;
    float reweight=1., error=0.;//,lowff=0.,highff=0.,lowee=0.,highee=0.;
    int bin=999;
    //if(printLevel>0)cout<<"Line 167"<<endl;
    if(numJets>2)numJets=2;
    int numJetsBin=numJets+1;
    //this gives the bins from 0-(numBins-1) even though they really go from 1-numBins, so that it lines up with the vector numbering
    if(diEMPT<100) bin=int(diEMPT/5);//----2.55 GeV bins so divide by that to get bin number (0-100)
    else if(diEMPT>=100 && diEMPT<150) bin=int((diEMPT+100)/10.);//----5 GeV bins so divide by that to get bin number (50-100)
    else if(diEMPT>=150 && diEMPT<200) bin=25;//bin=int((diEMPT+200)/10.);//----10 GeV bins so divide by that to get bin number (100-150)
    else if(diEMPT>=200 && diEMPT<400) bin=int((diEMPT+2400)/100.);
    else if(diEMPT>=400 && diEMPT<600) bin=28;
    else if(diEMPT>=600) bin=29;
    //if(bin>numBins)bin=numBins;
    //This was an attempt to be smart - it is incredibly slow!!! don't try to be smart...
    //TH1F* binHist = new TH1F("binHist","",numBins,DiEMPtBins);
    //  bin=binHist->FindBin(diEMPT)-1;
    if( type=="ff" ){
        reweight = binFF[numJetsBin][bin].first;
        error = binFF[numJetsBin][bin].second;
    }
    else if( type=="gf" ){
        reweight = binGF[numJetsBin][bin].first;
        error = binGF[numJetsBin][bin].second;
    }
    else if( type=="fg" ){
        reweight = binFG[numJetsBin][bin].first;
        error = binFG[numJetsBin][bin].second;
    }
    else if( type=="gammafake" ){
        reweight = binGammaFake[numJetsBin][bin].first;
        error = binGammaFake[numJetsBin][bin].second;
    }
    else if( type=="ee" ){
        reweight = binEE[numJetsBin][bin].first;
        error = binEE[numJetsBin][bin].second;
    }
    else if( type=="eeSbLow" ){
        reweight = binEEsidebandLowJet[numJetsBin][bin].first;
        error = binEEsidebandLowJet[numJetsBin][bin].second;
    }
    else if( type=="eeSbHigh" ){
        reweight = binEEsidebandHighJet[numJetsBin][bin].first;
        error = binEEsidebandHighJet[numJetsBin][bin].second;
    }
    else cout<<"Trying to reweight but have no type ee,ff,eeSbLow,eeSbHigh"<<endl;
    if(bin==-1 || bin==999 || reweight==0) {reweight=1.;error=0.;}
    //if(bin==18)cout<<"reweight: "<<reweight<<"  bin: "<<bin<<"  numJets: "<<numJets<<"  type: "<<type<<endl;
    //if(type=="ff")cout<<"bin: "<<bin<<"  reweight: "<<reweight<<"  diEMPT: "<<diEMPT<<"  numJets: "<<numJets<<"  type: "<<type<<endl;
    //if(printLevel>0)cout<<"End of GetMetReweight"<<endl;
    //delete binHist;
    return make_pair(reweight,error);
}


