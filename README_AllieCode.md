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
