#! /bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.csh
export SCRAM_ARCH=slc6_amd64_gcc491
cd /uscms_data/d3/asantra4/Thesis/ggNtuples/Phys14/NewPackage/CMSSW_7_4_9/src
eval `scramv1 runtime -sh`
cd -
root -l -b << EOF
gSystem->Load("MyNtupleMaker0_C.so") 
TChain chain("ggNtuplizer/EventTree")
chain.Add("GGGGG")
MyNtupleMaker0 Ka(&chain)
Ka.Loop("OOOOO",SSSSS,TTTTT)
.q
EOF
#eosmkdir -p /store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_RunD_25Jan/
#xrdcp -f OOOOO root://cmseos.fnal.gov//store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_RunD_28Feb/
#xrdcp -f OOOOO root://cmseos.fnal.gov//store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_RunD_Again_28Feb/
xrdcp -f OOOOO root://cmseos.fnal.gov//store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_RunD_ForHarrison/
rm OOOOO
