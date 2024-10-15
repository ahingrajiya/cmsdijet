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
                                             hRecoMultiplicity{nullptr}, hCorrectedMultiplicity{nullptr}, hGenMultiplicity{nullptr}, hSubEventMultiplicity{nullptr},
                                             hSelectedMultiplicity{nullptr}, hMultiplicities{nullptr}, hRecoJets{nullptr}, hMultiplicities_W{nullptr}, hRecoJets_W{nullptr},
                                             hGenJets{nullptr}, hGenJets_W{nullptr}, hLeadingJet{nullptr}, hSubLeadingJet{nullptr}, hPtHat{nullptr}, hPtHat_W{nullptr},
                                             hHiBin{nullptr}, hHiBin_W{nullptr}, hVz{nullptr}, hVz_W{nullptr}, hMultiplicities_DiJet_W{nullptr}, hRecoQuenching_W{nullptr}, hGenQuenching_W{nullptr}

{
    /* Empty*/
}

HistoManagerDiJet::~HistoManagerDiJet()
{
    if (hRecoMultiplicity)
        delete hRecoMultiplicity;
    if (hCorrectedMultiplicity)
        delete hCorrectedMultiplicity;
    if (hGenMultiplicity)
        delete hGenMultiplicity;
    if (hSubEventMultiplicity)
        delete hSubEventMultiplicity;
    if (hSelectedMultiplicity)
        delete hSelectedMultiplicity;
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
    if (hLeadingJet)
        delete hLeadingJet;
    if (hSubLeadingJet)
        delete hSubLeadingJet;
    if (hRecoQuenching_W)
        delete hRecoQuenching_W;
    if (hGenQuenching_W)
        delete hGenQuenching_W;
}

