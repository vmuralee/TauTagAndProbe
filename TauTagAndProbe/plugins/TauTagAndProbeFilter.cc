#ifndef TAUTAGANDPROBEFILTER_H
#define TAUTAGANDPROBEFILTER_H

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/MET.h>
#include <DataFormats/PatCandidates/interface/CompositeCandidate.h>

#include <iostream>

using namespace edm;
using namespace std;
// using namespace reco;

 
class TauTagAndProbeFilter : public edm::EDFilter {

    public:
        TauTagAndProbeFilter(const edm::ParameterSet &);
        ~TauTagAndProbeFilter();

    private:
        bool filter(edm::Event &, edm::EventSetup const&);

        EDGetTokenT<pat::TauRefVector>   _tausTag;
        EDGetTokenT<pat::MuonRefVector>  _muonsTag;
        // EDGetTokenT<MuonRefVector>  _metTag;
};

TauTagAndProbeFilter::TauTagAndProbeFilter(const edm::ParameterSet & iConfig) :
_tausTag(consumes<pat::TauRefVector>  (iConfig.getParameter<InputTag>("taus"))),
_muonsTag(consumes<pat::MuonRefVector>(iConfig.getParameter<InputTag>("muons")))
// _metTag(consumes<pat::TauRefVector>(iConfig.getParameter<InputTag>("met"))),
{
    produces <pat::TauRefVector>  (); // probe
    produces <pat::MuonRefVector> (); // tag
}

TauTagAndProbeFilter::~TauTagAndProbeFilter()
{}

bool TauTagAndProbeFilter::filter(edm::Event & iEvent, edm::EventSetup const& iSetup)
{
    auto_ptr<pat::MuonRefVector> resultMuon ( new pat::MuonRefVector );
    auto_ptr<pat::TauRefVector>  resultTau  ( new pat::TauRefVector  );

    // search for the tag in the event
    Handle<pat::MuonRefVector> muonHandle;
    iEvent.getByToken (_muonsTag, muonHandle);
    for (size_t imu = 0; imu < muonHandle->size(); ++imu )
    {
        const pat::MuonRef mu = (*muonHandle)[imu] ;
        cout << mu->pt() << endl;
    }

    iEvent.put(resultMuon);
    iEvent.put(resultTau);

    return true;
}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(TauTagAndProbeFilter);

#endif