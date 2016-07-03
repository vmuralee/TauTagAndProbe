#!/usr/bin/python

from ROOT import *
from array import array

fIn = TFile.Open('NTuple_Merge_2Lug.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

binning = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 45, 50, 60, 70, 80, 90, 100, 150]
bins = array('d', binning)

triggerNamesTree = fIn.Get("Ntuplizer/triggerNames")

triggerNamesList = []


# hpass = TH1F ("hpass", "hpass", 75, 0, 150)
# htot = TH1F ("htot", "htot", 75, 0, 150)
hPassListSS = []
hPassListOS = []
hTotListSS = []
hTotListOS = []
turnOnList = []

for iTrig in range (0, 6):
    triggerNamesTree.GetEntry(iTrig)
    triggerNamesList.append(triggerNamesTree.triggerNames.Data())

#Preparing the Histograms
for bitIndex in range(0, len(triggerNamesList)):
    hPassListOS.append(TH1F("hPassOS_"+triggerNamesList[bitIndex], "hPassOS_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    hTotListOS.append(TH1F("hTotOS_"+triggerNamesList[bitIndex], "hTotOS_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    hPassListSS.append(TH1F("hPassSS_"+triggerNamesList[bitIndex], "hPassSS_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    hTotListSS.append(TH1F("hTotSS_"+triggerNamesList[bitIndex], "hTotSS_"+triggerNamesList[bitIndex], len(binning)-1, bins))
    turnOnList.append(TGraphAsymmErrors())


#Populating the histograms
for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    pt = tree.tauPt
    triggerBits = tree.tauTriggerBits
    for bitIndex in range(0, len(triggerNamesList)):
        if tree.isOS == True:
            hTotListOS[bitIndex].Fill(pt)
            if ((triggerBits >> bitIndex) & 1) == 1:
                hPassListOS[bitIndex].Fill(pt)
        else:
            hTotListSS[bitIndex].Fill(pt)
            if ((triggerBits >> bitIndex) & 1) == 1:
                hPassListSS[bitIndex].Fill(pt)

#Calculating and saving the efficiencies

c1 = TCanvas ("c1", "c1", 600, 600)
c1.SetGridx()
c1.SetGridy()
fOut = TFile ("turnOn.root", "recreate")

for bitIndex in range(0, len(triggerNamesList)):
    hPassListOS[bitIndex].Add(hPassListSS[bitIndex], -1)
    hTotListOS[bitIndex].Add(hTotListSS[bitIndex], -1)
    turnOnList[bitIndex].Divide(hPassListOS[bitIndex], hTotListOS[bitIndex], "cl=0.683 b(1,1) mode")
    turnOnList[bitIndex].SetMarkerStyle(8)
    turnOnList[bitIndex].SetMarkerSize(0.8)
    turnOnList[bitIndex].SetMarkerColor(kRed)
    turnOnList[bitIndex].GetXaxis().SetTitle("p_t (GeV)");
    turnOnList[bitIndex].GetYaxis().SetTitle("Efficiency");
    turnOnList[bitIndex].SetTitle(triggerNamesList[bitIndex] + " turn-on curve")
    turnOnList[bitIndex].Draw("AP")
    c1.Update()
    c1.Print("turnOn_" + triggerNamesList[bitIndex] + ".pdf", "pdf")
    hTurnOn = hPassListOS[bitIndex].Clone("hTurnOn_" + triggerNamesList[bitIndex])
    hTurnOn.Divide(hTotListOS[bitIndex])
    hTurnOn.Write()
    hPassListOS[bitIndex].Write()
    hTotListOS[bitIndex].Write()


raw_input()
