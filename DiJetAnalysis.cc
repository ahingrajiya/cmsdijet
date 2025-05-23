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
                                     fDijetWeightTable{""}, hDijetWeight{nullptr}, fDijetWeightFile{nullptr}, fDijetWeight{1.0}, hDijetWeightRef{nullptr}, hDijetWeightGen{nullptr}, fDijetWeightType{"Reco"}, fIspp{kFALSE},
                                     fIsPbPb{kFALSE}, fCollSystem{""}, fUEType{""}, fDoTrackingClosures{kFALSE}, fpPbDoMultiplicityWeight{kFALSE}, fpPbMB{nullptr}, fpPbHM185{nullptr}, fspline185{nullptr}
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

    CollSystem(fCollSystem);

    SetUpTrackingEfficiency(fTrkEffTable);

    if (fUseMultiplicityWeight)
    {
        SetUpMultiplicityWeight(fMultWeightTable);
    }

    if (fpPbDoMultiplicityWeight)
    {
        SetUpMultiplicityWeight(fMultWeightTable, fIspPb);
        fpPbHM185 = new TF1("fHM185", "pol2", 185, 250);
        fpPbHM185->SetParameters(-5.31185e+00, 4.90035e-02, -8.71705e-05);
        fpPbMB = new TF1("fpPbMB", "pol4", 10, 185);
        fpPbMB->SetParameters(4.10681e-01, 3.82374e-03, 1.83548e-04, -2.27844e-06, 7.09986e-09);
        std::vector<double> x1 = {12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5, 30.5, 31.5, 32.5, 33.5, 34.5, 35.5, 36.5, 37.5, 38.5, 39.5, 40.5, 41.5, 42.5, 43.5, 44.5, 45.5, 46.5, 47.5, 48.5, 49.5, 50.5, 51.5, 52.5, 53.5, 54.5, 55.5, 56.5, 57.5, 58.5, 59.5, 60.5, 61.5, 62.5, 63.5, 64.5, 65.5, 66.5, 67.5, 68.5, 69.5, 70.5, 71.5, 72.5, 73.5, 74.5, 75.5, 76.5, 77.5, 78.5, 79.5, 80.5, 81.5, 82.5, 83.5, 84.5, 85.5, 86.5, 87.5, 88.5, 89.5, 90.5,
                                  91.5, 92.5, 93.5, 94.5, 95.5, 96.5, 97.5, 98.5, 99.5, 100.5, 101.5, 102.5, 103.5, 104.5, 105.5, 106.5, 107.5, 108.5, 109.5, 110.5, 111.5, 112.5, 113.5, 114.5, 115.5, 116.5, 117.5, 118.5, 119.5, 120.5, 121.5, 122.5, 123.5, 124.5, 125.5, 126.5, 127.5, 128.5, 129.5, 130.5, 131.5, 132.5, 133.5, 134.5, 135.5, 136.5, 137.5, 138.5, 139.5, 140.5, 141.5, 142.5, 143.5, 144.5, 145.5, 146.5, 147.5, 148.5, 149.5, 150.5, 151.5, 152.5, 153.5, 154.5, 155.5, 156.5, 157.5, 158.5, 159.5, 160.5, 161.5, 162.5, 163.5, 164.5, 165.5, 166.5, 167.5, 168.5, 169.5, 170.5, 171.5, 172.5, 173.5, 174.5, 175.5, 176.5, 177.5, 178.5, 179.5, 180.5, 181.5, 182.5, 183.5, 184.5, 185.5};
        std::vector<double> x2 = {0.785847, 1.11451, 2.9408, 0.956928, 0.903779, 0.184655, 0.941057, 1.01679, 0.572852, 0.858763, 0.970438, 0.363189, 0.330191, 0.686312, 0.522916, 0.619957, 0.779684, 0.77957, 0.708047, 0.707212, 0.840598, 0.783719, 0.67695, 0.75951, 0.752226, 0.62439, 0.856421, 0.674807, 0.760667, 0.611473, 0.801838, 0.756362, 0.812917, 0.87311, 0.817537, 0.87715, 0.760274, 0.829252, 0.725228, 0.889491, 0.819133, 0.809543, 0.750314, 0.88836, 0.87386, 0.946595, 0.906635, 0.929295, 0.899732, 0.88066, 0.955414, 0.9611, 0.855805, 0.87731, 0.91231, 0.942627, 0.985865, 0.973595, 0.963955, 0.896738, 0.930332, 1.01861, 0.910319, 0.994171, 0.939226, 1.01476, 1.00643, 1.06414,
                                  1.08069, 1.08287, 1.05135, 1.07035, 1.0267, 1.09152, 1.0712, 1.15492, 1.04679, 1.0661, 0.98994, 1.03941, 1.08256, 1.0039, 1.08708, 1.08303, 1.18413, 1.11922, 1.12263, 1.05683, 1.14685, 1.0697, 1.05888, 1.0111, 1.01032, 1.11791, 1.05392, 1.07378, 1.09766, 1.09196, 0.982468, 0.951398, 0.942924, 1.1066, 1.1391, 1.08528, 1.11649, 1.08408, 0.981395, 0.924843, 0.949008, 0.950872, 1.12204, 0.982796, 1.02534, 1.15567, 0.956297, 1.11618, 1.07165, 1.02482, 0.989294, 1.04214, 0.98642, 1.09231, 0.947318, 1.02259, 0.845876, 1.03996, 0.985341, 1.04476, 1.01518, 1.03616, 1.03334, 1.0152, 0.968115, 1.09645, 1.23663, 1.01934, 1.01453, 1.1305, 0.916963, 1.16796, 0.945794, 1.06894, 1.14167, 1.04576, 1.14347, 1.08493, 1.05247, 0.967752, 1.03084, 1.06475, 1.15961, 1.00651, 1.17418, 0.931205, 0.991397, 1.12812, 1.11935, 1.34352, 1.25928, 1.0574, 1.11926, 1.09296, 1.11885, 1.13512, 1.09893, 1.30236, 0.976742, 1.02147, 1.27068, 1.39491, 1.07141, 1.28213, 1.33463};

        TGraph *g1 = new TGraph(x1.size(), &x1[0], &x2[0]);
        fspline185 = new TSpline3("reweight_spline1", g1);
    }

    if (fUseDijetWeight)
    {
        SetUpDijetWeight(fDijetWeightTable);
    }
}

