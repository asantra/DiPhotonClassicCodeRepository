#define MyNtupleMakerQQQ_cxx
#include "MyNtupleMakerQQQ.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>
#include <iostream>
#include <TSystem.h>
#include <TString.h>
#include <algorithm>
#include <TTree.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <algorithm>

using namespace std;

//spring15 25 ns
void photonEffectiveAreas(double _eta, double* _effA)
{
  double& effACH(_effA[0]);
  double& effANH(_effA[1]);
  double& effAPh(_effA[2]);
  double& effAW(_effA[3]);

  // Source: CutBasedPhotonID Run2 twiki
  if(_eta < 1.){
    effACH = 0.0;
    effANH = 0.0599;
    effAPh = 0.1271;
    effAW  = 0.075; // from 2012
  }
  else if(_eta > 1. && _eta < 1.479){
    effACH = 0.0;
    effANH = 0.0819;
    effAPh = 0.1101;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 1.479 && _eta < 2.0){
    effACH = 0.0;
    effANH = 0.0696;
    effAPh = 0.0756;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.0 && _eta < 2.2){
    effACH = 0.0;
    effANH = 0.0360;
    effAPh = 0.1175;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.2 && _eta < 2.3){
    effACH = 0.0;
    effANH = 0.0360;
    effAPh = 0.1498;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.3 && _eta < 2.4){
    effACH = 0.0;
    effANH = 0.0462;
    effAPh = 0.1857;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.4){
    effACH = 0.0;
    effANH = 0.0656;
    effAPh = 0.2183;
    effAW  = 0.0617; // from 2012
  }
}
// for the new ggNtuple with MET filter worst isolation is not available
void photonEffectiveAreasPHYS14(double _eta, double* _effA)
{
  double& effACH(_effA[0]);
  double& effANH(_effA[1]);
  double& effAPh(_effA[2]);
  double& effAW(_effA[3]);

  // Source: CutBasedPhotonID Run2 twiki
  if(_eta < 1.){
    effACH = 0.0234;
    effANH = 0.0053;
    effAPh = 0.0784;
    effAW  = 0.075; // from 2012
  }
  else if(_eta > 1. && _eta < 1.479){
    effACH = 0.0189;
    effANH = 0.0103;
    effAPh = 0.0629;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 1.479 && _eta < 2.0){
    effACH = 0.0171;
    effANH = 0.0057;
    effAPh = 0.0264;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.0 && _eta < 2.2){
    effACH = 0.0129;
    effANH = 0.0070;
    effAPh = 0.0462;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.2 && _eta < 2.3){
    effACH = 0.0110;
    effANH = 0.0152;
    effAPh = 0.0740;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.3 && _eta < 2.4){
    effACH = 0.0074;
    effANH = 0.0230;
    effAPh = 0.0924;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.4){
    effACH = 0.0035;
    effANH = 0.1709;
    effAPh = 0.1484;
    effAW  = 0.0617; // from 2012
  }
}

// spring15 50 ns
void photonEffectiveAreasSpring15(double _eta, double* _effA)
{
  double& effACH(_effA[0]);
  double& effANH(_effA[1]);
  double& effAPh(_effA[2]);
  double& effAW(_effA[3]);

  // Source: CutBasedPhotonID Run2 twiki
  if(_eta < 1.){
    effACH = 0.0157;
    effANH = 0.0143;
    effAPh = 0.0725;
    effAW  = 0.075; // from 2012
  }
  else if(_eta > 1. && _eta < 1.479){
    effACH = 0.0143;
    effANH = 0.0210;
    effAPh = 0.0604;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 1.479 && _eta < 2.0){
    effACH = 0.0115;
    effANH = 0.0148;
    effAPh = 0.0320;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.0 && _eta < 2.2){
    effACH = 0.0094;
    effANH = 0.0082;
    effAPh = 0.0512;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.2 && _eta < 2.3){
    effACH = 0.0095;
    effANH = 0.0124;
    effAPh = 0.0766;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.3 && _eta < 2.4){
    effACH = 0.0068;
    effANH = 0.0186;
    effAPh = 0.0949;
    effAW  = 0.0617; // from 2012
  }
  else if(_eta > 2.4){
    effACH = 0.0053;
    effANH = 0.0320;
    effAPh = 0.1160;
    effAW  = 0.0617; // from 2012
  }
}

