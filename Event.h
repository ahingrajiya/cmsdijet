/**
 * @file Event.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Internal event structure of the framework
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Collections.h"
// C++ headers
#include <iostream>

//________________
class Event
{
   public:
    /// @brief Default constructor
    Event() noexcept;
    /// @brief Parametrized constructor
    Event(unsigned int runId, unsigned long long eventId, unsigned int lumi, float vx, float vy, float vz, int hiBin, int hiBinShifted, float ptHat, float weight,
          int nBadJets, int mult, int genMult, long long eveNumber) noexcept;
    /// @brief Destructor
    ~Event() noexcept = default;

    //
    // Setters
    //

    /// @brief Set run index
    void setRunId(unsigned int id) noexcept { fRunId = id; }
    /// @brief Set event index
    void setEventId(unsigned long long id) noexcept { fEventId = id; }
    /// @brief Set luminosity
    void setLumi(unsigned int lumi) noexcept { fLumi = lumi; }
    /// @brief Set vertex x position
    void setVx(float vx) noexcept { fVx = vx; }
    /// @brief Set vertex y position
    void setVy(float vy) noexcept { fVy = vy; }
    /// @brief Set vertex z position
    void setVz(float vz) noexcept { fVz = vz; }
    /// @brief Set vertex x, y, and z coordinates
    void setVertex(float x, float y, float z) noexcept
    {
        fVx = x;
        fVy = y;
        fVz = z;
    }
    /// @brief Set centrality bin (0-200)
    void setHiBin(int hiBin) noexcept { fHiBin = hiBin; }
    ///@brief Set Shifted Centrality Bin
    void setHiBinShifted(int hiBinShifted) noexcept { fHiBinShifted = hiBinShifted; }
    /// @brief Set ptHat
    void setPtHat(float ptHat) noexcept { fPtHat = ptHat; }
    /// @brief Set event weight
    void setPtHatWeight(float w) noexcept { fPtHatWeight = w; }
    /// @brief Set number of particle flow jets with pT > pThat
    void setNumberOfOverscaledPFJets(int n) noexcept { fNBadJets = (UChar_t)n; }
    /// @brief Set reference multiplicity (CMS way)
    void setMultiplicity(int mult) noexcept { fMult = (UShort_t)mult; }
    /// @brief Set reference multiplicity (CMS way)
    void setGenMultiplicity(int genMult) noexcept { fGenMult = (UShort_t)genMult; }
    /// @brief Set event number in the process
    void setEventNumber(long long eventNumber) noexcept { fEventNumber = eventNumber; }
    /// @brief Set trigger name and value
    void setTriggerNameAndValue(const std::vector<std::pair<std::string, int>>& triggerNameValuePair) noexcept { fTriggerNamesAndValues = triggerNameValuePair; }
    /// @brief Set skim filter name and value
    void setSkimFilterNameAndValue(const std::vector<std::pair<std::string, int>>& filterNameValuePair) noexcept { fSkimFilterNamesAndValues = filterNameValuePair; }

    /// @brief  Print event information
    void print();

    //
    // Getters
    //

    /// @brief Return run index
    unsigned int runId() const noexcept { return fRunId; }
    /// @brief Return event index
    unsigned long long eventId() const noexcept { return fEventId; }
    /// @brief Return luminosity
    unsigned int lumi() const noexcept { return fLumi; }
    /// @brief Return vertex z
    float vz() const noexcept { return fVz; }
    /// @brief Return hiBin bin
    int hiBin() const noexcept { return static_cast<int>(fHiBin); }
    /// @brief Return hiBin bin for PYTHIA+HYDJET. This hiBin is -5% shifted to match multiplicity
    /// distribution with MB PbPb data
    int hiBinWithShift() const noexcept { return (fHiBinShifted); }
    /// @brief Return centrality bin
    double centrality() const noexcept { return (fHiBin < 0) ? -5 : 100. - double(200 - fHiBin) * 0.5; }
    /// @brief Return ptHat
    float ptHat() const noexcept { return fPtHat; }
    /// @brief Return event weight
    float ptHatWeight() const noexcept { return fPtHatWeight; }
    /// @brief Return reference multiplicity (CMS way)
    int multiplicity() const noexcept { return static_cast<int>(fMult); }
    /// @brief Return gen multiplicity (CMS way)
    int genMultiplicity() const noexcept { return static_cast<int>(fGenMult); }
    /// @brief Return number of particle flow jets
    unsigned int numberOfRecoJets() const noexcept { return static_cast<unsigned int>(fRecoJetCollection->size()); }
    /// @brief Return number of generated jets
    unsigned int numberOfGenJets() const noexcept { return static_cast<unsigned int>(fGenJetCollection->size()); }
    /// @brief Return event number in the process
    long long eventNumber() const noexcept { return fEventNumber; }

    /// @brief Return pointer to a collection of tracks
    TrackCollection* trackCollection() const { return fTrackCollection; }
    /// @brief Return pointer to a collection of MC tracks
    GenTrackCollection* genTrackCollection() const { return fGenTrackCollection; }
    /// @brief Return pointer to a collection of reco jets
    RecoJetCollection& recoJetCollection() noexcept { return *fRecoJetCollection; }
    /// @brief Return pointer to a collection of generated jets
    GenJetCollection& genJetCollection() noexcept { return *fGenJetCollection; }

    /// @brief Return trigger name and value vector
    std::vector<std::pair<std::string, Int_t>> triggerNamesAndValues() const { return fTriggerNamesAndValues; }
    /// @brief Return skim filter name and value vector
    std::vector<std::pair<std::string, Int_t>> skimFilterNamesAndValues() const { return fSkimFilterNamesAndValues; }

   private:
    /// @brief Run index
    UInt_t fRunId;
    /// @brief Event index
    ULong64_t fEventId;
    /// @brief Luminosity value
    UInt_t fLumi;
    /// @brief Vertex x position
    Float_t fVx;
    /// @brief Vertex y position
    Float_t fVy;
    /// @brief Vertex z position
    Float_t fVz;
    /// @brief Centrality bin
    Short_t fHiBin;
    ///@brief Shifted Centrality Bin
    Short_t fHiBinShifted;
    /// @brief pthat sclaing
    Float_t fPtHat;
    /// @brief Event weight scaling
    Float_t fPtHatWeight;
    /// @brief Number of jets with pT > pThat
    UChar_t fNBadJets;
    /// @brief Reference charged track multiplicity (CMS way)
    UShort_t fMult;
    /// @brief Reference Gen Charged track multiplicity (CMS way)
    UShort_t fGenMult;
    /// @brief Check if collection of generated jets is filled
    Bool_t fGenJetsCollectionIsFilled;
    ///@brief Event number in the process
    Long64_t fEventNumber;
    ///@brief Trigger name and triggervalue vector for event
    std::vector<std::pair<std::string, Int_t>> fTriggerNamesAndValues;
    ///@brief Skim filter name and filter value vector for event
    std::vector<std::pair<std::string, Int_t>> fSkimFilterNamesAndValues;

    /// @brief Reco jet collection
    RecoJetCollection* fRecoJetCollection;
    /// @brief Generated jet collection
    GenJetCollection* fGenJetCollection;

    /// @brief Track collection
    TrackCollection* fTrackCollection;
    /// @brief MC track collection
    GenTrackCollection* fGenTrackCollection;

    ClassDef(Event, 1)
};

#endif  // #define Event_h