void DiJetAnalysis::SetUpMultiplicityWeight(const std::string &multWeightTable)
{
    fMultWeight = TFile::Open(multWeightTable.c_str(), "OPEN");
    if (!fMultWeight)
    {
        std::cerr << "Multiplicity weight table not found" << std::endl;
    }
    else
    {
        if (fVerbose)
        {
            std::cout << "DiJetAnalysis::SetUpMultiplicityWeight Setting up Multiplicity Weight" << std::endl;
            std::cout << "Multiplicity Weight Table: " << multWeightTable << std::endl;
        }
        fMultiplicityWeight[0] = (TH1D *)fMultWeight->Get("mult_60_120");
        fMultiplicityWeight[1] = (TH1D *)fMultWeight->Get("mult_120_185");
        // fMultiplicityWeight[2] = (TH1D *)f->Get("mult_185");
        // fMultiplicityWeight[3] = (TH1D *)f->Get("mult_250");
    }
}

void DiJetAnalysis::SetUpMultiplicityWeight(const std::string &multWeightTable, const Bool_t &ispPb)
{
    if (!fIspPb)
    {
        std::cerr << "This function is only for pPb. pPb is set to be FALSE." << std::endl;
        return;
    }
    else
    {
        fMultWeight = TFile::Open(multWeightTable.c_str(), "OPEN");
        if (!fMultWeight)
        {
            std::cerr << "Multiplicity weight table not found" << std::endl;
        }
        else
        {
            if (fVerbose)
            {
                std::cout << "DiJetAnalysis::SetUpMultiplicityWeight Setting up Multiplicity Weight Table for pPb" << std::endl;
                std::cout << "Multiplicity Weight Table: " << multWeightTable << std::endl;
            }
            fMultiplicityWeight[0] = (TH1D *)fMultWeight->Get("pPb_Mult_Weight");
        }
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
        if (fVerbose)
        {
            std::cout << "DiJetAnalysis::SetUpDijetWeight Setting up Dijet Weight" << std::endl;
            std::cout << "Dijet Weight Table: " << dijetWeightTable << std::endl;
        }
        hDijetWeight = (TH2D *)fDijetWeightFile->Get("leadptvsubleadpt_map");
        // hDijetWeightRef = (TH2D *)fDijetWeightFile->Get("leadrefptvsubleadrefpt_map");
        hDijetWeightGen = (TH2D *)fDijetWeightFile->Get("leadgenptvsubleadgenpt_map");
    }
}

void DiJetAnalysis::SetUpTrackingEfficiency(const std::string &trackingEfficiencyTable)
{

    // std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking EfficiencyT Tables" << std::endl;
    if (fIsPbPb)
    {
        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking EfficiencyT Tables for PbPb" << std::endl;
        fTrkEffPbPb = new TrkEff2018PbPb("general", "", false, trackingEfficiencyTable);
    }
    else if (fIspPb)
    {
        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking EfficiencyT Tables for pPb" << std::endl;

        fTrkEffpPb = new TrkEfficiency2016pPb(trackingEfficiencyTable, fUEType);
    }
    else if (fIspp)
    {
        std::cerr << "Tracking efficiency table not found for pp" << std::endl;
    }
    else
    {
        std::cerr << "Tracking efficiency table not found for the given system. Please Selected from pp, pPb or PbPb collision systems" << std::endl;
    }
}

std::pair<Int_t, Float_t> DiJetAnalysis::RecoCorrectedMultiplicity(const Event *event, const Double_t &eventWeight, const Double_t &multiplicityBin)
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
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], (isGoodTrack) ? "True" : "False");
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

