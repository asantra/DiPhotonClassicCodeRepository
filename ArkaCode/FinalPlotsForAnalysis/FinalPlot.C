#include <TH1.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
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
#include <TLatex.h>
#include <TLine.h>
#include <sys/stat.h>
#include "/home/arka/arka/include/MyFunction.h"

void FinalTexMaker(TLatex *&tex1, TLatex *&tex2, TLatex *&tex3){
  tex1 = new TLatex(0.88,0.963,"2.3 fb^{-1} (13 TeV)");
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
  
  tex3 = new TLatex(0.25,0.993,"Preliminary");//(0.15,0.84,"Simulation")
  tex3->SetNDC();
  tex3->SetTextAlign(13);
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.05);
  tex3->SetLineWidth(1);
  //tex2->Draw();
  
}


void FinalPlot(bool analysisFake){  

  
        TString OutputFolder="";
	if(analysisFake)OutputFolder="Data_RunD_Ratio_AnalysisFake_217fb";
	else OutputFolder="Data_RunD_Ratio_ExtendedFake_217fb";
	
        int stat0;
        stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	int xlow(0),xup(300);
	
	THStack *hs = new THStack("hs","QCD and EWK E_{T}^{miss} with candidate histograms");
	TFile *f = 0;
	if(analysisFake)f = new TFile("Data_RunD_All_AnalysisFake_217fb.root", "READ");
	else f = new TFile("Data_RunD_All_ExtendedFake_217fb.root", "READ");
	
	TFile *fsig1 = new TFile("/home/arka/arka/ggNtuples_Phys14/QCD_Closure/SignalAcceptanceNewestNtuples/SignalSampleNtuple/SignalPoint_mGlu_1400_mNeu_600.root", "READ");
	TFile *fsig2 = new TFile("/home/arka/arka/ggNtuples_Phys14/QCD_Closure/SignalAcceptanceNewestNtuples/SignalSampleNtuple/SignalPoint_mGlu_1600_mNeu_600.root", "READ");
	
	TH1F *h_DoublePhoton_Signal_MET1400 = (TH1F*)fsig1->Get("h_DoublePhoton_Signal_MET");
	h_DoublePhoton_Signal_MET1400 = getOverflow(h_DoublePhoton_Signal_MET1400);
	
	
	TH1F *h_DoublePhoton_Signal_MET1600 = (TH1F*)fsig2->Get("h_DoublePhoton_Signal_MET");
	h_DoublePhoton_Signal_MET1600 = getOverflow(h_DoublePhoton_Signal_MET1600);
	
        TH1F *h_DoublePhoton_MET    = (TH1F*)f->Get("h_DoublePhoton_MET");
	int lastBinData = h_DoublePhoton_MET->GetNbinsX();
	
	h_DoublePhoton_MET = getOverflow(h_DoublePhoton_MET);
	
	
	
	h_DoublePhoton_MET->Scale(1.0, "width");
	//cout << "Integral:" << h_DoublePhoton_Signal_MET1600->Integral(20,24) << endl;
	//cout << "Integral Last bin:" << h_DoublePhoton_Signal_MET1600->Integral(23,24) << endl;
	h_DoublePhoton_Signal_MET1400->Scale(1.0, "width");
	h_DoublePhoton_Signal_MET1600->Scale(1.0, "width");
	
	TFile *FQCD = new TFile(OutputFolder+"/QCD_Background.root", "READ");
	TH1F *h_met_QCD_error          = (TH1F*)FQCD->Get("h_DoubleElectron_MET_Reweighted_OnlyDiEMPt");
	
	TFile *FEWK = new TFile(OutputFolder+"/ErrorCorEWK_SymPt.root", "READ");
        TH1F *h_met_EWK_error          = (TH1F*)FEWK->Get("h_met_EWK_error");
	
	
        TH1F *h_met_error              = (TH1F*)h_DoublePhoton_MET->Clone("h_met_error");
	h_met_error->Reset();
	
	
        double toterr = 0;
	double totqcderr = 0;
	double totewkerr = 0;
	double totmet = 0;
	int bin100 = h_DoublePhoton_MET->FindBin(100);
	
        for(int k=0; k<h_DoublePhoton_MET->GetNbinsX(); ++k){
          double x  = h_met_QCD_error->GetBinContent(k+1);
          double x1 = h_met_QCD_error->GetBinError(k+1);
          double d  = h_met_EWK_error->GetBinContent(k+1);
          double d2 = h_met_EWK_error->GetBinError(k+1);
          double y  = x + d;
          double y1 = sqrt(x1*x1+d2*d2);
	  double cand = h_DoublePhoton_MET->GetBinContent(k+1);
	  if((k+1)>=bin100){
	    toterr += y1*y1;
	    totqcderr += x1*x1;
	    totewkerr += d2*d2;
	    totmet += y;
	  }
	  h_met_error->SetBinContent(k+1, y);
          h_met_error->SetBinError(k+1, y1); // only y1
        }
        cout << "total error after 100: " << sqrt(toterr) << endl;
	cout << "total ewk+qcd met >100: " << totmet << endl;
	cout << "total qcd error after 100: " << sqrt(totqcderr) << endl;
	cout << "total ewk error after 100: " << sqrt(totewkerr) << endl;
	
	TLatex *tex1, *tex2, *tex3;
	FinalTexMaker(tex1, tex2, tex3);
  
	h_met_EWK_error->SetFillColor(kAzure-2);
	h_met_EWK_error->SetLineColor(kAzure-2);
	hs->Add(h_met_EWK_error);

	h_met_QCD_error->SetFillColor(kRed+1);
	h_met_QCD_error->SetLineColor(kRed+1);
	hs->Add(h_met_QCD_error);

        h_met_error->SetFillColor(kOrange);
	h_met_error->SetLineColor(kOrange);
	h_met_error->SetFillStyle(3013);

        //hs.Add(h_met_QCD_plus_EWK);
	h_met_EWK_error->GetXaxis()->SetRangeUser(xlow, xup);
	h_met_EWK_error->GetYaxis()->SetTitleOffset(0.7);
        h_met_EWK_error->GetYaxis()->SetTitleSize(0.060);
	h_met_EWK_error->GetYaxis()->SetLabelSize(0.075);
	
        //h_met_QCD_subtract_error->SetFillColor(kRed);
	
	h_DoublePhoton_Signal_MET1400->SetMarkerStyle(kFullTriangleUp);
	h_DoublePhoton_Signal_MET1400->SetLineColor(kMagenta);
	h_DoublePhoton_Signal_MET1400->SetMarkerColor(kMagenta);
	
	h_DoublePhoton_Signal_MET1600->SetMarkerStyle(kFullDiamond);
	h_DoublePhoton_Signal_MET1600->SetLineColor(kCyan);
	h_DoublePhoton_Signal_MET1600->SetMarkerColor(kCyan);
	
	
	h_DoublePhoton_MET->SetMarkerStyle(kFullDotLarge);
	h_DoublePhoton_MET->SetLineColor(1);
	h_DoublePhoton_MET->GetXaxis()->SetRangeUser(xlow,xup);
	
	
	TCanvas *c1 = new TCanvas("c1","stacked hists",1200,900);
	
	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
	
	
	pad1->Draw();
	pad1->cd();
	pad1->SetLogy();
	pad1->SetBottomMargin(0);
	gStyle->SetOptStat(0);
	
	h_met_EWK_error->SetTitle("");
	h_met_EWK_error->GetYaxis()->SetRangeUser(0.0002,1000);
	h_met_EWK_error->GetXaxis()->SetRangeUser(xlow, xup);
	h_met_EWK_error->GetYaxis()->SetTitle("Events/GeV");
	h_met_EWK_error->GetYaxis()->SetTitleOffset(0.78);
	h_met_EWK_error->GetYaxis()->SetTitleSize(0.08);
	h_met_EWK_error->Draw();
	hs->Draw("hist sames");
	h_met_error->Draw("e2 sames");
        //h_met_QCD_plus_EWK->Draw("hist sames");
	h_DoublePhoton_MET->Draw("sames");
	h_DoublePhoton_Signal_MET1400->Draw("sames");
	h_DoublePhoton_Signal_MET1600->Draw("sames");
	//h_met_signal_onepoint->Draw("sames");
	TLegend *leg = new TLegend(0.5,0.6,0.9,0.9); // cms wants 0.5,0.6,0.9,0.9
	leg->SetFillColor(kWhite);
	leg->SetTextFont(42); // cms wants 42
	leg->SetBorderSize(0);
	leg->SetShadowColor(kWhite);
	leg->SetFillStyle(0);
	leg->AddEntry(h_DoublePhoton_MET,"Data","lep");
	leg->AddEntry(h_met_QCD_error,"QCD","f");
	leg->AddEntry(h_met_EWK_error,"EWK","f");
        leg->AddEntry(h_met_error, "combined uncertainty","f");
	leg->AddEntry(h_DoublePhoton_Signal_MET1400, "T5gg, M_{#tilde{g}} = 1.4 TeV, M_{#chi_{2}^{0}} = 0.6 TeV","lep");
	leg->AddEntry(h_DoublePhoton_Signal_MET1600, "T5gg, M_{#tilde{g}} = 1.6 TeV, M_{#chi_{2}^{0}} = 0.6 TeV","lep");
	//leg->AddEntry(h_met_signal_onepoint, "signal E_{T}^{miss}","lep");
	leg->Draw();
	tex1->Draw();
	tex2->Draw();
	tex3->Draw();
	
	
	
	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
	
	pad2->Draw();
	pad2->cd();
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.27);
	TH1F *h2 = (TH1F*)h_DoublePhoton_MET->Clone("h2");
	h2->Reset();
	h2->GetYaxis()->SetTitle("#gamma#gamma/bkg");
	h2->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
	h2->GetXaxis()->SetTitleOffset(0.82);
	
	TH1F *h3 = (TH1F*)h_DoublePhoton_MET->Clone("h3");
	h3->Reset();
	h3->GetYaxis()->SetTitle("#gamma#gamma/bkg");
	h3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
	h3->GetXaxis()->SetTitleOffset(0.82);
	
	TH1F *h4 = (TH1F*)h_DoublePhoton_MET->Clone("h4");
	h4->Reset();
	h4->GetYaxis()->SetTitle("#gamma#gamma/bkg");
	h4->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
	h4->GetXaxis()->SetTitleOffset(0.82);
	
	
	for(int i=0;i<h_DoublePhoton_MET->GetNbinsX();++i){
	  double y = h_DoublePhoton_MET->GetBinContent(i+1);
	  double erry = h_DoublePhoton_MET->GetBinError(i+1);
	  double y1  = h_met_QCD_error->GetBinContent(i+1);
	  double erry1 = h_met_QCD_error->GetBinError(i+1);
	  double z1  = h_met_EWK_error->GetBinContent(i+1);
	  double errz1  = h_met_EWK_error->GetBinError(i+1);
	  double central = y1+z1;
	  double r = y1+z1;
	  double errr = sqrt(erry1*erry1+errz1*errz1);
	  double sys = h_met_error->GetBinError(i+1)/(central);
	  h3->SetBinContent(i+1,1);
	  h3->SetBinError(i+1,sys);
	  if(r!=0)h2->SetBinContent(i+1,y/r);
	  
	  double erz(0), erstat(0);
	  if(y!=0 && r!=0)erz= (y/r)*sqrt((erry/y)*(erry/y)+(errr/r)*(errr/r));
	  if(i<11 && r!=0)h4->SetBinContent(i,y/r);
	  if(i<11)h4->SetBinError(i+1,erz);
	  if(r!=0)erstat= erry/r;
	  h2->SetBinError(i+1,erstat);
	}
	
	h3->GetXaxis()->SetRangeUser(xlow,xup);
	h3->GetXaxis()->SetLabelSize(0.15);
	h3->GetXaxis()->SetTitleSize(0.13);
	h3->GetXaxis()->SetTitle("E_{T}^{miss} (GeV)");
	h3->GetXaxis()->SetTitleOffset(0.97);
	h3->GetYaxis()->SetTitle("data/bkg");
	h3->GetYaxis()->SetRangeUser(0.2,2.5);
	h3->GetYaxis()->SetNdivisions(3);
	h3->GetYaxis()->SetLabelSize(0.16);
	h3->GetYaxis()->SetTitleOffset(0.25);
        h3->GetYaxis()->SetTitleSize(0.17);
	h3->SetTitle("");
	h3->GetYaxis()->CenterTitle();
	h3->SetFillStyle(1001);
        h3->SetFillColor(kGray);
	h3->SetLineColor(kGray);
	h3->SetMarkerColor(kGray);
