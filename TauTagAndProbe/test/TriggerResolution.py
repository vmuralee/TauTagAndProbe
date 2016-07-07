#!/usr/bin/python

from ROOT import *
from array import array

fIn = TFile.Open('NTuple.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

l1tResolution1 = TH1I("L1TriggerReso1", "L1T resolution for offline pt between 40 and 60 GeV", 100, -100, 100)
hltResolution1 = TH1I("HLTriggerReso1", "HLT resolution for offline pt between 40 and 60 GeV", 100, -100, 100)
l1tResolution2 = TH1I("L1TriggerReso2", "L1T resolution for offline pt between 60 and 100 GeV", 100, -100, 100)
hltResolution2 = TH1I("HLTriggerReso2", "HLT resolution for offline pt between 60 and 100 GeV", 100, -100, 100)
#x = resolution
#y = R
l1tResolutionVsDR = TH2I("L1TriggerResoVsDR", "L1T resolution vs DR", 100, -100, 100, 30, -0.1, 0.2)
hltResolutionVsDR = TH2I("HLTriggerResoVsDR", "HLT resolution vs DR", 100, -100, 100, 30, -0.1, 0.2)

for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    ptOffline = tree.tauPt
    ptL1T = tree.l1tPt
    ptHLT = tree.hltPt
    deltaPtL1T = ptOffline - ptL1T
    deltaPtHLT = ptOffline - ptHLT
    deltaR = ((tree.tauEta - tree.hltEta)**2 + (tree.tauPhi - tree.hltPhi)**2)**0.5
    
    if (ptOffline > 40)  and (ptOffline < 60):
        l1tResolution1.Fill(deltaPtL1T)
        hltResolution1.Fill(deltaPtHLT)
    if (ptOffline > 60)  and (ptOffline < 100):
        l1tResolution2.Fill(deltaPtL1T)
        hltResolution2.Fill(deltaPtHLT)

    hltResolutionVsDR.Fill(deltaPtHLT, deltaR)
  
l1tResolution1.GetXaxis().SetTitle("ptOffline - ptL1T")
#l1tResolution1.Draw()
#c1.Update()
#c1.Print("l1tReso_40_60.pdf", "pdf")
l1tResolution2.GetXaxis().SetTitle("ptOffline - ptL1T")
#l1tResolution2.Draw()
#c1.Update()
#c1.Print("l1tReso_60_100.pdf", "pdf")
hltResolution1.GetXaxis().SetTitle("ptOffline - ptHLT")
#hltResolution1.Draw()
#c1.Update()
#c1.Print("hltReso_40_60.pdf", "pdf")
hltResolution2.GetXaxis().SetTitle("ptOffline - ptHLT")
#hltResolution2.Draw()
#c1.Update()
#c1.Print("hltReso_60_100.pdf", "pdf")

hltResolutionVsDR.GetXaxis().SetTitle("ptOffline - ptHLT")
hltResolutionVsDR.GetYaxis().SetTitle("Delta R")
hltResolutionVsDR.Draw("COLZ")
c1.Update()
c1.Print("hltResoVsDR.pdf", "pdf")


raw_input()
