This set of codes is used to create small ntuple from ggNtuple for faster running. This is done through condor.

1. put the absolute path (including /eos/uscms etc) of the ggNtuples from where the small ntuples will be made in a .txt file.
Each file should be in a separate line.
2. Run the makeGGjobs.py like this:
python makeGGjobs.py <no of divideJobs> <textfile containing list of files>

3. If number of lines in .txt file is M and no of divideJobs is N, then MN number of condor jobs will be submitted.
