/**
 * @file HistoManagerDiJet.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-29
 *
 * @copyright Copyright (c) 2024
 *
 */

// Jet Analysis headers
#include "HistoManagerDiJet.h"

// ROOT headers
#include "TString.h"

// C++ Headers
#include <iostream>

ClassImp(HistoManagerDiJet)

    HistoManagerDiJet::HistoManagerDiJet() : BaseHistoManager(), fIsMC{kFALSE}, fMultiplicityBins{0.0},
                                             hRecoMultiplicity_W{nullptr}, hCorrectedMultiplicity_W{nullptr}, hGenMultiplicity_W{nullptr}, hSubEventMultiplicity_W{nullptr},
                                             hSelectedMultiplicity_W{nullptr}, hMultiplicities{nullptr}, hMultiplicities_W{nullptr}, hPtHat{nullptr}, hPtHat_W{nullptr},
                                             hHiBin{nullptr}, hHiBin_W{nullptr}, hVz{nullptr}, hVz_W{nullptr}, hMultiplicities_DiJet_W{nullptr}, hRecoQuenching_W{nullptr}, hGenQuenching_W{nullptr},
                                             hDeltaPhi_W{nullptr}, hMultVsXj_W{nullptr}, hNDijetEvent{nullptr}, hNEventsInMult{nullptr}, hGenDeltaPhi_W{nullptr},
                                             hMultVsGenXj_W{nullptr}, hNGenDijetEvent{nullptr}, hInJetMultiplicity_W{nullptr}, hGenInJetMultiplicity_W{nullptr}, hLeadSubLeadJets{nullptr},
                                             hGenLeadGenSubLeadJets{nullptr}, hGenLeadGenSubLeadJets_W{nullptr}, hLeadSubLeadJets_W{nullptr}, hVzWithDijet_W{nullptr}, hMultVsXj_DiJetW{nullptr}, hMultVsRefXj_W{nullptr}, hMultVsRefXj_DiJetW{nullptr},
                                             hMultVsRefXj_ER_W{nullptr}, hMultVsRefXj_ER_DiJetW{nullptr}, hRefLeadRefSubLeadJets{nullptr}, hRefLeadRefSubLeadJets_W{nullptr}, hMultVsGenXj_DiJetW{nullptr}, hRecoJES_W{nullptr}, hRefJES_W{nullptr},
                                             hGenLeadingVsGenSubLeading_WO_DiJet_W{nullptr}, hRefLeadingVsRefSubLeadingMatched_W{nullptr}, hLeadPtvsSubLeadPt_DiJetW{nullptr},
                                             hRefLeadPtvsRefSubLeadPt_DiJetW{nullptr}, hLeadSubLeadJets_MidRapidity_W{nullptr}, hGenLeadGenSubLeadJets_MidRapidity_W{nullptr}, hRefLeadRefSubLeadJets_MidRapidity_W{nullptr},
                                             hGenLeadPtvsGenSubLeadPt_DiJetW{nullptr}, hLeadSubLeadJets_WithDijet_W{nullptr}, hGenLeadGenSubLeadJets_WithDijet_W{nullptr}, hRefLeadRefSubLeadJets_WithDijet_W{nullptr},
                                             hGenLeadPtvsGenSubLeadPt_PtHatW{nullptr}, hRefLeadPtvsRefSubLeadPt_PtHatW{nullptr}, hLeadPtvsSubLeadPt_PtHatW{nullptr}, hDeltaPhi_WithDiJet_W{nullptr}, hGenDeltaPhi_WithDiJet_W{nullptr},
                                             hInclusiveUncorrectedRecoJets{nullptr}, hInclusiveUncorrectedRecoJets_W{nullptr}, hInclusiveRecoJetsLabFrame{nullptr}, hInclusiveRecoJetsLabFrame_W{nullptr},
                                             hInclusiveRecoJetsCMFrame{nullptr}, hInclusiveRecoJetsCMFrame_W{nullptr}, hSelectedInclusiveRecoJetsMidRapidity_W{nullptr}, hInclusiveGenJetsLabFrame{nullptr},
                                             hInclusiveGenJetsLabFrame_W{nullptr}, hInclusiveGenJetsCMFrame{nullptr}, hInclusiveGenJetsCMFrame_W{nullptr}, hSelectedInclusiveGenJetsMidRapidity_W{nullptr},
                                             hInclusiveRecoJetPtVsEtaLabFrame_W{nullptr}, hInclusiveRecoJetPtVsEtaCMFrame_W{nullptr}, hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W{nullptr}, hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W{nullptr},
                                             hInclusiveRecoJetPt{nullptr}, hInclusiveRecoJetPt_W{nullptr}, hInclusiveGenJetPt{nullptr}, hInclusiveGenJetPt_W{nullptr}, hSelectedInclusiveRecoJetPt_MidRapidity_W{nullptr},
                                             hSelectedInclusiveGenJetPt_MidRapidity_W{nullptr}, hInclusiveRecoJetEtaCMFrame{nullptr}, hInclusiveRecoJetEtaCMFrame_W{nullptr}, hInclusiveGenJetEtaLabFrame{nullptr}, hInclusiveRecoJetEtaLabFrame_W{nullptr},
                                             hSelectedInclusiveRecoJetEtaMidRapidity_W{nullptr}, hInclusiveGenJetEtaCMFrame{nullptr}, hInclusiveGenJetEtaCMFrame_W{nullptr}, hSelectedInclusiveGenJetEtaMidRapidity_W{nullptr},
                                             hLeadingRecoJetPt{nullptr}, hLeadingRecoJetPt_W{nullptr}, hSubLeadingRecoJetPt{nullptr}, hSubLeadingRecoJetPt_W{nullptr}, hLeadingGenJetPt{nullptr}, hLeadingGenJetPt_W{nullptr}, hSubLeadingGenJetPt{nullptr}, hSubLeadingGenJetPt_W{nullptr},
                                             hLeadingRecoJetPtWithDijet_W{nullptr}, hSubLeadingRecoJetPtWithDijet_W{nullptr}, hLeadingGenJetPtWithDijet_W{nullptr}, hSubLeadingGenJetPtWithDijet_W{nullptr}, hXj_Projection_W{nullptr}, hXj_Projection_DiJetW{nullptr},
                                             hGenXj_Projection_W{nullptr}, hGenXj_Projection_DiJetW{nullptr}, hInclusiveRefJetPt{nullptr}, hInclusiveRefJetPt_W{nullptr}, hInclusiveRefJetsCMFrame{nullptr}, hInclusiveRefJetsCMFrame_W{nullptr}, hInclusiveRefJetsLabFrame{nullptr}, hInclusiveRefJetsLabFrame_W{nullptr},
                                             hSelectedInclusiveRefJetsMidRapidity_W{nullptr}, hSelectedInclusiveRefJetPt_MidRapidity_W{nullptr}, hLeadingRefJetPt{nullptr}, hLeadingRefJetPt_W{nullptr}, hSubLeadingRefJetPt{nullptr}, hSubLeadingRefJetPt_W{nullptr},
                                             hLeadingRefJetPtWithDijet_W{nullptr}, hSubLeadingRefJetPtWithDijet_W{nullptr}, hXj_C0_W{nullptr}, hXj_C0_DiJetW{nullptr}, hGenXj_C0_W{nullptr}, hGenXj_C0_DiJetW{nullptr}
{
    /* Empty*/
}

