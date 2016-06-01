#include <TH1.h>
#include <TFile.h>
#include <TFractionFitter.h>
#include <iostream>
#include "/home/arka/arka/include/MyFunction.h"
#include <sys/stat.h>
#include <fstream>




void CalculateSysError(int pt, float pure, bool data, float ScaleMET, bool analysisFake){  
   
  TString OutputFolder="";
  if(analysisFake)OutputFolder = "Data_RunD_Ratio_AnalysisFake_217fb";
  else OutputFolder = "Data_RunD_Ratio_ExtendedFake_217fb";
  int stat0;
  stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  
  TString simpleOutputFolder="";
  if(analysisFake)simpleOutputFolder="Data_RunD_Simple_AnalysisFake";
  else simpleOutputFolder="Data_RunD_Simple_ExtendedFake";
    
  int stat1;
  stat1 = mkdir(simpleOutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   
  int xlow(0),xup(300);
  
  vector<float> MaxError;
  
  //////// electron reweighting  ////////////
  TH1F *h_Mix_MET;// = new TH1F("h_Mix_MET","h_Mix_MET;E_{T}^{miss} (GeV); Events",binnum, xbins);
  TH1F *h_Mix_MET_SysErr;// = new TH1F("h_Mix_MET_SysErr","h_Mix_MET;E_{T}^{miss} (GeV); Events",binnum, xbins);
  TH1F *hRatio;// = new TH1F("hRatio","Ratio; E_{T}^{miss} (GeV);ee+ff /QCD", binnum, xbins);
  TH1F *hRatioSys;// = new TH1F("hRatioSys","Ratio; E_{T}^{miss} (GeV);ee+ff /QCD", binnum, xbins);
   
  TFile *fsys=0;
  if(!data)fsys= new TFile("ErrorPropDiEMPttoElectronMET.root", "READ");
  else fsys= new TFile(OutputFolder+"/ErrorPropDiEMPttoElectronMET_Data.root", "READ");
   
   
  TH1F *ErrorPropDiEMPteeMET = (TH1F*)fsys->Get("ErrorPropDiEMPteeMET");
  TH1F *ErrorPropDiEMPtffMET = (TH1F*)fsys->Get("ErrorPropDiEMPtffMET");
  TH1F *ErrorPropDiEMPtffshowershapeMET = (TH1F*)fsys->Get("ErrorPropDiEMPtffshowershapeMET");
   
   
  TH1F *ErrorPropDiEMPtNJetseeMET = (TH1F*)fsys->Get("ErrorPropDiEMPtNJetseeMET");
  TH1F *ErrorPropDiEMPtNJetsffMET = (TH1F*)fsys->Get("ErrorPropDiEMPtNJetsffMET");
  TH1F *ErrorPropDiEMPtNJetsffshowershapeMET = (TH1F*)fsys->Get("ErrorPropDiEMPtNJetsffshowershapeMET");
   
   
  TH1F *ErrorPropDiEMPtWeightedNJetsee = (TH1F*)fsys->Get("ErrorPropDiEMPtWeightedNJetsee");
  TH1F *ErrorPropDiEMPtWeightedNJetsff = (TH1F*)fsys->Get("ErrorPropDiEMPtWeightedNJetsff");
   
  TH1F *ErrorPropDiEMPtVsNJetWeightedee = (TH1F*)fsys->Get("ErrorPropDiEMPtVsNJetWeightedee");
  TH1F *ErrorPropDiEMPtVsNJetWeightedff = (TH1F*)fsys->Get("ErrorPropDiEMPtVsNJetWeightedff");
   
   
  TFile *f8 = 0, *f9 = 0, *fTT = 0, *fZ=0;
  if(pt == 40 && !data)f8 = new TFile("DYtoEEWeightedProper74.root","READ");
  if(pt == 50 && !data)f8 = new TFile("DYtoEEWeightedProper74_Pt50.root","READ");
  if(pt == 40 && data){
    if(analysisFake)f8 = new TFile("Data_RunD_All_AnalysisFake_217fb.root","READ");
    else f8 = new TFile("Data_RunD_All_ExtendedFake_217fb.root","READ");
  }
  
  if(pt == 40 && data)fTT = new TFile("TTJetsAllFile.root","READ");
   
   
  ////////////// this is needed for TTJet subtraction /////////////////////////////
  TH1F *h_DoubleElectron_MET_DiEMPtReweighted = (TH1F*)fTT->Get("h_DoubleElectron_MET_DiEMPtReweighted");
  TH1F *h_DoubleElectron_MET_FromTT = (TH1F*)fTT->Get("h_DoubleElectron_MET");
  
  h_DoubleElectron_MET_DiEMPtReweighted = getOverflow(h_DoubleElectron_MET_DiEMPtReweighted);
  h_DoubleElectron_MET_FromTT = getOverflow(h_DoubleElectron_MET_FromTT);
  
  ///////////////////////// other files ////////////////////////////////////////////
   
  TH1F *h_DoubleElectron_MET_Reweighted = (TH1F*)f8->Get("h_DoubleElectron_MET_Reweighted");
  h_DoubleElectron_MET_Reweighted = getOverflow(h_DoubleElectron_MET_Reweighted);
  TH1F *h_DoubleElectron_MET_Reweighted_OnlyDiEMPt = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("h_DoubleElectron_MET_Reweighted_OnlyDiEMPt"); // needed for checking the diempt reweighting and then add njet reweghting difference as systematics
  
  
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "Before TTJets subtraction, ee events in signal region: " <<  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Integral(20,24) << endl;
   
  /////////////////// The TTJet Subtraction is done here ////////////////////////////////////////
  double ttJetNumber = h_DoubleElectron_MET_FromTT->Integral(0, h_DoubleElectron_MET_FromTT->GetNbinsX()+1);
  double ttJetShape = h_DoubleElectron_MET_DiEMPtReweighted->Integral(0, h_DoubleElectron_MET_DiEMPtReweighted->GetNbinsX()+1);
  h_DoubleElectron_MET_DiEMPtReweighted->Scale(ttJetNumber/ttJetShape);
  cout << "ttJetNumber/ttJetShape: " << ttJetNumber/ttJetShape << endl;
   
   
  for(int q = 0; q <= h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetNbinsX(); ++q){
    float metData =  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(q); 
    float metTT   =  h_DoubleElectron_MET_DiEMPtReweighted->GetBinContent(q);
    float reducedMET = fabs(metData - metTT);
    if(metData!=0)h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->SetBinContent(q, reducedMET);
    else h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->SetBinContent(q, 0);
  }
   
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "After TTJets subtraction, ee events in signal region: " <<  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Integral(20,24) << endl;
   
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  
   
  TH1F *h_DoubleElectron_NJets_Reweighted = (TH1F*)f8->Get("h_DoubleElectron_NJets_Reweighted");
  TH1F *h_DoubleFake_NJets_Reweighted = (TH1F*)f8->Get("h_DoubleFake_NJets_Reweighted");
  TH1F *h_DoublePhoton_NJets = (TH1F*)f8->Get("h_DoublePhoton_NJets");
   
  TH1F *h_DoublePhoton_MET_Upto100 = (TH1F*)f8->Get("h_DoublePhoton_MET_Upto100");
   
  TH1F *h_DoubleElectron_MET_ReweightedNJets = (TH1F*)f8->Get("h_DoubleElectron_MET_ReweightedNJets");
  TH1F *h_DoubleElectron_MET_ReweightedDiEMPtNJets = (TH1F*)f8->Get("h_DoubleElectron_MET_ReweightedDiEMPtNJets");
  TH1F *h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff");
   
  TH1F *h_DoubleElectron_MET_Reweighted_Normalized = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("h_DoubleElectron_MET_Reweighted_Normalized");
  TH1F *h_DoubleElectron_MET_Reweighted_ForMarc = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("h_DoubleElectron_MET_Reweighted_ForMarc");
  TH1F *h_DoubleElectron_MET = (TH1F*)f8->Get("h_DoubleElectron_MET");
   
  TH1F *h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio = (TH1F*)f8->Get("h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio");
  TH1F *h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio = (TH1F*)f8->Get("h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio");
  
  
  
  
  h_DoubleElectron_NJets_Reweighted = getOverflow(h_DoubleElectron_NJets_Reweighted);
  h_DoubleFake_NJets_Reweighted = getOverflow(h_DoubleFake_NJets_Reweighted);
  h_DoublePhoton_NJets = getOverflow(h_DoublePhoton_NJets);
  
  
  h_DoubleElectron_MET_ReweightedNJets = getOverflow(h_DoubleElectron_MET_ReweightedNJets);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff = getOverflow(h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff);
   
  h_DoubleElectron_MET_Reweighted_Normalized = getOverflow(h_DoubleElectron_MET_Reweighted_Normalized);
  h_DoubleElectron_MET_Reweighted_ForMarc = getOverflow(h_DoubleElectron_MET_Reweighted_ForMarc);
  h_DoubleElectron_MET = getOverflow(h_DoubleElectron_MET);
   
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio = getOverflow(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio);
  h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio = getOverflow(h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio);
   
  
  
  
   
  TH1F* h_LeadPhoton_Pt = (TH1F*)f8->Get("h_LeadPhoton_Pt");
  TH1F* h_TrailPhoton_Pt = (TH1F*)f8->Get("h_TrailPhoton_Pt");
  TH1F* h_LeadFake_Pt = (TH1F*)f8->Get("h_LeadFake_Pt");
  TH1F* h_TrailFake_Pt = (TH1F*)f8->Get("h_TrailFake_Pt");
  TH1F* h_LeadElectron_Pt = (TH1F*)f8->Get("h_LeadElectron_Pt");
  TH1F* h_TrailElectron_Pt = (TH1F*)f8->Get("h_TrailElectron_Pt");
  TH1F* h_DoubleElectron_InvMass = (TH1F*)f8->Get("h_DoubleElectron_InvMass");
  TH1F* h_ElectronPhoton_InvMass = (TH1F*)f8->Get("h_ElectronPhoton_InvMass");
   
   
  TH1F* h_ChargedHadIso = (TH1F*)f8->Get("h_ChargedHadIso");
  TH1F* h_ChargedHadIso_WithoutShowerCut = (TH1F*)f8->Get("h_ChargedHadIso_WithoutShowerCut");
  TH1F* h_NeutralHadIso_Photon = (TH1F*)f8->Get("h_NeutralHadIso_Photon");
  TH1F* h_PhotonHadIso_Photon = (TH1F*)f8->Get("h_PhotonHadIso_Photon");
  TH1F* h_SigmaIetaIeta_Photon = (TH1F*)f8->Get("h_SigmaIetaIeta_Photon");
  TH1F* h_NeutralHadIso_Fake = (TH1F*)f8->Get("h_NeutralHadIso_Fake");
  TH1F* h_PhotonHadIso_Fake = (TH1F*)f8->Get("h_PhotonHadIso_Fake");
  TH1F* h_SigmaIetaIeta_Fake = (TH1F*)f8->Get("h_SigmaIetaIeta_Fake");
  TH1F* h_PhotonTrigger = (TH1F*)f8->Get("h_PhotonTrigger");
  
  
  TH1F *h_ElectronPhoton_MET       = (TH1F*)f8->Get("h_ElectronPhoton_MET");
  TH1F *h_Scaled_ElectronPhoton_MET       = (TH1F*)f8->Get("h_Scaled_ElectronPhoton_MET");
  TH1F *h_Scaled_ElectronPhoton_MET_Up = (TH1F*)f8->Get("h_Scaled_ElectronPhoton_MET_Up");
  TH1F *h_Scaled_ElectronPhoton_MET_Down  = (TH1F*)f8->Get("h_Scaled_ElectronPhoton_MET_Down");
   
  h_ElectronPhoton_MET = getOverflow(h_ElectronPhoton_MET);
  h_Scaled_ElectronPhoton_MET = getOverflow(h_Scaled_ElectronPhoton_MET);
  h_Scaled_ElectronPhoton_MET_Up = getOverflow(h_Scaled_ElectronPhoton_MET_Up);
  h_Scaled_ElectronPhoton_MET_Down = getOverflow(h_Scaled_ElectronPhoton_MET_Down);
   
  TFile *Histofile = new TFile(OutputFolder+"/TwoHistogram_MET.root","RECREATE");
  //h_DoubleElectron_DiEMPt->Sumw2();
  TFile *Histofile2 = new TFile(OutputFolder+"/InvMass_Histogram.root","RECREATE");
   
  TFile *Histofile3 = new TFile(OutputFolder+"/QCD_Background.root","RECREATE");
  ////cout << "I am here too" << endl;

  if(pt == 40 && !data)f9 = new TFile("GJet_Pt40_All.root", "READ");
  if(pt == 50 && !data)f9 = new TFile("GJet_Pt40_All_Pt50.root", "READ");
  if(pt == 40 && data){
    if(analysisFake)f9 = new TFile("Data_RunD_All_AnalysisFake_217fb.root", "READ");
    else f9 = new TFile("Data_RunD_All_ExtendedFake_217fb.root", "READ");
  }
   
  TH1F *h_DoublePhoton_MET = (TH1F*)f9->Get("h_DoublePhoton_MET");
  h_DoublePhoton_MET = getOverflow(h_DoublePhoton_MET);
  
  TH1F *h_DoublePhoton_MET_Normalized = (TH1F*)h_DoublePhoton_MET->Clone("h_DoublePhoton_MET_Normalized");
   
  TH1F *h_DoubleFake_MET = (TH1F*)f9->Get("h_DoubleFake_MET");
  TH1F *h_DoubleFake_MET_Reweighted = (TH1F*)f9->Get("h_DoubleFake_MET_Reweighted");
  TH1F *h_DoubleFake_MET_ReweightedDiEMPtNJets = (TH1F*)f9->Get("h_DoubleFake_MET_ReweightedDiEMPtNJets");
  
  
  TH1F *h_DoubleFake_MET_Reweighted_OnlyDiEMPt = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_Reweighted_OnlyDiEMPt");
  
  h_DoubleFake_MET = getOverflow(h_DoubleFake_MET);
  h_DoubleFake_MET_Reweighted = getOverflow(h_DoubleFake_MET_Reweighted);
  h_DoubleFake_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleFake_MET_ReweightedDiEMPtNJets);
  h_DoubleFake_MET_Reweighted_OnlyDiEMPt = getOverflow(h_DoubleFake_MET_Reweighted_OnlyDiEMPt);
  
  TH1F *h_DoubleFake_MET_Reweighted_Normalized = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_Reweighted_Normalized");
  TH1F *h_DoubleFake_MET_Reweighted_ForMarc = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_Reweighted_ForMarc");
  
   
  TH1F *h_DoubleFakeShowershape_MET = (TH1F*)f9->Get("h_DoubleFakeShowershape_MET");
  TH1F *h_DoubleFakeShowershape_MET_Reweighted = (TH1F*)f9->Get("h_DoubleFakeShowershape_MET_Reweighted");
  TH1F *h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets = (TH1F*)f9->Get("h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets");
  
  TH1F *h_DoubleFake_MET_DiEMPt30to50 = (TH1F*)f9->Get("h_DoubleFake_MET_DiEMPt30to50");
  TH1F *h_DoublePhoton_MET_DiEMPt30to50 = (TH1F*)f9->Get("h_DoublePhoton_MET_DiEMPt30to50");
  TH1F *h_DoubleElectron_MET_DiEMPt30to50 = (TH1F*)f9->Get("h_DoubleElectron_MET_DiEMPt30to50");
  
  TH1F *h_DoubleFake_MET_DiEMPt50to70 = (TH1F*)f9->Get("h_DoubleFake_MET_DiEMPt50to70");
  TH1F *h_DoublePhoton_MET_DiEMPt50to70 = (TH1F*)f9->Get("h_DoublePhoton_MET_DiEMPt50to70");
  TH1F *h_DoubleElectron_MET_DiEMPt50to70 = (TH1F*)f9->Get("h_DoubleElectron_MET_DiEMPt50to70");
  
  TH1F *h_DoubleFake_MET_DiEMPt70to100 = (TH1F*)f9->Get("h_DoubleFake_MET_DiEMPt70to100");
  TH1F *h_DoublePhoton_MET_DiEMPt70to100 = (TH1F*)f9->Get("h_DoublePhoton_MET_DiEMPt70to100");
  TH1F *h_DoubleElectron_MET_DiEMPt70to100 = (TH1F*)f9->Get("h_DoubleElectron_MET_DiEMPt70to100");
  
  TH1F *h_DoubleFake_MET_NJet1to2 = (TH1F*)f9->Get("h_DoubleFake_MET_NJet1to2");
  TH1F *h_DoublePhoton_MET_NJet1to2 = (TH1F*)f9->Get("h_DoublePhoton_MET_NJet1to2");
  TH1F *h_DoubleElectron_MET_NJet1to2 = (TH1F*)f9->Get("h_DoubleElectron_MET_NJet1to2");
  
  TH1F *h_DoubleFake_MET_NJet3to4 = (TH1F*)f9->Get("h_DoubleFake_MET_NJet3to4");
  TH1F *h_DoublePhoton_MET_NJet3to4 = (TH1F*)f9->Get("h_DoublePhoton_MET_NJet3to4");
  TH1F *h_DoubleElectron_MET_NJet3to4 = (TH1F*)f9->Get("h_DoubleElectron_MET_NJet3to4");
  
  
  
  
  
  h_DoubleFakeShowershape_MET = getOverflow(h_DoubleFakeShowershape_MET);
  h_DoubleFakeShowershape_MET_Reweighted = getOverflow(h_DoubleFakeShowershape_MET_Reweighted);
  h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets);
  
  h_DoubleFake_MET_DiEMPt30to50 = getOverflow(h_DoubleFake_MET_DiEMPt30to50);
  h_DoublePhoton_MET_DiEMPt30to50 = getOverflow(h_DoublePhoton_MET_DiEMPt30to50);
  h_DoubleElectron_MET_DiEMPt30to50 = getOverflow(h_DoubleElectron_MET_DiEMPt30to50);
  
  h_DoubleFake_MET_DiEMPt50to70 = getOverflow(h_DoubleFake_MET_DiEMPt50to70);
  h_DoublePhoton_MET_DiEMPt50to70 = getOverflow(h_DoublePhoton_MET_DiEMPt50to70);
  h_DoubleElectron_MET_DiEMPt50to70 = getOverflow(h_DoubleElectron_MET_DiEMPt50to70);
  
  h_DoubleFake_MET_DiEMPt70to100 = getOverflow(h_DoubleFake_MET_DiEMPt70to100);
  h_DoublePhoton_MET_DiEMPt70to100 = getOverflow(h_DoublePhoton_MET_DiEMPt70to100);
  h_DoubleElectron_MET_DiEMPt70to100 = getOverflow(h_DoubleElectron_MET_DiEMPt70to100);
  
  h_DoubleFake_MET_NJet1to2 = getOverflow(h_DoubleFake_MET_NJet1to2);
  h_DoublePhoton_MET_NJet1to2 = getOverflow(h_DoublePhoton_MET_NJet1to2);
  h_DoubleElectron_MET_NJet1to2 = getOverflow(h_DoubleElectron_MET_NJet1to2);
  
  h_DoubleFake_MET_NJet3to4 = getOverflow(h_DoubleFake_MET_NJet3to4);
  h_DoublePhoton_MET_NJet3to4 = getOverflow(h_DoublePhoton_MET_NJet3to4);
  h_DoubleElectron_MET_NJet3to4 = getOverflow(h_DoubleElectron_MET_NJet3to4);
   
   
  ////////////// New histograms to show which error should be taken ////////////////////
  TH1F *h_DoubleElectron_NJetDiffError = (TH1F*)h_DoubleFake_MET->Clone("h_DoubleElectron_NJetDiffError");
  h_DoubleElectron_NJetDiffError->Reset();
  TH1F *h_DoubleElectron_NJetErrorProp = (TH1F*)h_DoubleFake_MET->Clone("h_DoubleElectron_NJetErrorProp");
  h_DoubleElectron_NJetErrorProp->Reset();
   
  TH1F *h_DoubleElectron_ffDiffError = (TH1F*)h_DoubleFake_MET->Clone("h_DoubleElectron_ffDiffError");
  h_DoubleElectron_ffDiffError->Reset();
  TH1F *h_DoubleElectron_ffErrorProp = (TH1F*)h_DoubleFake_MET->Clone("h_DoubleElectron_ffErrorProp");
  h_DoubleElectron_ffErrorProp->Reset();
   
  
   ///////////// this is needed for ZNuNuJet subtraction, only for extended fake samples ////////////////////
  
  if(pt == 40 && data){
    if(analysisFake)fZ = new TFile("ZNuNuAllHT_AnalysisFake.root","READ");
    else fZ = new TFile("ZNuNuAllHT_ExtendedFake.root","READ");
  }
  TH1F *h_DoubleFake_MET_DiEMPtReweighted_FromZ = (TH1F*)fZ->Get("h_DoubleFake_MET_DiEMPtReweighted");
  TH1F *h_DoubleFake_MET_FromZ = (TH1F*)fZ->Get("h_DoubleFake_MET");
  
  h_DoubleFake_MET_DiEMPtReweighted_FromZ  = getOverflow(h_DoubleFake_MET_DiEMPtReweighted_FromZ);
  h_DoubleFake_MET_FromZ = getOverflow(h_DoubleFake_MET_FromZ);
  
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "Before ZNuNuJets subtraction, ff events in signal region: " <<  h_DoubleFake_MET_Reweighted->Integral(20,24) << endl;
   
  
  /////////////////// The ZNuNuJet Subtraction is done here ////////////////////////////////////////
  double ZNuNuJetNumber = h_DoubleFake_MET_FromZ->Integral(0, h_DoubleFake_MET_FromZ->GetNbinsX()+1);
  double ZNuNuJetShape = h_DoubleFake_MET_DiEMPtReweighted_FromZ->Integral(0, h_DoubleFake_MET_DiEMPtReweighted_FromZ->GetNbinsX()+1);
  h_DoubleFake_MET_DiEMPtReweighted_FromZ->Scale(ZNuNuJetNumber/ZNuNuJetShape);
  cout << "ZNuNuJetNumber/ZNuNuJetShape: " << ZNuNuJetNumber/ZNuNuJetShape << endl;
   
   
  for(int q = 0; q <= h_DoubleFake_MET_Reweighted->GetNbinsX(); ++q){
    float metData =  h_DoubleFake_MET_Reweighted->GetBinContent(q); 
    float metZ   =  h_DoubleFake_MET_DiEMPtReweighted_FromZ->GetBinContent(q);
    float reducedMET = fabs(metData - metZ);
    if(metData!=0)h_DoubleFake_MET_Reweighted->SetBinContent(q, reducedMET);
    else h_DoubleFake_MET_Reweighted->SetBinContent(q, 0);
  }
   
  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  cout << "After ZNuNuJets subtraction, ff events in signal region: " <<  h_DoubleFake_MET_Reweighted->Integral(20,24) << endl;
   
  ///////////////////////////////////////////////////////////////////////////////////////////////
  
  ////////// These are needed to get additional systematcis coming from ff estimation from MonteCarlo //////////////
   
   
  TFile *KeithFile = new TFile("KeithSuggestionResult.root", "READ");
  TH1F *h_ff_FromKeithEstimate_WithSlopeError = (TH1F*)KeithFile->Get("h_ff_FromKeithEstimate_WithSlopeError");
  TH1F *h_ff_FromKeithEstimate_WithInterceptError = (TH1F*)KeithFile->Get("h_ff_FromKeithEstimate_WithInterceptError");
   
   
  TFile *KeithFileConstAndSlope = new TFile(/*"KeithSuggestionResultConstantAndSlope.root"*/"KeithSuggestionResultConstantAndSlopeNormalized.root", "READ");
  
  TH1F *h_ff_FromKeithEstimate_WithConstAndSlopeDiffError = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithConstAndSlopeDiffError");
  TH1F *h_ff_FromKeithEstimate_WithffStatError = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithffStatError");
  TH1F *h_ff_FromKeithEstimate_WithffDiEMPtError = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithffDiEMPtError");
  
  TH1F *h_ff_FromKeithEstimate_WithSlope = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithSlope");
  TH1F *h_ff_FromKeithEstimate_WithSlopeOneSigmaUp = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithSlopeOneSigmaUp");
  TH1F *h_ff_FromKeithEstimate_WithSlopeOneSigmaDown = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithSlopeOneSigmaDown");

  TH1F *h_ff_FromKeithEstimate_WithInterceptOneSigmaUp = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithInterceptOneSigmaUp");
  TH1F *h_ff_FromKeithEstimate_WithInterceptOneSigmaDown = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithInterceptOneSigmaDown");

  TH1F *h_ff_FromKeithEstimate_WithConstant = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithConstant");
  TH1F *h_ff_FromKeithEstimate_WithConstantOneSigmaUp = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithConstantOneSigmaUp");
  TH1F *h_ff_FromKeithEstimate_WithConstantOneSigmaDown = (TH1F*)KeithFileConstAndSlope->Get("h_ff_FromKeithEstimate_WithConstantOneSigmaDown");
   
   
  //// output text file printing out the error /////
   
  ofstream myfileText;
  if(analysisFake)myfileText.open(OutputFolder+"/EEAndFFDiffErrorUpdatedJan12AnalysisFake.txt");
  else myfileText.open(OutputFolder+"/EEAndFFDiffErrorUpdatedJan12ExtendedFake.txt");
  
  ofstream myfileErrorSignal;
  if(analysisFake)myfileErrorSignal.open(OutputFolder+"/EEAndFFDiffErrorSignalRegionAnalysisFake.txt");
  else myfileErrorSignal.open(OutputFolder+"/EEAndFFDiffErrorSignalRegionExtendedFake.txt");
   
  ofstream myfileNJets;
  if(analysisFake)myfileNJets.open(OutputFolder+"/NJetDiffErrorUpdatedJan12AnalysisFake.txt");
  else myfileNJets.open(OutputFolder+"/NJetDiffErrorUpdatedJan12ExtendedFake.txt");
  
  ofstream myfileSystematics;
  if(analysisFake)myfileSystematics.open(OutputFolder+"/FinalSystematicsAnalysisFake.txt");
  else myfileSystematics.open(OutputFolder+"/FinalSystematicsExtendedFake.txt");
  
  ofstream eeStatError;
  eeStatError.open(OutputFolder+"/StatErrorEESample.txt");
   
   
  //cout << "njets reweighted fakeshowershape E_{T}^{miss}: " << h_DoubleFakeShowershape_MET_Reweighted->GetBinContent(5) << endl;
  //cout << "diempt reweighted fake E_{T}^{miss}: " << h_DoubleFake_MET_Reweighted->Integral(1, 13) << endl;
  TH1F *h_DoubleElectron_MET_Reweighted_ExpFit = (TH1F*)h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Clone("h_DoubleElectron_MET_Reweighted_ExpFit");
  TH1F *h_DoubleFake_MET_Reweighted_ExpFit = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_Reweighted_ExpFit");
  
  for(int i = 0; i < h_DoubleElectron_MET_Reweighted->GetNbinsX(); ++i){
    double x = h_DoubleElectron_MET_Reweighted_ForMarc->GetBinContent(i+1);
    double staterx = h_DoubleElectron_MET_Reweighted_ForMarc->GetBinError(i+1);
    double syserx  = ErrorPropDiEMPteeMET->GetBinError(i+1);
    double toterr = sqrt(staterx*staterx+syserx*syserx);
    h_DoubleElectron_MET_Reweighted_ForMarc->SetBinError(i+1, toterr);
    h_DoubleElectron_MET_Reweighted_ExpFit->SetBinError(i+1, toterr);
    
    double staterx2 = h_DoubleFake_MET_Reweighted_ForMarc->GetBinError(i+1);
    double syserx2  = ErrorPropDiEMPtffMET->GetBinError(i+1);
    double toterr2 = sqrt(staterx2*staterx2+syserx2*syserx2);
    h_DoubleFake_MET_Reweighted_ForMarc->SetBinError(i+1, toterr2);
    h_DoubleFake_MET_Reweighted_ExpFit->SetBinError(i+1, toterr2);
    
  }
  
  
  Histofile->cd();
  h_DoubleElectron_MET_Reweighted_ForMarc->Write();
  h_DoubleFake_MET_Reweighted_ForMarc->Write();
  h_DoublePhoton_MET->Write();
   
  
   
  Histofile2->cd();
  h_DoubleElectron_InvMass->Write();
  h_ElectronPhoton_InvMass->Write();
   
  vector<TH1F*> VecTH1Check;
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
   
  vector<TString> LegName2;
  LegName2.clear();
  LegName2.push_back("ee E_{T}^{miss}");
   
  vector<Color_t>color2;
  color2.clear();
  color2.push_back(4);
   
  DrawHists(VecTH1Check, LegName2, color2, xlow, xup, 1, 3000, OutputFolder+"/OnlyDoubleElectronMETBeforeScale_Logy", 0, 0, false, true);
   
  double norm1 = h_DoubleElectron_MET_Reweighted_Normalized->Integral(0, h_DoubleElectron_MET_Reweighted_Normalized->GetNbinsX()+1);
  h_DoubleElectron_MET_Reweighted_Normalized->Scale(1./norm1);
   
   
  double norm2 = h_DoubleFake_MET_Reweighted_Normalized->Integral(0, h_DoubleFake_MET_Reweighted_Normalized->GetNbinsX()+1);
  h_DoubleFake_MET_Reweighted_Normalized->Scale(1./norm2);
   
   
  double norm3 = h_DoublePhoton_MET_Normalized->Integral(0, h_DoublePhoton_MET_Normalized->GetNbinsX()+1);
  h_DoublePhoton_MET_Normalized->Scale(1./norm3);
   
  TObjArray *bg = new TObjArray(2);        // MC histograms are put in this array
  bg->Add(h_DoubleElectron_MET_Reweighted_Normalized);
  bg->Add(h_DoubleFake_MET_Reweighted_Normalized);
  TFractionFitter* fit = new TFractionFitter(h_DoublePhoton_MET_Normalized, bg); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(1,h_DoubleElectron_MET_Reweighted_Normalized->GetNbinsX());                    // use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  //cout << "fit status: " << status << endl;
  double fitchi2=fit->GetChisquare();
  int NDF=fit->GetNDF();
  //std:://cout << "fit status: " << status << std::endl;
  //std:://cout << "chi2:       " << fitchi2 << std::endl;
  //std:://cout << "chi2/ndf:   " << fitchi2/NDF << std::endl;
   
   
  h_Mix_MET = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("h_Mix_MET");
  h_Mix_MET->Reset();
  h_Mix_MET->SetTitle("Mixture of ee and ff E_{T}^{miss}");
   
  h_Mix_MET_SysErr = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("h_Mix_MET_SysErr");
  h_Mix_MET_SysErr->Reset();
  h_Mix_MET_SysErr->SetTitle("Mixture of ee and ff E_{T}^{miss}");
   
  hRatio = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio");
  hRatio->Reset();
  hRatio->SetTitle("Ratio");
   
  hRatioSys = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioSys");
  hRatioSys->Reset();
  hRatioSys->SetTitle("Ratio");
  
   
  int ScaleBin = h_DoublePhoton_MET->FindBin(ScaleMET);
  double photonError;
  Double_t photonInt=h_DoublePhoton_MET->IntegralAndError(0, ScaleBin, photonError);// - h_Scaled_ElectronPhoton_MET->Integral(0, ScaleBin);
   
   
   
   
  //cout << "Photon Integral upto 50 GeV:" << photonInt << endl;
  //cout << "5th bin of DiEMPt reeweighted ee E_{T}^{miss} before scaling: " << h_DoubleElectron_MET_Reweighted->GetBinContent(5) << " and error: " << h_DoubleElectron_MET_Reweighted->GetBinError(5) << endl;;
   
  Double_t eeInt=h_DoubleElectron_MET->Integral(0, ScaleBin);
  h_DoubleElectron_MET->Scale(photonInt/eeInt);
   
   
  Double_t eediemptInt=h_DoubleElectron_MET_Reweighted->Integral(0, ScaleBin);
  h_DoubleElectron_MET_Reweighted->Scale(photonInt/eediemptInt);
   
   
   
  Double_t eediemptIntNew = h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Integral(0, ScaleBin);
  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Scale(photonInt/eediemptIntNew);
   
   
   
  Double_t eediemptnjetsInt=h_DoubleElectron_MET_ReweightedDiEMPtNJets->Integral(0, ScaleBin);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets->Scale(photonInt/eediemptnjetsInt);
   
  Double_t eediemptnjetsshapeInt=h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->Integral(0, ScaleBin);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->Scale(photonInt/eediemptnjetsshapeInt);
   
   
   
  //cout << "5th bin of DiEMPt reweighted ee E_{T}^{miss} after scaling: " << h_DoubleElectron_MET_Reweighted->GetBinContent(5) << " and error: " << h_DoubleElectron_MET_Reweighted->GetBinError(5) << endl;
  //cout << "Electron integral upto 50 GeV: " << h_DoubleElectron_MET_Reweighted->Integral(1, ScaleBin) << endl;
   
  //cout << "5th bin of DiEMPt reweighted ff E_{T}^{miss} before scaling: " << h_DoubleFake_MET_Reweighted->GetBinContent(5) << " and error: " << h_DoubleFake_MET_Reweighted->GetBinError(5) << endl;
   
  double fakeError;
  Double_t fakeInt=h_DoubleFake_MET->IntegralAndError(0, ScaleBin, fakeError);
   
   
  int METSignalBin = h_DoublePhoton_MET->FindBin(100);
   
  cout << "++++++++++++++++++++++++++++++++++ Testing Keith's hypothesis ++++++++++++++++++++++++++++++++++++" << endl;   
  cout << "photon E_{T}^{miss} upto 50 GeV: " << photonInt << " and error: " << photonError << " and fake E_{T}^{miss} upto 50 GeV: " << fakeInt << " and error: " << fakeError << " and ratio: " << photonInt/fakeInt << endl;
  double integralError(0), integralError2(0);
  double dummyIntegral = h_DoubleFake_MET->IntegralAndError(METSignalBin, h_DoubleFake_MET->GetNbinsX()+1, integralError);
  cout << "Fake E_{T}^{miss} without scaling > 100 GeV: " << h_DoubleFake_MET->Integral(METSignalBin, h_DoubleFake_MET->GetNbinsX()+1) << " and error: " << integralError << endl;
   
  h_DoubleFake_MET->Scale(photonInt/fakeInt);
  dummyIntegral = h_DoubleFake_MET->IntegralAndError(METSignalBin, h_DoubleFake_MET->GetNbinsX()+1, integralError2);
  cout << "Fake E_{T}^{miss} >100 GeV after scaling: " << h_DoubleFake_MET->IntegralAndError(METSignalBin, h_DoubleFake_MET->GetNbinsX()+1, integralError2) << " and error: " << integralError2 << endl;
   
  cout << "In each bin after E_{T}^{miss}>100 GeV" << endl;
   
  for(int q = METSignalBin; q <= h_DoubleFake_MET->GetNbinsX(); ++q){
    cout << "Bin: " << q << " Value: " << h_DoubleFake_MET->GetBinContent(q) << " and error: " << h_DoubleFake_MET->GetBinError(q) << endl; 
  }
     
   
  Double_t fakediemptInt=h_DoubleFake_MET_Reweighted->Integral(0, ScaleBin);
  h_DoubleFake_MET_Reweighted->Scale(photonInt/fakediemptInt);
  
  
  
  Double_t fakeOnlyDiemptInt=h_DoubleFake_MET_Reweighted_OnlyDiEMPt->Integral(0, ScaleBin);
  h_DoubleFake_MET_Reweighted_OnlyDiEMPt->Scale(photonInt/fakeOnlyDiemptInt);
   
   
  //cout << "Fake Integral upto 50 GeV:" << fakediemptInt << endl;
  //cout << "5th bin of DiEMPt reweighted ff E_{T}^{miss} after scaling: " << h_DoubleFake_MET_Reweighted->GetBinContent(5) << " and error: " << h_DoubleFake_MET_Reweighted->GetBinError(5) << endl;
  //cout << "DiEMPt reweighted Fake integral upto 50 GeV: " << h_DoubleFake_MET_Reweighted->Integral(1, ScaleBin) << endl;
   
  //cout << "5th bin of DiEMPt*NJets reweighted ff E_{T}^{miss} before scaling: " << h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinContent(5) << " and error: " << h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinError(5) << endl;
  Double_t fakediemptnjetsInt=h_DoubleFake_MET_ReweightedDiEMPtNJets->Integral(0, ScaleBin);
  h_DoubleFake_MET_ReweightedDiEMPtNJets->Scale(photonInt/fakediemptnjetsInt);
  //cout << "Fake DiEMPT NJETS Integral upto 50 GeV:" << fakediemptnjetsInt << endl;
  //cout << "5th bin of DiEMPt*NJets reweighted ff E_{T}^{miss} after scaling: " << h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinContent(5) << " and error: " << h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinError(5) << endl;
  //cout << "DiEMPt*NJets reweighted Fake integral upto 50 GeV: " << h_DoubleFake_MET_ReweightedDiEMPtNJets->Integral(1, ScaleBin) << endl;
  Double_t fakeshowershapeInt=h_DoubleFakeShowershape_MET->Integral(0, ScaleBin);
  h_DoubleFakeShowershape_MET->Scale(photonInt/fakeshowershapeInt);
   
   
  Double_t fakeshowershapediemptInt=h_DoubleFakeShowershape_MET_Reweighted->Integral(0, ScaleBin);
  h_DoubleFakeShowershape_MET_Reweighted->Scale(photonInt/fakeshowershapediemptInt);
   
  Double_t fakeshowershapediemptnjetsInt=h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->Integral(0, ScaleBin);
  h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->Scale(photonInt/fakeshowershapediemptnjetsInt);
   
  Double_t eeDiEMPtVsNJetInt = h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Integral(0, ScaleBin);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Scale(photonInt/eeDiEMPtVsNJetInt);
   
  Double_t ffDiEMPtVsNJetInt = h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->Integral(0, ScaleBin);
  h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->Scale(photonInt/ffDiEMPtVsNJetInt);
   
   
  ErrorPropDiEMPteeMET->Scale(photonInt/eediemptInt);
  ErrorPropDiEMPtffMET->Scale(photonInt/fakediemptInt);
   
  ErrorPropDiEMPtffshowershapeMET->Scale(photonInt/fakeshowershapediemptInt);
   
  ErrorPropDiEMPtNJetseeMET->Scale(photonInt/eediemptnjetsInt);
  ErrorPropDiEMPtNJetsffMET->Scale(photonInt/fakediemptnjetsInt);
   
  ErrorPropDiEMPtNJetsffshowershapeMET->Scale(photonInt/fakeshowershapediemptnjetsInt);
   
   
  ErrorPropDiEMPtVsNJetWeightedee->Scale(photonInt/eeDiEMPtVsNJetInt);
  ErrorPropDiEMPtVsNJetWeightedff->Scale(photonInt/ffDiEMPtVsNJetInt);
  
  
  
  
  Double_t eeDiEMPtBin30to50 = h_DoubleElectron_MET_DiEMPt30to50->Integral(0, h_DoubleElectron_MET_DiEMPt30to50->GetNbinsX()+1);
  h_DoubleElectron_MET_DiEMPt30to50->Scale(1./eeDiEMPtBin30to50, "width");
  Double_t eeDiEMPtBin50to70 = h_DoubleElectron_MET_DiEMPt50to70->Integral(0, h_DoubleElectron_MET_DiEMPt50to70->GetNbinsX()+1);
  h_DoubleElectron_MET_DiEMPt50to70->Scale(1./eeDiEMPtBin50to70, "width");
  Double_t eeDiEMPtBin70to100 = h_DoubleElectron_MET_DiEMPt70to100->Integral(0, h_DoubleElectron_MET_DiEMPt70to100->GetNbinsX()+1);
  h_DoubleElectron_MET_DiEMPt70to100->Scale(1./eeDiEMPtBin70to100, "width");
  
  
  Double_t ffDiEMPtBin30to50 = h_DoubleFake_MET_DiEMPt30to50->Integral(0, h_DoubleFake_MET_DiEMPt30to50->GetNbinsX()+1);
  h_DoubleFake_MET_DiEMPt30to50->Scale(1./ffDiEMPtBin30to50, "width");
  Double_t ffDiEMPtBin50to70 = h_DoubleFake_MET_DiEMPt50to70->Integral(0, h_DoubleFake_MET_DiEMPt50to70->GetNbinsX()+1);
  h_DoubleFake_MET_DiEMPt50to70->Scale(1./ffDiEMPtBin50to70, "width");
  Double_t ffDiEMPtBin70to100 = h_DoubleFake_MET_DiEMPt70to100->Integral(0, h_DoubleFake_MET_DiEMPt70to100->GetNbinsX()+1);
  h_DoubleFake_MET_DiEMPt70to100->Scale(1./ffDiEMPtBin70to100, "width");
   
  
  Double_t eeNJet1to2 = h_DoubleElectron_MET_NJet1to2->Integral(0, h_DoubleElectron_MET_NJet1to2->GetNbinsX()+1);
  h_DoubleElectron_MET_NJet1to2->Scale(1./eeNJet1to2, "width");
  Double_t ffNJet1to2 = h_DoubleFake_MET_NJet1to2->Integral(0, h_DoubleFake_MET_NJet1to2->GetNbinsX()+1);
  h_DoubleFake_MET_NJet1to2->Scale(1./ffNJet1to2, "width");
  
  Double_t eeNJet3to4 = h_DoubleElectron_MET_NJet3to4->Integral(0, h_DoubleElectron_MET_NJet3to4->GetNbinsX()+1);
  h_DoubleElectron_MET_NJet3to4->Scale(1./eeNJet3to4, "width");
  Double_t ffNJet3to4 = h_DoubleFake_MET_NJet3to4->Integral(0, h_DoubleFake_MET_NJet3to4->GetNbinsX()+1);
  h_DoubleFake_MET_NJet3to4->Scale(1./ffNJet3to4, "width");
  
  
  
  h_DoubleFake_MET->GetYaxis()->SetTitle("Events/GeV");
   
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoublePhoton_MET);
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFake_MET_Reweighted);
   
  color2.clear();
  color2.push_back(kBlack);
  color2.push_back(4);
  color2.push_back(2);
   
  LegName2.clear();
  LegName2.push_back("#gamma#gamma");
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioCheck = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioCheck");
  hRatioCheck->Reset();
  hRatioCheck->SetTitle("");
  hRatioCheck->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheck->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioCheck2 = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("hRatioCheck2");
  hRatioCheck2->Reset();
  hRatioCheck2->SetTitle("");
  hRatioCheck2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheck2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
     
     
  DrawHistsRatioTwo(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, simpleOutputFolder+"/NewMETDistributionBeforeErrorPropNotBinNormalized_Logy", hRatioCheck, hRatioCheck2, 1, 1, true, true);
   
   
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoublePhoton_MET);
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFakeShowershape_MET_Reweighted);
   
  LegName2.clear();
  LegName2.push_back("#gamma#gamma");
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioCheck3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioCheck3");
  hRatioCheck3->Reset();
  hRatioCheck3->SetTitle("");
  hRatioCheck3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheck3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioCheck23 = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("hRatioCheck23");
  hRatioCheck23->Reset();
  hRatioCheck23->SetTitle("");
  hRatioCheck23->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheck23->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
     
     
  DrawHistsRatioTwo(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, simpleOutputFolder+"/NewMETDistributionShowershapeBeforeErrorPropNotBinNormalized_Logy", hRatioCheck3, hRatioCheck23, 1, 1, true, true);
   
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoublePhoton_MET);
  VecTH1Check.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1Check.push_back(h_DoubleFake_MET_ReweightedDiEMPtNJets);
   
  color2.clear();
  color2.push_back(kBlack);
  color2.push_back(4);
  color2.push_back(2);
   
  LegName2.clear();
  LegName2.push_back("#gamma#gamma");
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioCheckNJets = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioCheckNJets");
  hRatioCheckNJets->Reset();
  hRatioCheckNJets->SetTitle("");
  hRatioCheckNJets->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheckNJets->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioCheckNJets2 = (TH1F*)h_DoubleFake_MET_ReweightedDiEMPtNJets->Clone("hRatioCheckNJets2");
  hRatioCheckNJets2->Reset();
  hRatioCheckNJets2->SetTitle("");
  hRatioCheckNJets2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheckNJets2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
     
     
  DrawHistsRatioTwo(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, simpleOutputFolder+"/NewMETDistributionDiEMPtNJetsBeforeErrorPropNotBinNormalized_Logy", hRatioCheckNJets, hRatioCheckNJets2, 1, 1, true, true);
   
   
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoublePhoton_MET);
  VecTH1Check.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1Check.push_back(h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets);
   
  LegName2.clear();
  LegName2.push_back("#gamma#gamma");
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioCheckNJets3 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioCheckNJets3");
  hRatioCheckNJets3->Reset();
  hRatioCheckNJets3->SetTitle("");
  hRatioCheckNJets3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheckNJets3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioCheckNJets23 = (TH1F*)h_DoubleFake_MET_ReweightedDiEMPtNJets->Clone("hRatioCheckNJets23");
  hRatioCheckNJets23->Reset();
  hRatioCheckNJets23->SetTitle("");
  hRatioCheckNJets23->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioCheckNJets23->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
     
     
  DrawHistsRatioTwo(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, simpleOutputFolder+"/NewMETDistributionShowershapeDiEMPtNJetsBeforeErrorPropNotBinNormalized_Logy", hRatioCheck3, hRatioCheck23, 1, 1, true, true);
   
   
      
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFake_MET_Reweighted);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_ratio_BeforeErrorPropNotBinNormalized_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_DiEMPt30to50);
  VecTH1Check.push_back(h_DoubleFake_MET_DiEMPt30to50);
   
   
   
  LegName2.clear();
  LegName2.push_back("ee (30 < di-EM p_{T} < 50)");
  LegName2.push_back("ff (30 < di-EM p_{T} < 50)");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0001, 1, OutputFolder+"/ee_ff_MET_ratio_DiEMPt30to50_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_DiEMPt50to70);
  VecTH1Check.push_back(h_DoubleFake_MET_DiEMPt50to70);
   
   
   
  LegName2.clear();
  LegName2.push_back("ee (50 < di-EM p_{T} < 70)");
  LegName2.push_back("ff (50 < di-EM p_{T} < 70)");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0001, 1, OutputFolder+"/ee_ff_MET_ratio_DiEMPt50to70_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_DiEMPt70to100);
  VecTH1Check.push_back(h_DoubleFake_MET_DiEMPt70to100);
   
   
   
  LegName2.clear();
  LegName2.push_back("ee (70 < di-EM p_{T} < 100)");
  LegName2.push_back("ff (70 < di-EM p_{T} < 100)");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0001, 1, OutputFolder+"/ee_ff_MET_ratio_DiEMPt70to100_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_NJet1to2);
  VecTH1Check.push_back(h_DoubleFake_MET_NJet1to2);
   
   
  LegName2.clear();
  LegName2.push_back("ee (1 <= N_{jets} <=2)");
  LegName2.push_back("ff (1 <= N_{jets} <=2)");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0001, 1, OutputFolder+"/ee_ff_MET_ratio_NJet1to2_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_NJet3to4);
  VecTH1Check.push_back(h_DoubleFake_MET_NJet3to4);
   
   
  LegName2.clear();
  LegName2.push_back("ee (3 <= N_{jets} <=4)");
  LegName2.push_back("ff (3 <= N_{jets} <=4)");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0001, 1, OutputFolder+"/ee_ff_MET_ratio_NJet3to4_Logy_", hRatioTwo, 1, 1, true, true);
 
   
   
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFakeShowershape_MET_Reweighted);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ee");
  LegName2.push_back("reweighted ff");
   
  TH1F *hRatioTwo2 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatioTwo2->Reset();
  hRatioTwo2->SetTitle("");
  hRatioTwo2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo2->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_ratio_BeforeErrorPropNotBinNormalized_Logy_", hRatioTwo2, 1, 1, true, true);
   
  double frac = pure;
  double errFraceeFromDiEMPt(0), errFraceeFromNJets(0), errFraceeFromNJetsNew(0);
  double errFracffFromDiEMPt(0), errFracffFromNJets(0);
  double errFraceeShapeDiff(0), errFraceeShapeDiffKeith(0);
  double errFraceeShapeDiffKeithSlope(0), errFraceeShapeDiffKeithIntercept(0);
  double totalMETEE(0), totalMETEENew(0), totalMETFF(0);
   
  //h_DoubleElectron_MET->Scale(eeInt/photonInt);
  //h_DoubleFake_MET->Scale(fakeInt/photonInt);
  /////////////// ee and ff MET values from fit to get shape difference from bin 71-90 to 140-300///////////////////////////// 
  double eeMETFromFit[] = {9.68, 5.74, 3.18, 1.87, 1.16, 1.25, 1.39}; 
  double ffMETFromFit[] = {27.27, 10.24, 4.30, 2.21, 1.30, 1.43, 3.48}; 
  
  for(int i=0; i < h_DoubleElectron_MET_Reweighted->GetNbinsX(); ++i){
    MaxError.clear();
    double x = h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1);
    double staterx = h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1);//
    double staterx_unweighted = h_DoubleElectron_MET->GetBinError(i+1);
    //staterx = staterx_unweighted;
    double syserx  = ErrorPropDiEMPteeMET->GetBinError(i+1);
    //syserx = syserx*(photonInt/eediemptInt);
    double erx = sqrt(staterx*staterx+syserx*syserx);
     
    eeStatError << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$ MET Bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    eeStatError << "Stat error of ee, weighted error: " << staterx << " unweighted error: " << staterx_unweighted << endl;
    eeStatError << "difference between them : " << fabs(staterx - staterx_unweighted) << " fraction: " << fabs(staterx - staterx_unweighted)*100/x << " % " << endl;
    //cout << "Only DiEMPt reweighted bin: " << i+1 << " ee Stat error: " << staterx << " ee Sys error: " << syserx << " total error ee E_{T}^{miss}: " << erx << endl;
    //h_DoubleElectron_MET_Reweighted->SetBinContent(i+1, x);
    h_DoubleElectron_MET_Reweighted->SetBinError(i+1, erx);
     
     
    double y = h_DoubleFake_MET_Reweighted->GetBinContent(i+1);
    double statery = h_DoubleFake_MET_Reweighted->GetBinError(i+1);
    double sysery  = ErrorPropDiEMPtffMET->GetBinError(i+1);
     
    //cout << "FF Only DiEMPt reweighted bin: " << i+1 << " ff E_{T}^{miss}: " << y << " ff sys error: " << sysery << " and scale factor: " << (photonInt/fakediemptInt) <<endl;
    //sysery = sysery*(photonInt/fakediemptInt);
    double ery = sqrt(statery*statery+sysery*sysery);
    //cout << "Only DiEMPt reweighted bin: " << i+1 << " ff Stat error: " << statery << " ff Sys error: " << sysery << " Error ff E_{T}^{miss}: " << ery << endl;
    h_DoubleFake_MET_Reweighted->SetBinContent(i+1, y);
    h_DoubleFake_MET_Reweighted->SetBinError(i+1, ery);
    
    h_DoubleFake_MET_Reweighted_OnlyDiEMPt->SetBinError(i+1, ery);
    
     
    double statery4 = h_DoubleFakeShowershape_MET_Reweighted->GetBinError(i+1);
    double sysery4  = ErrorPropDiEMPtffshowershapeMET->GetBinError(i+1);
    //sysery4 = sysery4*(photonInt/fakeshowershapediemptInt);
    double ery4 = sqrt(statery4*statery4+sysery4*sysery4);
    ////cout << "Only DiEMPt reweighted bin: " << i+1 << " ffshowershape Stat error: " << statery4 << " ff Sys error: " << sysery4 << " Error ff E_{T}^{miss}: " << ery4 << endl;
    h_DoubleFakeShowershape_MET_Reweighted->SetBinError(i+1, ery4);
     
     
     
    double staterx2 = h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinError(i+1);
    double syserx2  = ErrorPropDiEMPtNJetseeMET->GetBinError(i+1);
    double syserx3 = h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) - h_DoubleFake_MET_Reweighted->GetBinContent(i+1);
    //syserx2 = syserx2*(photonInt/eediemptnjetsInt);
    double erx2 = sqrt(staterx2*staterx2+syserx*syserx+syserx2*syserx2);
    //cout << "DiEMPt*NJets reweighting bin: " << i+1 << " ee Stat error: " << staterx2 << " ee Sys error: " << syserx2 << " Error ee E_{T}^{miss}: " << erx2 << endl;
    h_DoubleElectron_MET_ReweightedDiEMPtNJets->SetBinError(i+1, erx2);
     
    double erx3 = sqrt(staterx2*staterx2+syserx2*syserx2+syserx3*syserx3);
    //cout << "DiEMPt*NJets reweighting bin: " << i+1 << " ee Stat error: " << staterx2 << " ee Sys error: " << syserx2 << " Error total: " << erx3 << endl;
    //cout << "DiEMPt*NJets reweighting bin: " << i+1 << " ee E_{T}^{miss} value: " << h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) << endl;
    h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->SetBinError(i+1, erx3);
     
    double met = h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinContent(i+1);
    double statery2 = h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinError(i+1);
    double sysery2  = ErrorPropDiEMPtNJetsffMET->GetBinError(i+1);
    //cout << "DiEMPt*NJets reweighting bin: " << i+1 << " ff E_{T}^{miss}: " << met << " ff sys error before scaling: " << sysery2 << " and scale factor: " << (photonInt/fakediemptnjetsInt) << endl;
    //sysery2 = sysery2*(photonInt/fakediemptnjetsInt);
    double ery2 = sqrt(statery2*statery2+sysery2*sysery2);
    //cout << "DiEMPt*NJets reweighting bin: " << i+1 << " ff Stat error: " << statery2 << " ff Sys error: " << sysery2 << " Error ff E_{T}^{miss}: " << ery2 << endl;
    h_DoubleFake_MET_ReweightedDiEMPtNJets->SetBinError(i+1, ery2);
     
     
    double statery5 = h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->GetBinError(i+1);
    double sysery5  = ErrorPropDiEMPtNJetsffshowershapeMET->GetBinError(i+1);
    //sysery5 = sysery5*(photonInt/fakeshowershapediemptnjetsInt);
    double ery5 = sqrt(statery5*statery5+sysery5*sysery5);
    ////cout << "bin: " << i+1 << " ff Stat error: " << statery << " ff Sys error: " << sysery << " Error ff E_{T}^{miss}: " << ery << endl;
    h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->SetBinError(i+1, ery5);
     
     
    int binInclude = h_DoubleElectron_MET_ReweightedDiEMPtNJets->FindBin(100);
     
    double error = (frac*frac*erx*erx+(1-frac)*(1-frac)*ery*ery);
    error = sqrt(error);
    h_Mix_MET->SetBinContent(i+1, frac*x+(1-frac)*y);
    h_Mix_MET->SetBinError(i+1, error);
    h_Mix_MET_SysErr->SetBinContent(i+1,1);
    h_Mix_MET_SysErr->SetBinError(i+1, sqrt(frac*frac*syserx*syserx+(1-frac)*(1-frac)*sysery*sysery));
     
     
     
    // from 2D GetPlot
     
    double stat2Dee = h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinError(i+1);
    double sys2Dee = ErrorPropDiEMPtVsNJetWeightedee->GetBinError(i+1);
    double err2Dee = sqrt(stat2Dee*stat2Dee + sys2Dee*sys2Dee);
    h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->SetBinError(i+1, err2Dee);
     
    ////////// Work with ff systematcis here /////////////////////
     
     
     
    double diff = fabs(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(i+1) - h_DoubleElectron_MET_Reweighted->GetBinContent(i+1));
    cout << "For bin " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " diff : " << diff << endl;
    double diff_Error = sqrt(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinError(i+1)*h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinError(i+1) + h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1)*h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1));
     
    h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->SetBinContent(i+1, x);
    double ff_diff_eeAndff = 0, ff_diff_eeAndffSlope=0, ff_diff_slope = 0, ff_diff_intercept=0, ff_diff_stat=0;
    double ff_diff = 0, ff_diff_error = 0;
     
    int fittingBin = h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->FindBin(101);
    // these are needed for shape difference between data ee and MC ff ////
    if((i+1)<fittingBin){
      ff_diff_eeAndff = 0.1818*h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1);//fabs(eeMETFromFit[3] - ffMETFromFit[3]); // flat shape uncertainty below 100 GeV
      //fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_DoubleFake_MET_Reweighted->GetBinContent(i+1)); // this is now changed to get a flat shape uncertainty below 100 GeV, so we use the shape uncertainty of 100-110 flatly below 100 GeV
      ff_diff_error = sqrt(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1)*h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1)+ h_DoubleFake_MET_Reweighted->GetBinError(i+1)*h_DoubleFake_MET_Reweighted->GetBinError(i+1)); 
      ff_diff_stat = sqrt(h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1));
      /*if(ff_diff_eeAndff > ff_diff_error)*/ff_diff = ff_diff_eeAndff;
      //else ff_diff = ff_diff_error;
    }
    else{
      ff_diff_eeAndff = fabs(eeMETFromFit[i+1 - 17] - ffMETFromFit[i+1 - 17]); // taking shape difference from fit// fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_DoubleFake_MET_Reweighted->GetBinContent(i+1));
      //ff_diff_eeAndff = fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1)); 
      ff_diff_eeAndffSlope = fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1));
      
      ff_diff_slope = sqrt(h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinError(i+1));
      ff_diff_stat = sqrt(h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1));
      double ff_tot_error = sqrt(ff_diff_slope*ff_diff_slope+ff_diff_stat*ff_diff_stat);
      ff_diff_error = sqrt(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1)*h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1)+ff_tot_error*ff_tot_error);
      double ff_error = sqrt(statery*statery + sysery*sysery);
      if(ff_diff_eeAndff > ff_error)ff_diff = ff_diff_eeAndff;
      else ff_diff = ff_error;
    }////, this is needed when we take ff MC from const fit and error from const -  straight line fit*/
     
     
    cout << "For bin " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " diff : " << diff << endl;
     
     
    double stat2Dff = h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinError(i+1);
    double sys2Dff = ErrorPropDiEMPtVsNJetWeightedff->GetBinError(i+1);
    double err2Dff = sqrt(stat2Dff*stat2Dff + sys2Dff*sys2Dff);
    h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->SetBinError(i+1, err2Dff);
     
    cout << "++++++++++++++++++++++++++++++++++++++++++++ MET bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " +++++++++++++++++++++++++++++++++++" << endl;
    myfileText << "++++++++++++++++++++++++++++++++++++++++++++ MET bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " +++++++++++++++++++++++++++++++++++" << endl;
    myfileNJets << "++++++++++++++++++++++++++++++++++++++++++++ MET bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " +++++++++++++++++++++++++++++++++++" << endl;
    //cout << "ee E_{T}^{miss} after diempt and njets reweighting: " << h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) << " and uncertainty: " << h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->GetBinError(i+1) << endl; 
    cout << "ee E_{T}^{miss} after DiEMPt reweighting: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << " and uncertainty: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinError(i+1) << endl;
    //cout << "first histogram for ee E_{T}^{miss} : " << h_DoubleElectron_MET_Reweighted->GetBinContent(i+1) << " second histogram for ee E_{T}^{miss}: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    //cout << "ff E_{T}^{miss} after reweighting: " << h_DoubleFake_MET_Reweighted->GetBinContent(i+1) << " and uncertainty: " << h_DoubleFake_MET_Reweighted->GetBinError(i+1) << endl; 
    //cout << "Unreweighted ee E_{T}^{miss}: " << h_DoubleElectron_MET->GetBinContent(i+1) << " and uncertainty: " <<  h_DoubleElectron_MET->GetBinError(i+1) << endl;
    //cout << "Unreweighted ff E_{T}^{miss}: " << h_DoubleFake_MET->GetBinContent(i+1) << " and uncertainty: " <<  h_DoubleFake_MET->GetBinError(i+1) << endl;
    //cout << "fractional error from ee diEMPt: " << sqrt(syserx*syserx)/h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) << endl;
    //cout << "fractional error from ee NJets: " << sqrt((syserx - syserx2)*(syserx - syserx2))/h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) << endl;
    cout << "fractional error from ee diEMPt New: " << sqrt(syserx*syserx)/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    //cout << "total error from ee diEMPt New: " << sqrt(syserx*syserx) << endl;
    cout << "ee E_{T}^{miss} after DiEMPt reweighting: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << " and Njet diempt reweighting: " << h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(i+1) << endl;
    cout << "diff between them : " << diff << " and my diff : " << fabs(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(i+1) - h_DoubleElectron_MET_Reweighted->GetBinContent(i+1)) << endl;
    cout << "fractional error from ee NJets New Only Diff: " << diff/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    cout << "fractional error from ee NJets New Only DiffError: " << diff_Error/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    //cout << "total error from ee NJets New Only Diff: " << diff << endl;
      
    //cout << "fractional error from ee shapeDiff: " << sqrt(syserx3*syserx3)/h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1) << endl;
    //cout << "from ee: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << " and from Keith ff: " << h_DoubleFake_MET->GetBinContent(i+1) << endl;
    //cout << "ff_diff: " << ff_diff << " and ee E_{T}^{miss} etimates: " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    cout << "fractional error from ee shapeDiff by Keith: " << ff_diff/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    cout << "fractional error from ee shapeDiffConstAndSlope by Keith: " << ff_diff_slope/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    cout << "diff between constant and slope: " << ff_diff_slope << endl;
    cout << "difference between ee and ff(1): " << ff_diff_eeAndff << endl;
    cout << "error propagation on that difference(2): " << ff_diff_error << endl;
    cout << "1.96 times the error propagation(3): " << 1.96*ff_diff_error << endl;
    cout << "diff (1)-(2): " << fabs(ff_diff_error - ff_diff_eeAndff) << " and diff (1)-(3): " << fabs(1.96*ff_diff_error - ff_diff_eeAndff) << endl;
    
    
    
    if((i+1)<binInclude){
      myfileText << "difference between ee and ff:                                " << ff_diff_eeAndff << endl;
      myfileText << "fractional difference between ee and ff:                     " << ff_diff_eeAndff*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      myfileText << "error propagation on that difference:                        " << ff_diff_error << endl;
      myfileText << "fractional error propagation on that difference:             " << ff_diff_error*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
    }
    else{
      myfileText << "difference between ee and ff, estimated by const:            " << ff_diff_eeAndff << endl;
      myfileText << "fractional difference between ee and ff, estimated by const: " << ff_diff_eeAndff*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      myfileText << "difference between ee and ff, estimated by slope:            " << ff_diff_eeAndffSlope << endl;
      myfileText << "fractional difference between ee and ff, estimated by slope: " << ff_diff_eeAndffSlope*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      myfileText << "error propagation on that difference:                        " << ff_diff_error << endl;
      myfileText << "fractional error propagation on that difference:             " << ff_diff_error*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
      myfileErrorSignal << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileErrorSignal << "++++++++++++++++++++++++++++++++++++++++++++ MET bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " GeV +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileErrorSignal << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileErrorSignal << "N_gg, number of gg events from data:                                                                             " << h_DoublePhoton_MET->GetBinContent(i+1) << endl;
      myfileErrorSignal << "statistical error on number of gg events from data:                                                              " << h_DoublePhoton_MET->GetBinError(i+1) << endl;
      
      myfileErrorSignal << "                             *****                                             " << endl;
      
      myfileErrorSignal << "N_ee, number of ee events coming after diEMPt reweighting:                                                       " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
      
      myfileErrorSignal << "total error on that number:                                                                                      " << sqrt(staterx*staterx + syserx*syserx + diff*diff) << endl;
      myfileErrorSignal << "error contains stat error, diempt reweighting error and njet reweighting error  "                                 << endl;
      
      myfileErrorSignal << "                             *****                                             " << endl;
      
      myfileErrorSignal << "N_ff, number of ff events coming after diEMPt reweighting:                                                       " << h_DoubleFake_MET_Reweighted->GetBinContent(i+1) << endl;
      myfileErrorSignal << "total error on that number:                                                                                      " << sqrt(statery*statery + sysery*sysery) << endl;
      myfileErrorSignal << "error contains stat error and diempt reweighting error  " << endl;
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by diempt reweighting :                                                            " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_DoubleFake_MET_Reweighted->GetBinContent(i+1)) << endl;
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by diempt ratio, fraction of N_ee:                                                 " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_DoubleFake_MET_Reweighted->GetBinContent(i+1))*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
      
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "N_ff, estimated by constant fit to gg/ff ratio:                                                                  " << h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1) << endl;
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio:                                                    " << ff_diff_eeAndff << endl;
      MaxError.push_back(ff_diff_eeAndff);
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio, fraction of N_ee:                                  " << ff_diff_eeAndff*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
      
