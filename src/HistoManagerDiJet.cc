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
#include "../interface/HistoManagerDiJet.h"

// C++ Headers
#include <iostream>

ClassImp(HistoManagerDiJet)

    HistoManagerDiJet::HistoManagerDiJet() : BaseHistoManager()
{
    /* Empty*/
}

HistoManagerDiJet::~HistoManagerDiJet()
{
}

void HistoManagerDiJet::setCollisionSystem(const ForestReader& reader)
{
    std::cout << "============HistoManagerDiJet::SettingCollisionSystem============" << std::endl;

    ForestReader::CollidingSystemType collSystem = reader.getCollidingSystem();
    {
        if (collSystem == ForestReader::CollidingSystemType::pp)
        {
            fCollSystem = CollisionSystem::pp;
            std::cout << "Collision System set to be : pp" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::pPb)
        {
            fCollSystem = CollisionSystem::pPb;
            std::cout << "Collision System set to be : pPb" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::PbPb)
        {
            fCollSystem = CollisionSystem::PbPb;
            std::cout << "Collision System set to be : PbPb" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::OO)
        {
            fCollSystem = CollisionSystem::OO;
            std::cout << "Collision System set to be : OO" << std::endl;
        }
        else
        {
            std::cerr << "Invalid collision system. Please choose from pp, pPb, PbPb or OO" << std::endl;
        }
        std::cout << "==================================[Done]================================" << std::endl;
    }
}

