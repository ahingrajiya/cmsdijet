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

ClassImp(DiJetAnalysis)

    DiJetAnalysis::DiJetAnalysis() :
    BaseAnalysis(), fDebug{kFALSE}, fUseCentralityWeight{kFALSE}, fHM{nullptr}, fIspPb{kFALSE}, fIsMC{kFALSE}, fDeltaPhi{5. * TMath::Pi() / 6.}, fIsPbGoing{kFALSE},
    fUseCMFrame{kFALSE}, fEtaBoost{0.0}, fUseMultiplicityWeight{kFALSE}, fLeadJetPtLow{100.}, fSubLeadJetPtLow{50.}, fNEventsInSample{100000000}, fIsDiJetFound{kFALSE},
    fIsGenDiJetFound{kFALSE}, fVerbose{kFALSE}, fMinTrkPt{0.5}, fTrkEffPbPb{nullptr}, fTrkEffpPb{nullptr}, fTrkEffTable{""}, fEventCounter{0}, fCycleCounter{0},
    fDoInJetMult{kFALSE}, fMultiplicityType{0}, fUseDijetWeight{kFALSE}, fDijetWeightTable{""}, hDijetWeight{nullptr}, fDijetWeightFile{nullptr}, fDijetWeight{1.0},
    fDijetWeightType{"Reco"}, fIspp{kFALSE}, fIsPbPb{kFALSE}, fIsOO{kFALSE}, fCollSystem{""}, fUEType{""}, fDoTrackingClosures{kFALSE}, fVertexZWeight{nullptr},
    fDoVzWeight{kFALSE}, fRecoType{kFALSE}, fRefType{kFALSE}, fGenType{kFALSE}, fMultWeightFunctions{nullptr}, fXBinEdges{}, fYBinEdges{}, fBinContent{}, fXBinCount{0},
    fYBinCount{0}, fInclusiveCorrectedJetPtMin{50.}, fUseHiHFWeight{kFALSE}, fHiHFWeight{nullptr}
{
    fLeadJetEtaRange[0] = {-1.};
    fLeadJetEtaRange[1] = {1.};
    fSubLeadJetEtaRange[0] = {-1.};
    fSubLeadJetEtaRange[1] = {1.};
    fMultiplicityRange[0] = {30.};
    fMultiplicityRange[1] = {50.};
    fTrkEtaRange[0] = {-2.4};
    fTrkEtaRange[1] = {2.4};
    fInclusiveJetEtaRange[0] = {-1.6};
    fInclusiveJetEtaRange[1] = {1.6};
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
        for (auto& weightFunction : fMultWeightFunctions)
        {
            if (weightFunction)
            {
                delete weightFunction;
                weightFunction = nullptr;
            }
        }
    }
    if (fUseDijetWeight)
    {
        fDijetWeightFile->Close();
        delete hDijetWeight;
        hDijetWeight = nullptr;
        fXBinEdges.clear();
        fYBinEdges.clear();
        fBinContent.clear();
    }
    if (fReader)
    {
        delete fReader;
    }
    if (fHiHFWeight)
    {
        delete fHiHFWeight;
        fHiHFWeight = nullptr;
    }
}

void DiJetAnalysis::init()
{
    std::cout << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << "DiJetAnalysis::init  Initializing DiJet Analysis" << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << std::endl;
    report();

    CollSystem(*fReader);

    SetUpTrackingEfficiency(fTrkEffTable);

    if (fUseDijetWeight)
    {
        SetUpDijetWeight(fDijetWeightTable);
    }
    SetUpWeightFunctions();

    std::cout << std::endl;
    std::cout << "DiJetAnalysis::init Initializing Analysis Completed. Exiting DiJetAnalysis::init" << std::endl;
    std::cout << "==================================[Done]================================" << std::endl;
}

void DiJetAnalysis::SetUpWeightFunctions()
{
    std::cout << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << "DiJetAnalysis::Setting up Weight Functions for " << fCollSystem << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Use VertexZ Weights : " << std::boolalpha << fDoVzWeight << std::endl;
    std::cout << "Use Multiplicity Weights : " << std::boolalpha << fUseMultiplicityWeight << std::endl;
    std::cout << "Use HiHF Weights : " << std::boolalpha << fUseHiHFWeight << std::endl;
    if (fIspPb && fIsMC)
    {
        if (fDoVzWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Vertex Z Weight Function" << std::endl;
            fVertexZWeight = new TF1("fVertexZWeight", "pol8", -15.1, 15.1, TF1::EAddToList::kNo);
            fVertexZWeight->SetParameters(0.856516, -0.0159813, 0.00436628, -0.00012862, 2.61129e-05, -4.16965e-07, 1.73711e-08, -3.11953e-09, 6.24993e-10);
        }
        if (fUseMultiplicityWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Multiplicity Weight Functions" << std::endl;
            fMultWeightFunctions[0] = new TF1("fMultWeightFunctions0", "pol2", 10, 60, TF1::EAddToList::kNo);
            fMultWeightFunctions[0]->SetParameters(9.94057e-01, -1.44680e-02, 2.23186e-04);
            fMultWeightFunctions[1] = new TF1("fMultWeightFunctions1", "pol3", 60, 250, TF1::EAddToList::kNo);
            fMultWeightFunctions[1]->SetParameters(-8.19857e-01, 4.86311e-02, -4.12493e-04, 1.12352e-06);
            // fMultWeightFunctions[2] = new TF1("fMultWeightFunctions2", "pol2", 186, 260,
            // TF1::EAddToList::kNo);
            // fMultWeightFunctions[2]->SetParameters(-1.76375e+00, 1.13405e-02, 1.22664e-05);
        }
    }
    if (fIsOO && !fIsMC)
    {
        if (fUseHiHFWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up HiHF Weight Function" << std::endl;
            fHiHFWeight = new TF1("fHiHFWeight", "pol3", 20, 150, TF1::EAddToList::kNo);
            fHiHFWeight->SetParameters(9.03662e+00, -1.76712e-01, 1.18221e-03, -2.68303e-06);
        }
    }
    std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Weight Functions for " << fCollSystem << " completed." << std::endl;
    std::cout << "==================================[Done]================================" << std::endl;
}

