#ifndef MyFunction_h
#define MyFunction_h

#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <math.h>
#include <TMath.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLatex.h>
#include <vector>
#include <TString.h>
#include <TLine.h>
#include <TProfile.h>
#include <TPad.h>
#include <TGaxis.h>
#include <TPaletteAxis.h>
#include <TEfficiency.h>
#include <TPaletteAxis.h>




// calculate the response and resolution plots from root files coming from QCDJetMacro.C //
float CalculateError(float deltay, float y, float deltax, float x){
  float error = 0;
  if(y!=0 && x!=0)error= sqrt((deltay/y)*(deltay/y)+(deltax/x)*(deltax/x)/* - 2*(deltax*deltay)/(x*y)*/);
  return error;
}

float dPhiCalc(float phiLead, float phiTrail){
  float dphi = fabs(phiLead - phiTrail);
  if(dphi > TMath::Pi()) dphi = TMath::Pi()*2. - dphi;
  return dphi;
}

float dRCalc(float etaLead, float phiLead, float etaTrail, float phiTrail){
    
  float dphi = fabs(phiLead - phiTrail);
  if (dphi > TMath::Pi()) dphi = TMath::Pi()*2. - dphi;
  float deta = fabs(etaLead - etaTrail);
  float dR = sqrt(deta*deta + dphi*dphi);
  return dR;
    
}

TLine *MakeLine(float xlow, float ylow, float xup, float yup){
  TLine *line = new TLine(xlow,ylow,xup,yup);
  line->SetLineStyle(2);
  return line;
}
// this one for other plots apart from CMS standard
void TexMaker(TLatex *&tex1, TLatex *&tex2){
  tex1 = new TLatex(0.88,0.91,"#sqrt{s} = 13 TeV");
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.037);
  tex1->SetLineWidth(2);
  //tex1->Draw();
  tex2 = new TLatex(0.40,0.88,"#splitline{CMS}{Simulation}");
  tex2->SetNDC();
  tex2->SetTextAlign(13);
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.05);
  tex2->SetLineWidth(1);
  
}

/// this one used for PAS and ready for CMS standard
void TexMaker(TLatex *&tex1, TLatex *&tex2, TLatex *&tex3){
  tex1 = new TLatex(0.85,0.963,"2.3 fb^{-1} (13 TeV)"); //
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.042);
  tex1->SetLineWidth(2);
  //tex1->Draw();
  tex2 = new TLatex(0.20,0.996,"CMS");//(0.15,0.88,"CMS");
  tex2->SetNDC();
  tex2->SetTextAlign(13);
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.05);
  tex2->SetLineWidth(1);
  
  tex3 = new TLatex(0.29,0.993,"Preliminary");//(0.15,0.84,"Simulation")
  tex3->SetNDC();
  tex3->SetTextAlign(13);
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.05);
  tex3->SetLineWidth(1);
  //tex2->Draw();
  
}

/// this one used for EWK shape
void TexMakerForEWK(TLatex *&tex1, TLatex *&tex2, TLatex *&tex3){
  tex1 = new TLatex(0.85,0.915,"2.3 fb^{-1} (13 TeV)"); //0.963
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.042);
  tex1->SetLineWidth(2);
  //tex1->Draw();
  tex2 = new TLatex(0.20,0.94,"CMS");//(0.15,0.88,"CMS");0.996
  tex2->SetNDC();
  tex2->SetTextAlign(13);
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.05);
  tex2->SetLineWidth(1);
  
  tex3 = new TLatex(0.29,0.943,"Preliminary");//(0.15,0.84,"Simulation")0.993
  tex3->SetNDC();
  tex3->SetTextAlign(13);
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.05);
  tex3->SetLineWidth(1);
  //tex2->Draw();
  
}



/// this one used for PAS and ready for CMS standard
void TexMaker2D(TLatex *&tex1, TLatex *&tex2, TLatex *&tex3){
  tex1 = new TLatex(0.87,0.96,"2.3 fb^{-1} (13 TeV)");
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.033);
  tex1->SetLineWidth(2);
  //tex1->Draw();
  tex2 = new TLatex(0.20,0.993,"CMS");
  tex2->SetNDC();
  tex2->SetTextAlign(13);
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.05);
  tex2->SetLineWidth(1);
  
  tex3 = new TLatex(0.32,0.992,"Preliminary");
  tex3->SetNDC();
  tex3->SetTextAlign(13);
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.05);
  tex3->SetLineWidth(1);
  //tex2->Draw();
  
}

TLegend *LegendMaker(){
  TLegend *legend1 = new TLegend(0.5,0.6,0.9,0.9); // cms wants 
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42); // cms wants 42
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}