std::pair<Int_t, Int_t> DiJetAnalysis::GenSubeMultiplicity(const Event *event, const Double_t &eventWeight, const Double_t &multiplicityBin)
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
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for PYTHIA. Subevent multiplicity can not be calculated for PYTHIA" << std::endl;
        }
        if (fIspPb)
        {
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for PYTHIA+EPOS. \n Subevent multiplicity can not be calculated for PYTHIA + EPOS as information is MISSING in the forest" << std::endl;
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
            Form("%5.2f < Track Pt: %5.2f , %5.2f <= Track Eta: %5.2f <= %5.2f, Track Charge = %i /= 0 \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackCharge, (isGoodTrack) ? "True" : "False");
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

Double_t *DiJetAnalysis::MultiplicityWeight(const Int_t &multiplicity)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::MultiplicityWeight Calculating Multiplicity Weight" << std::endl;
    }

    Double_t *weight = new Double_t[4]{0.0};
    if (fIsMC)
    {
        if (fIsPbPb)
        {
            weight[0] = fMultiplicityWeight[0]->GetBinContent(fMultiplicityWeight[0]->FindBin((Double_t)multiplicity));
            weight[1] = fMultiplicityWeight[1]->GetBinContent(fMultiplicityWeight[1]->FindBin((Double_t)multiplicity));
            // weight[2] = fMultiplicityWeight[2]->GetBinContent(multiplicity);
            // weight[3] = fMultiplicityWeight[3]->GetBinContent(multiplicity);
        }
    }
    else
    {
        weight[0] = 1.;
        weight[1] = 1.;
        weight[2] = 1.;
        weight[3] = 1.;
    }
    if (fDebug)
    {
        std::cout << "Multiplicity Weight : " << weight[0] << " " << weight[1] << " " << weight[2] << " " << weight[3] << std::endl;
    }
    return weight;
}

Double_t DiJetAnalysis::MultiplicityWeight(const Double_t &multiplicity)
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
    else if (multiplicity < 185)
    {
        return fspline185->Eval(multiplicity);
    }
    else if (multiplicity < 250)
    {
        return fpPbHM185->Eval(multiplicity);
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

Float_t DiJetAnalysis::DijetWeight(const Bool_t &ispPb, const std::string &type, const Double_t &leadPt, const Double_t &subLeadPt)
{
    Float_t weight = 1.0;
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::DijetWeight Calculating Dijet Weight" << std::endl;
        std::cout << "Dijet Weight Type : " << type << std::endl;
    }
    if (!fIsMC)
    {
        std::cerr << "Dijet Weight is calculated for MonteCarlo Only. MC is set to be FALSE." << std::endl;
        std::cerr << "Returning Dijet Weight = 0" << std::endl;
        return 0;
    }
    if (fIsMC)
    {

        if (type == "Reco")
        {
            if (hDijetWeight == nullptr)
            {
                std::cerr << "Dijet Weight Type selected is Reco. Dijet Weight Histogram is not found" << std::endl;
                std::cerr << "Returning Dijet Weight = 0" << std::endl;
                return 0;
            }
            else
            {
                weight = hDijetWeight->GetBinContent(hDijetWeight->GetXaxis()->FindBin(subLeadPt), hDijetWeight->GetYaxis()->FindBin(leadPt));
            }
        }
        else if (type == "Ref")
        {
            if (hDijetWeight == nullptr)
            {
                std::cerr << "Dijet Weight Type selected is Ref. Dijet Weight Histogram is not found" << std::endl;
                std::cerr << "Returning Dijet Weight = 0" << std::endl;
                return 0;
            }
            // weight = hDijetWeightRef->GetBinContent(hDijetWeightRef->GetXaxis()->FindBin(subLeadPt), hDijetWeightRef->GetYaxis()->FindBin(leadPt));
        }
        else if (type == "Gen")
        {
            if (hDijetWeight == nullptr)
            {
                std::cerr << "Dijet Weight Type selected is Gen. Dijet Weight Histogram is not found" << std::endl;
                std::cerr << "Returning Dijet Weight = 0" << std::endl;
                return 0;
            }
            else
            {
                weight = hDijetWeightGen->GetBinContent(hDijetWeightGen->GetXaxis()->FindBin(subLeadPt), hDijetWeightGen->GetYaxis()->FindBin(leadPt));
            }
        }
        else
        {
            std::cerr << "Dijet weight type is not selected or wrong selection. Please select Dijet Weight time from Reco, Ref or Gen" << std::endl;
            std::cerr << "Returning Dijet Weight = 0" << std::endl;
        }
    }
    if (fDebug)
    {
        std::cout << "Dijet Weight : " << weight << std::endl;
    }
    if (weight == 0.0)
    {
        return 1.0;
    }
    return weight;
}

Double_t DiJetAnalysis::EventWeight(const Event *event)
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
    }
    else if (fIspp || fIsPbPb)
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

