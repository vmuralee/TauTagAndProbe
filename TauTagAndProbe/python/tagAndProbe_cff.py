import FWCore.ParameterSet.Config as cms

goodMuons = cms.EDFilter("PATMuonRefSelector",
        src = cms.InputTag("slimmedMuons"),
        cut = cms.string(
                'pt > 10 && abs(eta) < 2.5 && isGlobalMuon && isTrackerMuon '
                ' && innerTrack.hitPattern.numberOfValidTrackerHits > 9 & innerTrack.hitPattern.numberOfValidPixelHits > 0'
                ' && abs(dB) < 0.2 && globalTrack.normalizedChi2 < 10'
                ' && globalTrack.hitPattern.numberOfValidMuonHits > 0 && numberOfMatches > 1'
        ),
        filter = cms.bool(True)
)

TagAndProbe = cms.EDFilter("TauTagAndProbeFilter",
        taus  = cms.InputTag("slimmedTaus"),
        muons = cms.InputTag("goodMuons")
)

Ntuplizer = cms.EDAnalyzer("Ntuplizer")

TAndPseq = cms.Sequence(
    goodMuons + 
    TagAndProbe +
    Ntuplizer
)
