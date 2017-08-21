# TauTagAndProbe
Set of tools to evaluate tau trigger performance on T&amp;P

### Install instructions
```
cmsrel CMSSW_9_2_5_patch2
cd CMSSW_9_2_5_patch2/src
cmsenv
git clone https://github.com/tstreble/TauTagAndProbe
cd TauTagAndProbe
git checkout master_HLT
cd ..
scram b -j4
```

Run test.py to produce ntuples including offline taus + various online quantities


### Ntuples content
The Ntuple produced that way contain basic tau offline quantities (kinematics, DM, various discriminators) + bits corresponding to various HLT triggers (tauTriggerBits variable) + L1-HLT specific variables (for expert user)
The events stored pass basic mu+tauh T&P selections (OS requirement not applied for filter! isOS variable stored in Ntuple).
The tree triggerNames has the name of all the HLT paths included in the tauTriggerBits variable.
This can be checked for instance with
```
triggerNames->Scan("triggerNames","","colsize=100")
*******************************************************************************************************************
*    Row   *                                                                                         triggerNames *
*******************************************************************************************************************
*        0 *                                                 HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1_v *
*        1 *                                         HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1_v *
*        2 *                                                HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1_v *
*        3 *                                        HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1_v *
*        4 *                                                 HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1_v *
*        5 *                                         HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1_v *
...
```
The Row of the path correspond to the bit number in the tauTriggerBits variable.
In the example presented here, the decision of the MediumChargedIsoPFTau20 leg can be checked for instance by requiring (tauTriggerBits>>2)&1 (matching with tag muon + offline tau of 0.5 included).


### Plotting
Any basic check can be performed using those Ntuples (efficiency vs pT, eta-phi...) using custom code developed by the user.
A more fancy package is available to produce turn-on plots with CB fits.
For this, the Ntuples must first be converted using the script test/convertTreeForFitting.py (blame RooFit for not being able to deal with custom boolean cuts).
The package for plotting is available in test/fitter/ (to be compiled with make).
The CB fit can be run using a as an example test/fitter/hlt_turnOn_fitter.par (includes example for L1 and HLT turnons w/ subtraction of SS mu+tauh events to take into account contamination from fake taus using bkgSubW weight).
To be launched with
```
./fit.exe run/hlt_turnOn_fitter.par
```
The "Michelangelo" turn-on plot can then be produced adapting the script test/fitter/results/plot_turnOn_Data_vs_MC.py
```
./fit.exe run/hlt_turnOn_fitter.par
```
