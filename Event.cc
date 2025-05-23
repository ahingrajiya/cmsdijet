/**
 * @file Event.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Internal event structure of the framework
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// Jet analysis headers
#include "Event.h"

// ROOT headers
#include "TString.h"

// C++ headers
#include <iostream>

//________________
Event::Event() : TObject(), fRunId{0}, fEventId{0}, fLumi{0},
                 fVx{0}, fVy{0}, fVz{0}, fHiBin{-1}, fHiBinShifted{-10}, fPtHat{-1}, fPtHatWeight{-1},
                 fNBadJets{0}, fMult{0}, fGenMult{0}, fEventNumber{0},
                 fGenJetsCollectionIsFilled{kFALSE}
{
    fRecoJetCollection = new RecoJetCollection{};
    fGenJetCollection = new GenJetCollection{};
    fTrackCollection = new TrackCollection{};
    fGenTrackCollection = new GenTrackCollection{};
    fTriggerNamesAndValues.clear();
    fSkimFilterNamesAndValues.clear();
}

//________________
Event::Event(const UInt_t &runId, const ULong64_t &eventId, const UInt_t &lumi,
             const Float_t &vx, const Float_t &vy, const Float_t &vz,
             const Int_t &hiBin, const Int_t &hiBinShifted, const Float_t &ptHat,
             const Float_t &w, const Int_t &nBadJets, const Int_t &mult, const Int_t &genMult, const Long64_t &eveNumber) : TObject(),
                                                                                                                            fRunId{runId}, fEventId{eventId}, fLumi{lumi},
                                                                                                                            fVx{vx}, fVy{vy}, fVz{vz},
                                                                                                                            fHiBin{(Short_t)hiBin}, fHiBinShifted{(Short_t)hiBinShifted}, fPtHat{ptHat}, fPtHatWeight{w},
                                                                                                                            fNBadJets{(UChar_t)nBadJets},
                                                                                                                            fMult{(UShort_t)mult}, fGenMult{(UShort_t)genMult}, fGenJetsCollectionIsFilled{kFALSE}, fEventNumber{eveNumber}
{

    // Create new collections
    fRecoJetCollection = new RecoJetCollection{};
    fGenJetCollection = new GenJetCollection{};
    fTrackCollection = new TrackCollection{};
    fGenTrackCollection = new GenTrackCollection{};
    fTriggerNamesAndValues.clear();
    fSkimFilterNamesAndValues.clear();
}

//________________
Event::~Event()
{
    // Clean collection of particle jets
    for (RecoJetIterator iter = fRecoJetCollection->begin();
         iter != fRecoJetCollection->end(); iter++)
    {
        delete *iter;
    }
    // Clean collection of generated jets
    for (GenJetIterator iter = fGenJetCollection->begin();
         iter != fGenJetCollection->end(); iter++)
    {
        delete *iter;
    }
    // Clean track collection
    for (TrackIterator iter = fTrackCollection->begin();
         iter != fTrackCollection->end(); iter++)
    {
        delete *iter;
    }
    // Clean MC track collection
    for (GenTrackIterator iter = fGenTrackCollection->begin();
         iter != fGenTrackCollection->end(); iter++)
    {
        delete *iter;
    }
    // Clear trigger and skim filter
    fTriggerNamesAndValues.clear();
    fSkimFilterNamesAndValues.clear();
}

//________________
void Event::print()
{
    std::cout << Form("-------------------------------------\n")
              << Form("runId: %d  eventId: %llu  lumi: %d  vx: %5.2f  vy: %5.2f  vz: %5.2f\n", fRunId, fEventId, fLumi, fVx, fVy, fVz)
              << Form("hiBin: %d  ptHat: %3.2f  ptHatWeight: %4.2f \n", hiBin(), fPtHat, fPtHatWeight)
              << Form("-------------------------------------\n");
}