TLegend *LowerLegendMaker(){
  TLegend *legend1 = new TLegend(0.3,0.2,0.65,0.55); // cms wants 0.5,0.6,0.9,0.9
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42); // cms wants 42
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}

TLegend *RatioLegendMaker(){
  TLegend *legend1 = new TLegend(0.7,0.6,0.9,0.9); // cms wants 0.5,0.6,0.9,0.9
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42); // cms wants 42
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}


TLegend *RatioLowerLegendMaker(){
  TLegend *legend1 = new TLegend(0.5,0.35,0.7,0.65); // cms wants 0.5,0.6,0.9,0.9
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42); // cms wants 42
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}

TLegend *EffLegendMaker(){
  TLegend *legend1 = new TLegend(0.5,0.7,0.9,0.9); // cms wants 0.5,0.6,0.9,0.9,,,, 0.3,0.4,0.7,0.6
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42); // cms wants 42
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}

TLegend *LegendMakerTwoColumn(){
  TLegend *legend1 = new TLegend(0.30,0.4,0.84,0.6);//(0.2,0.6,0.9,0.9);
  legend1->SetNColumns(2);
  legend1->SetLineColor(kWhite);
  legend1->SetFillColor(kWhite);
  legend1->SetTextFont(42);
  legend1->SetBorderSize(0);
  legend1->SetShadowColor(kWhite);
  legend1->SetFillStyle(0);
  return legend1;
}


void MakeFit(TH2F* h2D, int bin, float &fitmean, float &fitmeanerror, float &sigma, float &sigmaError){
   TString Name = "Ratio1";
   TH1D *h1D;
   h1D = h2D->ProjectionY(Name, bin, bin);
   try{
     //if(hType1ParaChsMetRatioVsGen_Ph1PU140_YProject_1D->GetEntries()==0)continue;
     float mean = h1D->GetMean();
     float rms  = h1D->GetRMS();
     TF1 *f1 = new TF1("f1","gaus",mean - 2*rms, mean + 2*rms);
     h1D->Fit("f1","R");
     fitmean = f1->GetParameter(1);
     fitmeanerror = f1->GetParError(1);
     sigma = f1->GetParameter(2);
     sigmaError = f1->GetParError(2);
   }
   catch(const std::exception& e){
     cout << " error: " << e.what() << endl;
  }
}




void DrawHists(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",500, 500);
   gStyle->SetOptStat(1111);
   c->cd();
   if(logy)c->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->SetTitle("");
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(FirstTH1[0]->GetYaxis()->GetTitle());
     FirstTH1[i]->GetXaxis()->SetTitle(FirstTH1[0]->GetXaxis()->GetTitle());
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->GetYaxis()->SetTitleOffset(0.7);
     FirstTH1[i]->GetYaxis()->SetTitleSize(0.045);
     FirstTH1[i]->GetXaxis()->SetTitleSize(0.05);
     //FirstTH1[i]->GetXaxis()->SetTitle("");
     //FirstTH1[i]->GetXaxis()->SetLabelOffset(999);
     FirstTH1[i]->GetXaxis()->SetLabelSize(0.03);
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     /*else*/ 
     if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullDotMedium);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==kOrange+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==kPink+10)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else FirstTH1[i]->SetMarkerStyle(kOpenCircle);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw("lp");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("lp sames");  
   }
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   line->Draw();
   legend1->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
}



