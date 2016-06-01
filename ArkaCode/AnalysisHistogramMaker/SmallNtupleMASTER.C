#define SmallNtupleQQQ_cxx
#include "SmallNtupleQQQ.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>
#include <iostream>
#include <TSystem.h>
#include <TString.h>
#include <algorithm>
#include <TProfile.h>
#include <fstream>

//// rememeber to check few things:
/// pt cut is there and fakerate has good value

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

float findDiEMPt(float ELead, float EtaLead, float PhiLead, float ETrail, float EtaTrail, float PhiTrail){
  float theta1 = 2*atan(exp(-EtaLead));
  float theta2 = 2*atan(exp(-EtaTrail));
  float PX1 = ELead*sin(theta1)*cos(PhiLead);
  float PY1 = ELead*sin(theta1)*sin(PhiLead);
  float PX2 = ETrail*sin(theta2)*cos(PhiTrail);
  float PY2 = ETrail*sin(theta2)*sin(PhiTrail);
  float DiEMPt = sqrt((PX1+PX2)*(PX1+PX2)+(PY1+PY2)*(PY1+PY2));
  return DiEMPt;
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

void Make1DPlot(TH1F *hist1D, const TString str1D, bool logY, const int xlow, const int xhigh){
  TCanvas *BBB = new TCanvas("BBB", "E_{T}^{miss} Response",600,450);
  BBB->cd();
  hist1D->GetXaxis()->SetRangeUser(xlow, xhigh); 
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.88); 
  gStyle->SetOptStat(111111);
  if(logY)BBB->SetLogy();  
  hist1D->Draw();
  TString name1, name2;
  name1 = str1D+".eps";
  name2 = str1D+".pdf";
  BBB->SaveAs(name1);
  BBB->SaveAs(name2);
  BBB->Delete();
}
/////////////////////////////////////////////////////////
///////// this uses Spring15 25ns medium photon ///////////////////////
/////////////////////////////////////////////////////////

