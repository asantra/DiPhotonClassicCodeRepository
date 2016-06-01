#include <TGraphErrors.h>
#include <TMath.h>
#include <TAttFill.h>
#include <TFile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TCanvas.h>
#include <TPad.h> 
#include <THStack.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TLatex.h>
#include <sys/stat.h>
#include <fstream>
#include "/home/arka/arka/include/MyFunction.h"

void TexMakerSecond(TLatex *&tex1, TLatex *&tex2, TLatex *&tex3){
  tex1 = new TLatex(0.85,0.963,"2.3 fb^{-1} (13 TeV)");
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.042);
  tex1->SetLineWidth(2);
  //tex1->Draw();
  tex2 = new TLatex(0.18,0.996,"CMS");//(0.15,0.88,"CMS");
  tex2->SetNDC();
  tex2->SetTextAlign(13);
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.05);
  tex2->SetLineWidth(1);
  
  tex3 = new TLatex(0.30,0.993,"Preliminary");//(0.15,0.84,"Simulation")
  tex3->SetNDC();
  tex3->SetTextAlign(13);
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.05);
  tex3->SetLineWidth(1);
  
}

void DrawAsymErrorFakeRate(bool analysisFake){
  TString OutputFolder="";
  if(analysisFake)OutputFolder="Data_RunD_Ratio_AnalysisFake_217fb";
  else OutputFolder="Data_RunD_Ratio_ExtendedFake_217fb";
  
  
  int stat0;
  stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  
  int xlow(0),xup(300);
  
  TFile *F22 = 0;
  if(analysisFake)F22= new TFile("Data_RunD_All_AnalysisFake_217fb.root","READ");
  else F22= new TFile("Data_RunD_All_ExtendedFake_217fb.root","READ");
  
  TH1F *h_Scaled_ElectronPhoton_MET       = (TH1F*)F22->Get("h_Scaled_ElectronPhoton_MET");
  TH1F *h_Scaled_ElectronPhoton_MET_Up = (TH1F*)F22->Get("h_Scaled_ElectronPhoton_MET_Up");
  TH1F *h_Scaled_ElectronPhoton_MET_Down  = (TH1F*)F22->Get("h_Scaled_ElectronPhoton_MET_Down");
  
  cout << "h_Scaled_ElectronPhoton_MET last bin: " << h_Scaled_ElectronPhoton_MET->GetBinContent(h_Scaled_ElectronPhoton_MET->GetNbinsX()) << endl;
  cout << "h_Scaled_ElectronPhoton_MET last bin error: " << h_Scaled_ElectronPhoton_MET->GetBinError(h_Scaled_ElectronPhoton_MET->GetNbinsX()) << endl;
  cout << "h_Scaled_ElectronPhoton_MET overflow bin: " << h_Scaled_ElectronPhoton_MET->GetBinContent(h_Scaled_ElectronPhoton_MET->GetNbinsX()+1) << endl;
  cout << "h_Scaled_ElectronPhoton_MET overflow bin error: " << h_Scaled_ElectronPhoton_MET->GetBinError(h_Scaled_ElectronPhoton_MET->GetNbinsX()+1) << endl;
  
  h_Scaled_ElectronPhoton_MET = getOverflow(h_Scaled_ElectronPhoton_MET);
  h_Scaled_ElectronPhoton_MET_Up = getOverflow(h_Scaled_ElectronPhoton_MET_Up);
  h_Scaled_ElectronPhoton_MET_Down = getOverflow(h_Scaled_ElectronPhoton_MET_Down);
  
  cout << "h_Scaled_ElectronPhoton_MET last bin: " << h_Scaled_ElectronPhoton_MET->GetBinContent(h_Scaled_ElectronPhoton_MET->GetNbinsX()) << endl;
  cout << "h_Scaled_ElectronPhoton_MET last bin error: " << h_Scaled_ElectronPhoton_MET->GetBinError(h_Scaled_ElectronPhoton_MET->GetNbinsX()) << endl;
  cout << "h_Scaled_ElectronPhoton_MET overflow bin: " << h_Scaled_ElectronPhoton_MET->GetBinContent(h_Scaled_ElectronPhoton_MET->GetNbinsX()+1) << endl;
  cout << "h_Scaled_ElectronPhoton_MET overflow bin error: " << h_Scaled_ElectronPhoton_MET->GetBinError(h_Scaled_ElectronPhoton_MET->GetNbinsX()+1) << endl;
  
  TH1F* h_met_EWK_error = (TH1F*)h_Scaled_ElectronPhoton_MET->Clone("h_met_EWK_error");
  h_met_EWK_error->Reset();
  TH1F* g2 = (TH1F*)h_Scaled_ElectronPhoton_MET->Clone("g2");
  g2->Reset();
  
  const int arraySize = h_Scaled_ElectronPhoton_MET->GetNbinsX();
  double metvalue[arraySize];//                         = {0};
  double metvalueup[arraySize];//                       = {0};
  double metvaluedown[arraySize];//                     = {0};
  double metvalueerror[arraySize];//                    = {0};
  double errorup[arraySize];//                          = {0};
  double errordown[arraySize];//                        = {0};
  double totalerror[arraySize];//                       = {0};
  double errfake100(0), errstat100(0), metcount(0);
  int bin100 = h_Scaled_ElectronPhoton_MET->FindBin(100);
  for(int j=0 ; j < h_Scaled_ElectronPhoton_MET->GetNbinsX() ; ++j){
    metvalue[j] =  h_Scaled_ElectronPhoton_MET->GetBinContent(j+1);
    metvalueup[j] = h_Scaled_ElectronPhoton_MET_Up->GetBinContent(j+1);
    metvaluedown[j] = h_Scaled_ElectronPhoton_MET_Down->GetBinContent(j+1);
    metvalueerror[j] =  h_Scaled_ElectronPhoton_MET->GetBinError(j+1);
   
    errorup[j]   = fabs(metvalueup[j]-metvalue[j]);
    errordown[j]= fabs(metvalue[j]-metvaluedown[j]); 
    
    totalerror[j] = sqrt((errorup[j]+errordown[j])*(errorup[j]+errordown[j])+(metvalueerror[j])*(metvalueerror[j]));
    if((j+1)>=bin100){
      errfake100 += (errorup[j]+errordown[j])*(errorup[j]+errordown[j]);
      errstat100 +=(metvalueerror[j])*(metvalueerror[j]);
      metcount += metvalue[j];
      cout << "+++++++++++++++++++++++++++++++++++++ bin: " << j+1 << " +++++++++++++++++++++" << endl;
      cout << "EWK background :" << metvalue[j] << " and uncertainty: " << totalerror[j] << endl;
      cout << "error from fake rate: " << sqrt((errorup[j]+errordown[j])*(errorup[j]+errordown[j])) << endl;
      cout << "Fractional error from fake rate: " << sqrt((errorup[j]+errordown[j])*(errorup[j]+errordown[j]))*100/metvalue[j] << "%" << endl;
      cout << "statistical error: " << sqrt((metvalueerror[j])*(metvalueerror[j])) << endl;
      cout << "fractional error: " << sqrt((metvalueerror[j])*(metvalueerror[j]))*100/metvalue[j] << "%" << endl;
      
    }
    h_met_EWK_error->SetBinContent(j+1, metvalue[j]);
    h_met_EWK_error->SetBinError(j+1, totalerror[j]);
    
    g2->SetBinContent(j+1, metvalue[j]);
    g2->SetBinError(j+1, sqrt((errorup[j]+errordown[j])*(errorup[j]+errordown[j])));

  }  

  
  cout << "error from fake rate MET>100:" << sqrt(errfake100) <<endl;
  cout << "error from stat MET>100:" << sqrt(errstat100) <<endl;
  cout << "total EWK MET count in signal region: "<< metcount << endl;
  cout << "EWK fractional error: " << sqrt(errfake100)/metcount << endl;

  TFile* fout2 = new TFile(OutputFolder+"/ErrorCorEWK_SymPt.root","RECREATE");
  fout2->cd();
  
  h_met_EWK_error->Scale(1.0, "width");
  h_met_EWK_error->Draw();
  
  TCanvas *T = new TCanvas("T","Comparison",900,900);
  T->SetLogy();
  gStyle->SetOptStat(0);
  h_met_EWK_error->GetXaxis()->SetRangeUser(xlow,xup);
  g2->GetXaxis()->SetRangeUser(xlow,xup);
  g2->SetLineColor(kGray);
  g2->SetFillStyle(1001);
  g2->SetFillColor(kGray);
  g2->SetMarkerColor(kGray);
  
  TLegend *leg2 = new TLegend(0.5,0.6,0.95,0.95); // cms wants 0.5,0.6,0.9,0.9
  leg2->SetFillColor(kWhite);
  leg2->SetTextFont(42); // cms wants 42
  leg2->SetBorderSize(0);
  leg2->SetShadowColor(kWhite);
  leg2->SetFillStyle(0);
  leg2->AddEntry(g2, "uncertainty from fake rate", "F");
  leg2->AddEntry(h_met_EWK_error, "total uncertainty","lep");
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.02);
  
