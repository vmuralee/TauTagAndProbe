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