/// overloaded function for TGraphAsymmErrors
void DrawGraphs(vector<TGraphAsymmErrors*> FirstTH1, vector<TH1F*> SecondTH1, vector<TString> LegendName, vector<TString> LegendName2, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, float yrange2down, float yrange2up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",500, 500);
   gStyle->SetOptStat(0);
   c->cd();
   if(logy)c->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LegendMakerTwoColumn();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   
   SecondTH1[0]->GetYaxis()->SetRangeUser(yrange2down,yrange2up);
   SecondTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < SecondTH1.size(); ++i){
     SecondTH1[i]->SetTitle(" ");
     SecondTH1[i]->GetYaxis()->CenterTitle();
     SecondTH1[i]->GetYaxis()->SetTitle("Fakerate                       ");
     SecondTH1[i]->GetYaxis()->SetTitleOffset(0.75);
     SecondTH1[i]->GetYaxis()->SetTitleSize(0.055);
     SecondTH1[i]->GetYaxis()->SetNdivisions(5);
     SecondTH1[i]->GetYaxis()->SetLabelSize(0.043);
     SecondTH1[i]->GetXaxis()->SetTitleSize(0.055);
     SecondTH1[i]->GetXaxis()->SetTitleOffset(0.65);
     SecondTH1[i]->GetXaxis()->SetLabelSize(0.050);
     //SecondTH1[i]->GetXaxis()->SetNdivisions(4);
     SecondTH1[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==2)SecondTH1[i]->SetMarkerStyle(kOpenTriangleUp);
     else if(PlotColor[i]==4)SecondTH1[i]->SetMarkerStyle(kOpenSquare);
     else if(PlotColor[i]==kBlack)SecondTH1[i]->SetMarkerStyle(kOpenCircle);
     else if(PlotColor[i]==kRed+3)SecondTH1[i]->SetMarkerStyle(kOpenTriangleDown);
     else if(PlotColor[i]==kMagenta)SecondTH1[i]->SetMarkerStyle(kOpenStar);
     else if(PlotColor[i]==kGreen+3)SecondTH1[i]->SetMarkerStyle(27); //open diamond
     else SecondTH1[i]->SetMarkerStyle(kOpenCircle);
     SecondTH1[i]->SetMarkerColor(PlotColor[i]);
     SecondTH1[i]->SetMarkerSize(1.2);
     //legend1->AddEntry(SecondTH1[i], LegendName2[i], "lp");
   }
   TPad *pad1 = new TPad("pad1","",0,0,1,1);
   TPad *pad2 = new TPad("pad2","",0,0,1,1);
   pad2->SetFillStyle(4000); //will be transparent
   pad2->SetFrameFillStyle(0);
   
   pad1->Draw();
   pad1->cd();
   TGaxis::SetMaxDigits(3);
   SecondTH1[1]->Draw("lp[ Y+ X-");
   for(size_t i=0; i< SecondTH1.size(); ++i){
     if(i!=1)SecondTH1[i]->Draw("ALP same");  
   }
   
   
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetLimits(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->GetYaxis()->CenterTitle(-1);
     FirstTH1[i]->GetYaxis()->SetTitle("Efficiency");
     FirstTH1[i]->GetYaxis()->SetTitleOffset(0.75);
     FirstTH1[i]->GetYaxis()->SetTitleSize(0.048);
     FirstTH1[i]->GetYaxis()->SetLabelSize(0.050);
     FirstTH1[i]->GetYaxis()->SetNdivisions(5);
     FirstTH1[i]->GetXaxis()->SetTitleSize(0.050);
     FirstTH1[i]->GetXaxis()->SetTitleOffset(0.65);
     FirstTH1[i]->GetXaxis()->SetLabelSize(0.050);
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullCircle);
     else if(PlotColor[i]==kRed+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==kMagenta)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(33); //full diamond
     else FirstTH1[i]->SetMarkerStyle(kFullCircle);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     FirstTH1[i]->SetMarkerSize(1.2);
     legend1->AddEntry(FirstTH1[i], LegendName[i], "lp");
     legend1->AddEntry(SecondTH1[i], LegendName2[i], "lp");
   }
   
   pad2->Draw();
   pad2->cd();
   FirstTH1[0]->Draw("Alp");
   //FirstTH1[0]->GetXaxis()->SetAxisColor(kWhite);
   //FirstTH1[0]->GetXaxis()->SetLabelColor(kWhite);
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("pl same");  
   }
   
   
   
   
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   line->Draw();
   legend1->Draw();
   
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   myfile->cd();
   c->Write();
   myfile->Close();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
}



/// needed for axis sizes in the body of the distribution ////


TH1F *BodyAxisSize(TH1F *h1){
  h1->SetTitle("");
  h1->GetYaxis()->SetTitleOffset(0.90);
  h1->GetYaxis()->SetTitleSize(0.065);
  h1->GetYaxis()->SetLabelSize(0.05);
  
  h1->GetXaxis()->SetTitle("");
  h1->GetXaxis()->SetLabelSize(0.15);
  return h1;
} 


/// needed for axis sizes of the one ratio pad /// 

void OneRatioAxisSize(TH1F *&h2){
  h2->GetXaxis()->SetLabelSize(0.153);
  h2->GetXaxis()->SetTitleOffset(0.81);
  h2->GetXaxis()->SetTitleSize(0.17);
  
  h2->GetYaxis()->SetLabelSize(0.14);
  h2->GetYaxis()->SetNdivisions(3);
  h2->GetYaxis()->SetTitleOffset(0.25);
  h2->GetYaxis()->SetTitleSize(0.18);
  h2->GetYaxis()->SetRangeUser(0.1, 2.5);
  
  h2->SetLineColor(kBlack);
  h2->SetMarkerColor(kBlack);
  h2->SetMarkerStyle(kFullDotMedium);
  h2->GetYaxis()->CenterTitle();
  h2->SetTitle("");
}


