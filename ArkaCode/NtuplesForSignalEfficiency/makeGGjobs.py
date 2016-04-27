import os, sys, re, time, commands
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

    #mytextfile = open('FinalSignalSample19Feb.txt')
    #mytextfile = open('FinalSignalSample19Feb.txt') # with Allies newly ntuplized result.
    mytextfile = open(sys.argv[1])
    filelist = mytextfile.readlines()
    mytextfile.close()
    
    lumi = 2260.0 # in pb^{-1}
    ifile = 0
    myfile = open('MyNtupleMaker'+str(ifile)+'.C','w')
    for line in C_lines:
	if 'MyNtupleMakerQQQ' in line:
	    line = line.replace('MyNtupleMakerQQQ', 'MyNtupleMaker'+str(ifile))
	if 'WWW' in line:
	    line = line.replace('WWW', str(ifile))
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
        
    mGluNumber = 0
    eventNumber = []
    eventNumberTracker = 0
    for mGlu in xrange(1000, 2001):
      if((mGlu>=1000) and (mGlu%50==0)):
	glumass = 'mGlu_'+str(mGlu)
	for mNeu in xrange(100, 1901):
	  if((mNeu<mGlu) and (mNeu%100==0)):
	    neumass = 'mNeu_'+str(mNeu)
	    fullmass = glumass+'_'+neumass
	    fullmassRoot = fullmass+'.root'
	    totalEntryNumber = 0
	    for afile in filelist:
	      #afile = afile.replace('/eos/uscms/','root://cms-xrd-global.cern.ch//')
	      afile = afile.replace('/eos/uscms/','root://cmsxrootd.fnal.gov//')
	      if fullmassRoot in afile:
		myChain = TChain('ggNtuplizer/EventTree')
		inputFile=afile[:-1]
		myChain.Add(inputFile)
		totalEntryNumber = totalEntryNumber + myChain.GetEntries()
	    eventNumber.append(totalEntryNumber)
	    print 'mGlu ', mGlu,' mNeu: ', mNeu,' entryNumber: ',totalEntryNumber 
    
    ifile=0
    for mGlu in xrange(1000, 2001):
      if((mGlu>=1000) and (mGlu%50==0)):
	glumass = 'mGlu_'+str(mGlu)
	for mNeu in xrange(100, 1901):
	  if((mNeu<mGlu) and (mNeu%100==0)):
	    neumass = 'mNeu_'+str(mNeu)
	    fullmass = glumass+'_'+neumass
	    fullmassRoot = fullmass+'.root'
	    print 'fullmass selected: ', fullmass
	    #RootFile='SignalSample_'+fullmass+'_AllFiles.root'
	    for afile in filelist:
	      #afile = afile.replace('/eos/uscms/','root://cms-xrd-global.cern.ch//')
	      afile = afile.replace('/eos/uscms/','root://cmsxrootd.fnal.gov//')
	      if fullmassRoot in afile:
		myfile = open('condor_MyNtupleMaker'+str(ifile)+'.sh','w')
		for line in sh_lines:
		    if 'QQQ' in line:
			line = line.replace('QQQ',str(ifile))
		    if 'GGGGG' in line:
		      fileN = afile[:-1]
		      line = line.replace('GGGGG', fileN)
		    if 'OOOOO' in line:
		      line = line.replace('OOOOO', 'SignalPoint_'+fullmass+'.root') ########## change the name here ##############
		      print 'Expected output root file: SignalPoint_'+fullmass+'.root' 
		      #OutRootFile = 'SignalPoint_'+fullmass+'_*.root'
		    if 'WWWWW' in line:
		      # xsec for gluino-gluino production
		      if mGlu == 1000: xsec = 0.325388
		      elif mGlu == 1050: xsec = 0.229367
		      elif mGlu == 1100: xsec = 0.163491
		      elif mGlu == 1150: xsec = 0.117687
		      elif mGlu == 1200: xsec = 0.0856418
		      elif mGlu == 1250: xsec = 0.0627027
		      elif mGlu == 1300: xsec = 0.0460525
		      elif mGlu == 1350: xsec = 0.0340187
		      elif mGlu == 1400: xsec = 0.0252977
		      elif mGlu == 1450: xsec = 0.0188887
		      elif mGlu == 1500: xsec = 0.0141903
		      elif mGlu == 1550: xsec = 0.0107027
		      elif mGlu == 1600: xsec = 0.00810078
		      elif mGlu == 1650: xsec = 0.00616072
		      elif mGlu == 1700: xsec = 0.00470323
		      elif mGlu == 1750: xsec = 0.00359842
		      elif mGlu == 1800: xsec = 0.00276133
		      elif mGlu == 1850: xsec = 0.00212345
		      elif mGlu == 1900: xsec = 0.00163547
		      elif mGlu == 1950: xsec = 0.0012642
		      elif mGlu == 2000: xsec = 0.000981077
		      
		      if(eventNumber[eventNumberTracker] != 0):xsecValue = xsec*lumi/eventNumber[eventNumberTracker] # match eff 0.392667* 
		      else: xsecValue = 0
		      print 'mGlu: ',mGlu, ' mNeu: ',mNeu,' xSec: ',xsec,' evtNumber: ',eventNumber[eventNumberTracker]
		      line = line.replace('WWWWW',str(xsecValue))
		    myfile.write(line)
		myfile.close()
		
		
		myfile = open('condor_MyNtupleMaker'+str(ifile)+'.jdl','w')
		for line in jdl_lines:
		    if 'QQQ' in line:
			line = line.replace('QQQ',str(ifile))
		    myfile.write(line)
		myfile.close()
		

		os.system('condor_submit '+'condor_MyNtupleMaker'+str(ifile)+'.jdl')
		print '<Done>', fullmass, 'and ', ifile
		ifile+=1
		
	    eventNumberTracker = eventNumberTracker + 1
	    #time.sleep(1)
	    #(status, output) = commands.getstatusoutput('hadd '+RootFile+' '+OutRootFile)
	    #if status:
	      #print 'hadd did not work, find out the problem'
	    #else:
	      #print 'hadd worked, moving on to do all the other jobs'

    #print "created "+str(len(filelist))+' sets of jobs. please submit them.'
    time.sleep(300)
    #os.system('mv *.root SignalNtuples')
    #### extra security before rm ###
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
