/**
 * @file DiJetAnalysis.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Dijet analysis for pPb and PbPb
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

// Jet Analysis Header
#include "DiJetAnalysis.h"

// ROOT Headers
#include "TObject.h"
#include "TMath.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TF1.h"
#include "TVector3.h"

// C++ header
#include <iostream>

ClassImp(DiJetAnalysis)

    DiJetAnalysis::DiJetAnalysis() : BaseAnalysis(), fDebug{kFALSE}, fUseCentralityWeight{kFALSE}, fHM{nullptr}, fIspPb{kFALSE},
                                     fIsMC{kFALSE}, fDeltaPhi{5. * TMath::Pi() / 6.}, fIsPbGoing{kTRUE}, fUseCMFrame{kFALSE},
                                     fEtaBoost{0.0}, fUseMultiplicityWeight{kFALSE}, fLeadJetPtLow{100.}, fSubLeadJetPtLow{50.}, fNEventsInSample{100000000},
                                     fIsDiJetFound{kFALSE}, fVerbose{kFALSE}, fMinTrkPt{0.5}, fTrkEffPbPb{nullptr}, fTrkEffpPb{nullptr}, fTrkEffTable{""}, fEventCounter{0},
                                     fCycleCounter{0}, fMultWeightTable{""}, fMultiplicityWeight{nullptr}, fMultWeight{nullptr}
{
    fLeadJetEtaRange[0] = {-1.};
    fLeadJetEtaRange[1] = {1.};
    fSubLeadJetEtaRange[0] = {-1.};
    fSubLeadJetEtaRange[1] = {1.};
    fMultiplicityRange[0] = {30.};
    fMultiplicityRange[1] = {50.};
    fTrkEtaRange[0] = {-2.4};
    fTrkEtaRange[1] = {2.4};
}

DiJetAnalysis::~DiJetAnalysis()
{
    if (fHM)
    {
        delete fHM;
        // fHM = nullptr;
    }
    if (fTrkEffPbPb)
    {
        delete fTrkEffPbPb;
        fTrkEffPbPb = nullptr;
    }
    if (fTrkEffpPb)
    {
        delete fTrkEffpPb;
        fTrkEffpPb = nullptr;
    }
    if (fUseMultiplicityWeight)
    {
        fMultWeight->Close();
        for (Int_t i = 0; i < 4; i++)
        {
            if (fMultiplicityWeight[i])
            {
                delete fMultiplicityWeight[i];
            }
        }
    }
}

void DiJetAnalysis::init()
{
    if (fVerbose)
    {
        std::cout << "DiJetAnalysis::init  Initializing DiJet Analysis" << std::endl;
    }

    SetUpTrackingEfficiency(fIspPb, fTrkEffTable);

    if (fUseMultiplicityWeight)
    {
        SetUpMultiplicityWeight(fMultWeightTable);
    }
}

Int_t DiJetAnalysis::RecoMultiplicity(const Bool_t &ispPb, const Event *event)
{
    Int_t iRecoMult = 0;
    TrackIterator recoIterator;
    for (recoIterator = event->trackCollection()->begin(); recoIterator != event->trackCollection()->end(); recoIterator++)
    {
        Double_t trackPt = (*recoIterator)->TrkPt();
        Double_t trackEta = (*recoIterator)->TrkEta();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta > fTrkEtaRange[0] && trackEta < fTrkEtaRange[1]);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
            iRecoMult++;
    }
    return iRecoMult;
}

void DiJetAnalysis::SetUpMultiplicityWeight(const std::string &multWeightTable)
{
    fMultWeight = TFile::Open(multWeightTable.c_str(), "OPEN");
    // fMultWeight = TFile::Open("../aux_files/PbPb_5020/Multiplicity_Weight/mult_weight_1p0.root");

    if (!fMultWeight)
    {
        std::cerr << "Multiplicity weight table not found" << std::endl;
    }
    else
    {
        fMultiplicityWeight[0] = (TH1D *)fMultWeight->Get("mult_60_120");
        fMultiplicityWeight[1] = (TH1D *)fMultWeight->Get("mult_120_185");
        // fMultiplicityWeight[2] = (TH1D *)f->Get("mult_185");
        // fMultiplicityWeight[3] = (TH1D *)f->Get("mult_250");
    }
}

void DiJetAnalysis::SetUpTrackingEfficiency(const Bool_t &ispPb, const std::string &trackingEfficiencyTable)
{
    if (!ispPb)
    {
        fTrkEffPbPb = new TrkEff2018PbPb("general", "", false, trackingEfficiencyTable);
    }

    else if (ispPb)
    {
        fTrkEffpPb = new TrkEfficiency2016pPb(trackingEfficiencyTable);
    }

    else
    {
        std::cerr << "Tracking efficiency table not found for the given system and year" << std::endl;
    }
}

Float_t DiJetAnalysis::CorrectedMultiplicity(const Bool_t &ispPb, const Event *event)
{
    Float_t iCorrectedMult = 0;
    TrackIterator recoIterator;
    for (recoIterator = event->trackCollection()->begin(); recoIterator != event->trackCollection()->end(); recoIterator++)
    {
        Double_t trackPt = (*recoIterator)->TrkPt();
        Double_t trackEta = (*recoIterator)->TrkEta();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta > fTrkEtaRange[0] && trackEta < fTrkEtaRange[1]);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            if (ispPb)
            {
                iCorrectedMult += fTrkEffpPb->getCorrection(trackPt, trackEta);
            }
            else if (!ispPb)
            {
                iCorrectedMult += fTrkEffPbPb->getCorrection(trackPt, trackEta, event->hiBin());
            }
        }
    }
    return iCorrectedMult;
}

Int_t DiJetAnalysis::GenMultiplicity(const Bool_t &isMC, const Event *event)
{
    if (!isMC)
    {
        std::cerr << "This function is only for MC. MC is set to be FALSE." << std::endl;
        return -1;
    }
    Int_t iGenMult = 0;
    GenTrackIterator genIterator;
    for (genIterator = event->genTrackCollection()->begin(); genIterator != event->genTrackCollection()->end(); genIterator++)
    {
        Double_t trackPt = (*genIterator)->TrkPt();
        Double_t trackEta = (*genIterator)->TrkEta();
        Int_t trackCharge = (*genIterator)->TrkChg();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1] && trackCharge != 0);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f <= Track Eta: %5.2f <= %5.2f, Track Charge = %i /= 0 \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackCharge, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
            iGenMult++;
    }
    return iGenMult;
}

Int_t DiJetAnalysis::SubEventMultiplicity(const Bool_t &isMC, const Bool_t &ispPb, const Event *event)
{
    if (!isMC)
    {
        std::cerr << "Subevent can only be calculated for PYTHIA + HYDJET Monte Carlo. MC is set to be FALSE" << std::endl;
        return -1;
    }

    if (ispPb)
    {
        std::cerr << "Subevent can only be calculated for PYTHIA + HYDJET Monte Carlo. IspPb is set to be TRUE" << std::endl;
        return -1;
    }
    Int_t iSube = 0;
    GenTrackIterator genIterator;
    for (genIterator = event->genTrackCollection()->begin(); genIterator != event->genTrackCollection()->end(); genIterator++)
    {
        Double_t trackPt = (*genIterator)->TrkPt();
        Double_t trackEta = (*genIterator)->TrkEta();
        Int_t trackSube = (*genIterator)->TrackSube();
        Int_t trackCharge = (*genIterator)->TrkChg();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta > fTrkEtaRange[0] && trackEta < fTrkEtaRange[1] && trackSube > 0, trackCharge != 0);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f , Track Sube : %i, Track Charge : %i \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackSube, trackCharge, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
            iSube++;
    }
    return iSube;
}
Double_t *DiJetAnalysis::MultiplicityWeight(const Bool_t &ispPb, const Int_t &multiplicity)
{
    Double_t *weight = new Double_t[4]{0.0};
    if (!ispPb && fIsMC)
    {
        weight[0] = fMultiplicityWeight[0]->GetBinContent(multiplicity);
        weight[1] = fMultiplicityWeight[1]->GetBinContent(multiplicity);
        // weight[2] = fMultiplicityWeight[2]->GetBinContent(multiplicity);
        // weight[3] = fMultiplicityWeight[3]->GetBinContent(multiplicity);
    }
    else
    {
        weight[0] = 1.;
        weight[1] = 1.;
        weight[2] = 1.;
        weight[3] = 1.;
    }
    return weight;
}

Double_t DiJetAnalysis::EventWeight(const Bool_t &ispPb, Bool_t &isMC, const Event *event)
{
    Double_t ptHatWeight{1.};
    Double_t eventWeight{1.};
    Double_t vzWeight{1.};
    Double_t ptHat = event->ptHat();
    Double_t vertexZ = event->vz();
    if (isMC && ispPb)
    {
        // Magic numbers are (cross section x Nevents generated). These are derived manually and fixed
        if (ptHat > 15.0 && ptHat <= 30.)
        {
            ptHatWeight = 1.0404701e-06 * 961104;
        }
        else if (ptHat > 30. && ptHat <= 50.)
        {
            ptHatWeight = 7.7966624e-08 * 952110;
        }
        else if (ptHat > 50. && ptHat <= 80.)
        {
            ptHat = 1.0016052e-08 * 952554;
        }
        else if (ptHat > 80. && ptHat <= 120.)
        {
            ptHatWeight = 1.3018269e-09 * 996844;
        }
        else if (ptHat > 120. && ptHat <= 170.)
        {
            ptHatWeight = 2.2648493e-10 * 964681;
        }
        else if (ptHat > 170. && ptHat <= 220.)
        {
            ptHatWeight = 4.0879112e-11 * 999260;
        }
        else if (ptHat > 220. && ptHat <= 280.)
        {
            ptHatWeight = 1.1898939e-11 * 964336;
        }
        else if (ptHat > 280. && ptHat <= 370.)
        {
            ptHatWeight = 3.3364433e-12 * 995036;
        }
        else if (ptHat > 370. && ptHat <= 460.)
        {
            ptHatWeight = 7.6612402e-13 * 958160;
        }
        else if (ptHat > 460. && ptHat <= 540.)
        {
            ptHatWeight = 2.1341026e-13 * 981427;
        }
        else if (ptHat > 540.)
        {
            ptHatWeight = 7.9191586e-14 * 1000000;
        }
        ptHatWeight /= fNEventsInSample;
    }
    else if (isMC && !ispPb)
    {
        ptHatWeight = event->ptHatWeight();
    }

    eventWeight = ptHatWeight * vzWeight;

    return eventWeight;
}

void DiJetAnalysis::processEvent(const Event *event)
{
    if (fVerbose)
    {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "================Processing Events==================" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    fEventCounter++;
    if (fEventCounter >= 50000)
    {
        fCycleCounter++;
        std::cout << Form("DiJetAnalysis::processEvent [INFO] Events processed: %d out of %i. Processed Sample fraction: %3.2f%%",
                          fCycleCounter * 50000, fNEventsInSample, (Double_t)(fCycleCounter * 50000) * 100. / fNEventsInSample)
                  << std::endl;
        fEventCounter = {0};
    }

    if (!fHM)
    {
        std::cerr << "Oops ! You are missing something ! It is Histogram Manager." << std::endl;
        return;
    }

    Double_t Event_Weight = EventWeight(fIspPb, fIsMC, event);
    fIsDiJetFound = kFALSE;
    Double_t iMultiplicityBin = FindMultiplicityBin(event->multiplicity());

    fHM->hPtHat->Fill(event->ptHat());
    fHM->hPtHat_W->Fill(event->ptHat(), Event_Weight);

    fHM->hNEventsInMult->Fill(iMultiplicityBin);

    fHM->hHiBin->Fill(event->hiBin());
    fHM->hHiBin_W->Fill(event->hiBin(), Event_Weight);

    fHM->hVz->Fill(event->vz());
    fHM->hVz_W->Fill(event->vz(), Event_Weight);

    // Int_t iRecoMult = RecoMultiplicity(fIspPb, event);
    Int_t iRecoMult = event->multiplicity();
    fHM->hRecoMultiplicity->Fill(iRecoMult, Event_Weight);

    Double_t iCorrectedMult = CorrectedMultiplicity(fIspPb, event);
    fHM->hCorrectedMultiplicity->Fill(iCorrectedMult, Event_Weight);

    Int_t iGenMult = 0;
    Int_t iSubeMult = 0;
    if (fIsMC)
    {
        iGenMult = GenMultiplicity(fIsMC, event);
        fHM->hGenMultiplicity->Fill(iGenMult, Event_Weight);

        // iSubeMult = SubEventMultiplicity(fIsMC, fIspPb, event);
        iSubeMult = GenMultiplicity(fIsMC, event);
        fHM->hSubEventMultiplicity->Fill(iSubeMult, Event_Weight);
    }
    Double_t iMultiplicity;
    if (fMultiplicityType == 0)
    {
        iMultiplicity = (Double_t)iRecoMult;
    }
    else if (fMultiplicityType == 1)
    {
        iMultiplicity = iGenMult;
    }
    else if (fMultiplicityType == 2)
    {
        iMultiplicity = iCorrectedMult;
    }
    else if (fMultiplicityType == 3)
    {
        if (fIspPb)
        {
            iMultiplicity = iGenMult;
        }
        else if (!fIspPb)
        {
            iMultiplicity = iSubeMult;
        }
    }
    Double_t *MultWeight = new Double_t[4];

    if (fUseMultiplicityWeight)
    {
        MultWeight = MultiplicityWeight(fIspPb, iMultiplicity);
    }
    else
    {
        for (Int_t i = 0; i < 4; i++)
        {
            MultWeight[i] = 1.;
        }
    }

    if (fMultiplicityRange[0] < iMultiplicity && iMultiplicity < fMultiplicityRange[1])
    {
        fHM->hSelectedMultiplicity->Fill(iMultiplicity, Event_Weight);
    }

    if (fUseMultiplicityWeight)
    {
        for (Int_t i = 0; i < 4; i++)
        {
            Double_t Multiplicities[5] = {(Double_t)iRecoMult, (Double_t)iGenMult, (Double_t)iCorrectedMult, (Double_t)iSubeMult, (Double_t)i + 1};
            fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight * MultWeight[i]);
        }
    }
    else
    {
        Double_t Multiplicities[5] = {(Double_t)iRecoMult, (Double_t)iGenMult, (Double_t)iCorrectedMult, (Double_t)iSubeMult, iMultiplicityBin};
        fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight);
    }

    // std::cout << "Event Number: " << fEventCounter - 1 << std::endl;
    processRecoJets(event, Event_Weight, MultWeight, iMultiplicityBin);

    if (fIsDiJetFound)
    {
        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 4; i++)
            {
                Double_t Multiplicities[5] = {(Double_t)iRecoMult, (Double_t)iGenMult, (Double_t)iCorrectedMult, (Double_t)iSubeMult, (Double_t)i + 1};
                fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight * MultWeight[i]);
            }
        }
        else
        {
            Double_t Multiplicities[5] = {(Double_t)iRecoMult, (Double_t)iGenMult, (Double_t)iCorrectedMult, (Double_t)iSubeMult, iMultiplicityBin};
            fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight);
        }
    }
}

Double_t DiJetAnalysis::DeltaPhi(const Double_t &phi1, const Double_t &phi2)
{
    Double_t dPhi = phi1 - phi2;
    while (dPhi > TMath::Pi())
    {
        dPhi += -2 * TMath::Pi();
    }
    while (dPhi < -TMath::Pi())
    {
        dPhi += 2 * TMath::Pi();
    }
    return dPhi;
}

void DiJetAnalysis::processRecoJets(const Event *event, const Double_t &event_Weight, Double_t *multWeight, const Double_t &multiplicityBin)
{
    if (fVerbose)
    {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "================Processing RecoJets==================" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    Float_t leadJetPt = -999.;
    Float_t subLeadJetPt = -999.;
    Float_t leadJetEta = -999.;
    Float_t subLeadJetEta = -999.;
    Float_t leadJetPhi = -999.;
    Float_t subLeadJetPhi = -999.;

    RecoJetIterator recoJetIterator;
    int q = 0;
    for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
    {
        Float_t jetPt = (*recoJetIterator)->ptJECCorr();
        Float_t jetEta = (*recoJetIterator)->eta();
        Float_t jetPhi = (*recoJetIterator)->phi();

        // std::cout << Form("Jet Pt: %f, Jet Eta: %f, Jet Phi: %f", jetPt, jetEta, jetPhi) << std::endl;

        if (jetPt > leadJetPt)
        {
            subLeadJetPt = leadJetPt;
            subLeadJetEta = leadJetEta;
            subLeadJetPhi = leadJetPhi;

            leadJetPt = jetPt;
            leadJetEta = jetEta;
            leadJetPhi = jetPhi;
        }
        else if (jetPt > subLeadJetPt)
        {
            subLeadJetPt = jetPt;
            subLeadJetEta = jetEta;
            subLeadJetPhi = jetPhi;
        }

        Float_t jetEtaCM = MoveToCMFrame(jetEta);
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t JetQuantities[4] = {jetPt, jetEtaCM, jetPhi, (Double_t)i + 1};
                fHM->hRecoJets->Fill(JetQuantities);
                fHM->hRecoJets_W->Fill(JetQuantities, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t JetQuantities[4] = {jetPt, jetEtaCM, jetPhi, multiplicityBin};
            fHM->hRecoJets->Fill(JetQuantities);
            fHM->hRecoJets_W->Fill(JetQuantities, event_Weight);
        }
    }

    Float_t leadJetEtaCM = MoveToCMFrame(leadJetEta);
    Float_t subLeadJetEtaCM = MoveToCMFrame(subLeadJetEta);
    Bool_t isDiJet = CheckDijet(leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM);

    if (isDiJet)
    {
        Double_t deltaPhi = TMath::Abs(DeltaPhi(leadJetPhi, subLeadJetPhi));
        // Double_t deltaPhi1 = TVector2::Phi_mpi_pi((Double_t)(leadJetPhi - subLeadJetPhi));
        Double_t Xj = Asymmetry(leadJetPt, subLeadJetPt);

        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 4; i++)
            {

                Double_t QuenchingQuantities[5] = {Xj, deltaPhi, leadJetPt, subLeadJetPt, (Double_t)i + 1};
                fHM->hRecoQuenching_W->Fill(QuenchingQuantities, event_Weight * multWeight[i]);
                fHM->hNDijetEvent->Fill(1);
            }
        }
        else
        {
            Double_t QuenchingQuantities[5] = {Xj, deltaPhi, leadJetPt, subLeadJetPt, multiplicityBin};
            fHM->hRecoQuenching_W->Fill(QuenchingQuantities, event_Weight);
        }
        if (deltaPhi > fDeltaPhi)
        {
            // std::cout << Form("LeadPt: %f, LeadEta: %f, SubLeadPt: %f, SubLeadEta: %f, DeltaPhi: %f, Xj: %f, Mult: %i", leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM, deltaPhi, Xj, event->multiplicity()) << std::endl;
            // std::cout << Form("LeadPt: %f, LeadEta: %f, LeadPhi: %f, SubLeadPt: %f, SubLeadEta: %f, SubLeadPhi: %f, DeltaPhi: %f, Xj: %f, Mult: %i", leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, deltaPhi, Xj, event->multiplicity()) << std::endl;

            fIsDiJetFound = kTRUE;
            if (fUseMultiplicityWeight)
            {
                for (Int_t i = 0; i < 4; i++)
                {
                    fHM->hDeltaPhi->Fill(deltaPhi, event_Weight * multWeight[i]);
                    fHM->hXj->Fill(Xj, event_Weight * multWeight[i]);
                }
            }
            else
            {
                fHM->hDeltaPhi->Fill(deltaPhi, event_Weight);
                fHM->hXj->Fill(Xj, event_Weight);
            }
            fHM->hNDijetEvent->Fill(1);
        }
    }
    if (fIsDiJetFound)
    {
        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 1; i++)
            {
                Double_t LeadingJetQuantities[4] = {leadJetPt, leadJetEtaCM, leadJetPhi, (Double_t)i + 1};
                Double_t SubLeadingJetQuantities[4] = {subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, (Double_t)i + 1};
                fHM->hLeadingJet->Fill(LeadingJetQuantities, event_Weight * multWeight[i]);
                fHM->hSubLeadingJet->Fill(SubLeadingJetQuantities, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadingJetQuantities[4] = {leadJetPt, leadJetEtaCM, leadJetPhi, multiplicityBin};
            Double_t SubLeadingJetQuantities[4] = {subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
            fHM->hLeadingJet->Fill(LeadingJetQuantities, event_Weight);
            fHM->hSubLeadingJet->Fill(SubLeadingJetQuantities, event_Weight);
        }
    }
}

Double_t DiJetAnalysis::Asymmetry(const Float_t &leadJetPt, const Float_t &subLeadJetPt)
{
    return subLeadJetPt / leadJetPt;
}

Float_t DiJetAnalysis::MoveToCMFrame(const Float_t &jetEta)
{
    Float_t jetEtaCM = jetEta;
    if (fIspPb && fUseCMFrame)
    {
        jetEtaCM = jetEta + fEtaBoost;

        if (fIsMC)
        {
            if (!fIsPbGoing)
            {
                jetEtaCM = -jetEtaCM;
            }
        }
        else if (!fIsMC)
        {
            if (fIsPbGoing)
            {
                jetEtaCM = -jetEtaCM;
            }
        }
    }
    if (fVerbose)
    {
        std::cout << Form("Jet Eta: %f, Jet Eta CM: %f", jetEta, jetEtaCM) << std::endl;
    }

    return jetEtaCM;
}

Double_t DiJetAnalysis::FindMultiplicityBin(const Int_t &multiplicity)
{
    Int_t iBin = 0;
    if (multiplicity <= 60)
    {
        iBin = 1;
    }
    else if (multiplicity > 60 && multiplicity <= 120)
    {
        iBin = 2;
    }
    else if (multiplicity > 120 && multiplicity <= 185)
    {
        iBin = 3;
    }
    else if (multiplicity > 185 && multiplicity <= 250)
    {
        iBin = 4;
    }
    else if (multiplicity > 250 && multiplicity <= 400)
    {
        iBin = 5;
    }
    return (Double_t)iBin;
}

Bool_t DiJetAnalysis::CheckDijet(const Float_t &leadpt, const Float_t &leadeta, const Float_t &subleadpt, const Float_t &subleadeta)
{
    Bool_t isDijetPt = kFALSE;
    if (leadpt > fLeadJetPtLow && subleadpt > fSubLeadJetPtLow)
    {
        if (fVerbose)
        {
            std::cout << Form("DiJet Pt Requirement Satisfied. Leading Jet pt = %f > %f and Sub Leading Jet Pt =  %f > %f", leadpt, fLeadJetPtLow, subleadpt, fSubLeadJetPtLow) << std::endl;
        }
        isDijetPt = kTRUE;
    }
    Bool_t isDijetLeadEta = kFALSE;
    if (leadeta > fLeadJetEtaRange[0] && leadeta < fLeadJetEtaRange[1])
    {
        if (fVerbose)
        {
            std::cout << Form("DiJet Leading Jet Eta Requirement Satisfied. %f < Leading Jet Eta = %f < %f", fLeadJetEtaRange[0], leadeta, fLeadJetEtaRange[1]) << std::endl;
        }
        isDijetLeadEta = kTRUE;
    }
    Bool_t isDijetSubLeadEta = kFALSE;
    if (subleadeta > fSubLeadJetEtaRange[0] && subleadeta < fSubLeadJetEtaRange[1])
    {
        if (fVerbose)
        {
            std::cout << Form("DiJet Subleading Jet Eta Requirement Satisfied. %f < Sub Leading Jet Eta = %f < %f", fSubLeadJetEtaRange[0], subleadeta, fSubLeadJetEtaRange[1]) << std::endl;
        }
        isDijetSubLeadEta = kTRUE;
    }

    return (isDijetPt && isDijetLeadEta && isDijetSubLeadEta);
}

void DiJetAnalysis::report()
{
}

TList *DiJetAnalysis::getOutputList()
{
    TList *outputList = new TList();
    return outputList;
}

void DiJetAnalysis::finish()
{
    std::cout << "DiJetAnalysis::finish [INFO] Finishing the analysis" << std::endl;
}