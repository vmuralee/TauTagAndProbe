import FWCore.ParameterSet.Config as cms
process = cms.Process("TagAndProbe")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff") 

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/Run2016B/SingleMuon/MINIAOD/PromptReco-v2/000/273/150/00000/34A57FB8-D819-E611-B0A4-02163E0144EE.root',
    )
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# import TauTagAndProbe.TauTagAndProbe.tagAndProbe_cff as TAndP
process.load('TauTagAndProbe.TauTagAndProbe.tagAndProbe_cff')
process.p = cms.Path(
    process.TAndPseq
)

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1
