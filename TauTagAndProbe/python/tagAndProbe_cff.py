import FWCore.ParameterSet.Config as cms

# filter HLT paths for T&P
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt
hltFilter = hlt.hltHighLevel.clone(
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = ['HLT_Mu20_v*'],
    andOr = cms.bool(True), # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
    throw = cms.bool(True) #if True: throws exception if a trigger path is invalid  
)

goodMuons = cms.EDFilter("PATMuonRefSelector",
        src = cms.InputTag("slimmedMuons"),
        cut = cms.string(
                'pt > 10 && abs(eta) < 2.5 ' # && isGlobalMuon && isTrackerMuon '
               # ' && innerTrack.hitPattern.numberOfValidTrackerHits > 9 & innerTrack.hitPattern.numberOfValidPixelHits > 0'
               # ' && abs(dB) < 0.2 && globalTrack.normalizedChi2 < 10'
               # ' && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatches > 1'
        ),
        filter = cms.bool(True)
)

goodTaus = cms.EDFilter("PATTauRefSelector",
        src = cms.InputTag("slimmedTaus"),
        cut = cms.string(
                'pt > 10 && abs(eta) < 2.5 ' # && isGlobalMuon && isTrackerMuon '
               # ' && innerTrack.hitPattern.numberOfValidTrackerHits > 9 & innerTrack.hitPattern.numberOfValidPixelHits > 0'
               # ' && abs(dB) < 0.2 && globalTrack.normalizedChi2 < 10'
               # ' && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatches > 1'
        ),
        filter = cms.bool(False)
)

TagAndProbe = cms.EDFilter("TauTagAndProbeFilter",
        taus  = cms.InputTag("goodTaus"),
        muons = cms.InputTag("goodMuons"),
        met   = cms.InputTag("slimmedMETs")
)

Ntuplizer = cms.EDAnalyzer("Ntuplizer",
    treeName = cms.string("testtree"),
    muons = cms.InputTag("TagAndProbe")
)

TAndPseq = cms.Sequence(
    # hltFilter +
    goodMuons +
    goodTaus +
    TagAndProbe +
    Ntuplizer
)