void DiJetAnalysis::SetUpDijetWeight(const std::string& dijetWeightTable)
{
    if (!fUseDijetWeight)
    {
        std::cout << "DiJetAnalysis::SetUpDijetWeight Dijet Weighting is not enabled. Skipping setup." << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << "============================================================================================" << std::endl;
    std::cout << "DiJetAnalysis::SetUpDijetWeight Setting up Dijet Weight with DiJet Weight Type : " << fDijetWeightType << std::endl;
    std::cout << "============================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Dijet Weight Table: " << dijetWeightTable << std::endl;
    fDijetWeightFile = TFile::Open(dijetWeightTable.c_str(), "OPEN");
    if (!fDijetWeightFile)
    {
        std::cerr << "Dijet weight table not found" << std::endl;
        return;
    }
    if (fDijetWeightType == "Reco")
    {
        hDijetWeight = (TH2D*)fDijetWeightFile->Get("Reco");
        fRecoType = kTRUE;
    }
    else if (fDijetWeightType == "Ref")
    {
        hDijetWeight = (TH2D*)fDijetWeightFile->Get("Ref");

        fRefType = kTRUE;
    }
    else if (fDijetWeightType == "Gen")
    {
        hDijetWeight = (TH2D*)fDijetWeightFile->Get("Gen");
        fGenType = kTRUE;
    }
    else
    {
        std::cerr << "Dijet weight type is not selected or wrong selection. Please select Dijet "
                     "Weight time from Reco, Ref or Gen"
                  << std::endl;
        std::cerr << "Returning Dijet Weight = 0" << std::endl;
        return;
    }

    if (!hDijetWeight)
    {
        std::cerr << "Dijet weight histogram not found" << std::endl;
        throw std::runtime_error("Dijet weight histogram not found");
    }

    fXBinCount = hDijetWeight->GetNbinsX();
    fYBinCount = hDijetWeight->GetNbinsY();
    std::cout << "Dijet Weight Histogram has " << fXBinCount << " bins in X and " << fYBinCount << " bins in Y" << std::endl;
    fXBinEdges.resize(fXBinCount + 1);
    fYBinEdges.resize(fYBinCount + 1);
    fBinContent.resize(fXBinCount * fYBinCount);
    std::cout << "Dijet Weight Histogram X Axis Edges : " << std::endl;
    std::cout << "\t\t\t\t\t";

    for (Int_t i = 0; i < fXBinCount + 1; i++)
    {
        fXBinEdges[i] = hDijetWeight->GetXaxis()->GetBinLowEdge(i + 1);
        std::cout << fXBinEdges[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "Dijet Weight Histogram Y Axis Edges : " << std::endl;
    std::cout << "\t\t\t\t\t";
    for (Int_t i = 0; i < fYBinCount + 1; i++)
    {
        fYBinEdges[i] = hDijetWeight->GetYaxis()->GetBinLowEdge(i + 1);
        std::cout << fYBinEdges[i] << "  ";
    }
    std::cout << std::endl;
    for (Int_t i = 1; i <= fXBinCount; i++)
    {
        for (Int_t j = 1; j <= fYBinCount; j++)
        {
            fBinContent[(i - 1) * fYBinCount + (j - 1)] = hDijetWeight->GetBinContent(i, j);
        }
    }
    std::cout << "Dijet Weight Table Loaded Successfully" << std::endl;
    std::cout << "==================================[Done]================================" << std::endl;
}

Int_t DiJetAnalysis::BinBinarySearch(const std::vector<double>& binEdges, const double& bin)
{
    Int_t lowBin = 0;
    Int_t highBin = binEdges.size() - 2;

    while (lowBin <= highBin)
    {
        Int_t midBin = (highBin + lowBin) / 2;

        if (bin >= binEdges[midBin] && bin < binEdges[midBin + 1])
        {
            return midBin;  // Found the bin
        }
        else if (bin < binEdges[midBin])
        {
            highBin = midBin - 1;
        }
        else
        {
            lowBin = midBin + 1;
        }
    }
    return -1;
}

void DiJetAnalysis::SetUpTrackingEfficiency(const std::string& trackingEfficiencyTable)
{
    // std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking EfficiencyT Tables"
    // << std::endl;
    if (fIsPbPb)
    {
        std::cout << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking Efficiency "
                     "Tables for PbPb"
                  << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Tracking Efficiency Table: " << trackingEfficiencyTable << std::endl;
        fTrkEffPbPb = new TrkEff2018PbPb("general", "", false, trackingEfficiencyTable);
        std::cout << "Tracking Efficiency Table Loaded Successfully" << std::endl;
        std::cout << "==================================[Done]================================" << std::endl;
    }
    else if (fIspPb)
    {
        std::cout << std::endl;
        std::cout << "===================================================================================" << std::endl;

        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking Efficiency "
                     "Tables for pPb"
                  << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Tracking Efficiency Table: " << trackingEfficiencyTable << std::endl;

        fTrkEffpPb = new TrkEfficiency2016pPb(trackingEfficiencyTable, fUEType);
        std::cout << "Tracking Efficiency Table Loaded Successfully" << std::endl;
        std::cout << "==================================[Done]================================" << std::endl;
    }
    else if (fIspp)
    {
        std::cout << std::endl;
        std::cerr << "Tracking efficiency table not found for pp" << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cerr << "Tracking efficiency table not found for the given system. Please Selected "
                     "from pp, pPb or PbPb collision systems"
                  << std::endl;
    }
}

std::pair<Int_t, Float_t> DiJetAnalysis::RecoCorrectedMultiplicity(const Event* event, const Double_t& eventWeight, const Double_t& multiplicityBin)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::CorrectedMultiplicity Calculating Corrected Multiplicity" << std::endl;
    }
    Float_t iCorrectedMult = 0;
    Int_t iRecoMult = 0;
    TrackIterator recoIterator;
    Float_t iCorrectionFactor = 1.0;
    for (recoIterator = event->trackCollection()->begin(); recoIterator != event->trackCollection()->end(); recoIterator++)
    {
        Double_t trackPt = (*recoIterator)->TrkPt();
        Double_t trackEta = (*recoIterator)->TrkEta();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1]);
        if (fDebug)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1],
                 (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            iRecoMult++;
            if (fIspPb)
            {
                if (!fTrkEffpPb)
                {
                    std::cerr << "Tracking efficiency table not found for pPb" << std::endl;
                    std::cout << "Please Set up Tracking table to calculate corrected multiplicity" << std::endl;
                    std::cout << "Corrected Multiplicity will be returned as -1" << std::endl;
                    iCorrectedMult = -1;
                }
                else
                {
                    iCorrectionFactor = fTrkEffpPb->getCorrection(trackPt, trackEta);
                    iCorrectedMult += iCorrectionFactor;
                    if (fDoTrackingClosures)
                    {
                        fHM->hTrackPtVsEta->Fill(trackEta, trackPt, multiplicityBin);
                        fHM->hTrackPtVsEta_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight);
                        fHM->hTrackPtVsEtaCorrected->Fill(trackEta, trackPt, multiplicityBin, iCorrectionFactor);
                        fHM->hTrackPtVsEtaCorrected_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight * iCorrectionFactor);
                    }
                }
            }
            else if (fIsPbPb)
            {
                if (!fTrkEffPbPb)
                {
                    std::cerr << "Tracking efficiency table not found for PbPb" << std::endl;
                    std::cout << "Please Set up Tracking table to calculate corrected multiplicity" << std::endl;
                    std::cout << "Corrected Multiplicity will be returned as -1" << std::endl;
                    iCorrectedMult = -1;
                }
                else
                {
                    iCorrectionFactor = fTrkEffPbPb->getCorrection(trackPt, trackEta, event->hiBin());
                    iCorrectedMult += iCorrectionFactor;
                    if (fDoTrackingClosures)
                    {
                        fHM->hTrackPtVsEta->Fill(trackEta, trackPt, multiplicityBin);
                        fHM->hTrackPtVsEta_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight);
                        fHM->hTrackPtVsEtaCorrected->Fill(trackEta, trackPt, multiplicityBin, iCorrectionFactor);
                        fHM->hTrackPtVsEtaCorrected_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight * iCorrectionFactor);
                    }
                }
            }
            else if (fIspp)
            {
                iCorrectionFactor = 1.0;
                iCorrectedMult += 1;
                if (fDoTrackingClosures)
                {
                    fHM->hTrackPtVsEta->Fill(trackEta, trackPt, multiplicityBin);
                    fHM->hTrackPtVsEta_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight);
                    fHM->hTrackPtVsEtaCorrected->Fill(trackEta, trackPt, multiplicityBin, iCorrectionFactor);
                    fHM->hTrackPtVsEtaCorrected_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight * iCorrectionFactor);
                }
            }
        }
    }
    if (fDebug)
    {
        std::cout << "Corrected Multiplicity: " << iCorrectedMult << std::endl;
    }
    return {iRecoMult, iCorrectedMult};
}

