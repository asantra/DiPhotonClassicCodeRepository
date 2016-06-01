##Inside ArkaCode, the ntuple analyzer needed to get acceptance times efficiency is kept. 
#To run this set of codes:
 1. Put all the files in a folder at LPC/LXPLUS
 2. put the T5gg sorted (for T6gg, one needs to add 'EventTag' branch in MyNtupleMakerMASTER.h) files' address (eos address) in a text file (example is FinalSignalSample19Feb.txt). Python will assume that all the lines in the text file have newline character at the end of them. So don't forget to hit an enter after the last line so that the last line also has newline character at the end of it.
 3. Run like this:
 python makeGGjobs.py FinalSignalSample19Feb.txt
 4. One needs to be careful with the cross section values which are hard-coded in makeGGjobs.py (one needs to change them for T6gg here)