void DrawHistsRatio(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   //TexMaker(tex1, tex2, tex3);
   TexMakerForEWK(tex1, tex2, tex3); // needed only for EWK shape
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(/*FirstTH1[i]->GetYaxis()->GetTitle()*/"Events/GeV");
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->GetXaxis()->SetTitle("");
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     FirstTH1[i] = BodyAxisSize(FirstTH1[i]);
     
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kMagenta)FirstTH1[i]->SetMarkerStyle(kFullDiamond);
     else if(PlotColor[i]==kOrange)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1); 
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   //FirstTH1[0]->GetXaxis()->SetLabelOffset(0.0);
   FirstTH1[0]->GetYaxis()->SetTitleOffset(0.74);
   FirstTH1[0]->GetXaxis()->SetLabelOffset(0.0);
   
   //FirstTH1[0]->GetXaxis()->SetLabelSize(0.0);
   FirstTH1[0]->Draw("ep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   
   
   h2->Divide(FirstTH1[0], FirstTH1[1]);
   h2->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h2->GetXaxis()->SetTitle(h2->GetXaxis()->GetTitle());
   OneRatioAxisSize(h2);
   h2->Draw("ep");
   
   
   if(drawline)line->Draw();
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   myfile->cd();
   c->Write();
   myfile->Close();
   delete c;
}



void DrawHistsRatioLowerLegend(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LowerLegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(/*FirstTH1[i]->GetYaxis()->GetTitle()*/"Events/GeV");
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     FirstTH1[i] = BodyAxisSize(FirstTH1[i]);
     
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kMagenta)FirstTH1[i]->SetMarkerStyle(kFullDiamond);
     else if(PlotColor[i]==kOrange)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   //FirstTH1[0]->GetXaxis()->SetLabelOffset(999);
   FirstTH1[0]->GetXaxis()->SetLabelSize(0.0);
   FirstTH1[0]->Draw("ep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   
   h2->Divide(FirstTH1[0], FirstTH1[1]);
   h2->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h2->GetXaxis()->SetTitle(h2->GetXaxis()->GetTitle());
   OneRatioAxisSize(h2);
   
   h2->Draw("ep");
   
   
   if(drawline)line->Draw();
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   myfile->cd();
   c->Write();
   myfile->Close();
   delete c;
}



void Draw2DHists(vector<TH2F*>FirstTH1, TString xAxisName, TString yAxisName, TString zAxisName, Float_t xrange1down, Float_t xrange1up, Float_t yrange1down, Float_t yrange1up, Float_t zrange1down, Float_t zrange1up, TString CanvasName, bool logz){
   TCanvas *c = new TCanvas("c","c",500, 500);
   gStyle->SetOptStat(0);
   c->cd();
   //c.SetGrid()
   if(logz)
     c->SetLogz();
   TLatex *tex11, *tex12, *tex13;
   TexMaker2D(tex11, tex12, tex13);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     FirstTH1[i]->SetTitle("");
     FirstTH1[i]->GetYaxis()->SetTitle(yAxisName);
     FirstTH1[i]->GetXaxis()->SetTitle(xAxisName);
     FirstTH1[i]->GetZaxis()->SetTitle(zAxisName);
     FirstTH1[i]->GetYaxis()->SetTitleOffset(1.3);
     FirstTH1[i]->GetYaxis()->SetTitleSize(0.05);
     FirstTH1[i]->GetXaxis()->SetTitleSize(0.05);
     FirstTH1[i]->GetXaxis()->SetLabelSize(0.05);
     FirstTH1[i]->GetZaxis()->SetLabelSize(0.05);
     FirstTH1[i]->GetZaxis()->SetLabelOffset(0.0001);
     FirstTH1[i]->GetZaxis()->SetTitleOffset(0.4);
   }
   FirstTH1[0]->GetZaxis()->SetRangeUser(zrange1down,zrange1up);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   
   
   FirstTH1[0]->Draw("COLZ");
   for(size_t i = 1; i < FirstTH1.size(); ++i)
     FirstTH1[i]->Draw("sames");
   
   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)FirstTH1[0]->GetListOfFunctions()->FindObject("palette");

// the following lines moe the paletter. Choose the values you need for the position.
//    palette->SetX1NDC(0.88);
//    palette->SetX2NDC(0.92);
//    palette->SetY1NDC(0.1);
//    palette->SetY2NDC(0.9);
   palette->SetX1NDC(0.93);
   palette->SetX2NDC(0.945);
   palette->SetY1NDC(0.135);
   palette->SetY2NDC(0.95);
   gPad->Modified();
   gPad->Update();
   
   tex11->Draw();
   tex12->Draw();
   tex13->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");

}



///// Needed for axis labels in the two ratio bottom pads //////

