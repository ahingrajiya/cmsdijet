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

#ifndef Event_h
#define Event_h

// ROOT headers
#include "Collections.h"
#include "TObject.h"
#include "TString.h"

// C++ headers
#include <iostream>

//________________
class Event : public TObject
{
   public:
    /// @brief Default constructor
    Event();
    /// @brief Parametrized constructor
    Event(const UInt_t& runId, const ULong64_t& eventId, const UInt_t& lumi, const Float_t& vx, const Float_t& vy, const Float_t& vz, const Int_t& hiBin,
          const Int_t& hiBinShifted, const Float_t& ptHat, const Float_t& w, const Int_t& nBadJets, const Int_t& mult, const Int_t& genMult, const Long64_t& eveNumber,
          const Float_t& hiHFPlus, const Float_t& hiHFMinus, const int& corrNtrkoff);
    /// @brief Destructor
    virtual ~Event();

    //
    // Setters
    //

    /// @brief Set run index
    void setRunId(const UInt_t& id) { fRunId = id; }
    /// @brief Set event index
    void setEventId(const ULong64_t& id) { fEventId = id; }
    /// @brief Set luminosity
    void setLumi(const UInt_t& lumi) { fLumi = lumi; }
    /// @brief Set vertex x position
    void setVx(const Float_t& vx) { fVx = vx; }
    /// @brief Set vertex y position
    void setVy(const Float_t& vy) { fVy = vy; }
    /// @brief Set vertex z position
    void setVz(const Float_t& vz) { fVz = vz; }
    /// @brief Set vertex x, y, and z coordinates
    void setVertex(const Float_t& x, const Float_t& y, const Float_t& z)
    {
        fVx = x;
        fVy = y;
        fVz = z;
    }
    /// @brief Set centrality bin (0-200)
    void setHiBin(const Int_t& hiBin) { fHiBin = hiBin; }
    ///@brief Set Shifted Centrality Bin
    void setHiBinShifted(const Int_t& hiBinShifted) { fHiBinShifted = hiBinShifted; }
    /// @brief Set ptHat
    void setPtHat(const Float_t& ptHat) { fPtHat = ptHat; }
    /// @brief Set event weight
    void setPtHatWeight(const Float_t& w) { fPtHatWeight = w; }
    /// @brief Set number of particle flow jets with pT > pThat
    void setNumberOfOverscaledPFJets(const Int_t& n) { fNBadJets = (UChar_t)n; }
    /// @brief Set reference multiplicity (CMS way)
    void setMultiplicity(const Int_t& mult) { fMult = (UShort_t)mult; }
    /// @brief Set reference multiplicity (CMS way)
    void setGenMultiplicity(const Int_t& genMult) { fGenMult = (UShort_t)genMult; }
    /// @brief Set the flag that generated jet collection is filled to true
    void setGenJetCollectionIsFilled() { fGenJetsCollectionIsFilled = kTRUE; }
    /// @brief Set event number in the process
    void setEventNumber(const Long64_t& eventNumber) { fEventNumber = eventNumber; }
    /// @brief Set trigger name and value
    void setTriggerNameAndValue(const std::vector<std::pair<std::string, Int_t>>& triggerNameValuePair) { fTriggerNamesAndValues = triggerNameValuePair; }
    /// @brief Set skim filter name and value
    void setSkimFilterNameAndValue(const std::vector<std::pair<std::string, Int_t>>& filterNameValuePair) { fSkimFilterNamesAndValues = filterNameValuePair; }
    /// @brief Set HiHFPlus
    void setHiHFPlus(const Float_t& hiHFPlus) { fHiHFPlus = hiHFPlus; }
    /// @brief Set HiHFMinus
    void setHiHFMinus(const Float_t& hiHFMinus) { fHiHFMinus = hiHFMinus; }
    ///@brief Set Corrected Multiplicity
    void setCorrectedNtrkoff(const int& corrNtrkoff) { fCorrectedNtrkoff = corrNtrkoff; }

    /// @brief  Print event information
    void print();

    //
    // Getters
    //

    /// @brief Return run index
    UInt_t runId() const { return fRunId; }
    /// @brief Return event index
    ULong64_t eventId() const { return fEventId; }
    /// @brief Return luminosity
    UInt_t lumi() const { return fLumi; }
    /// @brief Return vertex z
    Float_t vz() const { return fVz; }
    /// @brief Return hiBin bin
    Int_t hiBin() const { return (Int_t)fHiBin; }
    /// @brief Return hiBin bin for PYTHIA+HYDJET. This hiBin is -5% shifted to match multiplicity
    /// distribution with MB PbPb data
    Int_t hiBinWithShift() const { return (fHiBinShifted); }
    /// @brief Return centrality bin
    Double_t centrality() const { return (fHiBin < 0) ? -5 : 100. - Double_t(200 - fHiBin) * 0.5; }
    /// @brief Return ptHat
    Float_t ptHat() const { return fPtHat; }
    /// @brief Return event weight
    Float_t ptHatWeight() const { return fPtHatWeight; }
    /// @brief Return number of particle flow jets in even with pT > pThat
    Int_t numberOfOverscaledPFJets() const { return (Int_t)fNBadJets; }
    /// @brief Return reference multiplicity (CMS way)
    Int_t multiplicity() const { return (Int_t)fMult; }
    /// @brief Return gen multiplicity (CMS way)
    Int_t genMultiplicity() const { return (Int_t)fGenMult; }
    /// @brief Return if generated jet collection filled
    Bool_t isGenJetCollectionFilled() const { return fGenJetsCollectionIsFilled; }
    /// @brief Return number of particle flow jets
    UInt_t numberOfRecoJets() const { return this->recoJetCollection()->size(); }
    /// @brief Return number of generated jets
    UInt_t numberOfGenJets() const { return this->genJetCollection()->size(); }
    /// @brief Return event number in the process
    Long64_t eventNumber() const { return fEventNumber; }
    /// @brief Return HiHFPlus
    Float_t hiHFPlus() const { return fHiHFPlus; }
    /// @brief Return HiHFMinus
    Float_t hiHFMinus() const { return fHiHFMinus; }
    ///@brief Return Corrected Ntrkoff
    int correctedNtrkoff() const { return fCorrectedNtrkoff; }

    /// @brief Return pointer to a collection of tracks
    TrackCollection* trackCollection() const { return fTrackCollection; }
    /// @brief Return pointer to a collection of MC tracks
    GenTrackCollection* genTrackCollection() const { return fGenTrackCollection; }
    /// @brief Return pointer to a collection of reco jets
    RecoJetCollection* recoJetCollection() const { return fRecoJetCollection; }
    /// @brief Return pointer to a collection of generated jets
    GenJetCollection* genJetCollection() const { return fGenJetCollection; }
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
    ///@brief Corrected Ntrkoff
    int fCorrectedNtrkoff;
    /// @brief Check if collection of generated jets is filled
    Bool_t fGenJetsCollectionIsFilled;
    ///@brief Event number in the process
    Long64_t fEventNumber;
    ///@brief Hi FOrward Calorimeter positive eta energy
    Float_t fHiHFPlus;
    ///@brief Hi Forward Calorimeter negative eta energy
    Float_t fHiHFMinus;
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