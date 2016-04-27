import os, sys, re, time, commands, math
from ROOT import *


import os, sys, re, math
from ROOT import *
from time import sleep
import numpy as n
import array
#### needed to import files from different folder ######
sys.path.insert(0, '/home/arka/arka/include')
from Functions import * 

mytextfile = open('SignalSampleFiles_All.txt')
filelist = mytextfile.readlines()
mytextfile.close()

mytextfilexsec = open('SignalSampleFiles_XSec.txt')
filelistxsec = mytextfilexsec.readlines()
mytextfilexsec.close()


#xbins = array.array('f',[1000, 1100, 1200, 1300, 1350, 1400, 1450, 1500, 1550, 1600, 1650, 1700, 1750, 1800, 1850, 1900, 1950, 2000, 2050])
#xbinnum = len(xbins)-1

#ybins = array.array('f',[100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000, 2100])
#ybinnum = len(ybins)-1


xbins = array.array('f',[950, 1050, 1150, 1250, 1325, 1375, 1425, 1475, 1525, 1575, 1625, 1675, 1725, 1775, 1825, 1875, 1925, 1975, 2025])
xbinnum = len(xbins)-1

ybins = array.array('f',[50,150,250,350,450,550,650,750,850,950,1050,1150,1250,1350,1450,1550,1650,1750,1850,1950, 2050])
ybinnum = len(ybins)-1