struct Object{
  int photonType;
  float pt;
  int tracker;
  Object(){
    photonType=0;
    pt=0;
    tracker=0;
  }
};
struct ExtendedObject{
  int photonType1;
  float pt1;
  int tracker1;
  int photonType2;
  float pt2;
  int tracker2;
  ExtendedObject(){
    photonType1 = 0;
    pt1 = 0;
    tracker1 = 0;
    photonType2 = 0;
    pt2 = 0;
    tracker2 = 0;
  }
};
bool my_cmp(const Object& a, const Object& b){
  // smallest comes first
  return a.pt > b.pt;
}

ExtendedObject Selection(vector<Object>Work){
  ExtendedObject Output;
  vector<Object> photonObject;
  photonObject.clear();
  std::sort(Work.begin(), Work.end(), my_cmp);
//   if(Work.size()>2){
//     for(size_t i=0; i < Work.size();++i)
//       cout << Work.at(i).photonType << ", " << Work.at(i).pt << ", " << Work.at(i).tracker << endl;
//   }
  if(Work.size()>1 && Work.at(0).photonType==1 && Work.at(1).photonType==1){
    photonObject.push_back(Work.at(0));
    photonObject.push_back(Work.at(1));
  }
  else if(Work.size()>1 && (Work.at(0).photonType==1 && Work.at(1).photonType==2)){
    photonObject.push_back(Work.at(0));
    photonObject.push_back(Work.at(1));
  }
  else if(Work.size()>1 && (Work.at(0).photonType==2 && Work.at(1).photonType==1)){
    photonObject.push_back(Work.at(1));
    photonObject.push_back(Work.at(0));
  }
  else if(Work.size()>1 && Work.at(0).photonType==2 && Work.at(1).photonType==2){
    photonObject.push_back(Work.at(0));
    photonObject.push_back(Work.at(1));
  }
  else if(Work.size()>1 && Work.at(0).photonType==3 && Work.at(1).photonType==3){
    photonObject.push_back(Work.at(0));
    photonObject.push_back(Work.at(1));
  }
  else if(Work.size()>2 && (Work.at(0).photonType==3 || Work.at(1).photonType==3) && (Work.at(0).photonType*Work.at(1).photonType!=9)){
    if(Work.at(0).photonType==3 && Work.at(1).photonType==1 && Work.at(2).photonType==1){
      photonObject.push_back(Work.at(1));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(0).photonType==3 && Work.at(1).photonType == 1 && Work.at(2).photonType==2){
      photonObject.push_back(Work.at(1));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(0).photonType==3 && Work.at(1).photonType == 2 && Work.at(2).photonType==1){
      photonObject.push_back(Work.at(2));
      photonObject.push_back(Work.at(1));
    }
    else if(Work.at(0).photonType==3 && Work.at(1).photonType==1 && Work.at(2).photonType==3){
      photonObject.push_back(Work.at(0));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(0).photonType==3 && Work.at(1).photonType==2 && Work.at(2).photonType==2){
      photonObject.push_back(Work.at(1));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(0).photonType==3 && Work.at(1).photonType==2 && Work.at(2).photonType==3){
      photonObject.push_back(Work.at(0));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==1 && Work.at(2).photonType==1){
      photonObject.push_back(Work.at(0));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==1 && Work.at(2).photonType==2){
      photonObject.push_back(Work.at(0));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==2 && Work.at(2).photonType==1){
      photonObject.push_back(Work.at(2));
      photonObject.push_back(Work.at(0));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==1 && Work.at(2).photonType==3){
      photonObject.push_back(Work.at(1));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==2 && Work.at(2).photonType==2){
      photonObject.push_back(Work.at(0));
      photonObject.push_back(Work.at(2));
    }
    else if(Work.at(1).photonType==3 && Work.at(0).photonType==2 && Work.at(2).photonType==3){
      photonObject.push_back(Work.at(1));
      photonObject.push_back(Work.at(2));
    }
  }
  if(photonObject.size()>1){
    Output.photonType1 = photonObject.at(0).photonType;
    Output.pt1         = photonObject.at(0).pt;
    Output.tracker1    = photonObject.at(0).tracker;
    Output.photonType2 = photonObject.at(1).photonType;
    Output.pt2         = photonObject.at(1).pt;
    Output.tracker2    = photonObject.at(1).tracker;
  }
  return Output;
}
    
float dRCalc(float etaLead, float phiLead, float etaTrail, float phiTrail){
    
  float dphi = fabs(phiLead - phiTrail);
  if (dphi > TMath::Pi()) dphi = TMath::Pi()*2. - dphi;
  float deta = fabs(etaLead - etaTrail);
  float dR = sqrt(deta*deta + dphi*dphi);
  return dR;
    
}

