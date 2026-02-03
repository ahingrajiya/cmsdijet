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

    ///@brief Initialize Histograms
    void init();
    ///@brief Use MC histograms
    void setIsMC(const Bool_t& isMC) { fIsMC = isMC; }
    ///@brief Projection histograms
    void projectHistograms();
    ///@brief Write all historgams to output file
    void writeOutput();
    ///@brief Histogram manager report
    void report();
    ///@brief Set Multiplicity bins
    void setMultiplicityBins(const std::vector<std::pair<Double_t, Double_t>>& bins)
    {
        fMultiplicityBins.clear();
        fMultiplicityBinThresholds.clear();
        for (const auto& [threshold, value] : bins)
        {
            fMultiplicityBins.push_back(static_cast<float>(value));
            fMultiplicityBinThresholds.push_back(static_cast<int>(threshold));
        }
    }

    void setHiHFEnergyBins(const std::vector<std::pair<Double_t, Double_t>>& bins)
    {
        fHiHFEnergyBins.clear();
        fHiHFEnergyBinThresholds.clear();
        for (const auto& [threshold, value] : bins)
        {
            fHiHFEnergyBins.push_back(static_cast<float>(value));
            fHiHFEnergyBinThresholds.push_back(static_cast<int>(threshold));
        }
    }
    ///@brief Set Collision System
    void setCollSystem(const TString& collSystem) { fCollSystem = collSystem; }

    TH1D* hPtHat;
    TH1D* hPtHat_W;
    TH1D* hHiBin;
    TH1D* hHiBin_W;
    TH1D* hVz;
    TH1D* hVz_W;
    TH1D* hNEventsInMult;
    TH1D* hRecoMultiplicity_W;
    TH1D* hCorrectedMultiplicity_W;
    TH1D* hGenMultiplicity_W;
    TH1D* hSubEventMultiplicity_W;
    TH1D* hSelectedMultiplicity_W;
    TH1D* hHiHF_PF;
    TH1D* hHiHF_PF_W;

    TH2D* hInJetMultiplicity_W;
    TH2D* hGenInJetMultiplicity_W;

    THnSparseD* hMultiplicities;
    THnSparseD* hMultiplicities_W;
    THnSparseD* hMultiplicities_DiJet_W;

    THnSparseD* hInclusiveUncorrectedRecoJets;
    THnSparseD* hInclusiveUncorrectedRecoJets_W;
    THnSparseD* hInclusiveRecoJetsLabFrame;
    THnSparseD* hInclusiveRecoJetsLabFrame_W;
    THnSparseD* hInclusiveRecoJetsCMFrame;
    THnSparseD* hInclusiveRecoJetsCMFrame_W;
    THnSparseD* hSelectedInclusiveRecoJetsMidRapidity_W;

    THnSparseD* hJetFlavorFractions_W;

    THnSparseD* hInclusiveRefJetsLabFrame;
    THnSparseD* hInclusiveRefJetsLabFrame_W;
    THnSparseD* hInclusiveRefJetsCMFrame;
    THnSparseD* hInclusiveRefJetsCMFrame_W;
    THnSparseD* hSelectedInclusiveRefJetsMidRapidity_W;

    THnSparseD* hInclusiveGenJetsLabFrame;
    THnSparseD* hInclusiveGenJetsLabFrame_W;
    THnSparseD* hInclusiveGenJetsCMFrame;
    THnSparseD* hInclusiveGenJetsCMFrame_W;
    THnSparseD* hSelectedInclusiveGenJetsMidRapidity_W;

    THnSparseD* hLeadSubLeadJets;
    THnSparseD* hLeadSubLeadJets_W;
    THnSparseD* hRefLeadRefSubLeadJets;
    THnSparseD* hRefLeadRefSubLeadJets_W;
    THnSparseD* hGenLeadGenSubLeadJets;
    THnSparseD* hGenLeadGenSubLeadJets_W;
    THnSparseD* hLeadSubLeadJets_MidRapidity_W;
    THnSparseD* hGenLeadGenSubLeadJets_MidRapidity_W;
    THnSparseD* hRefLeadRefSubLeadJets_MidRapidity_W;
    THnSparseD* hLeadSubLeadJets_WithDijet_W;
    THnSparseD* hGenLeadGenSubLeadJets_WithDijet_W;
    THnSparseD* hRefLeadRefSubLeadJets_WithDijet_W;
    THnSparseD* hLeadSubLeadJets_WithDijet_DiJetW;
    THnSparseD* hGenLeadGenSubLeadJets_WithDijet_DiJetW;
    THnSparseD* hRefLeadRefSubLeadJets_WithDijet_DiJetW;

    TH2D* hLeadPtvsSubLeadPt_DiJetW;
    TH2D* hLeadPtvsSubLeadPt_PtHatW;
    TH2D* hRefLeadPtvsRefSubLeadPt_DiJetW;
    TH2D* hRefLeadPtvsRefSubLeadPt_PtHatW;
    TH2D* hRefLeadPtVsRefSubLeadPtMatched_PtHatW;
    TH2D* hRefLeadPtVsRefSubLeadPtMatched_DiJetW;
    TH2D* hGenLeadPtvsGenSubLeadPt_DiJetW;
    TH2D* hGenLeadPtvsGenSubLeadPt_PtHatW;

    TH2D* hInclusiveRecoJetPtVsEtaLabFrame_W;
    TH2D* hInclusiveRecoJetPtVsEtaCMFrame_W;
    TH2D* hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W;
    TH2D* hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W;

    TH3D* hRecoJES_W;
    TH3D* hRefJES_W;
    TH3D* hRecoJES_Eta_W;
    TH3D* hRefJES_Eta_W;
    TH3D* hRecoJES_Eta_Pt100_W;
    TH3D* hRefJES_Eta_Pt100_W;
    TH3D* hRecoJES_Eta_Pt120_W;
    TH3D* hRefJES_Eta_Pt120_W;

    TH2D* hGenLeadingVsGenSubLeading_WO_DiJet_W;

    THnSparseD* hRecoQuenching_W;
    THnSparseD* hGenQuenching_W;
    TH2D* hMultVsXj_W;
    TH2D* hMultVsXj_DiJetW;
    TH2D* hMultVsXj_HiHFW;
    TH2D* hHiHFVsXj_W;
    TH2D* hHiHFVsXj_HiHFW;
    TH2D* hMultVsRefXj_W;
    TH2D* hMultVsMatchedRefXj_W;
    TH2D* hMultVsRefXj_DiJetW;
    TH2D* hMultVsMatchedRefXj_DiJetW;
    TH2D* hMultVsGenXj_W;
    TH2D* hMultVsGenXj_DiJetW;
    TH1D* hVzWithDijet_W;
    TH1D* hDeltaPhi_W;
    TH1D* hDeltaPhi_WithDiJet_W;
    TH1D* hGenDeltaPhi_W;
    TH1D* hGenDeltaPhi_WithDiJet_W;
    TH1I* hNDijetEvent;
    TH1D* hNGenDijetEvent;

    TH3D* hTrackPtVsEta;
    TH3D* hTrackPtVsEta_W;
    TH3D* hGenTrackPtVsEta;
    TH3D* hGenTrackPtVsEta_W;
    TH3D* hTrackPtVsEtaCorrected;
    TH3D* hTrackPtVsEtaCorrected_W;
    THnSparseD* hRecoTracks;
    THnSparseD* hRecoTracks_W;
    THnSparseD* hRecoTracks_Pt1_W;
    THnSparseD* hGenTracks;
    THnSparseD* hGenTracks_W;
    THnSparseD* hGenTracks_Pt1_W;

    TH2D* hHiHFPlusVsHiHFMinus;
    TH2D* hHiHFPlusVsHiHFMinus_W;
    TH2D* hHiHFPlusVsHiHFMinus_WithDijet_W;

    TH2D *hHiHFPlusVsMultiplicity_W, *hHiHFMinusVsMultiplicity_W;
    TH2D *hHiHFPlusVsMultiplicity_WithDijet_W, *hHiHFMinusVsMultiplicity_WithDijet_W;

    TH2D* hRefLeadRefSubLead_W;
    TH2D* hGenLeadGenSubLead_W;

    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W;
    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W;
    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W;
    TH3D* hUnfoldingRefXjVsRecoXjVsMultiplicity_Unflipped_W;
    TH2D* hMultVsRecoXjToBeUnfolded_W;
    TH2D* hMultVsRecoXjForTesting_W;
    TH2D* hMultVsRefXjToBeUnfolded_W;
    TH2D* hMultVsRefXjForTesting_W;

   private:
    Bool_t fIsMC;

    std::vector<float> fMultiplicityBins;
    std::vector<int> fMultiplicityBinThresholds;
    std::vector<float> fHiHFEnergyBins;
    std::vector<int> fHiHFEnergyBinThresholds;
    TString fCollSystem;

    // Projection Histograms
    TH1D* hInclusiveRecoJetPt;
    TH1D* hInclusiveRecoJetPt_W;
    TH1D* hSelectedInclusiveRecoJetPt_MidRapidity_W;
    TH1D* hInclusiveRecoJetEtaCMFrame;
    TH1D* hInclusiveRecoJetEtaCMFrame_W;
    TH1D* hInclusiveRecoJetEtaLabFrame;
    TH1D* hInclusiveRecoJetEtaLabFrame_W;
    TH1D* hSelectedInclusiveRecoJetEtaMidRapidity_W;

    TH1D* hInclusiveGenJetPt;
    TH1D* hInclusiveGenJetPt_W;
    TH1D* hSelectedInclusiveGenJetPt_MidRapidity_W;
    TH1D* hInclusiveGenJetEtaCMFrame;
    TH1D* hInclusiveGenJetEtaCMFrame_W;
    TH1D* hInclusiveGenJetEtaLabFrame;
    TH1D* hInclusiveGenJetEtaLabFrame_W;
    TH1D* hSelectedInclusiveGenJetEtaMidRapidity_W;

    TH1D* hInclusiveRefJetPt;
    TH1D* hInclusiveRefJetPt_W;
    TH1D* hSelectedInclusiveRefJetPt_MidRapidity_W;

    TH1D* hLeadingRecoJetPt;
    TH1D* hLeadingRecoJetPt_W;
    TH1D* hSubLeadingRecoJetPt;
    TH1D* hSubLeadingRecoJetPt_W;
    TH1D* hLeadingGenJetPt;
    TH1D* hLeadingGenJetPt_W;
    TH1D* hSubLeadingGenJetPt;
    TH1D* hSubLeadingGenJetPt_W;
    TH1D* hLeadingRefJetPt;
    TH1D* hLeadingRefJetPt_W;
    TH1D* hSubLeadingRefJetPt;
    TH1D* hSubLeadingRefJetPt_W;

    TH1D* hLeadingRecoJetPtWithDijet_W;
    TH1D* hLeadingGenJetPtWithDijet_W;
    TH1D* hLeadingRefJetPtWithDijet_W;
    TH1D* hSubLeadingRecoJetPtWithDijet_W;
    TH1D* hSubLeadingGenJetPtWithDijet_W;
    TH1D* hSubLeadingRefJetPtWithDijet_W;

    TH1D* hLeadingRecoJetPtWithDijet_DiJetW;
    TH1D* hLeadingGenJetPtWithDijet_DiJetW;
    TH1D* hLeadingRefJetPtWithDijet_DiJetW;
    TH1D* hSubLeadingRecoJetPtWithDijet_DiJetW;
    TH1D* hSubLeadingGenJetPtWithDijet_DiJetW;
    TH1D* hSubLeadingRefJetPtWithDijet_DiJetW;

    TH1D* hXj_C0_W;
    TH1D* hXj_C0_DiJetW;
    TH1D* hGenXj_C0_W;
    TH1D* hGenXj_C0_DiJetW;

    TH1D* hHiHFPlus;
    TH1D* hHiHFPlus_W;
    TH1D* hHiHFMinus;
    TH1D* hHiHFMinus_W;
    TH1D* hHiHFPlus_WithDijet_W;
    TH1D* hHiHFMinus_WithDijet_W;

    std::vector<TH1D*> hXj_Projection_W;
    std::vector<TH1D*> hXj_ProjectionHiHF_W;
    std::vector<TH1D*> hXj_Projection_HiHFW;
    std::vector<TH1D*> hXj_Projection_DiJetW;
    std::vector<TH1D*> hXj_ProjectionHiHF_HiHFW;
    std::vector<TH1D*> hGenXj_Projection_W;
    std::vector<TH1D*> hGenXj_Projection_DiJetW;
    std::vector<TH1D*> hRefXj_Projection_W;
    std::vector<TH1D*> hRefXj_Projection_DiJetW;
    std::vector<TH1D*> hMatchedRefXj_Projection_W;
    std::vector<TH1D*> hMatchedRefXj_Projection_DiJetW;

    // static constexpr double HiHFEnergyBins[] = {0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 70.0, 90.0, 120.0, 150.0, 1000.0};

    ClassDef(HistoManagerDiJet, 1)
};
#endif