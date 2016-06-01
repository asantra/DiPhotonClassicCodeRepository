#include <TH1.h>
#include <TFile.h>
#include <TFractionFitter.h>
#include <iostream>
#include "/home/arka/arka/include/MyFunction.h"
#include <sys/stat.h>
#include <fstream>




void FileForFF(bool data, int bin, bool analysisFake){  
  TString OutputFolder="";
  if(analysisFake)OutputFolder="Data_RunD_Ratio_AnalysisFake_217fb";
  else OutputFolder="Data_RunD_Ratio_ExtendedFake_217fb";
  
  int stat0;
  stat0 = mkdir(OutputFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  TFile *fsys = 0;
  
  if(!data)fsys= new TFile("ErrorPropDiEMPttoElectronMET.root", "READ");
  else fsys= new TFile(OutputFolder+"/ErrorPropDiEMPttoElectronMET_Data.root", "READ");
  TH1F *ErrorPropDiEMPtffMET = (TH1F*)fsys->Get("ErrorPropDiEMPtffMET");
  ErrorPropDiEMPtffMET = getOverflow(ErrorPropDiEMPtffMET);
  
  TFile *f8 = 0;
  if(analysisFake)f8 = new TFile("Data_RunD_All_AnalysisFake_217fb.root","READ");
  else f8 = new TFile("Data_RunD_All_ExtendedFake_217fb.root","READ");
    
  TH1F *h_DoubleFake_MET_Reweighted = (TH1F*)f8->Get("h_DoubleFake_MET_Reweighted");
  TH1F *h_DoubleFake_MET = (TH1F*)f8->Get("h_DoubleFake_MET");
  TH1F *h_DoubleFake_MET_ReweightedStatError = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_ReweightedStatError");
  TH1F *h_DoubleFake_MET_ReweighteddiEMPtError = (TH1F*)h_DoubleFake_MET_Reweighted->Clone("h_DoubleFake_MET_ReweighteddiEMPtError");
  TH1F *h_DoublePhoton_MET = (TH1F*)f8->Get("h_DoublePhoton_MET");
  
  h_DoubleFake_MET_Reweighted = getOverflow(h_DoubleFake_MET_Reweighted);
  h_DoubleFake_MET = getOverflow(h_DoubleFake_MET);
  h_DoubleFake_MET_ReweightedStatError = getOverflow(h_DoubleFake_MET_ReweightedStatError);
  h_DoubleFake_MET_ReweighteddiEMPtError = getOverflow(h_DoubleFake_MET_ReweighteddiEMPtError);
  h_DoublePhoton_MET = getOverflow(h_DoublePhoton_MET);
  
  
  int ScaleBin = h_DoublePhoton_MET->FindBin(bin);
  
  Double_t photonInt = h_DoublePhoton_MET->Integral(0, ScaleBin);
  Double_t ffInt = h_DoubleFake_MET_Reweighted->Integral(0, ScaleBin);
  
  //h_DoubleFake_MET_Reweighted->Scale(photonInt/ffInt);
  //ErrorPropDiEMPtffMET->Scale(photonInt/ffInt);
  
  ////// getting only ff histograms ///////
  
  for(int i=0; i <h_DoubleFake_MET_Reweighted->GetNbinsX();++i){
    double y = h_DoubleFake_MET_Reweighted->GetBinContent(i+1);
    double statery = h_DoubleFake_MET_Reweighted->GetBinError(i+1);
    double sysery  = ErrorPropDiEMPtffMET->GetBinError(i+1);
    double ery = sqrt(statery*statery+sysery*sysery);
    h_DoubleFake_MET_Reweighted->SetBinContent(i+1, y);
    h_DoubleFake_MET_Reweighted->SetBinError(i+1, ery);
    h_DoubleFake_MET_ReweightedStatError->SetBinContent(i+1, y);
    h_DoubleFake_MET_ReweightedStatError->SetBinError(i+1, statery);
    h_DoubleFake_MET_ReweighteddiEMPtError->SetBinContent(i+1, y);
    h_DoubleFake_MET_ReweighteddiEMPtError->SetBinError(i+1, sysery);
  }
  
  TFile *fFF = 0;
  if(analysisFake)fFF = new TFile("OnlyFakeHistogramsAnalysisFake_217fb.root","RECREATE");
  else fFF = new TFile("OnlyFakeHistogramsExtendedFake_217fb.root","RECREATE");
  
  fFF->cd();
  h_DoubleFake_MET_Reweighted->Write();
  h_DoubleFake_MET_ReweightedStatError->Write();
  h_DoubleFake_MET_ReweighteddiEMPtError->Write();
  h_DoubleFake_MET->Write();
  fFF->Close();
  h_DoubleFake_MET_Reweighted->Scale(photonInt/ffInt);
  cout << " ff MET in signal region: " << h_DoubleFake_MET_Reweighted->Integral(20,24) << endl;
}
   