void RatioAxisSize(TH1F *&h2, TH1F *&h3){
  
  h2->GetXaxis()->SetLabelSize(0.147);
  h2->GetXaxis()->SetTitleSize(0.16);
  h2->GetXaxis()->SetTitleOffset(0.88);
  
  h2->GetYaxis()->SetLabelSize(0.15);
  h2->GetYaxis()->SetNdivisions(5);
  h2->SetMarkerStyle(kFullSquare);
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetTitle("Ratio");
  h2->SetTitle("");
  h2->GetYaxis()->SetTitleOffset(0.25);
  h2->GetYaxis()->SetTitleSize(0.20);
  h2->GetYaxis()->SetRangeUser(0.1, 3.5);
  
  h3->GetXaxis()->SetLabelSize(0.15);
  h3->GetXaxis()->SetTitleSize(0.16);
  h3->GetXaxis()->SetTitleOffset(0.97);
  
  h3->GetYaxis()->SetLabelSize(0.16);
  h3->GetYaxis()->SetNdivisions(5);
  h3->SetMarkerStyle(kFullTriangleDown);
  h3->GetYaxis()->CenterTitle();
  h3->SetTitle("");
  h3->GetYaxis()->SetTitleOffset(0.25);
  h3->GetYaxis()->SetTitleSize(0.18);
  h3->GetYaxis()->SetRangeUser(0.0, 3.5);  
  
}

