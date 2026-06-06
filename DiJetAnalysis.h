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
#include <random>
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

enum class CollisionSystem
{
    Unknown,
    pp,
    pPb,
    PbPb,
    OO
};
enum class DijetWeightType
{
    None,
    Reco,
    Ref,
    Gen
};

struct JetKinematics
{
    float pt = -999.0f;
    float eta = -999.0f;
    float phi = -999.0f;
    float matchPt = -999.0f;
    float matchEta = -999.0f;
    float matchPhi = -999.0f;
    bool id = false;
    int flavor = -999;
};

struct DijetInfo
{
    bool isValidDijet = false;
    JetKinematics lead;
    JetKinematics subLead;
    double deltaPhi = -999.0;
    double xj = -999.0;
};
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

    ///@brief Set debug information
    void setDebug(bool debug) noexcept { fDebug = debug; }
    ///@brief Add histogram Manager
    void addHistoManager(HistoManagerDiJet* hm) { fHM = hm; }
    ///@brief Set DeltaPhi selection for dijet
    void setDeltaPhi(double deltaphi) noexcept { fDeltaPhi = deltaphi; }
    ///@brief Set if dataset is MC or not
    void setIsMC(bool isMC) noexcept { fIsMC = isMC; }
    ///@brief Set if it is Pbgoing direction
    void setIsPbGoing() noexcept { fIsPbGoing = true; }
    ///@brief Set if it is pgoing direction
    void setIspGoing() noexcept { fIsPbGoing = false; }
    ///@brief Set Multiplicity Range
    void setMultiplicityRange(double low, double hi)
    {
        fMultiplicityRange[0] = low;
        fMultiplicityRange[1] = hi;
    }
    void setUnfolding(bool unfold, const std::vector<double> ptBins, const std::vector<double> xjBins)
    {
        fDoUnfolding = unfold;
        fPtBins = std::move(ptBins);
        fXjBins = std::move(xjBins);
    }
    ///@brief Set Reader
    void setReader(ForestReader* reader) { fReader = reader; }
    /// @brief Set Center of mass reference frame for pPb
    void setUseCMFrame() noexcept { fUseCMFrame = true; }
    ///@brief Set Eta Boost
    void setEtaBoost(double boost)
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
    void setUseCentralityWeight() noexcept { fUseCentralityWeight = true; }
    /// @brief Set if to use jetpt weight
    void setUseJetPtWeight() noexcept { fUseJetPtWeight = true; }
    ///@brief Set if to use multiplicity weight
    void setUseMultiplicityWeigth() noexcept { fUseMultiplicityWeight = true; }
    ///@brief Set if to use dijet weight
    void setUseDijetWeight() noexcept { fUseDijetWeight = true; }
    ///@brief Set Leading jet pt selection
    void setLeadJetPt(double leadjetpt) noexcept { fLeadJetPtLow = leadjetpt; }
    ///@brief Set Sub leading jet pt selection
    void setSubLeadJetPt(double subleadjetpt) noexcept { fSubLeadJetPtLow = subleadjetpt; }
    ///@brief Set Leading jet eta range
    void setLeadJetEtaRange(double low, double hi)
    {
        fLeadJetEtaRange[0] = low;
        fLeadJetEtaRange[1] = hi;
    }
    ///@brief Set Sub leading jet eta range
    void setSubLeadJetEtaRange(double low, double hi)
    {
        fSubLeadJetEtaRange[0] = low;
        fSubLeadJetEtaRange[1] = hi;
    }
    ///@brief Set if verbose mode is used or not
    void setVerbose() noexcept { fVerbose = true; }
    ///@brief Set Number of events to process
    void setNEventsInSample(long nevents) noexcept { fNEventsInSample = nevents; }
    ///@brief Set Track Pt for specific multiplicty calculation
    void setMinTrkPt(double mintrkpt) noexcept { fMinTrkPt = mintrkpt; }
    ///@brief Set Track Eta Range for specicif multiplicity calculation
    void setTrkEtaRange(double low, double hi)
    {
        fTrkEtaRange[0] = low;
        fTrkEtaRange[1] = hi;
    }
    ///@brief Set which multiplicity type to use for the event selection
    void setMultiplicityType(int multType) noexcept { fMultiplicityType = multType; }
    ///@brief Set Tracking efficiency table
    void setTrackingTable(const std::string& trackingTable) { fTrkEffTable = trackingTable; }
    /// @brief Set Dijet weight table
    /// @param dijetWeightTable Path to the dijet weight table
    void setDijetWeightTable(const std::string& dijetWeightTable) { fDijetWeightTable = dijetWeightTable; }
    /// @brief Set if to calculate in jet multiplicity
    void doInJetMultiplicity() noexcept { fDoInJetMult = true; }
    ///@brief Set Dijet Weight type
    void setDijetWeightType(DijetWeightType type) noexcept { fWeightType = type; }
    ///@brief set underlying event type
    void setUEType(const std::string& UEType) { fUEType = UEType; }
    ///@brief Do tracking closure plots
    void doTrackingClosure() noexcept { fDoTrackingClosures = true; }

    ///@brief Set if to apply vz weight
    void setVzWeight() noexcept { fDoVzWeight = true; }
    ///@brief Set Inclusive Corrected Jet Pt Minimum
    void setInclusiveCorrectedJetPtMin(double minPt) noexcept { fInclusiveCorrectedJetPtMin = minPt; }
    ///@brief Set Inclusive Jet Eta Range
    void setInclusiveJetEtaRange(double low, double high)
    {
        fInclusiveJetEtaRange[0] = low;
        fInclusiveJetEtaRange[1] = high;
    }
    ///@brief Set hihf rewighting
    void useHiHFWeight(bool useWeight = false) noexcept { fUseHiHFWeight = useWeight; }

    void useAveragePt(bool useAveragePt = false) noexcept { fUseAveragePt = useAveragePt; }

   private:
    /// @brief Reco and Corrected Multiplicity calculator with custom track pt and track eta cuts
    /// @param event Event object
    /// @param eventWeight Event weight
    /// @param multiplicityBin Multiplicity bin
    /// @return Returns pair of Reco tracks with custom trackpt and track eta cut and number of
    /// tracks in given trk pt and eta range with tracking efficiency correction. Correction factor
    /// is [1-(fake rate)]/(efficiency)
    std::pair<int, float> RecoCorrectedMultiplicity(const Event* event, const double& eventWeight, const double& multiplicityBin);
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
    std::pair<int, int> GenSubeMultiplicity(const Event* event, const double& eventWeight, const double& multiplicityBin);
    /// @brief Event weight calculator
    /// @param event Event object
    /// @return Returns event level weight which has to be applied to every hisotgram
    double EventWeight(const Event* event);
    /// @brief @brief pPb ptHat weight calculator
    /// @param ptHat pthat value
    /// @return returns weight for given pthat of event in MC
    double pPbptHatWeight(const double& ptHat);
    /// @brief Multiplicity weights
    /// @param multiplicity Multiplicity of the event
    /// @return Array of weights for multiplicity ranges
    double* MultiplicityWeight(const int& multiplicity);
    /// @brief Multiplicity weights
    /// @param multiplicity Multiplicity of the event
    /// @return Array of weights for multiplicity ranges
    double MultiplicityWeight(const double& multiplicity);
    /// @brief Dijet weights
    /// @param ispPb Set to be true if it is pPb dataset. For PbPb dataset it needs is set to be
    /// false
    /// @param leadJetPt Leading jet pt
    /// @param subLeadJetPt Subleading jet pt
    /// @return Dijet weight
    float getDijetWeight(const double& leadJetPt, const double& subLeadJetPt);
    /// @brief Calaulates Delta Phi between two jets
    /// @param phi1 Jet Phi 1
    /// @param phi2 Jet Phi 2
    /// @return returns delta phi between two jets between -pi and pi
    double DeltaPhi(const double& phi1, const double& phi2);
    /// @brief Process all the events
    /// @param event Event object
    void processEvent(const Event* event);
    /// @brief Process Reco Jets
    /// @param event Event object
    void processRecoJets(const Event* event, const double& event_Weight, const double& multiplicityBin, const DijetInfo& recoDijet, const DijetInfo& refDijet);
    /// @brief Process Gen Jets
    /// @param event Event object
    void processGenJets(const Event* event, const double& event_Weight, const double& multiplicityBin, const DijetInfo& genDijet, const DijetInfo& recoDijet);
    /// @brief Calculate Dijet weight
    /// @param recoDijet reco dijet information
    /// @param refDijet ref dijet information
    /// @param genDijet gen dijet information
    /// @return dijet weight
    float CalculateDijetWeight(const DijetInfo& recoDijet, const DijetInfo& refDijet, const DijetInfo& genDijet);
    /// @brief Process Reco Tracks
    /// @param event Event object
    /// @param event_Weight Event weight
    /// @param multWeight Multiplicity weight
    /// @param multiplicityBin Multiplicity bin
    void processRecoTracks(const Event* event, const double& event_Weight, const double& multiplicityBin);
    /// @brief Process Gen Tracks
    /// @param event Event object
    /// @param event_Weight Event weight
    /// @param multWeight Multiplicity weight
    /// @param multiplicityBin Multiplicity bin
    void processGenTracks(const Event* event, const double& event_Weight, const double& multiplicityBin);
    /// @brief Check if all dijet requirements are satisfied
    /// @param leadJetPt Found leading jet pt
    /// @param leadJetEta Found leading jet eta
    /// @param subLeadJetPt Found subleading jet pt
    /// @param subLeadJetEta Found subleading jet eta
    /// @param leadID Leading jet ID
    /// @param subLeadID Subleading jet ID
    /// @return Returns true if all dijet requirements are satisfied
    bool CheckDijet(const float& leadJetPt, const float& leadJetEta, const float& subLeadJetPt, const float& subLeadJetEta, const bool& leadID, const bool& subLeadID);
    /// @brief Xj calculator
    /// @param leadJetPt Leading jet pt
    /// @param subLeadJetPt Subleading jet pt
    /// @return Xj value Xj = Suleading jet pt / Leading Jet pt
    double Asymmetry(const float& leadJetPt, const float& subLeadJetPt);
    /// @brief  Find Multiplicity Bin
    /// @param multiplicity or HiHF energy
    /// @return Multiplicity Bin. 1 for 60-120, 2 for 120-185, 3 for 185-250, 4 for 250-400
    double FindBin(const double& multiplicity, const std::map<double, double>& Bins);
    /// @brief Move to Center of Mass Frame
    /// @param jetEta Jet Eta
    float MoveToCMFrame(const float& jetEta);
    /// @brief Move to Lab Frame
    /// @param jetEta Jet Eta
    float MoveToLabFrame(const float& jetEta);
    /// @brief Set up Dijet weight table
    void SetUpDijetWeight(const std::string& dijetWeightTable);
    ///@brief Set up collision system booleans
    void CollSystem(ForestReader& reader);
    ///@brief Set up weight functions
    void SetUpWeightFunctions();

    ///@brief Get DiJet Region based on jet eta
    ///@param jetEta Jet Eta
    ///@return Returns 1 for Backward , 2 for Mid , 3 for Forward, and -1 for not in any region
    int GetDiJetRegion(const float& jetEta);
    ///@brief Flip Vertex
    ///@param vertexz Vertex Z for pPb
    ///@return Returns the vertexz after flipping it for pPb
    float FlipVertexZ(const float& vertexz);
    ///@brief Get Bin for Dijet Weight
    ///@param binEdges Bin Edges of Histogram
    ///@param value Value to search for in bin edges
    int BinBinarySearch(const std::vector<double>& binEdges, const double& value);
    ///@brief Get jet flavor
    ///@param partonFlavour Parton flavour from jet
    ///@return Returns jet flavor classified as quark jets ->1 and gluon jets -> -1 and unknown
    /// flavor -> 0
    double GetJetFlavor(const int& partonFlavour);
    ///@brief Get HiHFWeight
    ///@param hiHF HiHF value
    ///@return Returns HiHF weight
    double HiHFWeight(const double& hiHF);
    ///@brief Centrality Weight
    ///@param hiBin Centrality Bin
    ///@return Returns Centrality weight
    double CentralityWeight(const int& hiBin);
    ///@brief Random number generator
    ///@return Returns random number
    double uniform01();
    ///@brief Comparing two double values
    ///@param a First double value
    ///@param b Second double value
    ///@return Returns true if two double values are equal within a certain precision
    bool areDoublesEqual(const double& a, const double& b);
    /// @brief Calculates Average jet pt
    /// @param leadpt leading jet pt
    /// @param subleadpt subleading jet pt
    /// @return double value of average jet pt
    double averagePt(const double& leadpt, const double& subleadpt);
    /// @brief get bin indices for the unfolding flattening
    /// @param value xj or pt value
    /// @param edges xj or pt bin edges
    /// @return returns index for xj or pt bin
    int getBinIndex(const double value, const std::vector<double>& edges);
    /// @brief Find the flattened index for unfolding
    /// @param xj Xj value
    /// @param pt pt value
    /// @param xjBins xj bin endges
    /// @param ptBins pt bin edges
    /// @return integer index calculated for flattening of unfolding distribution
    int getFlattenedIndex(const double xj, const double pt, const std::vector<double>& xjBins, const std::vector<double>& ptBins);
    /// @brief  Unfolding function
    /// @param event Event object
    /// @param eventWeight Event weight
    /// @param multBin multiplicity or centrality bin
    /// @param recoDijet Reco Dijet information
    /// @param refDijet Ref Dijet information
    /// @param genDijet Gen Dijet Information
    void unfolding(const Event* event, const double& eventWeight, const double& multBin, const DijetInfo& recoDijet, const DijetInfo& refDijet,
                   const DijetInfo& genDijet);
    /// @brief Finding matched gen jet for given reco jet
    /// @param recoEta reco jet pseudorapidity
    /// @param recoPhi reco jet phi
    /// @param genEta gen jet pseudorapidity
    /// @param genPhi gen jet phi
    /// @return if given gen jet is matched to reco jet
    bool jetMatching(const double& recoEta, const double& recoPhi, const double& genEta, const double& genPhi);
    /// @brief Calculate the leading jet pt weight
    /// @param recoLeadPt reco lead jet pt
    /// @return leading jet pt weight
    float jetPtWeight(const double& recoLeadPt);
    /// @brief weight multiplier for dijet weight tuning
    /// @param xj dijet pt ratios
    /// @return weight multiplier
    double getWeightMultiplier(double xj);

    ///@brief Print debug information
    bool fDebug{false};
    ///@brief Verbose Mode
    bool fVerbose{false};

    // Selections and Ranges
    ///@brief Multiplicity Range
    std::array<double, 2> fMultiplicityRange{10., 600.};
    ///@brief Leading jet pt cut
    double fLeadJetPtLow{50.};
    ///@brief Subleading jet pt cut
    double fSubLeadJetPtLow{30.};
    /// @brief Leading jet eta cut
    std::array<double, 2> fLeadJetEtaRange{-2.1, 2.1};
    ///@brief Subleading jet eta cut
    std::array<double, 2> fSubLeadJetEtaRange{-2.1, 2.1};
    ///@brief Track eta range for specific multiplicity calculation
    std::array<double, 2> fTrkEtaRange{-2.4, 2.4};
    ///@brief Delta Phi selection for dijet
    double fDeltaPhi{5 * M_PI / 6.0};
    ///@brief Minimum Track Pt Cut for specific multiplicity calculation
    double fMinTrkPt{0.4};
    ///@brief Inclusive Corrected JetPt Minimum
    double fInclusiveCorrectedJetPtMin{50.};
    ///@brief Inclusive Jet Eta
    std::array<double, 2> fInclusiveJetEtaRange{-1.6, 1.6};

    // Collison system specific variables
    ///@brief Move to Center of Mass Frame
    bool fUseCMFrame{true};
    ///@brief Eta Boots for pPb
    double fEtaBoost{0.0};
    // Collision system
    CollisionSystem fSystem{CollisionSystem::Unknown};
    ///@brief Colliding system
    std::string fCollSystem{""};
    ///@brief If it it MC
    bool fIsMC{false};
    ///@brief if it is Pb going direction
    bool fIsPbGoing{false};

    // Event Specific selections and variables
    ///@brief Which Multiplicity type to use for event selection.
    /// 0 -> Reco Multiplicity
    /// 1 -> Gen Multiplicity (Only Applicable for MC)
    /// 2 -> Efficinecy corrected multiplicity
    /// 3 -> SubEvent Multiplicity
    int fMultiplicityType{0};
    ///@brief Event counter
    int fEventCounter{0};
    int fCycleCounter{0};
    ///@brief Set Number of events to process
    int fNEventsInSample{10000000};
    ///@brief Tracking efficiency table for PbPb
    std::string fTrkEffTable{""};
    ///@brief Underlying event
    std::string fUEType{""};

    // Config Flags
    ///@brief Use Centrality weight
    bool fUseCentralityWeight{false};
    ///@brief Use Multipicity weight
    bool fUseMultiplicityWeight{false};
    ///@brief Use Dijet Weighting
    bool fUseDijetWeight{false};
    ///@brief Do Injet Multiplicity
    bool fDoInJetMult{false};
    ///@brief Boolean for HiHFWeighting
    bool fUseHiHFWeight{false};
    ///@brief Boolean for using averagept
    bool fUseAveragePt{false};
    ///@brief Do Tracking Closures
    bool fDoTrackingClosures{false};
    ///@brief Do Vz weight
    bool fDoVzWeight{false};
    ///@brief Boolean for Unfolding
    bool fDoUnfolding{false};
    ///@brief Use jetpt weight
    bool fUseJetPtWeight{false};

    /// Dijet Weighting
    ///@brief Dijet Weight
    float fDijetWeight{1.0f};
    /// @brief Dijet weight type
    DijetWeightType fWeightType{DijetWeightType::None};
    ///@brief Dijet weight table PYTHIA at 8 TeV
    std::string fDijetWeightTable{""};
    ///@brief Bin Edges for DijetWeight Histogram
    std::vector<double> fXBinEdges;
    ///@brief Bin Edges for DijetWeight Histogram
    std::vector<double> fYBinEdges;
    ///@brief Dijet Weights Holder
    std::vector<double> fBinContent;
    ///@brief Number of Bins on X Axis
    int fXBinCount{0};
    ///@brief Number of Bins on Y Axis
    int fYBinCount{0};
    ///@brief Dijet Weight histograms
    TH2* hDijetWeight{nullptr};

    // Unfolding Bins
    /// @brief Pt bin boundries
    std::vector<double> fPtBins;
    ///@brief Xj bins boundries
    std::vector<double> fXjBins;

    // Manually managed memory pointers
    ///@brief Histogram Manager
    HistoManagerDiJet* fHM{nullptr};
    ///@brief Forest Reader
    ForestReader* fReader{nullptr};

    /// Automatically managed memory pointers for easy cleanup
    ///@brief Tracking efficiency for PbPb
    std::unique_ptr<TrkEff2018PbPb> fTrkEffPbPb;
    ///@brief Tracking efficiency for pPb
    std::unique_ptr<TrkEfficiency2016pPb> fTrkEffpPb;
    ///@brief Dijet Weight file
    std::unique_ptr<TFile> fDijetWeightFile;
    ///@brief Vertex Z weight function
    std::unique_ptr<TF1> fVertexZWeight;
    ///@brief Holds multiplicity weight functions
    std::array<std::unique_ptr<TF1>, 4> fMultWeightFunctions;
    ///@brief Centrality reweight
    std::array<std::unique_ptr<TF1>, 2> fCentWeightFunctions;
    ///@brief Weight function for HIHF
    std::unique_ptr<TF1> fHiHFWeight;
    /// @brief JetPt Weight Function
    std::unique_ptr<TF1> fJetPtWeight;

    ///@brief Randomnumber gneneration
    static constexpr uint64_t SEED = 1729;
    std::mt19937_64 gen_{SEED};
    std::uniform_real_distribution<double> dist_{0.0, 1.0};

    ///@brief Double comparison precision value
    static constexpr double fEpsilon = 1e-6;

    ClassDef(DiJetAnalysis, 0)
};

#endif