float dPhiCalc(float phiLead, float phiTrail){
  float dphi = fabs(phiLead - phiTrail);
  if(dphi > TMath::Pi()) dphi = TMath::Pi()*2. - dphi;
  return dphi;
}

float findMass(float ELead, float EtaLead, float PhiLead, float ETrail, float EtaTrail, float PhiTrail){
  float theta1 = 2*atan(exp(-EtaLead));
  float theta2 = 2*atan(exp(-EtaTrail));
  float PX1 = ELead*sin(theta1)*cos(PhiLead);
  float PY1 = ELead*sin(theta1)*sin(PhiLead);
  float PX2 = ETrail*sin(theta2)*cos(PhiTrail);
  float PY2 = ETrail*sin(theta2)*sin(PhiTrail);
  float PZ1 = ELead*cos(theta1);
  float PZ2 = ETrail*cos(theta2);
  float Mass = sqrt((ELead+ETrail)*(ELead+ETrail)-((PX1+PX2)*(PX1+PX2)+(PY1+PY2)*(PY1+PY2)+(PZ1+PZ2)*(PZ1+PZ2)));
  return Mass;
}

bool isSameObject(float etaLead, float phiLead, float etaTrail, float phiTrail, float deltaR){
  float dr = dRCalc(etaLead, phiLead, etaTrail, phiTrail);
  return (dr < deltaR);
}

