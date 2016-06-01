### run it: python PythonSubmit.py 40 <txt file name> <analysisFake/extendedFake boolean True/False>

import os, sys, re, time, commands



def main():
    myfile=open('condor_SmallNtupleMASTER.jdl')
    jdl_lines = myfile.readlines()
    myfile.close()

    myfile=open('condor_SmallNtupleMASTER.sh')
    sh_lines = myfile.readlines()
    myfile.close()
    
    myfile=open('SmallNtupleMASTER.C')
    C_lines = myfile.readlines()
    myfile.close()
    
    myfileheader=open('SmallNtupleMASTER.h')
    h_lines = myfileheader.readlines()
    myfileheader.close()
    
    myfileroot=open('RootPromptMASTER.sh')
    root_lines = myfileroot.readlines()
    myfileroot.close()

    textFileName = sys.argv[2]
    #mytextfile = open('SmallNtuple_Data_RunD.txt')
    #mytextfile = open('Data_UnblindedRunCD_25ns.txt')
    mytextfile = open(textFileName)
    filelist = mytextfile.readlines()
    mytextfile.close()
    
    ptcut = sys.argv[1]
    anFakeValue = sys.argv[3]
    
    if anFakeValue == 'True':
      anFake = True
    else:
      anFake = False

    ifile = 0
    RootFile = ''
    OutRootFile = ''
    myfileNew = open('SmallNtuple'+str(ifile)+'.C','w')
    for line in C_lines:	
	if 'SmallNtupleQQQ' in line:
	    line = line.replace('SmallNtupleQQQ', 'SmallNtuple'+str(ifile))
	if 'WWW' in line:
	    line = line.replace('WWW', str(ifile))
	if 'RRR' in line:
	    line = line.replace('RRR', str(ptcut))
	myfileNew.write(line)
    myfileNew.close()
    myfileNew = open('SmallNtuple'+str(ifile)+'.h','w')
    for line in h_lines:
	if 'QQQ' in line:
	    line = line.replace('QQQ',str(ifile))          
	myfileNew.write(line)
    myfileNew.close()
    myfile = open('RootPrompt'+str(ifile)+'.sh','w')
    for line in root_lines:
	myfile.write(line)
    myfile.close()
    os.system('bash RootPrompt0.sh')
    for afile in filelist:
        #if ifile > 1:
	  #break    
        afile = afile.replace('/eos/uscms/','root://cmsxrootd.fnal.gov//')
        
        myfile = open('condor_SmallNtuple'+str(ifile)+'.sh','w')
        for line in sh_lines:
            if 'QQQ' in line:
                line = line.replace('QQQ',str(0))
            if 'FILENAME' in line:
	      if 'DYtoEE' in afile:
	        line = line.replace('FILENAME', 'DYtoEEFile74_Pt_RRR_WWW.root')
	        RootFile='DYtoEEWeightedProper74.root'
	        OutRootFile='DYtoEEFile*.root'

	        ## comment them in if you want separate HT samples
	      '''if 'DYJet100' in afile:
		line = line.replace('FILENAME', 'DYJetFile74_Pt_RRR_WWW.root')
		RootFile='DYJetAllWeightedNewPhoId100.root'
	        OutRootFile='DYJetFile*.root'
              if 'DYJet200' in afile:
		line = line.replace('FILENAME', 'DYJetFile74_Pt_RRR_WWW.root')
		RootFile='DYJetAllWeightedNewPhoId200.root'
	        OutRootFile='DYJetFile*.root'
              if 'DYJet400' in afile:
		line = line.replace('FILENAME', 'DYJetFile74_Pt_RRR_WWW.root')
		RootFile='DYJetAllWeightedNewPhoId400.root'
	        OutRootFile='DYJetFile*.root'
              if 'DYJet600' in afile:
		line = line.replace('FILENAME', 'DYJetFile74_Pt_RRR_WWW.root')
		RootFile='DYJetAllWeightedNewPhoId600.root'
	        OutRootFile='DYJetFile*.root' '''
	        
	       ### comment this out if you want individual HT binned sample
	      if 'DYJet' in afile:
		line = line.replace('FILENAME', 'DYJetFile74_Pt_RRR_WWW.root')
		RootFile='DYJetAllWeightedNewPhoIdAll.root'
	        OutRootFile='DYJetFile*.root'
              if 'TTBar' in afile:
		line = line.replace('FILENAME', 'TTJetFile74_Pt_RRR_WWW.root')
		RootFile='TTJetAllWeightedNewPhoId.root'
	        OutRootFile='TTJetFile*.root'
              if 'WJets' in afile:
		line = line.replace('FILENAME', 'WJetFile74_Pt_RRR_WWW.root')
		RootFile='WJetAllWeightedNewPhoId.root'
	        OutRootFile='WJetFile*.root'
	      if 'GJet_Pt40_Large/Part1' in afile:
		line = line.replace('FILENAME', 'GJetFile1_Pt_RRR_74_WWW.root')
		RootFile='GJet_Pt40_1.root'
	        OutRootFile='GJetFile1*.root'
	      if 'GJet_Pt40_Large/Part2' in afile:
		line = line.replace('FILENAME', 'GJetFile2_Pt_RRR_74_WWW.root')
		RootFile='GJet_Pt40_2.root'
	        OutRootFile='GJetFile2*.root'
	      if 'Data_RunD_25ns' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		RootFile='Data_RunD_All.root'
	        OutRootFile='Data_RunD_Pt*.root'
	      if 'Data_UnblindedRunD_25ns' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		RootFile='Data_RunD_All.root'
	        OutRootFile='Data_RunD_Pt*.root'
	      if 'Data_UnblindedRunC_25ns' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		RootFile='Data_RunD_All.root'
	        OutRootFile='Data_RunD_Pt*.root'
	      if 'Data_RunD_10Nov' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		RootFile='Data_RunD_All.root'
	        OutRootFile='Data_RunD_Pt*.root'
	      if 'Data_RunD_25Jan' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
	      if 'Data_RunD_28Feb' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
	      if 'Data_RunD_Again_28Feb' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
              if 'Data_RunD_28Feb_Part3' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
	      if 'Data_RunD_28Feb_Part4' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
              if 'Data_RunD_28Feb_Part5' in afile:
		line = line.replace('FILENAME', 'Data_RunD_Pt_RRR_74_WWW.root')
		if(anFake):RootFile='Data_RunD_All_AnalysisFake_217fb.root'
		else:RootFile='Data_RunD_All_ExtendedFake_217fb.root'
		
	        OutRootFile='Data_RunD_Pt*.root'
	      if 'WWW' in line:
	        line = line.replace('WWW', str(ifile))
	      if 'RRR' in line:
	        line = line.replace('RRR', str(ptcut))
	    if 'GGGGG' in line:
	      namefile = afile[:-1]
              line = line.replace('GGGGG',namefile)
            myfile.write(line)
        myfile.close()
        
        
        myfile = open('condor_SmallNtuple'+str(ifile)+'.jdl','w')
        for line in jdl_lines:
            if 'QQQ' in line:
                line = line.replace('QQQ',str(ifile))
            if 'RRR' in line:
                line = line.replace('RRR',str(ptcut))
            myfile.write(line)
        myfile.close()
        
        os.system('condor_submit '+'condor_SmallNtuple'+str(ifile)+'.jdl')
        print '< Done Submitting jobs: >', ifile
        ifile+=1

    time.sleep(120)
    (status, output) = commands.getstatusoutput('hadd '+RootFile+' '+OutRootFile)
    if status:
      print 'hadd did not work, look for pathetic root files here: '+output
    else:
      os.system('mv '+RootFile+' ../RootSmallNtuple74')
      ### extra security before rm ###
      os.system('pwd > check.txt')
      pwdtextfile = open('check.txt')
      pwdline = pwdtextfile.readlines()
      for aline in pwdline:
        if '/uscms_data/d3' in aline:
          #os.system('rm *')
          os.system('rm JobCondor/*')
          print 'deleted all!'
    

       

if __name__=="__main__":
    main()
