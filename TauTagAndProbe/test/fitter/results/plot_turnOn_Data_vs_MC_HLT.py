import ROOT
import TurnOnPlot_DATA as TurnOnPlot


plots = []
plots.append(TurnOnPlot.TurnOnPlot(TriggerName="HLT MediumIsoPFTau32 Data - MC"))
plots[-1].name = "turnOn_Data_MC_MediumIsoPFTau32"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)

plots.append(TurnOnPlot.TurnOnPlot(TriggerName="HLT MediumIsoPFTau20 Data - MC"))
plots[-1].name = "turnOn_Data_MC_LooseIsoPFTau20"
plots[-1].xRange = (10,109.9)
#plots[-1].legendPosition = (0.6,0.2,0.9,0.4)
plots[-1].legendPosition = (0.6,0.2,0.9,0.4)


#open turn on file
inputFile_Data = ROOT.TFile.Open("FittedTurnOn_Final_Data.root")
inputFile_MC = ROOT.TFile.Open("FittedTurnOn_Final_MC.root")

histo_Data_PFTau32 = inputFile_Data.Get("histo_Stage2_Barrel_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
histo_Data_PFTau32.__class__ = ROOT.RooHist
histo_MC_PFTau32 = inputFile_MC.Get("histo_Stage2_Endcaps_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
histo_MC_PFTau32.__class__ = ROOT.RooHist

fit_Data_PFTau32 = inputFile_Data.Get("fit_Stage2_Barrel_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
fit_Data_PFTau32.__class__ = ROOT.RooCurve
fit_MC_PFTau32 = inputFile_MC.Get("fit_Stage2_Endcaps_vs_HLT_IsoMu19_eta2p1_MediumIsoPFTau32_Trk1_eta2p1_Reg_v")
fit_MC_PFTau32.__class__ = ROOT.RooCurve

turnon_Data_PFTau32 = TurnOnPlot.TurnOn(Name="Stage2_Data", Histo=histo_Data_PFTau32, Fit=fit_Data_PFTau32,
                                    MarkerColor=ROOT.kBlue, MarkerStyle=20, LineColor=ROOT.kBlue,LineStyle=1,
                                    Legend="Data")

turnon_MC_PFTau32 = TurnOnPlot.TurnOn(Name="Stage2_MC", Histo=histo_MC_PFTau32, Fit=fit_MC_PFTau32,
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Simulation")

plots[0].addTurnOn(turnon_Data_PFTau32)
plots[0].addTurnOn(turnon_MC_PFTau32)

histo_Data_PFTau20 = inputFile_Data.Get("histo_Stage2_Barrel_vs_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v")
histo_Data_PFTau20.__class__ = ROOT.RooHist
histo_MC_PFTau20 = inputFile_MC.Get("histo_Stage2_Endcaps_vs_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v")
histo_MC_PFTau20.__class__ = ROOT.RooHist

fit_Data_PFTau20 = inputFile_Data.Get("fit_Stage2_Barrel_vs_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v")
fit_Data_PFTau20.__class__ = ROOT.RooCurve
fit_MC_PFTau20 = inputFile_MC.Get("fit_Stage2_Endcaps_vs_HLT_IsoMu21_eta2p1_LooseIsoPFTau20_SingleL1_v")
fit_MC_PFTau20.__class__ = ROOT.RooCurve

turnon_Data_PFTau20 = TurnOnPlot.TurnOn(Name="Stage2_Data", Histo=histo_Data_PFTau20, Fit=fit_Data_PFTau20,
                                    MarkerColor=ROOT.kBlue, MarkerStyle=20, LineColor=ROOT.kBlue,LineStyle=1,
                                    Legend="Data")

turnon_MC_PFTau20 = TurnOnPlot.TurnOn(Name="Stage2_MC", Histo=histo_MC_PFTau20, Fit=fit_MC_PFTau20,
                                   MarkerColor=ROOT.kRed, MarkerStyle=20, LineColor=ROOT.kRed,LineStyle=1,
                                   Legend="Simulation")

plots[1].addTurnOn(turnon_Data_PFTau20)
plots[1].addTurnOn(turnon_MC_PFTau20)


canvas = []
for plot in plots:
    canvas.append(plot.plot())


inputFile_Data.Close()
inputFile_MC.Close()

raw_input()
