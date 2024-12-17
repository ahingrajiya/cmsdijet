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
                                             hSelectedMultiplicity_W{nullptr}, hMultiplicities{nullptr}, hRecoJets{nullptr}, hMultiplicities_W{nullptr}, hRecoJets_W{nullptr},
                                             hGenJets{nullptr}, hGenJets_W{nullptr}, hLeadingJet_W{nullptr}, hSubLeadingJet_W{nullptr}, hPtHat{nullptr}, hPtHat_W{nullptr},
                                             hHiBin{nullptr}, hHiBin_W{nullptr}, hVz{nullptr}, hVz_W{nullptr}, hMultiplicities_DiJet_W{nullptr}, hRecoQuenching_W{nullptr}, hGenQuenching_W{nullptr},
                                             hDeltaPhi_W{nullptr}, hXj_W{nullptr}, hNDijetEvent{nullptr}, hNEventsInMult{nullptr}, hGenLeadingJet_W{nullptr}, hGenSubLeadingJet_W{nullptr}, hGenDeltaPhi_W{nullptr},
                                             hGenXj_W{nullptr}, hNGenDijetEvent{nullptr}, hInJetMultiplicity_W{nullptr}, hGenInJetMultiplicity_W{nullptr}, hLeadSubLeadJets{nullptr},
                                             hGenLeadGenSubLeadJets{nullptr}, hGenLeadGenSubLeadJets_W{nullptr}, hLeadSubLeadJets_W{nullptr}, hVzWithDijet_W{nullptr}, hXj_DiJetW{nullptr}, hRefXj_W{nullptr}, hRefXj_DiJetW{nullptr},
                                             hRefXj_ER_W{nullptr}, hRefXj_ER_DiJetW{nullptr}, hRefLeadRefSubLeadJets{nullptr}, hRefLeadRefSubLeadJets_W{nullptr}, hGenXj_DiJetW{nullptr}, hRecoJES_W{nullptr}, hRefJES_W{nullptr},
                                             hRefLeadingJet_W{nullptr}, hRefSubLeadingJet_W{nullptr}, hGenLeadingVsGenSubLeading_WO_DiJet_W{nullptr}, hRefLeadingVsRefSubLeadingMatched_W{nullptr}, hLeadPtvsSubLeadPt_DiJetW{nullptr},
                                             hRefLeadPtvsRefSubLeadPt_DiJetW{nullptr}, hLeadSubLeadJets_MidRapidity_W{nullptr}, hGenLeadGenSubLeadJets_MidRapidity_W{nullptr}, hRefLeadRefSubLeadJets_MidRapidity_W{nullptr},
                                             hGenLeadPtvsGenSubLeadPt_DiJetW{nullptr}, hLeadSubLeadJets_WithDijet_W{nullptr}, hGenLeadGenSubLeadJets_WithDijet_W{nullptr}, hRefLeadRefSubLeadJets_WithDijet_W{nullptr},
                                             hGenLeadPtvsGenSubLeadPt_PtHatW{nullptr}, hRefLeadPtvsRefSubLeadPt_PtHatW{nullptr}, hLeadPtvsSubLeadPt_PtHatW{nullptr}, hDeltaPhi_WithDiJet_W{nullptr}, hGenDeltaPhi_WithDiJet_W{nullptr}

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
    if (hXj_W)
        delete hXj_W;
    if (hXj_DiJetW)
        delete hXj_DiJetW;
    if (hRefXj_W)
        delete hRefXj_W;
    if (hRefXj_DiJetW)
        delete hRefXj_DiJetW;
    if (hRefXj_ER_W)
        delete hRefXj_ER_W;
    if (hRefXj_ER_DiJetW)
        delete hRefXj_ER_DiJetW;
    if (hNDijetEvent)
        delete hNDijetEvent;
    if (hGenDeltaPhi_W)
        delete hGenDeltaPhi_W;
    if (hGenXj_W)
        delete hGenXj_W;
    if (hGenXj_DiJetW)
        delete hGenXj_DiJetW;
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
    if (hRecoJets)
        delete hRecoJets;
    if (hMultiplicities_W)
        delete hMultiplicities_W;
    if (hMultiplicities_DiJet_W)
        delete hMultiplicities_DiJet_W;
    if (hRecoJets_W)
        delete hRecoJets_W;
    if (hGenJets)
        delete hGenJets;
    if (hGenJets_W)
        delete hGenJets_W;
    if (hLeadingJet_W)
        delete hLeadingJet_W;
    if (hSubLeadingJet_W)
        delete hSubLeadingJet_W;
    if (hGenLeadingJet_W)
        delete hGenLeadingJet_W;
    if (hGenSubLeadingJet_W)
        delete hGenSubLeadingJet_W;
    if (hRefLeadingJet_W)
        delete hRefLeadingJet_W;
    if (hRefSubLeadingJet_W)
        delete hRefSubLeadingJet_W;
    if (hGenLeadingVsGenSubLeading_WO_DiJet_W)
        delete hGenLeadingVsGenSubLeading_WO_DiJet_W;
    if (hRefLeadingVsRefSubLeadingMatched_W)
        delete hRefLeadingVsRefSubLeadingMatched_W;
    if (hRecoQuenching_W)
        delete hRecoQuenching_W;
    if (hGenQuenching_W)
        delete hGenQuenching_W;
}