Double_t DiJetAnalysis::pPbptHatWeight(const Double_t &pthat)
{
    // Each tuple is {ptHatMin, ptHatMax, factor, eventCount}
    // Magic numbers are (cross section x Nevents generated). These are derived manually and fixed

    const std::vector<std::tuple<double, double, double, double>> ptHatBins = {
        {15.0, 30.0, 1.0404701e-06, 961104},
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

    for (const auto &[min, max, factor, events] : ptHatBins)
    {
        if (pthat > min && pthat <= max)
        {
            return (factor * events) / fNEventsInSample;
        }
    }

    return 1.0; // fallback if ptHat is not in any range
}

Float_t DiJetAnalysis::DijetWeight(const Event *event)
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
            }
            else if (jetPt > subLeadJetPt)
            {
                subLeadJetPt = jetPt;
                subLeadJetEta = jetEta;
                subLeadJetPhi = jetPhi;
                recoSubLeadJetID = jetID;
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
                // std::cout << "Reco Lead Jet Pt: " << leadJetPt << std::endl;
            }
        }
        if (fDijetWeightType == "Reco" && recoDijetPass)
        {
            dijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
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
            dijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
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
            dijetWeight = DijetWeight(fIspPb, fDijetWeightType, leadJetPt, subLeadJetPt);
            // std::cout << "Dijet Weight2 : " << fDijetWeight << std::endl;
        }
    }
    return dijetWeight;
}

void DiJetAnalysis::CollSystem(const TString &collSystem)
{
    if (fVerbose)
    {
        std::cout << "Setting up collision system : " << collSystem << std::endl;
    }
    if (collSystem == "pp")
    {
        fIspp = kTRUE;
        if (fVerbose)
        {
            std::cout << "Collision System set to : pp" << std::endl;
        }
    }
    else if (collSystem == "pPb")
    {
        fIspPb = kTRUE;
        if (fVerbose)
        {
            std::cout << "Collision System set to : pPb" << std::endl;
        }
    }
    else if (collSystem == "PbPb")
    {
        fIsPbPb = kTRUE;
        if (fVerbose)
        {
            std::cout << "Collision System set to : PbPb" << std::endl;
        }
    }
    else
    {
        std::cerr << "Invalid collision system. Please choose from pp, pPb, PbPb" << std::endl;
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
    if (fDebug)
    {
        std::cout << Form("Delta Phi: %f", dPhi) << std::endl;
    }
    return dPhi;
}

Double_t DiJetAnalysis::Asymmetry(const Float_t &leadJetPt, const Float_t &subLeadJetPt)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::Asymmetry : " << subLeadJetPt / leadJetPt << std::endl;
    }
    return subLeadJetPt / leadJetPt;
}

Float_t DiJetAnalysis::MoveToCMFrame(const Float_t &jetEta)
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

Float_t DiJetAnalysis::MoveToLabFrame(const Float_t &jetEta)
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

Double_t DiJetAnalysis::FindBin(const Int_t &multiplicity)
{
    if (fBins.empty())
    {
        throw std::runtime_error("Error: Bin configuration is empty!");
    }

    if (multiplicity <= fBins.begin()->first)
        return fBins.begin()->second;

    auto it = fBins.lower_bound(multiplicity);

    if (it == fBins.end() || it->first > multiplicity)
    {
        --it;
    }

    return it->second;
}

