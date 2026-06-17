#ifndef HIST_READER_H
#define HIST_READER_H

#include <iostream>
#include <string>

#include "TDirectory.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1I.h"
#include "TH2D.h"
#include "TH3D.h"
#include "THnSparse.h"

class HistReader
{
   private:
    template <typename T>
    void Load(T*& ptr, const char* name)
    {
        gDirectory->GetObject(name, ptr);
    }

   public:
    struct EventsGroup
    {
        TH1D *hVz = nullptr, *hRecoMultiplicity_W = nullptr, *hCorrectedMultiplicity_W = nullptr, *hSelectedMultiplicity_W = nullptr;
        TH1D *hHiBin = nullptr, *hHiBin_W = nullptr, *hHiHF_PF = nullptr, *hHiHF_PF_W = nullptr, *hPtHat = nullptr, *hSubEventMultiplicity_W = nullptr;
        TH1D *hGenMultiplicity_W = nullptr, *hNEventsInMult = nullptr, *hVz_W = nullptr, *hVzWithDijet_W = nullptr, *hPtHat_W = nullptr;
        TH2D *hInJetMultiplicity_W = nullptr, *hHiHFPlusVsHiHFMinus = nullptr, *hHiHFPlusVsHiHFMinus_W = nullptr, *hHiHFPlusVsHiHFMinus_WithDijet_W = nullptr;
        TH2D *hHiHFPlusVsMultiplicity_W = nullptr, *hHiHFMinusVsMultiplicity_W = nullptr, *hHiHFPlusVsMultiplicity_WithDijet_W = nullptr;
        TH2D *hHiHFMinusVsMultiplicity_WithDijet_W = nullptr, *hHiBinVsMultiplicity_W = nullptr, *hHiBinVsCorrectedMultiplicity_W = nullptr,
             *hGenInJetMultiplicity_W = nullptr;
        THnSparseD *hMultiplicities = nullptr, *hMultiplicities_W = nullptr, *hMultiplicities_DiJet_W = nullptr;
    } Events;

    struct JetsGroup
    {
        THnSparseD *hInclusiveUncorrectedRecoJets = nullptr, *hInclusiveUncorrectedRecoJets_W = nullptr, *hInclusiveRecoJetsCMFrame = nullptr;
        THnSparseD *hInclusiveRecoJetsCMFrame_W = nullptr, *hSelectedInclusiveRecoJetsMidRapidity_W = nullptr, *hJetFlavorFractions_W = nullptr;
        THnSparseD *hInclusiveRecoJetsLabFrame = nullptr, *hInclusiveRecoJetsLabFrame_W = nullptr, *hInclusiveGenJetsCMFrame = nullptr;
        THnSparseD *hInclusiveGenJetsCMFrame_W = nullptr, *hInclusiveRefJetsCMFrame = nullptr, *hInclusiveRefJetsCMFrame_W = nullptr;
        THnSparseD *hSelectedInclusiveGenJetsMidRapidity_W = nullptr, *hSelectedInclusiveRefJetsMidRapidity_W = nullptr;
        THnSparseD *hInclusiveGenJetsLabFrame = nullptr, *hInclusiveGenJetsLabFrame_W = nullptr, *hInclusiveRefJetsLabFrame = nullptr,
                   *hInclusiveRefJetsLabFrame_W = nullptr;
        THnSparseD *hLeadSubLeadJets = nullptr, *hLeadSubLeadJets_W = nullptr, *hLeadSubLeadJets_MidRapidity_W = nullptr, *hLeadSubLeadJets_WithDijet_W = nullptr;
        THnSparseD *hLeadSubLeadJets_WithDijet_DiJetW = nullptr, *hGenLeadGenSubLeadJets = nullptr, *hGenLeadGenSubLeadJets_W = nullptr,
                   *hGenLeadGenSubLeadJets_MidRapidity_W = nullptr;
        THnSparseD *hRefLeadRefSubLeadJets = nullptr, *hRefLeadRefSubLeadJets_W = nullptr, *hRefLeadRefSubLeadJets_MidRapidity_W = nullptr;
        THnSparseD *hGenLeadGenSubLeadJets_WithDijet_W = nullptr, *hGenLeadGenSubLeadJets_WithDijet_DiJetW = nullptr, *hRefLeadRefSubLeadJets_WithDijet_W = nullptr;
        TH2D *hInclusiveRecoJetPtVsEtaCMFrame_W = nullptr, *hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W = nullptr, *hInclusiveRecoJetPtVsEtaLabFrame_W = nullptr;
        TH2D *hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W = nullptr, *hLeadPtvsSubLeadPt_PtHatW = nullptr, *hLeadPtvsSubLeadPt_DiJetW = nullptr;
        TH2D *hRefLeadPtvsRefSubLeadPt_PtHatW = nullptr, *hRefLeadPtvsRefSubLeadPt_DiJetW = nullptr, *hGenLeadingVsGenSubLeading_WO_DiJet_W = nullptr;
        TH2D *hGenLeadPtvsGenSubLeadPt_DiJetW = nullptr, *hGenLeadPtvsGenSubLeadPt_PtHatW = nullptr, *hRefLeadPtVsRefSubLeadPtMatched_DiJetW = nullptr,
             *hRefLeadPtVsRefSubLeadPtMatched_PtHatW = nullptr;
        TH3D *hRecoJES_W = nullptr, *hRefJES_W = nullptr, *hRecoJES_Eta_W = nullptr, *hRefJES_Eta_W = nullptr, *hRecoJES_Eta_Pt100_W = nullptr;
        TH3D *hRecoJES_Eta_Pt120_W = nullptr, *hRefJES_Eta_Pt100_W = nullptr, *hRefJES_Eta_Pt120_W = nullptr;
        TH1D *hAverageRecoPt_W = nullptr, *hAverageGenPt_W = nullptr;
    } Jets;