std::pair<Int_t, Int_t> DiJetAnalysis::GenSubeMultiplicity(const Event* event, const Double_t& eventWeight, const Double_t& multiplicityBin)
{
    if (!fIsMC)
    {
        std::cerr << "This function is only for MC. MC is set to be FALSE." << std::endl;
        return {-1, -1};
    }
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Gen and Subevent Multiplicity" << std::endl;
        if (fIspp)
        {
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for "
                         "PYTHIA. Subevent multiplicity can not be calculated for PYTHIA"
                      << std::endl;
        }
        if (fIspPb)
        {
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for "
                         "PYTHIA+EPOS. \n Subevent multiplicity can not be calculated for PYTHIA + "
                         "EPOS as information is MISSING in the forest"
                      << std::endl;
        }
    }
    Int_t iGenMult = 0;
    Int_t iSubeMult = 0;
    GenTrackIterator genIterator;
    for (genIterator = event->genTrackCollection()->begin(); genIterator != event->genTrackCollection()->end(); genIterator++)
    {
        Double_t trackPt = (*genIterator)->TrkPt();
        Double_t trackEta = (*genIterator)->TrkEta();
        Int_t trackCharge = (*genIterator)->TrkChg();
        Int_t trackSube = (*genIterator)->TrackSube();

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1] && trackCharge != 0);
        if (fDebug)
        {
            Form(
                "%5.2f < Track Pt: %5.2f , %5.2f <= Track Eta: %5.2f <= %5.2f, Track Charge = %i "
                "/= 0 \t %s \n",
                fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackCharge, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            iGenMult++;
            if (fDoTrackingClosures)
            {
                fHM->hGenTrackPtVsEta->Fill(trackEta, trackPt, multiplicityBin);
                fHM->hGenTrackPtVsEta_W->Fill(trackEta, trackPt, multiplicityBin, eventWeight);
            }
            if (fIsPbPb && trackSube > 0)
            {
                iSubeMult++;
            }
        }
    }
    if (fDebug)
    {
        std::cout << Form("Gen Multiplicity  : %i and Subevent Multiplicity : %i", iGenMult, iSubeMult) << std::endl;
    }
    return {iGenMult, iSubeMult};
}

Double_t DiJetAnalysis::MultiplicityWeight(const Double_t& multiplicity)
{
    if (!fIsMC || !fIspPb)
    {
        std::cerr << "This function is only for MC. MC is set to be FALSE." << std::endl;
        return 1.0;
    }

    if (multiplicity < 10)
    {
        if (fDebug)
        {
            std::cerr << "Multiplicity is out of range. Returning 1.0" << std::endl;
        }
        return 1.0;
    }
    else if (multiplicity < 60)
    {
        return fMultWeightFunctions[0]->Eval(multiplicity);
    }
    else if (multiplicity < 250)
    {
        return fMultWeightFunctions[1]->Eval(multiplicity);
    }
    else
    {
        if (fDebug)
        {
            std::cerr << "Multiplicity is out of range. Returning 1.0" << std::endl;
        }
        return 1.0;
    }
}

Float_t DiJetAnalysis::DijetWeight(const Bool_t& ispPb, const Double_t& leadPt, const Double_t& subLeadPt)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::DijetWeight Calculating Dijet Weight" << std::endl;
    }
    if (!fIsMC)
    {
        std::cerr << "Dijet Weight is calculated for MonteCarlo Only. MC is set to be FALSE." << std::endl;
        std::cerr << "Returning Dijet Weight = 0" << std::endl;
        return 0;
    }
    if (fIsMC)
    {
        int xBin = BinBinarySearch(fXBinEdges, subLeadPt);
        int yBin = BinBinarySearch(fYBinEdges, leadPt);
        if (xBin < 0 || yBin < 0)
        {
            if (fDebug)
            {
                std::cout << "Bin Edges Out of Range for Lead Pt: " << leadPt << " and SubLead Pt: " << subLeadPt << std::endl;
                std::cout << "XBins: " << xBin << ", YBins: " << yBin << std::endl;
                std::cout << "Returning Dijet Weight = 1.0" << std::endl;
            }
            return 1.0;
        }
        else
        {
            if (fDebug)
            {
                std::cout << "Dijet Weight : " << fBinContent[xBin * fXBinCount + yBin] << std::endl;
            }
            return fBinContent[xBin * fXBinCount + yBin];
        }
    }
    else
    {
        std::cerr << "Dijet Weight is calculated for MonteCarlo Only. MC is set to be FALSE." << std::endl;
        std::cerr << "Returning Dijet Weight = 1.0" << std::endl;
        return 1.0;
    }
}

Double_t DiJetAnalysis::EventWeight(const Event* event)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::EventWeight Calculating Event Weight" << std::endl;
    }
    if (!fIsMC)
    {
        if (fDebug)
        {
            std::cout << "Event Weight is calculated for MonteCarlo Only. MC is set to be FALSE." << std::endl;
            std::cout << "Returning Event Weight = 1" << std::endl;
        }
        return 1.0;
    }

    Double_t ptHatWeight{1.};
    Double_t eventWeight{1.};
    Double_t vzWeight{1.};
    Double_t ptHat = event->ptHat();
    Double_t vertexZ = event->vz();
    if (ptHat < 0)
    {
        return 1.0;
    }
    if (fIspPb)
    {
        ptHatWeight = pPbptHatWeight(ptHat);
        if (fDoVzWeight)
        {
            vzWeight = fVertexZWeight->Eval(vertexZ);
            vzWeight = 1. / vzWeight;  // Inverse of the vertex Z weight
        }
    }
    else
    {
        ptHatWeight = event->ptHatWeight();
    }

    eventWeight = ptHatWeight * vzWeight;
    if (fDebug)
    {
        std::cout << "PtHat Weight : " << ptHatWeight << std::endl;
        std::cout << "Vz Weight : " << vzWeight << std::endl;
        std::cout << "Event Weight = PtHat Weight * Vz Weight = " << eventWeight << std::endl;
    }

    return eventWeight;
}

Double_t DiJetAnalysis::pPbptHatWeight(const Double_t& pthat)
{
    // Each tuple is {ptHatMin, ptHatMax, factor, eventCount}
    // Magic numbers are (cross section x Nevents generated). These are derived manually and fixed

    const std::vector<std::tuple<double, double, double, double>> ptHatBins = {{15.0, 30.0, 1.0404701e-06, 961104},
                                                                               {30.0, 50.0, 7.7966624e-08, 952110},
                                                                               {50.0, 80.0, 1.0016052e-08, 952554},
                                                                               {80.0, 120.0, 1.3018269e-09, 996844},
                                                                               {120.0, 170.0, 2.2648493e-10, 964681},
                                                                               {170.0, 220.0, 4.0879112e-11, 999260},
                                                                               {220.0, 280.0, 1.1898939e-11, 964336},
                                                                               {280.0, 370.0, 3.3364433e-12, 995036},
                                                                               {370.0, 460.0, 7.6612402e-13, 958160},
                                                                               {460.0, 540.0, 2.1341026e-13, 981427},
                                                                               {540.0, std::numeric_limits<double>::infinity(), 7.9191586e-14, 1000000}};

    for (const auto& [min, max, factor, events] : ptHatBins)
    {
        if (pthat > min && pthat <= max)
        {
            return (factor * events) / fNEventsInSample;
        }
    }

    std::cerr << "PtHat value " << pthat << " is out of range. Returning 1.0" << std::endl;
    return 1.0;  // fallback if ptHat is not in any range
}

