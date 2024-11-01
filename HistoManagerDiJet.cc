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
                                             hGenXj_W{nullptr}, hNGenDijetEvent{nullptr}, hInJetMultiplicity_W{nullptr}, hGenInJetMultiplicity_W{nullptr}, hLeadPtvsSubLeadPt_W{nullptr},
                                             hGenLeadPtvsGenSubLeadPt_W{nullptr}, hGenLeadPtvsGenSubLeadPt{nullptr}, hLeadPtvsSubLeadPt{nullptr}

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
    if (hDeltaPhi_W)
        delete hDeltaPhi_W;
    if (hXj_W)
        delete hXj_W;
    if (hNDijetEvent)
        delete hNDijetEvent;
    if (hGenDeltaPhi_W)
        delete hGenDeltaPhi_W;
    if (hGenXj_W)
        delete hGenXj_W;
    if (hNGenDijetEvent)
        delete hNGenDijetEvent;
    if (hNEventsInMult)
        delete hNEventsInMult;

    if (hInJetMultiplicity_W)
        delete hInJetMultiplicity_W;
    if (hGenInJetMultiplicity_W)
        delete hGenInJetMultiplicity_W;

    if (hLeadPtvsSubLeadPt)
        delete hLeadPtvsSubLeadPt;
    if (hGenLeadPtvsGenSubLeadPt)
        delete hGenLeadPtvsGenSubLeadPt;
    if (hLeadPtvsSubLeadPt_W)
        delete hLeadPtvsSubLeadPt_W;
    if (hGenLeadPtvsGenSubLeadPt_W)
        delete hGenLeadPtvsGenSubLeadPt_W;

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
    hRecoJets = new THnSparseD("hRecoJets", "Reco Jet Distribution", 5, JetBins, JetMin, JetMax);
    hRecoJets->Sumw2();
    hRecoJets_W = new THnSparseD("hRecoJets_W", "Reco Jet Distribution with Weights", 5, JetBins, JetMin, JetMax);
    hRecoJets_W->Sumw2();
    hGenJets = new THnSparseD("hGenJets", "Gen Jet Distribution", 5, JetBins, JetMin, JetMax);
    hGenJets->Sumw2();
    hGenJets_W = new THnSparseD("hGenJets_W", "Gen Jet Distribution with Weights", 5, JetBins, JetMin, JetMax);
    hGenJets_W->Sumw2();
    hLeadingJet_W = new THnSparseD("hLeadingJet_W", "Leading Jet Distribution Weighted", 5, JetBins, JetMin, JetMax);
    hLeadingJet_W->Sumw2();
    hSubLeadingJet_W = new THnSparseD("hSubLeadingJet_W", "SubLeading Jet Distribution Weighted", 5, JetBins, JetMin, JetMax);
    hSubLeadingJet_W->Sumw2();
    hGenLeadingJet_W = new THnSparseD("hGenLeadingJet_W", "Gen Leading Jet Distribution Weighted", 5, JetBins, JetMin, JetMax);
    hGenLeadingJet_W->Sumw2();
    hGenSubLeadingJet_W = new THnSparseD("hGenSubLeadingJet_W", "Gen SubLeading Jet Distribution Weighted", 5, JetBins, JetMin, JetMax);
    hGenSubLeadingJet_W->Sumw2();

    const int nDphiBins = 30; // number of bins
    double DphiBins[nDphiBins + 1] = {0.0, TMath::Pi() / 5., TMath::Pi() / 3., (3. / 7.) * TMath::Pi(), TMath::Pi() / 2., (4. / 7.) * TMath::Pi(), (3. / 5.) * TMath::Pi(), 1.93731547, 1.98967535, 2.04203522, 2.0943951, 2.14675498, 2.19911486, 2.25147474, 2.30383461, 2.35619449, 2.40855437, 2.46091425, 2.51327412, 2.565634, 2.61799388, 2.67035376, 2.72271363, 2.77507351, 2.82743339, 2.87979327, 2.93215314, 2.98451302, 3.0368729, 3.08923278, TMath::Pi()};
    const int nXjAjBins = 16; // number of bins
    double XjBins[nXjAjBins + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};

    int QuenchBins[5] = {nXjAjBins, nDphiBins, 100, 100, nMultiplicityBins};
    Double_t QuenchMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMax[5] = {1.0, TMath::Pi(), 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
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
    hGenDeltaPhi_W = new TH1D("hGenDeltaPhi_W", "Gen Delta Phi Distribution Weighted", nDphiBins, DphiBins);
    hGenDeltaPhi_W->Sumw2();
    hXj_W = new TH1D("hXj_W", "Xj Distribution Weighted", nXjAjBins, XjBins);
    hXj_W->Sumw2();
    hGenXj_W = new TH1D("hGenXj_W", "Gen Xj Distribution Weighted", nXjAjBins, XjBins);
    hGenXj_W->Sumw2();

    Float_t LeadSubLeadPtBins[] = {50., 60., 70., 80., 90., 100., 110., 120., 130., 140., 150., 160., 170., 180., 190., 200., 220., 240., 260., 280., 300., 350., 400., 450., 500., 600., 700., 1200.};
    Int_t nLeadSubLeadPtBins = sizeof(LeadSubLeadPtBins) / sizeof(Float_t) - 1;
    hLeadPtvsSubLeadPt = new TH2D("hLeadPtvsSubLeadPt", "Lead Pt vs SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt->Sumw2();
    hLeadPtvsSubLeadPt_W = new TH2D("hLeadPtvsSubLeadPt_W", "Lead Pt vs SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hLeadPtvsSubLeadPt_W->Sumw2();

    hGenLeadPtvsGenSubLeadPt = new TH2D("hGenLeadPtvsGenSubLeadPt", "Gen Lead Pt vs Gen SubLead Pt", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hGenLeadPtvsGenSubLeadPt->Sumw2();
    hGenLeadPtvsGenSubLeadPt_W = new TH2D("hGenLeadPtvsGenSubLeadPt_W", "Gen Lead Pt vs Gen SubLead Pt Weighted", nLeadSubLeadPtBins, LeadSubLeadPtBins, nLeadSubLeadPtBins, LeadSubLeadPtBins);
    hGenLeadPtvsGenSubLeadPt_W->Sumw2();
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
    hRecoMultiplicity_W->Write();
    hCorrectedMultiplicity_W->Write();
    hGenMultiplicity_W->Write();
    hSubEventMultiplicity_W->Write();
    hSelectedMultiplicity_W->Write();
    hMultiplicities->Write();
    hMultiplicities_W->Write();
    hInJetMultiplicity_W->Write();
    hGenInJetMultiplicity_W->Write();
    hNEventsInMult->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Jets");
    gDirectory->cd("Jets");
    hRecoJets->Write();
    hRecoJets_W->Write();
    hLeadingJet_W->Write();
    hSubLeadingJet_W->Write();

    hGenJets->Write();
    hGenJets_W->Write();
    hGenLeadingJet_W->Write();
    hGenSubLeadingJet_W->Write();

    hLeadPtvsSubLeadPt->Write();
    hLeadPtvsSubLeadPt_W->Write();
    hGenLeadPtvsGenSubLeadPt->Write();
    hGenLeadPtvsGenSubLeadPt_W->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Quenching");
    gDirectory->cd("Quenching");
    hRecoQuenching_W->Write();
    hDeltaPhi_W->Write();
    hXj_W->Write();
    hNDijetEvent->Write();

    hGenQuenching_W->Write();
    hGenDeltaPhi_W->Write();
    hGenXj_W->Write();
    hNGenDijetEvent->Write();
}
