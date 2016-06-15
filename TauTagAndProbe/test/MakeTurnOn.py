from ROOT import *
from array import array

fIn = TFile.Open('NTuple.root')
tree = fIn.Get('Ntuplizer/TagAndProbe')

binning = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 45, 50, 60, 70, 80, 90, 100, 150]
bins = array('d', binning)

# hpass = TH1F ("hpass", "hpass", 75, 0, 150)
# htot = TH1F ("htot", "htot", 75, 0, 150)
hpass = TH1F ("hpass", "hpass", len(binning)-1, bins)
htot = TH1F ("htot", "htot", len(binning)-1, bins)

for iEv in range (0, tree.GetEntries()):
    tree.GetEntry(iEv)
    pt = tree.tauPt
    htot.Fill(pt)
    if tree.isTriggered == 1:
        hpass.Fill(pt)

to = TGraphAsymmErrors()
to.BayesDivide (hpass, htot)

to.SetMarkerStyle(8)
to.SetMarkerSize(0.8)
to.SetMarkerColor(kRed)
c1 = TCanvas ("c1", "c1", 600, 600)
c1.SetGridx()
c1.SetGridy()
to.Draw("AP")

c1.Update()
c1.Print("turnOn.pdf", "pdf")

fOut = TFile ("turnOn.root", "recreate")
hTurnOn = hpass.Clone("hTurnOn")
hTurnOn.Divide(htot)
hTurnOn.Write()

raw_input()