void SmallNtupleQQQ::Loop(TString outfile)
{
//   In a ROOT session, you can do:
//      Root > .L SmallNtupleQQQ.C
//      Root > SmallNtupleQQQ t
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
  
  
  
  TFile *f1 = new TFile(outfile, "RECREATE");
  
   /* Defining Histograms */
   TH1::SetDefaultSumw2();
   TH1F* h_DrAll(new TH1F("h_DrAll", "DeltaR between two objects, ; DeltaR;Events", 50, 0 ,1));
   TH1F* h_Dr_MCElectron_Photon(new TH1F("h_Dr_MCElectron_Photon", "DeltaR between MCElectron and photon, ; DeltaR;Events", 50, 0 ,1));
   TH1F* h_Photon_MET(new TH1F("h_Photon_MET", "PfMet for photons, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_Fake_MET(new TH1F("h_Fake_MET", "PfMet for fakes, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_Fake_Photon_Pt(new TH1F("h_Fake_Photon_Pt","p_{T}for fake photons;p_{T} (GeV);Event/5 GeV", 100, 0, 500));
   TH1F* h_Electron_MET(new TH1F("h_Electron_MET", "PfMet for electrons, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_SinglePhoton_MET(new TH1F("h_SinglePhoton_MET", "PfMet for single photon, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_SingleFake_MET(new TH1F("h_SingleFake_MET", "PfMet for single fake, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_SingleElectron_MET(new TH1F("h_SingleElectron_MET", "PfMet for single electron, ; PfMet;Events", 100, 0 ,500));
   TH1F* h_CutFlow_Electron(new TH1F("h_CutFlow_Electron", "CutFlow for electron, ;Cuts;Events",10,0,10));
   TH1F* h_CutFlow_Photon(new TH1F("h_CutFlow_Photon", "CutFlow for photon, ;Cuts;Events",10,0,10));
   TH1F* h_HoverE_Electron(new TH1F("h_HoverE_Electron", "HoverE distribution, Electron, ;H/E;Number",40,0,0.1));
   TH1F* h_HoverE_Photon(new TH1F("h_HoverE_Photon", "HoverE distribution, Photon, ;H/E;Number",40,0,0.1));
   TH1F* h_ShowerShape(new TH1F("h_ShowerShape", "Showershape distribution, ;showershape;Number",80,0,0.05));
   TH1F* h_Pt(new TH1F("h_Pt", "Pt distribution, ;p_{T};Number",100,0,100));
   TH1F* h_Dr_Electrons(new TH1F("h_Dr_Electrons", "#Delta R between mcElectron and recoElectron from PHYS14 selection, ;#Delta R;Number",100,0,3));
   TH1F* h_Dr_ElectronJets(new TH1F("h_Dr_ElectronJets", "#Delta R between recoElectron and jets from PHYS14 selection, ;#Delta R;Number",100,0,3));
   TH1F* h_Ht(new TH1F("h_Ht", "Distribtuion of Ht;Ht;Events/4 GeV",1000,0,4000));
   TH1F* h_NTrks_All(new TH1F("h_NTrks_All", "Distribtuion of All Ntrks;NTrks;Events/4 GeV",50,0,200));

   TH1F* h_DeltaPhi_LeadPhotonMET(new TH1F("h_DeltaPhi_LeadPhotonMET", "Distribtuion of #Delta #phi between lead photon and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   TH1F* h_DeltaPhi_TrailPhotonMET(new TH1F("h_DeltaPhi_TrailPhotonMET", "Distribtuion of #Delta #phi between trail photon and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   TH1F* h_DeltaPhi_LeadElectronMET(new TH1F("h_DeltaPhi_LeadElectronMET", "Distribtuion of #Delta #phi between lead electron and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   TH1F* h_DeltaPhi_TrailElectronMET(new TH1F("h_DeltaPhi_TrailElectronMET", "Distribtuion of #Delta #phi between trail electron and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   TH1F* h_DeltaPhi_LeadFakeMET(new TH1F("h_DeltaPhi_LeadFakeMET", "Distribtuion of #Delta #phi between lead fake and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   TH1F* h_DeltaPhi_TrailFakeMET(new TH1F("h_DeltaPhi_TrailFakeMET", "Distribtuion of #Delta #phi between trail fake and E_{T}^{miss};#Delta#phi;Events",25,0,3.5));
   
   
   float xbins[] = {0,2,5,8,11,14,17,20,25,30,35,40,45,50,57,64,71,80,90, 100,110,120,140,300};
   int binnum = sizeof(xbins)/sizeof(Float_t) - 1;
   float diemptbins[] = {0,3,6,9,12,15,18,22,26,30,35,40,45,50,60,70,85,100,120,140,170,200,400,600}; //250
   int diemptbinnum = sizeof(diemptbins)/sizeof(Float_t) - 1;
   float ptbins[] = {0,20,40,42,45,48,51,54,57,60,63,66,69,72,76,80,85,90,95,100,110,120,130,140,150,170,190,220,250,300,350,400};
   int ptbinnum = sizeof(ptbins)/sizeof(Float_t) - 1;
   
   Double_t diemptbinsdouble[] = {0,3,6,9,12,15,18,22,26,30,35,40,45,50,60,70,85,100,120,140,170,200,250,600};

   TH1F* h_LeadPhoton_Pt(new TH1F("h_LeadPhoton_Pt", "Distribution of Lead photon pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   TH1F* h_TrailPhoton_Pt(new TH1F("h_TrailPhoton_Pt", "Distribution of trail photon pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   TH1F* h_LeadFake_Pt(new TH1F("h_LeadFake_Pt", "Distribution of Lead fake pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   TH1F* h_TrailFake_Pt(new TH1F("h_TrailFake_Pt", "Distribution of trail fake pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   TH1F* h_LeadElectron_Pt(new TH1F("h_LeadElectron_Pt", "Distribution of Lead electron pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   TH1F* h_TrailElectron_Pt(new TH1F("h_TrailElectron_Pt", "Distribution of trail electron pt;p_{T};Events/ GeV",ptbinnum,ptbins));
   
   
   
   
   TH1F* h_DoublePhoton_SignalInvMass(new TH1F("h_DoublePhoton_SignalInvMass","Invariant mass for double photon, E_{T}^{miss}>100 GeV; M_{#gamma#gamma} (GeV); Events/ GeV",500,0,1000));
   TH1F* h_DoublePhoton_AllInvMass(new TH1F("h_DoublePhoton_AllInvMass","Invariant mass for double photon; M_{#gamma#gamma} (GeV); Events/ GeV",500,0,1000));
   TH1F* h_DoublePhoton_AllInvMass_Endcap(new TH1F("h_DoublePhoton_AllInvMass_Endcap","Invariant mass for double photon, only endcap; M_{#gamma#gamma} (GeV); Events/ GeV",500,0,1000));
   
   TH1F* h_DoublePhoton_MET(new TH1F("h_DoublePhoton_MET","E_{T}^{miss} for double photon, E_{T}^{miss}<50 GeV; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_DiEMPt30to50(new TH1F("h_DoublePhoton_MET_DiEMPt30to50","E_{T}^{miss} for double photon, 40 < diEMpt < 50; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_DiEMPt50to70(new TH1F("h_DoublePhoton_MET_DiEMPt50to70","E_{T}^{miss} for double photon, 50 < diEMpt < 70; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_DiEMPt70to100(new TH1F("h_DoublePhoton_MET_DiEMPt70to100","E_{T}^{miss} for double photon, 70 < diEMpt < 100; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_Upto100(new TH1F("h_DoublePhoton_MET_Upto100","E_{T}^{miss} for double photon, E_{T}^{miss}<100 GeV; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_Full(new TH1F("h_DoublePhoton_MET_Full","E_{T}^{miss} for double photon; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_NJet1to2(new TH1F("h_DoublePhoton_MET_NJet1to2","E_{T}^{miss} for double photon, 1 <= NJet <= 2; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoublePhoton_MET_NJet3to4(new TH1F("h_DoublePhoton_MET_NJet3to4","E_{T}^{miss} for double photon, 3 <= NJet <= 4; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_DoubleElectron_MET(new TH1F("h_DoubleElectron_MET","E_{T}^{miss} for double electron; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_DiEMPt30to50(new TH1F("h_DoubleElectron_MET_DiEMPt30to50","E_{T}^{miss} for double electron, 40 < diEMpt < 50; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_DiEMPt50to70(new TH1F("h_DoubleElectron_MET_DiEMPt50to70","E_{T}^{miss} for double electron, 50 < diEMpt < 70; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_DiEMPt70to100(new TH1F("h_DoubleElectron_MET_DiEMPt70to100","E_{T}^{miss} for double electron, 70 < diEMpt < 100; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_NJet1to2(new TH1F("h_DoubleElectron_MET_NJet1to2","E_{T}^{miss} for double electron, 1 <= NJet <= 2; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_NJet3to4(new TH1F("h_DoubleElectron_MET_NJet3to4","E_{T}^{miss} for double electron, 3 <= NJet <= 4; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_DoubleElectron_MET_SignalRegion(new TH1F("h_DoubleElectron_MET_SignalRegion","E_{T}^{miss} for double electron, E_{T}^{miss}>100 GeV; E_{T}^{miss} (GeV); Events/10 GeV",40,100,500));
   TH1F* h_DoubleElectron_MET_Reweighted(new TH1F("h_DoubleElectron_MET_Reweighted","E_{T}^{miss} for double electron, diEMPt reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_ReweightedNJets(new TH1F("h_DoubleElectron_MET_ReweightedNJets","E_{T}^{miss} for double electron, NJets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleElectron_MET_ReweightedDiEMPtNJets(new TH1F("h_DoubleElectron_MET_ReweightedDiEMPtNJets","E_{T}^{miss} for double electron, diEMPt*njets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio(new TH1F("h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio","E_{T}^{miss} for double electron, diEMPt vs njets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   
   TH1F* h_DoubleFake_MET(new TH1F("h_DoubleFake_MET","E_{T}^{miss} for double fake; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_DiEMPt30to50(new TH1F("h_DoubleFake_MET_DiEMPt30to50","E_{T}^{miss} for double fake, 40 < diEMpt < 50; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_DiEMPt50to70(new TH1F("h_DoubleFake_MET_DiEMPt50to70","E_{T}^{miss} for double fake, 50 < diEMpt < 70; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_DiEMPt70to100(new TH1F("h_DoubleFake_MET_DiEMPt70to100","E_{T}^{miss} for double fake, 70 < diEMpt < 100; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_NJet1to2(new TH1F("h_DoubleFake_MET_NJet1to2","E_{T}^{miss} for double fake, 1 <= NJet <= 2; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_NJet3to4(new TH1F("h_DoubleFake_MET_NJet3to4","E_{T}^{miss} for double fake, 3 <= NJet <= 4; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_DoubleFake_MET_SignalRegion(new TH1F("h_DoubleFake_MET_SignalRegion","E_{T}^{miss} for double fake, E_{T}^{miss}>100 GeV; E_{T}^{miss} (GeV); Events/ GeV",40,100,500));
   TH1F* h_DoubleFake_MET_Reweighted(new TH1F("h_DoubleFake_MET_Reweighted","E_{T}^{miss} for double fake, diempt reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_ReweightedNJets(new TH1F("h_DoubleFake_MET_ReweightedNJets","E_{T}^{miss} for double fake, NJets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_ReweightedDiEMPtNJets(new TH1F("h_DoubleFake_MET_ReweightedDiEMPtNJets","E_{T}^{miss} for double fake, diempt*njets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio(new TH1F("h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio","E_{T}^{miss} for double fake, diempt vs njets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   
   TH1F* h_DoubleFakeShowershape_MET(new TH1F("h_DoubleFakeShowershape_MET","E_{T}^{miss} for double fake failing showershape or chargedhadiso; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFakeShowershape_MET_Reweighted(new TH1F("h_DoubleFakeShowershape_MET_Reweighted","E_{T}^{miss} for double fake failing showershape or chargedhadiso, diempt reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFakeShowershape_MET_ReweightedNJets(new TH1F("h_DoubleFakeShowershape_MET_ReweightedNJets","E_{T}^{miss} for double fake failing showershape or chargedhadiso, NJets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets(new TH1F("h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets","E_{T}^{miss} for double fake failing showershape or chargedhadiso, diempt*njets reweighted; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   
   TH1F* h_ElectronPhoton_MET(new TH1F("h_ElectronPhoton_MET","E_{T}^{miss} for electron-photon; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_ElectronPhoton_InvMass(new TH1F("h_ElectronPhoton_InvMass","Invariant Mass for electron-photon; Invariant Mass (GeV); Events/ GeV",350,0,200));
   TH1F* h_DoubleElectron_InvMass(new TH1F("h_DoubleElectron_InvMass","Invariant Mass for double electron; Invariant Mass (GeV); Events/ GeV",350,0,200));
   TH1F* h_DoubleFake_InvMass(new TH1F("h_DoubleFake_InvMass","Invariant Mass for double fake; Invariant Mass (GeV); Events/ GeV",200,0,1000));
   
   TH1F* h_Scaled_ElectronPhoton_MET(new TH1F("h_Scaled_ElectronPhoton_MET","E_{T}^{miss} for electron-photon, scaled with fake rate; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_Scaled_ElectronPhoton_MET_Up(new TH1F("h_Scaled_ElectronPhoton_MET_Up","E_{T}^{miss} for electron-photon, scaled with fake rate up; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_Scaled_ElectronPhoton_MET_Down(new TH1F("h_Scaled_ElectronPhoton_MET_Down","E_{T}^{miss} for electron-photon, scaled with fake rate down; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   TH1F* h_ElectronPhoton_MET_SingleElectron(new TH1F("h_ElectronPhoton_MET_SingleElectron","E_{T}^{miss} for electron-photon; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_Scaled_ElectronPhoton_MET_SingleElectron(new TH1F("h_Scaled_ElectronPhoton_MET_SingleElectron","E_{T}^{miss} for electron-photon, scaled with fake rate; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_Scaled_ElectronPhoton_MET_Up_SingleElectron(new TH1F("h_Scaled_ElectronPhoton_MET_Up_SingleElectron","E_{T}^{miss} for electron-photon, scaled with fake rate up; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_Scaled_ElectronPhoton_MET_Down_SingleElectron(new TH1F("h_Scaled_ElectronPhoton_MET_Down_SingleElectron","E_{T}^{miss} for electron-photon, scaled with fake rate down; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   
   
   TH1F* h_DoubleElectron_DiEMPt(new TH1F("h_DoubleElectron_DiEMPt","DiEMPt for di-electron; di-EM p_{T} (GeV); Events/ GeV", diemptbinnum, diemptbins));
   TH1F* h_DoublePhoton_DiEMPt(new TH1F("h_DoublePhoton_DiEMPt","DiEMPt for di-photon; di-EM p_{T} (GeV); Events/ GeV", diemptbinnum, diemptbins));
   TH1F* h_DoubleFake_DiEMPt(new TH1F("h_DoubleFake_DiEMPt","DiEMPt for di-fake; di-EM p_{T} (GeV); Events/ GeV", diemptbinnum, diemptbins));
   
   
   TH1F* h_DoubleFakeShowershape_DiEMPt(new TH1F("h_DoubleFakeShowershape_DiEMPt","DiEMPt for di-fake failing showershape or chargedhadiso; di-EM p_{T} (GeV); Events/ GeV", diemptbinnum, diemptbins));
   TH1F* h_DoubleElectron_Rho(new TH1F("h_DoubleElectron_Rho","Rho for di-electron; #rho; Events/ GeV",20,0,40));
   TH1F* h_DoublePhoton_Rho(new TH1F("h_DoublePhoton_Rho","Rho for di-photon; #rho; Events/ GeV",20,0,40));
   TH1F* h_DoubleFake_Rho(new TH1F("h_DoubleFake_Rho","Rho for di-fake; #rho; Events/ GeV",20,0,40));
   TH1F* h_DoubleFakeShowershape_Rho(new TH1F("h_DoubleFakeShowershape_Rho","Rho for di-fake failing showershape; #rho; Events/ GeV",20,0,40));
   TH1F* h_DoubleElectron_Nvtx(new TH1F("h_DoubleElectron_Nvtx","nVtx for di-electron; nvertex; Events/ GeV",20,0,40));
   TH1F* h_DoublePhoton_Nvtx(new TH1F("h_DoublePhoton_Nvtx","nVtx for di-photon; nvertex; Events/ GeV",20,0,40));
   TH1F* h_DoubleFake_Nvtx(new TH1F("h_DoubleFake_Nvtx","nVtx for di-fake; nvertex; Events/ GeV",20,0,40));
   TH1F* h_DoubleFakeShowershape_Nvtx(new TH1F("h_DoubleFakeShowershape_Nvtx","nVtx for di-fake failing showershape; nvertex; Events/ GeV",20,0,40));
   
   TH1F* h_DoublePhoton_DeltaPhi(new TH1F("h_DoublePhoton_DeltaPhi","#Delta#phi for di-photon; #Delta#phi; Events/(3.2/20)GeV",20,0,3.2));
   TH1F* h_DoublePhoton_DeltaPhi_AfterDRCut(new TH1F("h_DoublePhoton_DeltaPhi_AfterDRCut","#Delta#phi for di-photon; #Delta#phi; Events/(3.2/20)GeV",20,0,3.2));
   
   TH1F* h_DoublePhoton_NJets(new TH1F("h_DoublePhoton_NJets","NJets for di-photon; N_{jets}; Events/ GeV",10,0,10));
   TH1F* h_DoubleElectron_NJets(new TH1F("h_DoubleElectron_NJets","NJets for di-electron; N_{jets}; Events/ GeV",10,0,10));
   TH1F* h_DoubleFake_NJets(new TH1F("h_DoubleFake_NJets","NJets for di-fake; N_{jets}; Events/ GeV",10,0,10));
   TH1F* h_DoubleElectron_NJets_Reweighted(new TH1F("h_DoubleElectron_NJets_Reweighted","NJets for di-electron, reweighted by diEMPt; N_{jets}; Events/ GeV",10,0,10));
   TH1F* h_DoubleFake_NJets_Reweighted(new TH1F("h_DoubleFake_NJets_Reweighted","NJets for di-fake, reweighted by diEMPt; N_{jets}; Events/ GeV",10,0,10));
   TH1F* h_DoubleFakeShowershape_NJets(new TH1F("h_DoubleFakeShowershape_NJets","NJets for di-fake failing showershape; N_{jets}; Events/ GeV",10,0,10));
   
   TH1F* h_ChargedHadIso(new TH1F("h_ChargedHadIso","ChargedHadIso distribution for #gamma and fake, #rho corrected; chHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_ChargedHadIso_WithoutShowerCut(new TH1F("h_ChargedHadIso_WithoutShowerCut","ChargedHadIso distribution for #gamma and fake, without showercut, #rho corrected; chHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_NeutralHadIso_Photon(new TH1F("h_NeutralHadIso_Photon","NeutralHadIso distribution for #gamma, #rho corrected; nHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_PhotonHadIso_Photon(new TH1F("h_PhotonHadIso_Photon","PhotonHadIso distribution for #gamma, #rho corrected; pHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_SigmaIetaIeta_Photon(new TH1F("h_SigmaIetaIeta_Photon","SigmaIetaIeta distribution for #gamma; #sigma_{i#eta i#eta}; Events/0.0002 GeV",100,0,0.02));
   TH1F* h_NeutralHadIso_Fake(new TH1F("h_NeutralHadIso_Fake","NeutralHadIso distribution for fake, #rho corrected; nHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_PhotonHadIso_Fake(new TH1F("h_PhotonHadIso_Fake","PhotonHadIso distribution for fake, #rho corrected; pHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_NeutralHadIso_FakeShowershape(new TH1F("h_NeutralHadIso_FakeShowershape","NeutralHadIso distribution for fake failing showershape, #rho corrected; nHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_PhotonHadIso_FakeShowershape(new TH1F("h_PhotonHadIso_FakeShowershape","PhotonHadIso distribution for fake failing showershape, #rho corrected; pHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1F* h_SigmaIetaIeta_Fake(new TH1F("h_SigmaIetaIeta_Fake","SigmaIetaIeta distribution for fake; #sigma_{i#eta i#eta}; Events/0.0002 GeV",100,0,0.02));
   TH1F* h_SigmaIetaIeta(new TH1F("h_SigmaIetaIeta","SigmaIetaIeta distribution for #gamma and fake; #sigma_{i#eta i#eta}; Events/0.0002 GeV",100,0,0.02));
   TH1F* h_ChargedHadIso_FakeShowershape(new TH1F("h_ChargedHadIso_FakeShowershape","ChargedHadIso distribution for fake failing shower shape, #rho corrected; chHadIso (GeV); Events/0.4 GeV",100,0,40));
   TH1I* h_PhotonTrigger(new TH1I("h_PhotonTrigger","HLTPho Triger; TriggerBit; Events",25,0,25));
   
   TH1I* h_PhotonTrigger_EG(new TH1I("h_PhotonTrigger_EG","HLTPho Triger; TriggerBit; Events",25,0,25));
   TH1I* h_PhotonTrigger_EGOnly14(new TH1I("h_PhotonTrigger_EGOnly14","HLTPho Triger; TriggerBit; Events",25,0,25));
   TH1I* h_PhotonTrigger_EGOnly15(new TH1I("h_PhotonTrigger_EGOnly15","HLTPho Triger; TriggerBit; Events",25,0,25));
   TH1I* h_PhotonTrigger_EGOnly16(new TH1I("h_PhotonTrigger_EGOnly16","HLTPho Triger; TriggerBit; Events",25,0,25));
   TH1I* h_PhotonTrigger_EGOnly17(new TH1I("h_PhotonTrigger_EGOnly17","HLTPho Triger; TriggerBit; Events",25,0,25));
   
   TH2F* h_DoubleElectron_DiEMPtWeight(new TH2F("h_DoubleElectron_DiEMPtWeight","DiEMPt Weight for electron; diEMPt weight; Events/0.5GeV",diemptbinnum, diemptbinsdouble,10,0,5));
   TH2F* h_DoubleElectron_NJetWeight(new TH2F("h_DoubleElectron_NJetWeight","NJet Weight for electron; NJet weight; Events",8,0,8,10,0,5));
   TH2F* h_DoubleFake_DiEMPtWeight(new TH2F("h_DoubleFake_DiEMPtWeight","DiEMPt Weight for fake; diEMPt weight; Events/0.5",diemptbinnum, diemptbinsdouble,10,0,5));
   
   
   TH1F* h_EEGG_MET(new TH1F("h_EEGG_MET","E_{T}^{miss} for EEGG; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_EEFF_MET(new TH1F("h_EEFF_MET","E_{T}^{miss} for EEFF; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_GGFF_MET(new TH1F("h_GGFF_MET","E_{T}^{miss} for GGFF; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_EEGGUnseparated_MET(new TH1F("h_EEGGUnseparated_MET","E_{T}^{miss} for EEGG; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_EEFFUnseparated_MET(new TH1F("h_EEFFUnseparated_MET","E_{T}^{miss} for EEFF; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_GGFFUnseparated_MET(new TH1F("h_GGFFUnseparated_MET","E_{T}^{miss} for GGFF; E_{T}^{miss} (GeV); Events/ GeV",binnum,xbins));
   TH1F* h_DoubleFake_MET_WeightSignalRegion(new TH1F("h_DoubleFake_MET_WeightSignalRegion","DiEMPt weight for double fake, E_{T}^{miss}>100 GeV; Weight; Events",50,0,5));
   TH1F* h_DoubleFake_DiEMPt_SignalRegion(new TH1F("h_DoubleFake_DiEMPt_SignalRegion","DiEMPt for double fake, E_{T}^{miss}>100 GeV; Weight; Events",500,0,500));
   
   
   
   TH2F *h_DoublePhoton_NJet_vs_DiEMPt(new TH2F("h_DoublePhoton_NJet_vs_DiEMPt", "NJet vs DiEMPt, DoublePhoton", diemptbinnum, diemptbinsdouble, 8, 0, 8));
   TH2F *h_DoubleElectron_NJet_vs_DiEMPt(new TH2F("h_DoubleElectron_NJet_vs_DiEMPt", "NJet vs DiEMPt, DoubleElectron", diemptbinnum, diemptbinsdouble, 8, 0, 8));
   TH2F *h_DoubleFake_NJet_vs_DiEMPt(new TH2F("h_DoubleFake_NJet_vs_DiEMPt", "NJet vs DiEMPt, DoubleFake", diemptbinnum, diemptbinsdouble, 8, 0, 8));
   
   TH1F *h_DoubleElectron_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[1000];
   TH1F *h_DoubleElectron_MET_NJetsReweighted_ErrorPropagatedFromNJets[1000];
   TH1F *h_DoubleElectron_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[1000];
    
   char *histNameee        = new char[100];
   char *histtitleee       = new char[100];

   for (int d=0;d<1000; ++d){
     sprintf(histNameee, "DiEMPtReweightedee%d",d+1);
     sprintf(histtitleee,"Reweighted ee E_{T}^{miss} with DIEMPT %d",d+1);
     h_DoubleElectron_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "NJetsReweightedee%d",d+1);
     sprintf(histtitleee,"Reweighted ee E_{T}^{miss} with NJets %d",d+1);
     h_DoubleElectron_MET_NJetsReweighted_ErrorPropagatedFromNJets[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "DiEMPtReweightedNJetsee%d",d+1);
     sprintf(histtitleee,"Reweighted ee NJets with diEMPt %d",d+1);
     h_DoubleElectron_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
   }
   
   TH1F *h_DoubleFake_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[1000];
   TH1F *h_DoubleFake_MET_NJetsReweighted_ErrorPropagatedFromNJets[1000];
   TH1F *h_DoubleFake_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[1000];

   for (int d=0;d<1000; ++d){
     sprintf(histNameee, "DiEMPtReweightedff%d",d+1);
     sprintf(histtitleee,"Reweighted ff E_{T}^{miss} with DIEMPT %d",d+1);
     h_DoubleFake_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "NJetsReweightedff%d",d+1);
     sprintf(histtitleee,"Reweighted ff E_{T}^{miss} with NJets %d",d+1);
     h_DoubleFake_MET_NJetsReweighted_ErrorPropagatedFromNJets[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "DiEMPtReweightedNJetsff%d",d+1);
     sprintf(histtitleee,"Reweighted ff diEMPt with NJets %d",d+1);
     h_DoubleFake_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
   }
   
   
   TH1F *h_DoubleFakeShowershape_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[1000];
   TH1F *h_DoubleFakeShowershape_MET_NJetsReweighted_ErrorPropagatedFromNJets[1000];

   for (int d=0;d<1000; ++d) {
     sprintf(histNameee, "DiEMPtReweightedffshowershape%d",d+1);
     sprintf(histtitleee,"Reweighted ff E_{T}^{miss} with DIEMPT %d",d+1);
     h_DoubleFakeShowershape_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "NJetsReweightedffshowershape%d",d+1);
     sprintf(histtitleee,"Reweighted ff E_{T}^{miss} with NJets %d",d+1);
     h_DoubleFakeShowershape_MET_NJetsReweighted_ErrorPropagatedFromNJets[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
   }
   
   
   
   
   TH1F *h_DoubleElectron_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[1000];
   TH1F *h_DoubleFake_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[1000];

   for (int d=0;d<1000; ++d) {
     sprintf(histNameee, "DiEMPtVsNJetReweightedee%d",d+1);
     sprintf(histtitleee,"Reweighted ee E_{T}^{miss} with DIEMPT vs NJet %d",d+1);
     h_DoubleElectron_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
     sprintf(histNameee, "DiEMPtVsNJetReweightedff%d",d+1);
     sprintf(histtitleee,"Reweighted ff E_{T}^{miss} with DIEMPT vs NJet %d",d+1);
     h_DoubleFake_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[d]=new TH1F(histNameee,histtitleee,binnum, xbins);
   }
   
   
   TFile *Fnew = new TFile("DIEMPtRatioRRR.root","READ");
   TH1F *eephotondiempt = (TH1F*)Fnew->Get("eephotondiempt");
   TH1F *ffphotondiempt = (TH1F*)Fnew->Get("ffphotondiempt");
   TH1F *ffshowershapephotondiempt = (TH1F*)Fnew->Get("ffshowershapephotondiempt");
   TH1F *eephotonnjets = (TH1F*)Fnew->Get("eephotonnjets");
   TH1F *ffphotonnjets = (TH1F*)Fnew->Get("ffphotonnjets");
   TH1F *ffshowershapephotonnjets = (TH1F*)Fnew->Get("ffshowershapephotonnjets");
   TH2F *eephotondiemptnjets2D = (TH2F*)Fnew->Get("eephotondiemptnjets2D");
   TH2F *ffphotondiemptnjets2D = (TH2F*)Fnew->Get("ffphotondiemptnjets2D");
   
   
   TFile *FRandom = new TFile("RandomRatioErrorPropRRR.root","READ");
   TH1F *DiEMPtRatioGaus[1000];
   TH1F *DiEMPtRatioFFGaus[1000];
   TH1F *DiEMPtRatioFFShowershapeGaus[1000];
   TH1F *NJetsRatioGaus[1000];
   TH1F *NJetsRatioFFGaus[1000];
   TH1F *NJetsRatioFFShowershapeGaus[1000];
   TH2F *DiEMPtVsNJetRatioEE[1000];
   TH2F *DiEMPtVsNJetRatioFF[1000];
   
   // getting error propagation from diEMPt ratio
   for(int g=0; g<1000; ++g){
     char *nameGraph        = new char[60];

     sprintf(nameGraph,"DiEMPtee%d",g+1);
     DiEMPtRatioGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     sprintf(nameGraph,"DiEMPtff%d",g+1);
     DiEMPtRatioFFGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     sprintf(nameGraph,"DiEMPtffshowershape%d",g+1);
     DiEMPtRatioFFShowershapeGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     
     sprintf(nameGraph,"NJetsee%d",g+1);
     NJetsRatioGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     sprintf(nameGraph,"NJetsff%d",g+1);
     NJetsRatioFFGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     sprintf(nameGraph,"NJetsffshowershape%d",g+1);
     NJetsRatioFFShowershapeGaus[g] = (TH1F*)FRandom->Get(nameGraph);
     
     sprintf(nameGraph,"EEDiEMPtNJet2DRatio%d",g+1);
     DiEMPtVsNJetRatioEE[g] = (TH2F*)FRandom->Get(nameGraph);
     sprintf(nameGraph,"FFDiEMPtNJet2DRatio%d",g+1);
     DiEMPtVsNJetRatioFF[g] = (TH2F*)FRandom->Get(nameGraph);
     
   }
   
   //float 1.0 = 50100*1000*0.318*5/10017930.0;
   
   float fakerate = 0.021;
   float fakerateup = 0.023;
   float fakeratedown = 0.019;
   ////////////// change your jet requirement here /////////////////
   
   unsigned int jetRequirement = 2;
   
   //TH1F* h_ShowerShape_Electron(new TH1F("h_ShowerShape_Electron", "Showershape distribution, electron;showershape;Events",40,0,0.1));
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   bool Debug = false;
   
   int PhotonNu(0), FakeNu(0), ElectronNu(0), totalphoton(0), totalmismatchphoton(0);
   int EventCutFlow[10] = {0};//NeutralCut(0), EventChargedCut(0), EventPhotonIsoCut(0), EventShowerShapeCut(0), EventHoverECut(0), EventAfterPtCut(0);
   int EventElectronDr(0), EventOnlyElectron(0), EventHEElectron(0), TotalFake(0);
   TString CutFlowLabels[9] = {"nocut", "neutral", "charged", "photoniso","showershape","Pt","PixelMatch","HoverE","DeltaR"};
   cout << "Total Events: " << nentries << endl;
   
   int triggerBit[25]={0};
   
//    ofstream myfile;
//    myfile.open("ElectronAnalysis.txt");
   ofstream myfile_fake;
   myfile_fake.open("FakeAnalysis.txt");
   
   ofstream myfile_photon;
   myfile_photon.open("DetailsPhoton.txt");
   myfile_photon << "Run" << "\tLumis" << "\tEvent" << "\tLead Photon Pt" << "\tLead Photon Eta" << "\tLead Photon Phi" << "\tLead Photon E" << "\tTrail Photon Pt" << "\tTrail Photon Eta" << "\tTrail Photon Phi" << "\tTrail Photon E" << "\tMass" << endl;
  
  
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      /// Selecting good vertex ///
      
      if(!(NVtx>0))continue;
      if(!(METFilters==0))continue;
      
      if(jentry %10000 == 0)cout << "processed: " << jentry << endl;
      if(jentry >100000)break;
      //if(jentry > 200000)break;
      if(Debug)cout << "Just in event loop " << jentry << endl; 
      //if(jentry <  8810000)continue;
      
      int realphoton(0), fake(0), electron(0), fakeShowershape(0);
      int NeutralCut(0), ChargedCut(0), PhotonIsoCut(0), ShowerShapeCut(0), HoverECut(0), AfterPtCut(0), HoverECutElectron(0);
      int OnlyPhoton(0), OnlyElectron(0), NoCut(0);
      vector<int> realphoton_tracker, fake_tracker, fakeShowershape_tracker, electron_tracker, showershape_tracker, pt_tracker;
      realphoton_tracker.clear(); fake_tracker.clear(); fakeShowershape_tracker.clear(); electron_tracker.clear(); showershape_tracker.clear(); pt_tracker.clear();
      
      vector<Object> Work2;
      Work2.clear();
      //if(MCPID->size()>0)cout <<"MC: " << MCPID->size() <<endl;
      /*if(jentry==17){
        cout << "nPho: " << nPho << endl;
        cout << "phoSize: " << phoEta->size() << endl;
      }*/
      
      int fakephoton_count(0);
      vector <float> PhotonEta, ElectronEta;
      vector <float> PhotonPhi, ElectronPhi;
      vector <float> GoodMuonEta, GoodMuonPhi;
      vector <float> FakePhotonPt, ElectronMatchedPtVect, DzVect;
      vector <float> NTrksVect;
      PhotonEta.clear(); ElectronEta.clear();
      GoodMuonEta.clear(); GoodMuonPhi.clear();
      PhotonPhi.clear(); ElectronPhi.clear();
      FakePhotonPt.clear(); ElectronMatchedPtVect.clear(); DzVect.clear();
      NTrksVect.clear();
      
      h_NTrks_All->Fill(NTrks, 1.0);
      
      
      // photon loop starts
      for(size_t i=0;i < PhoEta->size(); ++i){
        //cout << i << endl;
	Object tempFile;
        if(Debug)cout << "Just in photon loop " << jentry << endl;
        float absEta = fabs(PhoEta->at(i));
	float absSCEta = fabs(PhoSCEta->at(i));
        double effA[4];
        photonEffectiveAreas(absEta, effA);
        if(/*(absSCEta > 1.4442) ||*/ (PhoR9->at(i) > 1.0))continue;
	// containing newest cuts fron https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2
	
        float pt = fabs(PhoEt->at(i)); 
        bool neutral         = (PhoPFNeuIso->at(i) - Rho * effA[1] -  (0.014*pt+0.000019*pt*pt)) < 1.06;
        bool charged         = (PhoPFChIso->at(i) - Rho * effA[0]) < 1.37;
        bool chargedfake     = (PhoPFChIso->at(i) - Rho * effA[0]) > 1.37;
        bool chargedlim      = (PhoPFChIso->at(i) - Rho * effA[0]) < 15.;
	bool chargedlimloose = (PhoPFChIso->at(i) - Rho * effA[0]) < 40.;
        bool photoniso       = (PhoPFPhoIso->at(i) - Rho * effA[2] - 0.0053*pt) < 0.28;
        //printf("absEta: %f and effACh: %f effPh:%f and effN:%f\n", absEta,effA[0],effA[2],effA[1]);
        bool worstiso        = (PhoPFChWorstIso->at(i) -Rho*effA[3]) < 2.6;
        bool showercut       = PhoSigmaIEtaIEta->at(i) > 0.005 && PhoSigmaIEtaIEta->at(i) < 0.0102 ;
	bool showercutfake   = PhoSigmaIEtaIEta->at(i) > 0.0102;
        bool shower          = PhoSigmaIEtaIEta->at(i) < 0.015;
	bool showerloose     = PhoSigmaIEtaIEta->at(i) < 0.020;
        bool pixelcut        = PhohasPixelSeed->at(i) == 0;
        //cout << phohasPixelSeed->at(i) << endl;
        bool HoverE          = PhoHoverE->at(i) < 0.05;
        bool SymPtCut        = pt > RRR;
	
	bool neutralECTightSpring15   = ( PhoPFNeuIso->at(i) - Rho * effA[1] - (0.0139*pt+0.000025*pt*pt) ) < 2.69;
        bool chargedECTightSpring15   = ( PhoPFChIso->at(i) - Rho * effA[0] ) < 1.10;
        bool photonisoECTightSpring15 = ( PhoPFPhoIso->at(i) - Rho * effA[2] - 0.0034*pt ) < 0.39;
        bool showercutECTightSpring15 = PhoSigmaIEtaIEta->at(i) < 0.0268 ; 
        bool HoverEECTightSpring15    = PhoHoverE->at(i) < 0.05;
        
        if(Debug)cout << "photon selection ends " << jentry << endl;
        //if(jentry==535519)printf("yy pixelseed head:%d\n",photon_pixelseed->at(i));
        NoCut++;
        if(neutral){
          NeutralCut++;
          if(charged){
            ChargedCut++;
            if(photoniso){
              PhotonIsoCut++;
              showershape_tracker.push_back(i);
              //h_ShowerShape->Fill(phoSigmaIEtaIEta->at(i));
              if(showercut){
                ShowerShapeCut++;
                pt_tracker.push_back(i);
                if(SymPtCut){
                  AfterPtCut++;
                  if(pixelcut){
                    OnlyPhoton++;
                    h_HoverE_Photon->Fill(PhoHoverE->at(i));
                    if(HoverE){
                      HoverECut++;
                    }
                  }
                  if(!pixelcut){
                    OnlyElectron++;
                    h_HoverE_Electron->Fill(PhoHoverE->at(i));
                    if(HoverE){
                      HoverECutElectron++;
                    }
                  }
                }
              }
            } 
          }
        }
        //if(neutral && charged && photoniso && pixelcut && HoverE && SymPtCut )h_ShowerShape_Photon->Fill(phoSigmaIEtaIEta->at(i));
        //if(neutral && charged && photoniso && !pixelcut && HoverE && SymPtCut )h_ShowerShape_Electron->Fill(phoSigmaIEtaIEta->at(i));
        
        
        /// needed for plotting some isolation variables ////////
        if(charged && photoniso && showercut && pixelcut && HoverE && SymPtCut)h_NeutralHadIso_Photon->Fill(PhoPFNeuIso->at(i) - Rho * effA[1] -  exp(0.0028*pt+0.5408));
	if(neutral && charged && showercut && pixelcut && HoverE && SymPtCut)h_PhotonHadIso_Photon->Fill(PhoPFPhoIso->at(i) - Rho * effA[2] - 0.0014*pt);
	if(neutral && charged && photoniso && pixelcut && HoverE && SymPtCut)h_SigmaIetaIeta_Photon->Fill(PhoSigmaIEtaIEta->at(i));
	
	if(!charged && chargedlim && photoniso && showercut && pixelcut && HoverE && SymPtCut)h_NeutralHadIso_Fake->Fill(PhoPFNeuIso->at(i) - Rho * effA[1] -  exp(0.0028*pt+0.5408));
	if(neutral && !charged && chargedlim && showercut && pixelcut && HoverE && SymPtCut)h_PhotonHadIso_Fake->Fill(PhoPFPhoIso->at(i) - Rho * effA[2] - 0.0014*pt);
	if(neutral && !charged && chargedlim && photoniso && pixelcut && HoverE && SymPtCut)h_SigmaIetaIeta_Fake->Fill(PhoSigmaIEtaIEta->at(i));
	
	
	if(charged && photoniso && !showercut && pixelcut && HoverE && SymPtCut)h_NeutralHadIso_FakeShowershape->Fill(PhoPFNeuIso->at(i) - Rho * effA[1] -  exp(0.0028*pt+0.5408));
	if(neutral && charged && !showercut && pixelcut && HoverE && SymPtCut)h_PhotonHadIso_FakeShowershape->Fill(PhoPFPhoIso->at(i) - Rho * effA[2] - 0.0014*pt);
	if(neutral && charged && photoniso && pixelcut && HoverE && SymPtCut)h_SigmaIetaIeta->Fill(PhoSigmaIEtaIEta->at(i));
	if(neutral && photoniso && !showercut && pixelcut && HoverE && SymPtCut)h_ChargedHadIso_FakeShowershape->Fill(PhoPFChIso->at(i) - Rho * effA[0]);
	
	if(neutral && photoniso && showercut && pixelcut && HoverE && SymPtCut)h_ChargedHadIso->Fill(PhoPFChIso->at(i) - Rho * effA[0]);
	if(neutral && photoniso && pixelcut && HoverE && SymPtCut)h_ChargedHadIso_WithoutShowerCut->Fill(PhoPFChIso->at(i) - Rho * effA[0]);
        
        /////////////// photon //////////////////////////////////
	if(absSCEta < 1.4442){
	  if(neutral && charged && photoniso && showercut && pixelcut && HoverE && SymPtCut ){//
	    cout << "photon inside loop: " << jentry << endl; 
	    //photon GenLevel Matching
	    tempFile.photonType=1; // 1 for photon
	    tempFile.pt=PhoEt->at(i);
	    tempFile.tracker=i;
	    Work2.push_back(tempFile);
	    realphoton++;
	    totalphoton++;
	    PhotonEta.push_back(PhoEta->at(i));
	    PhotonPhi.push_back(PhoPhi->at(i));
	    realphoton_tracker.push_back(i);
	    if(PhohasPixelSeed->at(i) != PhoEleVeto->at(i))totalmismatchphoton++;
	    if(Debug)cout << "doublephoton selection  " << jentry << endl;
	  } //worstiso not used*/
	}
        else{
	  if(neutralECTightSpring15 && chargedECTightSpring15 && photonisoECTightSpring15 && showercutECTightSpring15 && pixelcut && HoverEECTightSpring15 && SymPtCut ){//
	    //cout << "photon inside loop: " << jentry << endl; 
	    // photon GenLevel Matching
	    tempFile.photonType=1; // 1 for photon
	    tempFile.pt=PhoEt->at(i);
	    tempFile.tracker=i;
	    Work2.push_back(tempFile);
	    realphoton++;
	    totalphoton++;
	    PhotonEta.push_back(PhoEta->at(i));
	    PhotonPhi.push_back(PhoPhi->at(i));
	    //realphoton_tracker.push_back(i);
	    if(PhohasPixelSeed->at(i) != PhoEleVeto->at(i))totalmismatchphoton++;
	    if(Debug)cout << "doublephoton selection  " << jentry << endl;
	  } //worstiso not used*/
	}
        
        
        
        
        
        //////////////////// fake Old definition ////////////////////////////////
        if(neutral && chargedfake && chargedlim && photoniso && showercut && pixelcut  && HoverE && SymPtCut ){
          fakeShowershape++;
          fakeShowershape_tracker.push_back(i);
          if(Debug)cout << "doublefake selection  " << jentry << endl;
        }
        
        /////////////// Analysis Fake //////////
        //////////////////// fake failing showershape or chargediso but not both  ////////////////////////////////
//         if(neutral && photoniso && pixelcut && HoverE && SymPtCut ){
// 	  if((chargedfake && chargedlim) || (showercutfake && shower)){
// 	    if((chargedfake && chargedlim) && (showercutfake && shower))continue;
//             tempFile.photonType=3; // 3 for fake
// 	    tempFile.pt=PhoEt->at(i);
// 	    tempFile.tracker=i;
// 	    Work2.push_back(tempFile);
// 	    fake++;
//             //fake_tracker.push_back(i);
//             if(Debug)cout << "doublefake selection  " << jentry << endl;
// 	  }
//         }
        
        
           ////////////// Extended Fake /////////////////////////
        ////////////////// loose fake cut  ////////////////////////////////
        if(pixelcut && HoverE && SymPtCut ){
	  if( ((chargedfake && chargedlimloose) && (showercutfake && showerloose)) || ((chargedfake && chargedlimloose) && (showercut)) || (((charged) && (showercutfake && showerloose))) ){
            tempFile.photonType=3; // 3 for fake
	    tempFile.pt=PhoEt->at(i);
	    tempFile.tracker=i;
	    Work2.push_back(tempFile);
	    fake++;
            //fake_tracker.push_back(i);
            if(Debug)cout << "doublefake selection  " << jentry << endl;
	  }
        }
     
        
        
        
        
        
        
        ////////////////// electron ///////////////////////////////////
        if(neutral && charged && photoniso && showercut && !pixelcut && HoverE && SymPtCut ){// 
           electron++;
	  //cout << "electron inside loop: " << jentry << endl;
	  tempFile.photonType=2; // 2 for electron
	  tempFile.pt=PhoEt->at(i);
	  tempFile.tracker=i;
	  Work2.push_back(tempFile);
	  ElectronEta.push_back(PhoEta->at(i));
	  ElectronPhi.push_back(PhoPhi->at(i));
	  //electron_tracker.push_back(i);
	}
	
	
	
	
      }// photon loop ends
      
      
      
      
      // triggerBit info
      if(realphoton >= 2 || electron >= 2 || fake >= 2){
	for(int q=0; q<22;++q){
	  if(((HLT_Pho>>q)&1) == 1){triggerBit[q]++;}
        }
      }
      // trigger selection, for info see this: https://github.com/cmkuo/ggAnalysis/blob/master/ggNtuplizer/plugins/ggNtuplizer_globalEvent.cc#L279
      if(!(HLT_Pho>>14&1 || HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1 || HLT_Pho>>18&1 || HLT_EleMuX>>2&1 ))continue;
      
      ExtendedObject FinalEvent = Selection(Work2); // Object selection and deciding which events to be carried on.
      
      if(FinalEvent.photonType1 == 1 && FinalEvent.photonType2 == 1){
	//if(Work2.size()>2)cout << "This is a photon-photon event: " << jentry << endl;
	realphoton_tracker.push_back(FinalEvent.tracker1);
	realphoton_tracker.push_back(FinalEvent.tracker2);
	//if(Work2.size()>2)cout << "These are the two photon events: " << FinalEvent.tracker1 << " , " << FinalEvent.tracker2 << endl;
      }
      else if(FinalEvent.photonType1 == 2 && FinalEvent.photonType2 == 2){
	//if(Work2.size()>2)cout << "This is a electron-electron event: " << jentry << endl;
	electron_tracker.push_back(FinalEvent.tracker1);
	electron_tracker.push_back(FinalEvent.tracker2);
	//if(Work2.size()>2)cout << "These are the two electron events: " << FinalEvent.tracker1 << " , " << FinalEvent.tracker2 << endl;
      }
      else if(FinalEvent.photonType1 == 3 && FinalEvent.photonType2 == 3){
	//if(Work2.size()>2)cout << "This is a fake-fake event: " << jentry << endl;
	fake_tracker.push_back(FinalEvent.tracker1);
	fake_tracker.push_back(FinalEvent.tracker2);
	//if(Work2.size()>2)cout << "These are the two fake events: " << FinalEvent.tracker1 << " , " << FinalEvent.tracker2 << endl;
      }
      else if(FinalEvent.photonType1 == 1 && FinalEvent.photonType2 == 2){
	//if(Work2.size()>2)cout << "This is a photon-electron event: " << jentry << endl;
	realphoton_tracker.push_back(FinalEvent.tracker1);
	electron_tracker.push_back(FinalEvent.tracker2);
	//if(Work2.size()>2)cout << "These are the two photon-electron (in order) events: " << FinalEvent.tracker1 << " , " << FinalEvent.tracker2 << endl;
      }
      
//       if(electron_tracker.size()==2){
// 	float DR = dRCalc(PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), PhoEta->at(electron_tracker.at(1)), PhoPhi->at(electron_tracker.at(1)));
// 	if(DR<0.3)continue;
// 	if(fake_tracker.size()>=2){
// 	  float DRfake = dRCalc(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)));
// 	  if(DRfake>0.3)h_EEFF_MET->Fill(PFMET);
// 	}
// 	if(realphoton_tracker.size()>=2){
// 	  float DRpho = dRCalc(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)));
// 	  if(DRpho>0.3)h_EEGG_MET->Fill(PFMET);
// 	}
//       }
//       if(realphoton_tracker.size()>=2){
// 	float DRpho = dRCalc(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)));
// 	if(DRpho<0.3)continue;
// 	if(fake_tracker.size()>=2){
// 	  float DRfake = dRCalc(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)));
// 	  if(DRfake>0.3)h_GGFF_MET->Fill(PFMET);
// 	}
//       }
//       if(electron_tracker.size()>=2 && realphoton_tracker.size()>=2){
// 	h_EEGGUnseparated_MET->Fill(PFMET);
// 	continue;
//       }
//       if(electron_tracker.size()>=2 && fake_tracker.size()>=2){
// 	h_EEFFUnseparated_MET->Fill(PFMET);
// 	continue;
//       }
//       if(realphoton_tracker.size()>=2 && fake_tracker.size()>=2){
// 	h_GGFFUnseparated_MET->Fill(PFMET);
// 	continue;
//       }

      //muon selection
      vector<int> GoodMuonTracker;
      GoodMuonTracker.clear();
      if(Debug)cout << "Muon selection for entry: " << jentry << endl;
      for(size_t w=0; w < MuPt->size();++w){
        if(!(MuIsGood->at(w)==1 && fabs(MuEta->at(w))<1.4442 && MuPt->at(w)>30))continue;
	//if(!(MuIsLooseID->at(w)==1 && fabs(MuEta->at(w))<1.4442 && MuPt->at(w)>30))continue;
        //cout << "max: " << MuEta->at(w) << endl;
	// turned on muon isolation
        float combIso  = MuPFChIso->at(w) + TMath::Max(0.,MuPFNeuIso->at(w) + MuPFPhoIso->at(w) - 0.5*MuPFPUIso->at(w));
        if( combIso/MuPt->at(w) > 0.25 )continue;
        GoodMuonEta.push_back(MuEta->at(w));
        GoodMuonPhi.push_back(MuPhi->at(w));
        GoodMuonTracker.push_back(w);
      }
      
      
      
      
      //jet selection
      unsigned int jetNumAll(0);
      float ht(0);
      vector<float> GoodJetPt, GoodJetEta, GoodJetPhi;
      GoodJetPt.clear(); GoodJetEta.clear(); GoodJetPhi.clear();
      for(size_t w=0; w < JetPt->size(); ++w){
        if(!(JetPt->at(w) > 30 && JetPFLooseId))continue;//&& )
        if(fabs(JetEta->at(w) > 2.4))continue;
        float drminpho(9999), drminele(9999), drminmu(9999), drminfake(999);
        if(Debug)cout << "photon: " << PhotonEta.size() << " electron: " << ElectronEta.size() << " muon: " << GoodMuonEta.size() << " for entry: " << jentry << endl;
        for(size_t r=0; r < PhotonEta.size(); ++r){
          float drJetPho = dRCalc(JetEta->at(w), JetPhi->at(w), PhotonEta.at(r), PhotonPhi.at(r));
          if(!(drJetPho < drminpho))continue;
          drminpho = drJetPho;
        }
        for(size_t r=0; r < fake_tracker.size(); ++r){
          float drJetFake = dRCalc(JetEta->at(w), JetPhi->at(w), PhoEta->at(fake_tracker.at(r)), PhoPhi->at(fake_tracker.at(r)));
          if(!(drJetFake < drminfake))continue;
          drminfake = drJetFake;
        }
        for(size_t r=0; r < ElectronEta.size(); ++r){
          float drJetEle = dRCalc(JetEta->at(w), JetPhi->at(w), ElectronEta.at(r), ElectronPhi.at(r));
          if(!(drJetEle < drminele))continue;
          drminele = drJetEle;
        }
        for(size_t r=0; r < GoodMuonEta.size(); ++r){
          float drJetMu = dRCalc(JetEta->at(w), JetPhi->at(w), GoodMuonEta.at(r), GoodMuonPhi.at(r));
          if(!(drJetMu < drminmu))continue;
          drminmu = drJetMu;
        }
        
        if( PhotonEta.size() > 0 && drminpho < 0.4 )continue;
        if( ElectronEta.size() > 0 && drminele < 0.4 )continue;
        if( GoodMuonEta.size() > 0 && drminmu < 0.4 )continue;
	ht += JetPt->at(w);
	GoodJetPt.push_back(JetPt->at(w));
	GoodJetEta.push_back(JetEta->at(w));
	GoodJetPhi.push_back(JetPhi->at(w));
	if( fake_tracker.size() > 0 && drminfake < 0.4 )continue;
        if(Debug)cout << "Inside jet selection loop for entry: " << jentry << endl;
	jetNumAll++;
        //cout << "Ht: " << ht << endl;
      }
      h_Ht->Fill(ht, 1.0);
      
      if(Debug)cout << "total jets: " << jetNumAll << " for entry:" << jentry << endl;
      
      
      // if (Cut(ientry) < 0) continue;
      if(realphoton == 1)h_SinglePhoton_MET->Fill(PFMET);
      // double photon selection
      if(realphoton_tracker.size() == 2){
	///Only selecting this trigger for photon: HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v
	//if(!(HLT_Pho>>14&1))continue;
	
	if(!( HLT_Pho>>16&1 || HLT_Pho>>17&1 ))continue; // this is to take photon for Harrison and Pushpa with double electron trigger Inv Mass > 55 GeV.
	
	//if(!(jetNumAll > jetRequirement))continue;
        PhotonNu++;
        float DR = dRCalc(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)));
	float DiEMPt = findDiEMPt(PhoE->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoE->at(realphoton_tracker.at(1)), PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)));
	float Mass = findMass(PhoE->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoE->at(realphoton_tracker.at(1)), PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)));
        if(!(Mass>60))continue; // originally 105 GeV
	/// cleaning of the photon ///
	bool CloseElectronLead(false), CloseElectronTrail(false);
	bool CloseMuonLead(false), CloseMuonTrail(false);
	
	for(size_t h=0; h < ElectronEta.size(); ++h){
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), ElectronEta.at(h), ElectronPhi.at(h), 0.3)){
	    CloseElectronLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)), ElectronEta.at(h), ElectronPhi.at(h), 0.3)){
	    CloseElectronTrail = true;
	    break;
	  }
	}
	if(CloseElectronLead || CloseElectronTrail)continue;
	
	for(size_t h=0; h < GoodMuonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(1)), PhoPhi->at(realphoton_tracker.at(1)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonTrail = true;
	    break;
	  }
	}
	if(CloseMuonLead || CloseMuonTrail)continue;
	
	float deltaPhi = dPhiCalc(PhoPhi->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(1)));
	h_DoublePhoton_DeltaPhi->Fill(deltaPhi, 1.0);
        if(DR>0.3){
	  if(PFMET>100)h_DoublePhoton_SignalInvMass->Fill(Mass, 1.0);
	  h_DoublePhoton_AllInvMass->Fill(Mass, 1.0);
	  myfile_photon << Run << "\t" << Lumis << "\t" << Event << "\t" << PhoEt->at(realphoton_tracker.at(0)) << "\t" << PhoEta->at(realphoton_tracker.at(0)) << "\t" << PhoPhi->at(realphoton_tracker.at(0)) << "\t" << PhoE->at(realphoton_tracker.at(0)) << "\t" << PhoEt->at(realphoton_tracker.at(1)) << "\t" << PhoEta->at(realphoton_tracker.at(1)) << "\t" << PhoPhi->at(realphoton_tracker.at(1)) << "\t" << PhoE->at(realphoton_tracker.at(1)) << "\t" << Mass << endl;
	  
	  
	  if((PhoEta->at(realphoton_tracker.at(0)) > 1.4442) || (PhoEta->at(realphoton_tracker.at(1)) > 1.4442))h_DoublePhoton_AllInvMass_Endcap->Fill(Mass, 1.0);
	  h_DoublePhoton_DeltaPhi_AfterDRCut->Fill(deltaPhi, 1.0);
          h_DoublePhoton_DiEMPt->Fill(DiEMPt, 1.0);
	  h_DoublePhoton_Rho->Fill(Rho, 1.0);
	  h_DoublePhoton_Nvtx->Fill(NVtx, 1.0);
	  h_DoublePhoton_MET->Fill(PFMET, 1.0);
	  
	  if(jetNumAll>0 && jetNumAll<3)h_DoublePhoton_MET_NJet1to2->Fill(PFMET, 1.0);
	  if(jetNumAll>2 && jetNumAll<5)h_DoublePhoton_MET_NJet3to4->Fill(PFMET, 1.0);
	  
	  if(DiEMPt>30 && DiEMPt<50)h_DoublePhoton_MET_DiEMPt30to50->Fill(PFMET, 1.0);
          if(DiEMPt>50 && DiEMPt<70)h_DoublePhoton_MET_DiEMPt50to70->Fill(PFMET, 1.0);
          if(DiEMPt>70 && DiEMPt<100)h_DoublePhoton_MET_DiEMPt70to100->Fill(PFMET,1.0);
	  
	  if(PFMET<100)h_DoublePhoton_MET_Upto100->Fill(PFMET, 1.0);
	  h_DoublePhoton_MET_Full->Fill(PFMET, 1.0);
	  h_DoublePhoton_NJets->Fill(jetNumAll, 1.0);
	  h_DoublePhoton_NJet_vs_DiEMPt->Fill(DiEMPt, jetNumAll);
	  h_DeltaPhi_LeadPhotonMET->Fill(dPhiCalc(PhoPhi->at(realphoton_tracker.at(0)), PFMETPhi));
	  h_DeltaPhi_TrailPhotonMET->Fill(dPhiCalc(PhoPhi->at(realphoton_tracker.at(1)), PFMETPhi));
	  h_LeadPhoton_Pt->Fill(PhoEt->at(realphoton_tracker.at(0)));
	  h_TrailPhoton_Pt->Fill(PhoEt->at(realphoton_tracker.at(1)));
	  
          EventCutFlow[8]++;
          if(Debug)cout << "inside doublephoton  " << jentry << endl;
          h_Photon_MET->Fill(PFMET);
        }
      }
      
      
      if(fake == 1)h_SingleFake_MET->Fill(PFMET);
      
      // double fake selection
      if(fake_tracker.size() == 2){
	/// only selecting this trigger for fake: HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v
	if(!(HLT_Pho>>14&1))continue;
	//if(!(jetNumAll > jetRequirement))continue;
        FakeNu++;
        float DR = dRCalc(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)));
	float DiEMPt = findDiEMPt(PhoE->at(fake_tracker.at(0)), PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhoE->at(fake_tracker.at(1)), PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)));
	float Mass = findMass(PhoE->at(fake_tracker.at(0)), PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhoE->at(fake_tracker.at(1)), PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)));
	if(!(Mass>105))continue;
	
	bool CloseElectronLead(false), CloseElectronTrail(false);
	bool CloseMuonLead(false), CloseMuonTrail(false);
	bool ClosePhotonLead(false), ClosePhotonTrail(false);
	
	for(size_t h=0; h < ElectronEta.size(); ++h){
	  if(isSameObject(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), ElectronEta.at(h), ElectronPhi.at(h), 0.4)){
	    CloseElectronLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)), ElectronEta.at(h), ElectronPhi.at(h), 0.4)){
	    CloseElectronTrail = true;
	    break;
	  }
	}
	if(CloseElectronLead || CloseElectronTrail)continue;
	
	for(size_t h=0; h < GoodMuonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.4)){
	    CloseMuonLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.4)){
	    CloseMuonTrail = true;
	    break;
	  }
	}
	if(CloseMuonLead || CloseMuonTrail)continue;
	
	for(size_t h=0; h < PhotonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(fake_tracker.at(0)), PhoPhi->at(fake_tracker.at(0)), PhotonEta.at(h), PhotonPhi.at(h), 0.4)){
	    ClosePhotonLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(fake_tracker.at(1)), PhoPhi->at(fake_tracker.at(1)), PhotonEta.at(h), PhotonPhi.at(h), 0.4)){
	    ClosePhotonTrail = true;
	    break;
	  }
	}
	if(ClosePhotonLead || ClosePhotonTrail)continue;
	
	
        if(DR>0.3){
	  h_DeltaPhi_LeadFakeMET->Fill(dPhiCalc(PhoPhi->at(fake_tracker.at(0)), PFMETPhi));
	  h_DeltaPhi_TrailFakeMET->Fill(dPhiCalc(PhoPhi->at(fake_tracker.at(1)), PFMETPhi));
	  h_LeadFake_Pt->Fill(PhoEt->at(fake_tracker.at(0)));
	  h_TrailFake_Pt->Fill(PhoEt->at(fake_tracker.at(1)));
	  h_DoubleFake_InvMass->Fill(Mass);
	  
	  if(jetNumAll>0 && jetNumAll<3)h_DoubleFake_MET_NJet1to2->Fill(PFMET, 1.0);
	  if(jetNumAll>2 && jetNumAll<5)h_DoubleFake_MET_NJet3to4->Fill(PFMET, 1.0);
	  if(DiEMPt>30 && DiEMPt<50)h_DoubleFake_MET_DiEMPt30to50->Fill(PFMET, 1.0);
          if(DiEMPt>50 && DiEMPt<70)h_DoubleFake_MET_DiEMPt50to70->Fill(PFMET, 1.0);
          if(DiEMPt>70 && DiEMPt<100)h_DoubleFake_MET_DiEMPt70to100->Fill(PFMET,1.0);
	  
          h_DoubleFake_NJets->Fill(jetNumAll, 1.0);
	  h_DoubleFake_MET->Fill(PFMET, 1.0);
	  h_DoubleFake_DiEMPt->Fill(DiEMPt, 1.0);
	  h_DoubleFake_NJet_vs_DiEMPt->Fill(DiEMPt, jetNumAll);
	  h_DoubleFake_Rho->Fill(Rho, 1.0);
	  h_DoubleFake_Nvtx->Fill(NVtx, 1.0);
	  int BinC=ffphotondiempt->FindBin(DiEMPt);
          float WeightC=ffphotondiempt->GetBinContent(BinC);
	  h_DoubleFake_NJets_Reweighted->Fill(jetNumAll, WeightC);
	  
	  int BinD=ffphotonnjets->FindBin(jetNumAll);
          float WeightD=ffphotonnjets->GetBinContent(BinD);
	  
	  //cout << "Fake weight: " << WeightC << " for event: " << jentry << endl;
	  h_DoubleFake_MET_Reweighted->Fill(PFMET, 1.0*WeightC);
	  h_DoubleFake_MET_ReweightedNJets->Fill(PFMET, 1.0*WeightD);
	  h_DoubleFake_MET_ReweightedDiEMPtNJets->Fill(PFMET, 1.0*WeightC*WeightD);
	  
	  h_DoubleFake_DiEMPtWeight->Fill(DiEMPt, WeightC);
	  
	  if(PFMET>100){
	    h_DoubleFake_MET_SignalRegion->Fill(PFMET, 1.0);
	    myfile_fake << "++++++++++++++++ fake-fake event ++++++++++++++++++++++++++++++" << endl;
	    myfile_fake << "Lumi No: " << Lumis << " Run: " << Run << " Event No: " << Event << " E_{T}^{miss}: " << PFMET << endl;
	    myfile_fake << "First fake object at photon position :" << fake_tracker.at(0) <<  " and Pt: " << PhoEt->at(fake_tracker.at(0)) << " phi: " << PhoPhi->at(fake_tracker.at(0)) << " eta: " << PhoEta->at(fake_tracker.at(0))<< endl;
	    myfile_fake << "Second fake object at photon position:" << fake_tracker.at(1) <<  " and Pt: " << PhoEt->at(fake_tracker.at(1)) << " phi: " << PhoPhi->at(fake_tracker.at(1)) << " eta: " << PhoEta->at(fake_tracker.at(1))<< endl;
	    myfile_fake << " The diempt of the event: " << DiEMPt << " and the diempt weight: " << WeightC << endl;
	    myfile_fake << " The MET of the event: " << PFMET << endl;
	    myfile_fake << " charged hadron iso of two fakes: " << PhoPFChIso->at(fake_tracker.at(0)) << " and " << PhoPFChIso->at(fake_tracker.at(1)) << endl;
	    myfile_fake << " showershape for two fakes: " << PhoSigmaIEtaIEta->at(fake_tracker.at(0)) << " and " << PhoSigmaIEtaIEta->at(fake_tracker.at(1)) << endl;
	    myfile_fake << " Invariant mass: " << Mass << endl;
	    h_DoubleFake_MET_WeightSignalRegion->Fill(WeightC);
	    h_DoubleFake_DiEMPt_SignalRegion->Fill(DiEMPt);
	  }
	  
	  
	  int Bin2DX=ffphotondiemptnjets2D->GetXaxis()->FindBin(DiEMPt);
	  int Bin2DY=ffphotondiemptnjets2D->GetYaxis()->FindBin(jetNumAll);
	  
	  float WeightFrom2D=ffphotondiemptnjets2D->GetBinContent(Bin2DX, Bin2DY);
	  h_DoubleFake_MET_ReweightedDiEMPtNJets_From2DRatio->Fill(PFMET, 1.0*WeightFrom2D);
	  
	  for( int s=0 ; s<1000; ++s){
            float Weightprop = DiEMPtRatioFFGaus[s]->GetBinContent(BinC);
            h_DoubleFake_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[s]->Fill(PFMET, Weightprop*1.0);
	    h_DoubleFake_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[s]->Fill(jetNumAll, Weightprop*1.0);
	    
	    float Weightprop2 = NJetsRatioFFGaus[s]->GetBinContent(BinD);
            h_DoubleFake_MET_NJetsReweighted_ErrorPropagatedFromNJets[s]->Fill(PFMET, Weightprop2*1.0);
            //cout << "Random Fake weight: " << Weightprop << " for event: " << jentry << " and E_{T}^{miss}" << PFMET << endl;
	    
	    float WeightProp2D = DiEMPtVsNJetRatioFF[s]->GetBinContent(Bin2DX, Bin2DY);
            h_DoubleFake_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[s]->Fill(PFMET, WeightProp2D*1.0);
	    	    
          }
          TotalFake++;
          h_Fake_MET->Fill(PFMET);
          if(Debug)cout << "inside doublefake  " << jentry << endl;
        }
      }
      
      // double fake failing showershape selection
      if(fakeShowershape ==2){
        /// only selecting this trigger for fake: HLT_Diphoton30_18_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95_v
	if(!(HLT_Pho>>14&1))continue;
	float DR = dRCalc(PhoEta->at(fakeShowershape_tracker.at(0)), PhoPhi->at(fakeShowershape_tracker.at(0)), PhoEta->at(fakeShowershape_tracker.at(1)), PhoPhi->at(fakeShowershape_tracker.at(1)));
	float DiEMPt = findDiEMPt(PhoE->at(fakeShowershape_tracker.at(0)), PhoEta->at(fakeShowershape_tracker.at(0)), PhoPhi->at(fakeShowershape_tracker.at(0)), PhoE->at(fakeShowershape_tracker.at(1)), PhoEta->at(fakeShowershape_tracker.at(1)), PhoPhi->at(fakeShowershape_tracker.at(1)));
        if(DR > 0.3){
	  h_DoubleFakeShowershape_MET->Fill(PFMET, 1.0);
	  h_DoubleFakeShowershape_DiEMPt->Fill(DiEMPt, 1.0);
	  h_DoubleFakeShowershape_Rho->Fill(Rho, 1.0);
	  h_DoubleFakeShowershape_Nvtx->Fill(NVtx, 1.0);
	  h_DoubleFakeShowershape_NJets->Fill(jetNumAll, 1.0);
	  int BinC=ffshowershapephotondiempt->FindBin(DiEMPt);
          float WeightC=ffshowershapephotondiempt->GetBinContent(BinC);
	  int BinD=ffshowershapephotonnjets->FindBin(jetNumAll);
          float WeightD=ffshowershapephotonnjets->GetBinContent(BinD);
	  h_DoubleFakeShowershape_MET_Reweighted->Fill(PFMET, 1.0*WeightC);
	  h_DoubleFakeShowershape_MET_ReweightedNJets->Fill(PFMET, 1.0*WeightD);
	  h_DoubleFakeShowershape_MET_ReweightedDiEMPtNJets->Fill(PFMET, 1.0*WeightC*WeightD);
	  for( int s=0 ; s<1000; ++s){
            float Weightprop = DiEMPtRatioFFShowershapeGaus[s]->GetBinContent(BinC);
            h_DoubleFakeShowershape_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[s]->Fill(PFMET, Weightprop*1.0);
	    float Weightprop2 = NJetsRatioFFShowershapeGaus[s]->GetBinContent(BinD);
            h_DoubleFakeShowershape_MET_NJetsReweighted_ErrorPropagatedFromNJets[s]->Fill(PFMET, Weightprop2*1.0);
          }
          if(Debug)cout << "inside doublefakeShowershape  " << jentry << endl;
        }
      }
      
      
      
      if(electron == 1)h_SingleElectron_MET->Fill(PFMET);
      
      // double electron selection 
      if(electron_tracker.size() == 2){
	if(!(HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1 || HLT_EleMuX>>2&1))continue;
	//if(!(jetNumAll > jetRequirement))continue;
        ElectronNu++;
        float DR = dRCalc(PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), PhoEta->at(electron_tracker.at(1)), PhoPhi->at(electron_tracker.at(1)));
	float Mass = findMass(PhoE->at(electron_tracker.at(0)), PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), PhoE->at(electron_tracker.at(1)), PhoEta->at(electron_tracker.at(1)), PhoPhi->at(electron_tracker.at(1)));
	
	float DiEMPt = findDiEMPt(PhoE->at(electron_tracker.at(0)), PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), PhoE->at(electron_tracker.at(1)), PhoEta->at(electron_tracker.at(1)), PhoPhi->at(electron_tracker.at(1)));
        h_DrAll->Fill(DR);
	/// cleaning of the electron ///
	bool CloseMuonLead(false), CloseMuonTrail(false);
	for(size_t h=0; h < GoodMuonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonLead = true;
	    break;
	  }
	  if(isSameObject(PhoEta->at(electron_tracker.at(1)), PhoPhi->at(electron_tracker.at(1)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonTrail = true;
	    break;
	  }
	}
	if(CloseMuonLead || CloseMuonTrail)continue;
	if(DR > 0.3 && (HLT_EleMuX>>2&1))h_DoubleElectron_InvMass->Fill(Mass, 1.0);
	if(!(HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1))continue;
        if(DR > 0.3 && Mass >75 && Mass <105){
          h_DoubleElectron_DiEMPt->Fill(DiEMPt, 1.0);
	  h_DoubleElectron_Rho->Fill(Rho, 1.0);
	  h_DoubleElectron_Nvtx->Fill(NVtx, 1.0);
	  h_DoubleElectron_NJets->Fill(jetNumAll, 1.0);
	  h_DoubleElectron_NJet_vs_DiEMPt->Fill(DiEMPt, jetNumAll);
	  h_DeltaPhi_LeadElectronMET->Fill(dPhiCalc(PhoPhi->at(electron_tracker.at(0)), PFMETPhi));
	  h_DeltaPhi_TrailElectronMET->Fill(dPhiCalc(PhoPhi->at(electron_tracker.at(1)), PFMETPhi));
	  h_LeadElectron_Pt->Fill(PhoEt->at(electron_tracker.at(0)));
	  h_TrailElectron_Pt->Fill(PhoEt->at(electron_tracker.at(1)));
	  
	  if(jetNumAll>0 && jetNumAll<3)h_DoubleElectron_MET_NJet1to2->Fill(PFMET, 1.0);
	  if(jetNumAll>2 && jetNumAll<5)h_DoubleElectron_MET_NJet3to4->Fill(PFMET, 1.0);
	  if(DiEMPt>30 && DiEMPt<50)h_DoubleElectron_MET_DiEMPt30to50->Fill(PFMET, 1.0);
          if(DiEMPt>50 && DiEMPt<70)h_DoubleElectron_MET_DiEMPt50to70->Fill(PFMET, 1.0);
          if(DiEMPt>70 && DiEMPt<100)h_DoubleElectron_MET_DiEMPt70to100->Fill(PFMET,1.0);
	  
	  int BinC=eephotondiempt->FindBin(DiEMPt);
          float WeightC=eephotondiempt->GetBinContent(BinC);
	  h_DoubleElectron_NJets_Reweighted->Fill(jetNumAll, WeightC);
	  
	  int BinD=eephotonnjets->FindBin(jetNumAll);
          float WeightD=eephotonnjets->GetBinContent(BinD);
	  //cout << "Electron weight: " << WeightC << " for event: " << jentry << endl;
	  h_DoubleElectron_MET_Reweighted->Fill(PFMET, 1.0*WeightC);
	  h_DoubleElectron_MET_ReweightedNJets->Fill(PFMET, 1.0*WeightD);
	  h_DoubleElectron_MET_ReweightedDiEMPtNJets->Fill(PFMET, 1.0*WeightC*WeightD);
	  h_DoubleElectron_MET->Fill(PFMET, 1.0);
	  
	  h_DoubleElectron_DiEMPtWeight->Fill(DiEMPt, WeightC);
	  h_DoubleElectron_NJetWeight->Fill(jetNumAll, WeightD);
	  
	  if(PFMET>100){
	    h_DoubleElectron_MET_SignalRegion->Fill(PFMET, 1.0);
// 	    myfile << "++++++++++++++++ electron-electron event ++++++++++++++++++++++++++++++" << endl;
// 	    myfile << "Lumi No: " << Lumis << " Run: " << Run << " Event No: " << Event << " E_{T}^{miss}: " << PFMET << endl;
// 	    myfile << "First electron object at photon position :" << electron_tracker.at(0) <<  " and Pt: " << PhoEt->at(electron_tracker.at(0)) << " phi: " << PhoPhi->at(electron_tracker.at(0)) << " eta: " << PhoEta->at(electron_tracker.at(0)) << endl;
// 	    myfile << "Second electron object at photon position:" << electron_tracker.at(1) <<  " and Pt: " << PhoEt->at(electron_tracker.at(1)) << " phi: " << PhoPhi->at(electron_tracker.at(1)) << " eta: " << PhoEta->at(electron_tracker.at(1))<< endl;
	  }
	  
	  int Bin2DX=eephotondiemptnjets2D->GetXaxis()->FindBin(DiEMPt);
	  int Bin2DY=eephotondiemptnjets2D->GetYaxis()->FindBin(jetNumAll);
	  
	  float WeightFrom2D=eephotondiemptnjets2D->GetBinContent(Bin2DX, Bin2DY);
	  h_DoubleElectron_MET_ReweightedDiEMPtNJets_From2DRatio->Fill(PFMET, 1.0*WeightFrom2D);
	  
	  for( int s=0 ; s<1000; ++s){
            float Weightprop = DiEMPtRatioGaus[s]->GetBinContent(BinC);
            h_DoubleElectron_MET_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[s]->Fill(PFMET, Weightprop*1.0);
	    h_DoubleElectron_NJets_DiEMPtReweighted_ErrorPropagatedFromDiEMPt[s]->Fill(jetNumAll, Weightprop*1.0);
	    float Weightprop2 = NJetsRatioGaus[s]->GetBinContent(BinD);
            h_DoubleElectron_MET_NJetsReweighted_ErrorPropagatedFromNJets[s]->Fill(PFMET, Weightprop2*1.0);
	    
	    float WeightProp2D = DiEMPtVsNJetRatioEE[s]->GetBinContent(Bin2DX, Bin2DY);
            h_DoubleElectron_MET_DiEMPtVsNJetReweighted_ErrorPropagatedFromDiEMPtvsNJet[s]->Fill(PFMET, WeightProp2D*1.0);
	    
          }
          for(size_t l = 0; l < ElectronEta.size(); ++l){
            vector<float> MinDR, MinDRJet;
            MinDR.clear(); MinDRJet.clear();
            /// working with MC electron ////
            float mindr = 0;
            if(MinDR.size()!=0) mindr = *std::min_element(MinDR.begin(),MinDR.end());
            if(Debug && jentry > 8813873)cout << "MinDr: " << mindr << endl;
            if(mindr!=0)h_Dr_Electrons->Fill(mindr);
          
            /// working with Jets ////
            for(size_t m = 0; m < JetEta->size(); ++m){
              if(Debug)cout << "inside Jet " << jentry << endl;
              if(Debug){
                cout << "inside Jet  " << jentry << endl;
                cout << "JetPt(" << m << "): " << JetPt->at(m) << endl;
                cout << "JetEta(" << m << "): " << JetEta->at(m) << endl;
                cout << "JetPhi(" << m << "): " << JetPhi->at(m) << endl;
              }
              if(Debug)cout << "Jets!!!" << endl;
              float DRJet = dRCalc(ElectronEta.at(l), ElectronPhi.at(l), JetEta->at(m), JetPhi->at(m));
              MinDRJet.push_back(DRJet);
            }
            float mindrjet = 0;
            if(MinDRJet.size()!=0) mindrjet = *std::min_element(MinDRJet.begin(),MinDRJet.end());
            if(Debug)cout << "MinDrJet: " << mindrjet << endl;
            if(mindrjet!=0)h_Dr_ElectronJets->Fill(mindrjet);
          }
          if(Debug)cout << "inside doubleelectron  " << jentry << endl;
          EventElectronDr++;
          h_Electron_MET->Fill(PFMET);
        }
      }
      
      
      // e-gamma sample selection //
      if(electron_tracker.size()==1 && realphoton_tracker.size()==1){
	if(!(HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1 || HLT_Pho>>14&1 || HLT_EleMuX>>2&1 ))continue;
	
	float DR = dRCalc(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)));
	float Mass = findMass(PhoE->at(realphoton_tracker.at(0)), PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), PhoE->at(electron_tracker.at(0)), PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)));
	
	bool CloseMuonLead(false);
	for(size_t h=0; h < GoodMuonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(electron_tracker.at(0)), PhoPhi->at(electron_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonLead = true;
	    break;
	  }
	}
	if(CloseMuonLead)continue;
	
	bool CloseElectronLead(false);
	bool CloseMuonLeadPhoton(false);
	
	for(size_t h=0; h < ElectronEta.size(); ++h){
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), ElectronEta.at(h), ElectronPhi.at(h), 0.3)){
	    CloseElectronLead = true;
	    break;
	  }
	}
	if(CloseElectronLead)continue;
	
	for(size_t h=0; h < GoodMuonEta.size(); ++h){
	  if(isSameObject(PhoEta->at(realphoton_tracker.at(0)), PhoPhi->at(realphoton_tracker.at(0)), GoodMuonEta.at(h), GoodMuonPhi.at(h), 0.3)){
	    CloseMuonLeadPhoton = true;
	    break;
	  }
	}
	if(CloseMuonLeadPhoton)continue;
	
	if(DR>0.3){
	  if(HLT_EleMuX>>2&1)h_ElectronPhoton_InvMass->Fill(Mass, 1.0);
	  if(HLT_Pho>>14&1)h_PhotonTrigger_EG->Fill(14);
	  if(HLT_Pho>>15&1)h_PhotonTrigger_EG->Fill(15);
	  if(HLT_Pho>>16&1)h_PhotonTrigger_EG->Fill(16);
	  if(HLT_Pho>>17&1)h_PhotonTrigger_EG->Fill(17);
	  
	  if(HLT_Pho>>14&1 && !(HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1))h_PhotonTrigger_EGOnly14->Fill(14);
	  if(HLT_Pho>>15&1 && !(HLT_Pho>>14&1 || HLT_Pho>>16&1 || HLT_Pho>>17&1))h_PhotonTrigger_EGOnly15->Fill(14);
	  if(HLT_Pho>>16&1 && !(HLT_Pho>>15&1 || HLT_Pho>>14&1 || HLT_Pho>>17&1))h_PhotonTrigger_EGOnly16->Fill(14);
	  if(HLT_Pho>>17&1 && !(HLT_Pho>>15&1 || HLT_Pho>>16&1 || HLT_Pho>>14&1))h_PhotonTrigger_EGOnly17->Fill(14);
	  
	}
	
	if(DR > 0.3 && (HLT_EleMuX>>2&1)){
	  h_ElectronPhoton_MET_SingleElectron->Fill(PFMET, 1.0);
	  h_Scaled_ElectronPhoton_MET_SingleElectron->Fill(PFMET, fakerate/(1-fakerate)*1.0);
	  h_Scaled_ElectronPhoton_MET_Up_SingleElectron->Fill(PFMET, fakerateup/(1-fakerateup)*1.0);
	  h_Scaled_ElectronPhoton_MET_Down_SingleElectron->Fill(PFMET, fakeratedown/(1-fakeratedown)*1.0);
	}
	
	if(!(HLT_Pho>>14&1))continue;
	//if(!(jetNumAll > jetRequirement))continue;
        if(DR > 0.3 && Mass>105){
	  h_ElectronPhoton_MET->Fill(PFMET, 1.0);
	  h_Scaled_ElectronPhoton_MET->Fill(PFMET, fakerate/(1-fakerate)*1.0);
	  h_Scaled_ElectronPhoton_MET_Up->Fill(PFMET, fakerateup/(1-fakerateup)*1.0);
	  h_Scaled_ElectronPhoton_MET_Down->Fill(PFMET, fakeratedown/(1-fakeratedown)*1.0);
	}
      }
            
      
      
      if(NoCut>=2)EventCutFlow[0]++;
      if(NeutralCut>=2)EventCutFlow[1]++;
      if(ChargedCut>=2)EventCutFlow[2]++;
      if(PhotonIsoCut>=2){
        EventCutFlow[3]++;
        for(int k = 0; k < PhotonIsoCut; ++k){
          h_ShowerShape->Fill(PhoSigmaIEtaIEta->at(showershape_tracker.at(k))); 
        }
      }
      if(ShowerShapeCut>=2){
        EventCutFlow[4]++;
        if(ShowerShapeCut == 2){
          for(int k = 0; k < ShowerShapeCut; ++k){
            h_Pt->Fill(PhoEt->at(pt_tracker.at(k))); 
          }
        }
      }
      if(AfterPtCut>=2)EventCutFlow[5]++;
      if(OnlyPhoton>=2)EventCutFlow[6]++;
      if(HoverECut>=2)EventCutFlow[7]++;
      if(OnlyElectron>=2)EventOnlyElectron++;
      if(HoverECutElectron>=2)EventHEElectron++;
      // if (Cut(ientry) < 0) continue;
   }// event loop ends
   
   
   cout << "EventLoop ends" << endl;
   cout << triggerBit[0] << endl;
   cout << triggerBit[21] << endl;
   cout << "Before Histogram filling" << endl;
   for(int a = 0; a < 22; ++a){
     h_PhotonTrigger->SetBinContent(a+1, triggerBit[a]);  
   }
   
   cout << "Double Photon events: " << EventCutFlow[8] << endl;
   cout << "DOuble Fake events: " << TotalFake << endl;
   cout << "Double Electron events: " << EventElectronDr << endl;
   cout << "Number of photons: " << totalphoton << endl;
   cout << "number of photons with pixel seed and csev mismatch: " << totalmismatchphoton << endl;
    for(int i = 0; i < 9; ++i){
     h_CutFlow_Photon->SetBinContent(i+1, EventCutFlow[i]);
     h_CutFlow_Photon->GetXaxis()->SetBinLabel(i+1,CutFlowLabels[i]);
     if(i > 5)continue;
     h_CutFlow_Electron->SetBinContent(i+1, EventCutFlow[i]);
     h_CutFlow_Electron->GetXaxis()->SetBinLabel(i+1,CutFlowLabels[i]);
   }
   h_CutFlow_Electron->SetBinContent(7, EventOnlyElectron);
   h_CutFlow_Electron->GetXaxis()->SetBinLabel(7, CutFlowLabels[6]);
   h_CutFlow_Electron->SetBinContent(8, EventHEElectron);
   h_CutFlow_Electron->GetXaxis()->SetBinLabel(8, CutFlowLabels[7]);
   h_CutFlow_Electron->SetBinContent(9, EventElectronDr);
   h_CutFlow_Electron->GetXaxis()->SetBinLabel(9, CutFlowLabels[8]);
     
   gROOT->SetBatch(true);
  
   
   
   
   f1->Write();
}