    struct TracksGroup
    {
        TH3D *hGenTrackPtVsEta = nullptr, *hGenTrackPtVsEta_W = nullptr, *hTrackPtVsEta = nullptr, *hTrackPtVsEta_W = nullptr;
        TH3D *hTrackPtVsEtaCorrected = nullptr, *hTrackPtVsEtaCorrected_W = nullptr;
        THnSparseD *hRecoTracks = nullptr, *hRecoTracks_W = nullptr, *hRecoTracks_Pt1_W = nullptr;
        THnSparseD *hGenTracks = nullptr, *hGenTracks_W = nullptr, *hGenTracks_Pt1_W = nullptr;
    } Tracks;

    struct QuenchingGroup
    {
        TH3D *hMultVsXj_W = nullptr, *hMultVsXj_DiJetW = nullptr, *hMultVsRefXj_W = nullptr, *hMultVsMatchedRefXj_W = nullptr, *hMultVsMatchedRecoXj_W = nullptr;
        TH3D *hMultVsGenXj_W = nullptr, *hMultVsRefXj_DiJetW = nullptr, *hMultVsMatchedRefXj_DiJetW = nullptr, *hMultVsGenXj_DiJetW = nullptr;
        TH3D *hMultVsUnflippedMatchedRecoXj_W = nullptr, *hMultVsUnflippedMatchedRefXj_DiJetW = nullptr, *hMultVsUnflippedMatchedRefXj_W = nullptr;
        TH2D *hHiHFVsXj_W = nullptr, *hMultVsXj_HiHFW = nullptr, *hHiHFVsXj_HiHFW = nullptr;
        TH1D *hDeltaPhi_W = nullptr, *hDeltaPhi_WithDiJet_W = nullptr, *hGenDeltaPhi_W = nullptr, *hGenDeltaPhi_WithDiJet_W = nullptr;
        TH1D *hRefDeltaPhi_W = nullptr, *hRefDeltaPhi_WithDiJet_W = nullptr;
        TH1I* hNDijetEvent = nullptr;
        THnSparseD *hRecoQuenching_W = nullptr, *hRecoQuenching_WithDijet_W = nullptr, *hGenQuenching_W = nullptr, *hGenQuenching_WithDijet_W = nullptr;
    } Quenching;

    struct UnfoldingGroup
    {
        THnSparseD *hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W = nullptr, *hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W = nullptr;
        TH3D *hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W = nullptr, *hUnfoldingRefXjVsRecoXjVsMultiplicity_FakeJets_W = nullptr;
        TH3D *hFakeLeadXj_W = nullptr, *hFakeSubLeadXj_W = nullptr, *hResponseMatrix_W = nullptr, *hResponseMatrixA_W = nullptr, *hResponseMatrixB_W = nullptr;
        TH2D *hMultVsFakeRecoXjForTesting_W = nullptr, *hMultVsMissingRefXjForTesting_W = nullptr, *hMultVsFakeRecoXjToBeUnfolded_W = nullptr;
        TH2D *hMultVsMissingRefXjToBeUnfolded_W = nullptr, *hMultVsFakeRefXjForTesting_W = nullptr, *hMultVsFakeRefXjToBeUnfolded_W = nullptr;
        TH2D *hLeadPtVsRecoXj_W = nullptr, *hLeadPtVsRefXj_W = nullptr, *hLeadPtVsGenXj_W = nullptr, *hTotalReco_W = nullptr, *hTotalTruth_W = nullptr;
        TH2D *hMatchedGen_W = nullptr, *hMatchedReco_W = nullptr, *hTotalRecoA_W = nullptr, *hTotalTruthA_W = nullptr, *hMatchedGenA_W = nullptr;
        TH2D *hMatchedRecoA_W = nullptr, *hTotalRecoB_W = nullptr, *hTotalTruthB_W = nullptr, *hMatchedGenB_W = nullptr, *hMatchedRecoB_W = nullptr;
    } Unfolding;