h_Eff_Grid = TH2D('h_Eff_Grid','Efficiency#times Acceptance for T5gg signal points; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_2D_All = TH2D('h_2D_All','Efficiency#times Acceptance for T5gg signal points; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_2D_Pass = TH2D('h_2D_Pass','Efficiency#times Acceptance for T5gg signal points; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_Eff_Grid_Divide = TH2D('h_Eff_Grid_Divide','Efficiency#times Acceptance for T5gg signal points; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET100to110_Grid = TH2D('h_MET100to110_Grid','Events for MET>100 and MET < 110 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET110to120_Grid = TH2D('h_MET110to120_Grid','Events for MET>110 and MET < 120 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET120to140_Grid = TH2D('h_MET120to140_Grid','Events for MET>120 and MET < 140 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET140to6000_Grid = TH2D('h_MET140to6000_Grid','Events for MET>140 and MET < 6000 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)

h_MET100to110_GridStatError = TH2D('h_MET100to110_GridStatError','Events for MET>100 and MET < 110 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET110to120_GridStatError = TH2D('h_MET110to120_GridStatError','Events for MET>110 and MET < 120 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET120to140_GridStatError = TH2D('h_MET120to140_GridStatError','Events for MET>120 and MET < 140 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET140to6000_GridStatError = TH2D('h_MET140to6000_GridStatError','Events for MET>140 and MET < 6000 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)


h_MET100to110_GridJESUpError = TH2D('h_MET100to110_GridJESUpError','Events for MET>100 and MET < 110 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET110to120_GridJESUpError = TH2D('h_MET110to120_GridJESUpError','Events for MET>110 and MET < 120 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET120to140_GridJESUpError = TH2D('h_MET120to140_GridJESUpError','Events for MET>120 and MET < 140 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET140to6000_GridJESUpError = TH2D('h_MET140to6000_GridJESUpError','Events for MET>140 and MET < 6000 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)


h_MET100to110_GridJESDownError = TH2D('h_MET100to110_GridJESDownError','Events for MET>100 and MET < 110 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET110to120_GridJESDownError = TH2D('h_MET110to120_GridJESDownError','Events for MET>110 and MET < 120 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET120to140_GridJESDownError = TH2D('h_MET120to140_GridJESDownError','Events for MET>120 and MET < 140 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)
h_MET140to6000_GridJESDownError = TH2D('h_MET140to6000_GridJESDownError','Events for MET>140 and MET < 6000 GeV; Gluino Mass (GeV); Neutralino Mass (GeV)', xbinnum, xbins, ybinnum, ybins)


for mGlu in xrange(0, 2001):
  if((mGlu>=1000) and (mGlu%50==0)):
    glumass = 'mGlu_'+str(mGlu)
    for mNeu in xrange(0, 1901):
      if((mNeu>=100) and (mNeu<mGlu) and (mNeu%100==0)):
	neumass = 'mNeu_'+str(mNeu)
	fullmass = glumass+'_'+neumass+'.root'
	print 'fullmass selected: ', fullmass
	for afile in filelist:
	  if fullmass in afile:
	    filename = str(afile[:-1])
	    
	    fileData_ = TFile(filename) #TFile('SignalSampleNtuple/SignalSample_mG1000_mN200_AllFiles.root') # put the data file

	    h_All = fileData_.Get('h_All_Signal_MET')
	    h_Pass = fileData_.Get('h_DoublePhoton_Signal_MET')
	    h_Pass_Three = fileData_.Get('h_DoublePhotonFromThree_Signal_MET')
	    denom = h_All.Integral(0, h_All.GetNbinsX()+1)
	    nume = h_Pass.Integral(0, h_Pass.GetNbinsX()+1)  # - h_Pass_Three.GetEntries() # subtract events where we have fgg or gfg
	    
	    if(denom!=0):print 'Efficiency', nume/denom
	    
	    h_MET_Signal = fileData_.Get('h_DoublePhoton_Signal_METExpected')
	    h_MET_Signal_Stat = fileData_.Get('h_DoublePhoton_Signal_METExpectedUnweighted')
	    
	    h_MET_Signal_METJESUp = fileData_.Get('h_DoublePhoton_Signal_METJESUpExpected')
	    h_MET_Signal_METJESUp_Stat = fileData_.Get('h_DoublePhoton_Signal_METJESUpExpectedUnweighted')
	    
	    h_MET_Signal_METJESDown = fileData_.Get('h_DoublePhoton_Signal_METJESDownExpected')
	    h_MET_Signal_METJESDown_Stat = fileData_.Get('h_DoublePhoton_Signal_METJESDownExpectedUnweighted')
	    
	    #h_MET_Signal.Scale(1.0, "width")
	    
	    h_2D_All.Fill(mGlu, mNeu, denom)
	    h_2D_Pass.Fill(mGlu, mNeu, nume)
	    if(denom!=0):
	      h_Eff_Grid.Fill(mGlu, mNeu, nume/denom)
	      h_Eff_Grid.SetBinError(mGlu, mNeu, (nume/denom)*CalculateError(math.sqrt(nume), nume, math.sqrt(denom), denom))
	    else:
	      h_Eff_Grid.Fill(mGlu, mNeu, 0)
	      h_Eff_Grid.SetBinError(mGlu, mNeu, 0)
	    
	    h_MET100to110_Grid.Fill(mGlu, mNeu, h_MET_Signal.GetBinContent(1))
	    h_MET110to120_Grid.Fill(mGlu, mNeu, h_MET_Signal.GetBinContent(2))
	    h_MET120to140_Grid.Fill(mGlu, mNeu, h_MET_Signal.GetBinContent(3))
	    h_MET140to6000_Grid.Fill(mGlu, mNeu, h_MET_Signal.GetBinContent(4)+h_MET_Signal.GetBinContent(5))
	    
	    
	    #if(h_MET_Signal_Stat.GetBinContent(1)!=0):h_MET100to110_GridStatError.Fill(mGlu, mNeu, h_MET_Signal_Stat.GetBinError(1)/h_MET_Signal_Stat.GetBinContent(1))
	    #if(h_MET_Signal_Stat.GetBinContent(1)!=0):h_MET110to120_GridStatError.Fill(mGlu, mNeu, h_MET_Signal_Stat.GetBinError(2)/h_MET_Signal_Stat.GetBinContent(2))
	    #if(h_MET_Signal_Stat.GetBinContent(1)!=0):h_MET120to140_GridStatError.Fill(mGlu, mNeu, h_MET_Signal_Stat.GetBinError(3)/h_MET_Signal_Stat.GetBinContent(3))
	    #if(h_MET_Signal_Stat.GetBinContent(1)!=0):h_MET140to6000_GridStatError.Fill(mGlu, mNeu, math.sqrt(h_MET_Signal_Stat.GetBinError(4)*h_MET_Signal_Stat.GetBinError(4)+h_MET_Signal_Stat.GetBinError(5)*h_MET_Signal_Stat.GetBinError(5))/(h_MET_Signal_Stat.GetBinContent(4) + h_MET_Signal_Stat.GetBinContent(5)))
	    
	    #if(h_MET_Signal_Stat.GetBinContent(1)!=0):h_MET100to110_GridJESUpError.Fill(mGlu, mNeu, (h_MET_Signal_METJESUp.GetBinContent(1) - h_MET_Signal.GetBinContent(1))/h_MET_Signal.GetBinContent(1))
	    #h_MET110to120_GridJESUpError.Fill(mGlu, mNeu, (h_MET_Signal_METJESUp.GetBinContent(2) - h_MET_Signal.GetBinContent(2))/h_MET_Signal.GetBinContent(2))
	    #h_MET120to140_GridJESUpError.Fill(mGlu, mNeu, (h_MET_Signal_METJESUp.GetBinContent(3) - h_MET_Signal.GetBinContent(3))/h_MET_Signal.GetBinContent(3))
	    #h_MET140to6000_GridJESUpError.Fill(mGlu, mNeu, (h_MET_Signal_METJESUp.GetBinContent(4) + h_MET_Signal_METJESUp.GetBinContent(5) - h_MET_Signal.GetBinContent(4) - h_MET_Signal.GetBinContent(5))/(h_MET_Signal.GetBinContent(4)+h_MET_Signal.GetBinContent(5)) )
	    
	    #h_MET100to110_GridJESDownError.Fill(mGlu, mNeu, (h_MET_Signal.GetBinContent(1) - h_MET_Signal_METJESDown.GetBinContent(1))/h_MET_Signal.GetBinContent(1))
	    #h_MET110to120_GridJESDownError.Fill(mGlu, mNeu, (h_MET_Signal.GetBinContent(2) - h_MET_Signal_METJESDown.GetBinContent(2))/h_MET_Signal.GetBinContent(2))
	    #h_MET120to140_GridJESDownError.Fill(mGlu, mNeu, (h_MET_Signal.GetBinContent(3) - h_MET_Signal_METJESDown.GetBinContent(3))/h_MET_Signal.GetBinContent(3))
	    #h_MET140to6000_GridJESDownError.Fill(mGlu, mNeu, (h_MET_Signal.GetBinContent(4) + h_MET_Signal.GetBinContent(5) - h_MET_Signal_METJESDown.GetBinContent(4) - h_MET_Signal_METJESDown.GetBinContent(5) )/(h_MET_Signal.GetBinContent(4)+h_MET_Signal.GetBinContent(5)))

h_Eff_Grid_Divide.Divide(h_2D_Pass, h_2D_All)
fileSave = TFile('EfficiencyFile.root','RECREATE')
fileSave.cd()
#h_Eff_Grid.Write()
h_Eff_Grid_Divide.Write()
h_2D_Pass.Write()
h_2D_All.Write()
List2d = [h_Eff_Grid]
LegName = ["Signal points"]
xAxis = h_Eff_Grid.GetXaxis().GetTitle()
yAxis = h_Eff_Grid.GetYaxis().GetTitle()
zAxis = 'Efficiency#times Acceptance'
xrangedown = 950
xrangeup = 1825
yrangedown = 50
yrangeup = 1750
zrangedown = 0.16
zrangeup = 0.29

Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "Efficiency_Signal_Short_NewT5gg", False)


List2d = [h_Eff_Grid_Divide]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "Efficiency_Signal_Divide_Short_NewT5gg", False)


List2d = [h_MET100to110_Grid]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "SignalPoint_MET100to110_Short_NewT5gg", False)

List2d = [h_MET110to120_Grid]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "SignalPoint_MET110to120_Short_NewT5gg", False)

List2d = [h_MET120to140_Grid]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "SignalPoint_MET120to140_Short_NewT5gg", False)

