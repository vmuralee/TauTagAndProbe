#!/usr/bin/python

from ROOT import *
from array import array

gStyle.SetOptStat(111111)

fIn = TFile.Open('NTuple_10Ago_Riccardo.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

l1tResolution = TH1I("L1TriggerReso1", "L1T resolution for offline pt between 20 and 40 GeV", 100, -100, 100)
hltResolution = TH1I("HLTriggerReso1", "HLT resolution for offline pt between 20 and 40 GeV", 100, -100, 100)

for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    ptOffline = tree.tauPt
    ptL1T = tree.l1tPt
    ptHLT = tree.hltPt
    if ptHLT > 0:
        deltaPtHLT = ptOffline - ptHLT
        hltResolution.Fill(deltaPtHLT)
    if ptL1T > 0:
        deltaPtL1T = ptOffline - ptL1T
        l1tResolution.Fill(deltaPtL1T)

l1tCanvas = TCanvas("l1tCanvas")
l1tResolution.GetXaxis().SetTitle("ptOffline - ptL1T")
l1tResolution.Draw()
l1tCanvas.Update()
l1tCanvas.Print("l1tResolution.pdf", "pdf")

hltCanvas = TCanvas("hltCanvas")
hltResolution.GetXaxis().SetTitle("ptOffline - ptHLT")
hltResolution.Draw()
hltCanvas.Update()
hltCanvas.Print("hltResolution.pdf", "pdf")

raw_input()