void HistoManagerDiJet::init()
{
    std::cout << std::endl;
    std::cout << "=======================================================================" << std::endl;

    std::cout << "============HistoManagerDiJet::init Initializing Histograms============" << std::endl;
    std::cout << "=======================================================================" << std::endl;

    std::cout << std::endl;
    setCollisionSystem(*fReader);
    int nMultiplicityBins = fMultiplicityBins.size() - 1;
    int nHiHFEnergyBins = fHiHFEnergyBins.size() - 1;
    int nLeadPtBins = fPtBins.size() - 1;
    int nXjAjBins = fXjBins.size() - 1;

    double* multBinArray = fMultiplicityBins.data();
    double* hiHFEnergyBinArray = fHiHFEnergyBins.data();
    double* leadPtBins = fPtBins.data();
    double* XjBins = fXjBins.data();

    hRecoMultiplicity_W = new TH1D("hRecoMultiplicity_W", "Reco Multiplicity Weighted", 600, 0.0, 600.0);
    hRecoMultiplicity_W->Sumw2();
    hCorrectedMultiplicity_W = new TH1D("hCorrectedMultiplicity_W", "Corrected Multiplicity Weighted", 600, 0.0, 600.0);
    hCorrectedMultiplicity_W->Sumw2();
    hSelectedMultiplicity_W = new TH1D("hSelectedMultiplicity", "Multiplicity Distribution after selection Weighted", 600, 0., 600.);
    hSelectedMultiplicity_W->Sumw2();
    hInJetMultiplicity_W = new TH2D("hInJetMultiplicity_W", "Multiplicity in Jets", 30, 0., 30., 600, 0., 600.);
    hInJetMultiplicity_W->Sumw2();

    hImpactParameter_W = new TH1D("hImpactParameter_W", "Impact Parameter Weighted", 150, 0, 15);
    hImpactParameter_W->Sumw2();
    hImpactParameterVsHiBin_W = new TH2D("hImpactParameterVsHiBin_W", "Impact Parameter vs HiBin Weighted", 200, 0., 200., 150, 0., 15.);
    hImpactParameterVsHiBin_W->Sumw2();
    hImpactParameterVsMultiplicity_W = new TH2D("hImpactParameterVsMultiplicity_W", "Impact Parameter vs Multiplicity Weighted", 700, 0., 700., 150, 0., 15.);
    hImpactParameterVsMultiplicity_W->Sumw2();

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
    hHiHF_PF = new TH1D("hHiHF_PF", "HiHF PF Distribution", 100, 0.0, 1000.0);
    hHiHF_PF->Sumw2();
    hHiHF_PF_W = new TH1D("hHiHF_PF_W", "HiHF PF Distribution Weighted", 100, 0.0, 1000.0);
    hHiHF_PF_W->Sumw2();
    hHiBinVsMultiplicity_W = new TH2D("hHiBinvsMultiplicity_W", "HiBin vs Multiplicity Weighted", 600, 0.0, 600., 200, 0.0, 200.);
    hHiBinVsMultiplicity_W->Sumw2();
    hHiBinVsCorrectedMultiplicity_W = new TH2D("hHiBinVsCorrectedMultiplicity_W", "HiBin vs Corrected Multiplicities Weighted", 600, 0., 600., 200, 0., 200.);
    hHiBinVsCorrectedMultiplicity_W->Sumw2();
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

    int MultBins[7] = {5000, 5000, 5000, 5000, 5000, 200, nMultiplicityBins};
    Double_t MultMin[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t MultMax[7] = {5000.0, 5000.0, 5000.0, 5000.0, 5000.0, 200, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hMultiplicities = new THnSparseD("hMultiplicities", "Multiplicity Distribution", 7, MultBins, MultMin, MultMax);
    hMultiplicities->GetAxis(6)->Set(MultBins[6], multBinArray);
    hMultiplicities->Sumw2();
    hMultiplicities_W = new THnSparseD("hMultiplicities_W", "Multiplicity Distribution with Weights", 7, MultBins, MultMin, MultMax);
    hMultiplicities_W->GetAxis(6)->Set(MultBins[6], multBinArray);
    hMultiplicities_W->Sumw2();
    hMultiplicities_DiJet_W = new THnSparseD("hMultiplicities_DiJet_W", "Multiplicity Distribution with Dijet Present", 7, MultBins, MultMin, MultMax);
    hMultiplicities_DiJet_W->GetAxis(6)->Set(MultBins[6], multBinArray);
    hMultiplicities_DiJet_W->Sumw2();

    int JetBins[5] = {200, 52, 64, 5, nMultiplicityBins};
    Double_t JetMin[5] = {0.0, -5.2, -TMath::Pi(), -2, fMultiplicityBins[0]};
    Double_t JetMax[5] = {1000.0, 5.2, TMath::Pi(), 2, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hInclusiveUncorrectedRecoJets = new THnSparseD("hInclusiveUncorrectedRecoJets", "Inclusive Uncorrected Reco Jets", 5, JetBins, JetMin, JetMax);
    hInclusiveUncorrectedRecoJets->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveUncorrectedRecoJets->Sumw2();
    hInclusiveUncorrectedRecoJets_W = new THnSparseD("hInclusiveUncorrectedRecoJets_W", "Inclusive Uncorrected Reco Jets Weighted", 5, JetBins, JetMin, JetMax);
    hInclusiveUncorrectedRecoJets_W->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveUncorrectedRecoJets_W->Sumw2();
    hInclusiveRecoJetsLabFrame = new THnSparseD("hInclusiveRecoJetsLabFrame", "Inclusive Reco Jets in Lab Frame", 5, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsLabFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveRecoJetsLabFrame->Sumw2();
    hInclusiveRecoJetsLabFrame_W = new THnSparseD("hInclusiveRecoJetsLabFrame_W", "Inclusive Reco Jets in Lab Frame Weighted", 5, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsLabFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveRecoJetsLabFrame_W->Sumw2();
    hInclusiveRecoJetsCMFrame = new THnSparseD("hInclusiveRecoJetsCMFrame", "Inclusive Reco Jets in CM Frame", 5, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsCMFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveRecoJetsCMFrame->Sumw2();
    hInclusiveRecoJetsCMFrame_W = new THnSparseD("hInclusiveRecoJetsCMFrame_W", "Inclusive Reco Jets in CM Frame Weighted", 5, JetBins, JetMin, JetMax);
    hInclusiveRecoJetsCMFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
    hInclusiveRecoJetsCMFrame_W->Sumw2();
    hSelectedInclusiveRecoJetsMidRapidity_W =
        new THnSparseD("hSelectedInclusiveRecoJetsMidRapidity_W", "Inclusive Reco Jets (JetPt > 50.0) MidRapidity Weighted", 5, JetBins, JetMin, JetMax);
    hSelectedInclusiveRecoJetsMidRapidity_W->GetAxis(4)->Set(JetBins[4], multBinArray);
    hSelectedInclusiveRecoJetsMidRapidity_W->Sumw2();
    if (fIsMC)
    {
        hInclusiveGenJetsLabFrame = new THnSparseD("hInclusiveGenJetsLabFrame", "Inclusive Gen Jets in Lab Frame", 5, JetBins, JetMin, JetMax);
        hInclusiveGenJetsLabFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveGenJetsLabFrame->Sumw2();
        hInclusiveGenJetsLabFrame_W = new THnSparseD("hInclusiveGenJetsLabFrame_W", "Inclusive Gen Jets in Lab Frame Weighted", 5, JetBins, JetMin, JetMax);
        hInclusiveGenJetsLabFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveGenJetsLabFrame_W->Sumw2();
        hInclusiveGenJetsCMFrame = new THnSparseD("hInclusiveGenJetsCMFrame", "Inclusive Gen Jets in CM Frame", 5, JetBins, JetMin, JetMax);
        hInclusiveGenJetsCMFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveGenJetsCMFrame->Sumw2();
        hInclusiveGenJetsCMFrame_W = new THnSparseD("hInclusiveGenJetsCMFrame_W", "Inclusive Gen Jets in CM Frame Weighted", 5, JetBins, JetMin, JetMax);
        hInclusiveGenJetsCMFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveGenJetsCMFrame_W->Sumw2();
        hSelectedInclusiveGenJetsMidRapidity_W =
            new THnSparseD("hSelectedInclusiveGenJetsMidRapidity_W", "Inclusive Gen Jets (JetPt > 50.0) MidRapidity Weighted", 5, JetBins, JetMin, JetMax);
        hSelectedInclusiveGenJetsMidRapidity_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hSelectedInclusiveGenJetsMidRapidity_W->Sumw2();
        hInclusiveRefJetsLabFrame = new THnSparseD("hInclusiveRefJetsLabFrame", "Inclusive Ref Jets in Lab Frame", 5, JetBins, JetMin, JetMax);
        hInclusiveRefJetsLabFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveRefJetsLabFrame->Sumw2();
        hInclusiveRefJetsLabFrame_W = new THnSparseD("hInclusiveRefJetsLabFrame_W", "Inclusive Ref Jets in Lab Frame Weighted", 5, JetBins, JetMin, JetMax);
        hInclusiveRefJetsLabFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveRefJetsLabFrame_W->Sumw2();
        hInclusiveRefJetsCMFrame = new THnSparseD("hInclusiveRefJetsCMFrame", "Inclusive Ref Jets in CM Frame", 5, JetBins, JetMin, JetMax);
        hInclusiveRefJetsCMFrame->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveRefJetsCMFrame->Sumw2();
        hInclusiveRefJetsCMFrame_W = new THnSparseD("hInclusiveRefJetsCMFrame_W", "Inclusive Ref Jets in CM Frame Weighted", 5, JetBins, JetMin, JetMax);
        hInclusiveRefJetsCMFrame_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hInclusiveRefJetsCMFrame_W->Sumw2();
        hSelectedInclusiveRefJetsMidRapidity_W =
            new THnSparseD("hSelectedInclusiveRefJetsMidRapidity_W", "Inclusive Ref Jets (JetPt > 50.0) MidRapidity Weighted", 5, JetBins, JetMin, JetMax);
        hSelectedInclusiveRefJetsMidRapidity_W->GetAxis(4)->Set(JetBins[4], multBinArray);
        hSelectedInclusiveRefJetsMidRapidity_W->Sumw2();
    }
    hInclusiveRecoJetPtVsEtaCMFrame_W = new TH2D("hInclusiveRecoJetPtVsEtaCMFrame_W", "Inclusive Reco Jet Pt vs Eta in CM Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveRecoJetPtVsEtaCMFrame_W->Sumw2();
    hInclusiveRecoJetPtVsEtaLabFrame_W =
        new TH2D("hInclusiveRecoJetPtVsEtaLabFrame_W", "Inclusive Reco Jet Pt vs Eta in Lab Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveRecoJetPtVsEtaLabFrame_W->Sumw2();
    hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W =
        new TH2D("hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W", "Inclusive Uncorrected Reco Jet Pt vs Eta in CM Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Sumw2();
    hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W =
        new TH2D("hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W", "Inclusive Uncorrected Reco Jet Pt vs Eta in Lab Frame Weighted", 100, -5., 5., 200, 0., 1000.);
    hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Sumw2();

    int JetFractionBins[5] = {200, 100, 64, 50, nMultiplicityBins};
    Double_t JetFractionMin[5] = {0.0, -5.0, -TMath::Pi(), 0.0, fMultiplicityBins[0]};
    Double_t JetFractionMax[5] = {1000.0, 5.0, TMath::Pi(), 50.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};

    hJetFlavorFractions_W = new THnSparseD("hJetFlavorFractions_W", "Jet Flavor Fractions Weighted", 5, JetFractionBins, JetFractionMin, JetFractionMax);
    hJetFlavorFractions_W->GetAxis(4)->Set(JetFractionBins[4], multBinArray);
    hJetFlavorFractions_W->Sumw2();

    int TrackBins[4] = {100, 60, 64, nMultiplicityBins};
    Double_t TrackMin[4] = {0.0, -3.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t TrackMax[4] = {5.0, 3.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};

    hRecoTracks = new THnSparseD("hRecoTracks", "Reco Tracks", 4, TrackBins, TrackMin, TrackMax);
    hRecoTracks->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hRecoTracks->Sumw2();
    hRecoTracks_W = new THnSparseD("hRecoTracks_W", "Reco Tracks Weighted", 4, TrackBins, TrackMin, TrackMax);
    hRecoTracks_W->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hRecoTracks_W->Sumw2();
    hRecoTracks_Pt1_W = new THnSparseD("hRecoTracks_Pt1_W", "Reco Tracks Pt > 1.0 Weighted", 4, TrackBins, TrackMin, TrackMax);
    hRecoTracks_Pt1_W->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hRecoTracks_Pt1_W->Sumw2();
    hGenTracks = new THnSparseD("hGenTracks", "Gen Tracks", 4, TrackBins, TrackMin, TrackMax);
    hGenTracks->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hGenTracks->Sumw2();
    hGenTracks_W = new THnSparseD("hGenTracks_W", "Gen Tracks Weighted", 4, TrackBins, TrackMin, TrackMax);
    hGenTracks_W->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hGenTracks_W->Sumw2();
    hGenTracks_Pt1_W = new THnSparseD("hGenTracks_Pt1_W", "Gen Tracks Pt > 1.0 Weighted", 4, TrackBins, TrackMin, TrackMax);
    hGenTracks_Pt1_W->GetAxis(3)->Set(TrackBins[3], multBinArray);
    hGenTracks_Pt1_W->Sumw2();

    int LeadSLeadJetBins[7] = {200, 100, 64, 200, 100, 64, nMultiplicityBins};
    Double_t LeadSLeadJetMin[7] = {0.0, -5.0, -TMath::Pi(), 0.0, -5.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t LeadSLeadJetMax[7] = {1000.0, 5.0, TMath::Pi(), 1000.0, 5.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};

    hLeadSubLeadJets = new THnSparseD("hLeadSubLeadJets", "Lead vs SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
    hLeadSubLeadJets->Sumw2();
    hLeadSubLeadJets_W = new THnSparseD("hLeadSubLeadJets_W", "Lead vs SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
    hLeadSubLeadJets_W->Sumw2();
    hLeadSubLeadJets_MidRapidity_W =
        new THnSparseD("hLeadSubLeadJets_MidRapidity_W", "Lead vs SubLead Pt MidRapidity Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_MidRapidity_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
    hLeadSubLeadJets_MidRapidity_W->Sumw2();
    hLeadSubLeadJets_WithDijet_W =
        new THnSparseD("hLeadSubLeadJets_WithDijet_W", "Lead vs SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_WithDijet_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
    hLeadSubLeadJets_WithDijet_W->Sumw2();
    hLeadSubLeadJets_WithDijet_DiJetW =
        new THnSparseD("hLeadSubLeadJets_WithDijet_DiJetW", "Lead vs SubLead Pt With Dijet With DiJetWeighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_WithDijet_DiJetW->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
    hLeadSubLeadJets_WithDijet_DiJetW->Sumw2();
    hAverageRecoPt_W = new TH1D("hAverageRecoPt_W", "Average Reco Jet Pt", 200, 0.0, 1000.);
    hAverageRecoPt_W->Sumw2();
    if (fIsMC)
    {
        hGenLeadingVsGenSubLeading_WO_DiJet_W = new TH2D("hGenLeadingVsGenSubLeading_WO_DiJet_W", "Gen Leading vs Gen SubLeading Jet", 100, 0., 1000., 100, 0., 1000.);
        hGenLeadingVsGenSubLeading_WO_DiJet_W->Sumw2();
        hGenLeadGenSubLeadJets = new THnSparseD("hGenLeadGenSubLeadJets", "Gen Lead vs Gen SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hGenLeadGenSubLeadJets->Sumw2();
        hGenLeadGenSubLeadJets_W =
            new THnSparseD("hGenLeadGenSubLeadJets_W", "Gen Lead vs Gen SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hGenLeadGenSubLeadJets_W->Sumw2();
        hGenLeadGenSubLeadJets_MidRapidity_W = new THnSparseD("hGenLeadGenSubLeadJets_MidRapidity_W", "Gen Lead vs Gen SubLead Pt MidRapidity Weighted", 7,
                                                              LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_MidRapidity_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hGenLeadGenSubLeadJets_MidRapidity_W->Sumw2();
        hGenLeadGenSubLeadJets_WithDijet_W =
            new THnSparseD("hGenLeadGenSubLeadJets_WithDijet_W", "Gen Lead vs Gen SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_WithDijet_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hGenLeadGenSubLeadJets_WithDijet_W->Sumw2();
        hGenLeadGenSubLeadJets_WithDijet_DiJetW = new THnSparseD("hGenLeadGenSubLeadJets_WithDijet_DiJetW", "Gen Lead vs Gen SubLead Pt With Dijet With DiJetWeighted", 7,
                                                                 LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hGenLeadGenSubLeadJets_WithDijet_DiJetW->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hGenLeadGenSubLeadJets_WithDijet_DiJetW->Sumw2();
        hRefLeadRefSubLeadJets = new THnSparseD("hRefLeadRefSubLeadJets", "Ref Lead vs Ref SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hRefLeadRefSubLeadJets->Sumw2();
        hRefLeadRefSubLeadJets_W =
            new THnSparseD("hRefLeadRefSubLeadJets_W", "Ref Lead vs Ref SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hRefLeadRefSubLeadJets_W->Sumw2();
        hRefLeadRefSubLeadJets_MidRapidity_W = new THnSparseD("hRefLeadRefSubLeadJets_MidRapidity_W", "Ref Lead vs Ref SubLead Pt MidRapidity Weighted", 7,
                                                              LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_MidRapidity_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hRefLeadRefSubLeadJets_MidRapidity_W->Sumw2();
        hRefLeadRefSubLeadJets_WithDijet_W =
            new THnSparseD("hRefLeadRefSubLeadJets_WithDijet_W", "Ref Lead vs Ref SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_WithDijet_W->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hRefLeadRefSubLeadJets_WithDijet_W->Sumw2();
        hRefLeadRefSubLeadJets_WithDijet_DiJetW = new THnSparseD("hRefLeadRefSubLeadJets_WithDijet_DiJetW", "Ref Lead vs Ref SubLead Pt With Dijet With DiJetWeighted", 7,
                                                                 LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
        hRefLeadRefSubLeadJets_WithDijet_DiJetW->GetAxis(6)->Set(LeadSLeadJetBins[6], multBinArray);
        hRefLeadRefSubLeadJets_WithDijet_DiJetW->Sumw2();
        hAverageGenPt_W = new TH1D("hAverageGenPt_W", "Average Gen Jet Pt", 200, 0.0, 1000.);
        hAverageGenPt_W->Sumw2();
    }

    const int nDphiBins = 30;  // number of bins
    double DphiBins[nDphiBins + 1] = {0.0,
                                      TMath::Pi() / 5.,
                                      TMath::Pi() / 3.,
                                      (3. / 7.) * TMath::Pi(),
                                      TMath::Pi() / 2.,
                                      (4. / 7.) * TMath::Pi(),
                                      (3. / 5.) * TMath::Pi(),
                                      1.93731547,
                                      1.98967535,
                                      2.04203522,
                                      2.0943951,
                                      2.14675498,
                                      2.19911486,
                                      2.25147474,
                                      2.30383461,
                                      2.35619449,
                                      2.40855437,
                                      2.46091425,
                                      2.51327412,
                                      2.565634,
                                      2.61799388,
                                      2.67035376,
                                      2.72271363,
                                      2.77507351,
                                      2.82743339,
                                      2.87979327,
                                      2.93215314,
                                      2.98451302,
                                      3.0368729,
                                      3.08923278,
                                      TMath::Pi()};

    // const int nXjAjBins = 40;  // number of bins
    // double XjBins[nXjAjBins + 1] = {0.0,  0.025, 0.05, 0.075, 0.1,  0.125, 0.15, 0.175, 0.2,  0.225, 0.25, 0.275, 0.3,  0.325,
    //                                 0.35, 0.375, 0.4,  0.425, 0.45, 0.475, 0.5,  0.525, 0.55, 0.575, 0.6,  0.625, 0.65, 0.675,
    //                                 0.7,  0.725, 0.75, 0.775, 0.8,  0.825, 0.85, 0.875, 0.9,  0.925, 0.95, 0.975, 1.0};

    const int nXjAjBins_ER = 15;  // number of bins
    double XjBins_ER[nXjAjBins_ER + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};

    // const int nLeadPtBins = 8;
    // double leadPtBins[nLeadPtBins + 1] = {25.0, 50., 55., 60., 65., 70., 80., 90., 200.};

    int QuenchBins[5] = {nXjAjBins, nDphiBins, 200, 200, nMultiplicityBins};
    Double_t QuenchMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMax[5] = {1.0, TMath::Pi(), 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};

    int QuenchBinsWithDijet[4] = {nXjAjBins, 500, 500, nMultiplicityBins};
    Double_t QuenchMinWithDijet[4] = {0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMaxWithDijet[4] = {1.0, 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};

    int UnfoldingBins[4] = {nXjAjBins, nXjAjBins, nMultiplicityBins, nLeadPtBins};
    double UnfoldingMin[4] = {0., 0., fMultiplicityBins[0], 0.};
    double UnfoldingMax[4] = {1.0, 1.0, fMultiplicityBins[fMultiplicityBins.size() - 1] + 1, 1.};

    hRecoQuenching_W = new THnSparseD("hRecoQuenching_W", "Reco Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    hRecoQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hRecoQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hRecoQuenching_W->GetAxis(4)->Set(QuenchBins[4], multBinArray);
    hRecoQuenching_W->Sumw2();
    hRecoQuenching_WithDijet_W =
        new THnSparseD("hRecoQuenching_WithDijet_W", "Reco Quenching With Dijet Present", 4, QuenchBinsWithDijet, QuenchMinWithDijet, QuenchMaxWithDijet);
    hRecoQuenching_WithDijet_W->GetAxis(0)->Set(QuenchBinsWithDijet[0], XjBins);
    hRecoQuenching_WithDijet_W->GetAxis(3)->Set(QuenchBinsWithDijet[3], multBinArray);
    hRecoQuenching_WithDijet_W->Sumw2();
    hDeltaPhi_W = new TH1D("hDeltaPhi_W", "Delta Phi Distribution Weighted", nDphiBins, DphiBins);
    hDeltaPhi_W->Sumw2();
    hDeltaPhi_WithDiJet_W = new TH1D("hDeltaPhi_WithDiJet_W", "Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
    hDeltaPhi_WithDiJet_W->Sumw2();
    hMultVsXj_W = new TH3D("hMultVsXj_W", "Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
    hMultVsXj_W->Sumw2();
    hMultVsXj_DiJetW = new TH3D("hMultVsXj_DiJetW", "Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
    hMultVsXj_DiJetW->Sumw2();
    hMultVsXj_HiHFW = new TH2D("hMultVsXj_HiHFW", "Xj Distribution HiHFWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hMultVsXj_HiHFW->Sumw2();
    hHiHFVsXj_W = new TH2D("hHiHFVsXj_W", "Xj Distribution vs HiHF Energy Weighted", nXjAjBins, XjBins, nHiHFEnergyBins, hiHFEnergyBinArray);
    hHiHFVsXj_W->Sumw2();
    hHiHFVsXj_HiHFW = new TH2D("hHiHFVsXj_HiHFW", "Xj Distribution vs HiHF Energy HiHFWeighted", nXjAjBins, XjBins, nHiHFEnergyBins, hiHFEnergyBinArray);
    hHiHFVsXj_HiHFW->Sumw2();

    if (fIsMC)
    {
        hGenQuenching_W = new THnSparseD("hGenQuenching_W", "Gen Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
        hGenQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
        hGenQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
        hGenQuenching_W->GetAxis(4)->Set(QuenchBins[4], multBinArray);
        hGenQuenching_W->Sumw2();
        hGenQuenching_WithDijet_W =
            new THnSparseD("hGenQuenching_WithDijet_W", "Gen Quenching With Dijet Present", 4, QuenchBinsWithDijet, QuenchMinWithDijet, QuenchMaxWithDijet);
        hGenQuenching_WithDijet_W->GetAxis(0)->Set(QuenchBinsWithDijet[0], XjBins);
        hGenQuenching_WithDijet_W->GetAxis(3)->Set(QuenchBinsWithDijet[3], multBinArray);
        hGenQuenching_WithDijet_W->Sumw2();
        hGenDeltaPhi_W = new TH1D("hGenDeltaPhi_W", "Gen Delta Phi Distribution Weighted", nDphiBins, DphiBins);
        hGenDeltaPhi_W->Sumw2();
        hGenDeltaPhi_WithDiJet_W = new TH1D("hGenDeltaPhi_WithDiJet_W", "Gen Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
        hGenDeltaPhi_WithDiJet_W->Sumw2();
        hRefDeltaPhi_W = new TH1D("hRefDeltaPhi_W", "Ref Delta Phi Distribution Weighted", nDphiBins, DphiBins);
        hRefDeltaPhi_W->Sumw2();
        hRefDeltaPhi_WithDiJet_W = new TH1D("hRefDeltaPhi_WithDiJet_W", "Ref Delta Phi Distribution With Diejt Present Weighted", nDphiBins, DphiBins);
        hRefDeltaPhi_WithDiJet_W->Sumw2();
        hMultVsRefXj_W = new TH3D("hMultVsRefXj_W", "RefXj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsRefXj_W->Sumw2();
        hMultVsRefXj_DiJetW =
            new TH3D("hMultVsRefXj_DiJetW", "RefXj Distribution XjWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsRefXj_DiJetW->Sumw2();
        hMultVsMatchedRefXj_W =
            new TH3D("hMultVsMatchedRefXj_W", "Matched RefXj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsMatchedRefXj_W->Sumw2();
        hMultVsMatchedRefXj_DiJetW = new TH3D("hMultVsMatchedRefXj_DiJetW", "Matched RefXj Distribution DiJet Weighted", nXjAjBins, XjBins, nMultiplicityBins,
                                              multBinArray, nLeadPtBins, leadPtBins);
        hMultVsMatchedRefXj_DiJetW->Sumw2();
        hMultVsGenXj_W = new TH3D("hMultVsGenXj_W", "Gen Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsGenXj_W->Sumw2();
        hMultVsGenXj_DiJetW =
            new TH3D("hMultVsGenXj_DiJetW", "Gen Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsGenXj_DiJetW->Sumw2();
        hMultVsMatchedRecoXj_W =
            new TH3D("hMultVsMatchedRecoXj_W", "Matched RecoXj Distribution", nXjAjBins, XjBins, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsMatchedRecoXj_W->Sumw2();
        hMultVsUnflippedMatchedRecoXj_W = new TH3D("hMultVsUnflippedMatchedRecoXj_W", "Matched Unflipped RecoXj Distribution", nXjAjBins_ER, XjBins_ER, nMultiplicityBins,
                                                   multBinArray, nLeadPtBins, leadPtBins);
        hMultVsUnflippedMatchedRecoXj_W->Sumw2();
        hMultVsUnflippedMatchedRefXj_W = new TH3D("hMultVsUnflippedMatchedRefXj_W", "Matched Unflipped RefXj Distribution", nXjAjBins_ER, XjBins_ER, nMultiplicityBins,
                                                  multBinArray, nLeadPtBins, leadPtBins);
        hMultVsUnflippedMatchedRefXj_W->Sumw2();
        hMultVsUnflippedMatchedRefXj_DiJetW = new TH3D("hMultVsUnflippedMatchedRefXj_DiJetW", "Matched Unflipped RefXj Distribution DiJet Weighted", nXjAjBins_ER,
                                                       XjBins_ER, nMultiplicityBins, multBinArray, nLeadPtBins, leadPtBins);
        hMultVsUnflippedMatchedRefXj_DiJetW->Sumw2();

        hLeadPtVsRecoXj_W = new TH2D("hLeadPtVsRecoXj_W", "Lead Pt vs Reco Xj Weighted", nXjAjBins, XjBins, nLeadPtBins, leadPtBins);
        hLeadPtVsRecoXj_W->Sumw2();
        hLeadPtVsRefXj_W = new TH2D("hLeadPtVsRefXj_W", "Lead Pt vs Ref Xj Weighted", nXjAjBins, XjBins, nLeadPtBins, leadPtBins);
        hLeadPtVsRefXj_W->Sumw2();
        hLeadPtVsGenXj_W = new TH2D("hLeadPtVsGenXj_W", "Lead Pt vs Gen Xj Weighted", nXjAjBins, XjBins, nLeadPtBins, leadPtBins);
        hLeadPtVsGenXj_W->Sumw2();
    }
    int nFlatBins = nLeadPtBins * nXjAjBins;
    std::vector<double> flatEdges(nFlatBins + 1);
    for (int i = 0; i <= nFlatBins; ++i)
    {
        flatEdges[i] = i + 0.5;
    }

    if (fIsMC)
    {
        hResponseMatrix_W = new TH3D("hResponseMatrix_W", "Response Matrix", nFlatBins, flatEdges.data(), nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hResponseMatrix_W->Sumw2();
        hResponseMatrixA_W =
            new TH3D("hResponseMatrixA_W", "Response Matrix for Sample A", nFlatBins, flatEdges.data(), nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hResponseMatrixA_W->Sumw2();
        hResponseMatrixB_W =
            new TH3D("hResponseMatrixB_W", "Response Matrix for Sample B", nFlatBins, flatEdges.data(), nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hResponseMatrixB_W->Sumw2();

        hTotalReco_W = new TH2D("hTotalReco_W", "Total Reco Xj Flattened Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalReco_W->Sumw2();
        hTotalRecoA_W = new TH2D("hTotalRecoA_W", "Reco Xj Flattened for Sample A Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalRecoA_W->Sumw2();
        hTotalRecoB_W = new TH2D("hTotalRecoB_W", "Reco Xj Flattened for Sample B Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalRecoB_W->Sumw2();

        hTotalTruth_W = new TH2D("hTotalTruth_W", "Total Truth Xj Flattened Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalTruth_W->Sumw2();
        hTotalTruthA_W = new TH2D("hTotalTruthA_W", "Truth Xj Flattened for Sample A Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalTruthA_W->Sumw2();
        hTotalTruthB_W = new TH2D("hTotalTruthB_W", "Truth Xj Flattened for Sample B Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hTotalTruthB_W->Sumw2();

        hMatchedGen_W = new TH2D("hMatchedGen_W", "Total Matched Gen Xj Flattened Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedGen_W->Sumw2();
        hMatchedGenA_W = new TH2D("hMatchedGenA_W", "Matched Gen Xj Flattened for Sample A Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedGenA_W->Sumw2();
        hMatchedGenB_W = new TH2D("hMatchedGenB_W", "Matched Gen Xj Flattened for Sample B Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedGenB_W->Sumw2();

        hMatchedReco_W = new TH2D("hMatchedReco_W", "Total Matched Reco Xj Flattened Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedReco_W->Sumw2();
        hMatchedRecoA_W = new TH2D("hMatchedRecoA_W", "Matched Reco Xj Flattened for Sample A Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedRecoA_W->Sumw2();
        hMatchedRecoB_W = new TH2D("hMatchedRecoB_W", "Matched Reco Xj Flattened for Sample B Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hMatchedRecoB_W->Sumw2();

        hValidationTruth_W = new TH2D("hValidationTruth_W", "Modified Truth for Validation", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
        hValidationTruth_W->Sumw2();
    }

    hTotalRecoFlat_W = new TH2D("hTotalRecoFlat_W", "Total Reco Xj Flattened Weighted", nFlatBins, flatEdges.data(), nMultiplicityBins, multBinArray);
    hTotalRecoFlat_W->Sumw2();

    // Float_t LeadSubLeadPtBins[] = {0.0, 50., 60., 70., 80., 90., 100., 110., 120., 130., 140., 150., 160., 170., 180., 190., 200., 220., 240., 260., 280., 300.,
    // 350., 400., 450., 500., 600., 700., 1200.};
    Float_t LeadSubLeadPtBins[] = {0.0,  10.,  20.,  30.,  40.,  50.,  60.,  70.,  80.,  90.,  100., 110., 120.,
                                   130., 140., 150., 160., 170., 180., 190., 200., 220., 250., 300., 350., 400.};
    Int_t nLeadSubLeadPtBins = sizeof(LeadSubLeadPtBins) / sizeof(Float_t) - 1;

    Float_t GenLeadGenSubLeadPtBins[] = {0.0, 5.0, 10.,  15.,  20.,  25.,  30.,  35.,  40.,  45.,  50.,  55.,  60.,  65.,  70.,  75.,  80.,  85.,
                                         90., 95., 100., 110., 120., 130., 140., 150., 160., 170., 180., 190., 200., 220., 250., 300., 350., 400.};
    Int_t nGenLeadGenSubLeadPtBins = sizeof(GenLeadGenSubLeadPtBins) / sizeof(Float_t) - 1;
    hLeadPtvsSubLeadPt_PtHatW = new TH2D("hLeadPtvsSubLeadPt_PtHatW", "Lead Pt vs SubLead Pt", nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins,
                                         nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
    hLeadPtvsSubLeadPt_PtHatW->Sumw2();
    hLeadPtvsSubLeadPt_DiJetW = new TH2D("hLeadPtvsSubLeadPt_DiJetW", "Lead Pt vs SubLead Pt Weighted", nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins,
                                         nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
    hLeadPtvsSubLeadPt_DiJetW->Sumw2();

    if (fIsMC)
    {
        hGenLeadPtvsGenSubLeadPt_PtHatW = new TH2D("hGenLeadPtvsGenSubLeadPt_PtHatW", "Gen Lead Pt vs Gen SubLead Pt", nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins,
                                                   nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hGenLeadPtvsGenSubLeadPt_PtHatW->Sumw2();
        hGenLeadPtvsGenSubLeadPt_DiJetW = new TH2D("hGenLeadPtvsGenSubLeadPt_DiJetW", "Gen Lead Pt vs Gen SubLead Pt Weighted", nGenLeadGenSubLeadPtBins,
                                                   GenLeadGenSubLeadPtBins, nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hGenLeadPtvsGenSubLeadPt_DiJetW->Sumw2();

        hRefLeadPtvsRefSubLeadPt_PtHatW = new TH2D("hRefLeadPtvsRefSubLeadPt_PtHatW", "Ref Lead Pt vs Ref SubLead Pt", nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins,
                                                   nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hRefLeadPtvsRefSubLeadPt_PtHatW->Sumw2();
        hRefLeadPtvsRefSubLeadPt_DiJetW = new TH2D("hRefLeadPtvsRefSubLeadPt_DiJetW", "Ref Lead Pt vs Ref SubLead Pt Weighted", nGenLeadGenSubLeadPtBins,
                                                   GenLeadGenSubLeadPtBins, nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hRefLeadPtvsRefSubLeadPt_DiJetW->Sumw2();

        hRefLeadPtVsRefSubLeadPtMatched_DiJetW = new TH2D("hRefLeadPtvsRefSubLeadPtMatched_DiJetW", "Ref Lead Pt vs Ref SubLead Pt Matched", nGenLeadGenSubLeadPtBins,
                                                          GenLeadGenSubLeadPtBins, nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hRefLeadPtVsRefSubLeadPtMatched_DiJetW->Sumw2();
        hRefLeadPtVsRefSubLeadPtMatched_PtHatW = new TH2D("hRefLeadPtvsRefSubLeadPtMatched_PtHatW", "Ref Lead Pt vs Ref SubLead Pt Matched Pt Weighted",
                                                          nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins, nGenLeadGenSubLeadPtBins, GenLeadGenSubLeadPtBins);
        hRefLeadPtVsRefSubLeadPtMatched_PtHatW->Sumw2();

        int nJetPtBins = 500;
        int nRatioBins = 200;
        int nJetEtaBins = 200;
        double ratioMin = 0.0, ratioMax = 2.0;
        double jetPtMin = 0.0, jetPtMax = 1000.;
        double etaMin = -5.0, etaMax = 5.0;

        std::vector<double> jetPtBins(nJetPtBins + 1);
        for (int i = 0; i <= nJetPtBins; ++i)
        {
            jetPtBins[i] = jetPtMin + i * (jetPtMax - jetPtMin) / nJetPtBins;
        }
        std::vector<double> jetEtaBins(nJetEtaBins + 1);
        for (int i = 0; i <= nJetEtaBins; ++i)
        {
            jetEtaBins[i] = etaMin + i * (etaMax - etaMin) / nJetEtaBins;
        }
        std::vector<double> ratioBins(nRatioBins + 1);
        for (int i = 0; i <= nRatioBins; ++i)
        {
            ratioBins[i] = ratioMin + i * (ratioMax - ratioMin) / nRatioBins;
        }
        hRecoJES_W = new TH3D("hRecoJES_W", "Reco JES Weighted", nRatioBins, ratioBins.data(), nJetPtBins, jetPtBins.data(), nMultiplicityBins, multBinArray);
        hRecoJES_W->Sumw2();
        hRefJES_W = new TH3D("hRefJES_W", "Ref JES Weighted", nRatioBins, ratioBins.data(), nJetPtBins, jetPtBins.data(), nMultiplicityBins, multBinArray);
        hRefJES_W->Sumw2();
        hRecoJES_Eta_W = new TH3D("hRecoJES_Eta_W", "Reco JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRecoJES_Eta_W->Sumw2();
        hRefJES_Eta_W = new TH3D("hRefJES_Eta_W", "Ref JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRefJES_Eta_W->Sumw2();
        hRecoJES_Eta_Pt100_W =
            new TH3D("hRecoJES_Eta_Pt100_W", "Reco JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRecoJES_Eta_Pt100_W->Sumw2();
        hRecoJES_Eta_Pt120_W =
            new TH3D("hRecoJES_Eta_Pt120_W", "Reco JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRecoJES_Eta_Pt120_W->Sumw2();
        hRefJES_Eta_Pt100_W =
            new TH3D("hRefJES_Eta_Pt100_W", "Ref JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRefJES_Eta_Pt100_W->Sumw2();
        hRefJES_Eta_Pt120_W =
            new TH3D("hRefJES_Eta_Pt120_W", "Ref JES Weighted", nRatioBins, ratioBins.data(), nJetEtaBins, jetEtaBins.data(), nMultiplicityBins, multBinArray);
        hRefJES_Eta_Pt120_W->Sumw2();
    }

    Double_t trkEtaBins[] = {-2.4, -2.1, -1.8, -1.5, -1.3, -1.1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0,
                             0.1,  0.2,  0.3,  0.4,  0.5,  0.6,  0.7,  0.8,  0.9,  1.1,  1.3,  1.5,  1.8,  2.1,  2.4};
    Int_t nEtaBins = sizeof(trkEtaBins) / sizeof(Double_t) - 1;
    Double_t trkPtBins[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0, 1.2, 1.4, 1.6, 2.0, 2.5, 3.0, 4.0, 5.0, 8.0, 12.0, 30.0, 300.0, 1000.0};
    Int_t nPtBins = sizeof(trkPtBins) / sizeof(Double_t) - 1;
    hGenTrackPtVsEta = new TH3D("hGenTrackPtVsEta", "Gen Track Pt vs Eta", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hGenTrackPtVsEta->Sumw2();
    hGenTrackPtVsEta_W = new TH3D("hGenTrackPtVsEta_W", "Gen Track Pt vs Eta Weighted", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hGenTrackPtVsEta_W->Sumw2();
    hTrackPtVsEta = new TH3D("hRecoTrackPtVsEta", "Reco Track Pt vs Eta", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hTrackPtVsEta->Sumw2();
    hTrackPtVsEta_W = new TH3D("hRecoTrackPtVsEta_W", "Reco Track Pt vs Eta Weighted", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hTrackPtVsEta_W->Sumw2();
    hTrackPtVsEtaCorrected =
        new TH3D("hRecoTrackPtVsEtaCorrected", "Reco Track Pt vs Eta Corrected", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hTrackPtVsEtaCorrected->Sumw2();
    hTrackPtVsEtaCorrected_W =
        new TH3D("hRecoTrackPtVsEtaCorrected_W", "Reco Track Pt vs Eta Corrected Weighted", nEtaBins, trkEtaBins, nPtBins, trkPtBins, nMultiplicityBins, multBinArray);
    hTrackPtVsEtaCorrected_W->Sumw2();

    hHiHFPlusVsHiHFMinus =
        new TH2D("hHiHFPlusVsHiHFMinus", "Forward Calorimeter in Positive Eta (p-going)  vs Forward Calorimeter in Minus Eta (Pb-going)", 1000, 0., 500., 1000, 0., 500.);
    hHiHFPlusVsHiHFMinus->Sumw2();
    hHiHFPlusVsHiHFMinus_W = new TH2D("hHiHFPlusVsHiHFMinus_W", "Forward Calorimeter in Positive Eta (p-going)  vs Forward Calorimeter in Minus Eta (Pb-going) Weighted",
                                      1000, 0., 500., 1000, 0., 500.);
    hHiHFPlusVsHiHFMinus_W->Sumw2();
    hHiHFPlusVsHiHFMinus_WithDijet_W = new TH2D(
        "hHiHFPlusVsHiHFMinus_WithDijet_W", "Forward Calorimeter in Positive Eta (p-going)  vs Forward Calorimeter in Minus Eta (Pb-going) With Dijet Present Weighted",
        1000, 0., 500., 1000, 0., 500.);
    hHiHFPlusVsHiHFMinus_WithDijet_W->Sumw2();
    hHiHFPlusVsMultiplicity_W =
        new TH2D("hHiHFPlusVsMultiplicity_W", "Forward Calorimeter in Positive Eta (p-going)  vs Multiplicity Weighted", 500, 0.0, 500., 1000, 0.0, 500.);
    hHiHFPlusVsMultiplicity_W->Sumw2();
    hHiHFMinusVsMultiplicity_W =
        new TH2D("hHiHFMinusVsMultiplicity_W", "Forward Calorimeter in Minus Eta (Pb-going)  vs Multiplicity Weighted", 500, 0.0, 500., 1000, 0.0, 500.);
    hHiHFMinusVsMultiplicity_W->Sumw2();
    hHiHFPlusVsMultiplicity_WithDijet_W =
        new TH2D("hHiHFPlusVsMultiplicity_WithDijet_W", "Forward Calorimeter in Positive Eta (p-going)  vs Multiplicity With Dijet Present Weighted", 500, 0.0, 500.,
                 1000, 0.0, 500.);
    hHiHFPlusVsMultiplicity_WithDijet_W->Sumw2();
    hHiHFMinusVsMultiplicity_WithDijet_W =
        new TH2D("hHiHFMinusVsMultiplicity_WithDijet_W", "Forward Calorimeter in Minus Eta (Pb-going)  vs Multiplicity With Dijet Present Weighted", 500, 0.0, 500., 1000,
                 0.0, 500.);
    hHiHFMinusVsMultiplicity_WithDijet_W->Sumw2();

    std::cout << "=======================================================================" << std::endl;
    std::cout << "============HistoManagerDiJet::init Initialization Complete============" << std::endl;
    std::cout << "=======================================================================" << std::endl;
}

void HistoManagerDiJet::projectHistograms()
{
    std::cout << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Projecting Histograms" << std::endl;
    std::cout << "====================================" << std::endl;

    TH1D* iProjection;
    std::cout << "====>Reco level histograms being projected" << std::endl;
    iProjection = hInclusiveRecoJetsCMFrame->Projection(0);
    hInclusiveRecoJetPt = (TH1D*)iProjection->Clone("hInclusiveRecoJetPt");
    hInclusiveRecoJetPt->SetTitle("Inclusive Reco Jet Pt");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame_W->Projection(0);
    hInclusiveRecoJetPt_W = (TH1D*)iProjection->Clone("hInclusiveRecoJetPt_W");
    hInclusiveRecoJetPt_W->SetTitle("Inclusive Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hSelectedInclusiveRecoJetsMidRapidity_W->Projection(0);
    hSelectedInclusiveRecoJetPt_MidRapidity_W = (TH1D*)iProjection->Clone("hSelectedInclusiveRecoJetPt_MidRapidity_W");
    hSelectedInclusiveRecoJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Reco Jet Pt MidRapidity Weighted");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame->Projection(1);
    hInclusiveRecoJetEtaCMFrame = (TH1D*)iProjection->Clone("hInclusiveRecoJetEtaCMFrame");
    hInclusiveRecoJetEtaCMFrame->SetTitle("Inclusive Reco Jet Eta CM Frame");
    delete iProjection;

    iProjection = hInclusiveRecoJetsCMFrame_W->Projection(1);
    hInclusiveRecoJetEtaCMFrame_W = (TH1D*)iProjection->Clone("hInclusiveRecoJetEtaCMFrame_W");
    hInclusiveRecoJetEtaCMFrame_W->SetTitle("Inclusive Reco Jet Eta CM Frame Weighted");
    delete iProjection;

    iProjection = hInclusiveRecoJetsLabFrame->Projection(1);
    hInclusiveRecoJetEtaLabFrame = (TH1D*)iProjection->Clone("hInclusiveRecoJetEtaLabFrame");
    hInclusiveRecoJetEtaLabFrame->SetTitle("Inclusive Reco Jet Eta Lab Frame");
    delete iProjection;

    iProjection = hInclusiveRecoJetsLabFrame_W->Projection(1);
    hInclusiveRecoJetEtaLabFrame_W = (TH1D*)iProjection->Clone("hInclusiveRecoJetEtaLabFrame_W");
    hInclusiveRecoJetEtaLabFrame_W->SetTitle("Inclusive Reco Jet Eta Lab Frame Weighted");
    delete iProjection;

    iProjection = hSelectedInclusiveRecoJetsMidRapidity_W->Projection(1);
    hSelectedInclusiveRecoJetEtaMidRapidity_W = (TH1D*)iProjection->Clone("hSelectedInclusiveRecoJetEtaMidRapidity_W");
    hSelectedInclusiveRecoJetEtaMidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Reco Jet Eta MidRapidity Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets->Projection(0);
    hLeadingRecoJetPt = (TH1D*)iProjection->Clone("hLeadingRecoJetPt");
    hLeadingRecoJetPt->SetTitle("Leading Reco Jet Pt");
    delete iProjection;

    iProjection = hLeadSubLeadJets_W->Projection(0);
    hLeadingRecoJetPt_W = (TH1D*)iProjection->Clone("hLeadingRecoJetPt_W");
    hLeadingRecoJetPt_W->SetTitle("Leading Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets->Projection(3);
    hSubLeadingRecoJetPt = (TH1D*)iProjection->Clone("hSubLeadingRecoJetPt");
    hSubLeadingRecoJetPt->SetTitle("SubLeading Reco Jet Pt");
    delete iProjection;

    iProjection = hLeadSubLeadJets_W->Projection(3);
    hSubLeadingRecoJetPt_W = (TH1D*)iProjection->Clone("hSubLeadingRecoJetPt_W");
    hSubLeadingRecoJetPt_W->SetTitle("SubLeading Reco Jet Pt Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_W->Projection(0);
    hLeadingRecoJetPtWithDijet_W = (TH1D*)iProjection->Clone("hLeadingRecoJetPtWithDijet_W");
    hLeadingRecoJetPtWithDijet_W->SetTitle("Leading Reco Jet Pt With Dijet Present Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_W->Projection(3);
    hSubLeadingRecoJetPtWithDijet_W = (TH1D*)iProjection->Clone("hSubLeadingRecoJetPtWithDijet_W");
    hSubLeadingRecoJetPtWithDijet_W->SetTitle("SubLeading Reco Jet Pt With Dijet Present Weighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_DiJetW->Projection(0);
    hLeadingRecoJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hLeadingRecoJetPtWithDijet_DiJetW");
    hLeadingRecoJetPtWithDijet_DiJetW->SetTitle("Leading Reco Jet Pt With Dijet Present With DiJetWeighted");
    delete iProjection;

    iProjection = hLeadSubLeadJets_WithDijet_DiJetW->Projection(3);
    hSubLeadingRecoJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hSubLeadingRecoJetPtWithDijet_DiJetW");
    hSubLeadingRecoJetPtWithDijet_DiJetW->SetTitle("SubLeading Reco Jet Pt With Dijet Present With DiJetWeighted");
    delete iProjection;

    iProjection = hMultVsXj_W->ProjectionX();
    hXj_C0_W = (TH1D*)iProjection->Clone("hXj_W");
    hXj_C0_W->SetTitle("Xj Projection C0 Weighted");
    delete iProjection;

    iProjection = hMultVsXj_DiJetW->ProjectionX();
    hXj_C0_DiJetW = (TH1D*)iProjection->Clone("hXj_DiJetW");
    hXj_C0_DiJetW->SetTitle("Xj Projection C0 Dijet Weighted");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus->ProjectionX();
    hHiHFMinus = (TH1D*)iProjection->Clone("hHiHFMinus");
    hHiHFMinus->SetTitle("Forward Calorimeter in Minus Eta (Pb-going)");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus->ProjectionY();
    hHiHFPlus = (TH1D*)iProjection->Clone("hHiHFPlus");
    hHiHFPlus->SetTitle("Forward Calorimeter in Positive Eta (p-going)");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus_W->ProjectionX();
    hHiHFMinus_W = (TH1D*)iProjection->Clone("hHiHFMinus_W");
    hHiHFMinus_W->SetTitle("Forward Calorimeter in Minus Eta (Pb-going) Weighted");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus_W->ProjectionY();
    hHiHFPlus_W = (TH1D*)iProjection->Clone("hHiHFPlus_W");
    hHiHFPlus_W->SetTitle("Forward Calorimeter in Positive Eta (p-going) Weighted");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus_WithDijet_W->ProjectionX();
    hHiHFMinus_WithDijet_W = (TH1D*)iProjection->Clone("hHiHFMinus_WithDijet_W");
    hHiHFMinus_WithDijet_W->SetTitle("Forward Calorimeter in Minus Eta (Pb-going) With Dijet Present Weighted");
    delete iProjection;

    iProjection = hHiHFPlusVsHiHFMinus_WithDijet_W->ProjectionY();
    hHiHFPlus_WithDijet_W = (TH1D*)iProjection->Clone("hHiHFPlus_WithDijet_W");
    hHiHFPlus_WithDijet_W->SetTitle("Forward Calorimeter in Positive Eta (p-going) With Dijet Present Weighted");
    delete iProjection;

    if (fIsMC)
    {
        std::cout << "====>Gen level histograms being projected" << std::endl;

        iProjection = hInclusiveGenJetsCMFrame->Projection(0);
        hInclusiveGenJetPt = (TH1D*)iProjection->Clone("hInclusiveGenJetPt");
        hInclusiveGenJetPt->SetTitle("Inclusive Gen Jet Pt");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame_W->Projection(0);
        hInclusiveGenJetPt_W = (TH1D*)iProjection->Clone("hInclusiveGenJetPt_W");
        hInclusiveGenJetPt_W->SetTitle("Inclusive Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveGenJetsMidRapidity_W->Projection(0);
        hSelectedInclusiveGenJetPt_MidRapidity_W = (TH1D*)iProjection->Clone("hSelectedInclusiveGenJetPt_MidRapidity_W");
        hSelectedInclusiveGenJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Gen Jet Pt MidRapidity Weighted");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame->Projection(1);
        hInclusiveGenJetEtaCMFrame = (TH1D*)iProjection->Clone("hInclusiveGenJetEtaCMFrame");
        hInclusiveGenJetEtaCMFrame->SetTitle("Inclusive Gen Jet Eta CM Frame");
        delete iProjection;

        iProjection = hInclusiveGenJetsCMFrame_W->Projection(1);
        hInclusiveGenJetEtaCMFrame_W = (TH1D*)iProjection->Clone("hInclusiveGenJetEtaCMFrame_W");
        hInclusiveGenJetEtaCMFrame_W->SetTitle("Inclusive Gen Jet Eta CM Frame Weighted");
        delete iProjection;

        iProjection = hInclusiveGenJetsLabFrame->Projection(1);
        hInclusiveGenJetEtaLabFrame = (TH1D*)iProjection->Clone("hInclusiveGenJetEtaLabFrame");
        hInclusiveGenJetEtaLabFrame->SetTitle("Inclusive Gen Jet Eta Lab Frame");
        delete iProjection;

        iProjection = hInclusiveGenJetsLabFrame_W->Projection(1);
        hInclusiveGenJetEtaLabFrame_W = (TH1D*)iProjection->Clone("hInclusiveGenJetEtaLabFrame_W");
        hInclusiveGenJetEtaLabFrame_W->SetTitle("Inclusive Gen Jet Eta Lab Frame Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveGenJetsMidRapidity_W->Projection(1);
        hSelectedInclusiveGenJetEtaMidRapidity_W = (TH1D*)iProjection->Clone("hSelectedInclusiveGenJetEtaMidRapidity_W");
        hSelectedInclusiveGenJetEtaMidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Gen Jet Eta MidRapidity Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets->Projection(0);
        hLeadingGenJetPt = (TH1D*)iProjection->Clone("hLeadingGenJetPt");
        hLeadingGenJetPt->SetTitle("Leading Gen Jet Pt");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_W->Projection(0);
        hLeadingGenJetPt_W = (TH1D*)iProjection->Clone("hLeadingGenJetPt_W");
        hLeadingGenJetPt_W->SetTitle("Leading Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets->Projection(3);
        hSubLeadingGenJetPt = (TH1D*)iProjection->Clone("hSubLeadingGenJetPt");
        hSubLeadingGenJetPt->SetTitle("SubLeading Gen Jet Pt");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_W->Projection(3);
        hSubLeadingGenJetPt_W = (TH1D*)iProjection->Clone("hSubLeadingGenJetPt_W");
        hSubLeadingGenJetPt_W->SetTitle("SubLeading Gen Jet Pt Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_W->Projection(0);
        hLeadingGenJetPtWithDijet_W = (TH1D*)iProjection->Clone("hLeadingGenJetPtWithDijet_W");
        hLeadingGenJetPtWithDijet_W->SetTitle("Leading Gen Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_W->Projection(3);
        hSubLeadingGenJetPtWithDijet_W = (TH1D*)iProjection->Clone("hSubLeadingGenJetPtWithDijet_W");
        hSubLeadingGenJetPtWithDijet_W->SetTitle("SubLeading Gen Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_DiJetW->Projection(0);
        hLeadingGenJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hLeadingGenJetPtWithDijet_DiJetW");
        hLeadingGenJetPtWithDijet_DiJetW->SetTitle("Leading Gen Jet Pt With Dijet Present With DiJetWeighted");
        delete iProjection;

        iProjection = hGenLeadGenSubLeadJets_WithDijet_DiJetW->Projection(3);
        hSubLeadingGenJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hSubLeadingGenJetPtWithDijet_DiJetW");
        hSubLeadingGenJetPtWithDijet_DiJetW->SetTitle("SubLeading Gen Jet Pt With Dijet Present With DiJetWeighted");
        delete iProjection;

        iProjection = hInclusiveRefJetsCMFrame->Projection(0);
        hInclusiveRefJetPt = (TH1D*)iProjection->Clone("hInclusiveRefJetPt");
        hInclusiveRefJetPt->SetTitle("Inclusive Ref Jet Pt");
        delete iProjection;

        iProjection = hInclusiveRefJetsCMFrame_W->Projection(0);
        hInclusiveRefJetPt_W = (TH1D*)iProjection->Clone("hInclusiveRefJetPt_W");
        hInclusiveRefJetPt_W->SetTitle("Inclusive Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hSelectedInclusiveRefJetsMidRapidity_W->Projection(0);
        hSelectedInclusiveRefJetPt_MidRapidity_W = (TH1D*)iProjection->Clone("hSelectedInclusiveRefJetPt_MidRapidity_W");
        hSelectedInclusiveRefJetPt_MidRapidity_W->SetTitle("Selected (Jet Pt > 50) Inclusive Ref Jet Pt MidRapidity Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets->Projection(0);
        hLeadingRefJetPt = (TH1D*)iProjection->Clone("hLeadingRefJetPt");
        hLeadingRefJetPt->SetTitle("Leading Ref Jet Pt");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_W->Projection(0);
        hLeadingRefJetPt_W = (TH1D*)iProjection->Clone("hLeadingRefJetPt_W");
        hLeadingRefJetPt_W->SetTitle("Leading Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets->Projection(3);
        hSubLeadingRefJetPt = (TH1D*)iProjection->Clone("hSubLeadingRefJetPt");
        hSubLeadingRefJetPt->SetTitle("SubLeading Ref Jet Pt");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_W->Projection(3);
        hSubLeadingRefJetPt_W = (TH1D*)iProjection->Clone("hSubLeadingRefJetPt_W");
        hSubLeadingRefJetPt_W->SetTitle("SubLeading Ref Jet Pt Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_W->Projection(0);
        hLeadingRefJetPtWithDijet_W = (TH1D*)iProjection->Clone("hLeadingRefJetPtWithDijet_W");
        hLeadingRefJetPtWithDijet_W->SetTitle("Leading Ref Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_W->Projection(3);
        hSubLeadingRefJetPtWithDijet_W = (TH1D*)iProjection->Clone("hSubLeadingRefJetPtWithDijet_W");
        hSubLeadingRefJetPtWithDijet_W->SetTitle("SubLeading Ref Jet Pt With Dijet Present Weighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_DiJetW->Projection(0);
        hLeadingRefJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hLeadingRefJetPtWithDijet_DiJetW");
        hLeadingRefJetPtWithDijet_DiJetW->SetTitle("Leading Ref Jet Pt With Dijet Present With DiJetWeighted");
        delete iProjection;

        iProjection = hRefLeadRefSubLeadJets_WithDijet_DiJetW->Projection(3);
        hSubLeadingRefJetPtWithDijet_DiJetW = (TH1D*)iProjection->Clone("hSubLeadingRefJetPtWithDijet_DiJetW");
        hSubLeadingRefJetPtWithDijet_DiJetW->SetTitle("SubLeading Ref Jet Pt With Dijet Present With DiJetWeighted");
        delete iProjection;

        iProjection = hMultVsGenXj_W->ProjectionX();
        hGenXj_C0_W = (TH1D*)iProjection->Clone("hGenXj_W");
        hGenXj_C0_W->SetTitle("Gen Xj Projection C0 Weighted");
        delete iProjection;

        iProjection = hMultVsGenXj_DiJetW->ProjectionX();
        hGenXj_C0_DiJetW = (TH1D*)iProjection->Clone("hGenXj_DiJetW");
        hGenXj_C0_DiJetW->SetTitle("Gen Xj Projection C0 Dijet Weighted");
        delete iProjection;
    }

    hXj_Projection_W.clear();
    hXj_Projection_DiJetW.clear();
    hXj_Projection_HiHFW.clear();
    hGenXj_Projection_W.clear();
    hGenXj_Projection_DiJetW.clear();
    hRefXj_Projection_W.clear();
    hRefXj_Projection_DiJetW.clear();
    hMatchedRefXj_Projection_W.clear();
    hMatchedRefXj_Projection_DiJetW.clear();
    std::cout << " ====> Projecting Xj Histograms in Multiplicity Bins" << std::endl;
    for (Int_t i = 0; i < fMultiplicityBins.size() - 1; i++)
    {
        hXj_Projection_W.push_back(hMultVsXj_W->ProjectionX(Form("hXj_C%i_W", i), hMultVsXj_W->GetYaxis()->FindBin(i), hMultVsXj_W->GetYaxis()->FindBin(i)));
        hXj_Projection_W.at(i)->SetTitle(
            Form("Xj Projection for %i-%i Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
        hXj_Projection_DiJetW.push_back(
            hMultVsXj_DiJetW->ProjectionX(Form("hXj_C%i_DiJetW", i), hMultVsXj_DiJetW->GetYaxis()->FindBin(i), hMultVsXj_DiJetW->GetYaxis()->FindBin(i)));
        hXj_Projection_DiJetW.at(i)->SetTitle(
            Form("Xj Projection %i-%i Dijet Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
        hXj_Projection_HiHFW.push_back(
            hMultVsXj_HiHFW->ProjectionX(Form("hXj_C%i_HiHFW", i), hMultVsXj_HiHFW->GetYaxis()->FindBin(i), hMultVsXj_HiHFW->GetYaxis()->FindBin(i)));
        hXj_Projection_HiHFW.at(i)->SetTitle(
            Form("Xj Projection %i-%i HiHF Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));

        if (fIsMC)
        {
            hGenXj_Projection_W.push_back(
                hMultVsGenXj_W->ProjectionX(Form("hGenXj_C%i_W", i), hMultVsGenXj_W->GetYaxis()->FindBin(i), hMultVsGenXj_W->GetYaxis()->FindBin(i)));
            hGenXj_Projection_W.at(i)->SetTitle(
                Form("Gen Xj Projection %i-%i Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
            hGenXj_Projection_DiJetW.push_back(
                hMultVsGenXj_DiJetW->ProjectionX(Form("hGenXj_C%i_DiJetW", i), hMultVsGenXj_DiJetW->GetYaxis()->FindBin(i), hMultVsGenXj_DiJetW->GetYaxis()->FindBin(i)));
            hGenXj_Projection_DiJetW.at(i)->SetTitle(
                Form("Gen Xj Projection %i-%i Dijet Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
            hRefXj_Projection_W.push_back(
                hMultVsRefXj_W->ProjectionX(Form("hRefXj_C%i_W", i), hMultVsRefXj_W->GetYaxis()->FindBin(i), hMultVsRefXj_W->GetYaxis()->FindBin(i)));
            hRefXj_Projection_W.at(i)->SetTitle(
                Form("Ref Xj Projection %i-%i Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
            hRefXj_Projection_DiJetW.push_back(
                hMultVsRefXj_DiJetW->ProjectionX(Form("hRefXj_C%i_DiJetW", i), hMultVsRefXj_DiJetW->GetYaxis()->FindBin(i), hMultVsRefXj_DiJetW->GetYaxis()->FindBin(i)));
            hRefXj_Projection_DiJetW.at(i)->SetTitle(
                Form("Ref Xj Projection %i-%i Dijet Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
            hMatchedRefXj_Projection_W.push_back(hMultVsMatchedRefXj_W->ProjectionX(Form("hMatchedRefXj_C%i_W", i), hMultVsMatchedRefXj_W->GetYaxis()->FindBin(i),
                                                                                    hMultVsMatchedRefXj_W->GetYaxis()->FindBin(i)));
            hMatchedRefXj_Projection_W.at(i)->SetTitle(
                Form("Matched Ref Xj Projection %i-%i Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
            hMatchedRefXj_Projection_DiJetW.push_back(hMultVsMatchedRefXj_DiJetW->ProjectionX(
                Form("hMatchedRefXj_C%i_DiJetW", i), hMultVsMatchedRefXj_DiJetW->GetYaxis()->FindBin(i), hMultVsMatchedRefXj_DiJetW->GetYaxis()->FindBin(i)));
            hMatchedRefXj_Projection_DiJetW.at(i)->SetTitle(
                Form("Matched Ref Xj Projection %i-%i Dijet Weighted", static_cast<int>(fMultiplicityBins.at(i)), static_cast<int>(fMultiplicityBins.at(i + 1))));
        }
    }
    std::cout << "=======>Projecting Xj Histograms in HiHFBins" << std::endl;
    hXj_ProjectionHiHF_W.clear();
    hXj_ProjectionHiHF_HiHFW.clear();
    for (int i = 0; i < fHiHFEnergyBins.size() - 1; i++)
    {
        hXj_ProjectionHiHF_W.push_back(hHiHFVsXj_W->ProjectionX(Form("hXj_HiHFC%i_W", i), hHiHFVsXj_W->GetYaxis()->FindBin(i), hHiHFVsXj_W->GetYaxis()->FindBin(i)));
        hXj_ProjectionHiHF_W.at(i)->SetTitle(
            Form("Xj Projection for HiHF %0.1f-%0.1f Weighted", static_cast<float>(fHiHFEnergyBins.at(i)), static_cast<float>(fHiHFEnergyBins.at(i + 1))));
        hXj_ProjectionHiHF_HiHFW.push_back(
            hHiHFVsXj_HiHFW->ProjectionX(Form("hXj_HiHFC%i_HiHFW", i), hHiHFVsXj_HiHFW->GetYaxis()->FindBin(i), hHiHFVsXj_HiHFW->GetYaxis()->FindBin(i)));
        hXj_ProjectionHiHF_HiHFW.at(i)->SetTitle(
            Form("Xj Projection HiHF %0.1f-%0.1f HiHF Weighted", static_cast<float>(fHiHFEnergyBins.at(i)), static_cast<float>(fHiHFEnergyBins.at(i + 1))));
    }
    std::cout << "Projecting Histograms Complete" << std::endl;
    std::cout << "====================================" << std::endl;
}

void HistoManagerDiJet ::writeOutput()
{
    std::cout << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "Writing Histograms to File" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "  ===> Writing Event Histograms" << std::endl;
    gDirectory->mkdir("Events");
    gDirectory->cd("Events");
    if (fConfig.saveQA)
    {
        hVz->Write();
        hRecoMultiplicity_W->Write();
        hCorrectedMultiplicity_W->Write();
        hSelectedMultiplicity_W->Write();
        hInJetMultiplicity_W->Write();
        hMultiplicities->Write();
        hHiBin->Write();

        hHiHF_PF->Write();
        hHiHF_PF_W->Write();
        if (fIsMC)
        {
            hPtHat->Write();
            hGenInJetMultiplicity_W->Write();
            hSubEventMultiplicity_W->Write();
            hGenMultiplicity_W->Write();
        }
        hNEventsInMult->Write();
        hHiHFPlusVsHiHFMinus->Write();
        hHiHFPlusVsHiHFMinus_W->Write();
        hHiHFPlusVsHiHFMinus_WithDijet_W->Write();
        hHiHFPlusVsMultiplicity_W->Write();
        hHiHFMinusVsMultiplicity_W->Write();
        hHiHFPlusVsMultiplicity_WithDijet_W->Write();
        hHiHFMinusVsMultiplicity_WithDijet_W->Write();
    }
    if (fConfig.saveEvent)
    {
        if (fCollSystem == CollisionSystem::PbPb || fCollSystem == CollisionSystem::OO)
        {
            hHiBinVsMultiplicity_W->Write();
            hHiBinVsCorrectedMultiplicity_W->Write();
            hHiBin_W->Write();
        }
        hVz_W->Write();
        hVzWithDijet_W->Write();
        hMultiplicities_W->Write();
        hMultiplicities_DiJet_W->Write();

        if (fIsMC)
        {
            hPtHat_W->Write();
            hImpactParameter_W->Write();
            hImpactParameterVsHiBin_W->Write();
            hImpactParameterVsMultiplicity_W->Write();
        }
    }
    std::cout << "  ===> Writing Jets Histograms" << std::endl;

    gDirectory->cd("..");
    gDirectory->mkdir("Jets");
    gDirectory->cd("Jets");

    if (fConfig.saveInclusive)
    {
        hInclusiveUncorrectedRecoJets->Write();
        hInclusiveUncorrectedRecoJets_W->Write();
        hInclusiveRecoJetsCMFrame->Write();
        hInclusiveRecoJetsCMFrame_W->Write();
        hSelectedInclusiveRecoJetsMidRapidity_W->Write();
        hInclusiveRecoJetPtVsEtaCMFrame_W->Write();
        hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Write();
        hJetFlavorFractions_W->Write();
        hAverageRecoPt_W->Write();
        if (fCollSystem == CollisionSystem::pPb)
        {
            hInclusiveRecoJetsLabFrame->Write();
            hInclusiveRecoJetsLabFrame_W->Write();
            hInclusiveRecoJetPtVsEtaLabFrame_W->Write();
            hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Write();
        }
        if (fIsMC)
        {
            hInclusiveGenJetsCMFrame->Write();
            hInclusiveGenJetsCMFrame_W->Write();
            hInclusiveRefJetsCMFrame->Write();
            hInclusiveRefJetsCMFrame_W->Write();
            hSelectedInclusiveGenJetsMidRapidity_W->Write();
            hSelectedInclusiveRefJetsMidRapidity_W->Write();
            if (fCollSystem == CollisionSystem::pPb)
            {
                hInclusiveGenJetsLabFrame->Write();
                hInclusiveGenJetsLabFrame_W->Write();
                hInclusiveRefJetsLabFrame->Write();
                hInclusiveRefJetsLabFrame_W->Write();
            }

            hRecoJES_W->Write();
            hRefJES_W->Write();
            hRecoJES_Eta_W->Write();
            hRefJES_Eta_W->Write();
            hRecoJES_Eta_Pt100_W->Write();
            hRecoJES_Eta_Pt120_W->Write();
            hRefJES_Eta_Pt100_W->Write();
            hRefJES_Eta_Pt120_W->Write();
            hAverageGenPt_W->Write();
        }
    }

    if (fConfig.saveRecoDijet)
    {
        if (fConfig.saveQA)
        {
            hLeadSubLeadJets->Write();
            hLeadSubLeadJets_W->Write();
            hLeadSubLeadJets_MidRapidity_W->Write();
        }

        hLeadSubLeadJets_WithDijet_W->Write();
        hLeadSubLeadJets_WithDijet_DiJetW->Write();
        if (fCollSystem == CollisionSystem::pPb || fCollSystem == CollisionSystem::pp)
        {
            hLeadPtvsSubLeadPt_PtHatW->Write();
            hLeadPtvsSubLeadPt_DiJetW->Write();
        }
    }

    if (fIsMC)
    {
        if (fConfig.saveGenDijet)
        {
            if (fConfig.saveQA)
            {
                hGenLeadGenSubLeadJets->Write();
                hGenLeadGenSubLeadJets_W->Write();
                hGenLeadGenSubLeadJets_MidRapidity_W->Write();
                hRefLeadRefSubLeadJets->Write();
                hRefLeadRefSubLeadJets_W->Write();
                hRefLeadRefSubLeadJets_MidRapidity_W->Write();
            }

            hGenLeadGenSubLeadJets_WithDijet_W->Write();
            hGenLeadGenSubLeadJets_WithDijet_DiJetW->Write();

            hRefLeadRefSubLeadJets_WithDijet_W->Write();
            hRefLeadRefSubLeadJets_WithDijet_W->Write();

            if (fCollSystem == CollisionSystem::pPb || fCollSystem == CollisionSystem::pp)
            {
                hRefLeadPtvsRefSubLeadPt_PtHatW->Write();
                hRefLeadPtvsRefSubLeadPt_DiJetW->Write();
                hGenLeadingVsGenSubLeading_WO_DiJet_W->Write();
                hGenLeadPtvsGenSubLeadPt_DiJetW->Write();
                hGenLeadPtvsGenSubLeadPt_PtHatW->Write();
                hRefLeadPtVsRefSubLeadPtMatched_DiJetW->Write();
                hRefLeadPtVsRefSubLeadPtMatched_PtHatW->Write();
            }
        }
    }
    std::cout << "  ===> Writing Track Histograms" << std::endl;

    gDirectory->cd("..");
    gDirectory->mkdir("Tracks");
    gDirectory->cd("Tracks");
    if (fConfig.saveTracking)
    {
        hGenTrackPtVsEta->Write();
        hGenTrackPtVsEta_W->Write();
        hTrackPtVsEta->Write();
        hTrackPtVsEta_W->Write();
        hTrackPtVsEtaCorrected->Write();
        hTrackPtVsEtaCorrected_W->Write();
        hRecoTracks->Write();
        hRecoTracks_W->Write();
        hRecoTracks_Pt1_W->Write();
        if (fIsMC)
        {
            hGenTracks->Write();
            hGenTracks_W->Write();
            hGenTracks_Pt1_W->Write();
        }
    }

    std::cout << "  ===> Writing Quenching Histograms" << std::endl;

    gDirectory->cd("..");
    gDirectory->mkdir("Quenching");
    gDirectory->cd("Quenching");
    if (fConfig.saveQuenching)
    {
        hMultVsXj_W->Write();
        hHiHFVsXj_W->Write();
        if (fCollSystem != CollisionSystem::PbPb)
        {
            hMultVsXj_DiJetW->Write();
            hMultVsXj_HiHFW->Write();
            hHiHFVsXj_HiHFW->Write();
        }
        if (fIsMC)
        {
            hMultVsRefXj_W->Write();
            hMultVsMatchedRefXj_W->Write();
            hMultVsMatchedRecoXj_W->Write();

            hMultVsGenXj_W->Write();

            if (fCollSystem == CollisionSystem::pPb || fCollSystem == CollisionSystem::pp || fCollSystem == CollisionSystem::OO)
            {
                hMultVsRefXj_DiJetW->Write();
                hMultVsMatchedRefXj_DiJetW->Write();
                hMultVsGenXj_DiJetW->Write();
            }
        }
    }

    if (fConfig.saveQA)
    {
        hDeltaPhi_W->Write();
        hDeltaPhi_WithDiJet_W->Write();
        hNDijetEvent->Write();
        hRecoQuenching_W->Write();
        hRecoQuenching_WithDijet_W->Write();
        if (fIsMC)
        {
            hMultVsUnflippedMatchedRecoXj_W->Write();
            hMultVsUnflippedMatchedRefXj_DiJetW->Write();
            hMultVsUnflippedMatchedRefXj_W->Write();
            hGenDeltaPhi_W->Write();
            hGenDeltaPhi_WithDiJet_W->Write();
            hRefDeltaPhi_W->Write();
            hRefDeltaPhi_WithDiJet_W->Write();
            hNGenDijetEvent->Write();
            hGenQuenching_W->Write();
            hGenQuenching_WithDijet_W->Write();
        }
    }

    gDirectory->cd("..");
    gDirectory->mkdir("Unfolding");
    gDirectory->cd("Unfolding");
    if (fIsMC)
    {
        if (fConfig.saveUnfolding)
        {
            hResponseMatrix_W->Write();
            hTotalReco_W->Write();
            hTotalTruth_W->Write();
            hMatchedGen_W->Write();
            hMatchedReco_W->Write();
            hResponseMatrixA_W->Write();
            hTotalRecoA_W->Write();
            hTotalTruthA_W->Write();
            hMatchedGenA_W->Write();
            hMatchedRecoA_W->Write();
            hResponseMatrixB_W->Write();
            hTotalRecoB_W->Write();
            hTotalTruthB_W->Write();
            hMatchedGenB_W->Write();
            hMatchedRecoB_W->Write();
            hValidationTruth_W->Write();
        }
    }
    hTotalRecoFlat_W->Write();

    std::cout << "  ===> Writing Projections Histograms" << std::endl;

    gDirectory->cd("..");
    gDirectory->mkdir("Projections");
    gDirectory->cd("Projections");
    if (fConfig.saveQA)
    {
        hHiHFPlus->Write();
        hHiHFMinus->Write();
        hHiHFPlus_W->Write();
        hHiHFMinus_W->Write();
        hHiHFPlus_WithDijet_W->Write();
        hHiHFMinus_WithDijet_W->Write();
        hInclusiveRecoJetPt->Write();
        if (fCollSystem == CollisionSystem::pPb)
        {
            hInclusiveRecoJetEtaLabFrame->Write();
            hInclusiveRecoJetEtaLabFrame_W->Write();
        }
        hInclusiveRecoJetPt_W->Write();
        hInclusiveRecoJetEtaCMFrame->Write();
        hLeadingRecoJetPt->Write();
        hLeadingRecoJetPt_W->Write();
        hSubLeadingRecoJetPt->Write();
        hSubLeadingRecoJetPt_W->Write();
        if (fIsMC)
        {
            hInclusiveGenJetPt->Write();
            hInclusiveGenJetPt_W->Write();
            hInclusiveGenJetEtaCMFrame->Write();
            hLeadingGenJetPt->Write();
            hLeadingGenJetPt_W->Write();
            hSubLeadingGenJetPt->Write();
            hSubLeadingGenJetPt_W->Write();
            if (fCollSystem == CollisionSystem::pPb)
            {
                hInclusiveGenJetEtaLabFrame->Write();
                hInclusiveGenJetEtaLabFrame_W->Write();
            }
            hInclusiveRefJetPt->Write();
            hInclusiveRefJetPt_W->Write();
            hLeadingRefJetPt->Write();
            hLeadingRefJetPt_W->Write();
            hSubLeadingRefJetPt->Write();
            hSubLeadingRefJetPt_W->Write();
        }
    }

    hSelectedInclusiveRecoJetPt_MidRapidity_W->Write();
    hInclusiveRecoJetEtaCMFrame_W->Write();
    hSelectedInclusiveRecoJetEtaMidRapidity_W->Write();

    hLeadingRecoJetPtWithDijet_W->Write();
    hSubLeadingRecoJetPtWithDijet_W->Write();
    hLeadingRecoJetPtWithDijet_DiJetW->Write();
    hSubLeadingRecoJetPtWithDijet_DiJetW->Write();

    if (fIsMC)
    {
        hSelectedInclusiveGenJetPt_MidRapidity_W->Write();
        hInclusiveGenJetEtaCMFrame_W->Write();
        hSelectedInclusiveGenJetEtaMidRapidity_W->Write();

        hLeadingGenJetPtWithDijet_W->Write();
        hSubLeadingGenJetPtWithDijet_W->Write();
        hLeadingGenJetPtWithDijet_DiJetW->Write();
        hSubLeadingGenJetPtWithDijet_DiJetW->Write();

        hSelectedInclusiveRefJetPt_MidRapidity_W->Write();
        hLeadingRefJetPtWithDijet_W->Write();
        hSubLeadingRefJetPtWithDijet_W->Write();
        hLeadingRefJetPtWithDijet_DiJetW->Write();
        hSubLeadingRefJetPtWithDijet_DiJetW->Write();
    }
    hXj_C0_W->Write();
    if (fCollSystem != CollisionSystem::PbPb)
    {
        hXj_C0_DiJetW->Write();
    }
    if (fIsMC)
    {
        hGenXj_C0_W->Write();
        if (fCollSystem == CollisionSystem::pPb)
        {
            hGenXj_C0_DiJetW->Write();
        }
    }
    for (Int_t i = 0; i < hXj_Projection_W.size(); i++)
    {
        hXj_Projection_W[i]->Write();
        if (fCollSystem != CollisionSystem::PbPb)
        {
            hXj_Projection_DiJetW[i]->Write();
            hXj_Projection_HiHFW[i]->Write();
        }
        if (fIsMC)
        {
            hGenXj_Projection_W[i]->Write();
            hRefXj_Projection_W[i]->Write();
            hMatchedRefXj_Projection_W[i]->Write();
            if (fCollSystem == CollisionSystem::pPb || fCollSystem == CollisionSystem::pp)
            {
                hGenXj_Projection_DiJetW[i]->Write();
                hRefXj_Projection_DiJetW[i]->Write();
                hMatchedRefXj_Projection_DiJetW[i]->Write();
            }
        }
    }
    if (fCollSystem == CollisionSystem::pPb || fCollSystem == CollisionSystem::OO)
    {
        for (size_t i = 0; i < hXj_ProjectionHiHF_W.size(); i++)
        {
            hXj_ProjectionHiHF_W[i]->Write();
            hXj_ProjectionHiHF_HiHFW[i]->Write();
        }
    }

    std::cout << "Writing Histograms Complete" << std::endl;
    std::cout << "====================================" << std::endl;
}
