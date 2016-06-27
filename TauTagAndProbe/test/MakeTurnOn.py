#!/usr/bin/python

from ROOT import *
from array import array

fIn = TFile.Open('NTuple.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

binning = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 45, 50, 60, 70, 80, 90, 100, 150]
bins = array('d', binning)

triggerNamesList = fIn.Get("triggerNames")


# hpass = TH1F ("hpass", "hpass", 75, 0, 150)
# htot = TH1F ("htot", "htot", 75, 0, 150)
hPassList = []
hTotList = []
turnOnList = []

#Preparing the Histograms
for bitIndex in range(0, len(triggerNamesList)):
    hPassList.append(TH1F("hPass_"+triggerNamesList[bitIndex], "hPass_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    hTotList.append(TH1F("hTot_"+triggerNamesList[bitIndex], "hTot_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    turnOnList.append(TGraphAsymmErrors())


#Populating the histograms
for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    pt = tree.tauPt
    triggerBits = tree.tauTriggerBits

    for bitIndex in range(0, len(triggerNamesList)):
        hTotList[bitIndex].Fill(pt)
        if ((triggerBits >> bitIndex) & 1) == 1:
            hPassList[bitIndex].Fill(pt)

#Calculating and saving the efficiencies

c1 = TCanvas ("c1", "c1", 600, 600)
c1.SetGridx()
c1.SetGridy()
fOut = TFile ("turnOn.root", "recreate")

for bitIndex in range(0, len(triggerNamesList)):
    turnOnList[bitIndex].Divide(hPassList[bitIndex], hTotList[bitIndex], "cl=0.683 b(1,1) mode")
    turnOnList[bitIndex].SetMarkerStyle(8)
    turnOnList[bitIndex].SetMarkerSize(0.8)
    turnOnList[bitIndex].SetMarkerColor(kRed)
    turnOnList[bitIndex].GetXaxis().SetTitle("p_t (GeV)");
    turnOnList[bitIndex].GetYaxis().SetTitle("Efficiency");
    turnOnList[bitIndex].SetTitle(triggerNamesList[bitIndex] + " turn-on curve")
    turnOnList[bitIndex].Draw("AP")
    c1.Update()
    c1.Print("turnOn_" + triggerNamesList[bitIndex] + ".pdf", "pdf")
    hTurnOn = hPassList[bitIndex].Clone("hTurnOn_" + triggerNamesList[bitIndex])
    hTurnOn.Divide(hTotList[bitIndex])
    hTurnOn.Write()
    hPassList[bitIndex].Write()
    hTotList[bitIndex].Write()


raw_input()
