#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include "/home/arka/arka/include/MyFunction.h"
#include <sys/stat.h>




void ReweightDIEMPt(int pt, bool data, bool analysisFake){  

  //////// electron reweighting  ////////////
   TFile *f8 = 0;
   TFile *f9 = 0;
   TFile *f10= 0;
   TH1F *h_DoubleElectron_DiEMPt = 0;
   TH1F *h_DoubleElectron_Rho=0, *h_DoubleElectron_Nvtx=0;
   TH1F *h_DoublePhoton_DiEMPt=0;
   TH1F *h_DoubleFake_DiEMPt=0, *h_DoubleFakeShowershape_DiEMPt=0;
   TH1F *h_DoublePhoton_Rho=0, *h_DoublePhoton_Nvtx=0; 
   TH1F *h_DoubleFake_Rho=0, *h_DoubleFake_Nvtx=0;
   TH1F *h_DoubleFakeShowershape_Rho=0, *h_DoubleFakeShowershape_Nvtx=0;
   TH1F *h_DoublePhoton_NJets=0, *h_DoubleFake_NJets=0, *h_DoubleElectron_NJets=0;
   TH1F *h_DoubleFakeShowershape_NJets=0;
   TH1F *h_DoublePhoton_NJets_NotForward=0, *h_DoubleFake_NJets_NotForward=0, *h_DoubleElectron_NJets_NotForward=0;
   TH1F *h_DoubleFakeShowershape_NJets_NotForward=0;
   
   TH1F *h_DoublePhoton_DeltaPhi=0;
   TH1F *h_DoublePhoton_DeltaPhi_AfterDRCut=0;
   TString OutputFolder="";   
   TH2F *h_DoublePhoton_NJet_vs_DiEMPt = 0;
   TH2F *h_DoubleElectron_NJet_vs_DiEMPt = 0;
   TH2F *h_DoubleFake_NJet_vs_DiEMPt = 0;
   
   TH1F *h_DoublePhoton_MET = 0;
   TH1F *h_DoubleFake_MET = 0;
   TH1F *h_DoubleElectron_MET = 0; 
   
   if(!data){
     OutputFolder="MonteCarlo_Ratio";
     if(pt == 40)f8 = new TFile("DYtoEEWeightedProper74.root", "READ");
     else f8 = new TFile("DYtoEEWeightedProper74_Pt50.root", "READ");
     h_DoubleElectron_DiEMPt = (TH1F*)f8->Get("h_DoubleElectron_DiEMPt");
     h_DoubleElectron_Rho = (TH1F*)f8->Get("h_DoubleElectron_Rho");
     //h_DoubleElectron_DiEMPt->Sumw2();
     h_DoubleElectron_DiEMPt->Scale(1.0, "width");
     Float_t y1=h_DoubleElectron_DiEMPt->Integral(0, h_DoubleElectron_DiEMPt->GetNbinsX()+1);
     h_DoubleElectron_DiEMPt->Scale(1.0/y1);
     
     h_DoubleElectron_Rho->Scale(1.0, "width");
     Float_t y2=h_DoubleElectron_Rho->Integral(0, h_DoubleElectron_Rho->GetNbinsX()+1);
     h_DoubleElectron_Rho->Scale(1.0/y2);
     
     
     if(pt == 40)f9 = new TFile("GJet_Pt40_All.root", "READ");
     else f9 = new TFile("GJet_Pt40_All_Pt50.root", "READ");
     h_DoublePhoton_DiEMPt = (TH1F*)f9->Get("h_DoublePhoton_DiEMPt");
     h_DoubleFake_DiEMPt = (TH1F*)f9->Get("h_DoubleFake_DiEMPt");
     h_DoublePhoton_Rho = (TH1F*)f9->Get("h_DoublePhoton_Rho");
     h_DoubleFake_Rho = (TH1F*)f9->Get("h_DoubleFake_Rho");
     //h_DoublePhoton_DiEMPt->Sumw2();
     
     h_DoublePhoton_Rho->Scale(1.0, "width");
     Float_t d1=h_DoublePhoton_Rho->Integral(0, h_DoublePhoton_Rho->GetNbinsX()+1);
     h_DoublePhoton_Rho->Scale(1.0/d1);
     
     h_DoubleFake_Rho->Scale(1.0, "width");
     Float_t d2=h_DoubleFake_Rho->Integral(0, h_DoubleFake_Rho->GetNbinsX()+1);
     h_DoubleFake_Rho->Scale(1.0/d2);
     
     h_DoublePhoton_DiEMPt->Scale(1.0, "width");
     Float_t d3=h_DoublePhoton_DiEMPt->Integral(0, h_DoublePhoton_DiEMPt->GetNbinsX()+1);
     h_DoublePhoton_DiEMPt->Scale(1.0/d3);
     
     h_DoubleFake_DiEMPt->Scale(1.0, "width");
     Float_t d4=h_DoubleFake_DiEMPt->Integral(0, h_DoubleFake_DiEMPt->GetNbinsX());
     h_DoubleFake_DiEMPt->Scale(1.0/d4);
  }
   
   else{
     OutputFolder="";
     if(analysisFake)OutputFolder="Data_RunD_Ratio_AnalysisFake_217fb";
     else OutputFolder="Data_RunD_Ratio_ExtendedFake_217fb";
     
     if(pt == 40){
       if(analysisFake)f10 = new TFile("Data_RunD_All_AnalysisFake_217fb.root", "READ");
       else f10 = new TFile("Data_RunD_All_ExtendedFake_217fb.root", "READ");
     }
     
     h_DoubleElectron_DiEMPt = (TH1F*)f10->Get("h_DoubleElectron_DiEMPt");
     h_DoubleElectron_Rho = (TH1F*)f10->Get("h_DoubleElectron_Rho");
     h_DoubleElectron_Nvtx = (TH1F*)f10->Get("h_DoubleElectron_Nvtx");
     //h_DoubleElectron_DiEMPt->Sumw2();
     h_DoublePhoton_DiEMPt = (TH1F*)f10->Get("h_DoublePhoton_DiEMPt");
     h_DoubleFake_DiEMPt = (TH1F*)f10->Get("h_DoubleFake_DiEMPt");
     h_DoubleFakeShowershape_DiEMPt = (TH1F*)f10->Get("h_DoubleFakeShowershape_DiEMPt");
     
     h_DoublePhoton_Rho = (TH1F*)f10->Get("h_DoublePhoton_Rho");
     h_DoubleFake_Rho = (TH1F*)f10->Get("h_DoubleFake_Rho");
     h_DoubleFakeShowershape_Rho = (TH1F*)f10->Get("h_DoubleFakeShowershape_Rho");
     
     h_DoublePhoton_Nvtx = (TH1F*)f10->Get("h_DoublePhoton_Nvtx");
     h_DoubleFake_Nvtx = (TH1F*)f10->Get("h_DoubleFake_Nvtx");
     h_DoubleFakeShowershape_Nvtx = (TH1F*)f10->Get("h_DoubleFakeShowershape_Nvtx");
     
     h_DoubleElectron_NJets = (TH1F*)f10->Get("h_DoubleElectron_NJets");
     h_DoublePhoton_NJets = (TH1F*)f10->Get("h_DoublePhoton_NJets");
     h_DoubleFake_NJets = (TH1F*)f10->Get("h_DoubleFake_NJets");
     h_DoubleFakeShowershape_NJets = (TH1F*)f10->Get("h_DoubleFakeShowershape_NJets");
     
     
     
     h_DoubleElectron_DiEMPt = getOverflow(h_DoubleElectron_DiEMPt);
     h_DoubleElectron_Rho = getOverflow(h_DoubleElectron_Rho);
     h_DoubleElectron_Nvtx = getOverflow(h_DoubleElectron_Nvtx);
     //h_DoubleElectron_DiEMPt->Sumw2();
     h_DoublePhoton_DiEMPt = getOverflow(h_DoublePhoton_DiEMPt);
     h_DoubleFake_DiEMPt = getOverflow(h_DoubleFake_DiEMPt);
     h_DoubleFakeShowershape_DiEMPt = getOverflow(h_DoubleFakeShowershape_DiEMPt);
     
     h_DoublePhoton_Rho = getOverflow(h_DoublePhoton_Rho);
     h_DoubleFake_Rho = getOverflow(h_DoubleFake_Rho);
     h_DoubleFakeShowershape_Rho = getOverflow(h_DoubleFakeShowershape_Rho);
     
     h_DoublePhoton_Nvtx = getOverflow(h_DoublePhoton_Nvtx);
     h_DoubleFake_Nvtx = getOverflow(h_DoubleFake_Nvtx);
     h_DoubleFakeShowershape_Nvtx = getOverflow(h_DoubleFakeShowershape_Nvtx);
     
     h_DoubleElectron_NJets = getOverflow(h_DoubleElectron_NJets);
     h_DoublePhoton_NJets = getOverflow(h_DoublePhoton_NJets);
     h_DoubleFake_NJets = getOverflow(h_DoubleFake_NJets);
     h_DoubleFakeShowershape_NJets = getOverflow(h_DoubleFakeShowershape_NJets);
     
     
     
     
     
     h_DoublePhoton_DeltaPhi = (TH1F*)f10->Get("h_DoublePhoton_DeltaPhi");
     h_DoublePhoton_DeltaPhi_AfterDRCut = (TH1F*)f10->Get("h_DoublePhoton_DeltaPhi_AfterDRCut");
     
     h_DoublePhoton_NJet_vs_DiEMPt = (TH2F*)f10->Get("h_DoublePhoton_NJet_vs_DiEMPt");
     h_DoubleElectron_NJet_vs_DiEMPt = (TH2F*)f10->Get("h_DoubleElectron_NJet_vs_DiEMPt");
     h_DoubleFake_NJet_vs_DiEMPt = (TH2F*)f10->Get("h_DoubleFake_NJet_vs_DiEMPt");
     
     h_DoublePhoton_MET = (TH1F*)f10->Get("h_DoublePhoton_MET");
     h_DoubleElectron_MET = (TH1F*)f10->Get("h_DoubleElectron_MET");
     h_DoubleFake_MET = (TH1F*)f10->Get("h_DoubleFake_MET");
     
     h_DoublePhoton_MET = getOverflow(h_DoublePhoton_MET);
     h_DoubleElectron_MET = getOverflow(h_DoubleElectron_MET);
     h_DoubleFake_MET = getOverflow(h_DoubleFake_MET);
     
     
     TFile *Fdiempt = new TFile(OutputFolder+"/ThreeDiEMPtAndMET_ForMarc.root","RECREATE");
     h_DoubleElectron_DiEMPt->Write();
     h_DoubleFake_DiEMPt->Write();
     h_DoublePhoton_DiEMPt->Write();
     h_DoublePhoton_MET->Write();
     h_DoubleElectron_MET->Write();
     h_DoubleFake_MET->Write();
     Fdiempt->Close();
     
     //h_DoublePhoton_DiEMPt->Sumw2();
     h_DoubleElectron_DiEMPt->Scale(1.0, "width");
     Double_t y3=h_DoubleElectron_DiEMPt->Integral(0, h_DoubleElectron_DiEMPt->GetNbinsX()+1);
     h_DoubleElectron_DiEMPt->Scale(1.0/y3);
     
     h_DoublePhoton_DiEMPt->Scale(1.0, "width");
     Double_t d3=h_DoublePhoton_DiEMPt->Integral(0, h_DoublePhoton_DiEMPt->GetNbinsX()+1);
     h_DoublePhoton_DiEMPt->Scale(1.0/d3);
     
     h_DoubleFake_DiEMPt->Scale(1.0, "width");
     Double_t d4=h_DoubleFake_DiEMPt->Integral(0, h_DoubleFake_DiEMPt->GetNbinsX()+1);
     h_DoubleFake_DiEMPt->Scale(1.0/d4);
     
     h_DoubleFakeShowershape_DiEMPt->Scale(1.0, "width");
     Double_t d4A=h_DoubleFakeShowershape_DiEMPt->Integral(0, h_DoubleFakeShowershape_DiEMPt->GetNbinsX()+1);
     h_DoubleFakeShowershape_DiEMPt->Scale(1.0/d4A);
     
     
     
     h_DoubleElectron_Rho->Scale(1.0, "width");
     Double_t y4=h_DoubleElectron_Rho->Integral(0, h_DoubleElectron_Rho->GetNbinsX()+1);
     h_DoubleElectron_Rho->Scale(1.0/y4);
     
     h_DoublePhoton_Rho->Scale(1.0, "width");
     Double_t d1=h_DoublePhoton_Rho->Integral(0, h_DoublePhoton_Rho->GetNbinsX()+1);
     h_DoublePhoton_Rho->Scale(1.0/d1);
     
     h_DoubleFake_Rho->Scale(1.0, "width");
     Double_t d2=h_DoubleFake_Rho->Integral(0, h_DoubleFake_Rho->GetNbinsX()+1);
     h_DoubleFake_Rho->Scale(1.0/d2);
     
     h_DoubleFakeShowershape_Rho->Scale(1.0, "width");
     Double_t d2A=h_DoubleFakeShowershape_Rho->Integral(0, h_DoubleFakeShowershape_Rho->GetNbinsX()+1);
     h_DoubleFakeShowershape_Rho->Scale(1.0/d2A);
     
     
     
     h_DoubleElectron_Nvtx->Scale(1.0, "width");
     Double_t w4=h_DoubleElectron_Nvtx->Integral(0, h_DoubleElectron_Nvtx->GetNbinsX()+1);
     h_DoubleElectron_Nvtx->Scale(1.0/w4);
     
     h_DoublePhoton_Nvtx->Scale(1.0, "width");
     Double_t w1=h_DoublePhoton_Nvtx->Integral(0, h_DoublePhoton_Nvtx->GetNbinsX()+1);
     h_DoublePhoton_Nvtx->Scale(1.0/w1);
     
     h_DoubleFake_Nvtx->Scale(1.0, "width");
     Double_t w2=h_DoubleFake_Nvtx->Integral(0, h_DoubleFake_Nvtx->GetNbinsX()+1);
     h_DoubleFake_Nvtx->Scale(1.0/w2);
     
     h_DoubleFakeShowershape_Nvtx->Scale(1.0, "width");
     Double_t w2A=h_DoubleFakeShowershape_Nvtx->Integral(0, h_DoubleFakeShowershape_Nvtx->GetNbinsX()+1);
     h_DoubleFakeShowershape_Nvtx->Scale(1.0/w2A);
     
     
     
     h_DoubleElectron_NJets->Scale(1.0, "width");
     Double_t njet1=h_DoubleElectron_NJets->Integral(0, h_DoubleElectron_NJets->GetNbinsX()+1);
     h_DoubleElectron_NJets->Scale(1.0/njet1);
     
     h_DoublePhoton_NJets->Scale(1.0, "width");
     Double_t njet2=h_DoublePhoton_NJets->Integral(0, h_DoublePhoton_NJets->GetNbinsX()+1);
     h_DoublePhoton_NJets->Scale(1.0/njet2);
     
     h_DoubleFake_NJets->Scale(1.0, "width");
     Double_t njet3=h_DoubleFake_NJets->Integral(0, h_DoubleFake_NJets->GetNbinsX()+1);
     h_DoubleFake_NJets->Scale(1.0/njet3);
     
     h_DoubleFakeShowershape_NJets->Scale(1.0, "width");
     Double_t njet4=h_DoubleFakeShowershape_NJets->Integral(0, h_DoubleFakeShowershape_NJets->GetNbinsX()+1);
     h_DoubleFakeShowershape_NJets->Scale(1.0/njet4);
     
     
     Double_t nJetDiEMPtPhoton = h_DoublePhoton_NJet_vs_DiEMPt->Integral(0, h_DoublePhoton_NJet_vs_DiEMPt->GetNbinsX()+1);
     h_DoublePhoton_NJet_vs_DiEMPt->Scale(1.0/nJetDiEMPtPhoton);
     Double_t nJetDiEMPtElectron = h_DoubleElectron_NJet_vs_DiEMPt->Integral(0, h_DoubleElectron_NJet_vs_DiEMPt->GetNbinsX()+1);
     h_DoubleElectron_NJet_vs_DiEMPt->Scale(1.0/nJetDiEMPtElectron);
     Double_t nJetDiEMPtFake = h_DoubleFake_NJet_vs_DiEMPt->Integral(0, h_DoubleFake_NJet_vs_DiEMPt->GetNbinsX()+1);
     h_DoubleFake_NJet_vs_DiEMPt->Scale(1.0/nJetDiEMPtFake);
     
     
  }
   
   int stat0;
   stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);


   
   
   vector<Color_t> color;
   color.push_back(kGreen+3);
   color.push_back(4);
   
   vector<TH1F*> VecTH1;
   VecTH1.push_back(h_DoublePhoton_DiEMPt);
   VecTH1.push_back(h_DoubleElectron_DiEMPt);
   
   vector<TString> LegName;
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ee");
   
   TH2F *eephotondiemptnjets2D = (TH2F*)h_DoublePhoton_NJet_vs_DiEMPt->Clone("eephotondiemptnjets2D");
   eephotondiemptnjets2D->Reset();
   eephotondiemptnjets2D->SetTitle("candidate over ee, 2D");
   eephotondiemptnjets2D->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   eephotondiemptnjets2D->GetYaxis()->SetTitle("nJet");
   
   TH2F *ffphotondiemptnjets2D = (TH2F*)h_DoublePhoton_NJet_vs_DiEMPt->Clone("ffphotondiemptnjets2D");
   ffphotondiemptnjets2D->Reset();
   ffphotondiemptnjets2D->SetTitle("candidate over ff, 2D");
   ffphotondiemptnjets2D->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   ffphotondiemptnjets2D->GetYaxis()->SetTitle("nJet");
   
   eephotondiemptnjets2D->Divide(h_DoublePhoton_NJet_vs_DiEMPt, h_DoubleElectron_NJet_vs_DiEMPt);
   ffphotondiemptnjets2D->Divide(h_DoublePhoton_NJet_vs_DiEMPt, h_DoubleFake_NJet_vs_DiEMPt);
   
   
   TH1F *eephotondiempt = (TH1F*)h_DoublePhoton_DiEMPt->Clone("eephotondiempt");
   eephotondiempt->Reset();
   eephotondiempt->SetTitle("candidate over ee");
   eephotondiempt->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   eephotondiempt->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   //eephotondiempt->Sumw2();
   TH1F *ffphotondiempt = (TH1F*)h_DoubleFake_DiEMPt->Clone("ffphotondiempt");
   ffphotondiempt->Reset();
   ffphotondiempt->SetTitle("candidate over ff");
   ffphotondiempt->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   ffphotondiempt->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   TH1F *ffshowershapephotondiempt = (TH1F*)h_DoubleFakeShowershape_DiEMPt->Clone("ffshowershapephotondiempt");
   ffshowershapephotondiempt->Reset();
   ffshowershapephotondiempt->SetTitle("candidate over ff");
   ffshowershapephotondiempt->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   ffshowershapephotondiempt->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   
   TH1F *eephotonnjets = (TH1F*)h_DoublePhoton_NJets->Clone("eephotonnjets");
   eephotonnjets->Reset();
   eephotonnjets->SetTitle("candidate over ee");
   eephotonnjets->GetXaxis()->SetTitle("N_{jets}");
   eephotonnjets->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   TH1F *ffphotonnjets = (TH1F*)h_DoubleFake_NJets->Clone("ffphotonnjets");
   ffphotonnjets->Reset();
   ffphotonnjets->SetTitle("candidate over ff");
   ffphotonnjets->GetXaxis()->SetTitle("N_{jets}");
   ffphotonnjets->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   TH1F *ffshowershapephotonnjets = (TH1F*)h_DoubleFakeShowershape_NJets->Clone("ffshowershapephotonnjets");
   ffshowershapephotonnjets->Reset();
   ffshowershapephotonnjets->SetTitle("candidate over ff");
   ffshowershapephotonnjets->GetXaxis()->SetTitle("N_{jets}");
   ffshowershapephotonnjets->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   
   //ffphotondiempt->Sumw2();
   TH1F *eephotonrho = (TH1F*)h_DoublePhoton_Rho->Clone("eephotonrho");
   eephotonrho->Reset();
   eephotonrho->SetTitle("candidate over ee");
   eephotonrho->GetXaxis()->SetTitle("#rho");
   eephotonrho->GetYaxis()->SetTitle("#gamma#gamma/ee");
   //eephotonrho->Sumw2();
   TH1F *ffphotonrho = (TH1F*)h_DoubleFake_Rho->Clone("ffphotonrho");
   ffphotonrho->Reset();
   ffphotonrho->SetTitle("candidate over ff");
   ffphotonrho->GetXaxis()->SetTitle("#rho");
   ffphotonrho->GetYaxis()->SetTitle("#gamma#gamma/ff");
   
   TH1F *ffshowershapephotonrho = (TH1F*)h_DoubleFakeShowershape_Rho->Clone("ffshowershapephotonrho");
   ffshowershapephotonrho->Reset();
   ffshowershapephotonrho->SetTitle("candidate over ff");
   ffshowershapephotonrho->GetXaxis()->SetTitle("#rho");
   ffshowershapephotonrho->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //ffphotonrho->Sumw2();
   
   
   eephotondiempt->Divide(h_DoublePhoton_DiEMPt, h_DoubleElectron_DiEMPt);
   ffphotondiempt->Divide(h_DoublePhoton_DiEMPt, h_DoubleFake_DiEMPt);
   ffshowershapephotondiempt->Divide(h_DoublePhoton_DiEMPt, h_DoubleFakeShowershape_DiEMPt);
   
   eephotonnjets->Divide(h_DoublePhoton_NJets, h_DoubleElectron_NJets);
   ffphotonnjets->Divide(h_DoublePhoton_NJets, h_DoubleFake_NJets);
   ffshowershapephotonnjets->Divide(h_DoublePhoton_NJets, h_DoubleFakeShowershape_NJets);
   
   eephotonrho->Divide(h_DoublePhoton_Rho, h_DoubleElectron_Rho);
   ffphotonrho->Divide(h_DoublePhoton_Rho, h_DoubleFake_Rho);
   ffshowershapephotonrho->Divide(h_DoublePhoton_Rho, h_DoubleFakeShowershape_Rho);
   
   
   TH1F *hRatio = (TH1F*)h_DoublePhoton_DiEMPt->Clone("hRatio");
   hRatio->Reset();
   hRatio->SetTitle("candidate over ee");
   hRatio->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatio->GetYaxis()->SetTitle("Ratio");
   //hRatio->Sumw2();
   
   int xlow(0), xup(400);
   std::string strpt = std::to_string(pt);
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ee_photon_mc_diEMPt"+strpt, hRatio, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ee_photon_mc_diEMPt_Logy"+strpt, hRatio, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ee_photon_data_RunD_diEMPt"+strpt, hRatio, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ee_photon_data_RunD_diEMPt_Logy"+strpt, hRatio, 1, 1, true, true);
     DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.00002, 0.30, OutputFolder+"/ee_photon_data_RunD_diEMPt_ZOOMED"+strpt, hRatio, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, 100, 0.00002, 0.30, OutputFolder+"/ee_photon_data_RunD_diEMPt_ZOOMED_Logy"+strpt, hRatio, 1, 1, true, true);
  }
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(4);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Rho);
   VecTH1.push_back(h_DoubleElectron_Rho);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma #rho");
   LegName.push_back("ee #rho");
   
   TH1F *hRatio2 = (TH1F*)h_DoublePhoton_Rho->Clone("hRatio2");
   hRatio2->Reset();
   hRatio2->SetTitle("candidate over ee");
   hRatio2->GetXaxis()->SetTitle("#rho");
   hRatio2->GetYaxis()->SetTitle("#gamma#gamma/ee");
   //hRatio2->Sumw2();
   if(!data)
   {
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_mc_rho"+strpt, hRatio2, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_mc_rho_Logy"+strpt, hRatio2, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_data_RunD_rho"+strpt, hRatio2, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_data_RunD_rho_Logy"+strpt, hRatio2, 1, 1, true, true);
  }
  
  
  
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DeltaPhi);
   LegName.clear();
   LegName.push_back("#gamma#gamma #Delta#phi");
   DrawHists(VecTH1, LegName, color, 0, 3.2, 1, pow(10, 4), OutputFolder+"/doublephoton_DeltaPhi_Logy"+strpt, 0, 0, false, true);
   DrawHists(VecTH1, LegName, color, 0, 3.2, 1, pow(10, 4), OutputFolder+"/doublephoton_DeltaPhi"+strpt, 0, 0, false, false);
   
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DeltaPhi_AfterDRCut);
   LegName.clear();
   LegName.push_back("#gamma#gamma #Delta#phi");
   DrawHists(VecTH1, LegName, color, 0, 3.2, 1, pow(10, 4), OutputFolder+"/doublePhoton_DeltaPhi_AfterDRCut_Logy"+strpt, 0, 0, false, true);
   DrawHists(VecTH1, LegName, color, 0, 3.2, 1, pow(10, 4), OutputFolder+"/doublephoton_DeltaPhi_AfterDRCut"+strpt, 0, 0, false, false);
  
   color.clear();
   color.push_back(kBlack);
   color.push_back(4);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Rho);
   VecTH1.push_back(h_DoubleElectron_Rho);
   VecTH1.push_back(h_DoubleFake_Rho);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma #rho");
   LegName.push_back("ee #rho");
   LegName.push_back("ff #rho");
   
   //hRatio2->Sumw2();
   if(!data)
   {
     DrawHists(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_ee_mc_rho"+strpt, 1, 1, true, false);
     DrawHists(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_ee_mc_rho_Logy"+strpt, 1, 1, true, true);
   }
   else{
     DrawHists(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_ee_data_RunD_rho"+strpt, 1, 1, true, false);
     DrawHists(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_ee_data_RunD_rho_Logy"+strpt, 1, 1, true, true);
  }
  
  
  
  
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Rho);
   VecTH1.push_back(h_DoubleFake_Rho);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma #rho");
   LegName.push_back("ff #rho");
   
   TH1F *hRatio3 = (TH1F*)h_DoublePhoton_Rho->Clone("hRatio3");
   hRatio3->Reset();
   hRatio3->SetTitle("candidate over ff");
   hRatio3->GetXaxis()->SetTitle("#rho");
   hRatio3->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio3->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_mc_rho"+strpt, hRatio3, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_mc_rho_Logy"+strpt, hRatio3, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_data_RunD_rho"+strpt, hRatio3, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_data_RunD_rho_Logy"+strpt, hRatio3, 1, 1, true, true);
   }
   
   
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Rho);
   VecTH1.push_back(h_DoubleFakeShowershape_Rho);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma #rho");
   LegName.push_back("ff #rho");
   
   TH1F *hRatio3B = (TH1F*)h_DoublePhoton_Rho->Clone("hRatio3B");
   hRatio3B->Reset();
   hRatio3B->SetTitle("candidate over ff");
   hRatio3B->GetXaxis()->SetTitle("#rho");
   hRatio3B->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio3->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_mc_rho"+strpt, hRatio3B, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_mc_rho_Logy"+strpt, hRatio3B, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_data_RunD_rho"+strpt, hRatio3B, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_data_RunD_rho_Logy"+strpt, hRatio3B, 1, 1, true, true);
   }
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(4);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Nvtx);
   VecTH1.push_back(h_DoubleElectron_Nvtx);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma nvtx");
   LegName.push_back("ee nvtx");
   
   TH1F *hRatio2A = (TH1F*)h_DoublePhoton_Nvtx->Clone("hRatio2A");
   hRatio2A->Reset();
   hRatio2A->SetTitle("candidate over ee");
   hRatio2A->GetXaxis()->SetTitle("nvtx");
   hRatio2A->GetYaxis()->SetTitle("#gamma#gamma/ee");
   //hRatio2A->Sumw2();
   if(!data)
   {
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_mc_nvtx"+strpt, hRatio2A, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_mc_nvtx_Logy"+strpt, hRatio2A, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ee_photon_data_RunD_nvtx"+strpt, hRatio2A, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002,0.50, OutputFolder+"/ee_photon_data_RunD_nvtx_Logy"+strpt, hRatio2A, 1, 1, true, true);
  }
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Nvtx);
   VecTH1.push_back(h_DoubleFake_Nvtx);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma nvtx");
   LegName.push_back("ff nvtx");
   
   TH1F *hRatio3A = (TH1F*)h_DoublePhoton_Nvtx->Clone("hRatio3A");
   hRatio3A->Reset();
   hRatio3A->SetTitle("candidate over ff");
   hRatio3A->GetXaxis()->SetTitle("nvtx");
   hRatio3A->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio3A->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_mc_nvtx"+strpt, hRatio3A, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_mc_nvtx_Logy"+strpt, hRatio3A, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_data_RunD_nvtx"+strpt, hRatio3A, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ff_photon_data_RunD_nvtx_Logy"+strpt, hRatio3A, 1, 1, true, true);
   }
   
   
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_Nvtx);
   VecTH1.push_back(h_DoubleFakeShowershape_Nvtx);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma nvtx");
   LegName.push_back("ff nvtx");
   
   TH1F *hRatio3C = (TH1F*)h_DoublePhoton_Nvtx->Clone("hRatio3C");
   hRatio3C->Reset();
   hRatio3C->SetTitle("candidate over ff");
   hRatio3C->GetXaxis()->SetTitle("nvtx");
   hRatio3C->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio3A->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_mc_nvtx"+strpt, hRatio3C, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_mc_nvtx_Logy"+strpt, hRatio3C, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_data_RunD_nvtx"+strpt, hRatio3C, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 40, 0.00002, 0.50, OutputFolder+"/ffshowershape_photon_data_RunD_nvtx_Logy"+strpt, hRatio3C, 1, 1, true, true);
   }
   
   
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DiEMPt);
   VecTH1.push_back(h_DoubleFake_DiEMPt);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ff");
   
   TH1F *hRatio4 = (TH1F*)h_DoublePhoton_DiEMPt->Clone("hRatio4");
   hRatio4->Reset();
   hRatio4->SetTitle("candidate over ff");
   hRatio4->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatio4->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_mc_diempt"+strpt, hRatio4, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_mc_diempt_Logy"+strpt, hRatio4, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_data_RunD_diempt"+strpt, hRatio4, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_data_RunD_diempt_Logy"+strpt, hRatio4, 1, 1, true, true);
     DrawHistsRatio(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_data_RunD_diempt_ZOOMED"+strpt, hRatio4, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_data_RunD_diempt_ZOOMED_Logy"+strpt, hRatio4, 1, 1, true, true);
   }
   
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(4);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DiEMPt);
   VecTH1.push_back(h_DoubleElectron_DiEMPt);
   VecTH1.push_back(h_DoubleFake_DiEMPt);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ee");
   LegName.push_back("ff");
   
   TH1F *hRatioQ = (TH1F*)h_DoubleElectron_DiEMPt->Clone("hRatioQ");
   hRatioQ->Reset();
   hRatioQ->SetTitle("");
   hRatioQ->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatioQ->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   TH1F *hRatioR = (TH1F*)h_DoubleElectron_DiEMPt->Clone("hRatioR");
   hRatioR->Reset();
   hRatioR->SetTitle("");
   hRatioR->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatioR->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_ratio_RunD_diempt_"+strpt, hRatioQ, hRatioR, 1, 1, true, false);
   DrawHistsRatioTwoRatioLowerLegend(VecTH1, LegName, color, xlow, 600, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_ratio_RunD_diempt_Logy"+strpt, hRatioQ, hRatioR, 1, 1, true, true);
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_ratio_RunD_diempt_ZOOMED"+strpt, hRatioQ, hRatioR, 1, 1, true, false);
   DrawHistsRatioTwoLowerLegend(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_ratio_RunD_diempt_ZOOMED_Logy"+strpt, hRatioQ, hRatioR, 1, 1, true, true);
   
   
   
   
   
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_NJets);
   VecTH1.push_back(h_DoubleElectron_NJets);
   VecTH1.push_back(h_DoubleFake_NJets);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ee");
   LegName.push_back("ff");
   
   TH1F *hRatioJet1 = (TH1F*)h_DoubleElectron_NJets->Clone("hRatioJet1");
   hRatioJet1->Reset();
   hRatioJet1->SetTitle("");
   hRatioJet1->GetXaxis()->SetTitle("N_{jets}");
   hRatioJet1->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   TH1F *hRatioJet2 = (TH1F*)h_DoubleElectron_NJets->Clone("hRatioJet2");
   hRatioJet2->Reset();
   hRatioJet2->SetTitle("");
   hRatioJet2->GetXaxis()->SetTitle("N_{jets}");
   hRatioJet2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ff_photon_ee_data_ratio_RunD_NJets"+strpt, hRatioJet1, hRatioJet2, 1, 1, true, false);
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ff_photon_ee_data_ratio_RunD_NJets_Logy"+strpt, hRatioJet1, hRatioJet2, 1, 1, true, true);
   
   
   
   
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_NJets);
   VecTH1.push_back(h_DoubleElectron_NJets);
   VecTH1.push_back(h_DoubleFakeShowershape_NJets);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ee");
   LegName.push_back("ff");
   
   TH1F *hRatioJet11 = (TH1F*)h_DoubleElectron_NJets->Clone("hRatioJet11");
   hRatioJet11->Reset();
   hRatioJet11->SetTitle("");
   hRatioJet11->GetXaxis()->SetTitle("N_{jets}");
   hRatioJet11->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   TH1F *hRatioJet21 = (TH1F*)h_DoubleElectron_NJets->Clone("hRatioJet21");
   hRatioJet21->Reset();
   hRatioJet21->SetTitle("");
   hRatioJet21->GetXaxis()->SetTitle("N_{jets}");
   hRatioJet21->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_NJets"+strpt, hRatioJet11, hRatioJet21, 1, 1, true, false);
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 10, 0.00002, 1.00, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_NJets_Logy"+strpt, hRatioJet11, hRatioJet21, 1, 1, true, true);
   
  
     
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(4);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DiEMPt);
   VecTH1.push_back(h_DoubleElectron_DiEMPt);
   VecTH1.push_back(h_DoubleFakeShowershape_DiEMPt);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ee");
   LegName.push_back("ff");
   
   TH1F *hRatioQ2 = (TH1F*)h_DoubleElectron_DiEMPt->Clone("hRatioQ2");
   hRatioQ2->Reset();
   hRatioQ2->SetTitle("");
   hRatioQ2->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatioQ2->GetYaxis()->SetTitle("#gamma#gamma/ee");
   
   TH1F *hRatioR2 = (TH1F*)h_DoubleElectron_DiEMPt->Clone("hRatioR2");
   hRatioR2->Reset();
   hRatioR2->SetTitle("");
   hRatioR2->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatioR2->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_diempt_"+strpt, hRatioQ2, hRatioR2, 1, 1, true, false);
   DrawHistsRatioTwo(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_diempt_Logy"+strpt, hRatioQ2, hRatioR2, 1, 1, true, true);
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_diempt_ZOOMED"+strpt, hRatioQ2, hRatioR2, 1, 1, true, false);
   DrawHistsRatioTwo(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_ee_data_ratio_RunD_diempt_ZOOMED_Logy"+strpt, hRatioQ2, hRatioR2, 1, 1, true, true);
   
   
   
   
//    color.clear();
//    color.push_back(kBlack);
//    color.push_back(4);
//    color.push_back(2);
//    
//    VecTH1.clear();
//    VecTH1.push_back(h_DoublePhoton_DiEMPt);
//    VecTH1.push_back(h_DoubleElectron_DiEMPt);
//    VecTH1.push_back(h_DoubleFake_DiEMPt);
//    
//    LegName.clear();
//    LegName.push_back("#gamma#gamma");
//    LegName.push_back("ee");
//    LegName.push_back("ff");
//    
//    //hRatio4->Sumw2();
//    if(!data){
//      DrawHists(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_mc_diempt"+strpt, 1, 1, true, false);
//      DrawHists(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_mc_diempt_Logy"+strpt, 1, 1, true, true);
//    }
//    else{
//      DrawHists(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_RunD_diempt"+strpt, 1, 1, true, false);
//      DrawHists(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_RunD_diempt_Logy"+strpt, 1, 1, true, true);
//      DrawHists(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_RunD_diempt_ZOOMED"+strpt, 1, 1, true, false);
//      DrawHists(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ff_photon_ee_data_RunD_diempt_ZOOMED_Logy"+strpt, 1, 1, true, true);
//    }
   
   
   
   
   color.clear();
   color.push_back(kBlack);
   color.push_back(2);
   
   VecTH1.clear();
   VecTH1.push_back(h_DoublePhoton_DiEMPt);
   VecTH1.push_back(h_DoubleFakeShowershape_DiEMPt);
   
   LegName.clear();
   LegName.push_back("#gamma#gamma");
   LegName.push_back("ff");
   
   TH1F *hRatio4C = (TH1F*)h_DoublePhoton_DiEMPt->Clone("hRatio4C");
   hRatio4C->Reset();
   hRatio4C->SetTitle("candidate over ff");
   hRatio4C->GetXaxis()->SetTitle("di-EM p_{T} (GeV)");
   hRatio4C->GetYaxis()->SetTitle("#gamma#gamma/ff");
   //hRatio4->Sumw2();
   if(!data){
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_mc_diempt"+strpt, hRatio4C, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_mc_diempt_Logy"+strpt, hRatio4C, 1, 1, true, true);
   }
   else{
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_data_RunD_diempt"+strpt, hRatio4C, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, xlow, xup, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_data_RunD_diempt_Logy"+strpt, hRatio4C, 1, 1, true, true);
     DrawHistsRatio(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_data_RunD_diempt_ZOOMED"+strpt, hRatio4C, 1, 1, true, false);
     DrawHistsRatio(VecTH1, LegName, color, 0, 100, 0.00002, 0.30, OutputFolder+"/ffshowershape_photon_data_RunD_diempt_ZOOMED_Logy"+strpt, hRatio4C, 1, 1, true, true);
   }
   
   
   // 2D ratio plots
   
   
   vector<TH2F*> vecTH2;
   vecTH2.push_back(eephotondiemptnjets2D);
   Draw2DHists(vecTH2, "di-EM p_{T} (GeV)", "N_{jets}", "#gamma#gamma/ee", xlow, xup, 0, 8, 0.5, 7.0, OutputFolder+"/RatioPlot2D_DiEMPtVsNJets_Electron", false);
   Draw2DHists(vecTH2, "di-EM p_{T} (GeV)", "N_{jets}", "#gamma#gamma/ee", xlow, xup, 0, 8, 0.5, 35.0, OutputFolder+"/RatioPlot2D_DiEMPtVsNJets_Electron_Logz", true);
   
   
   TFile *fout = 0;
   /// for Data_RunD ///
   if(pt == 40 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/DIEMPtRatio40.root","RECREATE");
   if(pt == 50 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/DIEMPtRatio50.root","RECREATE");
   /// for 50ns data ///
   /*if(pt == 40 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/DIEMPtRatio40.root","RECREATE");
   if(pt == 50 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/DIEMPtRatio50.root","RECREATE");*/
   ///for montecarlo ///
   if(pt == 40 && !data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/DIEMPtRatio40.root","RECREATE");
   if(pt == 50 && !data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/DIEMPtRatio50.root","RECREATE");
   fout->cd();
   
   eephotondiempt->Write();
   ffphotondiempt->Write();
   ffshowershapephotondiempt->Write();
   
   eephotonrho->Write();
   ffphotonrho->Write();
   ffshowershapephotonrho->Write();
   
   eephotonnjets->Write();
   ffphotonnjets->Write();
   ffshowershapephotonnjets->Write();
   
   eephotondiemptnjets2D->Write();
   ffphotondiemptnjets2D->Write();
   
   if(data)f10->Close();
   else{
     f8->Close();
     f9->Close();
   }
   fout->Close();
}