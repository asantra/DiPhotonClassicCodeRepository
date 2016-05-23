// Jet energy correction is possible at ntuple level.
// $ cd ../jec/JetMETObjects
// $ make
// This will create a shared library in jec/lib
// which is included below as libJetMETObjects.so
//
// Come back to this directory and do
// $ make
// $ root -b -q -l ana.C
// will produce hist_"physics"_"ds".root



void ana(TString ds="analysis",TString physics="test"){


  TStopwatch ts;
  ts.Start();
  
  gSystem->Load("libSusyEvent.so");

  // Look ../jec/JetMETObjects/README
  //  gSystem->Load("../jec/lib/libJetMETObjects.so");

  // Printing utility for ntuple variables
  //gROOT->LoadMacro("SusyEventPrinter.cc+");

  // Main analysis code
  gROOT->LoadMacro("SusyEventAnalyzer.cc+");

  // chain of inputs
  TChain* chain = new TChain("ggNtuplizer/EventTree");
  
  std::cout<<"Grabbing Files..."<<std::endl;
   
  //chain->Add(fileName.Data());

  //  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/V07-04-14/full_dataset/reduced_TnPv2_SinglePhoton_RunCD.root");

  //   chain->Add("/afs/cern.ch/user/a/areinsvo/ggtree_mc.root");
  //    chain->Add("/afs/cern.ch/user/a/areinsvo/ggNtuples/CMSSW_7_0_6_patch3/src/ggtree_mc.root");
  //chain->Add("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/NtuplePlotter/DYJets_s14/DYJets_s14_skim.root"); 
  //  chain->Add("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/SusyAnalysis/SusyNtuplizer/macro/ggtree_mc_2.root");
  //  chain->Add("/eos/uscms/store/user/areinsvo/GJet_Pt20to40_doubleEMEnriched_TuneZ2star_13TeV-pythia6/CRAB3_ggNtuples_GJet_Pt20to40_doubleEMEnriched/141110_205027/0000/ggtree_mc_2.root");

  //      chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/V07_04_05/reduced_DoubleEG_Run2015B_PR_Jul24JSON.root");
  //chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/job_DoubleEG_Run2015B_PR_Jul24.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_1350_75_production/ggNtuples/T5gg_13TeV_1350_75_BX25ns_2kev.root");
  //chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_1350_225_production/ggNtuples/T5gg_13TeV_1350_225_BX25ns_2kev.root");
  //chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_1350_675_production/ggNtuples/T5gg_13TeV_1350_675_BX25ns_2kev.root");
  //chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_1350_1275_production/ggNtuples/T5gg_13TeV_1350_1275_BX25ns_2kev.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/mc/job_spring15_DYJetsToLL_m50_25ns.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/job_DoubleEG_Run2015C_PR_25ns.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/job_SinglePho_Run2015C_PR_25ns.root");
  //chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Run2105C_DoubleEG_v51.root");
  //  chain->Add("/afs/cern.ch/user/a/areinsvo/useful/reduced_TnP_Run2015D_DoubleEG.root");
  //  chain->Add("/afs/cern.ch/user/a/areinsvo/useful/reduced_DoubleEG_Run2015D_A.root");

  //  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_DoubleEG_Run2015D.root");
  //  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/old/reduced_TnP_Run2015D_DoubleEG.root");

  //  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/V07-04-14/reduced_TnP_Run2015CD.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V07_04_14_00/GoldenJSON/job_DoubleEG_Run2015D_PR_v4_miniAOD.root");

  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/mc/job_spring15_ggNtuple_DYJetsToLL_M-50_amcatnlo_pythia8_25ns_miniAOD.root");
  //  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/V07_04_14_00/GoldenJSON/job_SinglePho_Run2015D_PR_v4_miniAOD.root");

  /*
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015C.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_A.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_BC.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_DE.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_HI.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_JKL.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_Oct05_Z.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_A.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_CD.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_EF.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_GH.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_IJ.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_KL.root");
  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/reduced_Higgs_DoubleEG_Run2015D_v4_MN.root");
  */

  chain->Add("/afs/cern.ch/work/a/areinsvo/private/ggNtuples/reduced_ntuples/V07-04-14/reduced_Higgs_DoubleEG_Run2015CD.root");

//chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/data/job_SingleMu_Run2015C_PR_25ns.root");

/*  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN200/ggtree_mc_1_1_QFR.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN200/ggtree_mc_2_1_miW.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN200/ggtree_mc_4_1_kZ9.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN200/ggtree_mc_3_1_10o.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_1_1_1Qp.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_2_1_EVa.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_3_1_Ff4.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_4_1_76v.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_5_1_pAN.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN400/ggtree_mc_6_1_R9n.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN600/ggtree_mc_1_1_bUS.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN600/ggtree_mc_2_1_y06.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN600/ggtree_mc_3_1_aHd.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN600/ggtree_mc_4_1_pPh.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN600/ggtree_mc_5_1_E1s.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN800/ggtree_mc_1_1_sI6.root");  
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN800/ggtree_mc_2_1_jbn.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN800/ggtree_mc_3_1_h2W.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN800/ggtree_mc_4_1_6YX.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1000_mN800/ggtree_mc_5_1_j2X.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN200/ggtree_mc_1_1_wPf.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN200/ggtree_mc_2_1_Emu.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN200/ggtree_mc_3_1_Wsk.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN200/ggtree_mc_4_1_iUh.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN200/ggtree_mc_5_1_DSl.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN400/ggtree_mc_1_1_xGT.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN400/ggtree_mc_2_1_LpV.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN400/ggtree_mc_3_1_kf2.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN400/ggtree_mc_4_1_ygE.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN400/ggtree_mc_5_1_glF.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN600/ggtree_mc_1_1_F4s.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN600/ggtree_mc_2_1_7hJ.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN600/ggtree_mc_3_1_ALa.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN600/ggtree_mc_4_1_ziH.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN600/ggtree_mc_5_1_rjf.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_1_1_DD6.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_2_1_Ps0.root");  
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_3_1_EC3.root");  
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_4_1_vrB.root");  
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_5_1_xJo.root");  
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN800/ggtree_mc_6_1_LMY.root");  

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN1000/ggtree_mc_1_1_V1U.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN1000/ggtree_mc_2_1_9Yd.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN1000/ggtree_mc_3_1_6Z4.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN1000/ggtree_mc_4_1_7co.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1200_mN1000/ggtree_mc_5_1_TSc.root");

    chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN200/ggtree_mc_1_1_RBJ.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN200/ggtree_mc_2_1_8bg.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN200/ggtree_mc_3_1_QYs.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN200/ggtree_mc_4_1_vn5.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN200/ggtree_mc_5_1_fKz.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_1_1_qzs.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_2_1_drm.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_3_1_q5t.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_4_1_lQR.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_5_1_Nk4.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN200/ggtree_mc_6_1_Cfk.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_1_1_4zf.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_2_1_jHA.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_3_2_3YJ.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_4_2_zOP.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_5_2_e90.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN200/ggtree_mc_6_1_kLC.root");

   chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN200/ggtree_mc_1_1_00c.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN200/ggtree_mc_2_1_lVs.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN200/ggtree_mc_3_1_VMd.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN200/ggtree_mc_4_1_NeS.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN200/ggtree_mc_5_1_Aie.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_1_1_OXM.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_2_1_uQZ.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_3_1_vCD.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_4_1_jb0.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_5_1_lGe.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG2000_mN1800/ggtree_mc_6_1_E49.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_1_1_Msc.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_2_1_DZy.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_3_1_KMl.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_4_1_cRj.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_5_1_DJ2.root"); 
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1800_mN1600/ggtree_mc_6_1_7ct.root");

    chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_1_1_ZoN.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_2_1_KMk.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_3_1_Lml.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_4_1_M30.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_5_1_bYK.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1600_mN1400/ggtree_mc_6_1_EDK.root");

  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_1_1_anD.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_2_1_Ogq.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_3_1_ad9.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_4_1_bT4.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_5_1_yzQ.root");
  chain->Add("root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/itopsisg/T5gg_signalNtuples/mG1400_mN1200/ggtree_mc_6_1_e30.root");*/

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
  sea->SetUseJSON(true);
  sea->DoRhoCorrection(true);
  sea->DoNvertexCorrection(false);
  sea->SetDR03Rho25Corr(0.081,0.022,0.011);//Ecal,Hcal.Track
  sea->SetPFisoRho25Corr(0.031,0.013,0.078);//chargedHadronIso,neutralHadronIso,photonIso
  sea->SetFilter(false);                  // filter events passing final cuts
  sea->isFastSim(true);    //only matters for HiggsAna()
  sea->isFullSim(false);   //only matters for HiggsAna()
  sea->SetProcessNEvents(10);     //(set to -1 to process all events) number of events to be processed
  std::cout<<"Done seting variables"<<endl;
  // HLT trigger path names
  //sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_CaloId10_Iso50_v");
  //sea->AddHltName("HLT_Photon36_CaloId10_Iso50_Photon22_R9Id85_v");
  //sea->AddHltName("HLT_Photon36_R9Id85_Photon22_CaloId10_Iso50_v");
  //sea->AddHltName("HLT_Photon36_R9Id85_Photon22_R9Id85_v");
  

  //fully combined json
  //  sea->IncludeAJson("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/SusyAnalysis/SusyNtuplizer/macro/Run2015D_GoldenJSON_246908_2572599_v3.txt");
  //  sea->IncludeAJson("https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-259891_13TeV_PromptReco_Collisions15_25ns_JSON.txt");
  //  sea->IncludeAJson("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/SusyAnalysis/SusyNtuplizer/macro/Run2015D_246908-259891.json");
  sea->IncludeAJson("/afs/cern.ch/user/a/areinsvo/private/CMSSW_7_0_5/src/SusyAnalysis/SusyNtuplizer/macro/Run2015D_246908-260627.json");
  sea->Loop();
  //sea->DR03();
  //sea->Pileup();
  //sea->Filter();
  //sea->PhotonId();
  //sea->HiggsAna();

  ts.Stop();

  std::cout << "RealTime : " << ts.RealTime()/60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << ts.CpuTime()/60.0 << " minutes" << std::endl;

}
