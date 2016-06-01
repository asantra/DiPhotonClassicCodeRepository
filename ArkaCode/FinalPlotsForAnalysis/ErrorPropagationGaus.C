// ----------------------------------------------------------------------------------- //
/*
  ROOT macro for illustrating error propagation using random Gaussian numbers.
  The example is based on first doing the error propagation analytically, and then
  verifying it by running a so-called Monte-Carlo (MC) program.
  For more information on error propagation, see:
    R. J. Barlow: page 48-61 
    P. R. Bevington: page 36-48
  Author: Troels C. Petersen (NBI)
  Email:  petersen@nbi.dk
  Date:   8th of September 2011
*/
// ----------------------------------------------------------------------------------- //

#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TF1.h>
#include <TH2F.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <string>
#include "/home/arka/arka/include/MyFunction.h"

//---------------------------------------------------------------------------------- 
void ErrorPropagationGaus(int pt, bool data)
//---------------------------------------------------------------------------------- 
{
  


  // Set parameters:
  TRandom3 r;
  TRandom3 r2;
  TRandom r3;
  TRandom r4;
  TRandom r5; 
  
  

  // Make histograms:
  //cout << "here" << endl;
  TFile *Fnew = 0;
  TFile *fout = 0;
  if(pt == 40 && !data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/DIEMPtRatio40.root","READ");
  if(pt == 50 && !data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/DIEMPtRatio50.root","READ");
  /// for RunD data //
  if(pt == 40 && data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/DIEMPtRatio40.root","READ");
  if(pt == 50 && data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/DIEMPtRatio50.root","READ");
  // for 50ns data //
  /*if(pt == 40 && data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/DIEMPtRatio40.root","READ");
  if(pt == 50 && data)Fnew = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/DIEMPtRatio50.root","READ");*/
  
  
  TH1F *eephotondiempt = (TH1F*)Fnew->Get("eephotondiempt");
  TH1F *ffphotondiempt = (TH1F*)Fnew->Get("ffphotondiempt");
  TH1F *ffshowershapephotondiempt = (TH1F*)Fnew->Get("ffshowershapephotondiempt");
  
  TH1F *eephotonnjets = (TH1F*)Fnew->Get("eephotonnjets");
  TH1F *ffphotonnjets = (TH1F*)Fnew->Get("ffphotonnjets");
  TH1F *ffshowershapephotonnjets = (TH1F*)Fnew->Get("ffshowershapephotonnjets");
  
  
  
  
  TH2F *eephotondiemptnjets2D = (TH2F*)Fnew->Get("eephotondiemptnjets2D");
  TH2F *ffphotondiemptnjets2D = (TH2F*)Fnew->Get("ffphotondiemptnjets2D");
  
  if(pt == 40 && !data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/RandomRatioErrorProp40.root","RECREATE");
  if(pt == 50 && !data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/MonteCarlo/RandomRatioErrorProp50.root","RECREATE");
  /// for RunD data ///
  if(pt == 40 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/RandomRatioErrorProp40.root","RECREATE");
  if(pt == 50 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data_AlternativeApproach_7414/RandomRatioErrorProp50.root","RECREATE");
  /// for 50ns data ///
  /*if(pt == 40 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/RandomRatioErrorProp40.root","RECREATE");
  if(pt == 50 && data)fout = new TFile("/home/arka/arka/Condor_Submit_Python/SmallGGNtuple_Submitter/Ntuple_74/Data/RandomRatioErrorProp50.root","RECREATE");*/
  
  TH1F *RatioGaus[1000];// for ee diEMPt
  TH1F *RatioGausFF[1000];
  TH1F *RatioGausFFShowershape[1000];
  
  TH1F *RatioGausNJets[1000];// for ee diEMPt
  TH1F *RatioGausFFNJets[1000];
  TH1F *RatioGausFFShowershapeNJets[1000];
  
  TH2F *RatioGausEENJetDiEMPt2D[1000];
  TH2F *RatioGausFFNJetDiEMPt2D[1000];

  char *histnameY        = new char[25];
  char *histnameRatio    = new char[25];
  char *histnameX        = new char[25];
  char *histtitleY       = new char[50];
  char *histtitleRatio   = new char[50];
  char *histtitleX       = new char[50];



//----------------------------------------------------------------------------------
// Loop over process:
//----------------------------------------------------------------------------------




  double mu1[50]          =  {0};
  double sig1[50]         =  {0};
  double mu2[50]          =  {0};
  double sig2[50]         =  {0};
  double mu3[50]          =  {0};
  double sig3[50]         =  {0};
  
  double mu4[50]          =  {0};
  double sig4[50]         =  {0};
  double mu5[50]          =  {0};
  double sig5[50]         =  {0};
  double mu6[50]          =  {0};
  double sig6[50]         =  {0};
  
  
  double mu2Dee[50][50]   = {{0},{0}};
  double sig2Dee[50][50]  = {{0},{0}};
  double mu2Dff[50][50]   = {{0},{0}};
  double sig2Dff[50][50]  = {{0},{0}};

  //cout << "here too" << endl;
  for(int i = 0 ; i <  eephotondiempt->GetXaxis()->GetNbins(); i++){
     //cout << "i : " << i << endl;
     mu1[i]  = eephotondiempt->GetBinContent(i+1);
     sig1[i] = eephotondiempt->GetBinError(i+1);  
     mu2[i]  = ffphotondiempt->GetBinContent(i+1);
     sig2[i] = ffphotondiempt->GetBinError(i+1);
     mu3[i]  = ffshowershapephotondiempt->GetBinContent(i+1);
     sig3[i] = ffshowershapephotondiempt->GetBinError(i+1);
  }
  for(int i = 0 ; i < eephotonnjets->GetXaxis()->GetNbins(); i++){
     mu4[i]  = eephotonnjets->GetBinContent(i+1);
     sig4[i] = eephotonnjets->GetBinError(i+1);  
     mu5[i]  = ffphotonnjets->GetBinContent(i+1);
     sig5[i] = ffphotonnjets->GetBinError(i+1);
     mu6[i]  = ffshowershapephotonnjets->GetBinContent(i+1);
     sig6[i] = ffshowershapephotonnjets->GetBinError(i+1);
  }  

  
  for(int i = 0; i < eephotondiemptnjets2D->GetNbinsX(); ++i){
    for(int j = 0; j< eephotondiemptnjets2D->GetNbinsY(); ++j){
      mu2Dee[i][j] = eephotondiemptnjets2D->GetBinContent(i+1,j+1);
      sig2Dee[i][j] = eephotondiemptnjets2D->GetBinError(i+1,j+1);
      mu2Dff[i][j] = ffphotondiemptnjets2D->GetBinContent(i+1,j+1);
      sig2Dff[i][j] = ffphotondiemptnjets2D->GetBinError(i+1,j+1);
    }
  }


//----------------------------------------------------------------------------------
// Loop over process:
//----------------------------------------------------------------------------------
  //cout << "Loop begins: " << endl;
  for(int k=0; k < 1000; ++k){
    if(k%50 == 0)printf("processed diEMPt and njets: %d \n", k);
    sprintf(histnameRatio, "DiEMPtee%d",k+1);
    sprintf(histtitleRatio,"random DiEMPt ratio for ee %d",k+1);
    //RatioGaus[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGaus[k] = (TH1F*)eephotondiempt->Clone(histnameRatio);
    RatioGaus[k]->Reset();
    RatioGaus[k]->SetTitle(histtitleRatio);
    
    sprintf(histnameRatio, "DiEMPtff%d",k+1);
    sprintf(histtitleRatio,"random DiEMPt ratio for ff %d",k+1);
    //RatioGausFF[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausFF[k]=(TH1F*)ffphotondiempt->Clone(histnameRatio);
    RatioGausFF[k]->Reset();
    RatioGausFF[k]->SetTitle(histtitleRatio);
    
    sprintf(histnameRatio, "DiEMPtffshowershape%d",k+1);
    sprintf(histtitleRatio,"random DiEMPt ratio for ff %d",k+1);
    //RatioGausFFShowershape[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausFFShowershape[k]=(TH1F*)ffshowershapephotondiempt->Clone(histnameRatio);
    RatioGausFFShowershape[k]->Reset();
    RatioGausFFShowershape[k]->SetTitle(histtitleRatio);
    
    
    sprintf(histnameRatio, "NJetsee%d",k+1);
    sprintf(histtitleRatio,"random NJets ratio for ee %d",k+1);
    //RatioGaus[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausNJets[k] = (TH1F*)eephotonnjets->Clone(histnameRatio);
    RatioGausNJets[k]->Reset();
    RatioGausNJets[k]->SetTitle(histtitleRatio);
    
    sprintf(histnameRatio, "NJetsff%d",k+1);
    sprintf(histtitleRatio,"random NJets ratio for ff %d",k+1);
    //RatioGausFF[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausFFNJets[k]=(TH1F*)ffphotonnjets->Clone(histnameRatio);
    RatioGausFFNJets[k]->Reset();
    RatioGausFFNJets[k]->SetTitle(histtitleRatio);
    
    sprintf(histnameRatio, "NJetsffshowershape%d",k+1);
    sprintf(histtitleRatio,"random NJets ratio for ff %d",k+1);
    //RatioGausFFShowershape[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausFFShowershapeNJets[k]=(TH1F*)ffshowershapephotonnjets->Clone(histnameRatio);
    RatioGausFFShowershapeNJets[k]->Reset();
    RatioGausFFShowershapeNJets[k]->SetTitle(histtitleRatio);
    
    
    
    sprintf(histnameRatio, "EEDiEMPtNJet2DRatio%d",k+1);
    sprintf(histtitleRatio,"random 2D diEMPt vs NJet for ee %d",k+1);
    //RatioGausFFShowershape[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausEENJetDiEMPt2D[k]=(TH2F*)eephotondiemptnjets2D->Clone(histnameRatio);
    RatioGausEENJetDiEMPt2D[k]->Reset();
    RatioGausEENJetDiEMPt2D[k]->SetTitle(histtitleRatio);
    
    
    sprintf(histnameRatio, "FFDiEMPtNJet2DRatio%d",k+1);
    sprintf(histtitleRatio,"random 2D diEMPt vs NJet for ff %d",k+1);
    //RatioGausFFShowershape[k]=new TH1F(histnameRatio,histtitleRatio,50,0,200);
    RatioGausFFNJetDiEMPt2D[k]=(TH2F*)ffphotondiemptnjets2D->Clone(histnameRatio);
    RatioGausFFNJetDiEMPt2D[k]->Reset();
    RatioGausFFNJetDiEMPt2D[k]->SetTitle(histtitleRatio);
    
    
    //cout << "for K: " << k << endl;
    for(int j=0; j < eephotondiempt->GetXaxis()->GetNbins(); ++j){
      //cout << "j : " << j << endl;
      double u = r.Gaus(mu1[j], sig1[j]);
      RatioGaus[k]->SetBinContent(j+1,u);
      double v = r2.Gaus(mu2[j], sig2[j]);
      if(v>0)RatioGausFF[k]->SetBinContent(j+1,v);
      else RatioGausFF[k]->SetBinContent(j+1,0);
      double w = r3.Gaus(mu3[j], sig3[j]);
      if(w>0)RatioGausFFShowershape[k]->SetBinContent(j+1,w);
      else RatioGausFFShowershape[k]->SetBinContent(j+1,0);
    }
    
    
    for(int j=0; j < eephotonnjets->GetXaxis()->GetNbins(); ++j){
      //cout << "j : " << j << endl;
      double u = r.Gaus(mu4[j], sig4[j]);
      RatioGausNJets[k]->SetBinContent(j+1,u);
      double v = r2.Gaus(mu5[j], sig5[j]);
      if(v>0)RatioGausFFNJets[k]->SetBinContent(j+1,v);
      else RatioGausFFNJets[k]->SetBinContent(j+1,0);
      double w = r3.Gaus(mu6[j], sig6[j]);
      if(w>0)RatioGausFFShowershapeNJets[k]->SetBinContent(j+1,w);
      else RatioGausFFShowershapeNJets[k]->SetBinContent(j+1,0);
    }
    
    for(int i = 0; i < eephotondiemptnjets2D->GetNbinsX(); ++i){
      for(int j = 0; j< eephotondiemptnjets2D->GetNbinsY(); ++j){
	double u = r4.Gaus(mu2Dee[i][j], sig2Dee[i][j]);
	RatioGausEENJetDiEMPt2D[k]->SetBinContent(i+1, j+1, u);
	double v = r5.Gaus(mu2Dff[i][j], sig2Dff[i][j]);
	RatioGausFFNJetDiEMPt2D[k]->SetBinContent(i+1, j+1, v);
      }
    }
    
    RatioGaus[k]->Write();
    RatioGausFF[k]->Write();
    RatioGausFFShowershape[k]->Write();
    
    
    RatioGausNJets[k]->Write();
    RatioGausFFNJets[k]->Write();
    RatioGausFFShowershapeNJets[k]->Write();
    
    RatioGausEENJetDiEMPt2D[k]->Write();
    RatioGausFFNJetDiEMPt2D[k]->Write();

  }
  Fnew->Close();
  fout->Close();
  
}
