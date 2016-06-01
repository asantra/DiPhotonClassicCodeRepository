#### run it: python makeGGjobs.py <no of divideJobs> <textfile containing list of files>
### for RunD ggNtuple doubleEG, no of entries: 8283725
### for the file job_DoubleEG_Run2015D_Oct05_miniAOD.root no of entries: 22024624
### for the file job_DoubleEG_Run2015C_Oct05_miniAOD.root no of entries 1854782

import os, sys, re, time
from ROOT import *



def main():
    myfile=open('condor_MyNtupleMakerMASTER.jdl')
    jdl_lines = myfile.readlines()
    myfile.close()

    myfile=open('condor_MyNtupleMakerMASTER.sh')
    sh_lines = myfile.readlines()
    myfile.close()
    
    myfile=open('MyNtupleMakerMASTER.C')
    C_lines = myfile.readlines()
    myfile.close()
    
    myfileheader=open('MyNtupleMakerMASTER.h')
    h_lines = myfileheader.readlines()
    myfileheader.close()
    
    myfileroot=open('RootPromptMASTER.sh')
    root_lines = myfileroot.readlines()
    myfileroot.close()

    textfileName = sys.argv[2]
    #mytextfile = open('Data_Unblinded_RunD.txt')
    #mytextfile = open('NewData_RunD_25ns.txt')
    mytextfile = open(textfileName)
    filelist = mytextfile.readlines()
    mytextfile.close()

    ifile = 0
    myfile = open('MyNtupleMaker'+str(ifile)+'.C','w')
    for line in C_lines:
	if 'MyNtupleMakerQQQ' in line:
	    line = line.replace('MyNtupleMakerQQQ', 'MyNtupleMaker'+str(ifile))
	if 'WWW' in line:
	    line = line.replace('WWW', str(ifile))
	if 'EEEEE' in line:
	  if 'Run2015D_Data_ggNtuple_Ming' in filelist[0]:
	    foldername = '/eos/uscms/store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_RunD_10Nov/'
	    line = line.replace('EEEEE', foldername)
	    if not os.path.exists(foldername):
              os.makedirs(foldername)
          if 'Run2015D_DataUnblinded' in filelist[0]:
	    foldername = '/eos/uscms/store/user/asantra4/MyNtuples_Phys14/Ntuples_74/Data_UnblindedRunD_25ns/'
	    line = line.replace('EEEEE', foldername)
	    if not os.path.exists(foldername):
              os.makedirs(foldername)
	  if 'GJet_Pt40' in filelist[0]:
	    foldername = '/eos/uscms/store/user/asantra4/MyNtuples_Phys14/Ntuples_74/GJet_MC_25ns/'
	    line = line.replace('EEEEE', foldername)
	    if not os.path.exists(foldername):
              os.makedirs(foldername)
	myfile.write(line)
    myfile.close()
    #os.system('mv *_*_.py /uscms_data/d3/asantra4/Thesis/ggNtuples/CMSSW_7_0_6_patch3/src/ggAnalysis/ggNtuplizer/test/' )        

    myfile = open('MyNtupleMaker'+str(ifile)+'.h','w')
    for line in h_lines:
	if 'QQQ' in line:
	    line = line.replace('QQQ',str(ifile))            
	myfile.write(line)
    myfile.close()
    
    myfile = open('RootPrompt'+str(ifile)+'.sh','w')
    for line in root_lines:
      myfile.write(line)
    myfile.close()
    
    os.system('bash '+'RootPrompt'+str(ifile)+'.sh')
      
    fileNumber=0
    for afile in filelist:
      if '/eos/uscms/' in afile:
        afile = afile.replace('/eos/uscms/','root://cmsxrootd.fnal.gov//')
      if '/eos/cms/' in afile:
        afile = afile.replace('/eos/cms/','root://cmsxrootd.fnal.gov//')
      fileNumber=fileNumber+1
      if fileNumber > 3:
	  break
      Jobs = sys.argv[1]
      divideJobs = int(Jobs)
      myChain = TChain('ggNtuplizer/EventTree')
      inputFile=afile[:-1]
      myChain.Add(inputFile)
      EntryNumber = myChain.GetEntries()
      print 'Entry number for file ', fileNumber, ' : ', EntryNumber
      #EntryNumber = sys.argv[2]
      NoEntry = EntryNumber 
      for njob in xrange(0, divideJobs):
	floatchunk = NoEntry/divideJobs
	chunk = int(floatchunk)
	if(njob < (divideJobs-1)):
	  start = njob*chunk
	  stop = (njob+1)*chunk
	elif(njob == (divideJobs -1)):
	  start = njob*chunk
	  stop = NoEntry
	
        myfile = open('condor_MyNtupleMaker'+str(ifile)+'.sh','w')
        for line in sh_lines:
            if 'QQQ' in line:
                line = line.replace('QQQ',str(ifile))
            if 'GGGGG' in line:
	      fileN = afile[:-1]
	      line = line.replace('GGGGG', fileN)
	    if 'OOOOO' in line:
	      if 'Run2015D_Data_ggNtuple_Ming' in afile:
	        if 'job_DoubleEG_Run2015C_Oct05_miniAOD' in afile:
		  line = line.replace('OOOOO', 'NewData_RunC_'+str(ifile)+'.root')
		else:
		  line = line.replace('OOOOO', 'NewData_RunD_'+str(ifile)+'.root')
	      if 'phys_smp' in afile:
	        if 'job_DoubleEG_Run2015C_Oct05_miniAOD' in afile:
		  line = line.replace('OOOOO', 'NewData_RunC_'+str(ifile)+'.root')
		else:
		  line = line.replace('OOOOO', 'NewData_RunD_'+str(ifile)+'.root')
	      if 'GJet_Pt40' in afile:
		line = line.replace('OOOOO', 'NewData_SmallNtuple'+str(ifile)+'.root')
            if 'SSSSS' in line:
	      if 'Run2015D_Data_ggNtuple_Ming' in afile:
	        line = line.replace('SSSSS', str(start))
	      if 'GJet_Pt40' in afile:
		line = line.replace('SSSSS', str(start))
              if 'phys_smp' in afile:
		line = line.replace('SSSSS', str(start))
            if 'TTTTT' in line:
	      if 'Run2015D_Data_ggNtuple_Ming' in afile:
	        line = line.replace('TTTTT', str(stop))
	      if 'GJet_Pt40' in afile:
		line = line.replace('TTTTT', str(stop))
	      if 'phys_smp' in afile:
		line = line.replace('TTTTT', str(stop))
            myfile.write(line)
        myfile.close()
        
        
        myfile = open('condor_MyNtupleMaker'+str(ifile)+'.jdl','w')
        for line in jdl_lines:
            if 'QQQ' in line:
                line = line.replace('QQQ',str(ifile))
            myfile.write(line)
        myfile.close()
        

	os.system('condor_submit '+'condor_MyNtupleMaker'+str(ifile)+'.jdl')
	print '<Done>', ifile
	ifile+=1

    #print "created "+str(len(filelist))+' sets of jobs. please submit them.'
    time.sleep(120)
    ### extra security before rm ###
    os.system('pwd > check.txt')
    pwdtextfile = open('check.txt')
    pwdline = pwdtextfile.readlines()
    for aline in pwdline:
      if '/uscms_data/d3' in aline:
	#os.system('rm *')
	#os.system('rm JobCondor/*')
	print 'deleted all!'
    

       

if __name__=="__main__":
    main()
