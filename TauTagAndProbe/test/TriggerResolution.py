#!/usr/bin/python

from ROOT import *
from array import array

fIn = TFile.Open('NTuple.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

l1tResolution1 = TH1I("L1TriggerReso1", "L1T resolution for offline pt between 40 and 60 GeV", 100, -100, 100)
hltResolution1 = TH1I("HLTriggerReso1", "HLT resolution for offline pt between 40 and 60 GeV", 100, -100, 100)
l1tResolution2 = TH1I("L1TriggerReso2", "L1T resolution for offline pt between 60 and 100 GeV", 100, -100, 100)
hltResolution2 = TH1I("HLTriggerReso2", "HLT resolution for offline pt between 60 and 100 GeV", 100, -100, 100)

for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    ptOffline = tree.tauPt
    ptL1T = tree.l1tPt
    ptHLT = tree.hltPt
    deltaPtL1T = ptOffline - ptL1T
    deltaPtHLT = ptOffline - ptHLT
    if (ptOffline > 40)  and (ptOffline < 60):
        l1tResolution1.Fill(deltaPtL1T)
        hltResolution1.Fill(deltaPtHLT)
    if (ptOffline > 60)  and (ptOffline < 100):
        l1tResolution2.Fill(deltaPtL1T)
        hltResolution2.Fill(deltaPtHLT)

c1 = TCanvas("canvas1")
c1.cd()
l1tResolution1.GetXaxis().SetTitle("ptOffline - ptL1T");
l1tResolution1.Draw()
c1.Update()
c1.Print("l1tReso_40_60.pdf", "pdf")
c2 = TCanvas("canvas2")
c2.cd()
l1tResolution2.Draw()
l1tResolution2.GetXaxis().SetTitle("ptOffline - ptL1T");
c2.Update()
c2.Print("l1tReso_60_100.pdf", "pdf")
c3 = TCanvas("canvas3")
c3.cd()
hltResolution1.GetXaxis().SetTitle("ptOffline - ptHLT");
hltResolution1.Draw()
c3.Update()
c3.Print("hltReso_40_60.pdf", "pdf")
c4 = TCanvas("canvas4")
c4.cd()
hltResolution2.GetXaxis().SetTitle("ptOffline - ptHLT");
hltResolution2.Draw()
c4.Update()
c1.Print("hltReso_60_100.pdf", "pdf")

raw_input()
