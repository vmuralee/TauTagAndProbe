#ifndef MUONNUMBERFILTER_H
#define MUONNUMBERFILTER_H

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Muon.h>

#include <iostream>

using namespace edm;
using namespace std;
// using namespace reco;

 
class muonNumberFilter : public edm::EDFilter {

    public:
        muonNumberFilter(const edm::ParameterSet &);
        ~muonNumberFilter();

    private:
        bool filter(edm::Event &, edm::EventSetup const&);
        EDGetTokenT<pat::MuonCollection>  _muonTag;
};

muonNumberFilter::muonNumberFilter(const edm::ParameterSet & iConfig) :
_muonTag   (consumes<pat::MuonCollection> (iConfig.getParameter<InputTag>("src")))
{}

muonNumberFilter::~muonNumberFilter()
{}

bool muonNumberFilter::filter(edm::Event & iEvent, edm::EventSetup const& iSetup)
{
    Handle<pat::MuonCollection> muonHandle;
    iEvent.getByToken (_muonTag, muonHandle);
    if (muonHandle->size() != 1) return false;
    return true;
}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(muonNumberFilter);

#endif