void DrawHistsRatioTwo(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, TH1F* h3, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->Sumw2();
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(FirstTH1[i]->GetYaxis()->GetTitle());
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     FirstTH1[i] = BodyAxisSize(FirstTH1[i]);
     
     
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   //FirstTH1[0]->GetXaxis()->SetLabelOffset(999);
   FirstTH1[0]->GetXaxis()->SetLabelSize(0.0);
   FirstTH1[0]->Draw("ep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   

   h2->Divide(FirstTH1[0], FirstTH1[1]);
   h2->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h2->SetLineColor(PlotColor[1]);
   h2->SetMarkerColor(PlotColor[1]);
   
   h3->Divide(FirstTH1[0], FirstTH1[2]);
   h3->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h3->SetLineColor(PlotColor[2]);
   h3->SetMarkerColor(PlotColor[2]);
   
   RatioAxisSize(h2, h3);
   
   
   TLegend *legend2;
   legend2 = RatioLegendMaker();
   legend2->AddEntry(h2, "#gamma#gamma/ee","lp");
   legend2->AddEntry(h3, h3->GetYaxis()->GetTitle(),"lp");
   
   
   
   h2->Draw("ep");
   h3->Draw("ep same");
   legend2->Draw();
   if(drawline)line->Draw();
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   myfile->cd();
   c->Write();
   myfile->Close();
   delete c;
}





void DrawHistsRatioTwoRatioLowerLegend(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, TH1F* h3, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->Sumw2();
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(FirstTH1[i]->GetYaxis()->GetTitle());
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     
     FirstTH1[i] = BodyAxisSize(FirstTH1[i]);
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   //FirstTH1[0]->GetXaxis()->SetLabelOffset(999);
   FirstTH1[0]->GetXaxis()->SetLabelSize(0.0);
   FirstTH1[0]->Draw("ep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   

   h2->Divide(FirstTH1[0], FirstTH1[1]);
   h2->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h2->SetLineColor(PlotColor[1]);
   h2->SetMarkerColor(PlotColor[1]);
   h3->Divide(FirstTH1[0], FirstTH1[2]);
   h3->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h3->SetLineColor(PlotColor[2]);
   h3->SetMarkerColor(PlotColor[2]);
   RatioAxisSize(h2, h3);
   
   
   TLegend *legend2;
   legend2 = RatioLowerLegendMaker();
   legend2->AddEntry(h2, "#gamma#gamma/ee","lp");
   legend2->AddEntry(h3, h3->GetYaxis()->GetTitle(),"lp");
   
   
   
   h2->Draw("ep");
   h3->Draw("ep same");
   legend2->Draw();
   if(drawline)line->Draw();
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   myfile->cd();
   c->Write();
   myfile->Close();
   delete c;
}





void DrawHistsRatioTwoLowerLegend(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, TH1F* h3, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLegend *legend1;
   legend1 = LowerLegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //FirstTH1[i]->Sumw2();
     //FirstTH1[i]->Scale(1, "width");
     FirstTH1[i]->GetYaxis()->SetTitle(FirstTH1[i]->GetYaxis()->GetTitle());
     //FirstTH1[i]->GetYaxis()->CenterTitle();
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     FirstTH1[i] = BodyAxisSize(FirstTH1[i]);
     
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1);
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->GetXaxis()->SetLabelSize(0.0);
   FirstTH1[0]->Draw("ep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   

   h2->Divide(FirstTH1[0], FirstTH1[1]);
   h2->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h2->SetLineColor(PlotColor[1]);
   h2->SetMarkerColor(PlotColor[1]);
   h3->Divide(FirstTH1[0], FirstTH1[2]);
   h3->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h3->SetLineColor(PlotColor[2]);
   h3->SetMarkerColor(PlotColor[2]);
   RatioAxisSize(h2, h3);
   
   TLegend *legend2;
   legend2 = RatioLegendMaker();
   legend2->AddEntry(h2, "#gamma#gamma/ee","lp");
   legend2->AddEntry(h3, h3->GetYaxis()->GetTitle(),"lp");
   
   
   
   h2->Draw("ep");
   h3->Draw("ep same");
   legend2->Draw();
   if(drawline)line->Draw();
   TFile *myfile = new TFile("MyCanvas.root","RECREATE");
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   myfile->cd();
   c->Write();
   myfile->Close();
   delete c;
}






////!!!!!! Beware: this function is little customized !!!!!!!!! /////
void DrawHistsRatioWithSysErr(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, TH1F* h2, TH1F* hsys, TH1F* h3, float yline1low, float yline1up, bool drawline, bool logy, TLatex *tex4){
   TCanvas *c = new TCanvas("c","c",900, 900);
   TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);//
   pad1->SetBottomMargin(0.0);
   pad1->SetFillStyle(0);
   pad1->Draw();
   pad1->cd();
   gStyle->SetOptStat(0);
   if(logy)pad1->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw();
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("sames");  
   }
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   tex4->Draw();
   legend1->Draw();
   
   c->cd();
   TPad *pad2 = new TPad("pad2", "pad2",0.0,0.0,1.0,0.249);
   pad2->SetTopMargin(0.0);
   pad2->SetBottomMargin(0.3);
   pad2->SetFillStyle(0);
   pad2->Draw();
   pad2->cd();
   gStyle->SetOptStat(0);
   
   for(int i=1; i <= h2->GetNbinsX(); ++i){
     if(FirstTH1[1]->GetBinContent(i)!=0){
       h2->SetBinContent(i, FirstTH1[0]->GetBinContent(i)/FirstTH1[1]->GetBinContent(i));
       float err = (FirstTH1[0]->GetBinContent(i)/FirstTH1[1]->GetBinContent(i))*CalculateError(FirstTH1[0]->GetBinError(i), FirstTH1[0]->GetBinContent(i), FirstTH1[1]->GetBinError(i), FirstTH1[1]->GetBinContent(i));
       h2->SetBinError(i, err);
       h3->SetBinContent(i, 1);
       float syserr = (FirstTH1[0]->GetBinContent(i)/FirstTH1[1]->GetBinContent(i))*CalculateError(hsys->GetBinError(i), FirstTH1[0]->GetBinContent(i), FirstTH1[1]->GetBinError(i), FirstTH1[1]->GetBinContent(i));
       h3->SetBinError(i, syserr);
     }
   }
   h3->GetXaxis()->SetLabelSize(0.08);
   h3->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   h3->GetXaxis()->SetTitleSize(0.13);
   h3->GetYaxis()->SetLabelSize(0.06);
   h3->GetYaxis()->SetTitleSize(0.055);
   //h3->GetYaxis()->SetTitle("ee/ff");
   h3->SetLineColor(kGray);
   h3->SetFillColor(kGray);
   h3->SetMarkerColor(kGray);
   h3->GetYaxis()->SetRangeUser(0.0,3.0);
   h3->Draw("e2");
   h2->GetYaxis()->CenterTitle();
   h2->Draw("ep sames");
   
   TLegend *legend2 = new TLegend(0.15,0.7,0.4,0.9);
   legend2->SetFillColor(kWhite);
   legend2->SetTextFont(42);
   legend2->SetBorderSize(0);
   legend2->SetShadowColor(kWhite);
   legend2->SetFillStyle(0);
   legend2->AddEntry(h2,"stat+sys","lp");
   legend2->AddEntry(h3,"sys","f");
   legend2->Draw("sames");
   if(drawline)line->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
}



void OneCanvasMaker(vector<TH1F*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",800, 800);
   gStyle->SetOptStat(0);
   c->cd();
   if(logy)c->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   //FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   //FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
  
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //Float_t x = FirstTH1[i]->Integral();
     //FirstTH1[i]->Scale(1./x);
     FirstTH1[i]->SetTitle("");
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kRed+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==kMagenta)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1); 
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw();
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("sames");  
   }
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
}