//   TLegend *leg3 = new TLegend(0.9, 0.6, 0.6, 0.9);
//   leg3->AddEntry(g2, "error from mis-identification rate", "F");
//   leg3->AddEntry(h_met_EWK_error, "stat#oplus error from mis-identification rate","lep");
//   leg3->SetFillColor(0);
//   leg3->SetTextSize(0.025);
  
  TLatex *tex1, *tex2, *tex3;
  TexMakerSecond(tex1, tex2, tex3);
  
  g2->Scale(1.0, "width");
  g2->SetTitle("");
  g2->GetYaxis()->SetTitle("Events/GeV");
  g2->GetYaxis()->SetTitleSize(0.06);
  g2->Draw("e2");
  g2->GetXaxis()->SetLabelSize(0.05);
  g2->GetXaxis()->SetTitleOffset(0.93);
  g2->GetXaxis()->SetTitleSize(0.065);
  g2->GetYaxis()->SetLabelSize(0.05);
  h_met_EWK_error->Draw("same");
  leg2->Draw("same");
  tex1->Draw();
  tex2->Draw();
  tex3->Draw();
  T->SaveAs(OutputFolder+"/EWKBackground_Symmetric.eps");
  T->SaveAs(OutputFolder+"/EWKBackground_Symmetric.pdf");
  T->SaveAs(OutputFolder+"/EWKBackground_Symmetric.png");
  
  
  h_met_EWK_error->Write();
  g2->Write();
  F22->Close();
  fout2->Close();
  

}