Bool_t DiJetAnalysis::CheckDijet(const Float_t &leadpt, const Float_t &leadeta, const Float_t &subleadpt, const Float_t &subleadeta, const Bool_t &leadID, const Bool_t &subleadID)
{
    Bool_t isDijetPt = kFALSE;
    if (leadpt > fLeadJetPtLow && subleadpt > fSubLeadJetPtLow)
    {
        if (fDebug)
        {
            std::cout << Form("DiJet Pt Requirement Satisfied. Leading Jet pt = %f > %f and Sub Leading Jet Pt =  %f > %f", leadpt, fLeadJetPtLow, subleadpt, fSubLeadJetPtLow) << std::endl;
        }
        isDijetPt = kTRUE;
    }
    Bool_t isDijetLeadEta = kFALSE;
    if (leadeta > fLeadJetEtaRange[0] && leadeta < fLeadJetEtaRange[1])
    {
        if (fDebug)
        {
            std::cout << Form("DiJet Leading Jet Eta Requirement Satisfied. %f < Leading Jet Eta = %f < %f", fLeadJetEtaRange[0], leadeta, fLeadJetEtaRange[1]) << std::endl;
        }
        isDijetLeadEta = kTRUE;
    }
    Bool_t isDijetSubLeadEta = kFALSE;
    if (subleadeta > fSubLeadJetEtaRange[0] && subleadeta < fSubLeadJetEtaRange[1])
    {
        if (fDebug)
        {
            std::cout << Form("DiJet Subleading Jet Eta Requirement Satisfied. %f < Sub Leading Jet Eta = %f < %f", fSubLeadJetEtaRange[0], subleadeta, fSubLeadJetEtaRange[1]) << std::endl;
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
        // std::cout << "Dijet Weight : " << fDijetWeight << std::endl;
    }
    else
    {
        fDijetWeight = 1.0;
    }
    // std::cout << "Event Weight : " << Event_Weight << std::endl;
    if (fpPbDoMultiplicityWeight && fIspPb)
    {
        Event_Weight *= MultiplicityWeight(static_cast<Double_t>(event->multiplicity()));
    }
    // std::cout << "Event Weight * MultWeight : " << Event_Weight << std::endl;

    Double_t iMultiplicityBin;
    if (fMultiplicityType != 4)
    {
        iMultiplicityBin = FindBin(event->multiplicity());
    }
    else if (fMultiplicityType == 4)
    {
        iMultiplicityBin = FindBin(event->hiBinWithShift());
    }

    Double_t iVertexZ = event->vz();

    if (fIspPb && fUseCMFrame)
    {
        if (!fIsMC && !fIsPbGoing)
        {
            iVertexZ = -iVertexZ;
        }
        else if (fIsMC && fIsPbGoing)
        {
            iVertexZ = -iVertexZ;
        }
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
    iMultiplicity = (fMultiplicityType == 0) ? static_cast<Double_t>(iRecoMult) : (fMultiplicityType == 1)          ? static_cast<Double_t>(iGenSubeMult.first)
                                                                              : (fMultiplicityType == 2)            ? static_cast<Double_t>(iRecoCorrectedMult.second)
                                                                              : (fMultiplicityType == 3)            ? static_cast<Double_t>(fIspPb || fIspp ? iGenSubeMult.first : (fIsPbPb ? iGenSubeMult.second : 0))
                                                                              : (fMultiplicityType == 4 && fIsPbPb) ? static_cast<Double_t>(event->hiBinWithShift())
                                                                                                                    : 0;
    Double_t *MultWeight = new Double_t[4];
    if (fUseMultiplicityWeight && fMultiplicityType != 4)
    {
        MultWeight = MultiplicityWeight(static_cast<Int_t>(iMultiplicity));
    }
    else
    {
        for (Int_t i = 0; i < 4; i++)
        {
            MultWeight[i] = 1.;
        }
    }

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

    processRecoJets(event, Event_Weight, MultWeight, iMultiplicityBin);

    if (fIsMC)
    {
        processGenJets(event, Event_Weight, MultWeight, iMultiplicityBin);
    }

    if (fIsDiJetFound)
    {
        fHM->hVz->Fill(iVertexZ);
        fHM->hVz_W->Fill(iVertexZ, Event_Weight * fDijetWeight);
    }
    if (fUseMultiplicityWeight)
    {
        for (Int_t i = 0; i < 4; i++)
        {
            Double_t Multiplicities[7] = {static_cast<Double_t>(iRecoMult), static_cast<Double_t>(iGenSubeMult.first), static_cast<Double_t>(iRecoCorrectedMult.first), static_cast<Double_t>(iRecoCorrectedMult.second), static_cast<Double_t>(iGenSubeMult.second), static_cast<Double_t>(event->hiBinWithShift()), static_cast<Double_t>(i + 1)};
            fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight * MultWeight[i]);
            if (fIsDiJetFound)
            {
                fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight * MultWeight[i]);
            }
        }
    }
    else
    {
        Double_t Multiplicities[7] = {static_cast<Double_t>(iRecoMult), static_cast<Double_t>(iGenSubeMult.first), static_cast<Double_t>(iRecoCorrectedMult.first), static_cast<Double_t>(iRecoCorrectedMult.second), static_cast<Double_t>(iGenSubeMult.second), static_cast<Double_t>(event->hiBinWithShift()), iMultiplicityBin};
        fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight);
        if (fIsDiJetFound)
        {
            fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight);
        }
    }
    if (fIsDiJetFound && fDoTrackingClosures)
    {
        processRecoTracks(event, Event_Weight, MultWeight, iMultiplicityBin);
        processGenTracks(event, Event_Weight, MultWeight, iMultiplicityBin);
    }
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

        if (fIsMC && TMath::Abs(refEta) < 3.0)
        {
            // std::cout << Form("Raw Pt: %f, Jet Pt: %f, Jet Eta: %f, Jet Phi: %f", rawPt, jetPt, jetEta, jetPhi) << std::endl;
            // std::cout << Form("Ref Pt: %f, Ref Eta: %f, Ref Phi: %f", refPt, refEta, refPhi) << std::endl;

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
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t JetQuantities[4] = {jetPt, jetEtaCM, jetPhi, (Double_t)i + 1};
                Double_t JetQuantitiesLab[4] = {jetPt, MoveToLabFrame(jetEta), jetPhi, (Double_t)i + 1};
                Double_t UnCorrJetQuantities[4] = {rawPt, jetEtaCM, jetPhi, (Double_t)i + 1};
                fHM->hInclusiveRecoJetsCMFrame->Fill(JetQuantities);
                fHM->hInclusiveRecoJetsCMFrame_W->Fill(JetQuantities, event_Weight * multWeight[i]);
                fHM->hInclusiveUncorrectedRecoJets->Fill(UnCorrJetQuantities);
                fHM->hInclusiveUncorrectedRecoJets_W->Fill(UnCorrJetQuantities, event_Weight * multWeight[i]);
                if (jetPt > 50.0 && TMath::Abs(jetEtaCM) < 1.6)
                {
                    fHM->hSelectedInclusiveRecoJetsMidRapidity_W->Fill(JetQuantities, event_Weight * multWeight[i]);
                }
                if (fIspPb)
                {
                    fHM->hInclusiveRecoJetsLabFrame->Fill(JetQuantitiesLab);
                    fHM->hInclusiveRecoJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight * multWeight[i]);
                }
                if (rawPt > 50.)
                {
                    fHM->hInclusiveUnCorrectedRecoPtVsEtaCMFrame_W->Fill(jetEtaCM, rawPt, event_Weight * multWeight[i]);
                    fHM->hInclusiveRecoJetPtVsEtaCMFrame_W->Fill(jetEtaCM, jetPt, event_Weight * multWeight[i]);
                    if (fIspPb)
                    {
                        fHM->hInclusiveRecoJetPtVsEtaLabFrame_W->Fill(MoveToLabFrame(jetEta), jetPt, event_Weight * multWeight[i]);
                        fHM->hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Fill(MoveToLabFrame(jetEta), rawPt, event_Weight * multWeight[i]);
                    }
                }
                if (fIsMC)
                {
                    Double_t RefJetQuantities[4] = {refPt, MoveToCMFrame(refEta), refPhi, (Double_t)i + 1};
                    Double_t RefJetQuantitiesLab[4] = {refPt, MoveToLabFrame(refEta), refPhi, (Double_t)i + 1};

                    fHM->hInclusiveRefJetsCMFrame->Fill(RefJetQuantities);
                    fHM->hInclusiveRefJetsCMFrame_W->Fill(RefJetQuantities, event_Weight * multWeight[i]);
                    if (fIspPb)
                    {
                        fHM->hInclusiveRefJetsLabFrame->Fill(RefJetQuantitiesLab);
                        fHM->hInclusiveRefJetsLabFrame_W->Fill(RefJetQuantitiesLab, event_Weight * multWeight[i]);
                    }
                    if (jetPt > 50.0 && TMath::Abs(jetEtaCM) < 1.6)
                    {
                        fHM->hSelectedInclusiveRefJetsMidRapidity_W->Fill(RefJetQuantities, event_Weight * multWeight[i]);
                    }
                }
            }
        }
        else
        {
            Double_t JetQuantities[4] = {jetPt, jetEtaCM, jetPhi, multiplicityBin};
            Double_t JetQuantitiesLab[4] = {jetPt, MoveToLabFrame(jetEta), jetPhi, multiplicityBin};
            Double_t UnCorrJetQuantities[4] = {rawPt, jetEta, jetPhi, multiplicityBin};

            fHM->hInclusiveRecoJetsCMFrame->Fill(JetQuantities);
            fHM->hInclusiveRecoJetsCMFrame_W->Fill(JetQuantities, event_Weight);
            if (jetPt > 50.0 && TMath::Abs(jetEtaCM) < 1.6)
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
                fHM->hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Fill(MoveToLabFrame(jetEta), rawPt, event_Weight);
                fHM->hInclusiveRecoJetPtVsEtaLabFrame_W->Fill(MoveToLabFrame(jetEta), jetPt, event_Weight);
            }

            if (fIsMC)
            {
                Double_t RefJetQuantities[4] = {refPt, MoveToCMFrame(refEta), refPhi, multiplicityBin};
                Double_t RefJetQuantitiesLab[4] = {refPt, MoveToLabFrame(refEta), refPhi, multiplicityBin};

                fHM->hInclusiveRefJetsCMFrame->Fill(RefJetQuantities);
                fHM->hInclusiveRefJetsCMFrame_W->Fill(RefJetQuantities, event_Weight);
                if (fIspPb)
                {
                    fHM->hInclusiveRefJetsLabFrame->Fill(RefJetQuantitiesLab);
                    fHM->hInclusiveRefJetsLabFrame_W->Fill(RefJetQuantitiesLab, event_Weight);
                }
                if (jetPt > 50.0 && TMath::Abs(jetEtaCM) < 1.6)
                {
                    fHM->hSelectedInclusiveRefJetsMidRapidity_W->Fill(RefJetQuantities, event_Weight);
                }
            }
        }
    }

    Float_t leadJetEtaCM = MoveToCMFrame(leadJetEta);
    Float_t subLeadJetEtaCM = MoveToCMFrame(subLeadJetEta);
    Bool_t isDiJet = CheckDijet(leadJetPt, leadJetEtaCM, subLeadJetPt, subLeadJetEtaCM, leadJetID, subLeadJetID);
    if (leadJetPt > 100.0 && subLeadJetPt > 50.)
    {
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t LeadSLeadJets[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, (Double_t)i + 1};
                fHM->hLeadSubLeadJets->Fill(LeadSLeadJets);
                fHM->hLeadSubLeadJets_W->Fill(LeadSLeadJets, event_Weight * multWeight[i]);
                if (fIsMC)
                {
                    if (subLeadRefPt < leadRefPt)
                    {
                        Double_t LeadSLeadRefJets[7] = {leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, (Double_t)i + 1};
                        fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
                        fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight * multWeight[i]);
                    }
                    else if (subLeadRefPt > leadRefPt)
                    {
                        Double_t LeadSLeadRefJets[7] = {subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, (Double_t)i + 1};
                        fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
                        fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight * multWeight[i]);
                    }
                }
            }
        }
        else
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
    }

    if (isDiJet)
    {
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t LeadSLeadJetsMidRapidity[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, (Double_t)i + 1};
                fHM->hLeadSubLeadJets_MidRapidity_W->Fill(LeadSLeadJetsMidRapidity, event_Weight * multWeight[i]);

                if (fIsMC)
                {
                    if (subLeadRefPt < leadRefPt)
                    {
                        Double_t LeadSLeadRefJetsMidRapidity[7] = {leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, (Double_t)i + 1};
                        fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight * multWeight[i]);
                    }
                    else if (subLeadRefPt > leadRefPt)
                    {
                        Double_t LeadSLeadRefJetsMidRapidity[7] = {subLeadRefPt, MoveToCMFrame(subLeadRefEta), subLeadRefPhi, leadRefPt, MoveToCMFrame(leadRefEta), leadRefPhi, (Double_t)i + 1};
                        fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJetsMidRapidity, event_Weight * multWeight[i]);
                    }
                }
            }
        }
        else
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
            // std::cout << "Ref Lead : " << leadRefPt << "Ref SLead : " << subLeadRefPt << std::endl;
            // std::cout << "Ref Matched Lead : " << leadMatchedJetPt << "Ref Matched SLead :  " << subLeadMatchedJetPt << std::endl;
            // std::cout << "Lead Jet Pt: " << leadJetPt << " SubLead Jet Pt: " << subLeadJetPt << std::endl;
            // std::cout << "Lead Jet Eta: " << leadJetEtaCM << " SubLead Jet Eta: " << subLeadJetEtaCM << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Lead Jet Pt: " << leadJetPt << " SubLead Jet Pt: " << subLeadJetPt << std::endl;
            // std::cout << "Lead Jet Eta: " << leadJetEtaCM << " SubLead Jet Eta: " << subLeadJetEtaCM << std::endl;
            // std::cout << "Lead Jet Phi: " << leadJetPhi << " SubLead Jet Phi: " << subLeadJetPhi << std::endl;

            fIsDiJetFound = kTRUE;
            if (fUseMultiplicityWeight)
            {
                for (Int_t i = 0; i < 4; i++)
                {
                    fHM->hDeltaPhi_W->Fill(deltaPhi, event_Weight * multWeight[i]);
                    fHM->hMultVsXj_W->Fill(Xj, multiplicityBin, event_Weight * multWeight[i]);
                }
            }
            else
            {
                fHM->hDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
                fHM->hMultVsXj_W->Fill(Xj, multiplicityBin, event_Weight);
                fHM->hMultVsXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);

                if (fIsMC)
                {
                    fHM->hMultVsRefXj_ER_W->Fill(refXj, multiplicityBin, event_Weight);
                    fHM->hMultVsRefXj_ER_DiJetW->Fill(refXj, multiplicityBin, event_Weight * fDijetWeight);

                    if (refXj > 1.0)
                    {
                        refXj = 1. / refXj;
                    }
                    fHM->hMultVsRefXj_W->Fill(refXj, multiplicityBin, event_Weight);
                    fHM->hMultVsRefXj_DiJetW->Fill(refXj, multiplicityBin, event_Weight * fDijetWeight);
                }
            }
            fHM->hNDijetEvent->Fill(1);
        }
    }

    if (fIsDiJetFound)
    {
        if (fUseMultiplicityWeight)
        {
            for (Int_t i = 0; i < 4; i++)
            {

                Double_t LeadSLeadJetsWithDijet[7] = {leadJetPt, leadJetEtaCM, leadJetPhi, subLeadJetPt, subLeadJetEtaCM, subLeadJetPhi, (Double_t)i + 1};
                fHM->hLeadSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight * multWeight[i]);
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
        }

        fHM->hLeadPtvsSubLeadPt_PtHatW->Fill(subLeadJetPt, leadJetPt, event_Weight);
        fHM->hLeadPtvsSubLeadPt_DiJetW->Fill(subLeadJetPt, leadJetPt, event_Weight * fDijetWeight);
        fHM->hVzWithDijet_W->Fill(event->vz(), event_Weight);
        if (fIsMC)
        {
            if (subLeadRefPt > leadRefPt)
            {
                Double_t tempPt = leadRefPt;
                leadRefPt = subLeadRefPt;
                subLeadRefPt = tempPt;
            }

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
                Double_t JetQuantitiesLab[4] = {genJetPt, MoveToLabFrame(genJetEta), genJetPhi, (Double_t)i + 1};
                fHM->hInclusiveGenJetsCMFrame->Fill(JetQuantities);
                fHM->hInclusiveGenJetsCMFrame_W->Fill(JetQuantities, event_Weight * multWeight[i]);
                if (fIspPb)
                {
                    fHM->hInclusiveGenJetsLabFrame->Fill(JetQuantitiesLab);
                    fHM->hInclusiveGenJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight * multWeight[i]);
                }
                if (genJetPt > 50.0 && TMath::Abs(genJetEtaCM) < 1.6)
                {
                    fHM->hSelectedInclusiveGenJetsMidRapidity_W->Fill(JetQuantities, event_Weight * multWeight[i]);
                }
            }
        }
        else
        {
            Double_t JetQuantities[4] = {genJetPt, genJetEtaCM, genJetPhi, multiplicityBin};
            Double_t JetQuantitiesLab[4] = {genJetPt, MoveToLabFrame(genJetEta), genJetPhi, multiplicityBin};
            fHM->hInclusiveGenJetsCMFrame->Fill(JetQuantities);
            fHM->hInclusiveGenJetsCMFrame_W->Fill(JetQuantities, event_Weight);
            if (fIspPb)
            {
                fHM->hInclusiveGenJetsLabFrame->Fill(JetQuantitiesLab);
                fHM->hInclusiveGenJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight);
            }
            if (genJetPt > 50.0 && TMath::Abs(genJetEtaCM) < 1.6)
            {
                fHM->hSelectedInclusiveGenJetsMidRapidity_W->Fill(JetQuantities, event_Weight);
            }
        }
    }
    if (fIsDiJetFound)
    {
        // std::cout << "Gen Lead : " << genLeadJetPt << "Gen SLead : " << genSubLeadJetPt << std::endl;
        // std::cout << std::endl;

        fHM->hGenLeadPtvsGenSubLeadPt_PtHatW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight);
        fHM->hGenLeadPtvsGenSubLeadPt_DiJetW->Fill(genSubLeadJetPt, genLeadJetPt, event_Weight * fDijetWeight);
    }

    Float_t genLeadJetEtaCM = MoveToCMFrame(genLeadJetEta);
    Float_t genSubLeadJetEtaCM = MoveToCMFrame(genSubLeadJetEta);
    Bool_t isGenDiJet = CheckDijet(genLeadJetPt, genLeadJetEtaCM, genSubLeadJetPt, genSubLeadJetEtaCM, kTRUE, kTRUE);

    if (genLeadJetPt > 100. && genSubLeadJetPt > 50.)
    {
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t LeadSLeadGenJets[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, (Double_t)i + 1};
                fHM->hGenLeadGenSubLeadJets->Fill(LeadSLeadGenJets);
                fHM->hGenLeadGenSubLeadJets_W->Fill(LeadSLeadGenJets, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadSLeadGenJets[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
            fHM->hGenLeadGenSubLeadJets->Fill(LeadSLeadGenJets);
            fHM->hGenLeadGenSubLeadJets_W->Fill(LeadSLeadGenJets, event_Weight);
        }
    }

    if (isGenDiJet)
    {
        if (fUseMultiplicityWeight)
        {
            for (int i = 0; i < 4; i++)
            {
                Double_t LeadSLeadGenJetsMidRapidity[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, (Double_t)i + 1.};
                fHM->hGenLeadGenSubLeadJets_MidRapidity_W->Fill(LeadSLeadGenJetsMidRapidity, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadSLeadGenJetsMidRapidity[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
            fHM->hGenLeadGenSubLeadJets_MidRapidity_W->Fill(LeadSLeadGenJetsMidRapidity, event_Weight);
        }

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
                    fHM->hMultVsGenXj_W->Fill(Xj, multiplicityBin, event_Weight * multWeight[i]);
                }
            }
            else
            {
                fHM->hGenDeltaPhi_WithDiJet_W->Fill(deltaPhi, event_Weight);
                fHM->hMultVsGenXj_W->Fill(Xj, multiplicityBin, event_Weight);
                fHM->hMultVsGenXj_DiJetW->Fill(Xj, multiplicityBin, event_Weight * fDijetWeight);
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
                Double_t LeadSLeadJetsWithDijet[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, (Double_t)i + 1};
                fHM->hGenLeadGenSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight * multWeight[i]);
            }
        }
        else
        {
            Double_t LeadSLeadJetsWithDijet[7] = {genLeadJetPt, genLeadJetEtaCM, genLeadJetPhi, genSubLeadJetPt, genSubLeadJetEtaCM, genSubLeadJetPhi, multiplicityBin};
            fHM->hGenLeadGenSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
        }
    }
}

void DiJetAnalysis::processRecoTracks(const Event *event, const Double_t &event_Weight, Double_t *multWeight, const Double_t &multiplicityBin)
{
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
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            fHM->hRecoTracks_Pt1_W->Fill(trackQuantities, event_Weight);
        }
    }
}

void DiJetAnalysis::processGenTracks(const Event *event, const Double_t &event_Weight, Double_t *multWeight, const Double_t &multiplicityBin)
{
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
            Form("%5.2f < Track Pt: %5.2f , %5.2f <= Track Eta: %5.2f <= %5.2f, Track Charge = %i /= 0 \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1], trackCharge, (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            fHM->hGenTracks_Pt1_W->Fill(trackQuantities, event_Weight);
        }
    }
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