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
                                     fIsDiJetFound{kFALSE}, fVerbose{kFALSE}, fMinTrkPt{0.5}, fTrkEffPbPb{nullptr}, fTrkEffpPb{nullptr}, fTrkEffTable{""}, fEventCounter{0}, fCycleCounter{0}
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
        fHM = nullptr;
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
}

void DiJetAnalysis::init()
{
    if (fVerbose)
    {
        std::cout << "DiJetAnalysis::init  Initializing DiJet Analysis" << std::endl;
    }
    SetUpTrackingEfficiency(fIspPb, fTrkEffTable);
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

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta > fTrkEtaRange[0] && trackEta < fTrkEtaRange[1]);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], (isGoodTrack) ? "True" : "False");
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

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta > fTrkEtaRange[0] && trackEta < fTrkEtaRange[1] && trackSube > 0);
        if (fVerbose)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f , Track Sube : %i \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackSube, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
            iSube++;
    }
    return iSube;
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

    Int_t iRecoMult = RecoMultiplicity(fIspPb, event);
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

    if (fMultiplicityRange[0] < iMultiplicity && iMultiplicity < fMultiplicityRange[1])
    {
        fHM->hSelectedMultiplicity->Fill(iMultiplicity, Event_Weight);
    }
}

Double_t DiJetAnalysis::DeltaPhi(const Double_t &phi1, const Double_t &phi2)
{
    Double_t dPhi = phi1 - phi2;
    if (dPhi > TMath::Pi())
    {
        dPhi = dPhi - 2. * TMath::Pi();
    }
    if (dPhi < -TMath::Pi())
    {
        dPhi = dPhi + 2. * TMath::Pi();
    }
    return dPhi;
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
    if (fHM)
    {
        fHM->writeOutput(fIsMC);
    }
}