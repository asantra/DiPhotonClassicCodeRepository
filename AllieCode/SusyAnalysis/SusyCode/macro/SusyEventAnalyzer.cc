//
//  Susyeventanalyzer.cc
//
//
//  Created by Allie Reinsvold on 8/4/14.
//
//

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
#include <map>
#include <set>
#include <cmath>
#include <utility>
#include <fstream>

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
  //....
  TH1F * eeweights;
  TH1F * gammafakeweights;
  TH1F * ffweights;

  Double_t MetBins[13]={0,5,10,15,20,25,30,35,40,50,70,100,275};
    
  TH1I* h_NumMuons = new TH1I("NumMuons","Number of muons that pass quality cuts;;Events",20,0,20);
    
  TH1I* h_FakeCuts = new TH1I("FakeCuts","no cuts,#eta,E_{T},hOverE,pixelCut,IsoUpperCut,!(CHiso || sihih),!CHiso,!sihih",10,0,10);
    
    
  TH1F* h_ggMetSig = new TH1F("ggMetSig",";Met Significance;Events",200,0.,500.);
  TH2F* h_ggMetSigVsSumEt = new TH2F("ggMetSigVsSumEt",";#sumE_{T};Met Significance",500,0.,5000.,200,0.,500.);
    
  TH1F* h_ggPt = new TH1F("ggPt","gg Transverse Momentum;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_ggPtLead = new TH1F("ggPtLead","gg Transverse Momentum of leading object;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_ggPtTrail = new TH1F("ggPtTrail","gg Transverse Momentum of trailing object;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_gammafakePt = new TH1F("gammafakePt","gammafake Transverse Momentum;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_gammafakePtLead = new TH1F("gammafakePtLead","gammafake Transverse Momentum of leading object;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_gammafakePtTrail = new TH1F("gammafakePtTrail","gammafake Transverse Momentum of trailing object;p_{T} (GeV);Events", 200,0.,1000.);

  TH1F* h_egPt = new TH1F("egPt","eg Transverse Momentum;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_eePt = new TH1F("eePt","ee Transverse Momentum;p_{T} (GeV);Events", 200,0.,1000.);
  TH1F* h_ffPt = new TH1F("ffPt","ff Transverse Momentum;p_{T} (GeV);Events", 200,0.,1000.);

  TH1F* h_gammafakeEta = new TH1F("gammafakeEta","gammafake #eta;#eta;Events", 350,-3.5,3.5);
  TH1F* h_gammafakePhi = new TH1F("gammafakePhi","gammafake #phi;#phi;Events", 64,-3.2,3.2);

  TH1F* h_ggEta = new TH1F("ggEta","gg #eta;#eta;Events", 350,-3.5,3.5);
  TH1F* h_ggPhi = new TH1F("ggPhi","gg #phi;#phi;Events", 64,-3.2,3.2);
  TH1F* h_met = new TH1F("met","missing transverse energy;#slash{E}_{T} (GeV);Events",100,0.,200.);
  TH1F* h_sumEt = new TH1F("sumEt","Scalar sum of all calorimeter energy;#sigmaE_{T} (GeV);Events",500,0.0,5000.);h_met->Sumw2();
  TH1F* h_sumEt_gg = new TH1F("sumEt_gg","Scalar sum of all calorimeter energy in gg events;#sigmaE_{T} (GeV);Events",500,0.0,5000.);
  TH1F* h_sumEt_gammafake = new TH1F("sumEt_gammafake","Scalar sum of all calorimeter energy in #gammaf events;#sigmaE_{T} (GeV);Events",500,0.0,5000.);
  TH1F* h_eeHT = new TH1F("eeHT","Scalar sum of calorimeter energy of objects with Pt >20 GeV in Z to ee events;HT;Events",800,0.,4000.);
  TH1F* h_ggHT = new TH1F("ggHT","Scalar sum of calorimeter energy of object with Pt >20 GeV in gg events;HT;Events",800,0.,4000.);
  TH1F* h_ffHT = new TH1F("ffHT","Scalar sum of calorimeter energy of objects with Pt >20 GeV in ff events;HT;Events",800,0.,4000.);
  TH1F* h_ffHTReweighted = new TH1F("ffHTReweighted","Scalar sum of calorimeter energy of objects with Pt >20 GeV in ff events;HT;Events",800,0.,4000.);
  TH1F* h_gammafakeHT = new TH1F("gammafakeHT","Scalar sum of calorimeter energy of objects with Pt >20 GeV in gamma fake events;HT;Events",800,0.,4000.);
  TH1F* h_gammafakeHTReweighted = new TH1F("gammafakeHTReweighted","Scalar sum of calorimeter energy of objects with Pt >20 GeV in gamma fake events;HT;Events",800,0.,4000.);

  TH1F* h_realggMet = new TH1F("realggMet","Missing transverse energy in events with two gen-level photons;#slash{E}_{T} (GeV);Events",200,0.,1000.); //to be compared with the eeMet histogram for DY to ee events to see how well the DY events model the actual MET distribution of digamma events. This histogram is only made for MC.
  TH1F* h_realggHT = new TH1F("realggHT","Scalar sum of calorimeter energy of objects with Pt >20 GeV in events with two gen-level photons;HT;Events",800,0.,4000.);
  Double_t MetBins2[24]= {0,2,5,8,11,14,17,20,25,30,35,40,45,50,57,64,71,80,90, 100,110,120,140,500};    
  TH1F* h_ggMet = new TH1F("ggMet","Missing transverse energy in gg events;#slash{E}_{T} (GeV);Events",23,MetBins2);
  h_ggMet->Sumw2();
  TH1F* h_ffMet = new TH1F("ffMet","Missing transverse energy in ff events;#slash{E}_{T} (GeV);Events",23,MetBins2);
  TH1F* h_ffMetReweighted = new TH1F("ffMetReweighted","Reweighted missing transverse energy in ff events;#slash{E}_{T} (GeV);Events",23,MetBins2);
  TH1F* h_gammafakeMet = new TH1F("gammafakeMet","Missing transverse energy in events with one photon and one fake;#slash{E}_{T} (GeV);Events",50,0.,200.);
  TH1F* h_gammafakeMetReweighted = new TH1F("gammafakeMetReweighted","Missing transverse energy in events with one photon and one fake;#slash{E}_{T} (GeV);Events",50,0.,200.);
  TH1F* h_fgMet = new TH1F("fgMet","Missing transverse energy in events with one photon and one fake;#slash{E}_{T} (GeV);Events",50,0.,200.);
  TH1F* h_gfMet = new TH1F("gfMet","Missing transverse energy in events with one photon and one fake;#slash{E}_{T} (GeV);Events",50,0.,200.);

  TH1F* h_eeMetReweighted = new TH1F("eeMetReweighted","Missing transverse energy in events with two electrons;#slash{E}_{T} (GeV);Events",12,MetBins);


  TH1F* h_egMet = new TH1F("egMet","Missing transverse energy in events with one photon and one electron;#slash{E}_{T} (GeV);Events",23,MetBins2);
  TH1F* h_eeMet = new TH1F("eeMet","Missing transverse energy in events with two electrons;#slash{E}_{T} (GeV);Events",50,0.,500.);
  TH1F* h_realggDiEMPt = new TH1F("realggDiEMPt","real gg DiEMPt;DiEMPt (GeV);Events", 400,0.,1000.);h_realggDiEMPt->Sumw2();
  TH1F* h_ggDiEMPt = new TH1F("ggDiEMPt","gg DiEMPt;DiEMPt (GeV);Events", 200,0.,1000.);h_ggDiEMPt->Sumw2();
  TH1F* h_eeDiEMPt = new TH1F("eeDiEMPt","ee DiEMPt;DiEMPt (GeV);Events", 200,0.,1000.);h_eeDiEMPt->Sumw2();

  TH1F* h_realPhosSigIetaIeta = new TH1F("realPhosSigIetaIeta","SigmaIetaIeta of Generator Level Photons Passing All Cuts;#sigma_{i#etai#eta};Events", 150,0.,.03);
  TH1F* h_fakePhosSigIetaIeta = new TH1F("fakePhosSigIetaIeta","SigmaIetaIeta of Fake Photons Passing All Cuts;#sigma_{i#etai#eta};Events", 150,0.,.03);

  TH1F* h_nTotPhotons = new TH1F("nTotPhotons","Total # of Photons Before any Cuts",10,0.,10.);
    
  TH1F* h_ggSigIetaIeta = new TH1F("ggSigIetaIeta","gg SigmaIetaIeta;#sigma_{i#etai#eta};Events", 150,0.,.03);
  TH1F* h_egSigIetaIeta = new TH1F("egSigIetaIeta","eg SigmaIetaIeta;#sigma_{i#etai#eta};Events", 30,0.,.03);
  TH1F* h_eeSigIetaIeta = new TH1F("eeSigIetaIeta","ee SigmaIetaIeta;#sigma_{i#etai#eta};Events", 30,0.,.03);
  TH1F* h_ffSigIetaIeta = new TH1F("ffSigIetaIeta","ff SigmaIetaIeta;#sigma_{i#etai#eta};Events", 30,0.,.03);
  TH1F* h_gfSigIetaIeta = new TH1F("gfSigIetaIeta","gf SigmaIetaIeta;#sigma_{i#etai#eta};Events", 30,0.,.03);

  TH2F* h_phoCands_SigIetaIeta_vs_ChHadIso = new TH2F("phoCands_SigIetaIeta_vs_ChHadIso","Sigma Ieta Ieta vs Charged Hadron Isolation of Photon Candidates passing all other cuts;#sigma_{i#etai#eta};Charged Hadron Isolation (GeV)",30,0.,.03,60,0.,30.);
  TH2F* h_ffSigIetaIeta_vs_ChHadIso = new TH2F("ffSigIetaIeta_vs_ChHadIso","Sigma Ieta Ieta vs Charged Hadron Isolation of Fakes in ff Events;#sigma_{i#etai#eta};Charged Hadron Isolation (GeV)",30,0.,.03,120,0.,30.);
  TH2F* h_ffSigIetaIeta_vs_ChHadIso_Met100 = new TH2F("ffSigIetaIeta_vs_ChHadIso_Met100","Sigma Ieta Ieta vs Charged Hadron Isolation of Fakes in ff Events;#sigma_{i#etai#eta};Charged Hadron Isolation (GeV)",40,0.,.04,100,0.,50.);
  TH2F* h_ggSigIetaIeta_vs_ChHadIso = new TH2F("ggSigIetaIeta_vs_ChHadIso","Sigma Ieta Ieta vs Charged Hadron Isolation of Photons in gg Events;#sigma_{i#etai#eta};Charged Hadron Isolation (GeV)",30,0.,.03,120,0.,30.);
  TH2F* h_gfSigIetaIeta_vs_ChHadIso = new TH2F("gfSigIetaIeta_vs_ChHadIso","Sigma Ieta Ieta vs Charged Hadron Isolation of Fakes in gf Events;#sigma_{i#etai#eta};Charged Hadron Isolation (GeV)",30,0.,.03,120,0.,30.);
  TH1F* h_ffChHadIso = new TH1F("ffChHadIso","Charged Hadron Isolation of Fakes in ff Events;Charged Hadron Isolation (GeV);Fakes",120,0.,40.);
  TH1F* h_ggChHadIso = new TH1F("ggChHadIso","Charged Hadron Isolation of Photons in gg Events;Charged Hadron Isolation (GeV);Photons",120,0.,30.);
  TH1F* h_gfChHadIso = new TH1F("gfChHadIso","Charged Hadron Isolation of Fakes in gf Events;Charged Hadron Isolation (GeV);Fakes",120,0.,30.);

  TH1F* h_ggInvarMass = new TH1F("ggInvarMass","gg Invariant Mass;(GeV);Events", 200,0.,1000.);
  TH1F* h_eeInvarMassFullRange = new TH1F("eeInvarMassFullRange","ee Invariant Mass for all InvarMass;(GeV);Events", 2004,0.,1002.);
    
  TH1F* h_nHTJets_gg = new TH1F("nHTJets_gg","Number of HT jets in gg sample",10,0,10);
  TH1F* h_nHTJets_gammafake = new TH1F("nHTJets_gammafake","Number of HT jets in gammafake sample",10,0,10);
  TH1F* h_nHTJets_ee = new TH1F("nHTJets_ee","Number of HT jets in ee sample",10,0,10);
  TH1F* h_nHTJets_ff = new TH1F("nHTJets_ff","Number of HT jets in ff sample",10,0,10);
  TH1F* h_nHTJets_realgg = new TH1F("nHTJets_realgg","Number of HT jets in real gg sample",10,0,10);

  TH1F* h_ggHighestJetEnergy = new TH1F("ggHighestJetEnergy","Pt of most energetic jet in gg events;Energy (GeV);Events",150,0,300.);
  TH1F* h_eeHighestJetEnergy = new TH1F("eeHighestJetEnergy","Pt of most energetic jet in ee events;Energy (GeV);Events",150,0,300.);
  TH1F* h_gammafakeHighestJetEnergy = new TH1F("gammafakeHighestJetEnergy","Pt of most energetic jet in gf events;Energy (GeV);Events",150,0,300.);
  TH1F* h_ffHighestJetEnergy = new TH1F("ffHighestJetEnergy","Pt of most energetic jet in ff events;Energy (GeV);Events",150,0,300.);

  TH1F* h_ffJetEnergy = new TH1F("ffJetEnergy","Pt of jets in ff events;Energy (GeV);Events",150,0,300.);
  TH1F* h_ggJetEnergy = new TH1F("ggJetEnergy","Pt of jets in gg events;Energy (GeV);Events",150,0,300.);
  TH1F* h_eeJetEnergy = new TH1F("eeJetEnergy","Pt of jets in ee events;Energy (GeV);Events",150,0,300.);
  TH1F* h_gammafakeJetEnergy = new TH1F("gammafakeJetEnergy","Pt of jets in gammafake events;Energy (GeV);Events",150,0,300.);

  TH1F* h_ggcomposition = new TH1F("ggcomposition","Truth level composition of gg events; ; Events",3,0,3);    

  //insert new histogram definitions here

  fout->cd();
        
    
  //Define job wide variables
  int triggerIndex = 14; //bit with trigger information in the ggNtuples

  double diEMpt = 0;
  double InvMass;
  double muMass = 0.1057;  //muon mass, to be used to make the Lorentz vectors needed to find the invariant mass of two objects
  int nTwoCands = 0; //number of events with two photon candidates that pass all the cuts

  int weirdEvents[] = {};

  float PUweight=1.0;
  int nff_Met100 = 0;
    
  //Indices and momentum of the two photon candidates
  int PhoOne =-1, PhoTwo =-1, PhoThree = -1;
  TLorentzVector PhoOneVec, PhoThreeVec;
  TLorentzVector PhoTwoVec;// = &(new TLorentzVector());
  float dPhi;
  //counters for the number of events
  int  ngg=0, neg=0, nff=0;
  int nggMET0to50 = 0, nggMET50to100 =0, nggInvMass110 = 0;
  int nPhoCandsTotal=0,nFakeCandsTotal=0;
  //counters for things I want to keep track of
  int numGammaFake =0;

  fout->cd();
  //Read in the weights histograms located in reweights.root
  if(printLevel>0)cout<<"Read in weights histogram" << endl;
  TFile *f_weights = TFile::Open("reweights.root","READ");
  if(printLevel>0)cout<<"Weights histogram read in" << endl;
  f_weights->cd();
    
  TString eeWeightString = "ee_DiEMPtReweights";
  TH1F* eeweights1 = (TH1F *) f_weights->Get(eeWeightString);
  eeweights1->SetName("eeweights1");
  eeweights1->Draw();
    
  TH1F* ffweights1= (TH1F *) f_weights->Get("ff_DiEMPtReweights");
  ffweights1->SetName("ffweights1");
  ffweights1->Draw();
    
  TH1F* gammafakeweights1 = (TH1F *) f_weights->Get("gf_DiEMPtReweights");
  gammafakeweights1->SetName("gammafakeweights1");
  gammafakeweights1->Draw();
 
  fout->cd();
  ffweights = (TH1F*)f_weights->FindObject("ffweights1");
  ffweights->SetName("ffweights");
  gammafakeweights = (TH1F*)f_weights->FindObject("gammafakeweights1");
  gammafakeweights->SetName("gammafakeweights");
    
  eeweights=(TH1F*)f_weights->FindObject("eeweights1");
  eeweights->SetName("eeweights");
    
    
  if(printLevel>0)cout<<"Line: "<<__LINE__<<endl;
  fout->cd();
  if(printLevel>0)cout<<"Line: "<<__LINE__<<endl;
    
  fout->cd();


  cout<<"Past all of the weight histrogram definitions!"<<endl;

  fout->cd();
    
  // to check duplicated events
  std::map<int, std::set<int> > allEvents;
  fout->cd();

  // start event looping
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry < processNEvents; jentry++) {
    

    if(jentry%10000==0){
      cout<<"Processing event number " << jentry << " of " << processNEvents <<" events." <<endl;
    }
      

    for(unsigned int i = 0; i < 4; i++){
      if( event->event_ == weirdEvents[i]){
	cout << "Event to check! Event number "<< event->event_ << " and run number "<<event->run_ << endl;
	cout << "Trigger bits in  HLTPho = " << ( event->HLTPho_>>15&1)<< ", " <<( event->HLTPho_>>16&1)<< ", " <<( event->HLTPho_>>17&1) << endl;
	cout << "Met filters = " << event->metFilters_ << endl;
	cout << "Number of vertices = " << event->nVtx_ << endl;
	cout << "Met = " << event->pfMET_ << endl;
      }
    }
  

    nb = event->GetEntry(jentry);   nbytes += nb;
        
    if(event->run_>=0){
      nCnt[0]++; // total number of events
            
      if(printLevel>0) cout << "Apply good run (JSON) list." << endl;
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
	cout<<"Duplicate Event! Run "<<event->run_<<" Event "<<event->event_<<endl;
	continue;
      }
    }
        
    nCnt[2]++;//number of events that pass duplicate check
        
    if(printLevel>0) cout << "Apply trigger selection in the event." << endl;
    bool passHLT = (useTrigger ?  event->HLTPho_>>triggerIndex&1 : true);//( (event->HLTPho_>>15&1)  || (event->HLTPho_>>16&1)|| (event->HLTPho_>>17&1) || ( event->HLTPho_>>triggerIndex&1)) : true);
    if(!passHLT ) continue;//only accept events which pass our trigger(s)
    nCnt[3]++;// number of events that pass trigger
       
    float Rho = event->rho_;
    int NVertex=event->nVtx_;
        
    //Require at least one good vertex
    if(NVertex<1){
      if(printLevel>0){cout<<"No Good Vertex!!!!  Run: "<<event->run_<<"  Event: "<<event->event_<<endl;}
      continue;
    }
    nCnt[4]++;// number of events that pass nVertex>=1
        

    //pass MET filters
    if(event->metFilters_ > 0 ){
      if(printLevel>0){cout<<"Fail MET filters! Run: "<<event->run_<<"  Event: "<<event->event_<<endl;}
      continue;
    }
    nCnt[5]++;//number of events that pass met filters
  
    float met = event->pfMET_;
    float metSumEt = event->pfMETsumEt_;
    TVector2* metvec = new TVector2();
    metvec->SetMagPhi(met, event->pfMETPhi_);
    h_met->Fill(met);
    h_sumEt->Fill(metSumEt);
        
    //-------------Gen Photons------------------------------    
    int nGenPhos = 0;
    std::vector<int> genPhosIndices;
    if(!event->isData_){
      for(int Part_it = 0; Part_it < event->nMC_; Part_it++){
	int partPdgID = event->mcPID->at(Part_it);
	//Find all of the real photons in the event, so we can check later to see if the reconstructed photons match any of the gen-level photons
	if(fabs(partPdgID)==22){
	  nGenPhos++;
	}                    
	genPhosIndices.push_back(Part_it);   
      }
    }
    //-------------End of gen Photons------------------------------ 

    //------------Muons--------------------------------------
    //We trust muons more than any other object, so make a list of them first. Any other photons, electrons, or jets that overlap with a muon will be removed
    std::vector<TLorentzVector> looseMuons;//we will veto any jets which overlap with these muons when calculating ST  
    TLorentzVector thisMuon;
    float muPtCut = 30;
    float muEtaCut = 1.4442;
    for(int it_Mu = 0; it_Mu < event->nMu_; it_Mu++){
      float pt = event->muPt_->at(it_Mu);
      float eta = event->muEta_->at(it_Mu);
      float combIso  = event->muPFChIso_->at(it_Mu) + TMath::Max(0.,event->muPFNeuIso_->at(it_Mu) + event->muPFPhoIso_->at(it_Mu) - 0.5*event->muPFPUIso_->at(it_Mu));
      if(pt > muPtCut && event->muIsMediumID_->at(it_Mu) && abs(eta) < muEtaCut && combIso/pt > 0.25 ) {
	thisMuon = MassLorentzVector(pt, eta, event->muPhi_->at(it_Mu), muMass);
	looseMuons.push_back(thisMuon);
      }
    }

    h_NumMuons->Fill((int)looseMuons.size());
    //------------End muons------------------------------------
        
       
        
    //find photons, sort by energy, define cuts on photons
    //---------------------Photons (and electrons and fakes)------------------------------------------
    //Medium cut based photon id developed during Spring15: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2
    //cut values for Run2
    double maxHoverE = 0.05;
    double minSietaieta = 0.005;
    double looseSietaieta = 0.0102;
    double maxSietaieta = 0.0102; // 0.03; //0.0106;
    double upperCutSietaieta = 0.0150;
    double looseChIso = 3.32;
    double maxChIso = 1.37;  //this is the maximum rho-corrected isolation.
    double upperCutChIso = 40.0;//15.0; // an upper cut on the charged hadron isolation for fakes
    double maxNeuIso = 1.06; // + 0.014*pho_pt + 0.000019*pho_pt^2
    double maxPhoIso = 0.28, //+.0053*Photon pt
      maxEta = 1.4442;
        
        
    //find photons, sort by energy, define cuts on photons
    double EtCutValue    = 40.0;
    // maxMETdphi    =2.8;
    //***Set to a different value if we want to cut on the angle between the jets and the MET
    //minJetMETdphi     =0.5;
        
    typedef std::multimap<float, int, std::greater<float> > mmid;                                           
    //   The photons will be sorted in the maps by pt so we can select the two with the largest Pt.
    mmid  pho_Cands;
    mmid  uncleanedPhotons, uncleanedFakes, uncleanedEles;

    int nFakeCands = 0, nEleCands = 0, nPhoCands =0;

    std::vector<TLorentzVector> cleanedPhotons, cleanedEles;
  
    //Loop over the photon collection!!!
    int nTotPhotons = event->nPho_;
    h_nTotPhotons->Fill(nTotPhotons);
    //ignore event if there are not at least 2 photon candidates
    if(event->isData_){
      if(nTotPhotons < 2) continue; //Stop analyzing the event if there are not at least 2 pho candidates
    }
        
    for(int it_Pho = 0; it_Pho<nTotPhotons; it_Pho++){
      if(printLevel>0) cout<<"looping over photon collection"<<endl;
      //do things that want all photons with no cuts here: ie fill all histograms and such
      h_FakeCuts->Fill(0);
      double phoEta = std::abs(event->phoSCEta_->at(it_Pho));

      if(phoEta >= maxEta){ //only consider barrel photons
	continue;
      }
      //bool PhoEtaCut = phoEta < maxEta;
      //--------------Define rho-corrected isolations------  see https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2
            
      bool photonID, fakeID, electronID;
            
      float chIsoEA=0, neuIsoEA=0, phoIsoEA=0;
            
      if(phoEta<1.0){
	chIsoEA = 0.0;
	neuIsoEA = .0599;
	phoIsoEA= 0.1271;
      }
      else if (phoEta <1.479 && phoEta >=1.0){
	chIsoEA = 0.0;
	neuIsoEA = .0819;
	phoIsoEA= 0.1101;
      }
      else if (phoEta <2.0 && phoEta >=1.479){
	chIsoEA = 0.0;
	neuIsoEA = .0696;
	phoIsoEA=.0756;
      }
      else if (phoEta <2.2 && phoEta >=2.0){
	chIsoEA = 0.0;
	neuIsoEA = .0360;
	phoIsoEA=  .1175;
      }
      else if (phoEta <2.3 && phoEta >=2.2){
	chIsoEA = 0.0;
	neuIsoEA = .0360;
	phoIsoEA=  .1498;
      }
      else if (phoEta <2.4 && phoEta >=2.3){
	chIsoEA = 0.00;
	neuIsoEA = .0462;
	phoIsoEA=  .1857;
      }
      else if (phoEta >=2.4){
	chIsoEA = 0.0;
	neuIsoEA = .0656;
	phoIsoEA=  .2183;
      }
            
      //----------------set up cuts-------------------
      float PhoEt= event->phoEt_->at(it_Pho);
      float PhoHoverE = event->phoHoverE_->at(it_Pho);            
      float PhoSIetaIeta = event->phoSigmaIEtaIEta_->at(it_Pho);
      float PhoR9 = event->phoR9_->at(it_Pho);
      //uncorrected isolations
      float uncorrNeuHadIso = event->phoPFNeuIso_->at(it_Pho);
      float uncorrChHadIso = event->phoPFChIso_->at(it_Pho);
      float uncorrPhoIso = event->phoPFPhoIso_->at(it_Pho);
            
      //These are the pile-up corrected isolations
      float chargedHadronIso= uncorrChHadIso - Rho*chIsoEA > 0. ? uncorrChHadIso - Rho*chIsoEA : 0.00 ;
      float neutralHadronIso= ( uncorrNeuHadIso - Rho*neuIsoEA - 0.014*PhoEt - 0.000019*PhoEt*PhoEt ) > 0.00 ? uncorrNeuHadIso - Rho*neuIsoEA - 0.014*PhoEt - 0.000019*PhoEt*PhoEt: 0.00;
      float photonIso = ( uncorrPhoIso - Rho*phoIsoEA - 0.0053*PhoEt ) > 0.00 ? uncorrPhoIso - Rho*phoIsoEA - 0.0053*PhoEt : 0.00;

      // Et cuts
      bool EtCut = (PhoEt > EtCutValue);
            
      // H/E
      bool heCut = (PhoHoverE < maxHoverE);
      // sigma_ietaieta
      bool sIetaCut = (PhoSIetaIeta < maxSietaieta);
      bool upperSIetaCut = (PhoSIetaIeta< upperCutSietaieta);
      bool looseSIetaCut = (PhoSIetaIeta< looseSietaieta);
      bool minSIetaCut = (PhoSIetaIeta > minSietaieta);
      //R9
      bool R9Cut = (PhoR9 < 1.0);

      //isolation cuts
      bool looseChHadIsoCut = chargedHadronIso < looseChIso;
      bool chHadIsoCut = chargedHadronIso < maxChIso;
      bool upperChIsoCut = chargedHadronIso < upperCutChIso; //for fakes
      bool neuHadIsoCut = neutralHadronIso < maxNeuIso;
      bool phoIsoCut = photonIso < maxPhoIso;

      bool pixelCut = !event->phohasPixelSeed_->at(it_Pho);

      for(unsigned int i = 0; i < 4; i++){
	if( event->event_== weirdEvents[i]){
	  cout << "---------------------------------------------------" << endl;
	  cout <<"Photon candidate " << it_Pho << " has Pt " << PhoEt<< ", Phi = ,"<<event->phoPhi_->at(it_Pho) << " and Eta " << event->phoEta_->at(it_Pho) <<endl;
	  cout <<"H/E = " << PhoHoverE <<  ", cut = " << heCut<< endl;
	  cout <<"Sig ieta ieta = " << PhoSIetaIeta <<  ", cut = sIetaCut" << sIetaCut << endl;
	  cout <<"PhoR9 = " << PhoR9 <<  ", cut = " << R9Cut << endl;
	  cout <<"Corrected charged hadron isolation = " << chargedHadronIso <<  ", cut = " << chHadIsoCut <<endl;
	  cout <<"Corrected photon isolation  = " << photonIso <<  ", cut = " << phoIsoCut <<endl;
	  cout <<"Corrected neutral hadron isolation = " << neutralHadronIso << ", cut = " << neuHadIsoCut<< endl;
	  cout << "Pixel seed veto = " << event->phohasPixelSeed_->at(it_Pho) << ", cut = " << pixelCut << endl;
	  cout << "---------------------------------------------------" << endl;
	}
      }

      //photonID = ( EtCut && (event->phoIDbit_->at(it_Pho)>>1&1) && pixelCut && R9Cut); 
      photonID = ( EtCut && heCut && neuHadIsoCut && phoIsoCut && chHadIsoCut && sIetaCut && pixelCut && R9Cut && minSIetaCut);
      electronID = ( EtCut && heCut && neuHadIsoCut && phoIsoCut && chHadIsoCut && sIetaCut && !pixelCut && R9Cut && minSIetaCut);
      //fakeID =   ( EtCut && heCut && neuHadIsoCut && phoIsoCut && R9Cut &&  upperChIsoCut && (!chHadIsoCut || !sIetaCut) && upperSIetaCut && pixelCut && !(!chHadIsoCut && !sIetaCut) && minSIetaCut );
      fakeID =   ( EtCut && heCut && /* neuHadIsoCut &&  phoIsoCut && */ R9Cut && upperChIsoCut && (!chHadIsoCut || !sIetaCut) && upperSIetaCut &&  pixelCut /* && !(!chHadIsoCut && !sIetaCut)*/ );
      //fakeID =   ( EtCut && /*heCut && neuHadIsoCut && phoIsoCut && R9Cut &&  upperChIsoCut &&*/ (!chHadIsoCut || !sIetaCut) /*&& upperSIetaCut && pixelCut && !(!chHadIsoCut && !sIetaCut) */);
      if(EtCut && heCut && neuHadIsoCut && phoIsoCut && R9Cut){
	h_phoCands_SigIetaIeta_vs_ChHadIso->Fill(PhoSIetaIeta ,chargedHadronIso );
      }
            
      h_FakeCuts->Fill(1);
      if(EtCut){
	h_FakeCuts->Fill(2);
	if(heCut){
	  h_FakeCuts->Fill(3);
	  if(neuHadIsoCut){
	    h_FakeCuts->Fill(4);
	    if(phoIsoCut){
	      h_FakeCuts->Fill(5);
	      if(chHadIsoCut){
		h_FakeCuts->Fill(6);
		if(sIetaCut){
		  h_FakeCuts->Fill(7);
		  if(pixelCut){
		    h_FakeCuts->Fill(8);
		    if(R9Cut){
		      h_FakeCuts->Fill(9);
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
            
            
      if(photonID){
	nPhoCandsTotal++;
	nPhoCands++;
	uncleanedPhotons.insert(mmid::value_type(PhoEt, it_Pho));
      }
      if(fakeID){
	nFakeCands++;
	nFakeCandsTotal++;
	uncleanedFakes.insert(mmid::value_type(PhoEt, it_Pho));
      }
      if(electronID){
	nEleCands++;
	uncleanedEles.insert(mmid::value_type(PhoEt, it_Pho));
      }
            
      if(printLevel>0) cout<<"End of Photon Loop"<<endl;
    }//end of photon loop
    //cout<<"end of photon loop"<<endl;



    //Now clean eles, photons, and fakes from muons and from each other
    //Remove electrons that overlap within dR < 0.3 of a muon
    for (mmid::const_iterator iele = uncleanedEles.begin(); iele != uncleanedEles.end(); iele++){
      bool overlapMu = false;
      TLorentzVector thisEle = PhoLorentzVector(iele->first, event->phoEta_->at(iele->second), event->phoPhi_->at(iele->second),event->phoE_->at(iele->second));
      for(unsigned int imu = 0;imu<looseMuons.size(); imu++){
	if(getDR(looseMuons.at(imu),thisEle) < 0.3) overlapMu = true;
      }
      if(!overlapMu){
	cleanedEles.push_back(thisEle);
	pho_Cands.insert(mmid::value_type(iele->first, iele->second ) );
      }
      if(overlapMu){
        for(unsigned int i = 0; i < 4; i++){
	  if( event->event_== weirdEvents[i]){
            cout << "Electron " << iele->second << " removed due to cleaning!" << endl;
          }
        }
      }
    }
    //Remove photons that overlap within dR < 0.3 of an electron or muon
    for (mmid::const_iterator ipho = uncleanedPhotons.begin(); ipho != uncleanedPhotons.end(); ipho++){
      bool overlap = false;
      TLorentzVector thisPho = PhoLorentzVector(ipho->first, event->phoEta_->at(ipho->second), event->phoPhi_->at(ipho->second),event->phoE_->at(ipho->second));
      for(unsigned int imu = 0;imu<looseMuons.size(); imu++){
        if(getDR(looseMuons.at(imu),thisPho) < 0.3) overlap = true;
      }
      for(unsigned int iele = 0; iele < cleanedEles.size(); iele++){
	if(getDR(cleanedEles.at(iele), thisPho) < 0.3) overlap = true;
      }
      if(!overlap){
        cleanedPhotons.push_back(thisPho);
	pho_Cands.insert(mmid::value_type(ipho->first, ipho->second ) );
      } 
      if(overlap){
        for(unsigned int i = 0; i < 4; i++){
	  if( event->event_== weirdEvents[i]){
            cout << "Photon " << ipho->second << " removed due to cleaning!" << endl;
          }
        }
      }
    }
    //Remove fakes that overlap within dR < 0.4 of an electron, muon or photon (same cleaning as for jets)
    for (mmid::const_iterator ifake = uncleanedFakes.begin(); ifake != uncleanedFakes.end(); ifake++){
      bool overlap = false;
      TLorentzVector thisFake = PhoLorentzVector(ifake->first, event->phoEta_->at(ifake->second), event->phoPhi_->at(ifake->second),event->phoE_->at(ifake->second));
      for(unsigned int imu = 0;imu<looseMuons.size(); imu++){
	if(getDR(looseMuons.at(imu),thisFake) < 0.4) overlap = true;
      }
      for(unsigned int iele = 0; iele < cleanedEles.size(); iele++){
	if(getDR(cleanedEles.at(iele), thisFake) < 0.4) overlap = true;
      }
      for(unsigned int ipho = 0; ipho < cleanedPhotons.size(); ipho++){
        if(getDR(cleanedPhotons.at(ipho), thisFake) < 0.4) overlap = true;
      }
      if(!overlap){
        pho_Cands.insert(mmid::value_type(ifake->first, ifake->second ) );
      }
      if(overlap){
	for(unsigned int i = 0; i < 4; i++){
	  if( event->event_== weirdEvents[i]){
	    cout << "Fake Photon " << ifake->second << " removed due to cleaning!" << endl;
	  }
	}
      }
    }

        
    if(printLevel>0)cout<<"phoCands size= "<<pho_Cands.size()<<endl;
    if(printLevel>0)cout<<"Number of fake candidates= "<<nFakeCands<<endl;
        
    //Now back to photons
        
    if(printLevel>0)cout<<"Just sorted pho and fake Cands, about to create PhoOne and PhoTwo"<<endl;
    bool breakPho=false; 
    bool dogg=false,doee=false,doeg=false,doff=false,dogammafake=false,dogf=false,dofg=false;
    bool use13, use23;
    bool TwoPhos=false;
    PhoOne = -1;
    PhoTwo = -1;
    PhoThree = -1;

    //If there are at least 2 photon candidates, check to make sure they are well separated
    if( pho_Cands.size()>=2){

      //This makes sure the two pho objects are separated by dR > 0.4
      breakPho=false;
      mmid::const_iterator phoendminusone = pho_Cands.end();
      phoendminusone--;

      for(mmid::const_iterator pho_it = pho_Cands.begin();pho_it != (phoendminusone); pho_it++){
	if(breakPho) break;
	//recall PhoOne is the index of the first photon
	PhoOne= pho_it->second;
	PhoOneVec = PhoLorentzVector(pho_it->first, event->phoEta_->at(pho_it->second), event->phoPhi_->at(pho_it->second),event->phoE_->at(pho_it->second));                
	
	TLorentzVector PhoTwoCandVector, PhoThreeCandVector;
	mmid::const_iterator pho_it_next = pho_it;
	pho_it_next++;
	for(mmid::const_iterator pho_it2 = pho_it_next;pho_it2!=pho_Cands.end();pho_it2++){
	  PhoTwoCandVector = PhoLorentzVector(pho_it2->first, event->phoEta_->at(pho_it2->second), event->phoPhi_->at(pho_it2->second),event->phoE_->at(pho_it2->second));
                    
	  //require dR>0.3
	  if( !isSameObject(PhoOneVec, PhoTwoCandVector,0.3)){
	    PhoTwo= pho_it2->second;
	    PhoTwoVec = PhoTwoCandVector;
	    //      cout<<"Pho2 defined!"<<endl;
	    TwoPhos=true;
	    pho_it_next = pho_it2;
	    pho_it_next++;
	    breakPho = true;
	    for( mmid::const_iterator pho_it3 = pho_it_next; pho_it3 != pho_Cands.end(); pho_it3++){   
	      if(pho_it3->second > nTotPhotons) cout << "PROBLEM with pho_it3!!!" << endl;
	      PhoThreeCandVector = PhoLorentzVector(pho_it3->first, event->phoEta_->at(pho_it3->second), event->phoPhi_->at(pho_it3->second),event->phoE_->at(pho_it3->second));
	      if(   !isSameObject(PhoOneVec, PhoThreeCandVector,0.3) && !isSameObject(PhoTwoVec, PhoThreeCandVector, 0.3) ){
		PhoThree = pho_it3->second;
		PhoThreeVec = PhoThreeCandVector;
	      }
	    }
            break;  //Use break to stop looping with pho_it2                      
	  }           //end check that the two photon candidates are not the same object
	  else{      //if photons are too close, keep trying to find a second candidate
	    if(printLevel>0)cout <<"Photons fail DR separation requirement"<< "  Run: "<<event->run_<<"  Event: "<<event->event_<<"\n";
	    for(unsigned int i = 0; i < 4; i++){
	      if( event->event_== weirdEvents[i]){
		cout << "PhosFailDR!"<< "  Run: "<<event->run_<<"  Event: "<<event->event_<< endl;
	      }
	    }
	  }
	}//end pho_it2 loop
      } //end pho_it loop
    }//end of if two photons
        
        
    if(!TwoPhos){            //If there aren't two photon candidates passing all the selection criteria, move on to the next event 
      for(unsigned int i = 0; i < 4; i++){
	if( event->event_== weirdEvents[i]){
	  cout << " Less than two good photons!" << endl;
	}
      }
      continue;
    }
    nTwoCands++;
    //From here on out we are only looking at cases with 2 photon candidates

    //-------------Jets------------------------------------//
    int nJet = event->nJet_;
    std::map<float,int>    jetMap;
    vector<TLorentzVector> cleanJets;        //looseID+eta+pt+gamma/e/mu cuts
    double jetPt_cut = 30.0;
    double jetEta_cut = 2.4;
    int JetCounter = 0;
    for(int ijet=0; ijet<nJet; ijet++){            
      TLorentzVector thisJet;
      thisJet.SetPtEtaPhiM(event->jetPt_->at(ijet), event->jetEta_->at(ijet), event->jetPhi_->at(ijet), 0.00);
      jetMap[thisJet.Pt()] = ijet;
            
      if( event->jetPFLooseId_->at(ijet) ==0 ) continue;            
      if( thisJet.Pt() <jetPt_cut || TMath::Abs((thisJet.Eta())>jetEta_cut)) continue;
           
      bool overlapping = false;
      for(unsigned int ipho = 0; ipho<cleanedPhotons.size(); ipho++){
	if(getDR(cleanedPhotons.at(ipho), thisJet) < 0.4) overlapping = true; //remove jets that overlap with photons
      }
            
      for(unsigned int iele = 0;iele< cleanedEles.size(); iele++){
	if(getDR(cleanedEles.at(iele),thisJet) < 0.4) overlapping = true; //remove jets that overlap with electrons
      }
           
      for(unsigned int imu = 0;imu<looseMuons.size(); imu++){
	if(getDR(looseMuons.at(imu),thisJet) < 0.4) overlapping = true; //remove jets that overlap with muons
      }            

      if(overlapping) continue;

      cleanJets.push_back(thisJet);
      JetCounter++;
    }
        
    //obtain HT and MHT from cleaned jets
    float HT  = 0;
    float mHT = 0;
    TLorentzVector MHTvec;
    int nHTJets = cleanJets.size();
    float highestJetEnergy = 0;
    for(unsigned int jj=0; jj<cleanJets.size(); jj++){
      HT     = HT + cleanJets[jj].Pt();
      MHTvec = MHTvec + cleanJets[jj];
      if(cleanJets[jj].Pt() > highestJetEnergy){
	highestJetEnergy = cleanJets[jj].Pt();
      }
    }
    //Add electron pt to HT 
    for(unsigned int iele = 0;iele<cleanedEles.size(); iele++){
      HT = HT + cleanedEles.at(iele).Pt();
      MHTvec = MHTvec + cleanedEles.at(iele);
    }
    //Now add the contribution from muons
    for(unsigned int imu = 0;imu<looseMuons.size(); imu++){
      HT = HT + looseMuons.at(imu).Pt();
      MHTvec = MHTvec + looseMuons.at(imu);
    } 
    //Now add photon contribution
    for(unsigned int ipho = 0; ipho<cleanedPhotons.size(); ipho++){
      HT = HT+ cleanedPhotons.at(ipho).Pt();
      MHTvec = MHTvec + cleanedPhotons.at(ipho);
    }
    //	cout<<"HT = " << HT<<endl;
    TLorentzVector MHtvec = - MHTvec;
    mHT = MHtvec.Pt();
        
        
    //Sort the events!
    CategorizeEvents(PhoOne,PhoTwo,PhoThree,Rho,dogg,doee,doeg,doff,dogammafake,dogf,dofg, use13,use23);
    if(use13 && use23) cout << "Problem! Set to use both 13 and 23!" << endl;
    if(use13){
      PhoTwoVec = PhoThreeVec;
      PhoTwo = PhoThree;
    }
    if(use23){
      PhoOneVec = PhoTwoVec;
      PhoOne = PhoTwo;
      PhoTwo = PhoThree;
      PhoTwoVec = PhoThreeVec;
    }
    InvMass=InvariantMass(PhoOneVec, PhoTwoVec);        
    diEMpt=GetDiEmPt(PhoOneVec,PhoTwoVec);
    dPhi = std::fabs(TVector2::Phi_mpi_pi(event->phoPhi_->at(PhoOne) - event->phoPhi_->at(PhoTwo)));    

    for(unsigned int i = 0; i < 4; i++){
      if( event->event_== weirdEvents[i]){
	cout << "Invariant mass = " << InvMass << endl;
	cout << "PhoOne = " << PhoOne << ", and PhoTwo = "  << PhoTwo << endl;
	cout << "ee event? " << doee << endl;
      }
    }

    if( dogg && InvMass > 105){
      if(printLevel>0)cout<<"Inside gg"<<endl;
      ngg++;
      if (met < 50) nggMET0to50++;
      if( met > 50 && met < 100) nggMET50to100++;
      if(InvMass > 110) nggInvMass110++;

      //Try to find the gen level particles that match the photons most closely. The matching particle will have the smallest dR between it and the photon, and the difference between its pt and the photon's pt must be less than 15%
      float drClose1=999., drClose2=999.;
      int PhoOneGen, PhoTwoGen;
      bool goForGen=false,  goForGen1=false, goForGen2=false;
            
      for(int i =0; i < event->nMC_; i++){
	TLorentzVector part_it_vec = MassLorentzVector(event->mcPt->at(i), event->mcEta->at(i), event->mcPhi->at(i), event->mcMass->at(i));
	if(event->mcStatus->at(i)==1){
	  if(getDR(PhoOneVec, part_it_vec)<drClose1 && abs(event->phoEt_->at(PhoOne) - event->mcPt->at(i))/(event->phoEt_->at(PhoOne)) < 0.15){
	    drClose1 = getDR(PhoOneVec, part_it_vec);
	    PhoOneGen=i;
	    goForGen1=true;
	  }
	  if(getDR(PhoTwoVec, part_it_vec)<drClose2 && abs(event->phoEt_->at(PhoTwo) - event->mcPt->at(i))/(event->phoEt_->at(PhoTwo)) < 0.15){
	    drClose2 = getDR(PhoTwoVec, part_it_vec);
	    PhoTwoGen=i;
	    goForGen2=true;
	  }
	}
	if(goForGen1 && goForGen2){
	  goForGen=true; //This flag is set if both photon objects are matched to gen level objects.
	}
      }
            
      bool phoOneMatch = false, phoTwoMatch = false;
      if(goForGen1){
	//If the matching gen particle is a photon, fill histograms
	if(event->mcPID->at(PhoOneGen)==22){
	  phoOneMatch = true;
	  //fill sigma ieta ieta histogram to get the shape for real photons
	  h_realPhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
	}
	else{//If the matching gen particle isn't a photon, it is a fake
	  phoOneMatch = false;
	  //fill fake sigma ieta ieta histogram to get the shape for fakes
	  h_fakePhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
	}
      }
      else{
	//if the photon object is undefined, fill the fake histogram
	h_fakePhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
      }
      if(goForGen2){
	if(event->mcPID->at(PhoTwoGen)==22){
	  phoTwoMatch = true;
	  //fill sigma ieta ieta histogram to get the shape for real photons
	  h_realPhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
	}
	else{
	  phoTwoMatch = false;
	  //fill fake sigma ieta ieta histogram to get the shape for fakes
	  h_fakePhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
	}
      }
      else{
	//if the photon object is undefined, fill the fakes histogram
	h_fakePhosSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
      }
      if(phoOneMatch && phoTwoMatch){//If both of the photons correspond to actual photons, then we have a real di-gamma event. Plot the MET of these events, to be compared with the MET spectrum of the DY to EE events we use to model the di-gamma distribution.
	h_realggHT->Fill(HT);
	h_realggMet->Fill(met);
	h_realggDiEMPt->Fill(diEMpt);
	h_ggcomposition->Fill(0.5);
	h_nHTJets_realgg->Fill(nHTJets); 
      }
      else if((phoOneMatch && !phoTwoMatch)||(!phoOneMatch && phoTwoMatch) ){//gf events
	h_ggcomposition->Fill(1.5);
      }
      else if(!phoOneMatch&&!phoTwoMatch){//ff events
	h_ggcomposition->Fill(2.5);
      }
      else{//if anything gets placed here then a mistake has been made. All events should eith be gg, gf, or ff.
	h_ggcomposition->Fill(3.5);
      }
	
      h_ggMetSig->Fill(event->pfMETmEtSig_);
      h_ggMetSigVsSumEt->Fill(event->pfMETsumEt_,HT);
            
      h_ggPt->Fill(PhoOneVec.Pt());
      h_ggPt->Fill(PhoTwoVec.Pt());
      h_ggPtLead->Fill(PhoOneVec.Pt());
      h_ggPtTrail->Fill(PhoTwoVec.Pt());
      h_ggEta->Fill(PhoOneVec.Eta());
      h_ggPhi->Fill(PhoOneVec.Phi());
      h_ggEta->Fill(PhoTwoVec.Eta());
      h_ggPhi->Fill(PhoTwoVec.Phi());
      h_sumEt_gg->Fill(event->pfMETsumEt_);
      if(met <= 100)   h_ggMet->Fill(met);
      h_ggHT->Fill(HT);
      h_nHTJets_gg->Fill(nHTJets);
      h_ggHighestJetEnergy->Fill(highestJetEnergy);
      for(int i =0; i < nHTJets; i++){
        h_ggJetEnergy->Fill(cleanJets[i].Pt() );
      }
      h_ggSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
      h_ggSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
      h_ggDiEMPt->Fill(diEMpt);
      h_ggInvarMass->Fill(InvMass,PUweight);         
            
    }//end gg loop



    else if(doee){ 
      if(InvMass < 105 && InvMass > 75){
	//	  float eeinvmas = InvMass(PhoOneVec, PhoTwoVec);
	float diempt_weight=1; //The weights are stored in the histogram eeweights
	int bin = eeweights->FindFixBin(float(diEMpt));
	diempt_weight=eeweights->GetBinContent(bin);
	h_eeInvarMassFullRange->Fill(InvMass);
	h_eeMet->Fill(met);
	h_eeHT->Fill(HT);
	h_nHTJets_ee->Fill(nHTJets);
        h_eeHighestJetEnergy->Fill(highestJetEnergy);
	for(int i =0; i < nHTJets; i++){
	  h_eeJetEnergy->Fill(cleanJets[i].Pt() );
	}
	h_eeMetReweighted->Fill(met,diempt_weight);
	h_eeDiEMPt->Fill(diEMpt);
	h_eePt->Fill(PhoOneVec.Pt());
	h_eePt->Fill(PhoTwoVec.Pt());
      }
    }//end of ee
        
        
        
    else if(doeg){ 
      if( InvMass > 105){
	if(printLevel>0)cout<<"Inside eg"<<endl;
	neg++;
	h_egMet->Fill(met);
	h_egSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
	h_egSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
	h_egPt->Fill(PhoOneVec.Pt());
	h_egPt->Fill(PhoTwoVec.Pt());
      }
    }//end of eg
        
        
        
    //the dogammafake flag is set to true if there is one photon and one fake, irrespective of which of the two objects has the higher Pt value
    if(dogammafake){ 
      numGammaFake++;		

      float diempt_weight=1; //The weights are stored in the histogram gammafakeweights
      int bin = gammafakeweights->FindFixBin(float(diEMpt));
      diempt_weight=gammafakeweights->GetBinContent(bin);
      h_gammafakeMet->Fill(met);
      h_gammafakeMetReweighted->Fill(met,diempt_weight);
      h_gammafakeHTReweighted->Fill(HT,diempt_weight);
      h_gammafakeHT->Fill(HT);
      for(int i =0; i < nHTJets; i++){
	h_gammafakeJetEnergy->Fill(cleanJets[i].Pt() );
      }
      h_gammafakeHighestJetEnergy->Fill(highestJetEnergy);
      h_nHTJets_gammafake->Fill(nHTJets);
                
      if(printLevel>0)cout<<"Inside gammafake"<<endl;
      h_gammafakePt->Fill(PhoOneVec.Pt());
      h_gammafakePt->Fill(PhoTwoVec.Pt());
      h_gammafakePtLead->Fill(PhoOneVec.Pt()); 
      h_gammafakePtTrail->Fill(PhoTwoVec.Pt());

      h_gammafakeEta->Fill(PhoOneVec.Eta());
      h_gammafakeEta->Fill(PhoTwoVec.Eta());
      h_gammafakePhi->Fill(PhoOneVec.Phi());
      h_gammafakePhi->Fill(PhoTwoVec.Phi());
                
      float gammafakeEta = abs(event->phoEta_->at(PhoOne));
      float chIsoEA= 0, neuIsoEA = 0, phoIsoEA= 0;
      if(gammafakeEta<1.0){
	chIsoEA = .00;
	neuIsoEA = .0599;
	phoIsoEA=  .1271;
      }
      else if (gammafakeEta <1.479 && gammafakeEta >=1.0){
	chIsoEA = .00;
	neuIsoEA = .0819;
	phoIsoEA=  .1101;
      }
      float gammafakeChargedHadronIso= event->phoPFChIso_->at(PhoOne) - Rho*chIsoEA > 0. ? event->phoPFChIso_->at(PhoOne) - Rho*chIsoEA : 0.00 ;

      h_gfSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
      h_gfSigIetaIeta_vs_ChHadIso->Fill(event->phoSigmaIEtaIEta_->at(PhoOne), gammafakeChargedHadronIso);
      h_gfChHadIso->Fill(gammafakeChargedHadronIso);

      gammafakeEta = abs(event->phoEta_->at(PhoTwo));
      if(gammafakeEta<1.0){
	chIsoEA = .00;
	neuIsoEA = .0599;
	phoIsoEA=  .1271;
      }
      else if (gammafakeEta <1.479 && gammafakeEta >=1.0){
	chIsoEA = .00;
	neuIsoEA = .0819;
	phoIsoEA=  .1101;
      }
      gammafakeChargedHadronIso= event->phoPFChIso_->at(PhoTwo) - Rho*chIsoEA > 0. ? event->phoPFChIso_->at(PhoTwo) - Rho*chIsoEA : 0.00 ;

      h_gfSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
      h_gfSigIetaIeta_vs_ChHadIso->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo), gammafakeChargedHadronIso);
      h_gfChHadIso->Fill(gammafakeChargedHadronIso);
                
      h_sumEt_gammafake->Fill(event->pfMETsumEt_);
      

      //now do gf case specifically
      if( dogf ){
	int PhoOneGen;
	bool goForGen1 = false;
	float drClose1=999.;
	for(int i =0; i < event->nMC_; i++){
	  TLorentzVector part_it_vec = MassLorentzVector(event->mcPt->at(i), event->mcEta->at(i), event->mcPhi->at(i), event->mcMass->at(i));
	  //Try to find the gen level particles that match the photons most closely. The matching particle will have the smallest dR between it and the photon, and the difference between it's pt and the photon's pt must be less than 15%
	  if(event->mcStatus->at(i)==1){
	    if(getDR(PhoOneVec, part_it_vec)<drClose1 && abs(event->phoEt_->at(PhoOne) - event->mcPt->at(i))/(event->phoEt_->at(PhoOne)) < 0.15){
	      drClose1 = getDR(PhoOneVec, part_it_vec);
	      PhoOneGen=i;
	      goForGen1=true;
	    }
	  }
	}
	
	h_gfMet->Fill(met);
      }//end of if( dogf )
                
      //Now do fg case
      else if(dofg){ //lines 7166 to 7403 of Dave's code
	int PhoTwoGen;
	bool goForGen2 = false;
	float drClose2=999.;
	for(int i =0; i < event->nMC_; i++){
	  TLorentzVector part_it_vec = MassLorentzVector(event->mcPt->at(i), event->mcEta->at(i), event->mcPhi->at(i), event->mcMass->at(i));
	  //Try to find the gen level particles that match the photons most closely.The matching particle will have the smallest dR between it and the photon, and the difference between it's pt and the photon's pt must be less than 15%
	  if(event->mcStatus->at(i)==1){                            
	    if(getDR(PhoTwoVec, part_it_vec)<drClose2 && abs(event->phoEt_->at(PhoTwo) - event->mcPt->at(i))/(event->phoEt_->at(PhoTwo)) < 0.15){
	      drClose2 = getDR(PhoTwoVec, part_it_vec);
	      PhoTwoGen=i;
	      goForGen2=true;
	    }
	  }
	}//end of loop over MC particles
	h_fgMet->Fill(met);
      }//end of if(dofg)
                        
    }//end dogammafake if-statement
        

    if(doff && InvMass > 105){
      h_ffMet->Fill(met);
      if(met > 100) {
	nff_Met100++;
      }
      //Output to help with synchronization and to check specific events
      if(met > 100) {
	cout << "ff event with MET > 100! Event number "<< event->event_ << ", lumi "<< event->lumis_ << " and run number "<<event->run_ << endl;
	cout << "Pho One Index = " << PhoOne << " and PhoTwo Index= " << PhoTwo << endl;
	cout << "Pho One Pt, Eta, Phi =" << event-> phoEt_->at(PhoOne) << ", " << event->phoEta_->at(PhoOne) << ", " << event->phoPhi_->at(PhoOne) << endl;
	cout <<"Pho Two Pt, Eta, Phi =" << event-> phoEt_->at(PhoTwo) << ", " << event->phoEta_->at(PhoTwo) <<", " <<event->phoPhi_->at(PhoTwo) << endl;
	cout << "Bit 14 of HLT Pho = " << ( event->HLTPho_>>triggerIndex&1) << endl;
	cout << "Met filters = " << event->metFilters_ << endl;
	cout << "Number of vertices = " << event->nVtx_ << endl;
	cout << "Met = " << met << endl;
	cout << " PhoOne sig ieta ieta = " << event->phoSigmaIEtaIEta_->at(PhoOne) << endl;
	cout << " PhoTwo sig ieta ieta = " << event->phoSigmaIEtaIEta_->at(PhoTwo) << endl;
	cout << " PhoOne charged hadron isolation = " << event->phoPFChIso_->at(PhoOne) << endl;
	cout << " PhoTwo charged hadron isolation = " << event->phoPFChIso_->at(PhoTwo) << endl;
	cout << "Invariant mass = " << InvMass << endl;
      }

      nff++;
      float diempt_weight=1; //The weights are stored in the histogram ffweights
      int bin = ffweights->FindFixBin(float(diEMpt));
      diempt_weight=ffweights->GetBinContent(bin);
      h_ffMetReweighted->Fill(met,diempt_weight);
      h_ffHTReweighted->Fill(HT,diempt_weight);
      h_ffHT->Fill(HT);
      for(int i =0; i < nHTJets; i++){
	h_ffJetEnergy->Fill(cleanJets[i].Pt() );
      }
      h_ffHighestJetEnergy->Fill(highestJetEnergy);
      h_nHTJets_ff->Fill(nHTJets);

      bool leadIsoFake, leadShapeFake, trailIsoFake, trailShapeFake;
      float ffEta = abs(event->phoEta_->at(PhoOne));
      float chIsoEA, neuIsoEA, phoIsoEA;
      if(ffEta<1.0){
	chIsoEA = .00;
        neuIsoEA = .0599;
        phoIsoEA=  .1271;
      }
      else if (ffEta <1.479 && ffEta >=1.0){
        chIsoEA = .00;
        neuIsoEA = .0819;
        phoIsoEA=  .1101;
      }
      float ffChargedHadronIsoLead = event->phoPFChIso_->at(PhoOne) - Rho*chIsoEA > 0. ? event->phoPFChIso_->at(PhoOne) - Rho*chIsoEA : 0.00 ;

      if(ffChargedHadronIsoLead > 1.31){ leadIsoFake = true;}
      else{ leadIsoFake = false;}
      if(event->phoSigmaIEtaIEta_->at(PhoOne) > 0.0102){ leadShapeFake = true;}
      else {leadShapeFake = false;}

      h_ffSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoOne));
      h_ffSigIetaIeta_vs_ChHadIso->Fill(event->phoSigmaIEtaIEta_->at(PhoOne), ffChargedHadronIsoLead);
      if(met > 100)    h_ffSigIetaIeta_vs_ChHadIso_Met100->Fill(event->phoSigmaIEtaIEta_->at(PhoOne), ffChargedHadronIsoLead);
      h_ffChHadIso->Fill(ffChargedHadronIsoLead);

      ffEta = abs(event->phoEta_->at(PhoTwo));
      if(ffEta<1.0){
	chIsoEA = .00;
	neuIsoEA = .0599;
	phoIsoEA=  .1271;
      }
      else if (ffEta <1.479 && ffEta >=1.0){
	chIsoEA = .00;
	neuIsoEA = .0819;
	phoIsoEA=  .1101;
      }

      float ffChargedHadronIsoTrail= event->phoPFChIso_->at(PhoTwo) - Rho*chIsoEA > 0. ? event->phoPFChIso_->at(PhoTwo) - Rho*chIsoEA : 0.00 ;

      if(ffChargedHadronIsoTrail > 1.31){ trailIsoFake= true;}
      else{ trailIsoFake = false;}
      if(event->phoSigmaIEtaIEta_->at(PhoTwo) > 0.0102){ trailShapeFake =true;}
      else{ trailShapeFake = false;}

      h_ffSigIetaIeta->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo));
      h_ffSigIetaIeta_vs_ChHadIso->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo), ffChargedHadronIsoTrail);
      if(met > 100)    h_ffSigIetaIeta_vs_ChHadIso_Met100->Fill(event->phoSigmaIEtaIEta_->at(PhoTwo), ffChargedHadronIsoTrail);
      h_ffChHadIso->Fill(ffChargedHadronIsoTrail);

      h_ffPt->Fill(PhoOneVec.Pt());
      h_ffPt->Fill(PhoTwoVec.Pt());

    }//end of fake-fake if-statement
        
  }//end of looping over the events
  cout<< nCnt[5] << " events passed JSON file, trigger, and nvertex and met filter cuts." << endl; 
  cout<< "Total number of photons passing all selection cuts is " << nPhoCandsTotal<<endl;
  cout<< "Total number of fake candidates is " << nFakeCandsTotal << endl;
  cout << "We have " << ngg << " gamma gamma events, " << nff << " fake fake events, and " << numGammaFake << " gamma fake events." << endl;
  cout<<"Of the "<< ngg << " gg events, there are "<< nggMET0to50 << " events with MET < 50 GeV and "<<nggMET50to100 << " events with MET between 50 and 100 GeV." <<endl;
  cout<< "There are "<< nggInvMass110 << " gg events with invariant mass above 110 GeV." << endl;
  cout << "We have " << nff_Met100 << " ff events with MET > 100" << endl;

  cout << "Number of events with two photon candidates is " << nTwoCands <<endl;
  cout<<"Writing analysis root output to: hist_"<<ds<<".root"<<endl;
  // close the output file
    
  fout->cd();
  fout->Write();
  fout->Close();
  delete fout;
    
    
}//end of Loop() function





//---------------------------------------------------------------




//void SusyEventAnalyzer::CategorizeEvents(int pho1, int pho2, float Rho, bool &gogg, bool &goee, bool &goeg, bool &goff, bool &gogammafake, bool &gogf, bool &gofg){
//return;
//}



void SusyEventAnalyzer::CategorizeEvents(int pho1, int pho2, int pho3, float Rho, bool &gogg, bool &goee, bool &goeg, bool &goff, bool &gogammafake, bool &gogf, bool &gofg, bool &use13, bool&use23){
    //All of the photon candidates have had to pass cuts on H over E, photon isolation, and neutral hadron isolation
    //electrons and photons must also pass sigma ieta ieta and charged hadron isolation cuts. Photons must not have a pixel seed.
    //initialize all booleans to false
    bool g1=false, g2=false, f1=false, f2=false, e1=false, e2=false;
    gogg=false;goee=false;goeg=false;goff=false;gogammafake=false;gogf=false;gofg=false;
    use23 = false, use13 = false; 
    if((pho1>=event->nPho_)||(pho2>=event->nPho_)){
        cout << "Photon index higher than the number of photons in the event!! Error!!"<<endl;
        cout<< "PhoOne= " <<pho1<< "  PhoTwo= "<<pho2<<"  nPho= "<<event->nPho_<<endl;
        return;
    }
    
    float maxSihih = 0.0102; //.03; //.0106;
    float maxChHadIso = 1.37;
    
    //Define the effective area for pho1 (see https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2 )
    
    float pho1Eta = abs(event->phoEta_->at(pho1) );
    float chIsoEA1=0;
    
    if(pho1Eta<1.0){
        chIsoEA1 = .0;
    }
    else if (pho1Eta <1.479 && pho1Eta >=1.0){
        chIsoEA1 = .00;
    }
    else if (pho1Eta <2.0 && pho1Eta >=1.479){
        chIsoEA1 = .00;
    }
    else if (pho1Eta <2.2 && pho1Eta >=2.0){
        chIsoEA1 = .00;
    }
    else if (pho1Eta <2.3 && pho1Eta >=2.2){
        chIsoEA1 = .00;
    }
    else if (pho1Eta <2.4 && pho1Eta >=2.3){
        chIsoEA1 = .00;
    }
    else if (pho1Eta >=2.4){
        chIsoEA1 = .00;
    }
    
    //Define EA for pho 2
    
    float pho2Eta = abs(event->phoEta_->at(pho2) );
    float chIsoEA2=0.0;
    
    if(pho2Eta<1.0){
        chIsoEA2 = .00;
    }
    else if (pho2Eta <1.479 && pho2Eta >=1.0){
        chIsoEA2 = .00;
    }
    else if (pho2Eta <2.0 && pho2Eta >=1.479){
        chIsoEA2 = .00;
    }
    else if (pho2Eta <2.2 && pho2Eta >=2.0){
        chIsoEA2 = .00;
    }
    else if (pho2Eta <2.3 && pho2Eta >=2.2){
        chIsoEA2 = .00;
    }
    else if (pho2Eta <2.4 && pho2Eta >=2.3){
        chIsoEA2 = .00;
    }
    else if (pho2Eta >=2.4){
        chIsoEA2 = .00;
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
    
    if(g1 && g2)                    gogg=true; 
    if( (g1 && e2) || (e1 && g2))   goeg=true;
    if(e1 && e2)                    goee=true; 
    if(f1 && f2)                    goff=true;
    if( (g1 && f2) || (f1 && g2) ){
      gogammafake=true;
      if(g1 && f2)    gogf=true;
      else if(f1 && g2)   gofg=true;
    }

    if( ! (gogg || goee || goff || goeg) ) {
      if(pho3 > -1){
	//if the first two photons didn't fall into a useful category, use the third photon object
	float chIsoEA3 = 0.0; 
	float pho3iso  = (event->phoPFChIso_->at(pho3) - Rho*chIsoEA3) > 0.00 ? (event->phoPFChIso_->at(pho3) - Rho*chIsoEA3) : 0.00;
	bool g3 = false, e3 = false, f3 = false;
	if(event->phoSigmaIEtaIEta_->at(pho3) < maxSihih && pho3iso < maxChHadIso){
	  if(event->phohasPixelSeed_->at(pho3)){
            e3 = true;
	  }
	  else{
            g3 = true;
	  }
	}
	else{  //since all the photon candidates are either electrons, photons, or fakes, if it failed the sigma ieta ieta or the charged hadron isolation cut, it must be a fake      
	  f3 = true;
	}

	if(g1 && g3){ gogg = true; use13 = true;}
	else if( (g1 && e3) || (e1 && g3) ){ goeg = true; use13 = true;}
	else if( e1 && e3) {goee = true; use13 = true;}
	else if(f1 && f3) {goff = true; use13 = true;}
	else if( g2&&g3) {gogg = true; use23 = true;}
	else if( (g2 && e3) || (e2 && g3) ){ goeg = true; use23 = true;}
	else if (e2 && e3){ goee = true; use23 = true;}
	else if (f2 && f3 ){ goff = true;  use23 = true;}
      }
    }
    
    if(gogg&&goeg)cout<<"gg AND eg event!!!!! ------- PROBLEM!"<<endl;
    if(gogg&&goee)cout<<"gg AND ee event!!!!! ------- PROBLEM!"<<endl;
    if(gogg&&goff)cout<<"gg AND ff event!!!!! ------- PROBLEM!"<<endl;
    //    if(gogg&&gogammafake)cout<<"gg AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(goeg&&goee)cout<<"eg AND ee event!!!!! ------- PROBLEM!"<<endl;
    if(goeg&&goff)cout<<"eg AND ff event!!!!! ------- PROBLEM!"<<endl;
    //    if(goeg&&gogammafake)cout<<"eg AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(goee&&goff)cout<<"ee AND ff event!!!!! ------- PROBLEM!"<<endl;
    //    if(goee&&gogammafake)cout<<"ee AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    //    if(goff&&gogammafake)cout<<"ff AND gammafake event!!!!! ------- PROBLEM!"<<endl;
    if(gogf&&gofg)cout<<"gf AND fg event!!!!! ------- PROBLEM!"<<endl;
    if((gogammafake && !gogf) && (gogammafake && !gofg))cout<<"gammafake BUT NOT gf OR fg event!!!!! ------- PROBLEM!"<<endl;
    return;
} //end of Categorize Event function



void SusyEventAnalyzer::MatchPhosToJets(TLorentzVector pOne, TLorentzVector pTwo, std::vector<TLorentzVector*> jetvecs, TLorentzVector &jet1, TLorentzVector &jet2, bool &hasdijetpt, float dR){
    hasdijetpt=false;
    for(std::vector<TLorentzVector*>::iterator jet_it1 = jetvecs.begin(); jet_it1 != jetvecs.end(); jet_it1++){
        if(isSameObject(pOne,*(*jet_it1),dR)){
            for(std::vector<TLorentzVector*>::iterator jet_it2 = jetvecs.begin(); jet_it2 != jetvecs.end(); jet_it2++){
                if( !isSameObject(*(*jet_it1), *(*jet_it2),0.1) ){
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