Float_t DiJetAnalysis::DijetWeight(const Event* event)
{
    Float_t dijetWeight = 1.0;

    if (fUseDijetWeight)
    {
        Float_t leadJetPt = -999.;
        Float_t subLeadJetPt = -999.;
        Float_t leadJetEta = -999.;
        Float_t subLeadJetEta = -999.;
        Float_t leadJetPhi = -999.;
        Float_t subLeadJetPhi = -999.;
        Float_t matchedLeadRefPt = -999.;
        Float_t matchedSubLeadRefPt = -999.;
        Bool_t recoLeadJetID = kFALSE;
        Bool_t recoSubLeadJetID = kFALSE;
        Bool_t recoDijetPass = kFALSE;

        RecoJetIterator recoJetIterator;
        for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
        {
            Float_t jetPt = (*recoJetIterator)->ptJECCorr();
            Float_t jetEta = (*recoJetIterator)->eta();
            Float_t jetPhi = (*recoJetIterator)->phi();
            Bool_t jetID = (*recoJetIterator)->JetID();
            Float_t jetRefPt = (*recoJetIterator)->RefJetPt();
            if (jetPt > leadJetPt)
            {
                subLeadJetPt = leadJetPt;
                subLeadJetEta = leadJetEta;
                subLeadJetPhi = leadJetPhi;
                recoSubLeadJetID = recoLeadJetID;
                leadJetPt = jetPt;
                leadJetEta = jetEta;
                leadJetPhi = jetPhi;
                recoLeadJetID = jetID;

                matchedSubLeadRefPt = matchedLeadRefPt;
                matchedLeadRefPt = jetRefPt;
            }
            else if (jetPt > subLeadJetPt)
            {
                subLeadJetPt = jetPt;
                subLeadJetEta = jetEta;
                subLeadJetPhi = jetPhi;
                recoSubLeadJetID = jetID;

                matchedSubLeadRefPt = jetRefPt;
            }
        }

        Float_t leadJetEtaCM = MoveToCMFrame(leadJetEta);
        Float_t subLeadJetEtaCM = MoveToCMFrame(subLeadJetEta);
        Bool_t isDiJet = CheckDijet(leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM, recoLeadJetID, recoSubLeadJetID);
        if (isDiJet)
        {
            Double_t deltaPhi = TMath::Abs(DeltaPhi(leadJetPhi, subLeadJetPhi));
            if (deltaPhi > fDeltaPhi)
            {
                recoDijetPass = kTRUE;
                // std::cout << "Reco Lead Jet Pt: " << leadJetPt << " Reco Sub Lead Jet Pt: " <<
                // subLeadJetPt << std::endl;
            }
        }
        if (recoDijetPass)
        {
            if (fRecoType)
            {
                dijetWeight = DijetWeight(fIspPb, leadJetPt, subLeadJetPt);
            }
            else if (fRefType)
            {
                // std::cout << "Ref Lead Jet Pt: " << leadJetPt << " Ref Sub Lead Jet Pt: " <<
                // subLeadJetPt << std::endl;
                if (matchedLeadRefPt < matchedSubLeadRefPt)
                {
                    std::swap(matchedLeadRefPt, matchedSubLeadRefPt);
                }
                dijetWeight = DijetWeight(fIspPb, matchedLeadRefPt, matchedSubLeadRefPt);
            }
            else if (fGenType)
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
                dijetWeight = DijetWeight(fIspPb, leadJetPt, subLeadJetPt);
                // std::cout << "Dijet Weight : " << fDijetWeight << std::endl;
            }
            else
            {
                std::cerr << "Dijet Weight Type is not selected or wrong selection. Please select "
                             "Dijet Weight type from Reco, Ref or Gen"
                          << std::endl;
                std::cerr << "Returning Dijet Weight = 0" << std::endl;
                dijetWeight = 1.0;
            }
        }
    }
    return dijetWeight;
}

void DiJetAnalysis::CollSystem(ForestReader& reader)
{
    ForestReader::CollidingSystemType collSystem = reader.getCollidingSystem();
    {
        std::cout << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << "Setting up collision system from ForestReader::CollidingSystemType" << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << std::endl;
        if (collSystem == ForestReader::CollidingSystemType::pp)
        {
            fIspp = kTRUE;
            fCollSystem = "pp";
            std::cout << "Collision System set to be : pp" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::pPb)
        {
            fIspPb = kTRUE;
            fCollSystem = "pPb";
            std::cout << "Collision System set to be : pPb" << std::endl;
            std::cout << "Using CM Frame for pPb : " << std::boolalpha << fUseCMFrame << std::endl;
            std::cout << "Eta Boost for pPb : " << fEtaBoost << std::endl;
            if (fIsPbGoing)
                std::cout << "Pb going to positive Eta direction" << std::endl;

            else
                std::cout << "Proton going to positive Eta direction" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::PbPb)
        {
            fIsPbPb = kTRUE;
            fCollSystem = "PbPb";
            std::cout << "Collision System set to : PbPb" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::OO)
        {
            fIsOO = kTRUE;
            fCollSystem = "OO";
            std::cout << "Collision System set to be : OO" << std::endl;
        }
        else
        {
            std::cerr << "Invalid collision system. Please choose from pp, pPb, PbPb or OO" << std::endl;
        }
        std::cout << "==================================[Done]================================" << std::endl;
    }
}

Double_t DiJetAnalysis::DeltaPhi(const Double_t& phi1, const Double_t& phi2)
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
    if (fDebug)
    {
        std::cout << Form("Delta Phi: %f", dPhi) << std::endl;
    }
    return dPhi;
}

Double_t DiJetAnalysis::Asymmetry(const Float_t& leadJetPt, const Float_t& subLeadJetPt)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::Asymmetry : " << subLeadJetPt / leadJetPt << std::endl;
    }
    return subLeadJetPt / leadJetPt;
}

Double_t DiJetAnalysis::HiHFWeight(const Double_t& hiHF)
{
    if (!fIsOO) return 1.0;
    if (fHiHFWeight == nullptr)
    {
        return 1.0;
    }
    if (hiHF < 20 || hiHF > 150)
    {
        return 1.0;
    }
    else
    {
        return fHiHFWeight->Eval(hiHF);
    }
}

Float_t DiJetAnalysis::MoveToCMFrame(const Float_t& jetEta)
{
    if (!fIspPb)
    {
        return jetEta;
    }
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
    if (fDebug)
    {
        std::cout << Form("Jet Eta: %f, Jet Eta CM: %f", jetEta, jetEtaCM) << std::endl;
    }

    return jetEtaCM;
}

Float_t DiJetAnalysis::MoveToLabFrame(const Float_t& jetEta)
{
    Float_t jetEtaLab = jetEta;
    if (fIspPb)
    {
        jetEtaLab = jetEta;

        if (fIsMC)
        {
            if (fIsPbGoing)
            {
                jetEtaLab = -jetEtaLab;
            }
        }
        else if (!fIsMC)
        {
            if (!fIsPbGoing)
            {
                jetEtaLab = -jetEtaLab;
            }
        }
    }
    else if (!fIspPb)
    {
        jetEtaLab = jetEta + fEtaBoost;
    }
    if (fDebug)
    {
        std::cout << Form("Jet Eta: %f, Jet Eta Lab: %f", jetEta, jetEtaLab) << std::endl;
    }

    return jetEtaLab;
}

Double_t DiJetAnalysis::FindBin(const double& multiplicity, const std::map<Double_t, Double_t>& fBins)
{
    if (fBins.empty())
    {
        throw std::runtime_error("Error: Bin configuration is empty!");
    }

    if (multiplicity <= fBins.begin()->first) return fBins.begin()->second;

    auto it = fBins.lower_bound(multiplicity);

    if (it == fBins.end() || it->first > multiplicity)
    {
        --it;
    }

    return it->second;
}

Bool_t DiJetAnalysis::CheckDijet(const Float_t& leadpt, const Float_t& leadeta, const Float_t& subleadpt, const Float_t& subleadeta, const Bool_t& leadID,
                                 const Bool_t& subleadID)
{
    Bool_t isDijetPt = kFALSE;
    if (leadpt > fLeadJetPtLow && subleadpt > fSubLeadJetPtLow)
    {
        if (fDebug)
        {
            std::cout << Form(
                             "DiJet Pt Requirement Satisfied. Leading Jet pt = %f > %f and Sub "
                             "Leading Jet Pt =  %f > %f",
                             leadpt, fLeadJetPtLow, subleadpt, fSubLeadJetPtLow)
                      << std::endl;
        }
        isDijetPt = kTRUE;
    }
    Bool_t isDijetLeadEta = kFALSE;
    if (leadeta > fLeadJetEtaRange[0] && leadeta < fLeadJetEtaRange[1])
    {
        if (fDebug)
        {
            std::cout << Form(
                             "DiJet Leading Jet Eta Requirement Satisfied. %f < Leading Jet Eta = "
                             "%f < %f",
                             fLeadJetEtaRange[0], leadeta, fLeadJetEtaRange[1])
                      << std::endl;
        }
        isDijetLeadEta = kTRUE;
    }
    Bool_t isDijetSubLeadEta = kFALSE;
    if (subleadeta > fSubLeadJetEtaRange[0] && subleadeta < fSubLeadJetEtaRange[1])
    {
        if (fDebug)
        {
            std::cout << Form(
                             "DiJet Subleading Jet Eta Requirement Satisfied. %f < Sub Leading Jet "
                             "Eta = %f < %f",
                             fSubLeadJetEtaRange[0], subleadeta, fSubLeadJetEtaRange[1])
                      << std::endl;
        }
        isDijetSubLeadEta = kTRUE;
    }
    Bool_t isDijetID = kFALSE;
    if (leadID && subleadID)
    {
        if (fDebug)
        {
            std::cout << Form("DiJet ID Requirement Satisfied. Lead Jet ID : %i , Sub Lead Jet ID : %i ", leadID, subleadID) << std::endl;
        }
        isDijetID = kTRUE;
    }

    return (isDijetPt && isDijetLeadEta && isDijetSubLeadEta && isDijetID);
}

