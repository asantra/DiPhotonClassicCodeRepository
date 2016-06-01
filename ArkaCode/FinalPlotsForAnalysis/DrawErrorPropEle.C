/* used to draw error propagating from diempt ratio */

#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TFile.h>
#include <iostream>
#include <sys/stat.h>
#include "/home/arka/arka/include/MyFunction.h"


void DrawErrorPropEle(int pt, bool data, bool analysisFake){
  
  TFile *F22=0, *F23=0;
  if(pt == 40 && !data)F22 = new TFile("DYtoEEWeightedProper74.root","READ");
  if(pt == 50 && !data)F22 = new TFile("DYtoEEWeightedProper74_Pt50.root","READ");
  
  if(pt == 40 && data){
    if(analysisFake)F22 = new TFile("Data_RunD_All_AnalysisFake_217fb.root","READ");
    else F22 = new TFile("Data_RunD_All_ExtendedFake_217fb.root","READ");
  }
  
  TH1F *h_DoubleElectron_MET_Reweighted = (TH1F*)F22->Get("h_DoubleElectron_MET_Reweighted");
  TH1F *h_DoubleElectron_MET_ReweightedNJets = (TH1F*)F22->Get("h_DoubleElectron_MET_ReweightedNJets");
  TH1F *h_DoubleElectron_MET_ReweightedDiEMPtNJets = (TH1F*)F22->Get("h_DoubleElectron_MET_ReweightedDiEMPtNJets");
  
  h_DoubleElectron_MET_Reweighted = getOverflow(h_DoubleElectron_MET_Reweighted);
  h_DoubleElectron_MET_ReweightedNJets = getOverflow(h_DoubleElectron_MET_ReweightedNJets);
  h_DoubleElectron_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleElectron_MET_ReweightedDiEMPtNJets);
  
  double integralall = h_DoubleElectron_MET_Reweighted->Integral();
  //h_DoubleElectron_MET_Reweighted->Scale(1./integralall);
  
  
  if(pt == 40 && !data)F23 = new TFile("GJet_Pt40_All.root","READ");
  if(pt == 50 && !data)F23 = new TFile("GJet_Pt40_All_Pt50.root","READ");
  if(pt == 40 && data){
    if(analysisFake)F23 = new TFile("Data_RunD_All_AnalysisFake_217fb.root","READ");
    else F23 = new TFile("Data_RunD_All_ExtendedFake_217fb.root","READ");
  }
  
  TH1F *h_DoubleFake_MET_Reweighted = (TH1F*)F23->Get("h_DoubleFake_MET_Reweighted");
  TH1F *h_DoubleFakeShowershape_MET_Reweighted = (TH1F*)F23->Get("h_DoubleFakeShowershape_MET_Reweighted");
  
  TH1F *h_DoubleFake_MET_ReweightedNJets = (TH1F*)F23->Get("h_DoubleFake_MET_ReweightedNJets");
  TH1F *h_DoubleFakeShowershape_MET_ReweightedNJets = (TH1F*)F23->Get("h_DoubleFakeShowershape_MET_ReweightedNJets");
  
  TH1F *h_DoubleFake_MET_ReweightedDiEMPtNJets = (TH1F*)F23->Get("h_DoubleFake_MET_ReweightedDiEMPtNJets");
  TH1F *h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets = (TH1F*)F23->Get("h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets");
  
  TH1F* h_DoubleElectron_NJets_Reweighted = (TH1F*)F23->Get("h_DoubleElectron_NJets_Reweighted");
  TH1F* h_DoubleFake_NJets_Reweighted = (TH1F*)F23->Get("h_DoubleFake_NJets_Reweighted");
  
  TH1F *h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio = (TH1F*)F23->Get("h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio");
  TH1F *h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio = (TH1F*)F23->Get("h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio");
  
  
  h_DoubleFake_MET_Reweighted = getOverflow(h_DoubleFake_MET_Reweighted);
  h_DoubleFakeShowershape_MET_Reweighted = getOverflow(h_DoubleFakeShowershape_MET_Reweighted);
  
  h_DoubleFake_MET_ReweightedNJets = getOverflow(h_DoubleFake_MET_ReweightedNJets);
  h_DoubleFakeShowershape_MET_ReweightedNJets = getOverflow(h_DoubleFakeShowershape_MET_ReweightedNJets);
  
  h_DoubleFake_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleFake_MET_ReweightedDiEMPtNJets);
  h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets = getOverflow(h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets);
  
  h_DoubleElectron_NJets_Reweighted = getOverflow(h_DoubleElectron_NJets_Reweighted);
  h_DoubleFake_NJets_Reweighted = getOverflow(h_DoubleFake_NJets_Reweighted);
  
  h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio = getOverflow(h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio);
  h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio = getOverflow(h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio);
  
  
  double integralff = h_DoubleFake_MET_Reweighted->Integral();
  //h_DoubleFake_MET_Reweighted->Scale(1./integralff);
  double integralffshowershape = h_DoubleFakeShowershape_MET_Reweighted->Integral();
  //h_DoubleFakeShowershape_MET_Reweighted->Scale(1./integralffshowershape);
  
  
  //Float_t bins2[] = {0,5,10,15,20,25,30,35,40,45,50,55,60,70,80,100,125,175,250,400};
  //Int_t  binnum2 = sizeof(bins2)/sizeof(Float_t) - 1; 
  TH1F* ErrorPropDiEMPteeMET;
  TH1F* ErrorPropDiEMPtffMET;
  TH1F* ErrorPropDiEMPtffshowershapeMET;
  
  TH1F* ErrorPropNJetseeMET;
  TH1F* ErrorPropNJetsffMET;
  TH1F* ErrorPropNJetsffshowershapeMET;
  
  TH1F* ErrorPropDiEMPtNJetseeMET;
  TH1F* ErrorPropDiEMPtNJetsffMET;
  TH1F* ErrorPropDiEMPtNJetsffshowershapeMET;
  
  TH1F* ErrorPropDiEMPtWeightedNJetsee;
  TH1F* ErrorPropDiEMPtWeightedNJetsff;
  
  
  TH1F* ErrorPropDiEMPtVsNJetWeightedee;
  TH1F* ErrorPropDiEMPtVsNJetWeightedff;
  
  
  ErrorPropDiEMPteeMET = (TH1F*)h_DoubleElectron_MET_Reweighted->Clone("ErrorPropDiEMPteeMET");
  ErrorPropDiEMPteeMET->Reset();
  ErrorPropDiEMPteeMET->SetTitle("ee E_{T}^{miss} with error propagation from diempt");
  
  ErrorPropDiEMPtffMET = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("ErrorPropDiEMPtffMET");
  ErrorPropDiEMPtffMET->Reset();
  ErrorPropDiEMPtffMET->SetTitle("ff E_{T}^{miss} with error propagation from diempt");
  
  ErrorPropDiEMPtffshowershapeMET = (TH1F*)h_DoubleFakeShowershape_MET_Reweighted->Clone("ErrorPropDiEMPtffshowershapeMET");
  ErrorPropDiEMPtffshowershapeMET->Reset();
  ErrorPropDiEMPtffshowershapeMET->SetTitle("ff E_{T}^{miss} with error propagation from diempt");
  
  
  
  ErrorPropNJetseeMET = (TH1F*)h_DoubleElectron_MET_ReweightedNJets->Clone("ErrorPropNJetseeMET");
  ErrorPropNJetseeMET->Reset();
  ErrorPropNJetseeMET->SetTitle("ee E_{T}^{miss} with error propagation from njets");
  
  ErrorPropNJetsffMET = (TH1F*)h_DoubleFake_MET_ReweightedNJets->Clone("ErrorPropNJetsffMET");
  ErrorPropNJetsffMET->Reset();
  ErrorPropNJetsffMET->SetTitle("ff E_{T}^{miss} with error propagation from njets");
  
  ErrorPropNJetsffshowershapeMET = (TH1F*)h_DoubleFakeShowershape_MET_ReweightedNJets->Clone("ErrorPropNJetsffshowershapeMET");
  ErrorPropNJetsffshowershapeMET->Reset();
  ErrorPropNJetsffshowershapeMET->SetTitle("ff E_{T}^{miss} with error propagation from njets");
  
  
  
  ErrorPropDiEMPtNJetseeMET = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets->Clone("ErrorPropDiEMPtNJetseeMET");
  ErrorPropDiEMPtNJetseeMET->Reset();
  ErrorPropDiEMPtNJetseeMET->SetTitle("ee E_{T}^{miss} with error propagation from njets");
  
  ErrorPropDiEMPtNJetsffMET = (TH1F*)h_DoubleFake_MET_ReweightedDiEMPtNJets->Clone("ErrorPropDiEMPtNJetsffMET");
  ErrorPropDiEMPtNJetsffMET->Reset();
  ErrorPropDiEMPtNJetsffMET->SetTitle("ff E_{T}^{miss} with error propagation from njets");
  
  ErrorPropDiEMPtNJetsffshowershapeMET = (TH1F*)h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->Clone("ErrorPropDiEMPtNJetsffshowershapeMET");
  ErrorPropDiEMPtNJetsffshowershapeMET->Reset();
  ErrorPropDiEMPtNJetsffshowershapeMET->SetTitle("ff E_{T}^{miss} with error propagation from njets");
  
  
  ErrorPropDiEMPtWeightedNJetsee = (TH1F*)h_DoubleElectron_NJets_Reweighted->Clone("ErrorPropDiEMPtWeightedNJetsee");
  ErrorPropDiEMPtWeightedNJetsee->Reset();
  ErrorPropDiEMPtWeightedNJetsee->SetTitle("ee Njets with error propagation from diempt");
  
  
  ErrorPropDiEMPtWeightedNJetsff = (TH1F*)h_DoubleFake_NJets_Reweighted->Clone("ErrorPropDiEMPtWeightedNJetsff");
  ErrorPropDiEMPtWeightedNJetsff->Reset();
  ErrorPropDiEMPtWeightedNJetsff->SetTitle("ff Njets with error propagation from diempt");
  
  
  ErrorPropDiEMPtVsNJetWeightedee = (TH1F*)h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Clone("ErrorPropDiEMPtVsNJetWeightedee");
  ErrorPropDiEMPtVsNJetWeightedee->Reset();
  ErrorPropDiEMPtVsNJetWeightedee->SetTitle("ee diEMPt vs NJet error propagation");
  
  
  ErrorPropDiEMPtVsNJetWeightedff = (TH1F*)h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->Clone("ErrorPropDiEMPtVsNJetWeightedff");
  ErrorPropDiEMPtVsNJetWeightedff->Reset();
  ErrorPropDiEMPtVsNJetWeightedff->SetTitle("ff diEMPt vs NJet error propagation");
  
  

  TH1F *DiEMPtRatioWeightedee[1000], *DiEMPtRatioWeightedff[1000], *DiEMPtRatioWeightedffshowershape[1000];
  TH1F *NJetsRatioWeightedee[1000], *NJetsRatioWeightedff[1000], *NJetsRatioWeightedffshowershape[1000];
  TH1F *DiEMPtRatioWeightedeeNJets[1000], *DiEMPtRatioWeightedffNJets[1000];
  
  TH1F *DiEMPtVsNJetRatioWeightedee[1000], *DiEMPtVsNJetRatioWeightedff[1000];
  
  
  for(int g=0; g<1000; ++g){
    char *nameGraph3        = new char[50];
    
    sprintf(nameGraph3,"DiEMPtReweightedee%d",g+1);
    DiEMPtRatioWeightedee[g] = (TH1F*)F22->Get(nameGraph3);
    //double w = DiEMPtRatioWeightedee[g]->Integral();
    //DiEMPtRatioWeightedee[g]->Scale(1./w);
    
    sprintf(nameGraph3,"DiEMPtReweightedff%d",g+1);
    DiEMPtRatioWeightedff[g] = (TH1F*)F23->Get(nameGraph3);
    //double w2 = DiEMPtRatioWeightedff[g]->Integral();
    //DiEMPtRatioWeightedff[g]->Scale(1./w2);
    
    sprintf(nameGraph3,"DiEMPtReweightedffshowershape%d",g+1);
    DiEMPtRatioWeightedffshowershape[g] = (TH1F*)F23->Get(nameGraph3);
    //double w3 = DiEMPtRatioWeightedffshowershape[g]->Integral();
    //DiEMPtRatioWeightedffshowershape[g]->Scale(1./w3);
    
    
    sprintf(nameGraph3,"NJetsReweightedee%d",g+1);
    NJetsRatioWeightedee[g] = (TH1F*)F22->Get(nameGraph3);
    //double w = DiEMPtRatioWeightedee[g]->Integral();
    //DiEMPtRatioWeightedee[g]->Scale(1./w);
    
    sprintf(nameGraph3,"NJetsReweightedff%d",g+1);
    NJetsRatioWeightedff[g] = (TH1F*)F23->Get(nameGraph3);
    //double w2 = DiEMPtRatioWeightedff[g]->Integral();
    //DiEMPtRatioWeightedff[g]->Scale(1./w2);
    
    sprintf(nameGraph3,"NJetsReweightedffshowershape%d",g+1);
    NJetsRatioWeightedffshowershape[g] = (TH1F*)F23->Get(nameGraph3);
    //double w3 = DiEMPtRatioWeightedffshowershape[g]->Integral();
    //DiEMPtRatioWeightedffshowershape[g]->Scale(1./w3);
    
    sprintf(nameGraph3, "DiEMPtReweightedNJetsee%d",g+1);
    DiEMPtRatioWeightedeeNJets[g] = (TH1F*)F23->Get(nameGraph3);
    
    sprintf(nameGraph3, "DiEMPtReweightedNJetsff%d",g+1);
    DiEMPtRatioWeightedffNJets[g] = (TH1F*)F23->Get(nameGraph3);
    
    
    sprintf(nameGraph3, "DiEMPtVsNJetReweightedee%d",g+1);
    DiEMPtVsNJetRatioWeightedee[g] = (TH1F*)F23->Get(nameGraph3);
    
    sprintf(nameGraph3, "DiEMPtVsNJetReweightedff%d",g+1);
    DiEMPtVsNJetRatioWeightedff[g] = (TH1F*)F23->Get(nameGraph3);
    
  }

  


  double xbindiempt[50][1000]                 = {{0},{0}};
  double centraldiempt[50]                    = {0};
  double errorupdiempt[50]                    = {0};
  double errordowndiempt[50]                  = {0};
  
  double xbinffdiempt[50][1000]                 = {{0},{0}};
  double centralffdiempt[50]                    = {0};
  double errorupffdiempt[50]                    = {0};
  double errordownffdiempt[50]                  = {0};
  
  
  double xbindiemptreweightednjetsee[50][1000]   = {{0},{0}};
  double centraldiemptreweightednjetsee[50]      = {0};
  double errorupdiemptreweightednjetsee[50]      = {0};
  double errordowndiemptreweightednjetsee[50]    = {0};
  
  
  double xbindiemptreweightednjetsff[50][1000]   = {{0},{0}};
  double centraldiemptreweightednjetsff[50]      = {0};
  double errorupdiemptreweightednjetsff[50]      = {0};
  double errordowndiemptreweightednjetsff[50]    = {0};
  
  
  double xbinffshowershapediempt[50][1000]      = {{0},{0}};
  double centralffshowershapediempt[50]         = {0};
  double errorupffshowershapediempt[50]         = {0};
  double errordownffshowershapediempt[50]       = {0};
  
  
  double xbinnjets[50][1000]                 = {{0},{0}};
  double centralnjets[50]                    = {0};
  double errorupnjets[50]                    = {0};
  double errordownnjets[50]                  = {0};
  
  double xbinffnjets[50][1000]                 = {{0},{0}};
  double centralffnjets[50]                    = {0};
  double errorupffnjets[50]                    = {0};
  double errordownffnjets[50]                  = {0};
  
  double xbinffshowershapenjets[50][1000]      = {{0},{0}};
  double centralffshowershapenjets[50]         = {0};
  double errorupffshowershapenjets[50]         = {0};
  double errordownffshowershapenjets[50]       = {0};
  
  
  double totalerrordiempt[50]               = {0};
  double totalerrorffdiempt[50]             = {0};
  double totalerrorffshowershapediempt[50]  = {0};
  
  double totalerrornjets[50]               = {0};
  double totalerrorffnjets[50]             = {0};
  double totalerrorffshowershapenjets[50]  = {0};
  
  
  double totalerror[50]                     = {0};
  double totalerrorff[50]                   = {0};
  double totalerrorffshowershape[50]        = {0};
  
  
  double totalerrordiemptreweightednjetsee[50] = {0};
  double totalerrordiemptreweightednjetsff[50] = {0};
  
  
  
  
  
  double xbindiemptvsnjetsee[50][1000]                 = {{0},{0}};
  double centraldiemptvsnjetsee[50]                    = {0};
  double errorupdiemptvsnjetsee[50]                    = {0};
  double errordowndiemptvsnjetsee[50]                  = {0};
  
  double xbindiemptvsnjetsff[50][1000]                 = {{0},{0}};
  double centraldiemptvsnjetsff[50]                    = {0};
  double errorupdiemptvsnjetsff[50]                    = {0};
  double errordowndiemptvsnjetsff[50]                  = {0};
  
  double totalerrordiemptvsnjetreweightedee[50] = {0};
  double totalerrordiemptvsnjetreweightedff[50] = {0};

  for(int j=0 ; j < ErrorPropDiEMPteeMET->GetNbinsX() ; ++j){
    
    double mindiempt(100000000), minffdiempt(100000000), minffshowershapediempt(10000000);
    double maxdiempt(-10), maxffdiempt(-10), maxffshowershape(-10);
    
    double minnjets(100000000), minffnjets(100000000), minffshowershapenjets(10000000);
    double maxnjets(-10), maxffnjets(-10), maxffshowershapenjets(-10);
    
    double mindiemptvsnjetsee(100000000), mindiemptvsnjetsff(100000000);
    double maxdiemptvsnjetsee(-10), maxdiemptvsnjetsff(-10);
    
    
  
    for(int k=0 ; k<1000; ++k){
      xbindiempt[j][k]       = DiEMPtRatioWeightedee[k]->GetBinContent(j+1);
      if(maxdiempt < xbindiempt[j][k])maxdiempt=xbindiempt[j][k];
      if(mindiempt > xbindiempt[j][k])mindiempt=xbindiempt[j][k];
      
      
      xbinffdiempt[j][k]       = DiEMPtRatioWeightedff[k]->GetBinContent(j+1);
      if(maxffdiempt < xbinffdiempt[j][k])maxffdiempt=xbinffdiempt[j][k];
      if(minffdiempt > xbinffdiempt[j][k])minffdiempt=xbinffdiempt[j][k];
      
      xbinffshowershapediempt[j][k]       = DiEMPtRatioWeightedffshowershape[k]->GetBinContent(j+1);
      if(maxffshowershape < xbinffshowershapediempt[j][k])maxffshowershape=xbinffshowershapediempt[j][k];
      if(minffshowershapediempt > xbinffshowershapediempt[j][k])minffshowershapediempt=xbinffshowershapediempt[j][k];
      
      
      xbinnjets[j][k]       = NJetsRatioWeightedee[k]->GetBinContent(j+1);
      if(maxnjets < xbinnjets[j][k])maxnjets=xbinnjets[j][k];
      if(minnjets > xbinnjets[j][k])minnjets=xbinnjets[j][k];
      
      xbinffnjets[j][k]       = NJetsRatioWeightedff[k]->GetBinContent(j+1);
      if(maxffnjets < xbinffnjets[j][k])maxffnjets=xbinffnjets[j][k];
      if(minffnjets > xbinffnjets[j][k])minffnjets=xbinffnjets[j][k];
      
      xbinffshowershapenjets[j][k]       = NJetsRatioWeightedffshowershape[k]->GetBinContent(j+1);
      if(maxffshowershapenjets < xbinffshowershapenjets[j][k])maxffshowershapenjets=xbinffshowershapenjets[j][k];
      if(minffshowershapenjets > xbinffshowershapenjets[j][k])minffshowershapenjets=xbinffshowershapenjets[j][k];
      
      
      xbindiemptvsnjetsee[j][k]       = DiEMPtVsNJetRatioWeightedee[k]->GetBinContent(j+1);
      if(maxdiemptvsnjetsee < xbindiemptvsnjetsee[j][k])maxdiemptvsnjetsee=xbindiemptvsnjetsee[j][k];
      if(mindiemptvsnjetsee > xbindiemptvsnjetsee[j][k])mindiemptvsnjetsee=xbindiemptvsnjetsee[j][k];
      
      xbindiemptvsnjetsff[j][k]       = DiEMPtVsNJetRatioWeightedff[k]->GetBinContent(j+1);
      if(maxdiemptvsnjetsff < xbindiemptvsnjetsff[j][k])maxdiemptvsnjetsff=xbindiemptvsnjetsff[j][k];
      if(mindiemptvsnjetsff > xbindiemptvsnjetsff[j][k])mindiemptvsnjetsff=xbindiemptvsnjetsff[j][k];
      
    }
    
    centraldiempt[j]   = h_DoubleElectron_MET_Reweighted->GetBinContent(j+1);
    errorupdiempt[j]   = 0.68*(maxdiempt-centraldiempt[j]);
    errordowndiempt[j] = 0.68*(centraldiempt[j]-mindiempt); 
    
    centralffdiempt[j]   = h_DoubleFake_MET_Reweighted->GetBinContent(j+1);
    errorupffdiempt[j]   = 0.68*(maxffdiempt-centralffdiempt[j]);
    errordownffdiempt[j] = 0.68*(centralffdiempt[j]-minffdiempt); 
    
    centralffshowershapediempt[j]   = h_DoubleFakeShowershape_MET_Reweighted->GetBinContent(j+1);
    errorupffshowershapediempt[j]   = 0.68*(maxffshowershape-centralffshowershapediempt[j]);
    errordownffshowershapediempt[j] = 0.68*(centralffshowershapediempt[j]-minffshowershapediempt); 



    centralnjets[j]   = h_DoubleElectron_MET_ReweightedNJets->GetBinContent(j+1);
    errorupnjets[j]   = 0.68*(maxnjets-centralnjets[j]);
    errordownnjets[j] = 0.68*(centralnjets[j]-minnjets); 
    
    centralffnjets[j]   = h_DoubleFake_MET_ReweightedNJets->GetBinContent(j+1);
    errorupffnjets[j]   = 0.68*(maxffnjets-centralffnjets[j]);
    errordownffnjets[j] = 0.68*(centralffnjets[j]-minffnjets); 
    
    centralffshowershapenjets[j]   = h_DoubleFakeShowershape_MET_ReweightedNJets->GetBinContent(j+1);
    errorupffshowershapenjets[j]   = 0.68*(maxffshowershapenjets-centralffshowershapenjets[j]);
    errordownffshowershapenjets[j] = 0.68*(centralffshowershapenjets[j]-minffshowershapenjets);
    
    
    totalerrordiempt[j] = sqrt((errorupdiempt[j]+errordowndiempt[j])*(errorupdiempt[j]+errordowndiempt[j])); 
    totalerrorffdiempt[j] = sqrt((errorupffdiempt[j]+errordownffdiempt[j])*(errorupffdiempt[j]+errordownffdiempt[j]));
    totalerrorffshowershapediempt[j] = sqrt((errorupffshowershapediempt[j]+errordownffshowershapediempt[j])*(errorupffshowershapediempt[j]+errordownffshowershapediempt[j]));
    
    totalerrornjets[j] = sqrt((errorupnjets[j]+errordownnjets[j])*(errorupnjets[j]+errordownnjets[j])); 
    totalerrorffnjets[j] = sqrt((errorupffnjets[j]+errordownffnjets[j])*(errorupffnjets[j]+errordownffnjets[j]));
    totalerrorffshowershapenjets[j] = sqrt((errorupffshowershapenjets[j]+errordownffshowershapenjets[j])*(errorupffshowershapenjets[j]+errordownffshowershapenjets[j]));
    
    totalerror[j] = sqrt(totalerrordiempt[j]*totalerrordiempt[j]+totalerrornjets[j]*totalerrornjets[j]);
    totalerrorff[j] = sqrt(totalerrorffdiempt[j]*totalerrorffdiempt[j]+totalerrorffnjets[j]*totalerrorffnjets[j]);
    totalerrorffshowershape[j] = sqrt(totalerrorffshowershapediempt[j]*totalerrorffshowershapediempt[j]+totalerrorffshowershapenjets[j]*totalerrorffshowershapenjets[j]);
    
    
    
    double metvalue = h_DoubleElectron_MET_Reweighted->GetBinContent(j+1);
    ErrorPropDiEMPteeMET->SetBinContent(j+1, metvalue);
    ErrorPropDiEMPteeMET->SetBinError(j+1, totalerrordiempt[j]);
    //cout << "ee bin: " << j << " total error diempt: " << totalerrordiempt[j] << " and E_{T}^{miss} value: " << metvalue << endl;
    double metvalue2 = h_DoubleFake_MET_Reweighted->GetBinContent(j+1);
    ErrorPropDiEMPtffMET->SetBinContent(j+1, metvalue2);
    ErrorPropDiEMPtffMET->SetBinError(j+1, totalerrorffdiempt[j]);
    //cout << "ff bin: " << j << " total error diempt: " << totalerrorffdiempt[j] << " and E_{T}^{miss} value: " << metvalue2 << endl;
    
    double metvalue3 = h_DoubleFakeShowershape_MET_Reweighted->GetBinContent(j+1);
    ErrorPropDiEMPtffshowershapeMET->SetBinContent(j+1, metvalue3);
    ErrorPropDiEMPtffshowershapeMET->SetBinError(j+1, totalerrorffshowershapediempt[j]);
    
    
    
    
    double metvalue4 = h_DoubleElectron_MET_ReweightedNJets->GetBinContent(j+1);
    ErrorPropNJetseeMET->SetBinContent(j+1, metvalue4);
    ErrorPropNJetseeMET->SetBinError(j+1, totalerrornjets[j]);
    //cout << "ee bin: " << j << " total error njet: " << totalerrornjets[j] << " and E_{T}^{miss} value: " << metvalue4 << endl;
    double metvalue5 = h_DoubleFake_MET_ReweightedNJets->GetBinContent(j+1);
    ErrorPropNJetsffMET->SetBinContent(j+1, metvalue5);
    ErrorPropNJetsffMET->SetBinError(j+1, totalerrorffnjets[j]);
    //cout << "ff bin: " << j << " total error njet: " << totalerrorffnjets[j] << " and E_{T}^{miss} value: " << metvalue2 << endl;
    
    double metvalue6 = h_DoubleFakeShowershape_MET_ReweightedNJets->GetBinContent(j+1);
    ErrorPropNJetsffshowershapeMET->SetBinContent(j+1, metvalue6);
    ErrorPropNJetsffshowershapeMET->SetBinError(j+1, totalerrorffshowershapenjets[j]);
    
    
    
    metvalue4 = h_DoubleElectron_MET_ReweightedDiEMPtNJets->GetBinContent(j+1);
    ErrorPropDiEMPtNJetseeMET->SetBinContent(j+1, metvalue4);
    ErrorPropDiEMPtNJetseeMET->SetBinError(j+1, totalerror[j]);
    //cout << "ee bin: " << j << " total error: " << totalerror[j] << " and E_{T}^{miss} value: " << metvalue4 << endl;
    
    metvalue5 = h_DoubleFake_MET_ReweightedDiEMPtNJets->GetBinContent(j+1);
    ErrorPropDiEMPtNJetsffMET->SetBinContent(j+1, metvalue5);
    ErrorPropDiEMPtNJetsffMET->SetBinError(j+1, totalerrorff[j]);
    //cout << "ff bin: " << j << " total error: " << totalerrorff[j] << " and E_{T}^{miss} value: " << metvalue2 << endl;
    
    metvalue6 = h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->GetBinContent(j+1);
    ErrorPropDiEMPtNJetsffshowershapeMET->SetBinContent(j+1, metvalue6);
    ErrorPropDiEMPtNJetsffshowershapeMET->SetBinError(j+1, totalerrorffshowershapenjets[j]);
    
    
    
    
    // from 2D plots
    centraldiemptvsnjetsee[j]     = h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(j+1);
    errorupdiemptvsnjetsee[j]     = 0.68*(maxdiemptvsnjetsee - centraldiemptvsnjetsee[j]);
    errordowndiemptvsnjetsee[j]   = 0.68*(centraldiemptvsnjetsee[j] - mindiemptvsnjetsee);
    
    
    centraldiemptvsnjetsff[j]     = h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(j+1);
    errorupdiemptvsnjetsff[j]     = 0.68*(maxdiemptvsnjetsff - centraldiemptvsnjetsff[j]);
    errordowndiemptvsnjetsff[j]   = 0.68*(centraldiemptvsnjetsff[j] - mindiemptvsnjetsff);
    
    
    totalerrordiemptvsnjetreweightedee[j] = sqrt((errorupdiemptvsnjetsee[j]+errordowndiemptvsnjetsee[j])*(errorupdiemptvsnjetsee[j]+errordowndiemptvsnjetsee[j]));
    totalerrordiemptvsnjetreweightedff[j] = sqrt((errorupdiemptvsnjetsff[j]+errordowndiemptvsnjetsff[j])*(errorupdiemptvsnjetsff[j]+errordowndiemptvsnjetsff[j]));
    
    metvalue5 = h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(j+1);
    ErrorPropDiEMPtVsNJetWeightedee->SetBinContent(j+1, metvalue5);
    ErrorPropDiEMPtVsNJetWeightedee->SetBinError(j+1, totalerrordiemptvsnjetreweightedee[j]);
    
    metvalue5 = h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->GetBinContent(j+1);
    ErrorPropDiEMPtVsNJetWeightedff->SetBinContent(j+1, metvalue5);
    ErrorPropDiEMPtVsNJetWeightedff->SetBinError(j+1, totalerrordiemptvsnjetreweightedff[j]); 
  }
  
  
  for(int j = 0; j < ErrorPropDiEMPtWeightedNJetsee->GetNbinsX();++j){
    double mindiemptreweightednjetsee(100000000), mindiemptreweightednjetsff(100000000);
    double maxdiemptreweightednjetsee(-10), maxdiemptreweightednjetsff(-10);
    
    for(int k=0; k<1000; ++k){
      xbindiemptreweightednjetsee[j][k]       = DiEMPtRatioWeightedeeNJets[k]->GetBinContent(j+1);
      if(maxdiemptreweightednjetsee < xbindiemptreweightednjetsee[j][k])maxdiemptreweightednjetsee=xbindiemptreweightednjetsee[j][k];
      if(mindiemptreweightednjetsee > xbindiemptreweightednjetsee[j][k])mindiemptreweightednjetsee=xbindiemptreweightednjetsee[j][k];
      
      xbindiemptreweightednjetsff[j][k]       = DiEMPtRatioWeightedffNJets[k]->GetBinContent(j+1);
      if(maxdiemptreweightednjetsff < xbindiemptreweightednjetsff[j][k])maxdiemptreweightednjetsff=xbindiemptreweightednjetsff[j][k];
      if(mindiemptreweightednjetsff > xbindiemptreweightednjetsff[j][k])mindiemptreweightednjetsff=xbindiemptreweightednjetsff[j][k];
    }
    
    centraldiemptreweightednjetsee[j]   = h_DoubleElectron_NJets_Reweighted->GetBinContent(j+1);
    errorupdiemptreweightednjetsee[j]   = 0.68*(maxdiemptreweightednjetsee-centraldiemptreweightednjetsee[j]);
    errordowndiemptreweightednjetsee[j] = 0.68*(centraldiemptreweightednjetsee[j]-mindiemptreweightednjetsee); 
    
    centraldiemptreweightednjetsff[j]   = h_DoubleFake_NJets_Reweighted->GetBinContent(j+1);
    errorupdiemptreweightednjetsff[j]   = 0.68*(maxdiemptreweightednjetsff-centraldiemptreweightednjetsff[j]);
    errordowndiemptreweightednjetsff[j] = 0.68*(centraldiemptreweightednjetsff[j]-mindiemptreweightednjetsff); 
    
    totalerrordiemptreweightednjetsee[j] = sqrt((errorupdiemptreweightednjetsee[j]+errordowndiemptreweightednjetsee[j])*(errorupdiemptreweightednjetsee[j]+errordowndiemptreweightednjetsee[j]));
    totalerrordiemptreweightednjetsff[j] = sqrt((errorupdiemptreweightednjetsff[j]+errordowndiemptreweightednjetsff[j])*(errorupdiemptreweightednjetsff[j]+errordowndiemptreweightednjetsff[j]));
    
    
    double njetsValue = h_DoubleElectron_NJets_Reweighted->GetBinContent(j+1);
    ErrorPropDiEMPtWeightedNJetsee->SetBinContent(j+1, njetsValue);
    ErrorPropDiEMPtWeightedNJetsee->SetBinError(j+1, totalerrordiemptreweightednjetsee[j]);
    
    njetsValue = h_DoubleFake_NJets_Reweighted->GetBinContent(j+1);
    ErrorPropDiEMPtWeightedNJetsff->SetBinContent(j+1, njetsValue);
    ErrorPropDiEMPtWeightedNJetsff->SetBinError(j+1, totalerrordiemptreweightednjetsff[j]);
    
  }

  ErrorPropDiEMPteeMET->Draw();
  TString OutputFolder = "";
  
  if(analysisFake)OutputFolder="Data_RunD_Ratio_AnalysisFake_217fb";
  else OutputFolder="Data_RunD_Ratio_ExtendedFake_217fb";
    
  int stat0;
  stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

  TFile* fout2=0;
  if(!data)fout2= new TFile(OutputFolder+"/ErrorPropDiEMPttoElectronMET.root","RECREATE");
  else fout2= new TFile(OutputFolder+"/ErrorPropDiEMPttoElectronMET_Data.root","RECREATE");
  fout2->cd();
  
  ErrorPropDiEMPteeMET->Write();
  ErrorPropDiEMPtffMET->Write();
  ErrorPropDiEMPtffshowershapeMET->Write();
  
  ErrorPropNJetseeMET->Write();
  ErrorPropNJetsffMET->Write();
  ErrorPropNJetsffshowershapeMET->Write();
  
  ErrorPropDiEMPtNJetseeMET->Write();
  ErrorPropDiEMPtNJetsffMET->Write();
  ErrorPropDiEMPtNJetsffshowershapeMET->Write();
  
  ErrorPropDiEMPtWeightedNJetsee->Write();
  ErrorPropDiEMPtWeightedNJetsff->Write();
  
  ErrorPropDiEMPtVsNJetWeightedee->Write();
  ErrorPropDiEMPtVsNJetWeightedff->Write();
  
  F22->Close();
  F23->Close();
  fout2->Close();
  
}