List2d = [h_MET140to6000_Grid]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "SignalPoint_MET140to5000_Short_NewT5gg", False)


hEff = h_2D_Pass.Clone('hEff')
hEff.Reset()
tEff = TEfficiency(h_2D_Pass, h_2D_All)
for ibin in range(1,h_2D_Pass.GetXaxis().GetNbins()+1):
  for jbin in range(1,h_2D_Pass.GetYaxis().GetNbins()+1):
    CentralValue = 0.0
    if(h_2D_All.GetBinContent(ibin,jbin)!=0):
      CentralValue = h_2D_Pass.GetBinContent(ibin,jbin)/h_2D_All.GetBinContent(ibin,jbin)
    err = tEff.ClopperPearson(int(h_2D_All.GetBinContent(ibin,jbin)),int(h_2D_Pass.GetBinContent(ibin,jbin)),0.683,True)
    ehi = tEff.ClopperPearson(int(h_2D_All.GetBinContent(ibin,jbin)),int(h_2D_Pass.GetBinContent(ibin,jbin)),0.683,True)
    elo = tEff.ClopperPearson(int(h_2D_All.GetBinContent(ibin,jbin)),int(h_2D_Pass.GetBinContent(ibin,jbin)),0.683,False)
    hEff.SetBinContent(ibin,jbin,CentralValue)
    err = 0.5*TMath.Sqrt(pow(ehi-CentralValue,2)+pow(elo-CentralValue,2))
    hEff.SetBinError(ibin,jbin,err)


hEff.Write()
List2d = [hEff]
Draw2DHists(List2d, LegName, xAxis, yAxis, zAxis, xrangedown, xrangeup, yrangedown, yrangeup, zrangedown, zrangeup, "Efficiency_Signal_ClopperPearson_NotThree_Short", False)


Rootfile = TFile('SignalExpectation_NewNtuples.root','RECREATE')
Rootfile.cd()

h_MET100to110_Grid.Write()
h_MET110to120_Grid.Write()
h_MET120to140_Grid.Write()
h_MET140to6000_Grid.Write()

h_MET100to110_GridStatError.Write()
h_MET110to120_GridStatError.Write()
h_MET120to140_GridStatError.Write()
h_MET140to6000_GridStatError.Write()

h_MET100to110_GridJESUpError.Write()
h_MET110to120_GridJESUpError.Write()
h_MET120to140_GridJESUpError.Write()
h_MET140to6000_GridJESUpError.Write()

h_MET100to110_GridJESDownError.Write()
h_MET110to120_GridJESDownError.Write()
h_MET120to140_GridJESDownError.Write()
h_MET140to6000_GridJESDownError.Write()



