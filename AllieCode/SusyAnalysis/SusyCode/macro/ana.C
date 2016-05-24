// Come back to this directory and do
// $ make
// $ root -b -q -l ana.C
// will produce hist_"physics"_"ds".root



void ana(TString ds="analysis",TString physics="test"){
  TStopwatch ts;
  ts.Start();
  
  gSystem->Load("libSusyEvent.so");

  // Main analysis code
  gROOT->LoadMacro("SusyEventAnalyzer.cc+");

  // chain of inputs
  TChain* chain = new TChain("ggNtuplizer/EventTree");
  
  std::cout<<"Grabbing Files..."<<std::endl;
   
  //chain->Add(fileName.Data());

  chain->Add("/afs/cern.ch/work/a/areinsvo/public/reduceD_ntuples/reduced_TnPv2_SinglePhoton_RunCD.root");


  std::cout<<"Files grabbed.  Now to define sea:"<<std::endl;
  SusyEventAnalyzer* sea = new SusyEventAnalyzer(chain);
  std::cout<<"sea defined"<<std::endl;
  // configuration parameters
  // any values given here will replace the default values
  sea->SetDataset(physics+"_"+ds);        // dataset name
  sea->SetPrintInterval(2.5e5);             // print frequency
  sea->SetPrintLevel(0);                  // print level for event contents
  sea->SetOutputEventNumbers(false);      // print run and event numbers
  sea->SetUseTrigger(true);
  sea->SetUseJSON(false);
  sea->DoRhoCorrection(true);
  sea->DoNvertexCorrection(false);
  sea->SetDR03Rho25Corr(0.081,0.022,0.011);//Ecal,Hcal.Track
  sea->SetPFisoRho25Corr(0.031,0.013,0.078);//chargedHadronIso,neutralHadronIso,photonIso
  sea->SetFilter(false);                  // filter events passing final cuts
  sea->SetProcessNEvents(10);     //(set to -1 to process all events) number of events to be processed
  std::cout<<"Done seting variables"<<endl;
  

  //fully combined json
  //  sea->IncludeAJson("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/SusyAnalysis/SusyNtuplizer/macro/Run2015D_GoldenJSON_246908_2572599_v3.txt");
  sea->Loop();

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}