Int_t DiJetAnalysis::GetDiJetRegion(const Float_t& jetEta)
{
    if (jetEta > -3.3 && jetEta < -1.2)
    {
        return 1;
    }
    else if (jetEta > -1. && jetEta < 1.)
    {
        return 2;
    }
    else if (jetEta > 1.2 && jetEta < 3.3)
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

Float_t DiJetAnalysis::FlipVertexZ(const Float_t& vertexz)
{
    if (fIspPb)
    {
        if (!fIsMC && !fIsPbGoing)
        {
            return (-vertexz);
        }
        else if (fIsMC && fIsPbGoing)
        {
            return (-vertexz);
        }
        else
        {
            return vertexz;
        }
    }
    else
    {
        return vertexz;
    }
}

Double_t DiJetAnalysis::GetJetFlavor(const Int_t& partonFlavor)
{
    if (!fIsMC)
    {
        return 1.0;
    }
    if (partonFlavor == 21)
    {
        return -1.;  // Gluon
    }
    else if (partonFlavor == 0)
    {
        return 0.;  // Quark
    }
    else
    {
        return 1.;  // Undefined
    }
}

void DiJetAnalysis::processEvent(const Event* event)
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
        std::cout << Form(
                         "DiJetAnalysis::processEvent [INFO] Events processed: %d out of %i. "
                         "Processed Sample fraction: %3.2f%%",
                         fCycleCounter * 50000, fNEventsInSample, static_cast<Double_t>(fCycleCounter * 50000) * 100. / fNEventsInSample)
                  << std::endl;
        fEventCounter = {0};
    }
    // std::cout << "Event Counter : " << event->eventNumber() << std::endl;

    if (!fHM)
    {
        throw std::runtime_error("Oops ! You are missing something ! It is Histogram Manager.");
        return;
    }
    Double_t Event_Weight = EventWeight(event);

    if (fUseDijetWeight)
    {
        fDijetWeight = DijetWeight(event);
        fDijetWeight = pow(fDijetWeight, 1.45);  // std::cout << "Dijet Weight : " << fDijetWeight << std::endl;
    }
    else
    {
        fDijetWeight = 1.0;
    }
    // std::cout << "Event Weight : " << Event_Weight << std::endl;
    if (fIspPb && fUseMultiplicityWeight)
    {
        Event_Weight *= MultiplicityWeight(static_cast<Double_t>(event->multiplicity()));
    }
    // std::cout << "Event Weight * MultWeight : " << Event_Weight << std::endl;

    Double_t iMultiplicityBin;
    if (fMultiplicityType != 4)
    {
        iMultiplicityBin = FindBin(static_cast<double>(event->multiplicity()), fMultBins);
    }
    else if (fMultiplicityType == 4)
    {
        iMultiplicityBin = FindBin(static_cast<double>(event->hiBinWithShift()), fMultBins);
    }

    Double_t iVertexZ = event->vz();

    if (fIspPb)
    {
        iVertexZ = FlipVertexZ(iVertexZ);
    }

    // Int_t iRecoMult = RecoMultiplicity(fIspPb, event);
    Int_t iRecoMult = event->multiplicity();
    std::pair<Int_t, Float_t> iRecoCorrectedMult = RecoCorrectedMultiplicity(event, Event_Weight, iMultiplicityBin);
    std::pair<Int_t, Int_t> iGenSubeMult = {0.0, 0.0};
    if (fIsMC)
    {
        iGenSubeMult = GenSubeMultiplicity(event, Event_Weight, iMultiplicityBin);
    }

    Double_t iMultiplicity;
    iMultiplicity = (fMultiplicityType == 0)              ? static_cast<Double_t>(iRecoMult)
                    : (fMultiplicityType == 1)            ? static_cast<Double_t>(iGenSubeMult.first)
                    : (fMultiplicityType == 2)            ? static_cast<Double_t>(iRecoCorrectedMult.second)
                    : (fMultiplicityType == 3)            ? static_cast<Double_t>(fIspPb || fIspp ? iGenSubeMult.first : (fIsPbPb ? iGenSubeMult.second : 0))
                    : (fMultiplicityType == 4 && fIsPbPb) ? static_cast<Double_t>(event->hiBinWithShift())
                                                          : 0;

    if (fIsMC)
    {
        fHM->hPtHat->Fill(event->ptHat());
        fHM->hPtHat_W->Fill(event->ptHat(), Event_Weight);
    }

    fHM->hNEventsInMult->Fill(iMultiplicityBin);
    fHM->hHiBin->Fill(event->hiBinWithShift());
    fHM->hHiBin_W->Fill(event->hiBinWithShift(), Event_Weight);

    fHM->hRecoMultiplicity_W->Fill(iRecoMult, Event_Weight * fDijetWeight);
    fHM->hCorrectedMultiplicity_W->Fill(iRecoCorrectedMult.second, Event_Weight * fDijetWeight);
    if (fIsMC)
    {
        fHM->hGenMultiplicity_W->Fill(iGenSubeMult.first, Event_Weight * fDijetWeight);
        fHM->hSubEventMultiplicity_W->Fill(iGenSubeMult.second, Event_Weight * fDijetWeight);
    }

    if (fMultiplicityRange[0] < iMultiplicity && iMultiplicity < fMultiplicityRange[1])
    {
        fHM->hSelectedMultiplicity_W->Fill(iMultiplicity, Event_Weight * fDijetWeight);
    }

    fIsDiJetFound = kFALSE;
    fIsGenDiJetFound = kFALSE;

    processRecoJets(event, Event_Weight, iMultiplicityBin);

    if (fIsMC)
    {
        processGenJets(event, Event_Weight, iMultiplicityBin);
    }
    // std::cout << "HiHFPlus : " << event->hiHFPlus() << " HiHFMinus : " << event->hiHFMinus() << std::endl;
    // std::cout << "HiHFBins : " << FindBin(event->hiHFPlus(), fHiHFBins) << std::endl;
    // std::cout << "Multiplicity : " << iMultiplicity << " Multiplicity Bins : " << iMultiplicityBin << std::endl;

    fHM->hVz->Fill(iVertexZ);
    fHM->hVz_W->Fill(iVertexZ, Event_Weight * fDijetWeight);

    Double_t Multiplicities[7] = {static_cast<Double_t>(iRecoMult),
                                  static_cast<Double_t>(iGenSubeMult.first),
                                  static_cast<Double_t>(iRecoCorrectedMult.first),
                                  static_cast<Double_t>(iRecoCorrectedMult.second),
                                  static_cast<Double_t>(iGenSubeMult.second),
                                  static_cast<Double_t>(event->hiBinWithShift()),
                                  iMultiplicityBin};
    fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight);
    fHM->hHiHFPlusVsHiHFMinus->Fill(event->hiHFMinus(), event->hiHFPlus());
    fHM->hHiHFPlusVsHiHFMinus_W->Fill(event->hiHFMinus(), event->hiHFPlus(), Event_Weight);
    fHM->hHiHFPlusVsMultiplicity_W->Fill(iMultiplicity, event->hiHFPlus(), Event_Weight);
    fHM->hHiHFMinusVsMultiplicity_W->Fill(iMultiplicity, event->hiHFMinus(), Event_Weight);
    if (fIsDiJetFound)
    {
        fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight);
        fHM->hHiHFPlusVsHiHFMinus_WithDijet_W->Fill(event->hiHFMinus(), event->hiHFPlus(), Event_Weight * HiHFWeight(event->hiHFPlus()));
        fHM->hHiHFPlusVsMultiplicity_WithDijet_W->Fill(iRecoMult, event->hiHFPlus(), Event_Weight);
        fHM->hHiHFMinusVsMultiplicity_WithDijet_W->Fill(iRecoMult, event->hiHFMinus(), Event_Weight);
    }

    processRecoTracks(event, Event_Weight, iMultiplicityBin);
    if (fIsMC)
    {
        processGenTracks(event, Event_Weight, iMultiplicityBin);
    }
}

