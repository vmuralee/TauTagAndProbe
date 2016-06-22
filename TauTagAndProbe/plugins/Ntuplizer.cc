#ifndef NTUPLIZER_H
#define NTUPLIZER_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TNtuple.h>


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
#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"


/*
██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class Ntuplizer : public edm::EDAnalyzer {
    public:
        /// Constructor
        explicit Ntuplizer(const edm::ParameterSet&);
        /// Destructor
        virtual ~Ntuplizer();

    private:
        //----edm control---
        virtual void beginJob() ;
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        bool isTau(const std::vector<std::string>& eventLabels, const std::vector<std::string>& filtersToLookFor);

        TTree *_tree;
        std::string _treeName;
        // -------------------------------------
        // variables to be filled in output tree
        ULong64_t       _indexevents;
        Int_t           _runNumber;
        Int_t           _lumi;

        edm::EDGetTokenT<pat::MuonRefVector>  _muonsTag;
        edm::EDGetTokenT<pat::TauRefVector>   _tauTag;
        edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
        edm::EDGetTokenT<edm::TriggerResults> _triggerBits;

        //!Contains the parameters
        tVParameterSet _parameters;

        edm::InputTag _processName;

        //std::vector<Float_t> _tauPtVector;
        //std::vector<uint> _tauTriggerBitsVector;

        // std::vector<Float_t> _tauPtVector;
        // std::vector<uint> _tauTriggeredVector;
        float _tauPt;
        int   _tauTriggered;


        HLTConfigProvider _hltConfig;


};

/*
██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
Ntuplizer::Ntuplizer(const edm::ParameterSet& iConfig) :
_muonsTag       (consumes<pat::MuonRefVector>                     (iConfig.getParameter<edm::InputTag>("muons"))),
_tauTag         (consumes<pat::TauRefVector>                      (iConfig.getParameter<edm::InputTag>("taus"))),
_triggerObjects (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
_triggerBits    (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel")))
{
    this -> _treeName = iConfig.getParameter<std::string>("treeName");
    this -> _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTList = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerList");
    for (const edm::ParameterSet& parameterSet : HLTList) {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        this -> _parameters.push_back(pSet);
    }

    this -> Initialize();
    return;
}

Ntuplizer::~Ntuplizer()
{}

void Ntuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    Bool_t changedConfig = false;

    if(!this -> _hltConfig.init(iRun, iSetup, this -> _processName.process(), changedConfig)){
        edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
        return;
    }

//    this -> _doubleMediumIsoPFTau32Index = -1;
//    this -> _doubleMediumIsoPFTau35Index = -1;
//    this -> _doubleMediumIsoPFTau40Index = -1;

    const edm::TriggerNames::Strings& triggerNames = this -> _hltConfig.triggerNames();
    std::cout << " ===== LOOKING FOR THE PATH INDEXES =====" << std::endl;
    for (tParameterSet& parameter : this -> _parameters){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;
                std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }

}

void Ntuplizer::Initialize() {
    this -> _indexevents = 0;
    this -> _runNumber = 0;
    this -> _lumi = 0;
    // this -> _tauPtVector.clear();
    this -> _tauPt = -1.;
    this -> _tauTriggered = 0;
}


void Ntuplizer::beginJob()
{
    edm::Service<TFileService> fs;
    this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

    //Branches
    this -> _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    this -> _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    this -> _tree -> Branch("lumi",&_lumi,"lumi/I");
    // this -> _tree -> Branch("tauPt", &_tauPtVector);
    // this -> _tree -> Branch("isTriggered", &_tauTriggeredVector);
    this -> _tree -> Branch("tauPt", &_tauPt);
    this -> _tree -> Branch("isTriggered", &_tauTriggered);

    return;
}


void Ntuplizer::endJob()
{
    return;
}


void Ntuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    return;
}

void Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{

    this -> Initialize();

    _indexevents = iEvent.id().event();
    _runNumber = iEvent.id().run();
    _lumi = iEvent.luminosityBlock();

    // std::auto_ptr<pat::MuonRefVector> resultMuon(new pat::MuonRefVector);

    // search for the tag in the event
    edm::Handle<pat::MuonRefVector> muonHandle;
    edm::Handle<pat::TauRefVector>  tauHandle;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;

    iEvent.getByToken(this -> _muonsTag, muonHandle);
    iEvent.getByToken(this -> _tauTag,   tauHandle);
    iEvent.getByToken(this -> _triggerObjects, triggerObjects);
    iEvent.getByToken(this -> _triggerBits, triggerBits);

    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
    const pat::TauRef tau = (*tauHandle)[0] ;

    // int idx = 0;
    uint isTriggered = 0;
    for (pat::TriggerObjectStandAlone obj : *triggerObjects)
    {
        // std::cout << "XXXX " << deltaR2 (*tau, obj) << std::endl;
        if (deltaR (*tau, obj) < 0.5)
        {
            obj.unpackPathNames(names);
            const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
            //Looking for the path
            for (const tParameterSet& parameter : this -> _parameters){
                if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false))){
                    //Path found, now looking for the label 1, if present in the parameter set
                    std::cout << "==== FOUND PATH " << triggerNames[parameter.hltPathIndex] << " ====" << std::endl;
                    //Retrieving filter list for the event
                    const std::vector<std::string>& vLabels = obj.filterLabels();
                    const std::vector<std::string>& filters = (parameter.leg1 == 15)? (parameter.hltFilters1):(parameter.hltFilters2);
                    if (this -> isTau(vLabels, filters)){
                        std::cout << "#### FOUND TAU ####" << std::endl;
                        isTriggered = true;
                    }
                }
            }
        }
    }

    // this -> _tauPtVector.push_back(tau->pt());
    // this -> _tauTriggeredVector.push_back(isTriggered);
    this -> _tauPt = tau->pt();
    this -> _tauTriggered = isTriggered;

    // ++idx;

    /*
    for (size_t imu = 0; imu < muonHandle -> size(); ++imu )
    {
        const pat::MuonRef mu = (*muonHandle)[imu] ;
        std::cout << "##### MUON PT: " << mu -> pt() << std::endl;
        this -> _muonsPtVector.push_back(mu -> pt());
    }
    */

    this -> _tree -> Fill();

}

bool Ntuplizer::isTau(const std::vector<std::string>& eventLabels, const std::vector<std::string>& filtersToLookFor) {
    bool tau = true;
    for (const std::string& filter : filtersToLookFor)
    {
        //Looking for matching filters
        bool found = false;
        for (const std::string& label : eventLabels)
        {
            //if (label == std::string("hltOverlapFilterIsoMu17MediumIsoPFTau40Reg"))
            if (label == filter)
            {

                std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;

                found = true;
            }
        }
        if(!found) tau = false;
    }

    return tau;
}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(Ntuplizer);

#endif //NTUPLIZER_H