//       myfileErrorSignal << "                             *****                                             " << endl; 
//       myfileErrorSignal << "N_ff estimated by constant fit to gg/ff ratio, 1 sigma up:                                                       " << h_ff_FromKeithEstimate_WithConstantOneSigmaUp->GetBinContent(i+1) << endl;
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio, 1 sigma up:                                        " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaUp->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaUp->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio, 1 sigma up, fraction of N_ee:                      " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaUp->GetBinContent(i+1))*100/ h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
//       
//       
//       myfileErrorSignal << "                             *****                                             " << endl;
//       myfileErrorSignal << "N_ff estimated by constant fit to gg/ff ratio, 1 sigma down:                                                     " << h_ff_FromKeithEstimate_WithConstantOneSigmaDown->GetBinContent(i+1) << endl;
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio, 1 sigma down:                                      " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaDown->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaDown->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by constant fit to gg/ff ratio, 1 sigma down, fraction of N_ee:                    " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstantOneSigmaDown->GetBinContent(i+1))*100/ h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
      
      
      
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "N_ff estimated by straight line fit to gg/ff ratio:                                                              " << h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1) << endl;
      
      double ErrorForConstAndSlope = fabs(h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1));
      
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio:                                               " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1)) << endl;
      MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1)));
      myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, fraction of N_ee:                             " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1))*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
      
      
