/**
 * @file HistoManagerDiJet.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for Dijet Analysis
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HistoManagerDiJet_h
#define HistoManagerDiJet_h

// Jet Analysis headers

#include "BaseHistoManager.h"

// ROOT Headers

#include "ForestReader.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THnSparse.h"
#include "TList.h"
#include "TMath.h"
#include "TObject.h"
#include "TProfile.h"
#include "TString.h"

class HistoManagerDiJet : public BaseHistoManager
{
   public:
    ///@brief Constructor
    HistoManagerDiJet();
    ///@brief Destructor
    virtual ~HistoManagerDiJet();

    enum class CollisionSystem
    {
        Unknown,
        pp,
        pPb,
        PbPb,
        OO
    };
    ///@brief Initialize Histograms
    void init();
    ///@brief Use MC histograms
    void setIsMC(bool isMC) noexcept { fIsMC = isMC; }
    ///@brief Projection histograms
    void projectHistograms();
    ///@brief Write all historgams to output file
    void writeOutput();
    ///@brief Histogram manager report
    void report();
    ///@brief Set Multiplicity bins
    ///@param bins vector of bin boundaries
    void setMultiplicityBins(const std::vector<double>& bins) { fMultiplicityBins = std::move(bins); }
    /// @brief set Forward Calorimeter energy bins
    /// @param bins vector of bin boundaries
    void setHiHFEnergyBins(const std::vector<double>& bins) { fHiHFEnergyBins = std::move(bins); }
    /// @brief Set Pt bins. It could be average pt bins or leading pt bins
    /// @param bins vector of pt bin boundaries
    void setPtBins(const std::vector<double>& bins) { fPtBins = std::move(bins); }
    /// @brief set xj bins
    /// @param bins xj bin boundaries vector
    void setXjBins(const std::vector<double>& bins) { fXjBins = std::move(bins); }

    ///@brief Set Collision System
    void setForestReader(ForestReader* reader) { fReader = reader; }

    TH1D* hPtHat{nullptr};
    TH1D* hPtHat_W{nullptr};
    TH1D* hHiBin{nullptr};
    TH1D* hHiBin_W{nullptr};
    TH1D* hVz{nullptr};
    TH1D* hVz_W{nullptr};
    TH1D* hNEventsInMult{nullptr};
    TH1D* hRecoMultiplicity_W{nullptr};
    TH1D* hCorrectedMultiplicity_W{nullptr};
    TH1D* hGenMultiplicity_W{nullptr};
    TH1D* hSubEventMultiplicity_W{nullptr};
    TH1D* hSelectedMultiplicity_W{nullptr};
    TH1D* hHiHF_PF{nullptr};
    TH1D* hHiHF_PF_W{nullptr};

    TH2D* hInJetMultiplicity_W{nullptr};
    TH2D* hGenInJetMultiplicity_W{nullptr};

    THnSparseD* hMultiplicities{nullptr};
    THnSparseD* hMultiplicities_W{nullptr};
    THnSparseD* hMultiplicities_DiJet_W{nullptr};

    THnSparseD* hInclusiveUncorrectedRecoJets{nullptr};
    THnSparseD* hInclusiveUncorrectedRecoJets_W{nullptr};
    THnSparseD* hInclusiveRecoJetsLabFrame{nullptr};
    THnSparseD* hInclusiveRecoJetsLabFrame_W{nullptr};
    THnSparseD* hInclusiveRecoJetsCMFrame{nullptr};
    THnSparseD* hInclusiveRecoJetsCMFrame_W{nullptr};
    THnSparseD* hSelectedInclusiveRecoJetsMidRapidity_W{nullptr};

    THnSparseD* hJetFlavorFractions_W{nullptr};

    THnSparseD* hInclusiveRefJetsLabFrame{nullptr};
    THnSparseD* hInclusiveRefJetsLabFrame_W{nullptr};
    THnSparseD* hInclusiveRefJetsCMFrame{nullptr};
    THnSparseD* hInclusiveRefJetsCMFrame_W{nullptr};
    THnSparseD* hSelectedInclusiveRefJetsMidRapidity_W{nullptr};

    THnSparseD* hInclusiveGenJetsLabFrame{nullptr};
    THnSparseD* hInclusiveGenJetsLabFrame_W{nullptr};
    THnSparseD* hInclusiveGenJetsCMFrame{nullptr};
    THnSparseD* hInclusiveGenJetsCMFrame_W{nullptr};
    THnSparseD* hSelectedInclusiveGenJetsMidRapidity_W{nullptr};

    THnSparseD* hLeadSubLeadJets{nullptr};
    THnSparseD* hLeadSubLeadJets_W{nullptr};
    THnSparseD* hRefLeadRefSubLeadJets{nullptr};
    THnSparseD* hRefLeadRefSubLeadJets_W{nullptr};
    THnSparseD* hGenLeadGenSubLeadJets{nullptr};
    THnSparseD* hGenLeadGenSubLeadJets_W{nullptr};
    THnSparseD* hLeadSubLeadJets_MidRapidity_W{nullptr};
    THnSparseD* hGenLeadGenSubLeadJets_MidRapidity_W{nullptr};
    THnSparseD* hRefLeadRefSubLeadJets_MidRapidity_W{nullptr};
    THnSparseD* hLeadSubLeadJets_WithDijet_W{nullptr};
    THnSparseD* hGenLeadGenSubLeadJets_WithDijet_W{nullptr};
    THnSparseD* hRefLeadRefSubLeadJets_WithDijet_W{nullptr};
    THnSparseD* hLeadSubLeadJets_WithDijet_DiJetW{nullptr};
    THnSparseD* hGenLeadGenSubLeadJets_WithDijet_DiJetW{nullptr};
    THnSparseD* hRefLeadRefSubLeadJets_WithDijet_DiJetW{nullptr};

    TH2D* hLeadPtvsSubLeadPt_DiJetW{nullptr};
    TH2D* hLeadPtvsSubLeadPt_PtHatW{nullptr};
    TH2D* hRefLeadPtvsRefSubLeadPt_DiJetW{nullptr};
    TH2D* hRefLeadPtvsRefSubLeadPt_PtHatW{nullptr};
    TH2D* hRefLeadPtVsRefSubLeadPtMatched_PtHatW{nullptr};
    TH2D* hRefLeadPtVsRefSubLeadPtMatched_DiJetW{nullptr};
    TH2D* hGenLeadPtvsGenSubLeadPt_DiJetW{nullptr};
    TH2D* hGenLeadPtvsGenSubLeadPt_PtHatW{nullptr};

    TH2D* hInclusiveRecoJetPtVsEtaLabFrame_W{nullptr};
    TH2D* hInclusiveRecoJetPtVsEtaCMFrame_W{nullptr};
    TH2D* hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W{nullptr};
    TH2D* hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W{nullptr};

    TH3D* hRecoJES_W{nullptr};
    TH3D* hRefJES_W{nullptr};
    TH3D* hRecoJES_Eta_W{nullptr};
    TH3D* hRefJES_Eta_W{nullptr};
    TH3D* hRecoJES_Eta_Pt100_W{nullptr};
    TH3D* hRefJES_Eta_Pt100_W{nullptr};
    TH3D* hRecoJES_Eta_Pt120_W{nullptr};
    TH3D* hRefJES_Eta_Pt120_W{nullptr};

    TH2D* hGenLeadingVsGenSubLeading_WO_DiJet_W{nullptr};

    THnSparseD* hRecoQuenching_W{nullptr};
    THnSparseD* hGenQuenching_W{nullptr};
    THnSparseD* hRecoQuenching_WithDijet_W{nullptr};
    THnSparseD* hGenQuenching_WithDijet_W{nullptr};

    TH2D* hMultVsXj_HiHFW{nullptr};
    TH2D* hHiHFVsXj_W{nullptr};
    TH2D* hHiHFVsXj_HiHFW{nullptr};

    TH3D* hMultVsXj_W{nullptr};
    TH3D* hMultVsXj_DiJetW{nullptr};
    TH3D* hMultVsMatchedRefXj_W{nullptr};
    TH3D* hMultVsMatchedRefXj_DiJetW{nullptr};
    TH3D* hMultVsUnflippedMatchedRefXj_W{nullptr};
    TH3D* hMultVsUnflippedMatchedRefXj_DiJetW{nullptr};
    TH3D* hMultVsRefXj_W{nullptr};
    TH3D* hMultVsRefXj_DiJetW{nullptr};
    TH3D* hMultVsMatchedRecoXj_W{nullptr};
    TH3D* hMultVsUnflippedMatchedRecoXj_W{nullptr};
    TH3D* hMultVsGenXj_W{nullptr};
    TH3D* hMultVsGenXj_DiJetW{nullptr};

    TH1D* hVzWithDijet_W{nullptr};
    TH1D* hDeltaPhi_W{nullptr};
    TH1D* hDeltaPhi_WithDiJet_W{nullptr};
    TH1D* hRefDeltaPhi_W{nullptr};
    TH1D* hRefDeltaPhi_WithDiJet_W{nullptr};
    TH1D* hGenDeltaPhi_W{nullptr};
    TH1D* hGenDeltaPhi_WithDiJet_W{nullptr};
    TH1I* hNDijetEvent{nullptr};
    TH1D* hNGenDijetEvent{nullptr};

    TH3D* hTrackPtVsEta{nullptr};
    TH3D* hTrackPtVsEta_W{nullptr};
    TH3D* hGenTrackPtVsEta{nullptr};
    TH3D* hGenTrackPtVsEta_W{nullptr};
    TH3D* hTrackPtVsEtaCorrected{nullptr};
    TH3D* hTrackPtVsEtaCorrected_W{nullptr};
    THnSparseD* hRecoTracks{nullptr};
    THnSparseD* hRecoTracks_W{nullptr};
    THnSparseD* hRecoTracks_Pt1_W{nullptr};
    THnSparseD* hGenTracks{nullptr};
    THnSparseD* hGenTracks_W{nullptr};
    THnSparseD* hGenTracks_Pt1_W{nullptr};

    TH2D* hHiHFPlusVsHiHFMinus{nullptr};
    TH2D* hHiHFPlusVsHiHFMinus_W{nullptr};
    TH2D* hHiHFPlusVsHiHFMinus_WithDijet_W{nullptr};

    TH2D *hHiHFPlusVsMultiplicity_W{nullptr}, *hHiHFMinusVsMultiplicity_W{nullptr};
    TH2D *hHiHFPlusVsMultiplicity_WithDijet_W{nullptr}, *hHiHFMinusVsMultiplicity_WithDijet_W{nullptr};

    THnSparseD* hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W{nullptr};
    THnSparseD* hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W{nullptr};
    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W{nullptr};
    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicity_FakeJets_W{nullptr};
    TH2D* hMultVsFakeRefXjToBeUnfolded_W{nullptr};
    TH2D* hMultVsFakeRecoXjToBeUnfolded_W{nullptr};
    TH2D* hMultVsFakeRecoXjForTesting_W{nullptr};
    TH2D* hMultVsFakeRefXjForTesting_W{nullptr};
    TH2D* hMultVsMissingRefXjToBeUnfolded_W{nullptr};
    TH2D* hMultVsMissingRefXjForTesting_W{nullptr};
    TH3D* hFakeLeadXj_W{nullptr};
    TH3D* hFakeSubLeadXj_W{nullptr};

    TH3D* hResponseMatrix_W{nullptr};
    TH3D* hResponseMatrixA_W{nullptr};
    TH3D* hResponseMatrixB_W{nullptr};

    TH2D* hTotalReco_W{nullptr};
    TH2D* hTotalRecoA_W{nullptr};
    TH2D* hTotalRecoB_W{nullptr};

    TH2D* hTotalTruth_W{nullptr};
    TH2D* hTotalTruthA_W{nullptr};
    TH2D* hTotalTruthB_W{nullptr};

    TH2D* hMatchedReco_W{nullptr};
    TH2D* hMatchedRecoA_W{nullptr};
    TH2D* hMatchedRecoB_W{nullptr};

    TH2D* hMatchedGen_W{nullptr};
    TH2D* hMatchedGenA_W{nullptr};
    TH2D* hMatchedGenB_W{nullptr};

    TH2D* hLeadPtVsRecoXj_W{nullptr};
    TH2D* hLeadPtVsRefXj_W{nullptr};
    TH2D* hLeadPtVsGenXj_W{nullptr};

    TH1D* hAverageRecoPt_W{nullptr};
    TH1D* hAverageGenPt_W{nullptr};

    TH2D* hHiBinVsMultiplicity_W{nullptr};
    TH2D* hHiBinVsCorrectedMultiplicity_W{nullptr};

   private:
    void setCollisionSystem(const ForestReader& reader);
    bool fIsMC{false};
    CollisionSystem fCollSystem{CollisionSystem::Unknown};

    ForestReader* fReader{nullptr};

    std::vector<double> fMultiplicityBins{};
    std::vector<double> fHiHFEnergyBins{};
    std::vector<double> fPtBins{};
    std::vector<double> fXjBins{};

    // Projection Histograms
    TH1D* hInclusiveRecoJetPt{nullptr};
    TH1D* hInclusiveRecoJetPt_W{nullptr};
    TH1D* hSelectedInclusiveRecoJetPt_MidRapidity_W{nullptr};
    TH1D* hInclusiveRecoJetEtaCMFrame{nullptr};
    TH1D* hInclusiveRecoJetEtaCMFrame_W{nullptr};
    TH1D* hInclusiveRecoJetEtaLabFrame{nullptr};
    TH1D* hInclusiveRecoJetEtaLabFrame_W{nullptr};
    TH1D* hSelectedInclusiveRecoJetEtaMidRapidity_W{nullptr};

    TH1D* hInclusiveGenJetPt{nullptr};
    TH1D* hInclusiveGenJetPt_W{nullptr};
    TH1D* hSelectedInclusiveGenJetPt_MidRapidity_W{nullptr};
    TH1D* hInclusiveGenJetEtaCMFrame{nullptr};
    TH1D* hInclusiveGenJetEtaCMFrame_W{nullptr};
    TH1D* hInclusiveGenJetEtaLabFrame{nullptr};
    TH1D* hInclusiveGenJetEtaLabFrame_W{nullptr};
    TH1D* hSelectedInclusiveGenJetEtaMidRapidity_W{nullptr};

    TH1D* hInclusiveRefJetPt{nullptr};
    TH1D* hInclusiveRefJetPt_W{nullptr};
    TH1D* hSelectedInclusiveRefJetPt_MidRapidity_W{nullptr};

    TH1D* hLeadingRecoJetPt{nullptr};
    TH1D* hLeadingRecoJetPt_W{nullptr};
    TH1D* hSubLeadingRecoJetPt{nullptr};
    TH1D* hSubLeadingRecoJetPt_W{nullptr};
    TH1D* hLeadingGenJetPt{nullptr};
    TH1D* hLeadingGenJetPt_W{nullptr};
    TH1D* hSubLeadingGenJetPt{nullptr};
    TH1D* hSubLeadingGenJetPt_W{nullptr};
    TH1D* hLeadingRefJetPt{nullptr};
    TH1D* hLeadingRefJetPt_W{nullptr};
    TH1D* hSubLeadingRefJetPt{nullptr};
    TH1D* hSubLeadingRefJetPt_W{nullptr};

    TH1D* hLeadingRecoJetPtWithDijet_W{nullptr};
    TH1D* hLeadingGenJetPtWithDijet_W{nullptr};
    TH1D* hLeadingRefJetPtWithDijet_W{nullptr};
    TH1D* hSubLeadingRecoJetPtWithDijet_W{nullptr};
    TH1D* hSubLeadingGenJetPtWithDijet_W{nullptr};
    TH1D* hSubLeadingRefJetPtWithDijet_W{nullptr};

    TH1D* hLeadingRecoJetPtWithDijet_DiJetW{nullptr};
    TH1D* hLeadingGenJetPtWithDijet_DiJetW{nullptr};
    TH1D* hLeadingRefJetPtWithDijet_DiJetW{nullptr};
    TH1D* hSubLeadingRecoJetPtWithDijet_DiJetW{nullptr};
    TH1D* hSubLeadingGenJetPtWithDijet_DiJetW{nullptr};
    TH1D* hSubLeadingRefJetPtWithDijet_DiJetW{nullptr};

    TH1D* hXj_C0_W{nullptr};
    TH1D* hXj_C0_DiJetW{nullptr};
    TH1D* hGenXj_C0_W{nullptr};
    TH1D* hGenXj_C0_DiJetW{nullptr};

    TH1D* hHiHFPlus{nullptr};
    TH1D* hHiHFPlus_W{nullptr};
    TH1D* hHiHFMinus{nullptr};
    TH1D* hHiHFMinus_W{nullptr};
    TH1D* hHiHFPlus_WithDijet_W{nullptr};
    TH1D* hHiHFMinus_WithDijet_W{nullptr};

    std::vector<TH1D*> hXj_Projection_W{};
    std::vector<TH1D*> hXj_ProjectionHiHF_W{};
    std::vector<TH1D*> hXj_Projection_HiHFW{};
    std::vector<TH1D*> hXj_Projection_DiJetW{};
    std::vector<TH1D*> hXj_ProjectionHiHF_HiHFW{};
    std::vector<TH1D*> hGenXj_Projection_W{};
    std::vector<TH1D*> hGenXj_Projection_DiJetW{};
    std::vector<TH1D*> hRefXj_Projection_W{};
    std::vector<TH1D*> hRefXj_Projection_DiJetW{};
    std::vector<TH1D*> hMatchedRefXj_Projection_W{};
    std::vector<TH1D*> hMatchedRefXj_Projection_DiJetW{};

    // static constexpr double HiHFEnergyBins[] = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 120.0, 150.0, 1000.0};

    ClassDef(HistoManagerDiJet, 1)
};

#endif