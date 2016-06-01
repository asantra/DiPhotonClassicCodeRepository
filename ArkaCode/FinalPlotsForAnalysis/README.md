These are the files needed for final numbers in the signal region. Put all the files in a folder including the output of 
https://github.com/asantra/DiPhotonClassicCodeRepository/tree/master/ArkaCode/AnalysisHistogramMaker

1. Run the QCDClosure.sh in this fashion:
bash QCDClosure.sh 40 <purity_value> <data> <scaleMET range> <analysisFake Boolean>

here 40 is the photon pt selected

purity_value is something between 0 and 1. This is not doing anything great for this analysis as of now. This was added in case 
we want to use the purity of our QCD background and combine ee and ff as purity*ee+(1-purity*ff)

<data> is a boolean needs to be True

<scaleMET range> is the normalization region of MET. For the analysis done here, the MET<50 region was selected. So put a value
less than 50 (49 may be).

<analysisFake boolean> if true, you get plots for original fake, if false you get plots for loose fake. The plots will
be saved in different folders for original fake and extedned fake.

2. You may need to fix the location of 'MyFunction.h' in the #include section of each file.
