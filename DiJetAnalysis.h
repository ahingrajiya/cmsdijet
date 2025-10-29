/**
 * @file DijetAnalysis.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Dijet Analysis for CMS pPb
 * @version 0.1
 * @date 2024-08-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DiJetAnalysis_h
#define DiJetAnalysis_h

#include <iostream>

// ROOT libraries
#include "TObject.h"
#include "TString.h"
// ROOT Headers
#include "TF1.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TObject.h"
#include "TROOT.h"
#include "TVector3.h"

// Jet analysis headers
#include "BaseAnalysis.h"
#include "Event.h"
#include "ForestReader.h"
#include "HistoManagerDiJet.h"
#include "PbPb_TrackingEfficiencies/trackingEfficiency2018PbPb.h"
#include "TSpline.h"
#include "TVector2.h"
#include "pPb_TrackingEfficiency/TrkEfficiency2016pPb.h"

class DiJetAnalysis : public BaseAnalysis
{
   public:
    /// @brief Default Constructor
    DiJetAnalysis();
    ///@brief Destructor
    virtual ~DiJetAnalysis();

    ///@brief Initializing variables
    void init();

    ///@brief Process events
    void processEvents(const Event* ev);

    ///@brief Finish analysis
    void finish();

    ///@brief Return reprots of all selections applied
    virtual void report();
    ///@brief Return a list of objects to be written as output
    virtual TList* getOutputList();

    ///@brief Set Multiplicity or Centrality bins
    void setMultBins(const std::vector<std::pair<Double_t, Double_t>>& Bins)
    {
        for (const auto& [threshold, value] : Bins)
        {
            fMultBins[threshold] = value;
        }
    }

    void setHiHFBins(const std::vector<std::pair<Double_t, Double_t>>& Bins)
    {
        for (const auto& [threshold, value] : Bins)
        {
            fHiHFBins[threshold] = value;
        }
    }
    ///@brief Set debug information
    void setDebug(const Bool_t& debug) { fDebug = debug; }
    ///@brief Add histogram Manager
    void addHistoManager(HistoManagerDiJet* hm) { fHM = hm; }
    ///@brief Set DeltaPhi selection for dijet
    void setDeltaPhi(const Double_t& deltaphi) { fDeltaPhi = deltaphi; }
    ///@brief Set if dataset is MC or not
    void setIsMC(const Bool_t& isMC) { fIsMC = isMC; }
    ///@brief Set if it is Pbgoing direction
    void setIsPbGoing() { fIsPbGoing = kTRUE; }
    ///@brief Set if it is pgoing direction
    void setIspGoing() { fIsPbGoing = kFALSE; }
    ///@brief Set Multiplicity Range
    void setMultiplicityRange(const Double_t& low, const Double_t& hi)
    {
        fMultiplicityRange[0] = low;
        fMultiplicityRange[1] = hi;
    }
    ///@brief Set Reader
    void setReader(ForestReader* reader) { fReader = reader; }
    /// @brief Set Center of mass reference frame for pPb
    void setUseCMFrame() { fUseCMFrame = kTRUE; }
    ///@brief Set Eta Boost
    void setEtaBoost(const Double_t& boost)
    {
        if (!fIsMC)
        {
            if (fIsPbGoing)
            {
                fEtaBoost = -boost;
            }
            else if (!fIsPbGoing)
            {
                fEtaBoost = boost;
            }
        }
        else if (fIsMC)
        {
            if (fIsPbGoing)
            {
                fEtaBoost = boost;
            }
            else if (!fIsPbGoing)
            {
                fEtaBoost = -boost;
            }
        }
    }
    ///@brief Set if to use centrality weight
    void setUseCentralityWeight() { fUseCentralityWeight = kTRUE; }
    ///@brief Set if to use multiplicity weight
    void setUseMultiplicityWeigth() { fUseMultiplicityWeight = kTRUE; }
    ///@brief Set if to use dijet weight
    void setUseDijetWeight() { fUseDijetWeight = kTRUE; }
    ///@brief Set Leading jet pt selection
    void setLeadJetPt(const Double_t& leadjetpt) { fLeadJetPtLow = leadjetpt; }
    ///@brief Set Sub leading jet pt selection
    void setSubLeadJetPt(const Double_t& subleadjetpt) { fSubLeadJetPtLow = subleadjetpt; }
    ///@brief Set Leading jet eta range
    void setLeadJetEtaRange(const Double_t& low, const Double_t& hi)
    {
        fLeadJetEtaRange[0] = low;
        fLeadJetEtaRange[1] = hi;
    }
    ///@brief Set Sub leading jet eta range
    void setSubLeadJetEtaRange(const Double_t& low, const Double_t& hi)
    {
        fSubLeadJetEtaRange[0] = low;
        fSubLeadJetEtaRange[1] = hi;
    }
    ///@brief Set if verbose mode is used or not
    void setVerbose() { fVerbose = kTRUE; }
    ///@brief Set Number of events to process
    void setNEventsInSample(const Long64_t& nevents) { fNEventsInSample = nevents; }
    ///@brief Set Track Pt for specific multiplicty calculation
    void setMinTrkPt(const Double_t& mintrkpt) { fMinTrkPt = mintrkpt; }
    ///@brief Set Track Eta Range for specicif multiplicity calculation
    void setTrkEtaRange(const Double_t& low, const Double_t& hi)
    {
        fTrkEtaRange[0] = low;
        fTrkEtaRange[1] = hi;
    }
    ///@brief Set which multiplicity type to use for the event selection
    void setMultiplicityType(const Int_t& multType) { fMultiplicityType = multType; }
    ///@brief Set Tracking efficiency table
    void setTrackingTable(const std::string& trackingTable) { fTrkEffTable = trackingTable; }
    /// @brief Set Dijet weight table
    /// @param dijetWeightTable Path to the dijet weight table
    void setDijetWeightTable(const std::string& dijetWeightTable) { fDijetWeightTable = dijetWeightTable; }
    /// @brief Set if to calculate in jet multiplicity
    void doInJetMultiplicity() { fDoInJetMult = kTRUE; }
    ///@brief Set Dijet Weight type
    void setDijetWeightType(const std::string& dijetWeightType) { fDijetWeightType = dijetWeightType; }
    ///@brief set underlying event type
    void setUEType(const std::string& UEType) { fUEType = UEType; }
    ///@brief Do tracking closure plots
    void doTrackingClosure() { fDoTrackingClosures = kTRUE; }

    ///@brief Set if to apply vz weight
    void setVzWeight() { fDoVzWeight = kTRUE; }
    ///@brief Set Inclusive Corrected Jet Pt Minimum
    void setInclusiveCorrectedJetPtMin(const Double_t& minPt) { fInclusiveCorrectedJetPtMin = minPt; }
    ///@brief Set Inclusive Jet Eta Range
    void setInclusiveJetEtaRange(const Double_t& low, const Double_t& high)
    {
        fInclusiveJetEtaRange[0] = low;
        fInclusiveJetEtaRange[1] = high;
    }
    ///@brief Set hihf rewighting
    void useHiHFWeight(bool useWeight = false) noexcept { fUseHiHFWeight = useWeight; }

   private:
    /// @brief Reco and Corrected Multiplicity calculator with custom track pt and track eta cuts
    /// @param event Event object
    /// @param eventWeight Event weight
    /// @param multiplicityBin Multiplicity bin
    /// @return Returns pair of Reco tracks with custom trackpt and track eta cut and number of
    /// tracks in given trk pt and eta range with tracking efficiency correction. Correction factor
    /// is [1-(fake rate)]/(efficiency)
    std::pair<Int_t, Float_t> RecoCorrectedMultiplicity(const Event* event, const Double_t& eventWeight, const Double_t& multiplicityBin);
    /// @brief Sets up correct efficiency tables for tracking efficiency correction
    /// @param trackingTable Path to the tracking efficiency correction table with its name
    /// included. Table is usually root file with .root extension
    void SetUpTrackingEfficiency(const std::string& trackingTable);
    /// @brief Gen and Subevent Multiplicity calculator
    /// @param event Event object
    /// @param eventWeight Event weight
    /// @param multiplicityBin Multiplicity bin
    /// @return Returns number of generated tracks in the event for a given Trk Pt and Eta range and
    /// generated subevent tracks.
    std::pair<Int_t, Int_t> GenSubeMultiplicity(const Event* event, const Double_t& eventWeight, const Double_t& multiplicityBin);
    /// @brief Event weight calculator
    /// @param event Event object
    /// @return Returns event level weight which has to be applied to every hisotgram
    Double_t EventWeight(const Event* event);
    /// @brief @brief pPb ptHat weight calculator
    /// @param ptHat pthat value
    /// @return returns weight for given pthat of event in MC
    Double_t pPbptHatWeight(const Double_t& ptHat);
    /// @brief Multiplicity weights
    /// @param multiplicity Multiplicity of the event
    /// @return Array of weights for multiplicity ranges
    Double_t* MultiplicityWeight(const Int_t& multiplicity);
    /// @brief Multiplicity weights
    /// @param multiplicity Multiplicity of the event
    /// @return Array of weights for multiplicity ranges
    Double_t MultiplicityWeight(const Double_t& multiplicity);
    /// @brief Dijet weights
    /// @param ispPb Set to be true if it is pPb dataset. For PbPb dataset it needs is set to be
    /// false
    /// @param leadJetPt Leading jet pt
    /// @param subLeadJetPt Subleading jet pt
    /// @return Dijet weight
    Float_t DijetWeight(const Bool_t& ispPb, const Double_t& leadJetPt, const Double_t& subLeadJetPt);
    /// @brief Calaulates Delta Phi between two jets
    /// @param phi1 Jet Phi 1
    /// @param phi2 Jet Phi 2
    /// @return returns delta phi between two jets between -pi and pi
    Double_t DeltaPhi(const Double_t& phi1, const Double_t& phi2);
    /// @brief Process all the events
    /// @param event Event object
    void processEvent(const Event* event);
    /// @brief Process Reco Jets
    /// @param event Event object
    void processRecoJets(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin);
    /// @brief Process Gen Jets
    /// @param event Event object
    void processGenJets(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin);
    /// @brief Process Reco Tracks
    /// @param event Event object
    /// @param event_Weight Event weight
    /// @param multWeight Multiplicity weight
    /// @param multiplicityBin Multiplicity bin
    void processRecoTracks(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin);
    /// @brief Process Gen Tracks
    /// @param event Event object
    /// @param event_Weight Event weight
    /// @param multWeight Multiplicity weight
    /// @param multiplicityBin Multiplicity bin
    void processGenTracks(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin);
    /// @brief Check if all dijet requirements are satisfied
    /// @param leadJetPt Found leading jet pt
    /// @param leadJetEta Found leading jet eta
    /// @param subLeadJetPt Found subleading jet pt
    /// @param subLeadJetEta Found subleading jet eta
    /// @param leadID Leading jet ID
    /// @param subLeadID Subleading jet ID
    /// @return Returns true if all dijet requirements are satisfied
    Bool_t CheckDijet(const Float_t& leadJetPt, const Float_t& leadJetEta, const Float_t& subLeadJetPt, const Float_t& subLeadJetEta, const Bool_t& leadID,
                      const Bool_t& subLeadID);
    /// @brief Xj calculator
    /// @param leadJetPt Leading jet pt
    /// @param subLeadJetPt Subleading jet pt
    /// @return Xj value Xj = Suleading jet pt / Leading Jet pt
    Double_t Asymmetry(const Float_t& leadJetPt, const Float_t& subLeadJetPt);
    /// @brief  Find Multiplicity Bin
    /// @param multiplicity or HiHF energy
    /// @return Multiplicity Bin. 1 for 60-120, 2 for 120-185, 3 for 185-250, 4 for 250-400
    Double_t FindBin(const double& multiplicity, const std::map<Double_t, Double_t>& Bins);
    /// @brief Move to Center of Mass Frame
    /// @param jetEta Jet Eta
    Float_t MoveToCMFrame(const Float_t& jetEta);
    /// @brief Move to Lab Frame
    /// @param jetEta Jet Eta
    Float_t MoveToLabFrame(const Float_t& jetEta);
    /// @brief Set up Dijet weight table
    void SetUpDijetWeight(const std::string& dijetWeightTable);
    ///@brief Set up collision system booleans
    void CollSystem(ForestReader& reader);
    ///@brief Set up weight functions
    void SetUpWeightFunctions();
    ///@brief Dijet weight calculator
    ///@param event Event object
    ///@return Dijet weight
    Float_t DijetWeight(const Event* event);
    ///@brief Get DiJet Region based on jet eta
    ///@param jetEta Jet Eta
    ///@return Returns 1 for Backward , 2 for Mid , 3 for Forward, and -1 for not in any region
    Int_t GetDiJetRegion(const Float_t& jetEta);
    ///@brief Flip Vertex
    ///@param vertexz Vertex Z for pPb
    ///@return Returns the vertexz after flipping it for pPb
    Float_t FlipVertexZ(const Float_t& vertexz);
    ///@brief Get Bin for Dijet Weight
    ///@param binEdges Bin Edges of Histogram
    ///@param value Value to search for in bin edges
    Int_t BinBinarySearch(const std::vector<double>& binEdges, const double& value);
    ///@brief Get jet flavor
    ///@param partonFlavour Parton flavour from jet
    ///@return Returns jet flavor classified as quark jets ->1 and gluon jets -> -1 and unknown
    /// flavor -> 0
    Double_t GetJetFlavor(const Int_t& partonFlavour);
    ///@brief Get HiHFWeight
    ///@param hiHF HiHF value
    ///@return Returns HiHF weight
    Double_t HiHFWeight(const Double_t& hiHF);

    ///@brief Print debug information
    Bool_t fDebug;
    ///@brief Delta Phi selection for dijet
    Double_t fDeltaPhi;
    ///@brief If it is pPb dataset
    Bool_t fIspPb;
    ///@brief If it is pp dataset
    Bool_t fIspp;
    ///@brief If it is PbPb dataset
    Bool_t fIsPbPb;
    ///@brief If it is OO dataset
    Bool_t fIsOO;
    ///@brief Colliding system
    TString fCollSystem;
    ///@brief If it it MC
    Bool_t fIsMC;
    ///@brief if it is Pb going direction
    Bool_t fIsPbGoing;
    ///@brief Multiplicity Range
    Double_t fMultiplicityRange[2];
    ///@brief Move to Center of Mass Frame
    Bool_t fUseCMFrame;
    ///@brief Eta Boots for pPb
    Double_t fEtaBoost;
    ///@brief Use Centrality weight
    Bool_t fUseCentralityWeight;
    ///@brief Use Multipicity weight
    Bool_t fUseMultiplicityWeight;
    ///@brief Use Dijet Weighting
    Bool_t fUseDijetWeight;
    ///@brief Dijet Weight
    Float_t fDijetWeight;
    ///@brief Leading jet pt cut
    Double_t fLeadJetPtLow;
    ///@brief Subleading jet pt cut
    Double_t fSubLeadJetPtLow;
    /// @brief Leading jet eta cut
    Double_t fLeadJetEtaRange[2];
    ///@brief Subleading jet eta cut
    Double_t fSubLeadJetEtaRange[2];
    ///@brief Verbose Mode
    Bool_t fVerbose;
    ///@brief Set Number of events to process
    Int_t fNEventsInSample;
    ///@brief If Dijet is found
    Bool_t fIsDiJetFound;
    ///@brief If Gen Dijet is found
    Bool_t fIsGenDiJetFound;
    ///@brief Histogram Manager
    HistoManagerDiJet* fHM;
    ///@brief Minimum Track Pt Cut for specific multiplicity calculation
    Double_t fMinTrkPt;
    ///@brief Track eta range for specific multiplicity calculation
    Double_t fTrkEtaRange[2];
    ///@brief Tracking efficiency for PbPb
    TrkEff2018PbPb* fTrkEffPbPb;
    ///@brief Tracking efficiency for pPb
    TrkEfficiency2016pPb* fTrkEffpPb;
    ///@brief Dijet weight table PYTHIA at 8 TeV
    std::string fDijetWeightTable;
    ///@brief Dijet Weight histograms
    TH2* hDijetWeight;
    ///@brief Dijet weight type
    Bool_t fRecoType;
    Bool_t fRefType;
    Bool_t fGenType;
    ///@brief Tracking efficiency table for PbPb
    std::string fTrkEffTable;

    ///@brief Dijet Weight file
    TFile* fDijetWeightFile;
    ///@brief Do Injet Multiplicity
    Bool_t fDoInJetMult;
    ///@brief DiJet Weight Type
    std::string fDijetWeightType;
    ///@brief Underlying event
    std::string fUEType;
    ///@brief Do Tracking Closures
    Bool_t fDoTrackingClosures;

    ///@brief Which Multiplicity type to use for event selection.
    /// 0 -> Reco Multiplicity
    /// 1 -> Gen Multiplicity (Only Applicable for MC)
    /// 2 -> Efficinecy corrected multiplicity
    /// 3 -> SubEvent Multiplicity
    Int_t fMultiplicityType;
    ///@brief Event counter
    Int_t fEventCounter;

    Int_t fCycleCounter;

    ///@brief Vertex Z weight function
    TF1* fVertexZWeight;
    ///@brief Do Vz weight
    Bool_t fDoVzWeight;
    ///@brief Holds multiplicity weight functions
    TF1* fMultWeightFunctions[4];
    ///@brief Bin Edges for DijetWeight Histogram
    std::vector<double> fXBinEdges;
    ///@brief Bin Edges for DijetWeight Histogram
    std::vector<double> fYBinEdges;
    ///@brief Dijet Weights Holder
    std::vector<double> fBinContent;
    ///@brief Number of Bins on X Axis
    Int_t fXBinCount;
    ///@brief Number of Bins on Y Axis
    Int_t fYBinCount;
    ///@brief Inclusive Corrected JetPt Minimum
    Double_t fInclusiveCorrectedJetPtMin;
    ///@brief Inclusive Jet Eta
    Double_t fInclusiveJetEtaRange[2];
    ///@brief Forest Reader
    ForestReader* fReader;
    ///@brief Weight function for HIHF
    TF1* fHiHFWeight;
    ///@brief Boolean for HiHFWeighting
    bool fUseHiHFWeight;

    ///@brief Holds dynamic multiplicity or centrality bins
    std::map<Double_t, Double_t> fMultBins;

    ///@brief Holds dynamic multiplicity or centrality bins
    std::map<Double_t, Double_t> fHiHFBins;

    ClassDef(DiJetAnalysis, 0)
};

#endif
