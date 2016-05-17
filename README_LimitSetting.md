Directions for using the code in the LimitSetting Directory
to make limit plots.

For more information on the Higgs combine tool, see
https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideHiggsAnalysisCombinedLimit#How_to_run_the_tool

Step 1: Set up the environment

    > setenv SCRAM_ARCH slc6_amd64_gcc481
    > cmsrel CMSSW_7_1_5 
### must be a 7_1_X release  >= 7_1_5;  (7.0.X and 7.2.X are NOT supported either) 
    > cd CMSSW_7_1_5/src 
    > cmsenv
    > git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
    > cd HiggsAnalysis/CombinedLimit
    > git fetch origin
    > git checkout v5.0.3   # try v5.0.1 if any issues occur
    > scramv1 b clean; scramv1 b # always make a clean build, as scram doesn't always see updates to src/LinkDef.h


Step 2: Write data cards
    > cd macro
    
    * Copy WriteLimitCommands.C, SignalExpectation_NewNtuples.root, and counting_t5gg_XXX_YYY.txt to local directory
    * Run WriteLimitCommands.C to create the instructions to make the data cards
    * Run limitCommands.sh to create the data cards

Step 3: Compute Limits
     Edit and run step3.sh

Step 4: Create Limit Histograms
     Using step4a.sh through step4d.sh to create four scripts:
     ExpLimMid.C, ExpLimDown.C, ExpLimUp.C, and ObsLim.C 
     An example of ObsLim.C is included so you can see the form of each of them.
     Once you have run each of these scripts, you should have four ROOT files:
     ExpLimMid.root, ExpLimDown.root, ExpLimUp.root, and ObsLim.root

Step 5: Draw limit canvas
    * Copy DrawLimitCanvas.C and SusyCrossSections13TeVGluGlu.txt to local directory
    * Run DrawLimitCanvas.C, the result should be a nice-looking limit canvas.