void OneCanvasMakerTH2(vector<TH2F*> FirstTH2, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy, bool logz){
   TCanvas *c = new TCanvas("c","c",800, 800);
   gStyle->SetOptStat(0);
   c->cd();
   if(logy)c->SetLogy();
   if(logz)c->SetLogz();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   //FirstTH2[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   //FirstTH2[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
  
   for(size_t i =0 ; i < FirstTH2.size(); ++i){
     FirstTH2[i]->SetTitle("");
     FirstTH2[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==kGreen+3)FirstTH2[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH2[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH2[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH2[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kRed+3)FirstTH2[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==kMagenta)FirstTH2[i]->SetMarkerStyle(kFullStar);
     else FirstTH2[i]->SetMarkerStyle(PlotColor[i]+1); 
     FirstTH2[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH2[i],LegendName[i], "lp");
   }
   FirstTH2[0]->Draw("COLZ");
   for(size_t i=1; i< FirstTH2.size(); ++i){
     FirstTH2[i]->Draw("");  
   }
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   //legend1->Draw();
   gPad->Update();
   TPaletteAxis *palette = (TPaletteAxis*)FirstTH2[0]->GetListOfFunctions()->FindObject("palette");

// the following lines moe the paletter. Choose the values you need for the position.
   palette->SetX1NDC(0.9);
   palette->SetX2NDC(0.93);
   //palette->SetY1NDC(0.2);
   //palette->SetY2NDC(0.5);
   gPad->Modified();
   gPad->Update();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
}




void ProfileCanvasMaker(vector<TProfile*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",600, 400);
   gStyle->SetOptStat(0);
   c->cd();
   if(logy)c->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw();
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("sames");  
   }
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   delete c;
}



void TwoCanvasMaker(vector<TH1F*> FirstTH1, vector<TH1F*> SecondTH1, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, float xrange2down, float xrange2up, float yrange2down, float yrange2up, TString CanvasName, float yline1low, float yline1up, float yline2low, float yline2up, bool drawline){
   TCanvas *c = new TCanvas("c","c",1200, 400);
   c->Divide(2,1);
   gStyle->SetOptStat(0);
   c->cd(1);
   
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLine *line2 = MakeLine(xrange2down,yline2low,xrange2up,yline2up);
   
   TLegend *legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     FirstTH1[i]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
     FirstTH1[i]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw();
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("sames");  
   }
   line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   
   c->cd(2);
   
   TLegend *legend2 = LegendMaker();
   
   for(size_t i =0 ; i < SecondTH1.size(); ++i){
     SecondTH1[i]->GetYaxis()->SetRangeUser(yrange2down,yrange2up);
     SecondTH1[i]->GetXaxis()->SetRangeUser(xrange2down,xrange2up);
     SecondTH1[i]->SetLineColor(PlotColor[i]);
     legend2->AddEntry(SecondTH1[i], LegendName[i], "lp");
   }
   SecondTH1[0]->Draw();
   for(size_t i=1; i< SecondTH1.size(); ++i){
     SecondTH1[i]->Draw("sames");  
   }
   if(drawline)line2->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend2->Draw();

   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   delete c;
  
}



void AsymmCanvasMaker(vector<TGraphAsymmErrors*> SecondTH1, TString SecondTitle, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange2down, float xrange2up, float yrange2down, float yrange2up, TString CanvasName, float yline2low, float yline2up, bool drawline, TString XAxisTitle, TString YAxisTitle){
   TCanvas *c = new TCanvas("c","c",600, 400);
   gStyle->SetOptStat(0);
   c->cd();
   
   TLine *line2 = MakeLine(xrange2down,yline2low,xrange2up,yline2up);
   
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   
   TLegend *legend2 = LegendMaker();
   
   for(size_t i =0 ; i < SecondTH1.size(); ++i){
     SecondTH1[i]->SetTitle(SecondTitle);
     SecondTH1[i]->GetYaxis()->SetRangeUser(yrange2down,yrange2up);
     SecondTH1[i]->GetXaxis()->SetRangeUser(xrange2down,xrange2up);
     SecondTH1[i]->SetLineColor(PlotColor[i]);
     legend2->AddEntry(SecondTH1[i], LegendName[i], "lp");
   }
   SecondTH1[0]->GetXaxis()->SetTitle(XAxisTitle);
   SecondTH1[0]->GetYaxis()->SetTitle(YAxisTitle);
   SecondTH1[0]->Draw("AP");
   for(size_t i=1; i < SecondTH1.size(); ++i){
     SecondTH1[i]->Draw("sames");  
   }
   if(drawline)line2->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend2->Draw();

   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   delete c;
  
}



void AsymmTwoCanvasMaker(vector<TGraphAsymmErrors*> FirstTH1, TString FirstTitle, vector<TGraphAsymmErrors*> SecondTH1, TString SecondTitle, vector<TString> LegendName, vector<Color_t> PlotColor, float xrange1down, float xrange1up, float yrange1down, float yrange1up, float xrange2down, float xrange2up, float yrange2down, float yrange2up, TString CanvasName, float yline1low, float yline1up, float yline2low, float yline2up, bool drawline){
   TCanvas *c = new TCanvas("c","c",1200, 400);
   c->Divide(2,1);
   gStyle->SetOptStat(0);
   c->cd(1);
   
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   TLine *line2 = MakeLine(xrange2down,yline2low,xrange2up,yline2up);
   
   TLegend *legend1 = LegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     FirstTH1[i]->SetTitle(FirstTitle);
     FirstTH1[i]->GetYaxis()->SetRangeUser(yrange1down,yrange1up);
     FirstTH1[i]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw("AP");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("sames");  
   }
   line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   
   c->cd(2);
   
   TLegend *legend2 = LegendMaker();
   
   for(size_t i =0 ; i < SecondTH1.size(); ++i){
     SecondTH1[i]->SetTitle(SecondTitle);
     SecondTH1[i]->GetYaxis()->SetRangeUser(yrange2down,yrange2up);
     SecondTH1[i]->GetXaxis()->SetRangeUser(xrange2down,xrange2up);
     SecondTH1[i]->SetLineColor(PlotColor[i]);
     legend2->AddEntry(SecondTH1[i], LegendName[i], "lp");
   }
   SecondTH1[0]->Draw("AP");
   for(size_t i=1; i< SecondTH1.size(); ++i){
     SecondTH1[i]->Draw("sames");  
   }
   if(drawline)line2->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend2->Draw();

   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   delete c;
  
}

