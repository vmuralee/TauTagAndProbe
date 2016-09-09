import ROOT
import TurnOnPlot_DATA as TurnOnPlot


plots = []
plots.append(TurnOnPlot.TurnOnPlot(TriggerName="HLT MediumIsoPFTau32 Barrel - Endcap"))
plots[-1].name = "turnOn_Barrel_Endcap_MediumIsoPFTau32"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)

plots.append(TurnOnPlot.TurnOnPlot(TriggerName="HLT MediumIsoPFTau32"))
plots[-1].name = "turnOn_MediumIsoPFTau32"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)

#open turn on file
inputFile = ROOT.TFile.Open("FittedTurnOn.root")

histo_Barrel = inputFile.Get("histo_Stage2_Barrel_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
histo_Barrel.__class__ = ROOT.RooHist
histo_Endcaps = inputFile.Get("histo_Stage2_Endcaps_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
histo_Endcaps.__class__ = ROOT.RooHist
histo_All = inputFile.Get("histo_Stage2_All_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
histo_All.__class__ = ROOT.RooHist

fit_Barrel = inputFile.Get("fit_Stage2_Barrel_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
fit_Barrel.__class__ = ROOT.RooCurve
fit_Endcaps = inputFile.Get("fit_Stage2_Endcaps_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
fit_Endcaps.__class__ = ROOT.RooCurve
fit_All = inputFile.Get("fit_Stage2_All_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
fit_All.__class__ = ROOT.RooCurve

turnon_All = TurnOnPlot.TurnOn(Name="Stage2_All", Histo=histo_All, Fit=fit_All,
                                    MarkerColor=ROOT.kBlack, MarkerStyle=20, LineColor=ROOT.kBlack,LineStyle=1,
                                    Legend="Inclusive")

turnon_Barrel = TurnOnPlot.TurnOn(Name="Stage2_Barrel", Histo=histo_Barrel, Fit=fit_Barrel,
                                    MarkerColor=ROOT.kBlue, MarkerStyle=20, LineColor=ROOT.kBlue,LineStyle=1,
                                    Legend="Barrel")

turnon_Endcaps = TurnOnPlot.TurnOn(Name="Stage2_Endcaps", Histo=histo_Endcaps, Fit=fit_Endcaps,
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Endcaps")

plots[1].addTurnOn(turnon_All)
plots[0].addTurnOn(turnon_Barrel)
plots[0].addTurnOn(turnon_Endcaps)


canvas = []
for plot in plots:
    canvas.append(plot.plot())


inputFile.Close()

raw_input()