// 	TLegend *leg2 = new TLegend(0.5,0.6,0.9,0.9); // cms wants 0.5,0.6,0.9,0.9
// 	leg2->SetFillColor(kWhite);
// 	leg2->SetTextFont(42); // cms wants 42
// 	leg2->SetBorderSize(0);
// 	leg2->SetShadowColor(kWhite);
// 	leg2->SetFillStyle(0);
// 	leg2->AddEntry(h3, "Systematic error", "F");
// 	leg2->AddEntry(h2, "Statistical error","lep");
// 	leg2->SetFillColor(0);
// 	leg2->SetTextSize(0.065);
	TLine *lin1 = new TLine(xlow,1,xup,1);
        lin1->SetLineStyle(2);
	h3->Draw("e2");
	h2->Draw("ep same");
	//leg2->Draw("same");
	lin1->Draw();
	
	
	c1->SaveAs(OutputFolder+"/Gamma_QCD_EWK_FinalMET.eps");
	c1->SaveAs(OutputFolder+"/Gamma_QCD_EWK_FinalMET.pdf");
	c1->SaveAs(OutputFolder+"/Gamma_QCD_EWK_FinalMET.png");
	c1->Update();
	
	TCanvas *R = new TCanvas("R","Ratio",600,450); //1200,900
	R->cd();
	gStyle->SetOptStat(0);
	
	TLegend *leg3 = new TLegend(0.9, 0.7, 0.9, 0.9); //0.9, 0.7, 0.7, 0.9
	leg3->AddEntry(h4, "Sys #oplus Stat", "lep");
	leg3->SetFillColor(kWhite);
	leg3->SetTextFont(42); // cms wants 42
	leg3->SetBorderSize(0);
	leg3->SetShadowColor(kWhite);
	leg3->SetFillStyle(0);
	leg3->SetTextSize(0.040);
	h4->GetYaxis()->SetRangeUser(0.2,2.0);
	h4->Draw("ep same");
	leg3->Draw("same");
	
	
	TCanvas *B = new TCanvas("B","EWK E_{T}^{miss}",600,450); //1200,900
	B->cd();
	B->SetLogy();
	h_met_EWK_error->Draw();
	tex1->Draw();
	tex2->Draw();
	B->SaveAs(OutputFolder+"/EWKBackground_Symmetric_NoErBar.eps");
	
	f->Close();
	FQCD->Close();
	FEWK->Close();
	
}
