#Allie Reinsvold-Hall
#April 2016
#Script to sort T5gg or T6gg ntuples into one ntuple per gluino (or squark) and neutralino mass point
#Usage: adjust input file names, starting_event, and process_n_event parameters below,
#and define the mass grid, then run using python sort.py
#TODO: Needs to be updated to be able to be run using condor, rather than running it locally

import os, sys, ROOT, math
#from array import *
sw = ROOT.TStopwatch()
sw.Start()


chain_in = ROOT.TChain("ggNtuplizer/EventTree") #name of tree and directory the tree is in
#Input file names. Can use wildcard * !
chain_in.Add("SMS-T5gg_mGluino-1800-1850_mLSP-0to1700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_job_T5gg_mGluino_1800to1850/160405_140027/0000/ggtree_mc_*.root")

#Number of events to process. This is a hack, since this script isn't set up to run using condor
#For large files, I run this script several times, changing starting_event each time,
#and then at the end merge the resulting output files  
starting_event =           0000
process_n_events =     20000000
if (starting_event + process_n_events) > chain_in.GetEntries():
    last_event = chain_in.GetEntries()
else:
    last_event = starting_event + process_n_events
#define output file names
base = "./T5gg_sorted_ntuples/T5gg_mGlu_"
mid = "_mNeu_"
end = ".root"
#define mass grid here
min_gluino_mass = 1800
max_gluino_mass = 1851
gluino_mass_step = 50
min_neu_mass = 100
#max neutrino mass is set to equal the gluino mass
neu_mass_step = 100

#Define output files
file_num = 0
file_list = []
dir_list = []
tree_list = []
for glu_mass in xrange(min_gluino_mass,max_gluino_mass,gluino_mass_step):
    for neu_mass in range(min_neu_mass,glu_mass+1,neu_mass_step):
        out_file_name = base + str(glu_mass) +mid+str(neu_mass) +end
        print "File number " + str(file_num) + ": " + out_file_name
        temp_file = ROOT.TFile(out_file_name, "recreate")
        file_list.append(temp_file)
        temp_dir = file_list[file_num].mkdir("ggNtuplizer")
        dir_list.append(temp_dir)
        dir_list[file_num].cd()
        temp_tree = chain_in.CloneTree(0)
        tree_list.append(temp_tree)
        file_num=file_num+1
total_num_files = file_num-1

for j_entry in range(starting_event,last_event):
    i_entry = chain_in.LoadTree(j_entry)

    if i_entry < 0:
        break

    nb = chain_in.GetEntry(j_entry)
    if nb <= 0:
        continue
    
    if j_entry % 10000 ==0:
        print "Processing entry " + str(j_entry) + " of " + str(last_event)
    true_glu_mass = 0
    true_neu_mass = 0
    tag = chain_in.EventTag
    str_tag = str(tag)

    true_glu_mass = int(str_tag[13:17])
    true_neu_mass = int(str_tag[18:])

    if true_glu_mass ==0:
        print "Gluino mass = 0. Something is wrong!"
    if true_neu_mass ==0:
        print "Neutralino mass = 0. Something is wrong!"
    file_it = -1
    file_num =0
    for glu_mass in xrange(min_gluino_mass,max_gluino_mass,gluino_mass_step):
        if(file_it == -1):  #only need to continue if file_it has not already been set to something
            for neu_mass in range(min_neu_mass,glu_mass+1,neu_mass_step):
                if(true_glu_mass < (glu_mass + 20) and true_glu_mass > (glu_mass - 20) and
                   true_neu_mass < (neu_mass + 20) and true_neu_mass > (neu_mass - 20) ):
                    file_it = file_num
                    break
                else:
                    file_num+=1

    if file_it != -1:
        dir_list[file_it].cd()
        tree_list[file_it].Fill()
    else:
        print "No match! You messed up. Gluino mass = " + str(true_glu_mass) + " and neutralino mass = " + str(true_neu_mass)

for i in xrange(0,total_num_files+1):
    file_list[i].Write()
    file_list[i].Close()

sw.Stop()

print "Real Time = " + str(sw.RealTime() / 60.0 ) + " minutes."
print "CPU Time = " + str(sw.CpuTime() / 60.0 ) + " minutes."