HistoManagerDiJet::~HistoManagerDiJet()
{
    if (hRecoMultiplicity_W)
        delete hRecoMultiplicity_W;
    if (hCorrectedMultiplicity_W)
        delete hCorrectedMultiplicity_W;
    if (hGenMultiplicity_W)
        delete hGenMultiplicity_W;
    if (hSubEventMultiplicity_W)
        delete hSubEventMultiplicity_W;
    if (hSelectedMultiplicity_W)
        delete hSelectedMultiplicity_W;
    if (hPtHat)
        delete hPtHat;
    if (hPtHat_W)
        delete hPtHat_W;
    if (hHiBin)
        delete hHiBin;
    if (hHiBin_W)
        delete hHiBin_W;
    if (hVz)
        delete hVz;
    if (hVz_W)
        delete hVz_W;
    if (hVzWithDijet_W)
        delete hVzWithDijet_W;
    if (hDeltaPhi_W)
        delete hDeltaPhi_W;
    if (hMultVsXj_W)
        delete hMultVsXj_W;
    if (hMultVsXj_DiJetW)
        delete hMultVsXj_DiJetW;
    if (hMultVsRefXj_W)
        delete hMultVsRefXj_W;
    if (hMultVsRefXj_DiJetW)
        delete hMultVsRefXj_DiJetW;
    if (hMultVsRefXj_ER_W)
        delete hMultVsRefXj_ER_W;
    if (hMultVsRefXj_ER_DiJetW)
        delete hMultVsRefXj_ER_DiJetW;
    if (hNDijetEvent)
        delete hNDijetEvent;
    if (hGenDeltaPhi_W)
        delete hGenDeltaPhi_W;
    if (hMultVsGenXj_W)
        delete hMultVsGenXj_W;
    if (hMultVsGenXj_DiJetW)
        delete hMultVsGenXj_DiJetW;
    if (hNGenDijetEvent)
        delete hNGenDijetEvent;
    if (hNEventsInMult)
        delete hNEventsInMult;
    if (hDeltaPhi_WithDiJet_W)
        delete hDeltaPhi_WithDiJet_W;
    if (hGenDeltaPhi_WithDiJet_W)
        delete hGenDeltaPhi_WithDiJet_W;

    if (hInJetMultiplicity_W)
        delete hInJetMultiplicity_W;
    if (hGenInJetMultiplicity_W)
        delete hGenInJetMultiplicity_W;

    if (hLeadSubLeadJets)
        delete hLeadSubLeadJets;
    if (hGenLeadGenSubLeadJets)
        delete hGenLeadGenSubLeadJets;
    if (hLeadSubLeadJets_W)
        delete hLeadSubLeadJets_W;
    if (hGenLeadGenSubLeadJets_W)
        delete hGenLeadGenSubLeadJets_W;
    if (hRefLeadRefSubLeadJets)
        delete hRefLeadRefSubLeadJets;
    if (hRefLeadRefSubLeadJets_W)
        delete hRefLeadRefSubLeadJets_W;
    if (hRecoJES_W)
        delete hRecoJES_W;
    if (hRefJES_W)
        delete hRefJES_W;
    if (hLeadPtvsSubLeadPt_DiJetW)
        delete hLeadPtvsSubLeadPt_DiJetW;
    if (hGenLeadPtvsGenSubLeadPt_DiJetW)
        delete hGenLeadPtvsGenSubLeadPt_DiJetW;
    if (hRefLeadPtvsRefSubLeadPt_DiJetW)
        delete hRefLeadPtvsRefSubLeadPt_DiJetW;
    if (hLeadSubLeadJets_MidRapidity_W)
        delete hLeadSubLeadJets_MidRapidity_W;
    if (hGenLeadGenSubLeadJets_MidRapidity_W)
        delete hGenLeadGenSubLeadJets_MidRapidity_W;
    if (hRefLeadRefSubLeadJets_MidRapidity_W)
        delete hRefLeadRefSubLeadJets_MidRapidity_W;
    if (hLeadSubLeadJets_WithDijet_W)
        delete hLeadSubLeadJets_WithDijet_W;
    if (hGenLeadGenSubLeadJets_WithDijet_W)
        delete hGenLeadGenSubLeadJets_WithDijet_W;
    if (hRefLeadRefSubLeadJets_WithDijet_W)
        delete hRefLeadRefSubLeadJets_WithDijet_W;
    if (hLeadPtvsSubLeadPt_PtHatW)
        delete hLeadPtvsSubLeadPt_PtHatW;
    if (hGenLeadPtvsGenSubLeadPt_PtHatW)
        delete hGenLeadPtvsGenSubLeadPt_PtHatW;
    if (hRefLeadPtvsRefSubLeadPt_PtHatW)
        delete hRefLeadPtvsRefSubLeadPt_PtHatW;

    if (hMultiplicities)
        delete hMultiplicities;
    if (hMultiplicities_W)
        delete hMultiplicities_W;
    if (hMultiplicities_DiJet_W)
        delete hMultiplicities_DiJet_W;
    if (hGenLeadingVsGenSubLeading_WO_DiJet_W)
        delete hGenLeadingVsGenSubLeading_WO_DiJet_W;
    if (hRefLeadingVsRefSubLeadingMatched_W)
        delete hRefLeadingVsRefSubLeadingMatched_W;
    if (hRecoQuenching_W)
        delete hRecoQuenching_W;
    if (hGenQuenching_W)
        delete hGenQuenching_W;

    if (hInclusiveUncorrectedRecoJets)
        delete hInclusiveUncorrectedRecoJets;
    if (hInclusiveUncorrectedRecoJets_W)
        delete hInclusiveUncorrectedRecoJets_W;
    if (hInclusiveRecoJetsLabFrame)
        delete hInclusiveRecoJetsLabFrame;
    if (hInclusiveRecoJetsLabFrame_W)
        delete hInclusiveRecoJetsLabFrame_W;
    if (hInclusiveRecoJetsCMFrame)
        delete hInclusiveRecoJetsCMFrame;
    if (hInclusiveRecoJetsCMFrame_W)
        delete hInclusiveRecoJetsCMFrame_W;
    if (hSelectedInclusiveRecoJetsMidRapidity_W)
        delete hSelectedInclusiveRecoJetsMidRapidity_W;

    if (hInclusiveRefJetsCMFrame)
        delete hInclusiveRefJetsCMFrame;
    if (hInclusiveRefJetsCMFrame_W)
        delete hInclusiveRefJetsCMFrame_W;
    if (hInclusiveRefJetsLabFrame)
        delete hInclusiveRefJetsLabFrame;
    if (hInclusiveRefJetsLabFrame_W)
        delete hInclusiveRefJetsLabFrame_W;
    if (hSelectedInclusiveRefJetsMidRapidity_W)
        delete hSelectedInclusiveRefJetsMidRapidity_W;

    if (hInclusiveGenJetsLabFrame)
        delete hInclusiveGenJetsLabFrame;
    if (hInclusiveGenJetsLabFrame_W)
        delete hInclusiveGenJetsLabFrame_W;
    if (hInclusiveGenJetsCMFrame)
        delete hInclusiveGenJetsCMFrame;
    if (hInclusiveGenJetsCMFrame_W)
        delete hInclusiveGenJetsCMFrame_W;
    if (hSelectedInclusiveGenJetsMidRapidity_W)
        delete hSelectedInclusiveGenJetsMidRapidity_W;

    if (hInclusiveRecoJetPtVsEtaLabFrame_W)
        delete hInclusiveRecoJetPtVsEtaLabFrame_W;
    if (hInclusiveRecoJetPtVsEtaCMFrame_W)
        delete hInclusiveRecoJetPtVsEtaCMFrame_W;
    if (hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W)
        delete hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W;
    if (hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W)
        delete hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W;

    if (hInclusiveRecoJetPt)
        delete hInclusiveRecoJetPt;
    if (hInclusiveRecoJetPt_W)
        delete hInclusiveRecoJetPt_W;
    if (hSelectedInclusiveGenJetPt_MidRapidity_W)
        delete hSelectedInclusiveGenJetPt_MidRapidity_W;
    if (hInclusiveRecoJetEtaCMFrame)
        delete hInclusiveRecoJetEtaCMFrame;
    if (hInclusiveRecoJetEtaCMFrame_W)
        delete hInclusiveRecoJetEtaCMFrame_W;
    if (hInclusiveRecoJetEtaLabFrame)
        delete hInclusiveRecoJetEtaLabFrame;
    if (hInclusiveRecoJetEtaLabFrame_W)
        delete hInclusiveRecoJetEtaLabFrame_W;
    if (hSelectedInclusiveRecoJetEtaMidRapidity_W)
        delete hSelectedInclusiveRecoJetEtaMidRapidity_W;

    if (hInclusiveRefJetPt)
        delete hInclusiveRefJetPt;
    if (hInclusiveRefJetPt_W)
        delete hInclusiveRefJetPt_W;
    if (hSelectedInclusiveRefJetPt_MidRapidity_W)
        delete hSelectedInclusiveRefJetPt_MidRapidity_W;

    if (hInclusiveGenJetPt)
        delete hInclusiveGenJetPt;
    if (hInclusiveGenJetPt_W)
        delete hInclusiveGenJetPt_W;
    if (hSelectedInclusiveRecoJetPt_MidRapidity_W)
        delete hSelectedInclusiveRecoJetPt_MidRapidity_W;
    if (hInclusiveGenJetEtaCMFrame)
        delete hInclusiveGenJetEtaCMFrame;
    if (hInclusiveGenJetEtaCMFrame_W)
        delete hInclusiveGenJetEtaCMFrame_W;
    if (hInclusiveGenJetEtaLabFrame)
        delete hInclusiveGenJetEtaLabFrame;
    if (hInclusiveGenJetEtaLabFrame_W)
        delete hInclusiveGenJetEtaLabFrame_W;
    if (hSelectedInclusiveGenJetEtaMidRapidity_W)
        delete hSelectedInclusiveGenJetEtaMidRapidity_W;

    if (hLeadingRecoJetPt)
        delete hLeadingRecoJetPt;
    if (hLeadingRecoJetPt_W)
        delete hLeadingRecoJetPt_W;
    if (hSubLeadingRecoJetPt)
        delete hSubLeadingRecoJetPt;
    if (hSubLeadingRecoJetPt_W)
        delete hSubLeadingRecoJetPt_W;
    if (hLeadingGenJetPt)
        delete hLeadingGenJetPt;
    if (hLeadingGenJetPt_W)
        delete hLeadingGenJetPt_W;
    if (hSubLeadingGenJetPt)
        delete hSubLeadingGenJetPt;
    if (hSubLeadingGenJetPt_W)
        delete hSubLeadingGenJetPt_W;
    if (hLeadingRecoJetPtWithDijet_W)
        delete hLeadingRecoJetPtWithDijet_W;
    if (hSubLeadingRecoJetPtWithDijet_W)
        delete hSubLeadingRecoJetPtWithDijet_W;
    if (hLeadingGenJetPtWithDijet_W)
        delete hLeadingGenJetPtWithDijet_W;
    if (hSubLeadingGenJetPtWithDijet_W)
        delete hSubLeadingGenJetPtWithDijet_W;
    if (hLeadingRefJetPt)
        delete hLeadingRefJetPt;
    if (hSubLeadingRefJetPt)
        delete hSubLeadingRefJetPt;
    if (hLeadingRefJetPt_W)
        delete hLeadingRefJetPt_W;
    if (hSubLeadingRefJetPt_W)
        delete hSubLeadingRefJetPt_W;
    if (hLeadingRefJetPtWithDijet_W)
        delete hLeadingRefJetPtWithDijet_W;
    if (hSubLeadingRefJetPtWithDijet_W)
        delete hSubLeadingRefJetPtWithDijet_W;

    if (hXj_C0_DiJetW)
        delete hXj_C0_DiJetW;
    if (hXj_C0_W)
        delete hXj_C0_W;
    if (hGenXj_C0_DiJetW)
        delete hGenXj_C0_DiJetW;
    if (hGenXj_C0_W)
        delete hGenXj_C0_W;

    for (Int_t i = 0; i < 5; i++)
    {
        if (hXj_Projection_W[i])
            delete hXj_Projection_W[i];
        if (hXj_Projection_DiJetW[i])
            delete hXj_Projection_DiJetW[i];
        if (hGenXj_Projection_W[i])
            delete hGenXj_Projection_W[i];
        if (hGenXj_Projection_DiJetW[i])
            delete hGenXj_Projection_DiJetW[i];
    }
}