//       myfileErrorSignal << "                             *****                                             " << endl;
//       myfileErrorSignal << "N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma up:                                            " << h_ff_FromKeithEstimate_WithSlopeOneSigmaUp->GetBinContent(i+1) << endl;
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma up:                             " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaUp->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaUp->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma up, fraction of N_ee:           " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaUp->GetBinContent(i+1))*100/ h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
//       
//       
//       
//       myfileErrorSignal << "                             *****                                             " << endl;
//       myfileErrorSignal << "N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma down:                                          " << h_ff_FromKeithEstimate_WithSlopeOneSigmaDown->GetBinContent(i+1) << endl;
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma down:                           " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaDown->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaDown->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, slope 1 sigma down, fraction of N_ee:         " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithSlopeOneSigmaDown->GetBinContent(i+1))*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
//       
//       
//       
//       myfileErrorSignal << "                             *****                                             " << endl;
//       myfileErrorSignal << "N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma up:                                        " << h_ff_FromKeithEstimate_WithInterceptOneSigmaUp->GetBinContent(i+1) << endl;
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma up:                         " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaUp->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaUp->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma up, fraction of N_ee:       " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaUp->GetBinContent(i+1))*100/ h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
//       
//       
//       
//       
//       myfileErrorSignal << "                             *****                                             " << endl;
//       myfileErrorSignal << "N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma down:                                      " << h_ff_FromKeithEstimate_WithInterceptOneSigmaDown->GetBinContent(i+1) << endl;
//       
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma down:                       " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaDown->GetBinContent(i+1)) << endl;
//       MaxError.push_back(fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaDown->GetBinContent(i+1)));
//       myfileErrorSignal << "|N_ee - N_ff|, N_ff estimated by straight line fit to gg/ff ratio, intercept 1 sigma down, fraction of N_ee:     " << fabs(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithInterceptOneSigmaDown->GetBinContent(i+1))*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
      
      
      
      
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "(Delta N_ee + Delta N_ff):                                                                                       " << sqrt(staterx*staterx + syserx*syserx + diff*diff + h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)+h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)+ErrorForConstAndSlope*ErrorForConstAndSlope) << endl;
      
      MaxError.push_back(sqrt(staterx*staterx + syserx*syserx + diff*diff + h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)+h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)+ErrorForConstAndSlope*ErrorForConstAndSlope));
      myfileErrorSignal << "(Delta N_ee contains ee stat, diempt reweighting, njet reweighting from data)                                    " << endl;
      myfileErrorSignal << "(Delta N_ff contains ff stat error and diempt error from data, error from the difference in estimate from line and constant)      " << endl;
      
      myfileErrorSignal << "(Delta N_ee + Delta N_ff),fraction of N_ee:                                                                      " << sqrt(staterx*staterx + syserx*syserx + diff*diff + h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffStatError->GetBinError(i+1)+h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)*h_ff_FromKeithEstimate_WithffDiEMPtError->GetBinError(i+1)+ErrorForConstAndSlope*ErrorForConstAndSlope)*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%"<< endl;
      
      
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "Maximum error of them:                                                                                           " << *std::max_element(MaxError.begin(), MaxError.end()) << endl;
      myfileErrorSignal << "Maximum error of them in fraction of N_ee                                                                        " << *std::max_element(MaxError.begin(), MaxError.end())*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
      
      
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "                             *****                                             " << endl;
      myfileErrorSignal << "Difference between N_ff estimated by constant and by straight line fit to ratio, Delta N_Const_Slope:            " << fabs( h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1)) <<  endl;
      myfileErrorSignal << "Delta N_Const_Slope, fraction of N_ff estimated by constant fit to ratio:                                        " << fabs( h_ff_FromKeithEstimate_WithSlope->GetBinContent(i+1) - h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1))*100/h_ff_FromKeithEstimate_WithConstAndSlopeDiffError->GetBinContent(i+1) << "%" <<  endl;
      
      
      
      
      /////////////////////////////////////// Writing out the final systematics file ////////////////////////////////////////////////////
      myfileSystematics << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileSystematics << "++++++++++++++++++++++++++++++++++++++++++++ MET bin: " << h_DoubleFake_MET->GetXaxis()->GetBinLowEdge(i+1) << " GeV +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileSystematics << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      myfileSystematics << "N_gg, number of gg events from data:                                                                             " << h_DoublePhoton_MET->GetBinContent(i+1) << endl;
      myfileSystematics << "statistical error on number of gg events from data:                                                              " << h_DoublePhoton_MET->GetBinError(i+1) << endl;
      
      myfileSystematics << "                             *****                                             " << endl;
      
      myfileSystematics << "N_ee, number of ee events coming after diEMPt reweighting:                                                       " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
      
      myfileSystematics << "total error on that number:                                                                                      " << sqrt(staterx*staterx + syserx*syserx + diff*diff + ff_diff_eeAndff*ff_diff_eeAndff) << endl;
      myfileSystematics << "Error from diEMPt reweighting:                                                                                   " << sqrt(syserx*syserx)*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      myfileSystematics << "Error from NJet reweighting:                                                                                     " << sqrt(diff*diff)*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      myfileSystematics << "Error coming from fake samples:                                                                                  " << ff_diff_eeAndff*100/eeMETFromFit[i+1 - 17] << "%" << endl;
      
      myfileSystematics << "                             *****                                             " << endl;
      
      
      double metvalueup = h_Scaled_ElectronPhoton_MET_Up->GetBinContent(i+1);
      double metvaluedown = h_Scaled_ElectronPhoton_MET_Down->GetBinContent(i+1);
   
      double errorup   = fabs(metvalueup - h_Scaled_ElectronPhoton_MET->GetBinContent(i+1));
      double errordown= fabs(h_Scaled_ElectronPhoton_MET->GetBinContent(i+1) - metvaluedown); 
      
      double ewkStatError = h_Scaled_ElectronPhoton_MET->GetBinError(i+1);
    
      myfileSystematics << "EWK background :                                                                                                 " << h_Scaled_ElectronPhoton_MET->GetBinContent(i+1) << endl;
      myfileSystematics << "error from fake rate:                                                                                            " << sqrt((errorup+errordown)*(errorup+errordown))*100/h_Scaled_ElectronPhoton_MET->GetBinContent(i+1) << "%" << endl;
      
      myfileSystematics << "                             *****                                             " << endl;
      
      myfileSystematics << "Total Expected Background:                                                                                       " << h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) + h_Scaled_ElectronPhoton_MET->GetBinContent(i+1) << endl;
      
      myfileSystematics << "Total Uncertainty on Background:                                                                                 " << sqrt(staterx*staterx + syserx*syserx + diff*diff + ff_diff_eeAndff*ff_diff_eeAndff+(errorup+errordown)*(errorup+errordown)+ewkStatError*ewkStatError) << endl;
      
      
    }
    
    //cout << "Upto here" << endl;
    double erAll = 0;
    if((i+1)<binInclude){
      erAll = ff_diff_eeAndff;
    }
    else{
      double max = *std::max_element(MaxError.begin(), MaxError.end());
      erAll = /*ff_diff;*/ff_diff_eeAndff;//max;
    }
    double erx_Extended = sqrt(staterx*staterx+syserx*syserx+diff*diff+erAll*erAll); 
    h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->SetBinError(i+1, erx_Extended);
    
    myfileNJets << "error from ee NJets DiEMpt reweighting - ee diEMpt reweighting:            " << diff << endl;
    myfileNJets << "fractional error from ee NJets DiEMpt reweighting - ee diEMpt reweighting: " << diff*100/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << "%" << endl;
      
    //cout << "fractional error from ee shapeDiffIntercept by Keith: " << ff_diff_intercept/h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1) << endl;
    //cout << "diff Intercept: " << ff_diff_intercept << endl;
    h_DoubleElectron_NJetDiffError->SetBinContent(i+1, h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1));
    h_DoubleElectron_NJetDiffError->SetBinError(i+1, diff);
      
    h_DoubleElectron_NJetErrorProp->SetBinContent(i+1, h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1));
    h_DoubleElectron_NJetErrorProp->SetBinError(i+1, diff_Error);
      
    h_DoubleElectron_ffDiffError->SetBinContent(i+1, h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1));
    h_DoubleElectron_ffDiffError->SetBinError(i+1, ff_diff_eeAndff);
      
    h_DoubleElectron_ffErrorProp->SetBinContent(i+1, h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1));
    h_DoubleElectron_ffErrorProp->SetBinError(i+1, ff_diff_error);
    
     
    if((i+1)>=binInclude){
      totalMETEE += h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(i+1);
      totalMETEENew += h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->GetBinContent(i+1);
      errFraceeShapeDiffKeith += (ff_diff*ff_diff);
      errFraceeShapeDiffKeithSlope += (ff_diff_slope*ff_diff_slope);
      errFraceeShapeDiffKeithIntercept += (ff_diff_intercept*ff_diff_intercept);
       
      errFraceeFromDiEMPt += syserx*syserx;
      errFraceeFromNJets += (syserx - syserx2)*(syserx - syserx2);
      errFraceeFromNJetsNew += (diff*diff);
      errFraceeShapeDiff += syserx3*syserx3;
      totalMETFF += h_DoubleFake_MET_Reweighted->GetBinContent(i+1);
      errFracffFromDiEMPt += sysery*sysery;
      errFracffFromNJets += (sysery - sysery2)*(sysery - sysery2);
    }
  } // loop over each bin ends
  
  TFile *EEFFFile = new TFile(OutputFolder+"/EEAndFFExpFit.root","RECREATE");
  EEFFFile->cd();
  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Write("h_DoubleElectron_MET_Reweighted_ExpFit");
  h_DoubleFake_MET_Reweighted->Write("h_DoubleFake_MET_Reweighted_ExpFit");
  h_DoublePhoton_MET->Write("h_DoublePhoton_MET");
  h_DoubleElectron_MET_Reweighted->Write("h_DoubleElectron_MET_Reweighted");
  h_DoubleFake_MET_Reweighted_OnlyDiEMPt->Write("h_DoubleFake_MET_Reweighted_OnlyDiEMPt");
  h_DoubleElectron_MET->Write("h_DoubleElectron_MET");
  h_DoubleFake_MET->Write("h_DoubleFake_MET");
  
  
  
  TFile *histError = new TFile("DifferenceErrorValues.root","RECREATE");
  histError->cd();
  h_DoubleElectron_NJetDiffError->Write();
  h_DoubleElectron_NJetErrorProp->Write();
  
  h_DoubleElectron_ffDiffError->Write();  
  h_DoubleElectron_ffErrorProp->Write();
  
  delete histError;
   
  cout << "==============================================================================" << endl;
  cout << "EE error frac from diempt Old: " << sqrt(errFraceeFromDiEMPt)/totalMETEE << endl;
  cout << "EE error frac from njets Old: " << sqrt(errFraceeFromNJets)/totalMETEE << endl;
  cout << "EE error frac from shape Old: " << sqrt(errFraceeShapeDiff)/totalMETEE << endl;
   
   
  cout << "EE error frac from diempt New: " << sqrt(errFraceeFromDiEMPt)/totalMETEENew << endl;
  cout << "EE error frac from njets New: " << sqrt(errFraceeFromNJetsNew)/totalMETEENew << endl;
  cout << "EE error frac from shape New: " << sqrt(errFraceeShapeDiffKeith)/totalMETEENew << endl;
  cout << "EE error frac from shape slope New: " << sqrt(errFraceeShapeDiffKeithSlope)/totalMETEENew << endl;
  cout << "EE error frac from shape intercept New: " << sqrt(errFraceeShapeDiffKeithIntercept)/totalMETEENew << endl;
   
   
   
  cout << "EE E_{T}^{miss} in signal region: " << totalMETEE << " and error (without shape): " << sqrt(errFraceeFromDiEMPt+errFraceeFromNJets) << endl;
  cout << "EE E_{T}^{miss} in signal region Only DiEMPt: " << totalMETEENew << " and error (without shape): " << sqrt(errFraceeFromDiEMPt+errFraceeFromNJetsNew) << endl;
  cout << "EE E_{T}^{miss} in signal region: " << totalMETEE << " and error (with shape): " << sqrt(errFraceeFromDiEMPt+errFraceeFromNJets+errFraceeShapeDiff) << endl;
  cout << "EE E_{T}^{miss} in signal region Only DiEMPt: " << totalMETEENew << " and error (with shape): " << sqrt(errFraceeFromDiEMPt+errFraceeFromNJetsNew+errFraceeShapeDiffKeith) << endl;
   
   
   
  cout << "FF error frac from diempt: " << sqrt(errFracffFromDiEMPt)/totalMETFF << endl;
  cout << "FF error frac from njets: " << sqrt(errFracffFromNJets)/totalMETFF << endl;
  cout << "Weighted FF E_{T}^{miss} in signal region: " << totalMETFF << " and error: " <<  sqrt(errFracffFromDiEMPt + errFracffFromNJets) << endl;
     
   
  for(int i=0; i < h_DoubleElectron_NJets_Reweighted->GetNbinsX();++i){
     
    double staterx = h_DoubleElectron_NJets_Reweighted->GetBinError(i+1);
    double syserx  = ErrorPropDiEMPtWeightedNJetsee->GetBinError(i+1);
     
    double erx = sqrt(staterx*staterx+syserx*syserx);
    h_DoubleElectron_NJets_Reweighted->SetBinError(i+1, erx);
     
     
    double statery = h_DoubleFake_NJets_Reweighted->GetBinError(i+1);
    double sysery  = ErrorPropDiEMPtWeightedNJetsff->GetBinError(i+1);
     
    double ery = sqrt(statery*statery+sysery*sysery);
    h_DoubleFake_NJets_Reweighted->SetBinError(i+1, ery);
     
  }
   
   
  double njetsEE = h_DoubleElectron_NJets_Reweighted->Integral(0, h_DoubleElectron_NJets_Reweighted->GetNbinsX()+1);
  h_DoubleElectron_NJets_Reweighted->Scale(1.0/njetsEE);
   
  double njetsFF = h_DoubleFake_NJets_Reweighted->Integral(0, h_DoubleFake_NJets_Reweighted->GetNbinsX()+1);
  h_DoubleFake_NJets_Reweighted->Scale(1.0/njetsFF);
   
  double njetsGG = h_DoublePhoton_NJets->Integral(0, h_DoublePhoton_NJets->GetNbinsX()+1);
  h_DoublePhoton_NJets->Scale(1.0/njetsGG);
   
   
   
  std::string strpt = std::to_string(pt);
  std::string strfrac = std::to_string(frac);
   
   
  ///////////////////// Do the bin size normalization only after all the other calculation, only for Showing results ////////////////////////////
   
  h_DoubleElectron_MET_Reweighted_Normalized->Scale(1.0, "width");
  h_DoubleFake_MET_Reweighted_Normalized->Scale(1.0, "width");
  h_DoublePhoton_MET_Normalized->Scale(1.0, "width");
   
  h_DoublePhoton_MET->Scale(1.0, "width");
  h_DoublePhoton_MET_Upto100->Scale(1.0, "width");
  h_DoublePhoton_MET_Normalized->Scale(1.0, "width");
   
  h_DoubleElectron_MET->Scale(1.0, "width");
  h_DoubleElectron_MET_Reweighted->Scale(1.0, "width");
   
  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Scale(1.0, "width");
  h_DoubleElectron_MET_ReweightedDiEMPtNJets->Scale(1.0, "width");
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->Scale(1.0, "width");
   
  h_DoubleFake_MET->Scale(1.0, "width");
   
  h_DoubleFake_MET_Reweighted->Scale(1.0, "width");
  h_DoubleFake_MET_Reweighted_OnlyDiEMPt->Scale(1.0, "width");
  h_DoubleFake_MET_ReweightedDiEMPtNJets->Scale(1.0, "width");
  h_DoubleFakeShowershape_MET->Scale(1.0, "width");
   
  h_DoubleFakeShowershape_MET_Reweighted->Scale(1.0, "width");
  h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->Scale(1.0, "width");
   
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Scale(1.0, "width");
  h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->Scale(1.0, "width");
   
  ErrorPropDiEMPteeMET->Scale(1.0, "width");
  ErrorPropDiEMPtffMET->Scale(1.0, "width");
  ErrorPropDiEMPtffshowershapeMET->Scale(1.0, "width");
  ErrorPropDiEMPtNJetseeMET->Scale(1.0, "width");
  ErrorPropDiEMPtNJetsffMET->Scale(1.0, "width");
  ErrorPropDiEMPtNJetsffshowershapeMET->Scale(1.0, "width");
  ErrorPropDiEMPtVsNJetWeightedee->Scale(1.0, "width");
  ErrorPropDiEMPtVsNJetWeightedff->Scale(1.0, "width");
   
   
  h_DoubleElectron_NJets_Reweighted->Scale(1.0, "width");
  h_DoubleFake_NJets_Reweighted->Scale(1.0, "width");
  h_DoublePhoton_NJets->Scale(1.0, "width");
   
   
  /////////////// Plotting the histograms with bin normalized /////////////////////////
   
   
   
  Histofile3->cd();
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_AlsoShapeDiff->Write();
  h_DoubleElectron_MET_ReweightedDiEMPtNJets->Write();
  h_DoubleElectron_MET_Reweighted_OnlyDiEMPt->Write();
   
   
  vector<Color_t>color;
  color.push_back(2);
  color.push_back(4);
   
  vector<TString>LegName;
  LegName.push_back("ff");
  LegName.push_back("ee");
   
  vector<TH1F*>VecTH1;
  VecTH1.push_back(h_DoubleFake_MET);
  VecTH1.push_back(h_DoubleElectron_MET);
   
  if(!data){
     
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ff_MET_mc_Logy"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup, 0.0, pow(10, 4), OutputFolder+"/ee_ff_MET_mc_"+strpt, 0, 0, false, false);
  }
  else{
     
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ff_MET_data_withoutReweighting_"+strpt, 0, 0, false, false);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ff_MET_data_withoutReweighting_Logy"+strpt, 0, 0, false, true);
  }
   
   
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET);
  VecTH1Check.push_back(h_DoubleFake_MET);
   
   
   
  LegName2.clear();
  LegName2.push_back("ee");
  if(analysisFake)LegName2.push_back("ff");
  else LegName2.push_back("loose ff");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
    
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ee_unreweighted_ff_unreweighted_MET_ratio_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ee_unreweighted_ff_unreweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ee_unreweighted_ff_unreweighted_MET_ratio_LongX_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ee_unreweighted_ff_unreweighted_MET_ratio_LongX_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
  VecTH1Check.push_back(h_DoubleFake_MET);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ee");
  LegName2.push_back("ff");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
  
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_ratio_LowX_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_ratio_LowX_Logy_", hRatioTwo, 1, 1, true, true);
    
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_ratio_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  cout  << "++++++++++++++++++++++++++Weird+++++++++++++++++++++++++" << endl;
  cout << "ff 90<MET<100, no shape subtraction: " << h_DoubleFake_MET_Reweighted_OnlyDiEMPt->GetBinContent(19) << endl;
  cout << "ff 90<MET<100, after shape subtraction: " << h_DoubleFake_MET_Reweighted->GetBinContent(19) << endl;
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
  VecTH1Check.push_back(h_DoubleElectron_MET);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ee");
  LegName2.push_back("ee");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("#frac{reweighted ee}{ee}");
    
  
  DrawHistsRatioLowerLegend(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ee_unreweighted_ee_reweighted_MET_ratio_LowX_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ee_unreweighted_ee_reweighted_MET_ratio_LowX_Logy_", hRatioTwo, 1, 1, true, true);
    
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ee_unreweighted_ee_reweighted_MET_ratio_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ee_unreweighted_ee_reweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleFake_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFake_MET);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ff");
  LegName2.push_back("ff");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("#frac{reweighted ff}{ff}");
    
  
  DrawHistsRatioLowerLegend(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ff_unreweighted_ff_reweighted_MET_ratio_LowX_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1Check, LegName2, color2, xlow, 100,0.0012, 1000, OutputFolder+"/ff_unreweighted_ff_reweighted_MET_ratio_LowX_Logy_", hRatioTwo, 1, 1, true, true);
    
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ff_unreweighted_ff_reweighted_MET_ratio_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.0012, 1000, OutputFolder+"/ff_unreweighted_ff_reweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
  
  color2.clear();
  color2.push_back(4);
  color2.push_back(2);
   
  VecTH1Check.clear();
  VecTH1Check.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1Check.push_back(h_DoubleFake_MET);
   
   
   
  LegName2.clear();
  LegName2.push_back("reweighted ee (no shape subtraction)");
  LegName2.push_back("ff");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
  
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.2, 1000, OutputFolder+"/ee_reweighted_NoShapeSubtraction_ff_unreweighted_MET_ratio_LowX_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 100,0.2, 1000, OutputFolder+"/ee_reweighted_NoShapeSubtraction_ff_unreweighted_MET_ratio_LowX_Logy_", hRatioTwo, 1, 1, true, true);
    
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.2, 1000, OutputFolder+"/ee_reweighted_NoShapeSubtraction_ff_unreweighted_MET_ratio_", hRatioTwo, 1, 1, true, false);
  DrawHistsRatio(VecTH1Check, LegName2, color2, xlow, 300,0.2, 1000, OutputFolder+"/ee_reweighted_NoShapeSubtraction_ff_unreweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_NJets);
  VecTH1.push_back(h_DoubleElectron_NJets_Reweighted);
  VecTH1.push_back(h_DoubleFake_NJets_Reweighted);
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("ee");
  LegName.push_back("ff");
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  TH1F *hRatioJet1 = (TH1F*)h_DoubleElectron_NJets_Reweighted->Clone("hRatioJet1");
  hRatioJet1->Reset();
  hRatioJet1->SetTitle("");
  hRatioJet1->GetXaxis()->SetTitle("nJets");
  hRatioJet1->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioJet2 = (TH1F*)h_DoubleElectron_NJets_Reweighted->Clone("hRatioJet2");
  hRatioJet2->Reset();
  hRatioJet2->SetTitle("");
  hRatioJet2->GetXaxis()->SetTitle("nJets");
  hRatioJet2->GetYaxis()->SetTitle("#gamma#gamma/ff");
  //hRatio4->Sumw2();
  DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ff_photon_ee_data_ratio_RunD_DiEMPtReweightedNJets"+strpt, hRatioJet1, hRatioJet2, 1, 1, true, false);
  DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ff_photon_ee_data_ratio_RunD_DiEMPtReweightedNJets_Logy"+strpt, hRatioJet1, hRatioJet2, 1, 1, true, true);
   
   
   
  color.clear();
  color.push_back(2);
  color.push_back(4);
   
  LegName.clear();
  LegName.push_back("ff");
  LegName.push_back("ee");
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleFakeShowershape_MET);
  VecTH1.push_back(h_DoubleElectron_MET);
   
  if(!data){
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ffshowershape_MET_mc_Logy"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ffshowershape_MET_mc_"+strpt, 0, 0, false, false);
  }
  else{
     
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ffshowershape_MET_data_withoutReweighting_"+strpt, 0, 0, false, false);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, pow(10, 4), OutputFolder+"/ee_ffshowershape_MET_data_withoutReweighting_Logy"+strpt, 0, 0, false, true);
  }
     
     
     
  ///// Simple distributions //////  
     
  color.clear();
  color.push_back(4);
   
  VecTH1.clear();
  VecTH1.push_back(h_LeadPhoton_Pt);
   
  LegName.clear();
  LegName.push_back("Lead #gamma");
   
  DrawHists(VecTH1, LegName, color, 0, 400, 0.0, 10000, simpleOutputFolder+"/DoublePhoton_LeadPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 400, 0.1, 10000, simpleOutputFolder+"/DoublePhoton_LeadPt_data_Logy"+strpt, 0, 0, false, true);
   
  VecTH1.clear();
  VecTH1.push_back(h_TrailPhoton_Pt);
   
  LegName.clear();
  LegName.push_back("Trail #gamma");
   
  DrawHists(VecTH1, LegName, color, 0, 400, 0.0, 10000, simpleOutputFolder+"/DoublePhoton_TrailPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 400, 0.1, 10000, simpleOutputFolder+"/DoublePhoton_TrailPt_data_Logy"+strpt, 0, 0, false, true);
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_LeadFake_Pt);
   
  LegName.clear();
  LegName.push_back("Lead fake");
   
  DrawHists(VecTH1, LegName, color, 0, 200, 0.0, 10000, simpleOutputFolder+"/DoubleFake_LeadPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 200, 0.1, 10000, simpleOutputFolder+"/DoubleFake_LeadPt_data_Logy"+strpt, 0, 0, false, true);
   
  VecTH1.clear();
  VecTH1.push_back(h_TrailFake_Pt);
   
  LegName.clear();
  LegName.push_back("Trail fake");
   
  DrawHists(VecTH1, LegName, color, 0, 200, 0.0, 10000, simpleOutputFolder+"/DoubleFake_TrailPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 200, 0.1, 10000, simpleOutputFolder+"/DoubleFake_TrailPt_data_Logy"+strpt, 0, 0, false, true);
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_LeadElectron_Pt);
   
  LegName.clear();
  LegName.push_back("Lead e");
   
  DrawHists(VecTH1, LegName, color, 0, 400, 0, 10000, simpleOutputFolder+"/DoubleElectron_LeadPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 400, 0.1, 10000, simpleOutputFolder+"/DoubleElectron_LeadPt_data_Logy"+strpt, 0, 0, false, true);
   
  VecTH1.clear();
  VecTH1.push_back(h_TrailElectron_Pt);
   
  LegName.clear();
  LegName.push_back("Trail e");
   
  DrawHists(VecTH1, LegName, color, 0, 400, 0, 10000, simpleOutputFolder+"/DoubleElectron_TrailPt_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 400, 0.1, 10000, simpleOutputFolder+"/DoubleElectron_TrailPt_data_Logy"+strpt, 0, 0, false, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_InvMass);
   
  LegName.clear();
  LegName.push_back("ee InvMass");
   
  DrawHists(VecTH1, LegName, color, 20, 200, 0, 1000, simpleOutputFolder+"/DoubleElectron_InvMass_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 20, 200, 0.1, 1000, simpleOutputFolder+"/DoubleElectron_InvMass_data_Logy"+strpt, 0, 0, false, true);
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_ElectronPhoton_InvMass);
   
  LegName.clear();
  LegName.push_back("e#gamma InvMass");
   
  DrawHists(VecTH1, LegName, color, 20, 200, 0.0, 200, simpleOutputFolder+"/ElectronPhoton_InvMass_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 20, 200, 0.1, 200, simpleOutputFolder+"/ElectronPhoton_InvMass_data_Logy"+strpt, 0, 0, false, true);
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_ChargedHadIso);
   
  LegName.clear();
  LegName.push_back("ch Had Iso");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/ChargedHadIso_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/ChargedHadiso_data_Logy"+strpt, 0, 0, false, true);
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_ChargedHadIso_WithoutShowerCut);
   
  LegName.clear();
  LegName.push_back("ch Had Iso");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/ChargedHadIso_WithoutShowerCut_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/ChargedHadiso_WithoutShowerCut_data_Logy"+strpt, 0, 0, false, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_PhotonHadIso_Fake);
   
  LegName.clear();
  LegName.push_back("Ph Had Iso for Fake");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/PhotonHadIso_Fake_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/PhotonHadiso_Fake_data_Logy"+strpt, 0, 0, false, true);
   
  VecTH1.clear();
  VecTH1.push_back(h_PhotonHadIso_Photon);
   
  LegName.clear();
  LegName.push_back("Ph Had Iso for Photon");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/PhotonHadIso_Photon_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/PhotonHadiso_Photon_data_Logy"+strpt, 0, 0, false, true);
   
   
   
   
   
  VecTH1.clear();
  VecTH1.push_back(h_NeutralHadIso_Fake);
   
  LegName.clear();
  LegName.push_back("Neu Had Iso for Fake");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/NeutralHadIso_Fake_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/NeutralHadiso_Fake_data_Logy"+strpt, 0, 0, false, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_NeutralHadIso_Photon);
   
  LegName.clear();
  LegName.push_back("Neu Had Iso for Photon");
   
  DrawHists(VecTH1, LegName, color, 0, 40, 0, 200, simpleOutputFolder+"/NeutralHadIso_Photon_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 40, 0.1, 200, simpleOutputFolder+"/NeutralHadiso_Photon_data_Logy"+strpt, 0, 0, false, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_SigmaIetaIeta_Fake);
   
  LegName.clear();
  LegName.push_back("#sigma_{i#eta i#eta} for Fake");
   
  DrawHists(VecTH1, LegName, color, 0, 0.02, 0, 200, simpleOutputFolder+"/SigmaIetaIeta_Fake_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 0.02, 0.1, 200, simpleOutputFolder+"/SigmaIetaIeta_Fake_data_Logy"+strpt, 0, 0, false, true);
   
  VecTH1.clear();
  VecTH1.push_back(h_SigmaIetaIeta_Photon);
   
  LegName.clear();
  LegName.push_back("#sigma_{i#eta i#eta} for Photon");
   
  DrawHists(VecTH1, LegName, color, 0, 0.02, 0, 200, simpleOutputFolder+"/SigmaIetaIeta_Photon_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 0.02, 0.1, 200, simpleOutputFolder+"/SigmaIetaIeta_Photon_data_Logy"+strpt, 0, 0, false, true);
   
   
  VecTH1.clear();
  VecTH1.push_back(h_PhotonTrigger);
   
  LegName.clear();
  LegName.push_back("Triggers");
   
  DrawHists(VecTH1, LegName, color, 0, 25, 0, 200, simpleOutputFolder+"/PhotonTriggerSelected_data_"+strpt, 0, 0, false, false);
  DrawHists(VecTH1, LegName, color, 0, 25, 0.1, 2000, simpleOutputFolder+"/PhotonTriggerSelected_data_Logy"+strpt, 0, 0, false, true);
   
   
 
  //// Plotting E_{T}^{miss} distributions ////
   
   
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_Mix_MET);
  VecTH1.push_back(h_DoublePhoton_MET);
   
  LegName.clear();
  LegName.push_back("p#times ee+ (1-p)#times ff");
  LegName.push_back("#gamma#gamma");
  string texword = "purity (p) = "+strfrac;
  const char *texfinal = texword.c_str();
  TLatex *texwrite = new TLatex(0.55,0.75,texfinal);
  texwrite->SetNDC();
  texwrite->SetTextAlign(31);
  texwrite->SetTextFont(42);
  texwrite->SetTextSize(0.03);
  texwrite->SetLineWidth(2);
   
  if(!data){
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_mc_Logy_"+strpt+"_Purity_"+strfrac, hRatio, 1, 1, true, true);
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_mc_"+strpt+"_Purity_"+strfrac, hRatio, 1, 1, true, false);
   
    DrawHistsRatioWithSysErr(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_mc_Logy_"+strpt+"_Purity_"+strfrac, hRatio, h_Mix_MET_SysErr, hRatioSys, 1, 1, true, true, texwrite);
    DrawHistsRatioWithSysErr(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_mc_"+strpt+"_Purity_"+strfrac, hRatio, h_Mix_MET_SysErr, hRatioSys, 1, 1, true, false, texwrite);
  }
  else{
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_data_metfilter_Logy_"+strpt+"_Purity_"+strfrac, hRatio, 1, 1, true, true);
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_data_metfilter_"+strpt+"_Purity_"+strfrac, hRatio, 1, 1, true, false);
   
    DrawHistsRatioWithSysErr(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_data_metfilter_Logy_"+strpt+"_Purity_"+strfrac, hRatio, h_Mix_MET_SysErr, hRatioSys, 1, 1, true, true, texwrite);
    DrawHistsRatioWithSysErr(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/QCD_ee_ff_MET_data_metfilter_"+strpt+"_Purity_"+strfrac, hRatio, h_Mix_MET_SysErr, hRatioSys, 1, 1, true, false, texwrite);
  }
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted_OnlyDiEMPt);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  TH1F *hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatio3L = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("hRatio3L");
  hRatio3L->Reset();
  hRatio3L->SetTitle("");
  hRatio3L->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3L->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
  if(!data){
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_mc_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_mc_"+strpt, 0, 0, false, false);
  }
  else{
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_OnlyDiEMPtReweighting_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_OnlyDiEMPtReweighting_"+strpt, 0, 0, false, false);
     
     
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup, 0.001, 100, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3, hRatio3L, 1, 1, true, false);
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup, 0.001, 100, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3, hRatio3L, 1, 1, true, true);
  }
  
  
  
  
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
  VecTH1.push_back(h_DoubleFake_MET);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("ff");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  hRatio3L = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("hRatio3L");
  hRatio3L->Reset();
  hRatio3L->SetTitle("");
  hRatio3L->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3L->GetYaxis()->SetTitle("#gamma#gamma/ff");
    
    
  DrawHistsRatioTwo(VecTH1, LegName, color, xlow, 100, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_data_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3, hRatio3L, 1, 1, true, false);
  DrawHistsRatioTwo(VecTH1, LegName, color, xlow, 100, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_unreweighted_MET_data_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3, hRatio3L, 1, 1, true, true);
   
   
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   
  
  DrawHists(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_Logy_"+strpt, 0, 0, false, true);
  DrawHists(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_"+strpt, 0, 0, false, false);
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  
  DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_LowX_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1, LegName, color, xlow, 100, 0.002, 1000, OutputFolder+"/ee_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_LowX_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  
  
  
  
  color.clear();
  color.push_back(kBlack);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted_OnlyDiEMPt);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ff");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   
  
  DrawHists(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_Logy_"+strpt, 0, 0, false, true);
  DrawHists(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_"+strpt, 0, 0, false, false);
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  
  DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_LowX_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1, LegName, color, xlow, 100, 0.002, 1000, OutputFolder+"/ff_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_LowX_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  
  
  
   
   
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted_OnlyDiEMPt);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted);
   
   
   
  LegName.clear();
  LegName.push_back("reweighted ee");
  if(analysisFake)LegName.push_back("reweighted ff");
  else LegName.push_back("reweighted loose ff");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("ee/ff");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.0012, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatioLowerLegend(VecTH1, LegName, color, xlow, 100, 0.0012, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.0012, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_AllX_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.0012, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_AllX_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  DrawHistsRatio(VecTH1, LegName, color, 100, xup, 0.0012, 10, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_highMET_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, 100, xup, 0.0012, 10, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_ratio_highMET_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  
  
  
  
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted_OnlyDiEMPt);
   
   
   
  LegName.clear();
  LegName.push_back("reweighted ee (no shape subtraction)");
  if(analysisFake)LegName.push_back("reweighted ff (no shape subtraction)");
  else LegName.push_back("reweighted loose ff (no shape subtraction)");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("ee/ff");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction__ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction__ratio_highX_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.001, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction__ratio_highX_Logy_"+strpt, hRatio3, 1, 1, true, true);
  
  DrawHistsRatio(VecTH1, LegName, color, 100, xup, 0.001, 10, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction__ratio_highMET_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, 100, xup, 0.001, 10, OutputFolder+"/ee_reweighted_ff_reweighted_MET_OnlyDiEMPtReweighting_NoShapeSubtraction__ratio_highMET_Logy_"+strpt, hRatio3, 1, 1, true, true);
    
    
    
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted);
   
  LegName.clear();
  LegName.push_back("reweighted diempt*njet ee");
  LegName.push_back("reweighted diempt ee");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("ee/ee");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_ee_reweighteddiempt_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_ee_reweighteddiempt_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
  /// comparison of ee with gammagamma
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET_Upto100);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted diempt*njets ee");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_photonphoton_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_photonphoton_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET_Upto100);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted);
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted diempt ee");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiempt_photonphoton_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiempt_photonphoton_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
  // from 2D reweighting
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio);
   
  LegName.clear();
  LegName.push_back("reweighted diempt*njet ee");
  LegName.push_back("reweighted diempt njet from 2D ee");
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("ee(1)/ee(2)");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_ee_reweighted2D_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets_ee_reweighted2D_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
   
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted);
   
   
  LegName.clear();
  LegName.push_back("ee, reweighted by njet in bins of Di-EM p_{T}");
  LegName.push_back("ee, reweighted by Di-EM p_{T}");
   
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#frac{ee(1)}{ee(2)}");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.005, 1000, OutputFolder+"/ee_reweighteddiemptnjets2D_ee_reweighteddiempt_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.005, 1000, OutputFolder+"/ee_reweighteddiemptnjets2D_ee_reweighteddiempt_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET_Upto100);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted diempt njet from 2D ee");
   
   
   
  hRatio3 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Clone("hRatio3");
  hRatio3->Reset();
  hRatio3->SetTitle("");
  hRatio3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
    
    
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets2D_photonphoton_MET_ratio_"+strpt, hRatio3, 1, 1, true, false);
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighteddiemptnjets2D_photonphoton_MET_ratio_Logy_"+strpt, hRatio3, 1, 1, true, true);
   
   
  // again 1D reweighting
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleFake_MET_ReweightedDiEMPtNJets);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  TH1F *hRatioNJets3 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioNJets3");
  hRatioNJets3->Reset();
  hRatioNJets3->SetTitle("");
  hRatioNJets3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioNJets3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatioNJets3L = (TH1F*)h_DoubleFake_MET_ReweightedDiEMPtNJets->Clone("hRatioNJets3L");
  hRatioNJets3L->Reset();
  hRatioNJets3L->SetTitle("");
  hRatioNJets3L->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioNJets3L->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
  if(data){
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_DiEMPtNJetsReweighting_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup, 1, 200, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_DiEMPtNJetsReweighting_"+strpt, 0, 0, false, false);
     
     
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_DiEMPtNJetsReweighting_ratio_"+strpt, hRatioNJets3, hRatioNJets3L, 1, 1, true, false);
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ff_reweighted_MET_data_DiEMPtNJetsReweighting_ratio_Logy_"+strpt, hRatioNJets3, hRatioNJets3L, 1, 1, true, true);
  }
   
   
   
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted);
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  hRatioNJets3 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioNJets3");
  hRatioNJets3->Reset();
  hRatioNJets3->SetTitle("");
  hRatioNJets3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioNJets3->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  hRatioNJets3L = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("hRatioNJets3L");
  hRatioNJets3L->Reset();
  hRatioNJets3L->SetTitle("");
  hRatioNJets3L->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioNJets3L->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
  if(data){
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_diemptnjetsreweighted_ff_diemptreweighted_MET_data_ratio_"+strpt, hRatioNJets3, hRatioNJets3L, 1, 1, true, false);
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_diemptnjetsreweighted_ff_diemptreweighted_MET_data_ratio_Logy_"+strpt, hRatioNJets3, hRatioNJets3L, 1, 1, true, true);
  }
   
   
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleFake_MET_Reweighted);
   
   
  LegName.clear();
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  hRatioNJets3 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioNJets3");
  hRatioNJets3->Reset();
  hRatioNJets3->SetTitle("");
  hRatioNJets3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioNJets3->GetYaxis()->SetTitle("ee/ff");
   
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_diemptnjetsreweighted_ff_diemptreweighted_MET_ratio_Logy_", hRatioNJets3, 1, 1, true, true);
   
 
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_Reweighted);
  VecTH1.push_back(h_DoubleFakeShowershape_MET_Reweighted);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  TH1F *hRatio3W = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3W");
  hRatio3W->Reset();
  hRatio3W->SetTitle("");
  hRatio3W->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3W->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  TH1F *hRatio3W2 = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("hRatio3W2");
  hRatio3W2->Reset();
  hRatio3W2->SetTitle("");
  hRatio3W2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3W2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
  if(!data){
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_mc_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_mc_"+strpt, 0, 0, false, false);
  }
  else{
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_OnlyDiEMPtReweighting_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_OnlyDiEMPtReweighting_"+strpt, 0, 0, false, false);
     
     
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3W, 1, 1, true, false);
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3W, 1, 1, true, true);
     
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_ratio_OnlyDiEMPtReweighting_ratio_"+strpt, hRatio3W,hRatio3W2, 1, 1, true, false);
    DrawHistsRatioTwo(VecTH1, LegName, color,  xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_ratio_OnlyDiEMPtReweighting_ratio_Logy_"+strpt, hRatio3W, hRatio3W2, 1, 1, true, true);
  }
   
   
   
  color.clear();
  color.push_back(kBlack);
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoublePhoton_MET);
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets);
   
   
   
  LegName.clear();
  LegName.push_back("#gamma#gamma");
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  hRatio3W = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatio3W");
  hRatio3W->Reset();
  hRatio3W->SetTitle("");
  hRatio3W->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3W->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
  hRatio3W2 = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatio3W2");
  hRatio3W2->Reset();
  hRatio3W2->SetTitle("");
  hRatio3W2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatio3W2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
  if(!data){
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_mc_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_mc_"+strpt, 0, 0, false, false);
  }
  else{
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_diemptnjetsreweighting_Logy_"+strpt, 0, 0, false, true);
    DrawHists(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_diemptnjetsreweighting_"+strpt, 0, 0, false, false);
     
     
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_diemptnjetsreweighting_ratio_"+strpt, hRatio3W, 1, 1, true, false);
    DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_diemptnjetsreweighting_ratio_Logy_"+strpt, hRatio3W, 1, 1, true, true);
     
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_ratio_diemptnjetsreweighting_ratio_"+strpt, hRatio3W,hRatio3W2, 1, 1, true, false);
    DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/ee_reweighted_ffshowershape_reweighted_MET_data_ratio_diemptnjetsreweighting_ratio_Logy_"+strpt, hRatio3W, hRatio3W2, 1, 1, true, true);
  }
   
   
   
  color.clear();
  color.push_back(4);
  color.push_back(2);
   
  VecTH1.clear();
  VecTH1.push_back(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  VecTH1.push_back(h_DoubleFake_MET_ReweightedDiEMPtNJets);
   
   
   
  LegName.clear();
  LegName.push_back("reweighted ee");
  LegName.push_back("reweighted ff");
   
  hRatioTwo = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("hRatioTwo");
  hRatioTwo->Reset();
  hRatioTwo->SetTitle("");
  hRatioTwo->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
  hRatioTwo->GetYaxis()->SetTitle("ee/ff");
    
     
  DrawHistsRatio(VecTH1, LegName, color, xlow, xup,0.1, 1000, OutputFolder+"/diemptnjets_ee_reweighted_ff_reweighted_MET_ratio_Logy_", hRatioTwo, 1, 1, true, true);
  
  
  
   
   
  //    TH1F *CandidateOverFit = new TH1F("CandidateOverFit", "Candidate diEMPt to fit diEMPt ratio", 200, 0.0, 200.0);
  //    if (status == 0) {                       // check on fit status
  //      TH1F* result = (TH1F*) fit->GetPlot();
  //      h_DoublePhoton_MET->SetLineColor(kGreen+3);
  //      h_->Draw("Ep");
  //      result->SetLineColor(2);
  //      result->Draw("same");
  //      //TH1F *CandidateOverFit = new TH1F("CandidateOverFit", "Candidate E_{T}^{miss} to fit E_{T}^{miss} ratio", 200, 0.0, 200.0);
  //      CandidateOverFit->Sumw2();
  //      CandidateOverFit->Divide(h_met_candidate, result); 
  //      //CandidateOverFit->Draw();
  //    }
   
  fsys->Close();
  f8->Close();
  f9->Close();
  fTT->Close();
  Histofile->Close();
  Histofile2->Close();
  Histofile3->Close();
  KeithFile->Close();
  KeithFileConstAndSlope->Close();
  EEFFFile->Clear();
 
}