void HistoManagerDiJet::init(const Bool_t &isMC)
{
    int nMultiplicityBins = fMultiplicityBins.size() - 1;

    hRecoMultiplicity_W = new TH1D("hRecoMultiplicity_W", "Reco Multiplicity Weighted", 600, 0.0, 600.0);
    hRecoMultiplicity_W->Sumw2();
    hCorrectedMultiplicity_W = new TH1D("hCorrectedMultiplicity_W", "Corrected Multiplicity Weighted", 600, 0.0, 600.0);
    hCorrectedMultiplicity_W->Sumw2();
    hGenMultiplicity_W = new TH1D("hGenMultiplicity_W", "Gen Multiplicity Weighted", 600, 0.0, 600.0);
    hGenMultiplicity_W->Sumw2();
    hSubEventMultiplicity_W = new TH1D("hSubEventMultiplicity_W", "Underlying Event Multiplicity Weighted", 600, 0., 600.);
    hSubEventMultiplicity_W->Sumw2();
    hSelectedMultiplicity_W = new TH1D("hSelectedMultiplicity", "Multiplicity Distribution after selection Weighted", 600, 0., 600.);
    hSelectedMultiplicity_W->Sumw2();
    hInJetMultiplicity_W = new TH2D("hInJetMultiplicity_W", "Multiplicity in Jets", 30, 0., 30., 600, 0., 600.);
    hInJetMultiplicity_W->Sumw2();
    hGenInJetMultiplicity_W = new TH2D("hGenInJetMultiplicity_W", "Gen Multiplicity in Jets", 30, 0., 30., 600, 0., 600.);
    hGenInJetMultiplicity_W->Sumw2();

    hPtHat = new TH1D("hPtHat", "#hat{p_{T}} Distribution", 100, 0.0, 1000.0);
    hPtHat->Sumw2();
    hPtHat_W = new TH1D("hPtHat_W", "#hat{p_{T}} Distribution Weighted", 100, 0.0, 1000.0);
    hPtHat_W->Sumw2();
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
    hNGenDijetEvent = new TH1D("hNGenDijetEvent", "Number of Gen Dijet Events", 2, 0, 2);
    hNGenDijetEvent->Sumw2();

    int MultBins[5] = {600, 600, 600, 600, nMultiplicityBins};
    Double_t MultMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t MultMax[5] = {600.0, 600.0, 600.0, 600.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hMultiplicities = new THnSparseD("hMultiplicities", "Multiplicity Distribution", 5, MultBins, MultMin, MultMax);
    hMultiplicities->Sumw2();
    hMultiplicities_W = new THnSparseD("hMultiplicities_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    hMultiplicities_W->Sumw2();
    hMultiplicities_DiJet_W = new THnSparseD("hMultiplicities_DiJet_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    hMultiplicities_DiJet_W->Sumw2();

    int JetBins[4] = {100, 40, 32, nMultiplicityBins};
    Double_t JetMin[4] = {0.0, -4.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t JetMax[4] = {1000.0, 4.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hRecoJets = new THnSparseD("hRecoJets", "Reco Jet Distribution", 4, JetBins, JetMin, JetMax);
    hRecoJets->Sumw2();
    hRecoJets_W = new THnSparseD("hRecoJets_W", "Reco Jet Distribution with Weights", 4, JetBins, JetMin, JetMax);
    hRecoJets_W->Sumw2();
    hGenJets = new THnSparseD("hGenJets", "Gen Jet Distribution", 4, JetBins, JetMin, JetMax);
    hGenJets->Sumw2();
    hGenJets_W = new THnSparseD("hGenJets_W", "Gen Jet Distribution with Weights", 4, JetBins, JetMin, JetMax);
    hGenJets_W->Sumw2();
    hLeadingJet_W = new THnSparseD("hLeadingJet_W", "Leading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hLeadingJet_W->Sumw2();
    hSubLeadingJet_W = new THnSparseD("hSubLeadingJet_W", "SubLeading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hSubLeadingJet_W->Sumw2();
    hGenLeadingJet_W = new THnSparseD("hGenLeadingJet_W", "Gen Leading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hGenLeadingJet_W->Sumw2();
    hGenSubLeadingJet_W = new THnSparseD("hGenSubLeadingJet_W", "Gen SubLeading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hGenSubLeadingJet_W->Sumw2();
    hRefLeadingJet_W = new THnSparseD("hRefLeadingJet_W", "Ref Leading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hRefLeadingJet_W->Sumw2();
    hRefSubLeadingJet_W = new THnSparseD("hRefSubLeadingJet_W", "Ref SubLeading Jet Distribution Weighted", 4, JetBins, JetMin, JetMax);
    hRefSubLeadingJet_W->Sumw2();

    int LeadSLeadJetBins[7] = {100, 50, 32, 100, 50, 32, nMultiplicityBins};
    Double_t LeadSLeadJetMin[7] = {0.0, -5.0, -TMath::Pi(), 0.0, -5.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t LeadSLeadJetMax[7] = {1000.0, 5.0, TMath::Pi(), 1000.0, 5.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hGenLeadingVsGenSubLeading_WO_DiJet_W = new TH2D("hGenLeadingVsGenSubLeading_WO_DiJet_W", "Gen Leading vs Gen SubLeading Jet", 100, 0., 1000., 100, 0., 1000.);
    hGenLeadingVsGenSubLeading_WO_DiJet_W->Sumw2();
    hRefLeadingVsRefSubLeadingMatched_W = new TH2D("hRefLeadingVsRefSubLeadingMatched_W", "Ref Leading vs Ref SubLeading Jet", 100, 0., 1000., 100, 0., 1000.);
    hRefLeadingVsRefSubLeadingMatched_W->Sumw2();
    hLeadSubLeadJets = new THnSparseD("hLeadSubLeadJets", "Lead vs SubLead Pt", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets->Sumw2();
    hLeadSubLeadJets_W = new THnSparseD("hLeadSubLeadJets_W", "Lead vs SubLead Pt Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_W->Sumw2();
    hLeadSubLeadJets_MidRapidity_W = new THnSparseD("hLeadSubLeadJets_MidRapidity_W", "Lead vs SubLead Pt MidRapidity Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_MidRapidity_W->Sumw2();
    hLeadSubLeadJets_WithDijet_W = new THnSparseD("hLeadSubLeadJets_WithDijet_W", "Lead vs SubLead Pt With Dijet Weighted", 7, LeadSLeadJetBins, LeadSLeadJetMin, LeadSLeadJetMax);
    hLeadSubLeadJets_WithDijet_W->Sumw2();
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

    const int nDphiBins = 30; // number of bins
    double DphiBins[nDphiBins + 1] = {0.0, TMath::Pi() / 5., TMath::Pi() / 3., (3. / 7.) * TMath::Pi(), TMath::Pi() / 2., (4. / 7.) * TMath::Pi(), (3. / 5.) * TMath::Pi(), 1.93731547, 1.98967535, 2.04203522, 2.0943951, 2.14675498, 2.19911486, 2.25147474, 2.30383461, 2.35619449, 2.40855437, 2.46091425, 2.51327412, 2.565634, 2.61799388, 2.67035376, 2.72271363, 2.77507351, 2.82743339, 2.87979327, 2.93215314, 2.98451302, 3.0368729, 3.08923278, TMath::Pi()};
    const int nXjAjBins = 16; // number of bins
    double XjBins[nXjAjBins + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};
    const int nXjAjBins_ER = 26; // number of bins
    double XjBins_ER[nXjAjBins_ER + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5};

    int QuenchBins[5] = {nXjAjBins, nDphiBins, 100, 100, nMultiplicityBins};
    Double_t QuenchMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMax[5] = {1.0, TMath::Pi(), 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    double multBinArray[fMultiplicityBins.size()];
    copy(fMultiplicityBins.begin(), fMultiplicityBins.end(), multBinArray);

    hRecoQuenching_W = new THnSparseD("hRecoQuenching_W", "Reco Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    hRecoQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hRecoQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hRecoQuenching_W->Sumw2();
    hGenQuenching_W = new THnSparseD("hGenQuenching_W", "Gen Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    hGenQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hGenQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hGenQuenching_W->Sumw2();
    hDeltaPhi_W = new TH1D("hDeltaPhi_W", "Delta Phi Distribution Weighted", nDphiBins, DphiBins);
    hDeltaPhi_W->Sumw2();
    hDeltaPhi_WithDiJet_W = new TH1D("hDeltaPhi_WithDiJet_W", "Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
    hDeltaPhi_WithDiJet_W->Sumw2();
    hGenDeltaPhi_W = new TH1D("hGenDeltaPhi_W", "Gen Delta Phi Distribution Weighted", nDphiBins, DphiBins);
    hGenDeltaPhi_W->Sumw2();
    hGenDeltaPhi_WithDiJet_W = new TH1D("hGenDeltaPhi_WithDiJet_W", "Gen Delta Phi Distribution With Dijet Present Weighted", nDphiBins, DphiBins);
    hGenDeltaPhi_WithDiJet_W->Sumw2();
    hXj_W = new TH2D("hXj_W", "Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hXj_W->Sumw2();
    hXj_DiJetW = new TH2D("hXj_DiJetW", "Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hXj_DiJetW->Sumw2();
    hRefXj_W = new TH2D("hRefXj_W", "RefXj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hRefXj_W->Sumw2();
    hRefXj_DiJetW = new TH2D("hRefXj_DiJetW", "RefXj Distribution XjWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hRefXj_DiJetW->Sumw2();
    hRefXj_ER_W = new TH2D("hRefXj_ER_W", "RefXj Distribution ER Weighted", nXjAjBins_ER, XjBins_ER, nMultiplicityBins, multBinArray);
    hRefXj_ER_W->Sumw2();
    hRefXj_ER_DiJetW = new TH2D("hRefXj_ER_DiJetW", "RefXj Distribution ER XjWeighted", nXjAjBins_ER, XjBins_ER, nMultiplicityBins, multBinArray);
    hRefXj_ER_DiJetW->Sumw2();
    hGenXj_W = new TH2D("hGenXj_W", "Gen Xj Distribution Weighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hGenXj_W->Sumw2();
    hGenXj_DiJetW = new TH2D("hGenXj_DiJetW", "Gen Xj Distribution DijetWeighted", nXjAjBins, XjBins, nMultiplicityBins, multBinArray);
    hGenXj_DiJetW->Sumw2();

    Float_t LeadSubLeadPtBins[] = {50., 55., 60., 65., 70., 75., 80., 90., 100., 110., 120., 130., 145., 160., 175., 195., 215., 235., 260., 285., 315., 345., 380., 420, 460., 500., 550., 600., 700., 900., 1200., 1600., 2000.};
    Int_t nLeadSubLeadPtBins = sizeof(LeadSubLeadPtBins) / sizeof(Float_t) - 1;
    hLeadPtvsSubLeadPt_PtHatW = new TH2D("hLeadPtvsSubLeadPt_PtHatW", "Lead Pt vs SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt_PtHatW->Sumw2();
    hLeadPtvsSubLeadPt_DiJetW = new TH2D("hLeadPtvsSubLeadPt_DiJetW", "Lead Pt vs SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt_DiJetW->Sumw2();

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

void HistoManagerDiJet ::writeOutput(const Bool_t &isMC)
{
    gDirectory->mkdir("Events");
    gDirectory->cd("Events");
    hPtHat->Write();
    hPtHat_W->Write();
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
        hGenInJetMultiplicity_W->Write();
        hGenMultiplicity_W->Write();
        hSubEventMultiplicity_W->Write();
    }
    hNEventsInMult->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Jets");
    gDirectory->cd("Jets");
    hRecoJets->Write();
    hRecoJets_W->Write();
    hLeadingJet_W->Write();
    hSubLeadingJet_W->Write();

    if (fIsMC)
    {
        hGenJets->Write();
        hGenJets_W->Write();
        hGenLeadingJet_W->Write();
        hGenSubLeadingJet_W->Write();
        hRefLeadingJet_W->Write();
        hRefSubLeadingJet_W->Write();
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
    hXj_W->Write();
    hXj_DiJetW->Write();
    hNDijetEvent->Write();

    if (fIsMC)
    {
        hRefXj_W->Write();
        hRefXj_DiJetW->Write();
        hRefXj_ER_W->Write();
        hRefXj_ER_DiJetW->Write();
        hGenQuenching_W->Write();
        hGenDeltaPhi_W->Write();
        hGenDeltaPhi_WithDiJet_W->Write();
        hGenXj_W->Write();
        hGenXj_DiJetW->Write();
        hNGenDijetEvent->Write();
    }
}
