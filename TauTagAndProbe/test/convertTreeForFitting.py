from ROOT import *
import numpy as n

## FIXME: copy triggerNames structure for storing HLT info as well

# the hadd of all the output ntuples
fname = 'allICHEPIsoOrder.root'
pt = [25, 35, 45]

#######################################################
fIn = TFile.Open(fname)
tIn = fIn.Get('Ntuplizer/TagAndProbe')
outname = fname.replace ('.root', '_forFit.root')
fOut = TFile (outname, 'recreate')
tOut = tIn.CloneTree(0)

briso   = [n.zeros(1, dtype=int) for x in range (0, len(pt))]
brnoiso = [n.zeros(1, dtype=int) for x in range (0, len(pt))]

for i in range (0, len(pt)):
    name = ("hasL1_" + str(pt[i]))
    tOut.Branch(name, brnoiso[i], name+"/I")
    name += "_iso"
    tOut.Branch(name, briso[i], name+"/I")

nentries = tIn.GetEntries()
for ev in range (0, nentries):
    tIn.GetEntry(ev)
    if (ev%10000 == 0) : print ev, "/", nentries
    
    for i in range (0, len(pt)):
        briso[i][0] = 0
        brnoiso[i][0] = 0

    L1iso = True if tIn.l1tIso == 1 else False
    L1pt = tIn.l1tPt
    for i in range(0, len(pt)):
        # print L1pt, pt[i]
        if L1pt > pt[i]:
            brnoiso[i][0] = 1
            # print "SUCCESS!! ", brnoiso[i]
            if L1iso:
                briso[i][0] = 1
    
    tOut.Fill()

tOut.Write()
fOut.Close()