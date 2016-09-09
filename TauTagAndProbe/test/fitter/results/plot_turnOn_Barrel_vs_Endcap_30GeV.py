import ROOT
import TurnOnPlot_DATA as TurnOnPlot


plots = []
plots.append(TurnOnPlot.TurnOnPlot(TriggerName="L1 Threshold: 30 GeV iso + non-iso"))
plots[-1].name = "turnOn_Barrel_EndCap_30GeV"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)

#EE
plots.append(TurnOnPlot.TurnOnPlot(TriggerName="L1 Threshold: 30 GeV iso"))
plots[-1].name = "turnOn_Barrel_EndCap_30GeV_iso"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)

#open turn on file
inputFile = ROOT.TFile.Open("FittedTurnOn.root")

histo_EB = inputFile.Get("histo_Stage2_Barrel_vs_Pt_30GeV")
histo_EB.__class__ = ROOT.RooHist
histo_EE = inputFile.Get("histo_Stage2_Endcaps_vs_Pt_30GeV")
histo_EE.__class__ = ROOT.RooHist

fit_EB   = inputFile.Get("fit_Stage2_Barrel_vs_Pt_30GeV")
fit_EB.__class__ = ROOT.RooCurve
fit_EE   = inputFile.Get("fit_Stage2_Endcaps_vs_Pt_30GeV")
fit_EE.__class__ = ROOT.RooCurve

turnon_EB = TurnOnPlot.TurnOn(Name="Stage2_EB_noIso", Histo=histo_EB, Fit=fit_EB,
                                    MarkerColor=ROOT.kBlack, MarkerStyle=20, LineColor=ROOT.kBlack,LineStyle=1,
                                    Legend="Barrel")

turnon_EE = TurnOnPlot.TurnOn(Name="Stage2_EE_noIso", Histo=histo_EE, Fit=fit_EE,
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Endcaps")


plots[0].addTurnOn(turnon_EB)
plots[0].addTurnOn(turnon_EE)


histo_EB = inputFile.Get("histo_Stage2_Barrel_vs_Pt_30GeV_iso")
histo_EB.__class__ = ROOT.RooHist
histo_EE = inputFile.Get("histo_Stage2_Endcaps_vs_Pt_30GeV_iso")
histo_EE.__class__ = ROOT.RooHist

fit_EB   = inputFile.Get("fit_Stage2_Barrel_vs_Pt_30GeV_iso")
fit_EB.__class__ = ROOT.RooCurve
fit_EE   = inputFile.Get("fit_Stage2_Endcaps_vs_Pt_30GeV_iso")
fit_EE.__class__ = ROOT.RooCurve

turnon_EB = TurnOnPlot.TurnOn(Name="Stage2_EB_Iso", Histo=histo_EB, Fit=fit_EB,
                                    MarkerColor=ROOT.kBlack, MarkerStyle=20, LineColor=ROOT.kBlack,LineStyle=1,
                                    Legend="Barrel")

turnon_EE = TurnOnPlot.TurnOn(Name="Stage2_EE_Iso", Histo=histo_EE, Fit=fit_EE,
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Endcaps")


plots[1].addTurnOn(turnon_EB)
plots[1].addTurnOn(turnon_EE)

canvas = []
for plot in plots:
    canvas.append(plot.plot())


raw_input()
