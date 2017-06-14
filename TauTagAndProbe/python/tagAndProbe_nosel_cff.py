import FWCore.ParameterSet.Config as cms

print "Running on data"

# filter HLT paths for T&P
import HLTrigger.HLTfilters.hltHighLevel_cfi as hlt


HLTLIST = cms.VPSet(
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1_v1 "),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24LooseChargedIsoPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackLooseChargedIsoAgainstMuon", "hltOverlapFilterIsoMu24LooseChargedIsoPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1_v1"),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24LooseChargedIsoTightOOSCPhotonsPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackLooseChargedIsoTightOOSCPhotonsAgainstMuon", "hltOverlapFilterIsoMu24LooseChargedIsoTightOOSCPhotonsPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1_v1 "),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24MediumChargedIsoPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackMediumChargedIsoAgainstMuon", "hltOverlapFilterIsoMu24MediumChargedIsoPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1_v1"),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24MediumChargedIsoTightOOSCPhotonsPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackMediumChargedIsoTightOOSCPhotonsAgainstMuon", "hltOverlapFilterIsoMu24MediumChargedIsoTightOOSCPhotonsPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1_v1 "),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24TightChargedIsoPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackTightChargedIsoAgainstMuon", "hltOverlapFilterIsoMu24TightChargedIsoPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
    cms.PSet (
        HLT = cms.string("HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1_v1"),
        path1 = cms.vstring ("hltL3crIsoL1sSingleMu22erL1f0L2f10QL3f24QL3trkIsoFiltered0p07", "hltOverlapFilterIsoMu24TightChargedIsoTightOOSCPhotonsPFTau20"),
        path2 = cms.vstring ("hltPFTau20TrackTightChargedIsoTightOOSCPhotonsAgainstMuon", "hltOverlapFilterIsoMu24TightChargedIsoTightOOSCPhotonsPFTau20"),
        leg1 = cms.int32(13),
        leg2 = cms.int32(15)
    ),
)



hltFilter = hlt.hltHighLevel.clone(
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = ['HLT_IsoMu24_eta2p1_v*'],
    andOr = cms.bool(True), # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
    throw = cms.bool(True) #if True: throws exception if a trigger path is invalid
)



## good taus - apply analysis selection
goodTaus = cms.EDFilter("PATTauRefSelector",
        src = cms.InputTag("slimmedTaus"),
        cut = cms.string(
        #        'pt > 5 && abs(eta) < 2.1 ' #kinematics
                'pt > 20 && abs(eta) < 2.1 ' #kinematics
                '&& abs(charge) > 0 && abs(charge) < 2 ' #sometimes 2 prongs have charge != 1
                '&& tauID("decayModeFinding") > 0.5 ' # tau ID
                '&& tauID("byLooseIsolationMVArun2v1DBoldDMwLT") > 0.5 '
                '&& tauID("againstMuonTight3") > 0.5 ' # anti Muon tight
                '&& tauID("againstElectronVLooseMVA6") > 0.5 ' # anti-Ele loose
        ),
        filter = cms.bool(True)
)



Ntuplizer = cms.EDAnalyzer("Ntuplizer",
    treeName = cms.string("TagAndProbe"),
    muons = cms.InputTag("TagAndProbe"),
    taus = cms.InputTag("TagAndProbe"),
    triggerList = HLTLIST,
    triggerSet = cms.InputTag("selectedPatTrigger"),
    triggerResultsLabel = cms.InputTag("TriggerResults", "", "HLT"),
    L1Tau = cms.InputTag("caloStage2Digis", "Tau", "RECO"),
    #L1EmuTau = cms.InputTag("simCaloStage2Digis"),
    L1EmuTau = cms.InputTag("simCaloStage2Digis", "MP"),
    Vertexes = cms.InputTag("offlineSlimmedPrimaryVertices")
)

TAndPseq = cms.Sequence(
    hltFilter        +
    goodTaus
)

NtupleSeq = cms.Sequence(
    Ntuplizer
)