void DiJetAnalysis::processRecoJets(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin)
{
    if (event->recoJetCollection()->empty())
    {
        if (fVerbose)
        {
            std::cout << "No RecoJets found in the event. Skipping RecoJet processing." << std::endl;
        }
        return;
    }
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
    Bool_t leadJetID = kFALSE;
    Bool_t subLeadJetID = kFALSE;

    RecoJetIterator recoJetIterator;
    TrackIterator recoTrackIterator;

    for (recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
    {
        Float_t jetPt = (*recoJetIterator)->ptJECCorr();
        Float_t jetEta = (*recoJetIterator)->eta();
        Float_t jetPhi = (*recoJetIterator)->phi();
        Bool_t jetID = (*recoJetIterator)->JetID();
        Float_t rawPt = (*recoJetIterator)->pt();

        Float_t refPt;
        Float_t refEta;
        Float_t refPhi;
        if (fIsMC)
        {
            refPt = (*recoJetIterator)->RefJetPt();
            refEta = (*recoJetIterator)->RefJetEta();
            refPhi = (*recoJetIterator)->RefJetPhi();
        }
        // std::cout << Form("Raw Pt: %f, Jet Pt: %f, Jet Eta: %f, Jet Phi: %f", rawPt, jetPt,
        // jetEta, jetPhi) << std::endl;

        if (fIsMC && TMath::Abs(refEta) < 3.0)
        {
            // std::cout << Form("Ref Pt: %f, Ref Eta: %f, Ref Phi: %f", refPt, refEta, refPhi) <<
            // std::endl;

            fHM->hRecoJES_W->Fill(jetPt / refPt, jetPt, multiplicityBin, event_Weight);
            fHM->hRefJES_W->Fill(jetPt / refPt, refPt, multiplicityBin, event_Weight);
            if (refPt > 30.0)
            {
                fHM->hRecoJES_Eta_W->Fill(jetPt / refPt, jetEta, multiplicityBin, event_Weight);
                fHM->hRefJES_Eta_W->Fill(jetPt / refPt, refEta, multiplicityBin, event_Weight);
                if (refPt > 100)
                {
                    fHM->hRecoJES_Eta_Pt100_W->Fill(jetPt / refPt, jetEta, multiplicityBin, event_Weight);
                    fHM->hRefJES_Eta_Pt100_W->Fill(jetPt / refPt, refEta, multiplicityBin, event_Weight);
                }
                if (refPt > 120)
                {
                    fHM->hRefJES_Eta_Pt120_W->Fill(jetPt / refPt, refEta, multiplicityBin, event_Weight);
                    fHM->hRecoJES_Eta_Pt120_W->Fill(jetPt / refPt, jetEta, multiplicityBin, event_Weight);
                }
            }
        }
        if (fIsMC && TMath::Abs(refEta) < 3.0 && refPt > 30)
        {
            Double_t JetFractions[5] = {refPt, refEta, refPhi, static_cast<Double_t>(TMath::Abs((*recoJetIterator)->JetPartonFlavorForB())), multiplicityBin};
            fHM->hJetFlavorFractions_W->Fill(JetFractions, event_Weight);
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
            subLeadJetID = leadJetID;
            leadJetPt = jetPt;
            leadJetEta = jetEta;
            leadJetPhi = jetPhi;
            leadJetID = jetID;
            if (fIsMC)
            {
                subLeadMatchedJetPt = leadMatchedJetPt;
                leadMatchedJetPt = refPt;
            }
        }
        else if (jetPt > subLeadJetPt)
        {
            subLeadJetPt = jetPt;
            subLeadJetEta = jetEta;
            subLeadJetPhi = jetPhi;
            subLeadJetID = jetID;
            if (fIsMC)
            {
                subLeadMatchedJetPt = refPt;
            }
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
        Double_t jetFlavor = GetJetFlavor((*recoJetIterator)->JetPartonFlavorForB());

        Double_t JetQuantities[5] = {jetPt, jetEtaCM, jetPhi, jetFlavor, multiplicityBin};
        Double_t JetQuantitiesLab[5] = {jetPt, jetEta, jetPhi, jetFlavor, multiplicityBin};
        Double_t UnCorrJetQuantities[5] = {rawPt, jetEta, jetPhi, jetFlavor, multiplicityBin};

        fHM->hInclusiveRecoJetsCMFrame->Fill(JetQuantities);
        fHM->hInclusiveRecoJetsCMFrame_W->Fill(JetQuantities, event_Weight);
        if (jetPt > fInclusiveCorrectedJetPtMin && jetEtaCM < fInclusiveJetEtaRange[1] && jetEtaCM > fInclusiveJetEtaRange[0])
        {
            fHM->hSelectedInclusiveRecoJetsMidRapidity_W->Fill(JetQuantities, event_Weight);
        }

        fHM->hInclusiveUncorrectedRecoJets->Fill(UnCorrJetQuantities);
        fHM->hInclusiveUncorrectedRecoJets_W->Fill(UnCorrJetQuantities, event_Weight);
        fHM->hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Fill(jetEtaCM, rawPt, event_Weight);
        fHM->hInclusiveRecoJetPtVsEtaCMFrame_W->Fill(jetEtaCM, jetPt, event_Weight);
        if (fIspPb)
        {
            fHM->hInclusiveRecoJetsLabFrame->Fill(JetQuantitiesLab);
            fHM->hInclusiveRecoJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight);
            fHM->hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Fill(jetEta, rawPt, event_Weight);
            fHM->hInclusiveRecoJetPtVsEtaLabFrame_W->Fill(jetEta, jetPt, event_Weight);
        }

        if (fIsMC)
        {
            Double_t RefJetQuantities[5] = {refPt, MoveToCMFrame(refEta), refPhi, jetFlavor, multiplicityBin};
            Double_t RefJetQuantitiesLab[5] = {refPt, MoveToLabFrame(refEta), refPhi, jetFlavor, multiplicityBin};

            fHM->hInclusiveRefJetsCMFrame->Fill(RefJetQuantities);
            fHM->hInclusiveRefJetsCMFrame_W->Fill(RefJetQuantities, event_Weight);
            if (fIspPb)
            {
                fHM->hInclusiveRefJetsLabFrame->Fill(RefJetQuantitiesLab);
                fHM->hInclusiveRefJetsLabFrame_W->Fill(RefJetQuantitiesLab, event_Weight);
            }
            if (refPt > fInclusiveCorrectedJetPtMin && refEta < fInclusiveJetEtaRange[1] && refEta > fInclusiveJetEtaRange[0])
            {
                fHM->hSelectedInclusiveRefJetsMidRapidity_W->Fill(RefJetQuantities, event_Weight);
            }
        }
    }

    Float_t leadJetEtaCM = MoveToCMFrame(leadJetEta);
    Float_t subLeadJetEtaCM = MoveToCMFrame(subLeadJetEta);
    Bool_t isDiJet = CheckDijet(leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM, leadJetID, subLeadJetID);
    if (leadJetPt > fLeadJetPtLow && subLeadJetPt > fSubLeadJetPtLow)
    {
        Double_t LeadSLeadJets[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
        fHM->hLeadSubLeadJets->Fill(LeadSLeadJets);
        fHM->hLeadSubLeadJets_W->Fill(LeadSLeadJets, event_Weight);
        if (fIsMC)
        {
            if (subLeadRefPt < leadRefPt)
            {
                Double_t LeadSLeadRefJets[7] = {leadRefPt,      MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi,
                                                multiplicityBin};
                fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
                fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight);
            }
            else if (subLeadRefPt > leadRefPt)
            {
                Double_t LeadSLeadRefJets[7] = {subLeadRefPt,   MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi,
                                                multiplicityBin};
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
                Double_t LeadSLeadRefJetsMidRapidity[7] = {
                    leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight);
            }
            else if (subLeadRefPt > leadRefPt)
            {
                Double_t LeadSLeadRefJetsMidRapidity[7] = {subLeadRefPt,   MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi,
                                                           multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight);
            }
        }

        Double_t deltaPhi = TMath::Abs(DeltaPhi(leadJetPhi, subLeadJetPhi));
        Double_t Xj = Asymmetry(leadJetPt, subLeadJetPt);

        fHM->hDeltaPhi_W->Fill(deltaPhi, event_Weight);

        Double_t refXj;
        Double_t refDeltaPhi;
        Double_t matchedRefXj;
        if (fIsMC)
        {
            refDeltaPhi = TMath::Abs(DeltaPhi(leadRefPhi, subLeadRefPhi));
            refXj = Asymmetry(leadRefPt, subLeadRefPt);
            matchedRefXj = Asymmetry(leadMatchedJetPt, subLeadMatchedJetPt);
        }

        Double_t QuenchingQuantities[5] = {Xj, deltaPhi, leadJetPt, subLeadJetPt, multiplicityBin};
        fHM->hRecoQuenching_W->Fill(QuenchingQuantities, event_Weight);

        if (deltaPhi > fDeltaPhi)
        {
            // std::cout << "Ref Lead : " << leadRefPt << " Ref SLead : " << subLeadRefPt <<
            // std::endl; std::cout << "Ref Matched Lead : " << leadMatchedJetPt << " Ref Matched
            // SLead :  " << subLeadMatchedJetPt << std::endl; std::cout << "Lead Jet Pt: " <<
            // leadJetPt << " SubLead Jet Pt: " << subLeadJetPt << std::endl; std::cout << "Lead Jet
            // Eta: " << leadJetEtaCM << " SubLead Jet Eta: " << subLeadJetEtaCM << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Lead Jet Pt: " << leadJetPt << " SubLead Jet Pt: " << subLeadJetPt <<
            // std::endl; std::cout << "Lead Jet Eta: " << leadJetEtaCM << " SubLead Jet Eta: " <<
            // subLeadJetEtaCM << std::endl; std::cout << "Lead Jet Phi: " << leadJetPhi << "
            // SubLead Jet Phi: " << subLeadJetPhi << std::endl; std::cout << std::endl;
            fIsDiJetFound = kTRUE;
            fHM->hDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
            fHM->hMultVsXj_W->Fill(Xj, multiplicityBin, event_Weight);
            fHM->hMultVsXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);
            fHM->hMultVsXj_HiHFW->Fill(Xj, multiplicityBin, event_Weight * HiHFWeight(event->hiHFPlus()));
            fHM->hHiHFVsXj_W->Fill(Xj, FindBin(static_cast<double>(event->hiHFPlus()), fHiHFBins), event_Weight);
            fHM->hHiHFVsXj_HiHFW->Fill(Xj, FindBin(static_cast<double>(event->hiHFPlus()), fHiHFBins), event_Weight * HiHFWeight(event->hiHFPlus()));
            if (fIsMC)
            {
                if (refXj > 1.0)
                {
                    refXj = 1. / refXj;
                }
                if (matchedRefXj > 1.0)
                {
                    matchedRefXj = 1. / matchedRefXj;
                }
                fHM->hMultVsRefXj_W->Fill(refXj, multiplicityBin, event_Weight);
                fHM->hMultVsRefXj_DiJetW->Fill(refXj, multiplicityBin, event_Weight * fDijetWeight);
                fHM->hMultVsMatchedRefXj_W->Fill(matchedRefXj, multiplicityBin, event_Weight);
                fHM->hMultVsMatchedRefXj_DiJetW->Fill(matchedRefXj, multiplicityBin, event_Weight * fDijetWeight);
            }

            fHM->hNDijetEvent->Fill(1);
        }
    }

    if (fIsDiJetFound)
    {
        Double_t LeadSLeadJetsWithDijet[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, multiplicityBin};
        fHM->hLeadSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
        fHM->hLeadSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadJetsWithDijet, event_Weight * fDijetWeight);
        if (fIsMC)
        {
            if (subLeadRefPt < leadRefPt)
            {
                Double_t LeadSLeadRefJetsWithDijet[7] = {leadRefPt,      MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi,
                                                         multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_WithDijet_W->Fill(LeadSLeadRefJetsWithDijet, event_Weight);
                fHM->hRefLeadRefSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadRefJetsWithDijet, event_Weight * fDijetWeight);
            }
            else if (subLeadRefPt > leadRefPt)
            {
                Double_t LeadSLeadRefJetsWithDijet[7] = {subLeadRefPt,   MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi,
                                                         multiplicityBin};
                fHM->hRefLeadRefSubLeadJets_WithDijet_W->Fill(LeadSLeadRefJetsWithDijet, event_Weight);
                fHM->hRefLeadRefSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadRefJetsWithDijet, event_Weight * fDijetWeight);
            }
        }

        fHM->hLeadPtvsSubLeadPt_PtHatW->Fill(subLeadJetPt, leadJetPt, event_Weight);
        fHM->hLeadPtvsSubLeadPt_DiJetW->Fill(subLeadJetPt, leadJetPt, event_Weight * fDijetWeight);
        fHM->hVzWithDijet_W->Fill(event->vz(), event_Weight);
        if (fIsMC)
        {
            if (subLeadRefPt > leadRefPt)
            {
                std::swap(leadRefPt, subLeadRefPt);
            }

            if (leadMatchedJetPt < subLeadMatchedJetPt)
            {
                std::swap(leadMatchedJetPt, subLeadMatchedJetPt);
            }
            fHM->hRefLeadPtVsRefSubLeadPtMatched_PtHatW->Fill(subLeadMatchedJetPt, leadMatchedJetPt, event_Weight);
            fHM->hRefLeadPtVsRefSubLeadPtMatched_DiJetW->Fill(subLeadMatchedJetPt, leadMatchedJetPt, event_Weight * fDijetWeight);
            fHM->hRefLeadPtvsRefSubLeadPt_PtHatW->Fill(subLeadRefPt, leadRefPt, event_Weight);
            fHM->hRefLeadPtvsRefSubLeadPt_DiJetW->Fill(subLeadRefPt, leadRefPt, event_Weight * fDijetWeight);
            fHM->hRefLeadRefSubLead_W->Fill(subLeadMatchedJetPt, leadMatchedJetPt, event_Weight);
        }
    }
}

