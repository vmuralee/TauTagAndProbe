#ifndef ZeroBias_H
#define ZeroBias_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TNtuple.h>
#include <TString.h>
#include <bitset>


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"


#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"



//Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64


/*
  ██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
  ██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
  ██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class ZeroBias : public edm::EDAnalyzer {
public:
  /// Constructor
  explicit ZeroBias(const edm::ParameterSet&);
  /// Destructor
  virtual ~ZeroBias();

private:
  //----edm control---
  virtual void beginJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  void Initialize();
  bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);
  Long64_t FindTriggerBit(const vector<string> foundPaths, const vector<int> indexOfPaths, const edm::Handle<edm::TriggerResults>& triggerResults);

  TTree *_tree;
  TTree *_triggerNamesTree;
  std::string _treeName;
  // -------------------------------------
  // variables to be filled in output tree
  ULong64_t       _indexevents;
  Int_t           _runNumber;
  Int_t           _lumi;
  unsigned long _EventTriggerBits;

  std::vector<int> _l1tQual;
  std::vector<float> _l1tPt;
  std::vector<float> _l1tEta;
  std::vector<float> _l1tPhi;
  std::vector<int> _l1tIso;
  std::vector<int> _l1tEmuQual;
  std::vector<float> _l1tEmuPt;
  std::vector<float> _l1tEmuEta;
  std::vector<float> _l1tEmuPhi;
  std::vector<int> _l1tEmuIso;
  std::vector<int> _l1tEmuNTT;
  std::vector<int> _l1tEmuHasEM;
  std::vector<int> _l1tEmuIsMerged;
  std::vector<int> _l1tEmuTowerIEta;
  std::vector<int> _l1tEmuTowerIPhi;
  std::vector<int> _l1tEmuRawEt;
  std::vector<int> _l1tEmuIsoEt;
        
  std::vector<int> _l1tQualJet;
  std::vector<float> _l1tPtJet;
  std::vector<float> _l1tEtaJet;
  std::vector<float> _l1tPhiJet;
  std::vector<int> _l1tIsoJet;
  std::vector<int> _l1tTowerIEtaJet;
  std::vector<int> _l1tTowerIPhiJet;
  std::vector<int> _l1tRawEtJet;  
        
  std::vector<int> _l1tEmuQualJet;
  std::vector<float> _l1tEmuPtJet;
  std::vector<float> _l1tEmuEtaJet;
  std::vector<float> _l1tEmuPhiJet;
  std::vector<int> _l1tEmuIsoJet;
  std::vector<int> _l1tEmuTowerIEtaJet;
  std::vector<int> _l1tEmuTowerIPhiJet;
  std::vector<int> _l1tEmuRawEtJet; 

  std::vector<float> _hltTauPt;
  std::vector<float> _hltTauEta;
  std::vector<float> _hltTauPhi;
  std::vector<int> _hltTauTriggerBits;

  std::vector<float> _hltMuPt;
  std::vector<float> _hltMuEta;
  std::vector<float> _hltMuPhi;
  std::vector<int> _hltMuTriggerBits;

  std::vector<float> _hltElePt;
  std::vector<float> _hltEleEta;
  std::vector<float> _hltElePhi;
  std::vector<int> _hltEleTriggerBits;
  
  int _hlt_L2CaloJets_L1TauSeeded_N;
  std::vector<float> _hlt_L2CaloJets_L1TauSeeded_Pt;
  std::vector<float> _hlt_L2CaloJets_L1TauSeeded_Eta;
  std::vector<float> _hlt_L2CaloJets_L1TauSeeded_Phi;

  int _hlt_L2CaloJets_ForIsoPix_N;
  std::vector<float> _hlt_L2CaloJets_ForIsoPix_Pt;
  std::vector<float> _hlt_L2CaloJets_ForIsoPix_Eta;
  std::vector<float> _hlt_L2CaloJets_ForIsoPix_Phi;
  std::vector<float> _hlt_L2CaloJets_ForIsoPix_Iso;

  int _hlt_L2CaloJets_IsoPix_N;
  std::vector<float> _hlt_L2CaloJets_IsoPix_Pt;
  std::vector<float> _hlt_L2CaloJets_IsoPix_Eta;
  std::vector<float> _hlt_L2CaloJets_IsoPix_Phi;


  edm::EDGetTokenT<l1t::TauBxCollection> _L1TauTag  ;
  edm::EDGetTokenT<l1t::TauBxCollection> _L1EmuTauTag  ;
  edm::EDGetTokenT<BXVector<l1t::Jet> > _l1tJetTag;
  edm::EDGetTokenT<BXVector<l1t::Jet> > _l1tEmuJetTag;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
  edm::EDGetTokenT<edm::TriggerResults> _triggerBits;

  edm::EDGetTokenT<reco::CaloJetCollection> _hltL2CaloJet_L1TauSeeded_Tag;
  edm::EDGetTokenT<reco::CaloJetCollection> _hltL2CaloJet_ForIsoPix_Tag;
  edm::EDGetTokenT<reco::JetTagCollection> _hltL2CaloJet_ForIsoPix_IsoTag;
  edm::EDGetTokenT<reco::CaloJetCollection> _hltL2CaloJet_IsoPix_Tag;

  //!Contains the parameters
  tVParameterSet _parameters;

  edm::InputTag _processName;
  //! Maximum
  std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _EventTriggerBitSet;
  HLTConfigProvider _hltConfig;

  vector<string> _triggerlist;
  vector<int> _indexOfPath;
  vector<string> _foundPaths;

};

/*
  ██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
  ██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
  ██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
  ██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
  ██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
ZeroBias::ZeroBias(const edm::ParameterSet& iConfig) :
  _L1TauTag       (consumes<l1t::TauBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1Tau"))),
  _L1EmuTauTag    (consumes<l1t::TauBxCollection>                   (iConfig.getParameter<edm::InputTag>("L1EmuTau"))),
  _l1tJetTag      (consumes<BXVector<l1t::Jet> >                     (iConfig.getParameter<edm::InputTag>("l1tJetCollection"))),
  _l1tEmuJetTag   (consumes<BXVector<l1t::Jet> >                     (iConfig.getParameter<edm::InputTag>("l1tEmuJetCollection"))),
  _triggerObjects (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
  _triggerBits    (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))),
  _hltL2CaloJet_L1TauSeeded_Tag(consumes<reco::CaloJetCollection>   (iConfig.getParameter<edm::InputTag>("L2CaloJet_L1TauSeeded_Collection"))), 
  _hltL2CaloJet_ForIsoPix_Tag(consumes<reco::CaloJetCollection>     (iConfig.getParameter<edm::InputTag>("L2CaloJet_ForIsoPix_Collection"))),
  _hltL2CaloJet_ForIsoPix_IsoTag(consumes<reco::JetTagCollection>   (iConfig.getParameter<edm::InputTag>("L2CaloJet_ForIsoPix_IsoCollection"))),
  _hltL2CaloJet_IsoPix_Tag(consumes<reco::CaloJetCollection>   (iConfig.getParameter<edm::InputTag>("L2CaloJet_IsoPix_Collection"))) 
{
  this -> _treeName = iConfig.getParameter<std::string>("treeName");
  this -> _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");
    
  TString triggerName;
  edm::Service<TFileService> fs;
  this -> _triggerNamesTree = fs -> make<TTree>("triggerNames", "triggerNames");
  this -> _triggerNamesTree -> Branch("triggerNames",&triggerName);
    
  //Building the trigger arrays
  const std::vector<edm::ParameterSet>& HLTList = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerList");
  for (const edm::ParameterSet& parameterSet : HLTList) {
    tParameterSet pSet;
    pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
    triggerName = pSet.hltPath;
    pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
    pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
    pSet.leg1 = parameterSet.getParameter<int>("leg1");
    pSet.leg2 = parameterSet.getParameter<int>("leg2");
    
    _triggerlist.push_back(pSet.hltPath);
    this -> _parameters.push_back(pSet);
    this -> _triggerNamesTree -> Fill();
  }
  

  this -> Initialize();
  return;
}

ZeroBias::~ZeroBias()
{}

void ZeroBias::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{

  Bool_t changedConfig = false;
  
  if(!this -> _hltConfig.init(iRun, iSetup, this -> _processName.process(), changedConfig)){
    edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
    return;
  }


    const edm::TriggerNames::Strings& triggerNames = this -> _hltConfig.triggerNames();
    std::cout << " ===== LOOKING FOR THE PATH INDEXES =====" << std::endl;
    for (tParameterSet& parameter : this -> _parameters){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
	  std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }


    if(changedConfig || _foundPaths.size()==0){
      //cout<<"The present menu is "<<hltConfig.tableName()<<endl;
      _indexOfPath.clear();
      _foundPaths.clear();
    //for(size_t i=0; i<triggerPaths.size(); i++){
    // bool foundThisPath = false;
      for(size_t j=0; j<_hltConfig.triggerNames().size(); j++){
	string pathName = _hltConfig.triggerNames()[j];
	//TString tempo= hltConfig_.triggerNames()[j];
	//printf("%s\n",tempo.Data());
	//if(pathName==triggerPaths[i]){
	//foundThisPath = true;
	_indexOfPath.push_back(j);
	_foundPaths.push_back(pathName);
	
	cout << j << " - TTT: " << pathName << endl;
	//	  edm::LogInfo("AnalyzeRates")<<"Added path "<<pathName<<" to foundPaths";
      } 
    }


}

void ZeroBias::Initialize() {
  this -> _indexevents = 0;
  this -> _runNumber = 0;
  this -> _lumi = 0;

  this -> _l1tPt .clear();
  this -> _l1tEta .clear();
  this -> _l1tPhi .clear();
  this -> _l1tQual .clear();
  this -> _l1tIso .clear();
  this -> _l1tEmuPt .clear();
  this -> _l1tEmuEta .clear();
  this -> _l1tEmuPhi .clear();
  this -> _l1tEmuQual .clear();
  this -> _l1tEmuIso .clear();
  this -> _l1tEmuNTT .clear();
  this -> _l1tEmuHasEM .clear();
  this -> _l1tEmuIsMerged .clear();
  this -> _l1tEmuTowerIEta .clear();
  this -> _l1tEmuTowerIPhi .clear();
  this -> _l1tEmuRawEt .clear();
  this -> _l1tEmuIsoEt .clear();

  this -> _l1tPtJet        .clear();
  this -> _l1tEtaJet       .clear();
  this -> _l1tPhiJet       .clear();
  this -> _l1tIsoJet       .clear();
  this -> _l1tQualJet      .clear();
  this -> _l1tTowerIEtaJet .clear();
  this -> _l1tTowerIPhiJet .clear();
  this -> _l1tRawEtJet     .clear();

  this -> _l1tEmuPtJet        .clear();
  this -> _l1tEmuEtaJet       .clear();
  this -> _l1tEmuPhiJet       .clear();
  this -> _l1tEmuIsoJet       .clear();
  this -> _l1tEmuQualJet      .clear();
  this -> _l1tEmuTowerIEtaJet .clear();
  this -> _l1tEmuTowerIPhiJet .clear();
  this -> _l1tEmuRawEtJet     .clear();

  this -> _hltTauPt .clear();
  this -> _hltTauEta .clear();
  this -> _hltTauPhi .clear();
  this -> _hltTauTriggerBits .clear();

  this -> _hltMuPt .clear();
  this -> _hltMuEta .clear();
  this -> _hltMuPhi .clear();
  this -> _hltMuTriggerBits .clear();

  this -> _hltElePt .clear();
  this -> _hltEleEta .clear();
  this -> _hltElePhi .clear();
  this -> _hltEleTriggerBits .clear();

  this -> _hlt_L2CaloJets_L1TauSeeded_N = 0;
  this -> _hlt_L2CaloJets_L1TauSeeded_Pt.clear();
  this -> _hlt_L2CaloJets_L1TauSeeded_Eta.clear();
  this -> _hlt_L2CaloJets_L1TauSeeded_Phi.clear();

  this -> _hlt_L2CaloJets_ForIsoPix_N = 0;
  this -> _hlt_L2CaloJets_ForIsoPix_Pt.clear();
  this -> _hlt_L2CaloJets_ForIsoPix_Eta.clear();
  this -> _hlt_L2CaloJets_ForIsoPix_Phi.clear();
  this -> _hlt_L2CaloJets_ForIsoPix_Iso.clear();

  this -> _hlt_L2CaloJets_IsoPix_N = 0;
  this -> _hlt_L2CaloJets_IsoPix_Pt.clear();
  this -> _hlt_L2CaloJets_IsoPix_Eta.clear();
  this -> _hlt_L2CaloJets_IsoPix_Phi.clear();

}


void ZeroBias::beginJob()
{
  edm::Service<TFileService> fs;
  this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

  //Branches
  this -> _tree -> Branch("EventNumber",  &_indexevents);
  this -> _tree -> Branch("RunNumber",  &_runNumber);
  this -> _tree -> Branch("lumi",  &_lumi);
  this -> _tree -> Branch("EventTriggerBits", &_EventTriggerBits, "EventTriggerBits/L");
  this -> _tree -> Branch("l1tPt",  &_l1tPt);
  this -> _tree -> Branch("l1tEta", &_l1tEta);
  this -> _tree -> Branch("l1tPhi", &_l1tPhi);
  this -> _tree -> Branch("l1tQual", &_l1tQual);
  this -> _tree -> Branch("l1tIso", &_l1tIso);
  this -> _tree -> Branch("l1tEmuPt",  &_l1tEmuPt);
  this -> _tree -> Branch("l1tEmuEta", &_l1tEmuEta);
  this -> _tree -> Branch("l1tEmuPhi", &_l1tEmuPhi);
  this -> _tree -> Branch("l1tEmuQual", &_l1tEmuQual);
  this -> _tree -> Branch("l1tEmuIso", &_l1tEmuIso);
  this -> _tree -> Branch("l1tEmuNTT", &_l1tEmuNTT);
  this -> _tree -> Branch("l1tEmuHasEM", &_l1tEmuHasEM);
  this -> _tree -> Branch("l1tEmuIsMerged", &_l1tEmuIsMerged);
  this -> _tree -> Branch("l1tEmuTowerIEta", &_l1tEmuTowerIEta);
  this -> _tree -> Branch("l1tEmuTowerIPhi", &_l1tEmuTowerIPhi);
  this -> _tree -> Branch("l1tEmuRawEt", &_l1tEmuRawEt);
  this -> _tree -> Branch("l1tEmuIsoEt", &_l1tEmuIsoEt);

  this -> _tree -> Branch("l1tPtJet",  &_l1tPtJet);
  this -> _tree -> Branch("l1tEtaJet", &_l1tEtaJet);
  this -> _tree -> Branch("l1tPhiJet", &_l1tPhiJet);
  this -> _tree -> Branch("l1tQualJet", &_l1tQualJet);
  this -> _tree -> Branch("l1tIsoJet", &_l1tIsoJet);
  this -> _tree -> Branch("l1tTowerIEtaJet", &_l1tTowerIEtaJet);
  this -> _tree -> Branch("l1tTowerIPhiJet", &_l1tTowerIPhiJet);
  this -> _tree -> Branch("l1tRawEtJet", &_l1tRawEtJet);

  this -> _tree -> Branch("l1tEmuPtJet",  &_l1tEmuPtJet);
  this -> _tree -> Branch("l1tEmuEtaJet", &_l1tEmuEtaJet);
  this -> _tree -> Branch("l1tEmuPhiJet", &_l1tEmuPhiJet);
  this -> _tree -> Branch("l1tEmuQualJet", &_l1tEmuQualJet);
  this -> _tree -> Branch("l1tEmuIsoJet", &_l1tEmuIsoJet);
  this -> _tree -> Branch("l1tEmuTowerIEtaJet", &_l1tEmuTowerIEtaJet);
  this -> _tree -> Branch("l1tEmuTowerIPhiJet", &_l1tEmuTowerIPhiJet);
  this -> _tree -> Branch("l1tEmuRawEtJet", &_l1tEmuRawEtJet);

  this -> _tree -> Branch("hltTauPt",  &_hltTauPt);
  this -> _tree -> Branch("hltTauEta", &_hltTauEta);
  this -> _tree -> Branch("hltTauPhi", &_hltTauPhi);
  this -> _tree -> Branch("hltTauTriggerBits", &_hltTauTriggerBits);

  this -> _tree -> Branch("hltMuPt",  &_hltMuPt);
  this -> _tree -> Branch("hltMuEta", &_hltMuEta);
  this -> _tree -> Branch("hltMuPhi", &_hltMuPhi);
  this -> _tree -> Branch("hltMuTriggerBits", &_hltMuTriggerBits);

  this -> _tree -> Branch("hltElePt",  &_hltElePt);
  this -> _tree -> Branch("hltEleEta", &_hltEleEta);
  this -> _tree -> Branch("hltElePhi", &_hltElePhi);
  this -> _tree -> Branch("hltEleTriggerBits", &_hltEleTriggerBits);

  this -> _tree -> Branch("hlt_L2CaloJets_L1TauSeeded_N", &_hlt_L2CaloJets_L1TauSeeded_N, "hlt_L2CaloJets_L1TauSeeded_N/I");
  this -> _tree -> Branch("hlt_L2CaloJets_L1TauSeeded_Pt", &_hlt_L2CaloJets_L1TauSeeded_Pt);
  this -> _tree -> Branch("hlt_L2CaloJets_L1TauSeeded_Eta", &_hlt_L2CaloJets_L1TauSeeded_Eta);
  this -> _tree -> Branch("hlt_L2CaloJets_L1TauSeeded_Phi", &_hlt_L2CaloJets_L1TauSeeded_Phi);

  this -> _tree -> Branch("hlt_L2CaloJets_ForIsoPix_N", &_hlt_L2CaloJets_ForIsoPix_N, "hlt_L2CaloJets_ForIsoPix_N/I");
  this -> _tree -> Branch("hlt_L2CaloJets_ForIsoPix_Pt", &_hlt_L2CaloJets_ForIsoPix_Pt);
  this -> _tree -> Branch("hlt_L2CaloJets_ForIsoPix_Eta", &_hlt_L2CaloJets_ForIsoPix_Eta);
  this -> _tree -> Branch("hlt_L2CaloJets_ForIsoPix_Phi", &_hlt_L2CaloJets_ForIsoPix_Phi);
  this -> _tree -> Branch("hlt_L2CaloJets_ForIsoPix_Iso", &_hlt_L2CaloJets_ForIsoPix_Iso);

  this -> _tree -> Branch("hlt_L2CaloJets_IsoPix_N", &_hlt_L2CaloJets_IsoPix_N, "hlt_L2CaloJets_IsoPix_N/I");
  this -> _tree -> Branch("hlt_L2CaloJets_IsoPix_Pt", &_hlt_L2CaloJets_IsoPix_Pt);
  this -> _tree -> Branch("hlt_L2CaloJets_IsoPix_Eta", &_hlt_L2CaloJets_IsoPix_Eta);
  this -> _tree -> Branch("hlt_L2CaloJets_IsoPix_Phi", &_hlt_L2CaloJets_IsoPix_Phi);

  return;
}


void ZeroBias::endJob()
{
  return;
}


void ZeroBias::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  return;
}


void ZeroBias::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
  this -> Initialize();

  _indexevents = iEvent.id().event();
  _runNumber = iEvent.id().run();
  _lumi = iEvent.luminosityBlock();

  edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
  try {iEvent.getByToken(_L1TauTag, L1TauHandle);}  catch (...) {;}

  if(L1TauHandle.isValid()){
    for (l1t::TauBxCollection::const_iterator bx0TauIt = L1TauHandle->begin(0); bx0TauIt != L1TauHandle->end(0) ; bx0TauIt++)
      {
	const l1t::Tau& l1tTau = *bx0TauIt;
	
	//cout<<"FW Tau, pT = "<<l1tTau.pt()<<", eta = "<<l1tTau.eta()<<", phi = "<<l1tTau.phi()<<endl;
	
	this -> _l1tPt.push_back(l1tTau.pt());
	this -> _l1tEta.push_back(l1tTau.eta());
	this -> _l1tPhi.push_back(l1tTau.phi());
	this -> _l1tIso.push_back(l1tTau.hwIso());
	this -> _l1tQual.push_back(l1tTau.hwQual());
	
      }
  }

  edm::Handle< BXVector<l1t::Tau> >  L1EmuTauHandle;
  try {iEvent.getByToken(_L1EmuTauTag, L1EmuTauHandle);} catch (...) {;}

  if (L1EmuTauHandle.isValid())
    {	
      for (l1t::TauBxCollection::const_iterator bx0EmuTauIt = L1EmuTauHandle->begin(0); bx0EmuTauIt != L1EmuTauHandle->end(0) ; bx0EmuTauIt++)
	{
	  const l1t::Tau& l1tEmuTau = *bx0EmuTauIt;
	    
	  //cout<<"Emul Tau, pT = "<<l1tEmuTau.pt()<<", eta = "<<l1tEmuTau.eta()<<", phi = "<<l1tEmuTau.phi()<<endl;
	    
	  this -> _l1tEmuPt       .push_back(l1tEmuTau.pt());
	  this -> _l1tEmuEta      .push_back(l1tEmuTau.eta());
	  this -> _l1tEmuPhi      .push_back(l1tEmuTau.phi());
	  this -> _l1tEmuIso      .push_back(l1tEmuTau.hwIso());
	  this -> _l1tEmuNTT      .push_back(l1tEmuTau.nTT());
	  this -> _l1tEmuQual     .push_back(l1tEmuTau.hwQual());
	  this -> _l1tEmuHasEM    .push_back(l1tEmuTau.hasEM());
	  this -> _l1tEmuIsMerged .push_back(l1tEmuTau.isMerged());
	  this -> _l1tEmuTowerIEta.push_back(l1tEmuTau.towerIEta());
	  this -> _l1tEmuTowerIPhi.push_back(l1tEmuTau.towerIPhi());
	  this -> _l1tEmuRawEt    .push_back(l1tEmuTau.rawEt());
	  this -> _l1tEmuIsoEt    .push_back(l1tEmuTau.isoEt());

	}
    }

  edm::Handle<BXVector<l1t::Jet>> l1tJetHandle;
  try {iEvent.getByToken(this -> _l1tJetTag, l1tJetHandle);}  catch (...) {;}

  if(l1tJetHandle.isValid()){
    for(BXVector<l1t::Jet>::const_iterator jet = l1tJetHandle -> begin(0); jet != l1tJetHandle -> end(0) ; jet++)
      {
	
	this -> _l1tPtJet        . push_back(jet -> pt());
	this -> _l1tEtaJet       . push_back(jet -> eta());
	this -> _l1tPhiJet       . push_back(jet -> phi());
	this -> _l1tIsoJet       . push_back(jet -> hwIso());
	this -> _l1tQualJet      . push_back(jet -> hwQual());
	this -> _l1tTowerIEtaJet . push_back(jet -> towerIEta());
	this -> _l1tTowerIPhiJet . push_back(jet -> towerIPhi());
	this -> _l1tRawEtJet     . push_back(jet -> rawEt());
      }
  }

  edm::Handle<BXVector<l1t::Jet> > l1tEmuJetHandle;  
  try {iEvent.getByToken(this -> _l1tEmuJetTag, l1tEmuJetHandle);}  catch (...) {;}

  if (l1tEmuJetHandle.isValid()){

    for(BXVector<l1t::Jet>::const_iterator jet = l1tEmuJetHandle -> begin(0); jet != l1tEmuJetHandle -> end(0) ; jet++)
      {
	
	this -> _l1tEmuPtJet        . push_back(jet -> pt());
	this -> _l1tEmuEtaJet       . push_back(jet -> eta());
	this -> _l1tEmuPhiJet       . push_back(jet -> phi());
	this -> _l1tEmuIsoJet       . push_back(jet -> hwIso());
	this -> _l1tEmuQualJet      . push_back(jet -> hwQual());
	this -> _l1tEmuTowerIEtaJet . push_back(jet -> towerIEta());
	this -> _l1tEmuTowerIPhiJet . push_back(jet -> towerIPhi());
	this -> _l1tEmuRawEtJet     . push_back(jet -> rawEt());
      }
    
  }
  

  edm::Handle<edm::TriggerResults> triggerBits;
  iEvent.getByToken(this -> _triggerBits, triggerBits);
  const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
  this ->_EventTriggerBits = this->FindTriggerBit(_foundPaths,_indexOfPath,triggerBits);

  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  try {iEvent.getByToken(this -> _triggerObjects, triggerObjects);}  catch (...) {;}

  if (triggerObjects.isValid()){
  
    for (pat::TriggerObjectStandAlone  obj : *triggerObjects)
      {
	
	obj.unpackPathNames(names);
	const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
	
	bool hasTriggerTauType = obj.hasTriggerObjectType(trigger::TriggerTau);
	bool hasTriggerMuType = obj.hasTriggerObjectType(trigger::TriggerMuon);
	bool hasTriggerEleType = obj.hasTriggerObjectType(trigger::TriggerElectron);

	//Looking for the path
	unsigned int x = 0;
	for (const tParameterSet& parameter : this -> _parameters)
	  {
	    
	    
	    if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
	      {
		
		//cout<<"FOUND EVENT with HLT PATH "<<triggerNames[parameter.hltPathIndex]<<endl;
		
		this -> _EventTriggerBitSet[x] = true;
		
		if(hasTriggerTauType)
		  {
		    //std::cout << "#### FOUND TAU WITH HLT PATH " << x << " ####" << std::endl;
		    this -> _hltTauPt.push_back(obj.pt());
		    this -> _hltTauEta.push_back(obj.eta());
		    this -> _hltTauPhi.push_back(obj.phi());
		    this -> _hltTauTriggerBits.push_back( x );
		  }
		
		if(hasTriggerMuType)
		  {
		    //std::cout << "#### FOUND MUON WITH HLT PATH " << x << " ####" << std::endl;
		    this -> _hltMuPt.push_back(obj.pt());
		    this -> _hltMuEta.push_back(obj.eta());
		    this -> _hltMuPhi.push_back(obj.phi());
		    this -> _hltMuTriggerBits.push_back( x );
		  }
		
		if(hasTriggerEleType)
		  {
		    //std::cout << "#### FOUND ELE WITH HLT PATH " << x << " ####" << std::endl;
		    this -> _hltElePt.push_back(obj.pt());
		    this -> _hltEleEta.push_back(obj.eta());
		    this -> _hltElePhi.push_back(obj.phi());
		    this -> _hltEleTriggerBits.push_back( x );
		  }
		
	      }
	    
	    x++;
	  }
	
      }

  }


  edm::Handle< reco::CaloJetCollection > L2CaloJets_L1TauSeeded_Handle;
  try {iEvent.getByToken(_hltL2CaloJet_L1TauSeeded_Tag, L2CaloJets_L1TauSeeded_Handle);}  catch (...) {;}

  if(L2CaloJets_L1TauSeeded_Handle.isValid()){

    for (reco::CaloJet  jet : *L2CaloJets_L1TauSeeded_Handle){

      _hlt_L2CaloJets_L1TauSeeded_N++;
      _hlt_L2CaloJets_L1TauSeeded_Pt.push_back(jet.pt());
      _hlt_L2CaloJets_L1TauSeeded_Eta.push_back(jet.eta());
      _hlt_L2CaloJets_L1TauSeeded_Phi.push_back(jet.phi());
      
    }

  }


  edm::Handle< reco::CaloJetCollection > L2CaloJets_ForIsoPix_Handle;
  try {iEvent.getByToken(_hltL2CaloJet_ForIsoPix_Tag, L2CaloJets_ForIsoPix_Handle);}  catch (...) {;}

  edm::Handle< reco::JetTagCollection > L2CaloJets_ForIsoPix_IsoHandle;
  try {iEvent.getByToken(_hltL2CaloJet_ForIsoPix_IsoTag, L2CaloJets_ForIsoPix_IsoHandle);}  catch (...) {;}
  

  if(L2CaloJets_ForIsoPix_Handle.isValid() && L2CaloJets_ForIsoPix_IsoHandle.isValid()){

    for (auto const &  jet : *L2CaloJets_ForIsoPix_IsoHandle){
      edm::Ref<reco::CaloJetCollection> jetRef = edm::Ref<reco::CaloJetCollection>(L2CaloJets_ForIsoPix_Handle,jet.first.key());
      _hlt_L2CaloJets_ForIsoPix_N++;
      _hlt_L2CaloJets_ForIsoPix_Pt.push_back(jet.first->pt());
      _hlt_L2CaloJets_ForIsoPix_Eta.push_back(jet.first->eta());
      _hlt_L2CaloJets_ForIsoPix_Phi.push_back(jet.first->phi());
      _hlt_L2CaloJets_ForIsoPix_Iso.push_back(jet.second);
   
    }

  }



  edm::Handle< reco::CaloJetCollection > L2CaloJets_IsoPix_Handle;
  try {iEvent.getByToken(_hltL2CaloJet_IsoPix_Tag, L2CaloJets_IsoPix_Handle);}  catch (...) {;}

  if(L2CaloJets_IsoPix_Handle.isValid()){

    for (reco::CaloJet  jet : *L2CaloJets_IsoPix_Handle){

      _hlt_L2CaloJets_IsoPix_N++;
      _hlt_L2CaloJets_IsoPix_Pt.push_back(jet.pt());
      _hlt_L2CaloJets_IsoPix_Eta.push_back(jet.eta());
      _hlt_L2CaloJets_IsoPix_Phi.push_back(jet.phi());
      
    }

  }


  this -> _tree -> Fill();

}



bool ZeroBias::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

    const std::vector<std::string>& eventLabels = obj.filterLabels();
    for (const std::string& filter : filtersToLookFor)
    {
        //Looking for matching filters
        bool found = false;
        for (const std::string& label : eventLabels)
        {

            if (label == filter)
            {

                //std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;
                found = true;
            }
        }
        if(!found) return false;
    }

    return true;
}



Long64_t ZeroBias::FindTriggerBit(const vector<string> foundPaths, const vector<int> indexOfPaths, const edm::Handle<edm::TriggerResults>& triggerResults){
  
  Long64_t bit =0;
 
  for(int it=0;it<(int)_triggerlist.size();it++){
    for(int j=0;j<(int)foundPaths.size();j++){
      
      string toCheckTrigger  = _triggerlist.at(it) ;
      string elemAllTriggers = foundPaths.at(j) ;
      /*if(triggerResults->accept(indexOfPaths[j]))
	cout<<"Path "<<elemAllTriggers<<endl;*/

      if (elemAllTriggers.find(toCheckTrigger) != std::string::npos) // equivalent to wildcard at the end or beginning of triggername 
      {
	if(triggerResults->accept(indexOfPaths[j]))bit |= long(1) <<it;
	break;
      }
    }
  }
  //printf("bit: %d\n",bit);

  return bit;
}



#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(ZeroBias);

#endif //ZeroBias_H
