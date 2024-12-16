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
                                     fIsMC{kFALSE}, fDeltaPhi{5. * TMath::Pi() / 6.}, fIsPbGoing{kFALSE}, fUseCMFrame{kFALSE},
                                     fEtaBoost{0.0}, fUseMultiplicityWeight{kFALSE}, fLeadJetPtLow{100.}, fSubLeadJetPtLow{50.}, fNEventsInSample{100000000},
                                     fIsDiJetFound{kFALSE}, fIsGenDiJetFound{kFALSE}, fVerbose{kFALSE}, fMinTrkPt{0.5}, fTrkEffPbPb{nullptr}, fTrkEffpPb{nullptr}, fTrkEffTable{""}, fEventCounter{0},
                                     fCycleCounter{0}, fMultWeightTable{""}, fMultiplicityWeight{nullptr}, fMultWeight{nullptr}, fDoInJetMult{kFALSE}, fMultiplicityType{0}, fUseDijetWeight{kFALSE},
                                     fDijetWeightTable{""}, hDijetWeight{nullptr}, fDijetWeightFile{nullptr}, fDijetWeight{1.0}, hDijetWeightRef{nullptr}, hDijetWeightGen{nullptr}, fDijetWeightType{"Reco"}
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
    if (fUseDijetWeight)
    {
        fDijetWeightFile->Close();
        delete hDijetWeight;
        delete hDijetWeightRef;
        delete hDijetWeightGen;
        hDijetWeight = nullptr;
        hDijetWeightRef = nullptr;
        hDijetWeightGen = nullptr;
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

    if (fUseDijetWeight)
    {
        SetUpDijetWeight(fDijetWeightTable);
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

void DiJetAnalysis::SetUpDijetWeight(const std::string &dijetWeightTable)
{
    fDijetWeightFile = TFile::Open(dijetWeightTable.c_str(), "OPEN");
    if (!fDijetWeightFile)
    {
        std::cerr << "Dijet weight table not found" << std::endl;
    }
    else
    {
        hDijetWeight = (TH2D *)fDijetWeightFile->Get("leadptvsubleadpt_map");
        hDijetWeightRef = (TH2D *)fDijetWeightFile->Get("leadrefptvsubleadrefpt_map");
        hDijetWeightGen = (TH2D *)fDijetWeightFile->Get("leadgenptvsubleadgenpt_map");
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
        weight[0] = fMultiplicityWeight[0]->GetBinContent(fMultiplicityWeight[0]->FindBin((Double_t)multiplicity));
        weight[1] = fMultiplicityWeight[1]->GetBinContent(fMultiplicityWeight[1]->FindBin((Double_t)multiplicity));
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

Float_t DiJetAnalysis::DijetWeight(const Bool_t &ispPb, const std::string &type, const Double_t &leadPt, const Double_t &subLeadPt)
{
    Float_t weight = 1.0;
    if (ispPb && fIsMC && type == "Reco")
    {
        weight = hDijetWeight->GetBinContent(hDijetWeight->GetXaxis()->FindBin(subLeadPt), hDijetWeight->GetYaxis()->FindBin(leadPt));
    }
    else if (ispPb && fIsMC && type == "Ref")
    {
        weight = hDijetWeightRef->GetBinContent(hDijetWeightRef->GetXaxis()->FindBin(subLeadPt), hDijetWeightRef->GetYaxis()->FindBin(leadPt));
    }
    if (ispPb && fIsMC && type == "Reco")
    {
        weight = hDijetWeightGen->GetBinContent(hDijetWeightGen->GetXaxis()->FindBin(subLeadPt), hDijetWeightGen->GetYaxis()->FindBin(leadPt));
    }
    if (weight == 0)
    {
        weight = 1.0;
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
    fDijetWeight = 1.0;
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
            ptHatWeight = 1.0016052e-08 * 952554;
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
    if (fUseDijetWeight && fIspPb)
    {
        Float_t leadJetPt = -999.;
        Float_t subLeadJetPt = -999.;
        Float_t leadJetEta = -999.;
        Float_t subLeadJetEta = -999.;
        Float_t leadJetPhi = -999.;
        Float_t subLeadJetPhi = -999.;
        Bool_t recoDijetPass = kFALSE;

        RecoJetIterator recoJetIterator;
        for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
        {
            Float_t jetPt = (*recoJetIterator)->ptJECCorr();
            Float_t jetEta = (*recoJetIterator)->eta();
            Float_t jetPhi = (*recoJetIterator)->phi();
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
        }

        Float_t leadJetEtaCM = MoveToCMFrame(leadJetEta);
        Float_t subLeadJetEtaCM = MoveToCMFrame(subLeadJetEta);
        Bool_t isDiJet = CheckDijet(leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM);
        if (isDiJet)
        {
            Double_t deltaPhi = TMath::Abs(DeltaPhi(leadJetPhi, subLeadJetPhi));
            if (deltaPhi > fDeltaPhi)
            {
                recoDijetPass = kTRUE;
                // std::cout << "Reco Lead Jet Pt: " << leadJetPt << std::endl;
            }
        }
        if (fDijetWeightType == "Reco" && recoDijetPass)
        {
            fDijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
        }
        else if (fDijetWeightType == "Ref" && recoDijetPass)
        {
            leadJetPt = -999.;
            subLeadJetPt = -999.;
            leadJetEta = -999.;
            subLeadJetEta = -999.;
            leadJetPhi = -999.;
            subLeadJetPhi = -999.;
            RecoJetIterator recoJetIterator;
            for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
            {
                Float_t jetPt = (*recoJetIterator)->RefJetPt();
                Float_t jetEta = (*recoJetIterator)->RefJetEta();
                Float_t jetPhi = (*recoJetIterator)->RefJetPhi();

                if (fIsMC)
                {
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
                }
            }
            fDijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
        }
        if (fDijetWeightType == "Gen" && recoDijetPass)
        {
            leadJetPt = -999.;
            subLeadJetPt = -999.;
            leadJetEta = -999.;
            subLeadJetEta = -999.;
            leadJetPhi = -999.;
            subLeadJetPhi = -999.;
            GenJetIterator genJetIterator;
            for (genJetIterator = event->genJetCollection()->begin(); genJetIterator != event->genJetCollection()->end(); genJetIterator++)
            {
                Float_t jetPt = (*genJetIterator)->pt();
                Float_t jetEta = (*genJetIterator)->eta();
                Float_t jetPhi = (*genJetIterator)->phi();

                if (fIsMC)
                {
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
                }
            }

            fDijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
        }
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
    fIsGenDiJetFound = kFALSE;
    Double_t iMultiplicityBin = FindMultiplicityBin(event->multiplicity());

    fHM->hPtHat->Fill(event->ptHat());
    fHM->hPtHat_W->Fill(event->ptHat(), Event_Weight);

    fHM->hNEventsInMult->Fill(iMultiplicityBin);

    fHM->hHiBin->Fill(event->hiBin());
    fHM->hHiBin_W->Fill(event->hiBin(), Event_Weight);

    Double_t iVertexZ = event->vz();
    if (fIspPb && fUseCMFrame && !fIsPbGoing)
    {
        iVertexZ = -iVertexZ;
    }
    fHM->hVz->Fill(iVertexZ);
    fHM->hVz_W->Fill(iVertexZ, Event_Weight * fDijetWeight);

    // Int_t iRecoMult = RecoMultiplicity(fIspPb, event);
    Int_t iRecoMult = event->multiplicity();
    fHM->hRecoMultiplicity_W->Fill(iRecoMult, Event_Weight * fDijetWeight);

    Double_t iCorrectedMult = CorrectedMultiplicity(fIspPb, event);
    fHM->hCorrectedMultiplicity_W->Fill(iCorrectedMult, Event_Weight * fDijetWeight);

    Int_t iGenMult = 0;
    Int_t iSubeMult = 0;
    if (fIsMC)
    {
        iGenMult = GenMultiplicity(fIsMC, event);
        fHM->hGenMultiplicity_W->Fill(iGenMult, Event_Weight * fDijetWeight);

        // iSubeMult = SubEventMultiplicity(fIsMC, fIspPb, event);
        iSubeMult = GenMultiplicity(fIsMC, event);
        fHM->hSubEventMultiplicity_W->Fill(iSubeMult, Event_Weight * fDijetWeight);
    }
    Double_t iMultiplicity;
    if (fMultiplicityType == 0)
    {
        iMultiplicity = (Double_t)iRecoMult;
    }
    else if (fMultiplicityType == 1)
    {
        iMultiplicity = (Double_t)iGenMult;
    }
    else if (fMultiplicityType == 2)
    {
        iMultiplicity = (Double_t)iCorrectedMult;
    }
    else if (fMultiplicityType == 3)
    {
        if (fIspPb)
        {
            iMultiplicity = (Double_t)iGenMult;
        }
        else if (!fIspPb)
        {
            iMultiplicity = (Double_t)iSubeMult;
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
        fHM->hSelectedMultiplicity_W->Fill(iMultiplicity, Event_Weight * fDijetWeight);
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
    processRecoJets(event, Event_Weight, MultWeight, iMultiplicityBin);

    processGenJets(event, Event_Weight, MultWeight, iMultiplicityBin);

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
    Float_t leadRefPt = -999.;
    Float_t subLeadJetPt = -999.;
    Float_t subLeadRefPt = -999.;
    Float_t leadJetEta = -999.;
    Float_t leadRefEta = -999.;
    Float_t subLeadJetEta = -999.;
    Float_t subLeadRefEta = -999.;
    Float_t leadJetPhi = -999.;
    Float_t leadRefPhi = -999.;
    Float_t subLeadJetPhi = -999.;
    Float_t subLeadRefPhi = -999.;
    Float_t leadMatchedJetPt = -999.;
    Float_t subLeadMatchedJetPt = -999.;

    RecoJetIterator recoJetIterator;
    TrackIterator recoTrackIterator;
    for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
    {
        Float_t jetPt = (*recoJetIterator)->ptJECCorr();
        Float_t jetEta = (*recoJetIterator)->eta();
        Float_t jetPhi = (*recoJetIterator)->phi();
        Float_t refPt = (*recoJetIterator)->RefJetPt();
        Float_t refEta = (*recoJetIterator)->RefJetEta();
        Float_t refPhi = (*recoJetIterator)->RefJetPhi();

        // std::cout << Form("Jet Pt: %f, Jet Eta: %f, Jet Phi: %f", jetPt, jetEta, jetPhi) << std::endl;
        // std::cout << Form("Ref Pt: %f, Ref Eta: %f, Ref Phi: %f", refPt, refEta, refPhi) << std::endl;

        if (refPt > 0.0)
        {
            fHM->hRecoJES_W->Fill(refPt / jetPt, jetPt, event_Weight);
            fHM->hRefJES_W->Fill(refPt / jetPt, refPt, event_Weight);
        }

        if (fDoInJetMult && jetPt > fSubLeadJetPtLow)
        {
            Int_t iInJetMult = 0;
            for (recoTrackIterator = event->trackCollection()->begin(); recoTrackIterator != event->trackCollection()->end(); recoTrackIterator++)
            {
                Float_t trackPt = (*recoTrackIterator)->TrkPt();
                Float_t trackEta = (*recoTrackIterator)->TrkEta();
                Float_t trackPhi = (*recoTrackIterator)->TrkPhi();

                Float_t dR = TMath::Sqrt(TMath::Power(jetEta - trackEta, 2) + TMath::Power(DeltaPhi(jetPhi, trackPhi), 2));

                if (dR <= 0.4)
                {
                    iInJetMult++;
                }
            }
            fHM->hInJetMultiplicity_W->Fill(iInJetMult, event->multiplicity(), event_Weight);
        }

        if (jetPt > leadJetPt)
        {
            subLeadJetPt = leadJetPt;
            subLeadJetEta = leadJetEta;
            subLeadJetPhi = leadJetPhi;
            leadJetPt = jetPt;
            leadJetEta = jetEta;
            leadJetPhi = jetPhi;
            subLeadMatchedJetPt = leadMatchedJetPt;
            leadMatchedJetPt = refPt;
        }
        else if (jetPt > subLeadJetPt)
        {
            subLeadJetPt = jetPt;
            subLeadJetEta = jetEta;
            subLeadJetPhi = jetPhi;
            subLeadMatchedJetPt = refPt;
        }

        if (fIsMC)
        {

            if (refPt > leadRefPt)
            {
                subLeadRefPt = leadRefPt;
                subLeadRefEta = leadRefEta;
                subLeadRefPhi = leadRefPhi;

                leadRefEta = refEta;
                leadRefPhi = refPhi;
                leadRefPt = refPt;
            }
            else if (refPt > subLeadRefPt)
            {

                subLeadRefPt = refPt;
                subLeadRefEta = refEta;
                subLeadRefPhi = refPhi;
            }
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

    if (leadJetPt > 100.0 && subLeadJetPt > 50.)
    {
        Double_t LeadSLeadJets[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
        fHM->hLeadSubLeadJets->Fill(LeadSLeadJets);
        fHM->hLeadSubLeadJets_W->Fill(LeadSLeadJets, event_Weight);
        if (fIsMC)
        {
            if (subLeadRefPt < leadRefPt)
            {
                Double_t LeadSLeadRefJets[7] = {leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, multiplicityBin};
                fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
                fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight);
            }
            else if (subLeadRefPt > leadRefPt)
            {
                Double_t LeadSLeadRefJets[7] = {subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, multiplicityBin};
                fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
                fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight);
            }
        }
    }

    if (isDiJet)
    {
        Double_t LeadSLeadJetsMidRapidity[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
        fHM->hLeadSubLeadJets_MidRapidity_W->Fill(LeadSLeadJetsMidRapidity, event_Weight);
        if (fIsMC)
        {
            if (subLeadRefPt < leadRefPt)
            {
                Double_t LeadSLeadRefJetsMidRapidity[7] = {leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight);
            }
            else if (subLeadRefPt > leadRefPt)
            {
                Double_t LeadSLeadRefJetsMidRapidity[7] = {subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight);
            }
        }
        Double_t deltaPhi = TMath::Abs(DeltaPhi(leadJetPhi, subLeadJetPhi));
        Double_t Xj = Asymmetry(leadJetPt, subLeadJetPt);

        fHM->hDeltaPhi_W->Fill(deltaPhi, event_Weight);

        Double_t refXj;
        Double_t refDeltaPhi;
        if (fIsMC)
        {
            refDeltaPhi = TMath::Abs(DeltaPhi(leadRefPhi, subLeadRefPhi));
            refXj = Asymmetry(leadRefPt, subLeadRefPt);
        }

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

            fIsDiJetFound = kTRUE;
            if (fUseMultiplicityWeight)
            {
                for (Int_t i = 0; i < 4; i++)
                {
                    fHM->hDeltaPhi_W->Fill(deltaPhi, event_Weight * multWeight[i]);
                    fHM->hXj_W->Fill(Xj, multiplicityBin, event_Weight * multWeight[i]);
                }
            }
            else
            {
                fHM->hDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
                fHM->hXj_W->Fill(Xj, multiplicityBin, event_Weight);
                fHM->hXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);

                if (fIsMC)
                {
                    fHM->hRefXj_ER_W->Fill(refXj, multiplicityBin, event_Weight);
                    fHM->hRefXj_ER_DiJetW->Fill(refXj, multiplicityBin, event_Weight * fDijetWeight);

                    if (refXj > 1.0)
                    {
                        refXj = 1. / refXj;
                    }
                    fHM->hRefXj_W->Fill(refXj, multiplicityBin, event_Weight);
                    fHM->hRefXj_DiJetW->Fill(refXj, multiplicityBin, event_Weight * fDijetWeight);
                }
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
                fHM->hLeadingJet_W->Fill(LeadingJetQuantities, event_Weight * multWeight[i]);
                fHM->hSubLeadingJet_W->Fill(SubLeadingJetQuantities, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadSLeadJetsWithDijet[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
            fHM->hLeadSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
            if (fIsMC)
            {
                if (subLeadRefPt < leadRefPt)
                {
                    Double_t LeadSLeadRefJetsWithDijet[7] = {leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, multiplicityBin};
                    fHM->hRefLeadRefSubLeadJets_WithDijet_W->Fill(LeadSLeadRefJetsWithDijet, event_Weight);
                }
                else if (subLeadRefPt > leadRefPt)
                {

                    Double_t LeadSLeadRefJetsWithDijet[7] = {subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, multiplicityBin};
                    fHM->hRefLeadRefSubLeadJets_WithDijet_W->Fill(LeadSLeadRefJetsWithDijet, event_Weight);
                }
            }

            Double_t LeadingJetQuantities[4] = {leadJetPt, leadJetEtaCM, leadJetPhi, multiplicityBin};
            Double_t SubLeadingJetQuantities[4] = {subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
            fHM->hLeadingJet_W->Fill(LeadingJetQuantities, event_Weight);
            fHM->hSubLeadingJet_W->Fill(SubLeadingJetQuantities, event_Weight);

            fHM->hLeadPtvsSubLeadPt_PtHatW->Fill(subLeadJetPt, leadJetPt, event_Weight);
            fHM->hLeadPtvsSubLeadPt_DiJetW->Fill(subLeadJetPt, leadJetPt, event_Weight * fDijetWeight);
            fHM->hVzWithDijet_W->Fill(event->vz(), event_Weight);

            if (subLeadRefPt > leadRefPt)
            {
                Double_t tempPt = leadRefPt;
                leadRefPt = subLeadRefPt;
                subLeadRefPt = tempPt;
            }
            Double_t RefLeadingJetQuantities[4] = {leadRefPt, leadRefEta, leadRefPhi, multiplicityBin};
            Double_t RefSubLeadingJetQuantities[4] = {subLeadRefPt, subLeadRefEta, subLeadRefPhi, multiplicityBin};
            fHM->hRefLeadingJet_W->Fill(RefLeadingJetQuantities, event_Weight);
            fHM->hRefSubLeadingJet_W->Fill(RefSubLeadingJetQuantities, event_Weight);

            fHM->hRefLeadPtvsRefSubLeadPt_PtHatW->Fill(subLeadRefPt, leadRefPt, event_Weight);
            fHM->hRefLeadPtvsRefSubLeadPt_DiJetW->Fill(subLeadRefPt, leadRefPt, event_Weight * fDijetWeight);

            if (subLeadMatchedJetPt > leadMatchedJetPt)
            {
                Double_t tempPt = leadMatchedJetPt;
                leadMatchedJetPt = subLeadMatchedJetPt;
                subLeadMatchedJetPt = tempPt;
            }
            fHM->hRefLeadingVsRefSubLeadingMatched_W->Fill(subLeadMatchedJetPt, leadMatchedJetPt, event_Weight);
        }
    }
}

void DiJetAnalysis::processGenJets(const Event *event, const Double_t &event_Weight, Double_t *multWeight, const Double_t &multiplicityBin)
{
    if (fVerbose)
    {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "================Processing GenJets==================" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    Float_t genLeadJetPt = -999.;
    Float_t genSubLeadJetPt = -999.;
    Float_t genLeadJetEta = -999.;
    Float_t genSubLeadJetEta = -999.;
    Float_t genLeadJetPhi = -999.;
    Float_t genSubLeadJetPhi = -999.;

    GenJetIterator genJetIterator;
    GenTrackIterator genTrackIterator;
    for (genJetIterator = event->genJetCollection()->begin(); genJetIterator != event->genJetCollection()->end(); genJetIterator++)
    {
        Float_t genJetPt = (*genJetIterator)->pt();
        Float_t genJetEta = (*genJetIterator)->eta();
        Float_t genJetPhi = (*genJetIterator)->phi();

        if (genJetPt > genLeadJetPt)
        {
            genSubLeadJetPt = genLeadJetPt;
            genSubLeadJetEta = genLeadJetEta;
            genSubLeadJetPhi = genLeadJetPhi;

            genLeadJetPt = genJetPt;
            genLeadJetEta = genJetEta;
            genLeadJetPhi = genJetPhi;
        }
        else if (genJetPt > genSubLeadJetPt)
        {
            genSubLeadJetPt = genJetPt;
            genSubLeadJetEta = genJetEta;
            genSubLeadJetPhi = genJetPhi;
        }

        if (fDoInJetMult && fSubLeadJetPtLow > 50.0)
        {
            Int_t iInJetMult = 0;
            for (genTrackIterator = event->genTrackCollection()->begin(); genTrackIterator != event->genTrackCollection()->end(); genTrackIterator++)
            {
                Float_t trackPt = (*genTrackIterator)->TrkPt();
                Float_t trackEta = (*genTrackIterator)->TrkEta();
                Float_t trackPhi = (*genTrackIterator)->TrkPhi();

                Float_t dR = TMath::Sqrt(TMath::Power(genJetEta - trackEta, 2) + TMath::Power(DeltaPhi(genJetPhi, trackPhi), 2));

                if (dR <= 0.4)
                {
                    iInJetMult++;
                }
            }
            fHM->hGenInJetMultiplicity_W->Fill(iInJetMult, event->multiplicity(), event_Weight);
        }

        Float_t genJetEtaCM = MoveToCMFrame(genJetEta);
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t JetQuantities[4] = {genJetPt, genJetEtaCM, genJetPhi, (Double_t)i + 1};
                fHM->hGenJets->Fill(JetQuantities);
                fHM->hGenJets_W->Fill(JetQuantities, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t JetQuantities[4] = {genJetPt, genJetEtaCM, genJetPhi, multiplicityBin};
            fHM->hGenJets->Fill(JetQuantities);
            fHM->hGenJets_W->Fill(JetQuantities, event_Weight);
        }
    }
    if (fIsDiJetFound)
    {
        fHM->hGenLeadPtvsGenSubLeadPt_PtHatW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight);
        fHM->hGenLeadPtvsGenSubLeadPt_DiJetW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight * fDijetWeight);
    }

    Float_t genLeadJetEtaCM = MoveToCMFrame(genLeadJetEta);
    Float_t genSubLeadJetEtaCM = MoveToCMFrame(genSubLeadJetEta);
    Bool_t isGenDiJet = CheckDijet(genLeadJetPt, genLeadJetEtaCM, genSubLeadJetPt, genSubLeadJetEtaCM);

    if (genLeadJetPt > 100. && genSubLeadJetPt > 50.)
    {
        Double_t LeadSLeadGenJets[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
        fHM->hGenLeadGenSubLeadJets->Fill(LeadSLeadGenJets);
        fHM->hGenLeadGenSubLeadJets_W->Fill(LeadSLeadGenJets, event_Weight);
    }

    if (isGenDiJet)
    {

        Double_t LeadSLeadGenJetsMidRapidity[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
        fHM->hGenLeadGenSubLeadJets_MidRapidity_W->Fill(LeadSLeadGenJetsMidRapidity, event_Weight);
        Double_t deltaPhi = TMath::Abs(DeltaPhi(genLeadJetPhi, genSubLeadJetPhi));
        Double_t Xj = Asymmetry(genLeadJetPt, genSubLeadJetPt);
        fHM->hGenDeltaPhi_W->Fill(deltaPhi, event_Weight);

        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 4; i++)
            {

                Double_t QuenchingQuantities[5] = {Xj, deltaPhi, genLeadJetPt, genSubLeadJetPt, (Double_t)i + 1};
                fHM->hGenQuenching_W->Fill(QuenchingQuantities, event_Weight * multWeight[i]);
                fHM->hNGenDijetEvent->Fill(1);
            }
        }
        else
        {
            Double_t QuenchingQuantities[5] = {Xj, deltaPhi, genLeadJetPt, genSubLeadJetPt, multiplicityBin};
            fHM->hGenQuenching_W->Fill(QuenchingQuantities, event_Weight);
        }
        if (deltaPhi > fDeltaPhi)
        {
            fIsGenDiJetFound = kTRUE;
            if (fUseMultiplicityWeight)
            {
                for (Int_t i = 0; i < 4; i++)
                {
                    fHM->hGenDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight * multWeight[i]);
                    fHM->hGenXj_W->Fill(Xj, multiplicityBin, event_Weight * multWeight[i]);
                }
            }
            else
            {
                fHM->hGenDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
                fHM->hGenXj_W->Fill(Xj, multiplicityBin, event_Weight);
                fHM->hGenXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);
            }
            fHM->hNGenDijetEvent->Fill(1);
        }
    }
    if (fIsGenDiJetFound)
    {
        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 1; i++)
            {
                Double_t LeadingJetQuantities[4] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, (Double_t)i + 1};
                Double_t SubLeadingJetQuantities[4] = {genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, (Double_t)i + 1};
                fHM->hGenLeadingJet_W->Fill(LeadingJetQuantities, event_Weight * multWeight[i]);
                fHM->hGenSubLeadingJet_W->Fill(SubLeadingJetQuantities, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadingJetQuantities[4] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, multiplicityBin};
            Double_t SubLeadingJetQuantities[4] = {genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
            fHM->hGenLeadingJet_W->Fill(LeadingJetQuantities, event_Weight);
            fHM->hGenSubLeadingJet_W->Fill(SubLeadingJetQuantities, event_Weight);
            Double_t LeadSLeadJetsWithDijet[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
            fHM->hGenLeadGenSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
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
            if (fIsPbGoing)
            {
                jetEtaCM = -jetEtaCM;
            }
        }
        else if (!fIsMC)
        {
            if (!fIsPbGoing)
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
    Int_t iBin = -1;
    if (multiplicity <= 10)
    {
        iBin = 0;
    }
    else if (multiplicity > 10 && multiplicity <= 60)
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