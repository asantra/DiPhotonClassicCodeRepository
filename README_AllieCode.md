Erf_fit.C
ROOT macro to fit an error function to a trigger efficiency
vs photon PT plot. Also does a lot of cosmetics to make the plots
look nice.

Erf_fit_InvMass.C
ROOT macro to fit an error function to a trigger efficiency
vs diphoton InvariantMass plot. Also does a lot of cosmetics 
to make the plots look nice.

skimNtuples.py is a script that takes ggNtuples, and produces
smaller, skimmed ggNtuples including only those events that pass the 
criteria you specify in the script. Can also be used to prune 
ntuples, by removing variables that are no longer needed. 
I have used this to skim for Tag and Probe events for trigger
efficiency studies, and for selecting only events that passed 
one of our diphoton triggers
#Usage: adjust input file names, save_event criteria, starting_event, 
and process_n_event parameters, then run using python skimNtuples.py

sort.py is a script to sort T5gg or T6gg ntuples into one ntuple per 
gluino (or squark) and neutralino mass point
Usage: adjust input file names, starting_event, and process_n_event 
parameters, define the mass grid, then run using python sort.py    


***********************************
INSTRUCTIONS FOR MAKING TRIGGER EFFICIENCY PLOTS
Step 1: Make a skimmed set of ntuples to run over
I’m pretty sure that the skim I used to make the plots we included in the analysis can be found here:
/afs/cern.ch/work/a/areinsvo/public/reduceD_ntuples/reduced_TnPv2_SinglePhoton_RunCD.root

In case this doesn’t work though, here are the instructions for remaking the skim:
Use skimNtuples_TnP.py (can find it on my branch on github https://github.com/asantra/DiPhotonClassicCodeRepository/tree/Allie ). Run with nohup python skimNutples_TnP.py >& log &
You’ll first have to change file_out, chain_in.Add and process_n_events to fit your needs. The parameter process_n_events needs to be set to something reasonable to run locally, and then I normally just change starting_event  and file_out each time I run the code. At the end you can take all of the output files and merge them into one final file. 

TODO: find a way to run the skim scripts using condor, because once we get more data, I don’t think this method will really work anymore.

Step 2: Run the analysis code
I tried to get this to work in a more recent CMSSW version, but something about the switch from ROOT version 5 to ROOT version 6 messes up the code. For now I would just run it using CMSSW_7_0_5, because I know it works in the release.
cmsrel CMSSW_7_0_5 
cd CMSSW_7_0_5/src
cmsenv
copy everything in the SusyAnalysis directory from my github branch to here
cd SusyAnalysis/SusyCode/macro
make
cp SusyEventAnalyzer_TnPv2.cc SusyEventAnalyzer.cc
SusyEventAnalyzer.cc contains the bulk of the analysis code, including all of the histograms and cuts. 
edit ana.C so that the line chain->Add(“filename”) includes the path to your skim.
Also change the line sea->SetProcessNEvents(10); to a large number, or to -1 to process all events in the the input files.
Run using root -q -b ana.C
This will create an output file hist_test_analysis.root with all of the output histograms that were defined in SusyEventAnalyzer.cc

Step 3: Fit the trigger efficiency plots 
This step uses the AllieCode/Erf_fit.C script, and the Erf_fit_InvMass.C script if you also want to remake the efficiency plot with respect to the diphoton invariant mass.
The first part of the code has several fit functions, but I labeled each based on what I ended up using for each plot. The “LeadTrail” plot is the efficiency of the leading photon to pass the subleading filter. You will have to look at the fit parameters and the fit function definition to figure out what the plateau efficiency is for each plot.
Uncomment one of the 2015 fit functions, based on which plot you are making. Note that you may have to mess with the fit ranges for the myFit1T1 functions.
Change the line below to your output histogram from step 2.
    TFile *f0 = TFile::Open("hist_TnPv2_analysis.root","UPDATE");
Edit lines 84 to 87 depending on which histogram you are trying to fit. The histogram names can be found in the SusyEventAnalyzer.cc macro. Change the title and axis labels accordingly.
After running this macro in root, you should get a canvas out that is decently pretty.