void HistoManagerDiJet::init()
{
    int nMultiplicityBins = fMultiplicityBins.size() - 1;

    hRecoMultiplicity_W = new TH1D("hRecoMultiplicity_W", "Reco Multiplicity Weighted", 600, 0.0, 600.0);
    hRecoMultiplicity_W->Sumw2();
    hCorrectedMultiplicity_W = new TH1D("hCorrectedMultiplicity_W", "Corrected Multiplicity Weighted", 600, 0.0, 600.0);
    hCorrectedMultiplicity_W->Sumw2();
    hSelectedMultiplicity_W = new TH1D("hSelectedMultiplicity", "Multiplicity Distribution after selection Weighted", 600, 0., 600.);
    hSelectedMultiplicity_W->Sumw2();
    hInJetMultiplicity_W = new TH2D("hInJetMultiplicity_W", "Multiplicity in Jets", 30, 0., 30., 600, 0., 600.);
    hInJetMultiplicity_W->Sumw2();

    hHiBin = new TH1D("hHiBin", "HiBin Distribution", 200, 0.0, 200.0);
    hHiBin->Sumw2();
    hHiBin_W = new TH1D("hHiBin_W", "HiBin Distribution Weighted", 200, 0.0, 200.0);
    hHiBin_W->Sumw2();
    hVz = new TH1D("hVz", "Vz Distribution", 200, -20.0, 20.0);
    hVz->Sumw2();
    hVz_W = new TH1D("hVz_W", "Vz Distribution Weighted", 200, -20.0, 20.0);
    hVz_W->Sumw2();
    hVzWithDijet_W = new TH1D("hVzWithDijet_W", "Vz Distribution With Dijet Present Weighted", 200, -20.0, 20.0);
    hVzWithDijet_W->Sumw2();
    hNEventsInMult = new TH1D("hNEventsInMult", "Number of Events in Multiplicity Bins", 6, 0., 6.);
    hNEventsInMult->Sumw2();
    hNDijetEvent = new TH1I("hNDijetEvent", "Number of Dijet Events", 2, 0, 2);
    hNDijetEvent->Sumw2();

    if (fIsMC)
    {
        hGenMultiplicity_W = new TH1D("hGenMultiplicity_W", "Gen Multiplicity Weighted", 600, 0.0, 600.0);
        hGenMultiplicity_W->Sumw2();
        hSubEventMultiplicity_W = new TH1D("hSubEventMultiplicity_W", "Underlying Event Multiplicity Weighted", 600, 0., 600.);
        hSubEventMultiplicity_W->Sumw2();
        hGenInJetMultiplicity_W = new TH2D("hGenInJetMultiplicity_W", "Gen Multiplicity in Jets", 30, 0., 30., 600, 0., 600.);
        hGenInJetMultiplicity_W->Sumw2();
        hPtHat = new TH1D("hPtHat", "#hat{p_{T}} Distribution", 100, 0.0, 1000.0);
        hPtHat->Sumw2();
        hPtHat_W = new TH1D("hPtHat_W", "#hat{p_{T}} Distribution Weighted", 100, 0.0, 1000.0);
        hPtHat_W->Sumw2();
        hNGenDijetEvent = new TH1D("hNGenDijetEvent", "Number of Gen Dijet Events", 2, 0, 2);
        hNGenDijetEvent->Sumw2();
    }

    int MultBins[5] = {600, 600, 600, 600, nMultiplicityBins};
    Double_t MultMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t MultMax[5] = {600.0, 600.0, 600.0, 600.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hMultiplicities = new THnSparseD("hMultiplicities", "Multiplicity Distribution", 5, MultBins, MultMin, MultMax);
    hMultiplicities->Sumw2();
    hMultiplicities_W = new THnSparseD("hMultiplicities_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    hMultiplicities_W->Sumw2();
    hMultiplicities_DiJet_W = new THnSparseD("hMultiplicities_DiJet_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    hMultiplicities_DiJet_W->Sumw2();

    int JetBins[4] = {200, 52, 64, nMultiplicityBins};
    Double_t JetMin[4] = {0.0, -5.2, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t JetMax[4] = {1000.0, 5.2, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hInclusiveUncorrectedRecoJets = new THnSparseD("hInclusiveUncorrectedRecoJets", "Inclusive Uncorrected Reco Jets", 4, JetBins, JetMin, JetMax);
    hInclusiveUncorrectedRecoJets->Sumw2();
    hInclusiveUncorrectedRecoJets_W = new THnSparseD("hInclusiveUncorrectedRecoJets_W", "Inclusive Uncorrected Reco Jets Weighted", 4, JetBins, JetMin, JetMax);
    hInclusiveUncorrectedRecoJets_W->Sumw2();
    hInclusiveRecoJetsLabFrame = new THnSparseD("hInclusiveRecoJetsLabFrame", "Inclusive Reco Jets in Lab Frame", 4, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsLabFrame->Sumw2();
    hInclusiveRecoJetsLabFrame_W = new THnSparseD("hInclusiveRecoJetsLabFrame_W", "Inclusive Reco Jets in Lab Frame Weighted", 4, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsLabFrame_W->Sumw2();
    hInclusiveRecoJetsCMFrame = new THnSparseD("hInclusiveRecoJetsCMFrame", "Inclusive Reco Jets in CM Frame", 4, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsCMFrame->Sumw2();
    hInclusiveRecoJetsCMFrame_W = new THnSparseD("hInclusiveRecoJetsCMFrame_W", "Inclusive Reco Jets in CM Frame Weighted", 4, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsCMFrame_W->Sumw2();
    hSelectedInclusiveRecoJetsMidRapidity_W = new THnSparseD("hSelectedInclusiveRecoJetsMidRapidity_W", "Inclusive Reco Jets (JetPt > 50.0) MidRapidity Weighted", 4, JetBins, JetMin, JetMax);
    hSelectedInclusiveRecoJetsMidRapidity_W->Sumw2();
    if (fIsMC)
    {
        hInclusiveGenJetsLabFrame = new THnSparseD("hInclusiveGenJetsLabFrame", "Inclusive Gen Jets in Lab Frame", 4, JetBins, JetMin, JetMax);
        hInclusiveGenJetsLabFrame->Sumw2();
        hInclusiveGenJetsLabFrame_W = new THnSparseD("hInclusiveGenJetsLabFrame_W", "Inclusive Gen Jets in Lab Frame Weighted", 4, JetBins, JetMin, JetMax);
        hInclusiveGenJetsLabFrame_W->Sumw2();
        hInclusiveGenJetsCMFrame = new THnSparseD("hInclusiveGenJetsCMFrame", "Inclusive Gen Jets in CM Frame", 4, JetBins, JetMin, JetMax);
        hInclusiveGenJetsCMFrame->Sumw2();
        hInclusiveGenJetsCMFrame_W = new THnSparseD("hInclusiveGenJetsCMFrame_W", "Inclusive Gen Jets in CM Frame Weighted", 4, JetBins, JetMin, JetMax);
        hInclusiveGenJetsCMFrame_W->Sumw2();
        hSelectedInclusiveGenJetsMidRapidity_W = new THnSparseD("hSelectedInclusiveGenJetsMidRapidity_W", "Inclusive Gen Jets (JetPt > 50.0) MidRapidity Weighted", 4, JetBins, JetMin, JetMax);
        hSelectedInclusiveGenJetsMidRapidity_W->Sumw2();
        hInclusiveRefJetsLabFrame = new THnSparseD("hInclusiveRefJetsLabFrame", "Inclusive Ref Jets in Lab Frame", 4, JetBins, JetMin, JetMax);
        hInclusiveRefJetsLabFrame->Sumw2();
        hInclusiveRefJetsLabFrame_W = new THnSparseD("hInclusiveRefJetsLabFrame_W", "Inclusive Ref Jets in Lab Frame Weighted", 4, JetBins, JetMin, JetMax);
        hInclusiveRefJetsLabFrame_W->Sumw2();
        hInclusiveRefJetsCMFrame = new THnSparseD("hInclusiveRefJetsCMFrame", "Inclusive Ref Jets in CM Frame", 4, JetBins, JetMin, JetMax);
        hInclusiveRefJetsCMFrame->Sumw2();
        hInclusiveRefJetsCMFrame_W = new THnSparseD("hInclusiveRefJetsCMFrame_W", "Inclusive Ref Jets in CM Frame Weighted", 4, JetBins, JetMin, JetMax);
        hInclusiveRefJetsCMFrame_W->Sumw2();
        hSelectedInclusiveRefJetsMidRapidity_W = new THnSparseD("hSelectedInclusiveRefJetsMidRapidity_W", "Inclusive Ref Jets (JetPt > 50.0) MidRapidity Weighted", 4, JetBins, JetMin, JetMax);
        hSelectedInclusiveRefJetsMidRapidity_W->Sumw2();
    }
    hInclusiveRecoJetPtVsEtaCMFrame_W = new TH2D("hInclusiveRecoJetPtVsEtaCMFrame_W", "Inclusive Reco Jet Pt vs Eta in CM Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveRecoJetPtVsEtaCMFrame_W->Sumw2();
    hInclusiveRecoJetPtVsEtaLabFrame_W = new TH2D("hInclusiveRecoJetPtVsEtaLabFrame_W", "Inclusive Reco Jet Pt vs Eta in Lab Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveRecoJetPtVsEtaLabFrame_W->Sumw2();
    hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W = new TH2D("hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W", "Inclusive Uncorrected Reco Jet Pt vs Eta in CM Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Sumw2();
    hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W = new TH2D("hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W", "Inclusive Uncorrected Reco Jet Pt vs Eta in Lab Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Sumw2();

    int LeadSLeadJetBins[7] = {200, 100, 64, 200, 100, 64, nMultiplicityBins};
    Double_t LeadSLeadJetMin[7] = {0.0, -5.0, -TMath::Pi(), 0.0, -5.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t LeadSLeadJetMax[7] = {1000.0, 5.0, TMath::Pi(), 1000.0, 5.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};

    hLeadSubLeadJets = new THnSparseD("hLeadSubLeadJets", "Lead vs SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets->Sumw2();
    hLeadSubLeadJets_W = new THnSparseD("hLeadSubLeadJets_W", "Lead vs SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_W->Sumw2();
    hLeadSubLeadJets_MidRapidity_W = new THnSparseD("hLeadSubLeadJets_MidRapidity_W", "Lead vs SubLead Pt MidRapidity Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_MidRapidity_W->Sumw2();
    hLeadSubLeadJets_WithDijet_W = new THnSparseD("hLeadSubLeadJets_WithDijet_W", "Lead vs SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_WithDijet_W->Sumw2();
    if (fIsMC)
    {
        hGenLeadingVsGenSubLeading_WO_DiJet_W = new TH2D("hGenLeadingVsGenSubLeading_WO_DiJet_W", "Gen Leading vs Gen SubLeading Jet", 100, 0., 1000., 100, 0., 1000.);
        hGenLeadingVsGenSubLeading_WO_DiJet_W->Sumw2();
        hRefLeadingVsRefSubLeadingMatched_W = new TH2D("hRefLeadingVsRefSubLeadingMatched_W", "Ref Leading vs Ref SubLeading Jet", 100, 0., 1000., 100, 0., 1000.);
        hRefLeadingVsRefSubLeadingMatched_W->Sumw2();
        hGenLeadGenSubLeadJets = new THnSparseD("hGenLeadGenSubLeadJets", "Gen Lead vs Gen SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets->Sumw2();
        hGenLeadGenSubLeadJets_W = new THnSparseD("hGenLeadGenSubLeadJets_W", "Gen Lead vs Gen SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_W->Sumw2();
        hGenLeadGenSubLeadJets_MidRapidity_W = new THnSparseD("hGenLeadGenSubLeadJets_MidRapidity_W", "Gen Lead vs Gen SubLead Pt MidRapidity Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_MidRapidity_W->Sumw2();
        hGenLeadGenSubLeadJets_WithDijet_W = new THnSparseD("hGenLeadGenSubLeadJets_WithDijet_W", "Gen Lead vs Gen SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_WithDijet_W->Sumw2();
        hRefLeadRefSubLeadJets = new THnSparseD("hRefLeadRefSubLeadJets", "Ref Lead vs Ref SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets->Sumw2();
        hRefLeadRefSubLeadJets_W = new THnSparseD("hRefLeadRefSubLeadJets_W", "Ref Lead vs Ref SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_W->Sumw2();
        hRefLeadRefSubLeadJets_MidRapidity_W = new THnSparseD("hRefLeadRefSubLeadJets_MidRapidity_W", "Ref Lead vs Ref SubLead Pt MidRapidity Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_MidRapidity_W->Sumw2();
        hRefLeadRefSubLeadJets_WithDijet_W = new THnSparseD("hRefLeadRefSubLeadJets_WithDijet_W", "Ref Lead vs Ref SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_WithDijet_W->Sumw2();
    }

    const int nDphiBins = 30; // number of bins
    double DphiBins[nDphiBins + 1] = {0.0, TMath::Pi() / 5., TMath::Pi() / 3., (3. / 7.) * TMath::Pi(), TMath::Pi() / 2., (4. / 7.) * TMath::Pi(), (3. / 5.) * TMath::Pi(), 1.93731547, 1.98967535, 2.04203522, 2.0943951, 2.14675498, 2.19911486, 2.25147474, 2.30383461, 2.35619449, 2.40855437, 2.46091425, 2.51327412, 2.565634, 2.61799388, 2.67035376, 2.72271363, 2.77507351, 2.82743339, 2.87979327, 2.93215314, 2.98451302, 3.0368729, 3.08923278, TMath::Pi()};
    // const int nXjAjBins = 16; // number of bins
    // double XjBins[nXjAjBins + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};
    const int nXjAjBins = 40; // number of bins
    double XjBins[nXjAjBins + 1] = {0.0, 0.025, 0.05, 0.075, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275, 0.3, 0.325, 0.35, 0.375, 0.4, 0.425, 0.45, 0.475, 0.5, 0.525, 0.55, 0.575, 0.6, 0.625, 0.65, 0.675, 0.7, 0.725, 0.75, 0.775, 0.8, 0.825, 0.85, 0.875, 0.9, 0.925, 0.95, 0.975, 1.0};

    const int nXjAjBins_ER = 26; // number of bins
    double XjBins_ER[nXjAjBins_ER + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5};

    int QuenchBins[5] = {nXjAjBins, nDphiBins, 100, 100, nMultiplicityBins};
    Double_t QuenchMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMax[5] = {2.0, TMath::Pi(), 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    double multBinArray[fMultiplicityBins.size()];
    copy(fMultiplicityBins.begin(), fMultiplicityBins.end(), multBinArray);

    hRecoQuenching_W = new THnSparseD("hRecoQuenching_W", "Reco Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    hRecoQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hRecoQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hRecoQuenching_W->Sumw2();
    hDeltaPhi_W = new TH1D("hDeltaPhi_W", "Delta Phi Distribution Weighted", nDphiBins, DphiBins);
    hDeltaPhi_W->Sumw2();
    hDeltaPhi_WithDiJet_W = new TH1D("hDeltaPhi_WithDiJet_W", "Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
    hDeltaPhi_WithDiJet_W->Sumw2();
    hMultVsXj_W = new TH2D("hMultVsXj_W", "Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hMultVsXj_W->Sumw2();
    hMultVsXj_DiJetW = new TH2D("hMultVsXj_DiJetW", "Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hMultVsXj_DiJetW->Sumw2();

    if (fIsMC)
    {
        hGenQuenching_W = new THnSparseD("hGenQuenching_W", "Gen Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
        hGenQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
        hGenQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
        hGenQuenching_W->Sumw2();
        hGenDeltaPhi_W = new TH1D("hGenDeltaPhi_W", "Gen Delta Phi Distribution Weighted", nDphiBins, DphiBins);
        hGenDeltaPhi_W->Sumw2();
        hGenDeltaPhi_WithDiJet_W = new TH1D("hGenDeltaPhi_WithDiJet_W", "Gen Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
        hGenDeltaPhi_WithDiJet_W->Sumw2();
        hMultVsRefXj_W = new TH2D("hRefXj_W", "RefXj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
        hMultVsRefXj_W->Sumw2();
        hMultVsRefXj_DiJetW = new TH2D("hRefXj_DiJetW", "RefXj Distribution XjWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
        hMultVsRefXj_DiJetW->Sumw2();
        hMultVsRefXj_ER_W = new TH2D("hRefXj_ER_W", "RefXj Distribution ER Weighted", nXjAjBins_ER, XjBins_ER, nMultiplicityBins, multBinArray);
        hMultVsRefXj_ER_W->Sumw2();
        hMultVsRefXj_ER_DiJetW = new TH2D("hRefXj_ER_DiJetW", "RefXj Distribution ER XjWeighted", nXjAjBins_ER, XjBins_ER, nMultiplicityBins, multBinArray);
        hMultVsRefXj_ER_DiJetW->Sumw2();
        hMultVsGenXj_W = new TH2D("hGenXj_W", "Gen Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
        hMultVsGenXj_W->Sumw2();
        hMultVsGenXj_DiJetW = new TH2D("hGenXj_DiJetW", "Gen Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
        hMultVsGenXj_DiJetW->Sumw2();
    }
    Float_t LeadSubLeadPtBins[] = {50., 60., 70., 80., 90., 100., 110., 120., 130., 140., 150., 160., 170., 180., 190., 200., 220., 240., 260., 280., 300., 350., 400., 450., 500., 600., 700., 1200.};
    Int_t nLeadSubLeadPtBins = sizeof(LeadSubLeadPtBins) / sizeof(Float_t) - 1;
    hLeadPtvsSubLeadPt_PtHatW = new TH2D("hLeadPtvsSubLeadPt_PtHatW", "Lead Pt vs SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt_PtHatW->Sumw2();
    hLeadPtvsSubLeadPt_DiJetW = new TH2D("hLeadPtvsSubLeadPt_DiJetW", "Lead Pt vs SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt_DiJetW->Sumw2();

    if (fIsMC)
    {
        hGenLeadPtvsGenSubLeadPt_PtHatW = new TH2D("hGenLeadPtvsGenSubLeadPt_PtHatW", "Gen Lead Pt vs Gen SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
        hGenLeadPtvsGenSubLeadPt_PtHatW->Sumw2();
        hGenLeadPtvsGenSubLeadPt_DiJetW = new TH2D("hGenLeadPtvsGenSubLeadPt_DiJetW", "Gen Lead Pt vs Gen SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
        hGenLeadPtvsGenSubLeadPt_DiJetW->Sumw2();

        hRefLeadPtvsRefSubLeadPt_PtHatW = new TH2D("hRefLeadPtvsRefSubLeadPt_PtHatW", "Ref Lead Pt vs Ref SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
        hRefLeadPtvsRefSubLeadPt_PtHatW->Sumw2();
        hRefLeadPtvsRefSubLeadPt_DiJetW = new TH2D("hRefLeadPtvsRefSubLeadPt_DiJetW", "Ref Lead Pt vs Ref SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
        hRefLeadPtvsRefSubLeadPt_DiJetW->Sumw2();

        hRecoJES_W = new TH2D("hRecoJES_W", "Reco JES Weighted", 200, 0.0, 5.0, 200, 0.0, 1000.0);
        hRecoJES_W->Sumw2();
        hRefJES_W = new TH2D("hRefJES_W", "Ref JES Weighted", 200, 0.0, 5.0, 200, 0.0, 1000.0);
        hRefJES_W->Sumw2();
    }
}

void HistoManagerDiJet::projectHistograms()
{
    TH1D *iProjection;

    iProjection = hInclusiveRecoJetsCMFrame->Projection(0);
    hInclusiveRecoJetPt = (TH1D *)iProjection->Clone("hInclusiveRecoJetPt");
    hInclusiveRecoJetPt->SetTitle("Inclusive Reco Jet Pt");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame_W->Projection(0);
    hInclusiveRecoJetPt_W = (TH1D *)iProjection->Clone("hInclusiveRecoJetPt_W");
    hInclusiveRecoJetPt_W->SetTitle("Inclusive Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hSelectedInclusiveRecoJetsMidRapidity_W->Projection(0);
    hSelectedInclusiveRecoJetPt_MidRapidity_W = (TH1D *)iProjection->Clone("hSelectedInclusiveRecoJetPt_MidRapidity_W");
    hSelectedInclusiveRecoJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Reco Jet Pt MidRapidity Weighted");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame->Projection(1);
    hInclusiveRecoJetEtaCMFrame = (TH1D *)iProjection->Clone("hInclusiveRecoJetEtaCMFrame");
    hInclusiveRecoJetEtaCMFrame->SetTitle("Inclusive Reco Jet Eta CM Frame");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame_W->Projection(1);
    hInclusiveRecoJetEtaCMFrame_W = (TH1D *)iProjection->Clone("hInclusiveRecoJetEtaCMFrame_W");
    hInclusiveRecoJetEtaCMFrame_W->SetTitle("Inclusive Reco Jet Eta CM Frame Weighted");
    delete iProjection;

    iProjection = hInclusiveRecoJetsLabFrame->Projection(1);
    hInclusiveRecoJetEtaLabFrame = (TH1D *)iProjection->Clone("hInclusiveRecoJetEtaLabFrame");
    hInclusiveRecoJetEtaLabFrame->SetTitle("Inclusive Reco Jet Eta Lab Frame");
    delete iProjection;

    iProjection = hInclusiveRecoJetsLabFrame_W->Projection(1);
    hInclusiveRecoJetEtaLabFrame_W = (TH1D *)iProjection->Clone("hInclusiveRecoJetEtaLabFrame_W");
    hInclusiveRecoJetEtaLabFrame_W->SetTitle("Inclusive Reco Jet Eta Lab Frame Weighted");
    delete iProjection;

    iProjection = hSelectedInclusiveRecoJetsMidRapidity_W->Projection(1);
    hSelectedInclusiveRecoJetEtaMidRapidity_W = (TH1D *)iProjection->Clone("hSelectedInclusiveRecoJetEtaMidRapidity_W");
    hSelectedInclusiveRecoJetEtaMidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Reco Jet Eta MidRapidity Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets->Projection(0);
    hLeadingRecoJetPt = (TH1D *)iProjection->Clone("hLeadingRecoJetPt");
    hLeadingRecoJetPt->SetTitle("Leading Reco Jet Pt");
    delete iProjection;

    iProjection = hLeadSubLeadJets_W->Projection(0);
    hLeadingRecoJetPt_W = (TH1D *)iProjection->Clone("hLeadingRecoJetPt_W");
    hLeadingRecoJetPt_W->SetTitle("Leading Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets->Projection(3);
    hSubLeadingRecoJetPt = (TH1D *)iProjection->Clone("hSubLeadingRecoJetPt");
    hSubLeadingRecoJetPt->SetTitle("SubLeading Reco Jet Pt");
    delete iProjection;

    iProjection = hLeadSubLeadJets_W->Projection(3);
    hSubLeadingRecoJetPt_W = (TH1D *)iProjection->Clone("hSubLeadingRecoJetPt_W");
    hSubLeadingRecoJetPt_W->SetTitle("SubLeading Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_W->Projection(0);
    hLeadingRecoJetPtWithDijet_W = (TH1D *)iProjection->Clone("hLeadingRecoJetPtWithDijet_W");
    hLeadingRecoJetPtWithDijet_W->SetTitle("Leading Reco Jet Pt With Dijet Present Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_W->Projection(3);
    hSubLeadingRecoJetPtWithDijet_W = (TH1D *)iProjection->Clone("hSubLeadingRecoJetPtWithDijet_W");
    hSubLeadingRecoJetPtWithDijet_W->SetTitle("SubLeading Reco Jet Pt With Dijet Present Weighted");
    delete iProjection;

    if (fIsMC)
    {
        iProjection = hInclusiveGenJetsCMFrame->Projection(0);
        hInclusiveGenJetPt = (TH1D *)iProjection->Clone("hInclusiveGenJetPt");
        hInclusiveGenJetPt->SetTitle("Inclusive Gen Jet Pt");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame_W->Projection(0);
        hInclusiveGenJetPt_W = (TH1D *)iProjection->Clone("hInclusiveGenJetPt_W");
        hInclusiveGenJetPt_W->SetTitle("Inclusive Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveGenJetsMidRapidity_W->Projection(0);
        hSelectedInclusiveGenJetPt_MidRapidity_W = (TH1D *)iProjection->Clone("hSelectedInclusiveGenJetPt_MidRapidity_W");
        hSelectedInclusiveGenJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Gen Jet Pt MidRapidity Weighted");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame->Projection(1);
        hInclusiveGenJetEtaCMFrame = (TH1D *)iProjection->Clone("hInclusiveGenJetEtaCMFrame");
        hInclusiveGenJetEtaCMFrame->SetTitle("Inclusive Gen Jet Eta CM Frame");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame_W->Projection(1);
        hInclusiveGenJetEtaCMFrame_W = (TH1D *)iProjection->Clone("hInclusiveGenJetEtaCMFrame_W");
        hInclusiveGenJetEtaCMFrame_W->SetTitle("Inclusive Gen Jet Eta CM Frame Weighted");
        delete iProjection;

        iProjection = hInclusiveGenJetsLabFrame->Projection(1);
        hInclusiveGenJetEtaLabFrame = (TH1D *)iProjection->Clone("hInclusiveGenJetEtaLabFrame");
        hInclusiveGenJetEtaLabFrame->SetTitle("Inclusive Gen Jet Eta Lab Frame");
        delete iProjection;

        iProjection = hInclusiveGenJetsLabFrame_W->Projection(1);
        hInclusiveGenJetEtaLabFrame_W = (TH1D *)iProjection->Clone("hInclusiveGenJetEtaLabFrame_W");
        hInclusiveGenJetEtaLabFrame_W->SetTitle("Inclusive Gen Jet Eta Lab Frame Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveGenJetsMidRapidity_W->Projection(1);
        hSelectedInclusiveGenJetEtaMidRapidity_W = (TH1D *)iProjection->Clone("hSelectedInclusiveGenJetEtaMidRapidity_W");
        hSelectedInclusiveGenJetEtaMidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Gen Jet Eta MidRapidity Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets->Projection(0);
        hLeadingGenJetPt = (TH1D *)iProjection->Clone("hLeadingGenJetPt");
        hLeadingGenJetPt->SetTitle("Leading Gen Jet Pt");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_W->Projection(0);
        hLeadingGenJetPt_W = (TH1D *)iProjection->Clone("hLeadingGenJetPt_W");
        hLeadingGenJetPt_W->SetTitle("Leading Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets->Projection(3);
        hSubLeadingGenJetPt = (TH1D *)iProjection->Clone("hSubLeadingGenJetPt");
        hSubLeadingGenJetPt->SetTitle("SubLeading Gen Jet Pt");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_W->Projection(3);
        hSubLeadingGenJetPt_W = (TH1D *)iProjection->Clone("hSubLeadingGenJetPt_W");
        hSubLeadingGenJetPt_W->SetTitle("SubLeading Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_W->Projection(0);
        hLeadingGenJetPtWithDijet_W = (TH1D *)iProjection->Clone("hLeadingGenJetPtWithDijet_W");
        hLeadingGenJetPtWithDijet_W->SetTitle("Leading Gen Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_W->Projection(3);
        hSubLeadingGenJetPtWithDijet_W = (TH1D *)iProjection->Clone("hSubLeadingGenJetPtWithDijet_W");
        hSubLeadingGenJetPtWithDijet_W->SetTitle("SubLeading Gen Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hInclusiveRefJetsCMFrame->Projection(0);
        hInclusiveRefJetPt = (TH1D *)iProjection->Clone("hInclusiveRefJetPt");
        hInclusiveRefJetPt->SetTitle("Inclusive Ref Jet Pt");
        delete iProjection;

        iProjection = hInclusiveRefJetsCMFrame_W->Projection(0);
        hInclusiveRefJetPt_W = (TH1D *)iProjection->Clone("hInclusiveRefJetPt_W");
        hInclusiveRefJetPt_W->SetTitle("Inclusive Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveRefJetsMidRapidity_W->Projection(0);
        hSelectedInclusiveRefJetPt_MidRapidity_W = (TH1D *)iProjection->Clone("hSelectedInclusiveRefJetPt_MidRapidity_W");
        hSelectedInclusiveRefJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Ref Jet Pt MidRapidity Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets->Projection(0);
        hLeadingRefJetPt = (TH1D *)iProjection->Clone("hLeadingRefJetPt");
        hLeadingRefJetPt->SetTitle("Leading Ref Jet Pt");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_W->Projection(0);
        hLeadingRefJetPt_W = (TH1D *)iProjection->Clone("hLeadingRefJetPt_W");
        hLeadingRefJetPt_W->SetTitle("Leading Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets->Projection(3);
        hSubLeadingRefJetPt = (TH1D *)iProjection->Clone("hSubLeadingRefJetPt");
        hSubLeadingRefJetPt->SetTitle("SubLeading Ref Jet Pt");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_W->Projection(3);
        hSubLeadingRefJetPt_W = (TH1D *)iProjection->Clone("hSubLeadingRefJetPt_W");
        hSubLeadingRefJetPt_W->SetTitle("SubLeading Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_W->Projection(0);
        hLeadingRefJetPtWithDijet_W = (TH1D *)iProjection->Clone("hLeadingRefJetPtWithDijet_W");
        hLeadingRefJetPtWithDijet_W->SetTitle("Leading Ref Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_W->Projection(3);
        hSubLeadingRefJetPtWithDijet_W = (TH1D *)iProjection->Clone("hSubLeadingRefJetPtWithDijet_W");
        hSubLeadingRefJetPtWithDijet_W->SetTitle("SubLeading Ref Jet Pt With Dijet Present Weighted");
        delete iProjection;
    }
    iProjection = hMultVsXj_W->ProjectionX();
    hXj_C0_W = (TH1D *)iProjection->Clone("hXj_C0_W");
    hXj_C0_W->SetTitle("Xj Projection C0 Weighted");
    delete iProjection;

    iProjection = hMultVsXj_DiJetW->ProjectionX();
    hXj_C0_DiJetW = (TH1D *)iProjection->Clone("hXj_C0_DiJetW");
    hXj_C0_DiJetW->SetTitle("Xj Projection C0 Dijet Weighted");
    delete iProjection;

    if (fIsMC)
    {
        iProjection = hMultVsGenXj_W->ProjectionX();
        hGenXj_C0_W = (TH1D *)iProjection->Clone("hGenXj_C0_W");
        hGenXj_C0_W->SetTitle("Gen Xj Projection C0 Weighted");
        delete iProjection;

        iProjection = hMultVsGenXj_DiJetW->ProjectionX();
        hGenXj_C0_DiJetW = (TH1D *)iProjection->Clone("hGenXj_C0_DiJetW");
        hGenXj_C0_DiJetW->SetTitle("Gen Xj Projection C0 Dijet Weighted");
        delete iProjection;
    }

    for (Int_t i = 0; i < 5; i++)
    {
        hXj_Projection_W[i] = hMultVsXj_W->ProjectionX(Form("hXj_C%i_W", i + 1), hMultVsXj_W->GetYaxis()->FindBin(i + 1), hMultVsXj_W->GetYaxis()->FindBin(i + 1));
        hXj_Projection_W[i]->SetTitle(Form("Xj Projection C%i Weighted", i + 1));
        hXj_Projection_DiJetW[i] = hMultVsXj_DiJetW->ProjectionX(Form("hXj_C%i_DiJetW", i + 1), hMultVsXj_DiJetW->GetYaxis()->FindBin(i + 1), hMultVsXj_DiJetW->GetYaxis()->FindBin(i + 1));
        hXj_Projection_DiJetW[i]->SetTitle(Form("Xj Projection C%i Dijet Weighted", i + 1));
        if (fIsMC)
        {
            hGenXj_Projection_W[i] = hMultVsGenXj_W->ProjectionX(Form("hGenXj_C%i_W", i + 1), hMultVsGenXj_W->GetYaxis()->FindBin(i + 1), hMultVsGenXj_W->GetYaxis()->FindBin(i + 1));
            hGenXj_Projection_W[i]->SetTitle(Form("Gen Xj Projection C%i Weighted", i + 1));
            hGenXj_Projection_DiJetW[i] = hMultVsGenXj_DiJetW->ProjectionX(Form("hGenXj_C%i_DiJetW", i + 1), hMultVsGenXj_DiJetW->GetYaxis()->FindBin(i + 1), hMultVsGenXj_DiJetW->GetYaxis()->FindBin(i + 1));
            hGenXj_Projection_DiJetW[i]->SetTitle(Form("Gen Xj Projection C%i Dijet Weighted", i + 1));
        }
    }
}

void HistoManagerDiJet ::writeOutput()
{
    gDirectory->mkdir("Events");
    gDirectory->cd("Events");

    hHiBin->Write();
    hHiBin_W->Write();
    hVz->Write();
    hVz_W->Write();
    hVzWithDijet_W->Write();
    hRecoMultiplicity_W->Write();
    hCorrectedMultiplicity_W->Write();
    hSelectedMultiplicity_W->Write();
    hMultiplicities->Write();
    hMultiplicities_W->Write();
    hInJetMultiplicity_W->Write();
    if (fIsMC)
    {
        hPtHat->Write();
        hPtHat_W->Write();
        hGenInJetMultiplicity_W->Write();
        hGenMultiplicity_W->Write();
        hSubEventMultiplicity_W->Write();
    }
    hNEventsInMult->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Jets");
    gDirectory->cd("Jets");

    hInclusiveUncorrectedRecoJets->Write();
    hInclusiveUncorrectedRecoJets_W->Write();
    hInclusiveRecoJetsLabFrame->Write();
    hInclusiveRecoJetsLabFrame_W->Write();
    hInclusiveRecoJetsCMFrame->Write();
    hInclusiveRecoJetsCMFrame_W->Write();
    hSelectedInclusiveRecoJetsMidRapidity_W->Write();
    hInclusiveRecoJetPtVsEtaLabFrame_W->Write();
    hInclusiveRecoJetPtVsEtaCMFrame_W->Write();
    hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Write();
    hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Write();
    if (fIsMC)
    {
        hInclusiveGenJetsLabFrame->Write();
        hInclusiveGenJetsLabFrame_W->Write();
        hInclusiveGenJetsCMFrame->Write();
        hInclusiveGenJetsCMFrame_W->Write();
        hSelectedInclusiveGenJetsMidRapidity_W->Write();
        hInclusiveRefJetsCMFrame->Write();
        hInclusiveRefJetsCMFrame_W->Write();
        hInclusiveRefJetsLabFrame->Write();
        hInclusiveRefJetsLabFrame_W->Write();
        hSelectedInclusiveRefJetsMidRapidity_W->Write();
    }
    if (fIsMC)
    {
        hRecoJES_W->Write();
        hRefJES_W->Write();
    }

    hLeadSubLeadJets->Write();
    hLeadSubLeadJets_W->Write();
    hLeadSubLeadJets_MidRapidity_W->Write();
    hLeadSubLeadJets_WithDijet_W->Write();
    hLeadPtvsSubLeadPt_PtHatW->Write();
    hLeadPtvsSubLeadPt_DiJetW->Write();

    if (fIsMC)
    {
        hGenLeadGenSubLeadJets->Write();
        hGenLeadGenSubLeadJets_W->Write();
        hGenLeadGenSubLeadJets_MidRapidity_W->Write();
        hGenLeadGenSubLeadJets_WithDijet_W->Write();
        hGenLeadPtvsGenSubLeadPt_PtHatW->Write();
        hGenLeadPtvsGenSubLeadPt_DiJetW->Write();
        hRefLeadRefSubLeadJets->Write();
        hRefLeadRefSubLeadJets_W->Write();
        hRefLeadRefSubLeadJets_MidRapidity_W->Write();
        hRefLeadRefSubLeadJets_WithDijet_W->Write();
        hRefLeadPtvsRefSubLeadPt_PtHatW->Write();
        hRefLeadPtvsRefSubLeadPt_DiJetW->Write();
        hGenLeadingVsGenSubLeading_WO_DiJet_W->Write();
        hRefLeadingVsRefSubLeadingMatched_W->Write();
    }

    gDirectory->cd("..");
    gDirectory->mkdir("Quenching");
    gDirectory->cd("Quenching");
    hRecoQuenching_W->Write();
    hDeltaPhi_W->Write();
    hDeltaPhi_WithDiJet_W->Write();
    hMultVsXj_W->Write();
    hMultVsXj_DiJetW->Write();
    hNDijetEvent->Write();

    if (fIsMC)
    {
        hMultVsRefXj_W->Write();
        hMultVsRefXj_DiJetW->Write();
        hMultVsRefXj_ER_W->Write();
        hMultVsRefXj_ER_DiJetW->Write();
        hGenQuenching_W->Write();
        hGenDeltaPhi_W->Write();
        hGenDeltaPhi_WithDiJet_W->Write();
        hMultVsGenXj_W->Write();
        hMultVsGenXj_DiJetW->Write();
        hNGenDijetEvent->Write();
    }

    gDirectory->cd("..");
    gDirectory->mkdir("Projections");
    gDirectory->cd("Projections");
    hInclusiveRecoJetPt->Write();
    hInclusiveRecoJetPt_W->Write();
    hSelectedInclusiveRecoJetPt_MidRapidity_W->Write();
    hInclusiveRecoJetEtaCMFrame->Write();
    hInclusiveRecoJetEtaCMFrame_W->Write();
    hInclusiveRecoJetEtaLabFrame->Write();
    hInclusiveRecoJetEtaLabFrame_W->Write();
    hSelectedInclusiveRecoJetEtaMidRapidity_W->Write();
    hLeadingRecoJetPt->Write();
    hLeadingRecoJetPt_W->Write();
    hSubLeadingRecoJetPt->Write();
    hSubLeadingRecoJetPt_W->Write();
    hLeadingRecoJetPtWithDijet_W->Write();
    hSubLeadingRecoJetPtWithDijet_W->Write();
    if (fIsMC)
    {
        hInclusiveGenJetPt->Write();
        hInclusiveGenJetPt_W->Write();
        hSelectedInclusiveGenJetPt_MidRapidity_W->Write();
        hInclusiveGenJetEtaCMFrame->Write();
        hInclusiveGenJetEtaCMFrame_W->Write();
        hInclusiveGenJetEtaLabFrame->Write();
        hInclusiveGenJetEtaLabFrame_W->Write();
        hSelectedInclusiveGenJetEtaMidRapidity_W->Write();
        hLeadingGenJetPt->Write();
        hLeadingGenJetPt_W->Write();
        hSubLeadingGenJetPt->Write();
        hSubLeadingGenJetPt_W->Write();
        hLeadingGenJetPtWithDijet_W->Write();
        hSubLeadingGenJetPtWithDijet_W->Write();
        hInclusiveRefJetPt->Write();
        hInclusiveRefJetPt_W->Write();
        hSelectedInclusiveRefJetPt_MidRapidity_W->Write();
        hLeadingRefJetPt->Write();
        hLeadingRefJetPt_W->Write();
        hSubLeadingRefJetPt->Write();
        hSubLeadingRefJetPt_W->Write();
        hLeadingRefJetPtWithDijet_W->Write();
        hSubLeadingRefJetPtWithDijet_W->Write();
    }
    hXj_C0_W->Write();
    hXj_C0_DiJetW->Write();
    if (fIsMC)
    {
        hGenXj_C0_W->Write();
        hGenXj_C0_DiJetW->Write();
    }
    for (Int_t i = 0; i < 5; i++)
    {
        hXj_Projection_W[i]->Write();
        hXj_Projection_DiJetW[i]->Write();
        if (fIsMC)
        {
            hGenXj_Projection_W[i]->Write();
            hGenXj_Projection_DiJetW[i]->Write();
        }
    }
}
