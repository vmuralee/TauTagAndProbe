import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
process = cms.Process("TagAndProbe")

isMC = False

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

#### handling of cms line options for tier3 submission
#### the following are dummy defaults, so that one can normally use the config changing file list by hand etc.

options = VarParsing.VarParsing ('analysis')
options.register ('skipEvents',
                  -1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Number of events to skip")
options.register ('JSONfile',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "JSON file (empty for no JSON)")
options.outputFile = 'NTuple_SingleMu296174.root'
options.inputFiles = []
options.maxEvents  = -999
options.parseArguments()

if not isMC:
    from Configuration.AlCa.autoCond import autoCond
    process.GlobalTag.globaltag = '92X_dataRun2_HLT_v3'
    process.load('TauTagAndProbe.TauTagAndProbe.tagAndProbe_nosel_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/172/00000/66D29210-674C-E711-AFD2-02163E01A270.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/4C85F093-654C-E711-99AA-02163E01A203.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/92ED5B44-6E4C-E711-A6FF-02163E011AC8.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/A04BCF64-734C-E711-9DD7-02163E019D14.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/A4DDC7F2-794C-E711-9AE1-02163E01A20B.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/BE9B75D5-614C-E711-BD09-02163E01A4D3.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/C426AE34-894C-E711-9319-02163E019B6A.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/E4A6AF0C-7E4C-E711-903C-02163E0143F9.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/173/00000/F4E4645B-6D4C-E711-87D1-02163E019DCC.root',
            '/store/data/Run2017A/SingleMuon/MINIAOD/PromptReco-v2/000/296/174/00000/F89D7E25-7C4C-E711-B14D-02163E01A270.root'
        ),
    )



else:
    process.GlobalTag.globaltag = '80X_mcRun2_asymptotic_2016_miniAODv2' #MC 25 ns miniAODv2
    # process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'
    process.load('TauTagAndProbe.TauTagAndProbe.MCanalysis_cff')
    process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring(            
            '/store/mc/RunIISpring16MiniAODv2/GluGluHToTauTau_M125_13TeV_powheg_pythia8/MINIAODSIM/FlatPU20to70HcalNZSRAW_withHLT_80X_mcRun2_asymptotic_v14-v1/50000/B0D22F36-9567-E611-A5FB-0CC47A4DEE76.root'
        )
    )

if options.JSONfile:
    print "Using JSON: " , options.JSONfile
    process.source.lumisToProcess = LumiList.LumiList(filename = options.JSONfile).getVLuminosityBlockRange()

if options.inputFiles:
    process.source.fileNames = cms.untracked.vstring(options.inputFiles)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

if options.maxEvents >= -1:
    process.maxEvents.input = cms.untracked.int32(options.maxEvents)
if options.skipEvents >= 0:
    process.source.skipEvents = cms.untracked.uint32(options.skipEvents)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.p = cms.Path(
    process.TAndPseq +
    process.NtupleSeq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