void HistoManagerDiJet::init(const Bool_t &isMC)
{
    int nMultiplicityBins = fMultiplicityBins.size() - 1;

    hRecoMultiplicity = new TH1D("hRecoMultiplicity", "Reco Multiplicity", 600, 0.0, 600.0);
    hRecoMultiplicity->Sumw2();
    hCorrectedMultiplicity = new TH1D("hCorrectedMultiplicity", "Corrected Multiplicity", 600, 0.0, 600.0);
    hCorrectedMultiplicity->Sumw2();
    hGenMultiplicity = new TH1D("hGenMultiplicity", "Gen Multiplicity", 600, 0.0, 600.0);
    hGenMultiplicity->Sumw2();
    hSubEventMultiplicity = new TH1D("hSubEventMultiplicity", "Underlying Event Multiplicity", 600, 0., 600.);
    hSubEventMultiplicity->Sumw2();
    hSelectedMultiplicity = new TH1D("hSelectedMultiplicity", "Multiplicity Distribution after selection", 600, 0., 600.);
    hSelectedMultiplicity->Sumw2();
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

    int MultBins[5] = {600, 600, 600, 600, nMultiplicityBins};
    Double_t MultMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t MultMax[5] = {600.0, 600.0, 600.0, 600.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hMultiplicities = new THnSparseD("hMultiplicities", "Multiplicity Distribution", 5, MultBins, MultMin, MultMax);
    // hMultiplicities->GetAxis(4)->Set(fMultiplicityBins.size() - 1, fMultiplicityBins.data());
    hMultiplicities->Sumw2();
    hMultiplicities_W = new THnSparseD("hMultiplicities_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    // hMultiplicities_W->GetAxis(4)->Set(fMultiplicityBins.size() - 1, fMultiplicityBins.data());
    hMultiplicities_W->Sumw2();
    hMultiplicities_DiJet_W = new THnSparseD("hMultiplicities_DiJet_W", "Multiplicity Distribution with Weights", 5, MultBins, MultMin, MultMax);
    // hMultiplicities_DiJet_W->GetAxis(4)->Set(fMultiplicityBins.size() - 1, fMultiplicityBins.data());

    int JetBins[4] = {100, 40, 32, nMultiplicityBins};
    Double_t JetMin[4] = {0.0, -4.0, -TMath::Pi(), fMultiplicityBins[0]};
    Double_t JetMax[4] = {1000.0, 4.0, TMath::Pi(), fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hRecoJets = new THnSparseD("hRecoJets", "Reco Jet Distribution", 5, JetBins, JetMin, JetMax);
    // hRecoJets->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hRecoJets->Sumw2();
    hRecoJets_W = new THnSparseD("hRecoJets_W", "Reco Jet Distribution with Weights", 5, JetBins, JetMin, JetMax);
    // hRecoJets_W->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hRecoJets_W->Sumw2();
    hGenJets = new THnSparseD("hGenJets", "Gen Jet Distribution", 5, JetBins, JetMin, JetMax);
    // hGenJets->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hGenJets->Sumw2();
    hGenJets_W = new THnSparseD("hGenJets_W", "Gen Jet Distribution with Weights", 5, JetBins, JetMin, JetMax);
    // hGenJets_W->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hGenJets_W->Sumw2();
    hLeadingJet = new THnSparseD("hLeadingJet", "Leading Jet Distribution", 5, JetBins, JetMin, JetMax);
    // hLeadingJet->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hLeadingJet->Sumw2();
    hSubLeadingJet = new THnSparseD("hSubLeadingJet", "SubLeading Jet Distribution", 5, JetBins, JetMin, JetMax);
    // hSubLeadingJet->GetAxis(3)->Set(JetBins[3], fMultiplicityBins.data());
    hSubLeadingJet->Sumw2();

    const int nDphiBins = 30; // number of bins
    double DphiBins[nDphiBins + 1] = {0.0, TMath::Pi() / 5., TMath::Pi() / 3., (3. / 7.) * TMath::Pi(), TMath::Pi() / 2., (4. / 7.) * TMath::Pi(), (3. / 5.) * TMath::Pi(), 1.93731547, 1.98967535, 2.04203522, 2.0943951, 2.14675498, 2.19911486, 2.25147474, 2.30383461, 2.35619449, 2.40855437, 2.46091425, 2.51327412, 2.565634, 2.61799388, 2.67035376, 2.72271363, 2.77507351, 2.82743339, 2.87979327, 2.93215314, 2.98451302, 3.0368729, 3.08923278, TMath::Pi()};
    const int nXjAjBins = 16; // number of bins
    double XjBins[nXjAjBins + 1] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0};

    int QuenchBins[5] = {nXjAjBins, nDphiBins, 100, 100, nMultiplicityBins};
    Double_t QuenchMin[5] = {0.0, 0.0, 0.0, 0.0, fMultiplicityBins[0]};
    Double_t QuenchMax[5] = {1.0, TMath::Pi(), 1000.0, 1000.0, fMultiplicityBins[fMultiplicityBins.size() - 1]};
    hRecoQuenching_W = new THnSparseD("hRecoQuenching_W", "Reco Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    // hRecoQuenching_W->GetAxis(4)->Set(QuenchBins[4], fMultiplicityBins.data());
    hRecoQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hRecoQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hRecoQuenching_W->Sumw2();
    hGenQuenching_W = new THnSparseD("hGenQuenching_W", "Gen Quenching", 5, QuenchBins, QuenchMin, QuenchMax);
    // hGenQuenching_W->GetAxis(4)->Set(QuenchBins[4], fMultiplicityBins.data());
    hGenQuenching_W->GetAxis(0)->Set(QuenchBins[0], XjBins);
    hGenQuenching_W->GetAxis(1)->Set(QuenchBins[1], DphiBins);
    hGenQuenching_W->Sumw2();
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
    hRecoMultiplicity->Write();
    hCorrectedMultiplicity->Write();
    hGenMultiplicity->Write();
    hSubEventMultiplicity->Write();
    hSelectedMultiplicity->Write();
    hMultiplicities->Write();
    hMultiplicities_W->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Jets");
    gDirectory->cd("Jets");
    hRecoJets->Write();
    hRecoJets_W->Write();
    hGenJets->Write();
    hGenJets_W->Write();
    hLeadingJet->Write();
    hSubLeadingJet->Write();

    gDirectory->cd("..");
    gDirectory->mkdir("Quenching");
    gDirectory->cd("Quenching");
    hRecoQuenching_W->Write();
    hGenQuenching_W->Write();
}