void DiJetAnalysis::processGenJets(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin)
{
    if (event->genJetCollection()->empty())
    {
        if (fVerbose)
        {
            std::cout << "No GenJets found in the event. Skipping GenJet processing." << std::endl;
        }
        return;
    }
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

        if (fDoInJetMult && fSubLeadJetPtLow > fSubLeadJetPtLow)
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
        double_t jetFlavor = 1.0;  // Placeholder for jet flavor in gen jets
        Double_t JetQuantities[5] = {genJetPt, genJetEtaCM, genJetPhi, jetFlavor, multiplicityBin};
        Double_t JetQuantitiesLab[5] = {genJetPt, MoveToLabFrame(genJetEta), genJetPhi, jetFlavor, multiplicityBin};
        fHM->hInclusiveGenJetsCMFrame->Fill(JetQuantities);
        fHM->hInclusiveGenJetsCMFrame_W->Fill(JetQuantities, event_Weight);
        if (fIspPb)
        {
            fHM->hInclusiveGenJetsLabFrame->Fill(JetQuantitiesLab);
            fHM->hInclusiveGenJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight);
        }
        if (genJetPt > fInclusiveCorrectedJetPtMin && genJetEtaCM < fInclusiveJetEtaRange[1] && genJetEtaCM > fInclusiveJetEtaRange[0])
        {
            fHM->hSelectedInclusiveGenJetsMidRapidity_W->Fill(JetQuantities, event_Weight);
        }
    }

    if (fIsDiJetFound)
    {
        // std::cout << "Gen Lead : " << genLeadJetPt << "Gen SLead : " << genSubLeadJetPt <<
        // std::endl; std::cout << std::endl;

        fHM->hGenLeadPtvsGenSubLeadPt_PtHatW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight);
        fHM->hGenLeadPtvsGenSubLeadPt_DiJetW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight * fDijetWeight);
        fHM->hGenLeadGenSubLead_W->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight);
    }

    Float_t genLeadJetEtaCM = MoveToCMFrame(genLeadJetEta);
    Float_t genSubLeadJetEtaCM = MoveToCMFrame(genSubLeadJetEta);
    Bool_t isGenDiJet = CheckDijet(genLeadJetPt, genLeadJetEtaCM, genSubLeadJetPt, genSubLeadJetEtaCM, kTRUE, kTRUE);

    if (genLeadJetPt > fLeadJetPtLow && genSubLeadJetPt > fSubLeadJetPtLow)
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

        Double_t QuenchingQuantities[5] = {Xj, deltaPhi, genLeadJetPt, genSubLeadJetPt, multiplicityBin};
        fHM->hGenQuenching_W->Fill(QuenchingQuantities, event_Weight);

        if (deltaPhi > fDeltaPhi)
        {
            fIsGenDiJetFound = kTRUE;

            fHM->hGenDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
            fHM->hMultVsGenXj_W->Fill(Xj, multiplicityBin, event_Weight);
            fHM->hMultVsGenXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);
            fHM->hNGenDijetEvent->Fill(1);
        }
    }
    if (fIsGenDiJetFound)
    {
        Double_t LeadSLeadJetsWithDijet[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
        fHM->hGenLeadGenSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
        fHM->hGenLeadGenSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadJetsWithDijet, event_Weight * fDijetWeight);
    }
}

