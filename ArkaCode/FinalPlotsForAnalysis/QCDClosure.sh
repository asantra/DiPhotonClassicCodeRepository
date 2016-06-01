#!/bin/bash

#### run this using : bash <name> <40/50> <purity_value> <data> <scaleMET range> <analysisFake>
#### The pt 40 file names should be: DYtoEEWeightedProper74.root and GJet_Pt40_All.root
#### the pt 50 file names should be: DYtoEEWeightedProper74_Pt50.root and GJet_Pt40_All_Pt50.root
#### Data file: Data_RunD_All.root for new RunD or NewData_50ns.root for 50ns old data

pt=$1 # pt value
purity=$2 # a value
data=$3 # a bool
scaleMET=$4 # a value to scale MET
analysisFake=$5 # a bool to take analysisFake or not
#//.L tdrStyle.C // old file
#.L CMSTDR.C
#setTDRStyleAgain()
root -l -b << EOF
cout << "=========================" << endl;
cout << "Doing DiEMPt Reweighting " << endl;
cout << "=========================" << endl;
cout << "Testing photon's pt " << $pt << endl;
.L ReweightDIEMPt.C++ 
ReweightDIEMPt($pt, $data, $analysisFake)
cout << "=================================" << endl;
cout << "Doing Gaussian Error Propagation " << endl;
cout << "=================================" << endl;
.L ErrorPropagationGaus.C++
ErrorPropagationGaus($pt, $data)
cout << "=========================" << endl;
cout << "Doing Error Propgagation " << endl;
cout << "=========================" << endl;
.L DrawErrorPropEle.C++
DrawErrorPropEle($pt, $data, $analysisFake)
cout << "=====================" << endl;
cout << "Doing Fake Rate error" << endl;
cout << "=====================" << endl;
.L DrawAsymErrorFakeRate.C++
DrawAsymErrorFakeRate($analysisFake)
cout << "===============================" << endl;
cout <<  "Getting File for FF estimation" << endl;
cout << "===============================" << endl;
.L FileForFF.C++
FileForFF($data, $scaleMET, $analysisFake)
EOF
cd /home/arka/arka/CheckingKeithSuggestion
echo "==========================================="
echo "Getting FF estimation from Keith Suggestion"
echo "==========================================="
### Run the below code using: 
# python FFEstimateFromConstantAndSlope.py <constant> <constant1sigma> <slope> <slope1sigma> <intercept> <intercept1sigma>
#python FFEstimateFromConstantAndSlope.py  4.141 0.283 -0.031 0.019 4.988 0.283 47

python FFEstimateFromConstantAndSlopeData.py  4.409 0.124 -0.030 0.009 5.149 0.246

#python FFEstimateFromConstantAndSlopeData.py 0.08143 0.00133 -0.00066 0.00001 0.09956 0.00133
cp KeithSuggestionResultConstantAndSlope.root /home/arka/arka/ggNtuples_Phys14/QCD_Closure
cd /home/arka/arka/ggNtuples_Phys14/QCD_Closure
root -l -b << EOF
cout << "==================================" << endl;
cout <<  "Getting All Background estimation" << endl;
cout << "==================================" << endl;
.L CalculateSysError.C++ 
CalculateSysError($pt, $purity, $data, $scaleMET, $analysisFake)
cout << "=====================================" << endl;
cout << "Getting Final Plots with Shape Error " << endl;
cout << "=====================================" << endl;
.L FinalPlot.C++
FinalPlot($analysisFake)
cout << "==================================" << endl;
cout << "Getting Final Plots without Shape " << endl;
cout << "==================================" << endl;
EOF

echo "==========================================="
echo "Sending InvMass histograms to roofit folder"
echo "==========================================="
if [ $analysisFake == "1" ]
then
  cp Data_RunD_Ratio_AnalysisFake_217fb/InvMass_Histogram.root /home/arka/arka/ggNtuples_Phys14/QCD_Closure/FittingForAN
else
  cp Data_RunD_Ratio_ExtendedFake_217fb/InvMass_Histogram.root /home/arka/arka/ggNtuples_Phys14/QCD_Closure/FittingForAN
fi
times