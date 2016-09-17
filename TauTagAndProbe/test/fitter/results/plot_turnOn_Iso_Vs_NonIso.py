import ROOT
import TurnOnPlot_DATA as TurnOnPlot

### Edit here ###

# TRIGGERS MUST BE DECLARED
triggers = ["Pt_26GeV","Pt_30GeV","Pt_34GeV"]
# PLOT TITLES
#plotTitles = ["HLT MediumIsoPFTau32 Barrel - Endcaps", "HLT MediumIsoPFTau20 Barrel - Endcaps"]
# ROOT FILE CONTAINING THE Barrel
fileName = "FittedTurnOn_Final_MC.root"

### Do not edit from here ###

#open turn on file
inputFile = ROOT.TFile.Open(fileName)

histo_NonIso = []
histo_Iso = []
fit_NonIso = []
fit_Iso = []
turnon_NonIso = []
turnon_Iso = []
plots = []

for trigger in triggers:
    histo_NonIso.append(inputFile.Get("histo_Stage2_All_vs_" + trigger))
    histo_NonIso[-1].__class__ = ROOT.RooHist
    histo_Iso.append(inputFile.Get("histo_Stage2_All_vs_" + trigger + "_iso"))
    histo_Iso[-1].__class__ = ROOT.RooHist
    fit_NonIso.append(inputFile.Get("fit_Stage2_All_vs_" + trigger))
    fit_NonIso[-1].__class__ = ROOT.RooCurve
    fit_Iso.append(inputFile.Get("fit_Stage2_All_vs_" + trigger + "_iso"))
    fit_Iso[-1].__class__ = ROOT.RooCurve
    turnon_NonIso.append(TurnOnPlot.TurnOn(Name="Stage2_NonIso", Histo=histo_NonIso[-1], Fit=fit_NonIso[-1],
                                    MarkerColor=ROOT.kBlue, MarkerStyle=20, LineColor=ROOT.kBlue,LineStyle=1,
                                    Legend="Non isolated"))
    turnon_Iso.append(TurnOnPlot.TurnOn(Name="Stage2_Iso", Histo=histo_Iso[-1], Fit=fit_Iso[-1],
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Isolated"))
    plots.append(TurnOnPlot.TurnOnPlot(TriggerName = trigger + "Non iso - iso"))
    plots[-1].name = "turnOn_NonIso_Iso_" + trigger
    plots[-1].xRange = (10,109.9)
    #plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
    plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
    plots[-1].addTurnOn(turnon_NonIso[-1])
    plots[-1].addTurnOn(turnon_Iso[-1])

canvas = []
for plot in plots:
    canvas.append(plot.plot())

inputFile.Close()

raw_input()