void MyNtupleMakerQQQ::Loop(TString outfile, double WEIGHT)
{
  //   In a ROOT session, you can do:
  //      Root > .L MyNtupleMaker.C
  //      Root > MyNtupleMaker t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  
   
 
  TFile *fout = new TFile(outfile, "RECREATE");
  fout->cd();
  TH1::SetDefaultSumw2();
  
  float xbins2[] = {0,2,5,8,11,14,17,20,25,30,35,40,45,50,57,64,71,80,90, 100,110,120,140,300};
  int binnum2 = sizeof(xbins2)/sizeof(Float_t) - 1;
  
  TH1F *h_All_Signal_MET = new TH1F("h_All_Signal_MET","All Signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET = new TH1F("h_DoublePhoton_Signal_MET","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET_NoTriggerCut = new TH1F("h_DoublePhoton_Signal_MET_NoTriggerCut","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET_AsymPtCut = new TH1F("h_DoublePhoton_Signal_MET_AsymPtCut","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET_InvMassCut = new TH1F("h_DoublePhoton_Signal_MET_InvMassCut","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET_InvMassAndAsymPtCut = new TH1F("h_DoublePhoton_Signal_MET_InvMassAndAsymPtCut","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhoton_Signal_MET_HighInvMassAndAsymPtCut = new TH1F("h_DoublePhoton_Signal_MET_HighInvMassAndAsymPtCut","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  TH1F *h_DoublePhotonFromThree_Signal_MET = new TH1F("h_DoublePhotonFromThree_Signal_MET","Di-photon signal MET; Events; MET (GeV)", binnum2, xbins2);
  float xbins[] = {100, 110, 120, 140, 300};
  int binnum = sizeof(xbins)/sizeof(Float_t) - 1;
  TH1F *h_DoublePhoton_Signal_METExpected = new TH1F("h_DoublePhoton_Signal_METExpected","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  TH1F *h_DoublePhoton_Signal_METJESUpExpected = new TH1F("h_DoublePhoton_Signal_METJESUpExpected","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  TH1F *h_DoublePhoton_Signal_METJESDownExpected = new TH1F("h_DoublePhoton_Signal_METJESDownExpected","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  
  TH1F *h_DoublePhoton_Signal_METExpectedUnweighted = new TH1F("h_DoublePhoton_Signal_METExpectedUnweighted","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  TH1F *h_DoublePhoton_Signal_METJESUpExpectedUnweighted = new TH1F("h_DoublePhoton_Signal_METJESUpExpectedUnweighted","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  TH1F *h_DoublePhoton_Signal_METJESDownExpectedUnweighted = new TH1F("h_DoublePhoton_Signal_METJESDownExpectedUnweighted","Double Photon MET, MET>100; Events; MET (GeV)", binnum, xbins);
  
  
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();
  

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if(jentry%10000 == 0)cout << "Processed: " << jentry << endl;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    h_All_Signal_MET->Fill(pfMET, WEIGHT);
    
    vector<unsigned int> realphoton_tracker, electron_tracker;
    realphoton_tracker.clear(); electron_tracker.clear();
    
    vector<Object> Work2;
    Work2.clear();
    //muon selection
    vector<float> GoodMuonEta, GoodMuonPhi;
    GoodMuonEta.clear(); GoodMuonPhi.clear();
    
    for(size_t w=0; w < muPt->size();++w){
      if(!(muIsMediumID->at(w) && fabs(muEta->at(w))<1.4442 && muPt->at(w)>30))continue;
      float combIso  = muPFChIso->at(w) + TMath::Max(0.,muPFNeuIso->at(w) + muPFPhoIso->at(w) - 0.5*muPFPUIso->at(w));
      if( combIso/muPt->at(w) > 0.25 )continue;
      GoodMuonEta.push_back(muEta->at(w));
      GoodMuonPhi.push_back(muPhi->at(w));
    }
    //cout << "4" << endl;
    /// clearing flat ntuples ////
    for(unsigned int i = 0; i < phoEta->size(); ++i){
      Object tempFile;
      float absEta = fabs(phoEta->at(i));
      double effA[4];
      photonEffectiveAreas(absEta, effA);
      if((fabs(phoSCEta->at(i)) >= 1.4442) || (phoR9->at(i) > 1.0))continue;
      // containing newest cuts fron https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedphotonIdentificationRun2
      
      float pt                 = fabs(phoEt->at(i)); 
      bool neutral             = (phoPFNeuIso->at(i) - rho * effA[1] -  0.014*pt - 0.000019*pt*pt) < 1.06;
      bool charged             = (phoPFChIso->at(i) - rho * effA[0]) < 1.37;
      bool photoniso           = (phoPFPhoIso->at(i) - rho * effA[2] - 0.0053*pt) < 0.28;
      //printf("absEta: %f and effACh: %f effPh:%f and effN:%f\n", absEta,effA[0],effA[2],effA[1]);
      bool worstiso            = (phoPFChWorstIso->at(i) -rho*effA[3]) < 2.6;
      bool showercut           = phoSigmaIEtaIEta->at(i) > 0.005 && phoSigmaIEtaIEta->at(i) < 0.0102 ;
      bool fakeshowercut       = (phoSigmaIEtaIEta->at(i) > 0.0102) && (phoSigmaIEtaIEta->at(i) < 0.015) ;
      bool fakeshowercutLoose  = (phoSigmaIEtaIEta->at(i) > 0.0102) && (phoSigmaIEtaIEta->at(i) < 0.020) ;
      bool fakecharged         = ((phoPFChIso->at(i) - rho * effA[0]) > 1.37) && ((phoPFChIso->at(i) - rho * effA[0]) < 15.0);
      bool fakechargedLoose    = ((phoPFChIso->at(i) - rho * effA[0]) > 1.37) && ((phoPFChIso->at(i) - rho * effA[0]) < 40.0);
      bool pixelcut            = phohasPixelSeed->at(i) == 0;
      //cout << phohasPixelSeed->at(i) << endl;
      bool HoverE              = phoHoverE->at(i) < 0.05;
      bool SymPtCut            = pt > 40;
      
      if(neutral && photoniso && HoverE && SymPtCut && charged && showercut && pixelcut){
	tempFile.photonType=1;
	tempFile.pt=phoEt->at(i);
	tempFile.tracker=i;
	Work2.push_back(tempFile);
	//realphoton_tracker.push_back(i);
      }
      if(neutral && photoniso && HoverE && SymPtCut && charged && showercut && !pixelcut){
	tempFile.photonType=2;
	tempFile.pt=phoEt->at(i);
	tempFile.tracker=i;
	Work2.push_back(tempFile);
	electron_tracker.push_back(i);
      }
      
      ///////// Tight fake cut ///////////////
//       if(neutral && photoniso && HoverE && SymPtCut && (fakecharged || fakeshowercut) && pixelcut){
// 	if(fakecharged && fakeshowercut)continue;
// 	tempFile.photonType=3;
// 	tempFile.pt=phoEt->at(i);
// 	tempFile.tracker=i;
// 	Work2.push_back(tempFile);
//       }

      
      ////////// Loose fake cut ////////////////
      if(pixelcut && HoverE && SymPtCut ){
	if( (fakechargedLoose && fakeshowercutLoose) || (fakechargedLoose && showercut) || ((charged && fakeshowercutLoose)) ){
	  tempFile.photonType=3; // 3 for fake
	  tempFile.pt=phoEt->at(i);
	  tempFile.tracker=i;
	  Work2.push_back(tempFile);
	}
      }
      
    }
    
    ExtendedObject FinalEvent = Selection(Work2);
    std::sort(Work2.begin(), Work2.end(), my_cmp);
    
    if(FinalEvent.photonType1 == 1 && FinalEvent.photonType2 == 1){
      if(Work2.size()>2 && (Work2.at(0).photonType==3 || Work2.at(1).photonType==3) && (Work2.at(0).photonType*Work2.at(1).photonType!=9))h_DoublePhotonFromThree_Signal_MET->Fill(pfMET,WEIGHT);// subtracting events with gfg and fgg scenario
      realphoton_tracker.push_back(FinalEvent.tracker1);
      realphoton_tracker.push_back(FinalEvent.tracker2);
    }
    if(realphoton_tracker.size() == 2){
      float Mass = findMass(phoE->at(realphoton_tracker.at(0)), phoEta->at(realphoton_tracker.at(0)), phoPhi->at(realphoton_tracker.at(0)), phoE->at(realphoton_tracker.at(1)), phoEta->at(realphoton_tracker.at(1)), phoPhi->at(realphoton_tracker.at(1)));
      
      bool CloseElectronLead(false), CloseElectronTrail(false);
      bool CloseMuonLead(false), CloseMuonTrail(false);
      
      for(size_t h=0; h < electron_tracker.size(); ++h){
	if(isSameObject(phoEta->at(realphoton_tracker.at(0)), phoPhi->at(realphoton_tracker.at(0)), phoEta->at(electron_tracker.at(h)), phoPhi->at(electron_tracker.at(h)), 0.3)){
	  CloseElectronLead = true;
	  break;
	}
	if(isSameObject(phoEta->at(realphoton_tracker.at(1)), phoPhi->at(realphoton_tracker.at(1)), phoEta->at(electron_tracker.at(h)), phoPhi->at(electron_tracker.at(h)), 0.3)){
	  CloseElectronTrail = true;
	  break;
	}
      }
      if(CloseElectronLead || CloseElectronTrail)continue;
      
      for(size_t h=0; h < GoodMuonEta.size(); ++h){
	if(isSameObject(phoEta->at(realphoton_tracker.at(0)), phoPhi->at(realphoton_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	  CloseMuonLead = true;
	  break;
	}
	if(isSameObject(phoEta->at(realphoton_tracker.at(1)), phoPhi->at(realphoton_tracker.at(1)),  GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	  CloseMuonTrail = true;
	  break;
	}
      }
      if(CloseMuonLead || CloseMuonTrail)continue;
      float DR = dRCalc(phoEta->at(realphoton_tracker.at(0)), phoPhi->at(realphoton_tracker.at(0)), phoEta->at(realphoton_tracker.at(1)), phoEta->at(realphoton_tracker.at(1)));
      if(DR>0.3){
	h_DoublePhoton_Signal_MET_NoTriggerCut->Fill(pfMET);
	if(Mass > 95)h_DoublePhoton_Signal_MET_InvMassCut->Fill(pfMET);
	if(phoE->at(realphoton_tracker.at(0))>30 && phoE->at(realphoton_tracker.at(1))>18){
	  h_DoublePhoton_Signal_MET_AsymPtCut->Fill(pfMET);
	  if(Mass>95)h_DoublePhoton_Signal_MET_InvMassAndAsymPtCut->Fill(pfMET);
	  if(Mass>105)h_DoublePhoton_Signal_MET_HighInvMassAndAsymPtCut->Fill(pfMET);
	} 
	if(!(phoE->at(realphoton_tracker.at(0))>40 && phoE->at(realphoton_tracker.at(1))>40))continue;
	if(!(Mass>105))continue;
	h_DoublePhoton_Signal_MET->Fill(pfMET, WEIGHT);
	if(pfMET>100){
	  h_DoublePhoton_Signal_METExpected->Fill(pfMET, WEIGHT);
	  h_DoublePhoton_Signal_METExpectedUnweighted->Fill(pfMET);
	}
	if(pfMET_T1JESUp > 100){
	  h_DoublePhoton_Signal_METJESUpExpected->Fill(pfMET_T1JESUp, WEIGHT);
	  h_DoublePhoton_Signal_METJESUpExpectedUnweighted->Fill(pfMET_T1JESUp);
	}
	if(pfMET_T1JESDo > 100){
	  h_DoublePhoton_Signal_METJESDownExpected->Fill(pfMET_T1JESDo, WEIGHT);
	  h_DoublePhoton_Signal_METJESDownExpectedUnweighted->Fill(pfMET_T1JESDo);
	}
      }
    }
    // if (Cut(ientry) < 0) continue;
  }// end event loop
  fout->cd();
  fout->Write();
  delete fout;
}
