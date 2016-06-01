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

using namespace std;


// for the new ggNtuple with MET filter worst isolation is not available


void MyNtupleMakerQQQ::Loop(TString outfile, Long64_t Start, Long64_t Stop)//
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
  Int_t           Run;
  Long64_t        Event;
  Int_t           Lumis;
  Int_t           NVtx;
  Int_t           NTrks;
  Float_t         Rho;
  vector<int>     NPU;
  vector<int>     PUBX;
  vector<float>   PUTrue;
  ULong64_t       HLT_EleMuX;
  ULong64_t       HLT_Pho;
  ULong64_t       HLT_Jet;
  ULong64_t       HLT_EleMuXIsPrescaled;
  ULong64_t       HLT_PhoIsPrescaled;
  ULong64_t       HLT_JetIsPrescaled;
  Int_t           METFilters;
  //ULong64_t       HLT_50ns;
  //ULong64_t       HLT_IsPrescaled50ns;
  Float_t         PFMET;
  Float_t         PFMETPhi;
  Float_t         PFMETsumEt;
  Float_t         PFMETmEtSig;
  Float_t         PFMETSig;
  
  vector<float>   ElePt;
  vector<float>   EleEta;
  vector<float>   ElePhi;
  vector<float>   EleD0;
  vector<float>   EleDz;
  vector<unsigned short> EleIDbit;
  
  vector<float>   PhoE;
  vector<float>   PhoEt;
  vector<float>   PhoEta;
  vector<float>   PhoSCEta;
  vector<float>   PhoPhi;
  vector<int>     PhohasPixelSeed;
  vector<int>     PhoEleVeto;
  vector<float>   PhoR9;
  vector<float>   PhoHoverE;
  vector<float>   PhoSigmaIEtaIEta;
  vector<float>   PhoSigmaIEtaIPhi;
  vector<float>   PhoSigmaIPhiIPhi;
  vector<float>   PhoPFChIso;
  vector<float>   PhoPFPhoIso;
  vector<float>   PhoPFNeuIso;
  vector<float>   PhoPFChWorstIso;
  
  vector<float>   MuPt;
  vector<float>   MuEta;
  vector<float>   MuPhi;
  vector<int>     MuCharge;
  vector<int>     MuType;
  vector<int>     MuIsGood;
  vector<int>     MuIsLooseID;
  vector<float>   MuD0;
  vector<float>   MuDz;
  vector<float>   MuChi2NDF;
  vector<int>     MuTrkLayers;
  vector<int>     MuPixelLayers;
  vector<int>     MuPixelHits;
  vector<int>     MuMuonHits;
  vector<int>     MuStations;
  vector<int>     MuTrkQuality;
  vector<float>   MuIsoTrk;
  vector<float>   MuPFChIso;
  vector<float>   MuPFPhoIso;
  vector<float>   MuPFNeuIso;
  vector<float>   MuPFPUIso;
  
  vector<float>   JetPt;
  vector<float>   JetEta;
  vector<float>   JetPhi;
  vector<float>   JetCHF;
  vector<float>   JetNHF;
  vector<float>   JetCEF;
  vector<float>   JetNEF;
  vector<int>     JetNCH;
  vector<float>   JetHFHAE;
  vector<float>   JetHFEME;
  vector<int>     JetNConstituents;
  vector<int>     JetPartonID;
  vector<bool>    JetPFLooseId;
  
  TString EosAddress = "EEEEE";
  
 
  //TFile *fout = new TFile(EosAddress+"/"+outfile, "RECREATE");
  TFile *fout = new TFile(outfile, "RECREATE");
  fout->cd();
  
  TTree* tree = new TTree("tree", "SUSY tree");
  
  tree->Branch("Run",                 & Run,           "Run/I");
  tree->Branch("Lumis",               & Lumis,         "Lumis/I");
  tree->Branch("Event",               & Event,         "Event/L");
  tree->Branch("NVtx",                & NVtx,          "NVtx/I");
  tree->Branch("NTrks",               & NTrks,         "NTrks/I");
  tree->Branch("Rho",                 & Rho,           "Rho/F");
  tree->Branch("HLT_EleMuX",          & HLT_EleMuX,    "HLT_EleMuX/l");
  tree->Branch("HLT_Pho",             & HLT_Pho,       "HLT_Pho/l");
  tree->Branch("HLT_Jet",             & HLT_Jet,       "HLT_Jet/l");
  tree->Branch("HLT_EleMuXIsPrescaled", & HLT_EleMuXIsPrescaled, "HLT_EleMuXIsPrescaled/l");
  tree->Branch("HLT_PhoIsPrescaled",  & HLT_PhoIsPrescaled, "HLT_PhoIsPrescaled/l");
  tree->Branch("HLT_JetIsPrescaled",  & HLT_JetIsPrescaled, "HLT_JetIsPrescaled/l");
  tree->Branch("METFilters",          & METFilters,     "METFilters/I");
  //tree->Branch("HLT_50ns",            & HLT_50ns, "HLT_50ns/l");
  //tree->Branch("HLT_IsPrescaled50ns", & HLT_IsPrescaled50ns, "HLT_IsPrescaled50ns/l");
   
  tree->Branch("PFMET",               & PFMET,         "PFMET/F");
  tree->Branch("PFMETPhi",            & PFMETPhi,      "PFMETPhi/F");
  tree->Branch("PFMETsumEt",          & PFMETsumEt,    "PFMETsumEt/F");
  tree->Branch("PFMETmEtSig",         & PFMETmEtSig,   "PFMETmEtSig/F");
  tree->Branch("PFMETSig",            & PFMETSig,      "PFMETSig/F");
  
  tree->Branch("ElePt",               "vector<float>", & ElePt);
  tree->Branch("EleEta",              "vector<float>", & EleEta);
  tree->Branch("ElePhi",              "vector<float>", & ElePhi);
  tree->Branch("EleD0",               "vector<float>", & EleD0);
  tree->Branch("EleDz",               "vector<float>", & EleDz);
  tree->Branch("EleIDbit",            "vector<unsigned short>", & EleIDbit);
  
  tree->Branch("PhoE",                "vector<float>", & PhoE);
  tree->Branch("PhoEt",               "vector<float>", & PhoEt);
  tree->Branch("PhoEta",              "vector<float>", & PhoEta);
  tree->Branch("PhoSCEta",            "vector<float>", & PhoSCEta);
  tree->Branch("PhoPhi",              "vector<float>", & PhoPhi);
  tree->Branch("PhohasPixelSeed",     "vector<int>",   & PhohasPixelSeed);
  tree->Branch("PhoEleVeto",          "vector<int>",   & PhoEleVeto);
  tree->Branch("PhoR9",               "vector<float>", & PhoR9);
  tree->Branch("PhoHoverE",           "vector<float>", & PhoHoverE);
  tree->Branch("PhoSigmaIEtaIEta",    "vector<float>", & PhoSigmaIEtaIEta);
  tree->Branch("PhoSigmaIEtaIPhi",    "vector<float>", & PhoSigmaIEtaIPhi);
  tree->Branch("PhoSigmaIPhiIPhi",    "vector<float>", & PhoSigmaIPhiIPhi);
  tree->Branch("PhoPFChIso",          "vector<float>", & PhoPFChIso);
  tree->Branch("PhoPFPhoIso",         "vector<float>", & PhoPFPhoIso);
  tree->Branch("PhoPFNeuIso",         "vector<float>", & PhoPFNeuIso);
  tree->Branch("PhoPFChWorstIso",     "vector<float>", & PhoPFChWorstIso);
  
  tree->Branch("MuPt",                "vector<float>", & MuPt);
  tree->Branch("MuEta",               "vector<float>", & MuEta);
  tree->Branch("MuPhi",               "vector<float>", & MuPhi);
  tree->Branch("MuCharge",            "vector<int>",   & MuCharge);
  tree->Branch("MuType",              "vector<int>",   & MuType);
  tree->Branch("MuIsGood",            "vector<int>",   & MuIsGood);
  tree->Branch("MuIsLooseID",         "vector<int>",   & MuIsLooseID);
  tree->Branch("MuD0",                "vector<float>", & MuD0);
  tree->Branch("MuDz",                "vector<float>", & MuDz);
  tree->Branch("MuChi2NDF",           "vector<float>", & MuChi2NDF);
  tree->Branch("MuTrkLayers",         "vector<int>",   & MuTrkLayers);
  tree->Branch("MuPixelLayers",       "vector<int>",   & MuPixelLayers);
  tree->Branch("MuPixelHits",         "vector<int>",   & MuPixelHits);
  tree->Branch("MuMuonHits",          "vector<int>",   & MuMuonHits);
  tree->Branch("MuStations",          "vector<int>",   & MuStations);
  tree->Branch("MuTrkQuality",        "vector<int>",   & MuTrkQuality);
  tree->Branch("MuIsoTrk",            "vector<float>", & MuIsoTrk);
  tree->Branch("MuPFChIso",           "vector<float>", & MuPFChIso);
  tree->Branch("MuPFPhoIso",          "vector<float>", & MuPFPhoIso);
  tree->Branch("MuPFNeuIso",          "vector<float>", & MuPFNeuIso);
  tree->Branch("MuPFPUIso",           "vector<float>", & MuPFPUIso);
  
  tree->Branch("JetPt",               "vector<float>", & JetPt);
  tree->Branch("JetEta",              "vector<float>", & JetEta);
  tree->Branch("JetPhi",              "vector<float>", & JetPhi);
  tree->Branch("JetCHF",              "vector<float>", & JetCHF);
  tree->Branch("JetNHF",              "vector<float>", & JetNHF);
  tree->Branch("JetCEF",              "vector<float>", & JetCEF);
  tree->Branch("JetNEF",              "vector<float>", & JetNEF);
  tree->Branch("JetNCH",              "vector<int>",   & JetNCH);
  tree->Branch("JetHFHAE",            "vector<float>", & JetHFHAE);
  tree->Branch("JetHFEME",            "vector<float>", & JetHFEME);
  tree->Branch("JetNConstituents",    "vector<int>",   & JetNConstituents);
  tree->Branch("JetPFLooseId",        "vector<bool>",  & JetPFLooseId);
  
  
  
  
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntries();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=Start; jentry<Stop;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if(jentry%10000 == 0)cout << "Processed: " << jentry << endl;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //cout << "4" << endl;
    /// clearing flat ntuples ////
    
    ElePt.clear();
    EleEta.clear();
    ElePhi.clear();
    EleD0.clear();
    EleDz.clear();
    EleIDbit.clear();
    
    NPU.clear();
    PUBX.clear();
    PUTrue.clear();
    PhoE.clear();
    PhoEt.clear();
    PhoEta.clear();
    PhoSCEta.clear();
    PhoPhi.clear();
    PhohasPixelSeed.clear();
    PhoEleVeto.clear();
    PhoR9.clear();
    PhoHoverE.clear();
    PhoSigmaIEtaIEta.clear();
    PhoSigmaIEtaIPhi.clear();
    PhoSigmaIPhiIPhi.clear();
    PhoPFChIso.clear();
    PhoPFPhoIso.clear();
    PhoPFNeuIso.clear();
    PhoPFChWorstIso.clear();
    
    MuPt.clear();
    MuEta.clear();
    MuPhi.clear();
    MuCharge.clear();
    MuType.clear();
    MuIsGood.clear();
    MuIsLooseID.clear();
    MuD0.clear();
    MuDz.clear();
    MuChi2NDF.clear();
    MuTrkLayers.clear();
    MuPixelLayers.clear();
    MuPixelHits.clear();
    MuMuonHits.clear();
    MuStations.clear();
    MuTrkQuality.clear();
    MuIsoTrk.clear();
    MuPFChIso.clear();
    MuPFPhoIso.clear();
    MuPFNeuIso.clear();
    MuPFPUIso.clear();
  
  
    JetPt.clear();
    JetEta.clear();
    JetPhi.clear();
    JetCHF.clear();
    JetNHF.clear();
    JetCEF.clear();
    JetNEF.clear();
    JetNCH.clear();
    JetHFHAE.clear();
    JetHFEME.clear();
    JetNConstituents.clear();
    JetPFLooseId.clear();
      
    //cout << "1" << endl;
      
    Run = run;
    Event = event;
    Lumis = lumis;
    NVtx = nVtx;
    NTrks = nTrksPV;
    Rho = rho;
    HLT_EleMuX = HLTEleMuX;
    HLT_Pho = HLTPho;
    HLT_Jet = HLTJet;
    HLT_EleMuXIsPrescaled = HLTEleMuXIsPrescaled;
    HLT_PhoIsPrescaled = HLTPhoIsPrescaled;
    HLT_JetIsPrescaled = HLTJetIsPrescaled;
    METFilters = metFilters;
    //HLT_50ns = HLT50ns;
    //HLT_IsPrescaled50ns = HLTIsPrescaled50ns;
    PFMET =pfMET;/*noHFMETType1*;*///noHFMET;//; // noHFMET was there for 50ns data
    PFMETPhi = pfMETPhi;/*noHFMETPhi;*/// // noHFMET was there for 50ns data
    PFMETsumEt = pfMETsumEt;
    PFMETmEtSig = pfMETmEtSig;
    PFMETSig = pfMETSig;
     
    
    
    for(unsigned int i = 0; i < eleD0->size(); ++i){
      ElePt.push_back(elePt->at(i));
      EleEta.push_back(eleEta->at(i));
      ElePhi.push_back(elePhi->at(i));
      EleD0.push_back(eleD0->at(i));
      EleDz.push_back(eleDz->at(i));
      EleIDbit.push_back(eleIDbit->at(i));
    }
      
    for(unsigned int i = 0; i < phoE->size(); ++i){
      if(phoEt->at(i) < 20)continue;
      if(phoHoverE->at(i) > 0.08)continue;
      //if(phoEta->at(i) > 1.479)continue;
      if(phoR9->at(i) > 1.0)continue;
      if(phoSigmaIEtaIEta->at(i) > 0.030)continue;
      PhoE.push_back(phoE->at(i));
      PhoEt.push_back(phoEt->at(i));
      PhoEta.push_back(phoEta->at(i));
      PhoSCEta.push_back(phoSCEta->at(i));
      PhoPhi.push_back(phoPhi->at(i));
      PhohasPixelSeed.push_back(phohasPixelSeed->at(i));
      PhoEleVeto.push_back(phoEleVeto->at(i));
      PhoR9.push_back(phoR9->at(i));
      PhoHoverE.push_back(phoHoverE->at(i));
      PhoSigmaIEtaIEta.push_back(phoSigmaIEtaIEta->at(i));
      PhoSigmaIEtaIPhi.push_back(phoSigmaIEtaIPhi->at(i));
      PhoSigmaIPhiIPhi.push_back(phoSigmaIPhiIPhi->at(i));
      PhoPFChIso.push_back(phoPFChIso->at(i));
      PhoPFPhoIso.push_back(phoPFPhoIso->at(i));
      PhoPFNeuIso.push_back(phoPFNeuIso->at(i));
      PhoPFChWorstIso.push_back(0); // for the new ggNtuple with MET filter this isolation is not available
    }
    
    for(unsigned int i = 0; i < muPt->size(); ++i){
      if(muPt->at(i) < 10) continue;
      MuPt.push_back(muPt->at(i));
      MuEta.push_back(muEta->at(i));
      MuPhi.push_back(muPhi->at(i));
      MuCharge.push_back(muCharge->at(i));
      MuType.push_back(muType->at(i));
      MuIsGood.push_back(muIsMediumID->at(i));
      MuIsLooseID.push_back(muIsLooseID->at(i));
      MuD0.push_back(muD0->at(i));
      MuDz.push_back(muDz->at(i));
      MuChi2NDF.push_back(muChi2NDF->at(i));
      MuTrkLayers.push_back(muTrkLayers->at(i));
      MuPixelLayers.push_back(muPixelLayers->at(i));
      MuPixelHits.push_back(muPixelHits->at(i));
      MuMuonHits.push_back(muMuonHits->at(i));
      MuStations.push_back(muStations->at(i));
      MuTrkQuality.push_back(muTrkQuality->at(i));
      MuIsoTrk.push_back(muIsoTrk->at(i));
      MuPFChIso.push_back(muPFChIso->at(i));
      MuPFPhoIso.push_back(muPFPhoIso->at(i));
      MuPFNeuIso.push_back(muPFNeuIso->at(i));
      MuPFPUIso.push_back(muPFPUIso->at(i));
    }
    
      
    for(unsigned int i = 0; i < jetPt->size(); ++i){
      if(jetPt->at(i) < 20)continue;
      JetPt.push_back(jetPt->at(i));
      JetEta.push_back(jetEta->at(i));
      JetPhi.push_back(jetPhi->at(i));
      JetPFLooseId.push_back(jetPFLooseId->at(i));
      JetCHF.push_back(jetCHF->at(i));
      JetNHF.push_back(jetNHF->at(i));
      JetCEF.push_back(jetCEF->at(i));
      JetNEF.push_back(jetNEF->at(i));
      JetNCH.push_back(jetNCH ->at(i));
      JetHFHAE.push_back(0);
      JetHFEME.push_back(0);
      JetNConstituents.push_back(0);
    }
      
      
    tree->Fill();
      
      
      
    // if (Cut(ientry) < 0) continue;
  }
  fout->cd();
  fout->Write();
  delete tree;
  delete fout;
}