void DiJetAnalysis::processRecoTracks(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin)
{
    if (event->trackCollection()->empty())
    {
        if (fVerbose)
        {
            std::cout << "No RecoTracks found in the event. Skipping RecoTrack processing." << std::endl;
        }
        return;
    }

    if (fVerbose)
    {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "================Processing RecoTracks==================" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }
    TrackIterator trackIterator;
    for (trackIterator = event->trackCollection()->begin(); trackIterator != event->trackCollection()->end(); trackIterator++)
    {
        Float_t trackPt = (*trackIterator)->TrkPt();
        Float_t trackEta = (*trackIterator)->TrkEta();
        Float_t trackPhi = (*trackIterator)->TrkPhi();

        Double_t trackQuantities[4] = {trackPt, trackEta, trackPhi, multiplicityBin};

        fHM->hRecoTracks->Fill(trackQuantities);
        fHM->hRecoTracks_W->Fill(trackQuantities, event_Weight);
        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1]);
        if (fDebug)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1],
                 (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            fHM->hRecoTracks_Pt1_W->Fill(trackQuantities, event_Weight);
        }
    }
}

void DiJetAnalysis::processGenTracks(const Event* event, const Double_t& event_Weight, const Double_t& multiplicityBin)
{
    if (event->genTrackCollection()->empty())
    {
        if (fVerbose)
        {
            std::cout << "No GenTracks found in the event. Skipping GenTrack processing." << std::endl;
        }
        return;
    }
    if (fVerbose)
    {
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "================Processing GenTracks==================" << std::endl;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
        std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

    GenTrackIterator genTrackIterator;
    for (genTrackIterator = event->genTrackCollection()->begin(); genTrackIterator != event->genTrackCollection()->end(); genTrackIterator++)
    {
        Double_t trackPt = (*genTrackIterator)->TrkPt();
        Double_t trackEta = (*genTrackIterator)->TrkEta();
        Double_t trackPhi = (*genTrackIterator)->TrkPhi();
        Int_t trackCharge = (*genTrackIterator)->TrkChg();

        Double_t trackQuantities[4] = {trackPt, trackEta, trackPhi, multiplicityBin};
        fHM->hGenTracks->Fill(trackQuantities);
        fHM->hGenTracks_W->Fill(trackQuantities, event_Weight);

        Bool_t isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1] && trackCharge != 0);
        if (fDebug)
        {
            Form(
                "%5.2f < Track Pt: %5.2f , %5.2f <= Track Eta: %5.2f <= %5.2f, Track Charge = %i "
                "/= 0 \t %s \n",
                fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackCharge, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            fHM->hGenTracks_Pt1_W->Fill(trackQuantities, event_Weight);
        }
    }
}

void DiJetAnalysis::report()
{
    TString reportString = "\n===========DiJetAnalysis::Reporting Analysis Setup===============\n";
    reportString += Form("Is MC :                            :  %s \n", (fIsMC) ? "True" : "False");
    reportString += Form("Inclusive Jet Pt Cut               :  %5.2f \n", fInclusiveCorrectedJetPtMin);
    reportString += Form("Inclusive Jet Eta Range            :  %5.2f < eta < %5.2f \n", fInclusiveJetEtaRange[0], fInclusiveJetEtaRange[1]);
    reportString += Form("Leading Jet Pt Cut                 :  %5.2f \n", fLeadJetPtLow);
    reportString += Form("SubLeading Jet Pt Cut              :  %5.2f \n", fSubLeadJetPtLow);
    reportString += Form("Delta Phi Cut                      :  %5.2f \n", fDeltaPhi);
    reportString += Form("Leading Jet Eta Range              :  %5.2f < eta < %5.2f \n", fLeadJetEtaRange[0], fLeadJetEtaRange[1]);
    reportString += Form("SubLeading Jet Eta Range           :  %5.2f < eta < %5.2f \n", fSubLeadJetEtaRange[0], fSubLeadJetEtaRange[1]);
    reportString += Form("Do Dijet Weight                    :  %s \n", (fUseDijetWeight) ? "True" : "False");
    if (fUseDijetWeight)
    {
        reportString += Form("Dijet Weight Type                  :  %s \n", fDijetWeightType.c_str());
    }
    reportString += Form("Min Track Pt Cut                   :  %5.2f \n", fMinTrkPt);
    reportString += Form("Track Eta Range                    :  %5.2f < eta < %5.2f \n", fTrkEtaRange[0], fTrkEtaRange[1]);
    reportString += Form("Do InJet Multiplicity              :  %s \n", (fDoInJetMult) ? "True" : "False");
    reportString += Form("Use Vz Weights                     :  %s \n", (fDoVzWeight) ? "True" : "False");
    reportString += Form("Use Multiplicity Weights           :  %s \n", (fUseMultiplicityWeight) ? "True" : "False");
    reportString += Form("Underlying Event Type              :  %s \n", fUEType.c_str());
    reportString += Form("Do Tracking Closure                :  %s \n", (fDoTrackingClosures) ? "True" : "False");
    reportString += "===============================================================\n";

    std::cout << reportString.Data() << std::endl;

    // if () reportString
}

TList* DiJetAnalysis::getOutputList()
{
    TList* outputList = new TList();
    return outputList;
}

void DiJetAnalysis::finish()
{
    std::cout << "DiJetAnalysis::finish [INFO] Finishing the analysis" << std::endl;
}