    HistReader() {}
    ~HistReader() {}

    void ReadAll(TFile* fIn)
    {
        if (!fIn || fIn->IsZombie())
        {
            std::cerr << "Error: Invalid file passed to HistReader!" << std::endl;
            return;
        }

        // 1. Read Events
        if (fIn->GetDirectory("Events"))
        {
            fIn->cd("Events");
            Load(Events.hVz, "hVz");
            Load(Events.hRecoMultiplicity_W, "hRecoMultiplicity_W");
            Load(Events.hCorrectedMultiplicity_W, "hCorrectedMultiplicity_W");
            Load(Events.hSelectedMultiplicity_W, "hSelectedMultiplicity_W");
            Load(Events.hInJetMultiplicity_W, "hInJetMultiplicity_W");
            Load(Events.hMultiplicities, "hMultiplicities");
            Load(Events.hHiBin, "hHiBin");
            Load(Events.hHiBin_W, "hHiBin_W");
            Load(Events.hHiHF_PF, "hHiHF_PF");
            Load(Events.hHiHF_PF_W, "hHiHF_PF_W");
            Load(Events.hPtHat, "hPtHat");
            Load(Events.hGenInJetMultiplicity_W, "hGenInJetMultiplicity_W");
            Load(Events.hSubEventMultiplicity_W, "hSubEventMultiplicity_W");
            Load(Events.hGenMultiplicity_W, "hGenMultiplicity_W");
            Load(Events.hNEventsInMult, "hNEventsInMult");
            Load(Events.hHiHFPlusVsHiHFMinus, "hHiHFPlusVsHiHFMinus");
            Load(Events.hHiHFPlusVsHiHFMinus_W, "hHiHFPlusVsHiHFMinus_W");
            Load(Events.hHiHFPlusVsHiHFMinus_WithDijet_W, "hHiHFPlusVsHiHFMinus_WithDijet_W");
            Load(Events.hHiHFPlusVsMultiplicity_W, "hHiHFPlusVsMultiplicity_W");
            Load(Events.hHiHFMinusVsMultiplicity_W, "hHiHFMinusVsMultiplicity_W");
            Load(Events.hHiHFPlusVsMultiplicity_WithDijet_W, "hHiHFPlusVsMultiplicity_WithDijet_W");
            Load(Events.hHiHFMinusVsMultiplicity_WithDijet_W, "hHiHFMinusVsMultiplicity_WithDijet_W");
            Load(Events.hHiBinVsMultiplicity_W, "hHiBinVsMultiplicity_W");
            Load(Events.hHiBinVsCorrectedMultiplicity_W, "hHiBinVsCorrectedMultiplicity_W");
            Load(Events.hVz_W, "hVz_W");
            Load(Events.hVzWithDijet_W, "hVzWithDijet_W");
            Load(Events.hMultiplicities_W, "hMultiplicities_W");
            Load(Events.hMultiplicities_DiJet_W, "hMultiplicities_DiJet_W");
            Load(Events.hPtHat_W, "hPtHat_W");
        }

        // 2. Read Jets
        if (fIn->GetDirectory("Jets"))
        {
            fIn->cd("Jets");
            Load(Jets.hInclusiveUncorrectedRecoJets, "hInclusiveUncorrectedRecoJets");
            Load(Jets.hInclusiveUncorrectedRecoJets_W, "hInclusiveUncorrectedRecoJets_W");
            Load(Jets.hInclusiveRecoJetsCMFrame, "hInclusiveRecoJetsCMFrame");
            Load(Jets.hInclusiveRecoJetsCMFrame_W, "hInclusiveRecoJetsCMFrame_W");
            Load(Jets.hSelectedInclusiveRecoJetsMidRapidity_W, "hSelectedInclusiveRecoJetsMidRapidity_W");
            Load(Jets.hInclusiveRecoJetPtVsEtaCMFrame_W, "hInclusiveRecoJetPtVsEtaCMFrame_W");
            Load(Jets.hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W, "hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W");
            Load(Jets.hJetFlavorFractions_W, "hJetFlavorFractions_W");
            Load(Jets.hAverageRecoPt_W, "hAverageRecoPt_W");
            Load(Jets.hInclusiveRecoJetsLabFrame, "hInclusiveRecoJetsLabFrame");
            Load(Jets.hInclusiveRecoJetsLabFrame_W, "hInclusiveRecoJetsLabFrame_W");
            Load(Jets.hInclusiveRecoJetPtVsEtaLabFrame_W, "hInclusiveRecoJetPtVsEtaLabFrame_W");
            Load(Jets.hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W, "hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W");
            Load(Jets.hInclusiveGenJetsCMFrame, "hInclusiveGenJetsCMFrame");
            Load(Jets.hInclusiveGenJetsCMFrame_W, "hInclusiveGenJetsCMFrame_W");
            Load(Jets.hInclusiveRefJetsCMFrame, "hInclusiveRefJetsCMFrame");
            Load(Jets.hInclusiveRefJetsCMFrame_W, "hInclusiveRefJetsCMFrame_W");
            Load(Jets.hSelectedInclusiveGenJetsMidRapidity_W, "hSelectedInclusiveGenJetsMidRapidity_W");
            Load(Jets.hSelectedInclusiveRefJetsMidRapidity_W, "hSelectedInclusiveRefJetsMidRapidity_W");
            Load(Jets.hInclusiveGenJetsLabFrame, "hInclusiveGenJetsLabFrame");
            Load(Jets.hInclusiveGenJetsLabFrame_W, "hInclusiveGenJetsLabFrame_W");
            Load(Jets.hInclusiveRefJetsLabFrame, "hInclusiveRefJetsLabFrame");
            Load(Jets.hInclusiveRefJetsLabFrame_W, "hInclusiveRefJetsLabFrame_W");
            Load(Jets.hRecoJES_W, "hRecoJES_W");
            Load(Jets.hRefJES_W, "hRefJES_W");
            Load(Jets.hRecoJES_Eta_W, "hRecoJES_Eta_W");
            Load(Jets.hRefJES_Eta_W, "hRefJES_Eta_W");
            Load(Jets.hRecoJES_Eta_Pt100_W, "hRecoJES_Eta_Pt100_W");
            Load(Jets.hRecoJES_Eta_Pt120_W, "hRecoJES_Eta_Pt120_W");
            Load(Jets.hRefJES_Eta_Pt100_W, "hRefJES_Eta_Pt100_W");
            Load(Jets.hRefJES_Eta_Pt120_W, "hRefJES_Eta_Pt120_W");
            Load(Jets.hAverageGenPt_W, "hAverageGenPt_W");
            Load(Jets.hLeadSubLeadJets, "hLeadSubLeadJets");
            Load(Jets.hLeadSubLeadJets_W, "hLeadSubLeadJets_W");
            Load(Jets.hLeadSubLeadJets_MidRapidity_W, "hLeadSubLeadJets_MidRapidity_W");
            Load(Jets.hLeadSubLeadJets_WithDijet_W, "hLeadSubLeadJets_WithDijet_W");
            Load(Jets.hLeadSubLeadJets_WithDijet_DiJetW, "hLeadSubLeadJets_WithDijet_DiJetW");
            Load(Jets.hLeadPtvsSubLeadPt_PtHatW, "hLeadPtvsSubLeadPt_PtHatW");
            Load(Jets.hLeadPtvsSubLeadPt_DiJetW, "hLeadPtvsSubLeadPt_DiJetW");
            Load(Jets.hGenLeadGenSubLeadJets, "hGenLeadGenSubLeadJets");
            Load(Jets.hGenLeadGenSubLeadJets_W, "hGenLeadGenSubLeadJets_W");
            Load(Jets.hGenLeadGenSubLeadJets_MidRapidity_W, "hGenLeadGenSubLeadJets_MidRapidity_W");
            Load(Jets.hRefLeadRefSubLeadJets, "hRefLeadRefSubLeadJets");
            Load(Jets.hRefLeadRefSubLeadJets_W, "hRefLeadRefSubLeadJets_W");
            Load(Jets.hRefLeadRefSubLeadJets_MidRapidity_W, "hRefLeadRefSubLeadJets_MidRapidity_W");
            Load(Jets.hGenLeadGenSubLeadJets_WithDijet_W, "hGenLeadGenSubLeadJets_WithDijet_W");
            Load(Jets.hGenLeadGenSubLeadJets_WithDijet_DiJetW, "hGenLeadGenSubLeadJets_WithDijet_DiJetW");
            Load(Jets.hRefLeadRefSubLeadJets_WithDijet_W, "hRefLeadRefSubLeadJets_WithDijet_W");
            Load(Jets.hRefLeadPtvsRefSubLeadPt_PtHatW, "hRefLeadPtvsRefSubLeadPt_PtHatW");
            Load(Jets.hRefLeadPtvsRefSubLeadPt_DiJetW, "hRefLeadPtvsRefSubLeadPt_DiJetW");
            Load(Jets.hGenLeadingVsGenSubLeading_WO_DiJet_W, "hGenLeadingVsGenSubLeading_WO_DiJet_W");
            Load(Jets.hGenLeadPtvsGenSubLeadPt_DiJetW, "hGenLeadPtvsGenSubLeadPt_DiJetW");
            Load(Jets.hGenLeadPtvsGenSubLeadPt_PtHatW, "hGenLeadPtvsGenSubLeadPt_PtHatW");
            Load(Jets.hRefLeadPtVsRefSubLeadPtMatched_DiJetW, "hRefLeadPtvsRefSubLeadPtMatched_DiJetW");
            Load(Jets.hRefLeadPtVsRefSubLeadPtMatched_PtHatW, "hRefLeadPtvsRefSubLeadPtMatched_PtHatW");
        }

        // 3. Read Tracks
        if (fIn->GetDirectory("Tracks"))
        {
            fIn->cd("Tracks");
            Load(Tracks.hGenTrackPtVsEta, "hGenTrackPtVsEta");
            Load(Tracks.hGenTrackPtVsEta_W, "hGenTrackPtVsEta_W");
            Load(Tracks.hTrackPtVsEta, "hRecoTrackPtVsEta");
            Load(Tracks.hTrackPtVsEta_W, "hRecoTrackPtVsEta_W");
            Load(Tracks.hTrackPtVsEtaCorrected, "hRecoTrackPtVsEtaCorrected");
            Load(Tracks.hTrackPtVsEtaCorrected_W, "hRecoTrackPtVsEtaCorrected_W");
            Load(Tracks.hRecoTracks, "hRecoTracks");
            Load(Tracks.hRecoTracks_W, "hRecoTracks_W");
            Load(Tracks.hRecoTracks_Pt1_W, "hRecoTracks_Pt1_W");
            Load(Tracks.hGenTracks, "hGenTracks");
            Load(Tracks.hGenTracks_W, "hGenTracks_W");
            Load(Tracks.hGenTracks_Pt1_W, "hGenTracks_Pt1_W");
        }

        // 4. Read Quenching
        if (fIn->GetDirectory("Quenching"))
        {
            fIn->cd("Quenching");
            Load(Quenching.hMultVsXj_W, "hMultVsXj_W");
            Load(Quenching.hHiHFVsXj_W, "hHiHFVsXj_W");
            Load(Quenching.hMultVsXj_DiJetW, "hMultVsXj_DiJetW");
            Load(Quenching.hMultVsXj_HiHFW, "hMultVsXj_HiHFW");
            Load(Quenching.hHiHFVsXj_HiHFW, "hHiHFVsXj_HiHFW");
            Load(Quenching.hMultVsRefXj_W, "hMultVsRefXj_W");
            Load(Quenching.hMultVsMatchedRefXj_W, "hMultVsMatchedRefXj_W");
            Load(Quenching.hMultVsMatchedRecoXj_W, "hMultVsMatchedRecoXj_W");
            Load(Quenching.hMultVsGenXj_W, "hMultVsGenXj_W");
            Load(Quenching.hMultVsRefXj_DiJetW, "hMultVsRefXj_DiJetW");
            Load(Quenching.hMultVsMatchedRefXj_DiJetW, "hMultVsMatchedRefXj_DiJetW");
            Load(Quenching.hMultVsGenXj_DiJetW, "hMultVsGenXj_DiJetW");
            Load(Quenching.hDeltaPhi_W, "hDeltaPhi_W");
            Load(Quenching.hDeltaPhi_WithDiJet_W, "hDeltaPhi_WithDiJet_W");
            Load(Quenching.hNDijetEvent, "hNDijetEvent");
            Load(Quenching.hRecoQuenching_W, "hRecoQuenching_W");
            Load(Quenching.hRecoQuenching_WithDijet_W, "hRecoQuenching_WithDijet_W");
            Load(Quenching.hMultVsUnflippedMatchedRecoXj_W, "hMultVsUnflippedMatchedRecoXj_W");
            Load(Quenching.hMultVsUnflippedMatchedRefXj_DiJetW, "hMultVsUnflippedMatchedRefXj_DiJetW");
            Load(Quenching.hMultVsUnflippedMatchedRefXj_W, "hMultVsUnflippedMatchedRefXj_W");
            Load(Quenching.hGenDeltaPhi_W, "hGenDeltaPhi_W");
            Load(Quenching.hGenDeltaPhi_WithDiJet_W, "hGenDeltaPhi_WithDiJet_W");
            Load(Quenching.hRefDeltaPhi_W, "hRefDeltaPhi_W");
            Load(Quenching.hRefDeltaPhi_WithDiJet_W, "hRefDeltaPhi_WithDiJet_W");
            Load(Quenching.hGenQuenching_W, "hGenQuenching_W");
            Load(Quenching.hGenQuenching_WithDijet_W, "hGenQuenching_WithDijet_W");
        }

        // 5. Read Unfolding
        if (fIn->GetDirectory("Unfolding"))
        {
            fIn->cd("Unfolding");
            Load(Unfolding.hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W, "hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W");
            Load(Unfolding.hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W, "hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W");
            Load(Unfolding.hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W, "hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W");
            Load(Unfolding.hUnfoldingRefXjVsRecoXjVsMultiplicity_FakeJets_W, "hUnfoldingRefXjVsRecoXjVsMultiplicity_FakeJets_W");
            Load(Unfolding.hMultVsFakeRecoXjForTesting_W, "hMultVsFakeRecoXjForTesting_W");
            Load(Unfolding.hMultVsMissingRefXjForTesting_W, "hMultVsMissingRefXjForTesting_W");
            Load(Unfolding.hMultVsFakeRecoXjToBeUnfolded_W, "hMultVsFakeRecoXjToBeUnfolded_W");
            Load(Unfolding.hMultVsMissingRefXjToBeUnfolded_W, "hMultVsMissingRefXjToBeUnfolded_W");
            Load(Unfolding.hMultVsFakeRefXjForTesting_W, "hMultVsFakeRefXjForTesting_W");
            Load(Unfolding.hMultVsFakeRefXjToBeUnfolded_W, "hMultVsFakeRefXjToBeUnfolded_W");
            Load(Unfolding.hFakeLeadXj_W, "hFakeLeadXj_W");
            Load(Unfolding.hFakeSubLeadXj_W, "hFakeSubLeadXj_W");
            Load(Unfolding.hLeadPtVsRecoXj_W, "hLeadPtVsRecoXj_W");
            Load(Unfolding.hLeadPtVsRefXj_W, "hLeadPtVsRefXj_W");
            Load(Unfolding.hLeadPtVsGenXj_W, "hLeadPtVsGenXj_W");
            Load(Unfolding.hResponseMatrix_W, "hResponseMatrix_W");
            Load(Unfolding.hTotalReco_W, "hTotalReco_W");
            Load(Unfolding.hTotalTruth_W, "hTotalTruth_W");
            Load(Unfolding.hMatchedGen_W, "hMatchedGen_W");
            Load(Unfolding.hMatchedReco_W, "hMatchedReco_W");
            Load(Unfolding.hResponseMatrixA_W, "hResponseMatrixA_W");
            Load(Unfolding.hTotalRecoA_W, "hTotalRecoA_W");
            Load(Unfolding.hTotalTruthA_W, "hTotalTruthA_W");
            Load(Unfolding.hMatchedGenA_W, "hMatchedGenA_W");
            Load(Unfolding.hMatchedRecoA_W, "hMatchedRecoA_W");
            Load(Unfolding.hResponseMatrixB_W, "hResponseMatrixB_W");
            Load(Unfolding.hTotalRecoB_W, "hTotalRecoB_W");
            Load(Unfolding.hTotalTruthB_W, "hTotalTruthB_W");
            Load(Unfolding.hMatchedGenB_W, "hMatchedGenB_W");
            Load(Unfolding.hMatchedRecoB_W, "hMatchedRecoB_W");
        }

        // Always reset directory context back to the file root
        fIn->cd();
    }
};

#endif