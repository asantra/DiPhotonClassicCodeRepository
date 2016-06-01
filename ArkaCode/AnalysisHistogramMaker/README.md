This set of codes are used to get the histograms related to two photons, double fakes and double electron etc. Put all the
files in a folder and do the following:
Step 1
----------
1. Run the PythonSubmit.py in the following way:
python PythonSubmit.py <photon Pt selection> <txt file name> <analysisFake/extendedFake boolean True/False>
i.e. python PythonSubmit.py 40 sample.txt True # for analysis Fake
where txt file contains absolute paths of the small ntuples (output of the codes in folder SmallNtupleMakerFromggNtuple).

photon Pt selection is always kept at 40

2. Right now, changing from Extended Fake (loose fake) to Analysis Fake (original fake) is done manually, by commenting in
https://github.com/asantra/DiPhotonClassicCodeRepository/blob/master/ArkaCode/AnalysisHistogramMaker/SmallNtupleMASTER.C#L903-L916
and commenting out
https://github.com/asantra/DiPhotonClassicCodeRepository/blob/master/ArkaCode/AnalysisHistogramMaker/SmallNtupleMASTER.C#L919-L931

or vice versa

But this can be automated. 


3. If there are N filepaths in .txt file (in separate lines), there will be N condor jobs. 
4. Hadd the output .root files. Depending on the fake selection, choose these names:
Data_RunD_All_AnalysisFake_217fb.root
Data_RunD_All_ExtendedFake_217fb.root

######################################################
Step 2
--------
REMEMBER: 
A. The first iteration of Step 1 will have wrong DiEMPt weighting and Random ratio (random ratios are needed for systematic uncertainty of diEMPt reweighting).

Run the codes with wrong diempt weighting to get Data_RunD_All_AnalysisFake_217fb.root/Data_RunD_All_ExtendedFake_217fb.root
and then put them in the folder where https://github.com/asantra/DiPhotonClassicCodeRepository/blob/master/ArkaCode/FinalPlotsForAnalysis/QCDClosure.sh is kept.

B. After running QCDClosure.sh (see instructions here: https://github.com/asantra/DiPhotonClassicCodeRepository/blob/master/ArkaCode/FinalPlotsForAnalysis/README.md)
you will get the correct DiEMPt and RandomRatio. Then put those files (DIEMPtRatio40.root and RandomRatioErrorProp40.root) back to this folder again 
(you can modify https://github.com/asantra/DiPhotonClassicCodeRepository/blob/master/ArkaCode/FinalPlotsForAnalysis/QCDClosure.sh to do this for you)

C. Then in the second iteration of Step 1, one should get 
Data_RunD_All_AnalysisFake_217fb.root
Data_RunD_All_ExtendedFake_217fb.root
with correct diEMPt weight and uncertainty.