void DrawEfficiency(vector<TGraphAsymmErrors*> FirstTH1, vector<TString> LegendName, vector<Color_t> PlotColor, TString xaxisTitle, TString yaxisTitle, float xrange1down, float xrange1up, float yrange1down, float yrange1up, TString CanvasName, float yline1low, float yline1up, bool drawline, bool logy){
   TCanvas *c = new TCanvas("c","c",800, 800);
   gStyle->SetOptStat(0);
   c->cd();
   if(logy)c->SetLogy();
   TLine *line = MakeLine(xrange1down,yline1low,xrange1up,yline1up);
   
   TLegend *legend1;
   legend1 = EffLegendMaker();
   TLatex *tex1, *tex2, *tex3;
   TexMaker(tex1, tex2, tex3);
   FirstTH1[0]->GetXaxis()->SetRangeUser(xrange1down,xrange1up);
   FirstTH1[0]->GetYaxis()->SetRangeUser(yrange1down, yrange1up);
   FirstTH1[0]->GetXaxis()->SetTitle(xaxisTitle);
   FirstTH1[0]->GetYaxis()->SetTitle(yaxisTitle);
  
   for(size_t i =0 ; i < FirstTH1.size(); ++i){
     //Float_t x = FirstTH1[i]->Integral();
     //FirstTH1[i]->Scale(1./x);
     FirstTH1[i]->SetTitle("");
     FirstTH1[i]->SetLineColor(PlotColor[i]);
     if(PlotColor[i]==kGreen+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleUp);
     else if(PlotColor[i]==kBlack)FirstTH1[i]->SetMarkerStyle(kFullDotLarge);
     else if(PlotColor[i]==2)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==4)FirstTH1[i]->SetMarkerStyle(kFullSquare);
     else if(PlotColor[i]==kRed+3)FirstTH1[i]->SetMarkerStyle(kFullTriangleDown);
     else if(PlotColor[i]==kMagenta)FirstTH1[i]->SetMarkerStyle(kFullStar);
     else FirstTH1[i]->SetMarkerStyle(PlotColor[i]+1); 
     FirstTH1[i]->SetMarkerColor(PlotColor[i]);
     legend1->AddEntry(FirstTH1[i],LegendName[i], "lp");
   }
   FirstTH1[0]->Draw("aep");
   for(size_t i=1; i< FirstTH1.size(); ++i){
     FirstTH1[i]->Draw("ep sames");  
   }
   if(drawline)line->Draw();
   tex1->Draw();
   tex2->Draw();
   tex3->Draw();
   legend1->Draw();
   
   c->SaveAs(CanvasName+".eps");
   c->SaveAs(CanvasName+".png");
   c->SaveAs(CanvasName+".pdf");
   delete c;
  
}

TH1F *getOverflow(TH1F *h_Sample){
  int bin = h_Sample->GetNbinsX();
  float lastBinValue = h_Sample->GetBinContent(bin);
  float lastBinError = h_Sample->GetBinError(bin);
  
  float lastBinOverflowValue = h_Sample->GetBinContent(bin+1);
  float lastBinOverflowError = h_Sample->GetBinError(bin+1);
  
  float finalValue = lastBinValue + lastBinOverflowValue;
  float finalError = sqrt(lastBinError*lastBinError + lastBinOverflowError*lastBinOverflowError);
  
  h_Sample->SetBinContent(bin, finalValue);
  h_Sample->SetBinContent(bin+1, 0);
  h_Sample->SetBinError(bin, finalError);
  h_Sample->SetBinError(bin+1, 0);
  
  return h_Sample;
}

#endif
