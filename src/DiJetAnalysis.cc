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
#include "../interface/DiJetAnalysis.h"

ClassImp(DiJetAnalysis)

    namespace
{
    // Universal template to find leading/subleading jets for ANY jet collection
    template <typename JetIterator, typename Extractor>
    DijetInfo FindDijet(JetIterator begin, JetIterator end, Extractor extractKinematics)
    {
        DijetInfo info;
        if (begin == end) return info;

        for (auto it = begin; it != end; ++it)
        {
            // The lambda translates RecoJet or GenJet into our unified struct
            JetKinematics currentJet = extractKinematics(*it);

            if (currentJet.pt > info.lead.pt)
            {
                info.subLead = info.lead;  // Push lead down to sublead
                info.lead = currentJet;    // Assign new lead
            }
            else if (currentJet.pt > info.subLead.pt)
            {
                info.subLead = currentJet;  // Assign new sublead
            }
        }
        return info;
    }
}  // end anonymous namespace

DiJetAnalysis::DiJetAnalysis() : BaseAnalysis()
{
}

DiJetAnalysis::~DiJetAnalysis()
{
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
    std::cout << "Use JetPt Weights : " << std::boolalpha << fUseJetPtWeight << std::endl;
    if (fSystem == CollisionSystem::pPb && fIsMC)
    {
        if (fDoVzWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Vertex Z Weight Function" << std::endl;
            fVertexZWeight = std::make_unique<TF1>("fVertexZWeight", "pol8", -15.1, 15.1, TF1::EAddToList::kNo);
            fVertexZWeight->SetParameters(0.856516, -0.0159813, 0.00436628, -0.00012862, 2.61129e-05, -4.16965e-07, 1.73711e-08, -3.11953e-09, 6.24993e-10);
        }
        if (fUseMultiplicityWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Multiplicity Weight Functions" << std::endl;
            fMultWeightFunctions[0] = std::make_unique<TF1>("fMultWeightFunctions0", "pol2", 10, 60, TF1::EAddToList::kNo);
            fMultWeightFunctions[0]->SetParameters(9.94057e-01, -1.44680e-02, 2.23186e-04);
            fMultWeightFunctions[1] = std::make_unique<TF1>("fMultWeightFunctions1", "pol3", 60, 250, TF1::EAddToList::kNo);
            fMultWeightFunctions[1]->SetParameters(-8.19857e-01, 4.86311e-02, -4.12493e-04, 1.12352e-06);
            // fMultWeightFunctions[2] = new TF1("fMultWeightFunctions2", "pol2", 186, 260,
            // TF1::EAddToList::kNo);
            // fMultWeightFunctions[2]->SetParameters(-1.76375e+00, 1.13405e-02, 1.22664e-05);
        }
    }
    if (fSystem == CollisionSystem::OO)
    {
        if (fUseHiHFWeight && !fIsMC)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up HiHF Weight Function" << std::endl;
            fHiHFWeight = std::make_unique<TF1>("fHiHFWeight", "pol3", 20, 150, TF1::EAddToList::kNo);
            fHiHFWeight->SetParameters(9.03662e+00, -1.76712e-01, 1.18221e-03, -2.68303e-06);
        }
        if (fUseCentralityWeight && fIsMC)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up Centrality Weight Functions" << std::endl;
            fCentWeightFunctions[0] = std::make_unique<TF1>("fCentWeightFunctions0", "pol3", 0, 30, TF1::EAddToList::kNo);
            fCentWeightFunctions[0]->SetParameters(1.19999e+01, 7.01699e-01, -4.39143e-02, 6.78303e-04);
            fCentWeightFunctions[1] = std::make_unique<TF1>("fCentWeightFunctions1", "pol3", 30, 180, TF1::EAddToList::kNo);
            fCentWeightFunctions[1]->SetParameters(2.27178e+01, -4.09285e-01, 2.53942e-03, -5.29161e-06);
        }
    }
    if (fSystem == CollisionSystem::pp)
    {
        if (fIsMC && fUseJetPtWeight)
        {
            std::cout << "DiJetAnalysis::SetUpWeightFunctions Setting up JetPt Weight Functions" << std::endl;
            fJetPtWeight = std::make_unique<TF1>("fJetPtWeight", "pol2", 50, 500, TF1::EAddToList::kNo);
            fJetPtWeight->SetParameters(9.54788e-01, 6.57695e-04);
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
    std::string typeStr = "Unknown";
    if (fWeightType == DijetWeightType::Reco)
        typeStr = "Reco";
    else if (fWeightType == DijetWeightType::Ref)
        typeStr = "Ref";
    else if (fWeightType == DijetWeightType::Gen)
        typeStr = "Gen";
    std::cout << std::endl;
    std::cout << "============================================================================================" << std::endl;
    std::cout << "DiJetAnalysis::SetUpDijetWeight Setting up Dijet Weight with DiJet Weight Type : " << typeStr << std::endl;
    std::cout << "============================================================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Dijet Weight Table: " << dijetWeightTable << std::endl;
    std::unique_ptr<TFile> localWeightFile(TFile::Open(dijetWeightTable.c_str(), "OPEN"));
    if (!localWeightFile || localWeightFile->IsZombie())
    {
        std::cerr << "Dijet weight table not found" << std::endl;
        return;
    }
    TH2D* hDijetWeight = nullptr;
    if (fWeightType == DijetWeightType::Reco)
    {
        hDijetWeight = (TH2D*)localWeightFile->Get("Reco");
    }
    else if (fWeightType == DijetWeightType::Ref)
    {
        hDijetWeight = (TH2D*)localWeightFile->Get("Ref");
    }
    else if (fWeightType == DijetWeightType::Gen)
    {
        hDijetWeight = (TH2D*)localWeightFile->Get("Gen");
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

    for (int i = 0; i < fXBinCount + 1; i++)
    {
        fXBinEdges[i] = hDijetWeight->GetXaxis()->GetBinLowEdge(i + 1);
        std::cout << fXBinEdges[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "Dijet Weight Histogram Y Axis Edges : " << std::endl;
    std::cout << "\t\t\t\t\t";
    for (int i = 0; i < fYBinCount + 1; i++)
    {
        fYBinEdges[i] = hDijetWeight->GetYaxis()->GetBinLowEdge(i + 1);
        std::cout << fYBinEdges[i] << "  ";
    }
    std::cout << std::endl;
    for (int i = 1; i <= fXBinCount; i++)
    {
        for (int j = 1; j <= fYBinCount; j++)
        {
            fBinContent[(i - 1) * fYBinCount + (j - 1)] = hDijetWeight->GetBinContent(i, j);
        }
    }
    std::cout << "Dijet Weight Table Loaded Successfully" << std::endl;
    std::cout << "==================================[Done]================================" << std::endl;
}

int DiJetAnalysis::BinBinarySearch(const std::vector<double>& binEdges, const double& bin)
{
    int lowBin = 0;
    int highBin = binEdges.size() - 2;

    while (lowBin <= highBin)
    {
        int midBin = (highBin + lowBin) / 2;

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

double DiJetAnalysis::uniform01()
{
    return dist_(gen_);
}

float DiJetAnalysis::CalculateDijetWeight(const DijetInfo& recoDijet, const DijetInfo& refDijet, const DijetInfo& genDijet)
{
    if (!fUseDijetWeight) return 1.0f;

    bool recoDijetPass = recoDijet.isValidDijet && recoDijet.deltaPhi > fDeltaPhi;
    if (!recoDijetPass)
    {
        return 1.0f;
    }

    if (fWeightType == DijetWeightType::Reco)
    {
        return getDijetWeight(recoDijet.lead.pt, recoDijet.subLead.pt);
    }
    else if (fWeightType == DijetWeightType::Ref)
    {
        float matchedLead = recoDijet.lead.matchPt;
        float matchedSubLead = recoDijet.subLead.matchPt;

        if (matchedLead < matchedSubLead)
        {
            std::swap(matchedLead, matchedSubLead);
        }
        return getDijetWeight(matchedLead, matchedSubLead);
    }
    else if (fWeightType == DijetWeightType::Gen)
    {
        float weight = getDijetWeight(genDijet.lead.pt, genDijet.subLead.pt);
        if (fSystem == CollisionSystem::pp || fSystem == CollisionSystem::OO)
        {
            // weight *= getWeightMultiplier(genDijet.xj);
            weight = getWeightMultiplier(genDijet.xj);
        }
        return weight;
    }

    return 1.0f;
}

void DiJetAnalysis::SetUpTrackingEfficiency(const std::string& trackingEfficiencyTable)
{
    // std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking EfficiencyT Tables"
    // << std::endl;
    if (fSystem == CollisionSystem::PbPb)
    {
        std::cout << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking Efficiency "
                     "Tables for PbPb"
                  << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Tracking Efficiency Table: " << trackingEfficiencyTable << std::endl;
        fTrkEffPbPb = std::make_unique<TrkEff2018PbPb>("general", "", false, trackingEfficiencyTable);
        std::cout << "Tracking Efficiency Table Loaded Successfully" << std::endl;
        std::cout << "==================================[Done]================================" << std::endl;
    }
    else if (fSystem == CollisionSystem::pPb)
    {
        std::cout << std::endl;
        std::cout << "===================================================================================" << std::endl;

        std::cout << "Dijet Analysis::SetUpTrackingEfficiency Setting up Tracking Efficiency "
                     "Tables for pPb"
                  << std::endl;
        std::cout << "===================================================================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Tracking Efficiency Table: " << trackingEfficiencyTable << std::endl;

        fTrkEffpPb = std::make_unique<TrkEfficiency2016pPb>(trackingEfficiencyTable, fUEType);
        std::cout << "Tracking Efficiency Table Loaded Successfully" << std::endl;
        std::cout << "==================================[Done]================================" << std::endl;
    }
    else if (fSystem == CollisionSystem::pp)
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

std::pair<int, float> DiJetAnalysis::RecoCorrectedMultiplicity(const Event* event, const double& eventWeight, const double& multiplicityBin)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::CorrectedMultiplicity Calculating Corrected Multiplicity" << std::endl;
    }
    float iCorrectedMult = 0;
    int iRecoMult = 0;
    TrackIterator recoIterator;
    float iCorrectionFactor = 1.0;
    for (recoIterator = event->trackCollection()->begin(); recoIterator != event->trackCollection()->end(); recoIterator++)
    {
        double trackPt = (*recoIterator)->TrkPt();
        double trackEta = (*recoIterator)->TrkEta();

        bool isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1]);
        if (fDebug)
        {
            Form("%5.2f < Track Pt: %5.2f , %5.2f < Track Eta: %5.2f < %5,2f \t %s \n", fMinTrkPt, trackPt, fTrkEtaRange[0], trackEta, fTrkEtaRange[1],
                 (isGoodTrack) ? "True" : "False");
        }

        if (isGoodTrack)
        {
            iRecoMult++;
            if (fSystem == CollisionSystem::pPb)
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
            else if (fSystem == CollisionSystem::PbPb)
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
            else if (fSystem == CollisionSystem::pp)
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

std::pair<int, int> DiJetAnalysis::GenSubeMultiplicity(const Event* event, const double& eventWeight, const double& multiplicityBin)
{
    if (!fIsMC)
    {
        std::cerr << "This function is only for MC. MC is set to be FALSE." << std::endl;
        return {-1, -1};
    }
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Gen and Subevent Multiplicity" << std::endl;
        if (fSystem == CollisionSystem::pp)
        {
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for "
                         "PYTHIA. Subevent multiplicity can not be calculated for PYTHIA"
                      << std::endl;
        }
        if (fSystem == CollisionSystem::pPb)
        {
            std::cout << "DiJetAnalysis::GenSubeMultiplicity Calculating Only Gen Multiplicity for "
                         "PYTHIA+EPOS. \n Subevent multiplicity can not be calculated for PYTHIA + "
                         "EPOS as information is MISSING in the forest"
                      << std::endl;
        }
    }
    int iGenMult = 0;
    int iSubeMult = 0;
    GenTrackIterator genIterator;
    for (genIterator = event->genTrackCollection()->begin(); genIterator != event->genTrackCollection()->end(); genIterator++)
    {
        double trackPt = (*genIterator)->TrkPt();
        double trackEta = (*genIterator)->TrkEta();
        int trackCharge = (*genIterator)->TrkChg();
        int trackSube = (*genIterator)->TrackSube();

        bool isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1] && trackCharge != 0);
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
            if (trackSube > 0)
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

double DiJetAnalysis::MultiplicityWeight(const double& multiplicity)
{
    if (!fIsMC || fSystem != CollisionSystem::pPb)
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

float DiJetAnalysis::getDijetWeight(const double& leadPt, const double& subLeadPt)
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

double DiJetAnalysis::EventWeight(const Event* event)
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

    double ptHatWeight{1.};
    double eventWeight{1.};
    double vzWeight{1.};
    double ptHat = event->ptHat();
    double vertexZ = event->vz();
    double centWeight{1.};
    if (ptHat < 0)
    {
        return 1.0;
    }
    if (fSystem == CollisionSystem::pPb)
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
    centWeight = CentralityWeight(event->hiBin());
    eventWeight = ptHatWeight * vzWeight * centWeight;

    if (fDebug)
    {
        std::cout << "PtHat Weight : " << ptHatWeight << std::endl;
        std::cout << "Vz Weight : " << vzWeight << std::endl;
        std::cout << "Event Weight = PtHat Weight * Vz Weight = " << eventWeight << std::endl;
    }

    return eventWeight;
}

double DiJetAnalysis::pPbptHatWeight(const double& pthat)
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
            fSystem = CollisionSystem::pp;
            fCollSystem = "pp";
            std::cout << "Collision System set to be : pp" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::pPb)
        {
            fSystem = CollisionSystem::pPb;
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
            fSystem = CollisionSystem::PbPb;
            fCollSystem = "PbPb";
            std::cout << "Collision System set to : PbPb" << std::endl;
        }
        else if (collSystem == ForestReader::CollidingSystemType::OO)
        {
            fSystem = CollisionSystem::OO;
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

double DiJetAnalysis::DeltaPhi(const double& phi1, const double& phi2)
{
    double dPhi = phi1 - phi2;
    if (dPhi > TMath::Pi())
    {
        dPhi += -2 * TMath::Pi();
    }
    else if (dPhi <= -TMath::Pi())
    {
        dPhi += 2 * TMath::Pi();
    }
    if (fDebug)
    {
        std::cout << Form("Delta Phi: %f", dPhi) << std::endl;
    }
    return dPhi;
}

double DiJetAnalysis::Asymmetry(const float& leadJetPt, const float& subLeadJetPt)
{
    if (fDebug)
    {
        std::cout << "DiJetAnalysis::Asymmetry : " << subLeadJetPt / leadJetPt << std::endl;
    }
    return subLeadJetPt / leadJetPt;
}

double DiJetAnalysis::HiHFWeight(const double& hiHF)
{
    if (fSystem != CollisionSystem::OO) return 1.0;
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

float DiJetAnalysis::MoveToCMFrame(const float& jetEta)
{
    if (fSystem != CollisionSystem::pPb)
    {
        return jetEta;
    }
    float jetEtaCM = jetEta;
    if (fSystem == CollisionSystem::pPb && fUseCMFrame)
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

float DiJetAnalysis::MoveToLabFrame(const float& jetEta)
{
    float jetEtaLab = jetEta;
    if (fSystem == CollisionSystem::pPb)
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
    else if (fSystem != CollisionSystem::pPb)
    {
        jetEtaLab = jetEta + fEtaBoost;
    }
    if (fDebug)
    {
        std::cout << Form("Jet Eta: %f, Jet Eta Lab: %f", jetEta, jetEtaLab) << std::endl;
    }

    return jetEtaLab;
}

double DiJetAnalysis::CentralityWeight(const int& centrality)
{
    if (fSystem != CollisionSystem::OO || !fIsMC || !fUseCentralityWeight) return 1.0;
    if (centrality <= 30)
        return fCentWeightFunctions[0]->Eval(centrality);
    else if (centrality > 30 && centrality <= 180)
        return fCentWeightFunctions[1]->Eval(centrality);
    else
        return 1.0;
}

bool DiJetAnalysis::CheckDijet(const float& leadpt, const float& leadeta, const float& subleadpt, const float& subleadeta, const bool& leadID, const bool& subleadID)
{
    bool isDijetPt = false;
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
        isDijetPt = true;
    }
    bool isDijetLeadEta = false;
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
        isDijetLeadEta = true;
    }
    bool isDijetSubLeadEta = false;
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
        isDijetSubLeadEta = true;
    }
    bool isDijetID = false;
    if (leadID && subleadID)
    {
        if (fDebug)
        {
            std::cout << Form("DiJet ID Requirement Satisfied. Lead Jet ID : %i , Sub Lead Jet ID : %i ", leadID, subleadID) << std::endl;
        }
        isDijetID = true;
    }

    return (isDijetPt && isDijetLeadEta && isDijetSubLeadEta && isDijetID);
}

int DiJetAnalysis::GetDiJetRegion(const float& jetEta)
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

float DiJetAnalysis::FlipVertexZ(const float& vertexz)
{
    if (fSystem == CollisionSystem::pPb)
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

double DiJetAnalysis::GetJetFlavor(const int& partonFlavor)
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
                         fCycleCounter * 50000, fNEventsInSample, static_cast<double>(fCycleCounter * 50000) * 100. / fNEventsInSample)
                  << std::endl;
        fEventCounter = {0};
    }
    // std::cout << "Event Counter : " << event->eventNumber() << std::endl;

    if (!fHM)
    {
        throw std::runtime_error("Oops ! You are missing something ! It is Histogram Manager.");
        return;
    }
    double Event_Weight = EventWeight(event);

    // A. Find Reco Dijet
    DijetInfo recoDijet = FindDijet(event->recoJetCollection()->begin(), event->recoJetCollection()->end(),
                                    [&](const auto& jetPtr)
                                    {
                                        JetKinematics k;
                                        k.pt = jetPtr->ptJECCorr();
                                        k.eta = MoveToCMFrame(jetPtr->eta());
                                        k.phi = jetPtr->phi();
                                        k.id = jetPtr->JetID();
                                        k.flavor = jetPtr->JetPartonFlavorForB();
                                        if (fIsMC)
                                        {
                                            k.matchPt = jetPtr->RefJetPt();
                                        }
                                        return k;
                                    });

    // Calculate derived Reco properties
    recoDijet.isValidDijet = CheckDijet(recoDijet.lead.pt, recoDijet.lead.eta, recoDijet.subLead.pt, recoDijet.subLead.eta, recoDijet.lead.id, recoDijet.subLead.id);
    if (recoDijet.isValidDijet)
    {
        recoDijet.deltaPhi = TMath::Abs(DeltaPhi(recoDijet.lead.phi, recoDijet.subLead.phi));
        recoDijet.xj = Asymmetry(recoDijet.lead.pt, recoDijet.subLead.pt);
    }

    DijetInfo refDijet;
    DijetInfo genDijet;

    if (fIsMC)
    {
        // B. Find Ref Dijet (By swapping the lambda properties, the template perfectly sorts by RefPt instead of RecoPt!)
        refDijet = FindDijet(event->recoJetCollection()->begin(), event->recoJetCollection()->end(),
                             [&](const auto& jetPtr)
                             {
                                 JetKinematics k;
                                 k.pt = jetPtr->RefJetPt();  // <--- Notice we map RefJetPt to primary pt!
                                 k.eta = MoveToCMFrame(jetPtr->RefJetEta());
                                 k.phi = jetPtr->RefJetPhi();
                                 k.id = true;                               //
                                 k.flavor = jetPtr->JetPartonFlavorForB();  // Ref doesn't have ID check
                                 k.matchPt = jetPtr->ptJECCorr();
                                 return k;
                             });

        refDijet.isValidDijet = CheckDijet(refDijet.lead.pt, refDijet.lead.eta, refDijet.subLead.pt, refDijet.subLead.eta, true, true);
        if (refDijet.isValidDijet)
        {
            refDijet.deltaPhi = TMath::Abs(DeltaPhi(refDijet.lead.phi, refDijet.subLead.phi));
            refDijet.xj = Asymmetry(refDijet.lead.pt, refDijet.subLead.pt);
        }

        // C. Find Gen Dijet
        genDijet = FindDijet(event->genJetCollection()->begin(), event->genJetCollection()->end(),
                             [&](const auto& jetPtr)
                             {
                                 JetKinematics k;
                                 k.pt = jetPtr->pt();
                                 k.eta = MoveToCMFrame(jetPtr->eta());
                                 k.phi = jetPtr->phi();
                                 k.id = true;
                                 return k;
                             });

        genDijet.isValidDijet = CheckDijet(genDijet.lead.pt, genDijet.lead.eta, genDijet.subLead.pt, genDijet.subLead.eta, true, true);
        if (genDijet.isValidDijet)
        {
            genDijet.deltaPhi = TMath::Abs(DeltaPhi(genDijet.lead.phi, genDijet.subLead.phi));
            genDijet.xj = Asymmetry(genDijet.lead.pt, genDijet.subLead.pt);
        }
    }

    fDijetWeight = CalculateDijetWeight(recoDijet, refDijet, genDijet);
    // std::cout << "Event Weight : " << Event_Weight << std::endl;
    if (fSystem == CollisionSystem::pPb && fUseMultiplicityWeight)
    {
        Event_Weight *= MultiplicityWeight(static_cast<double>(event->multiplicity()));
    }
    // std::cout << "Event Weight * MultWeight : " << Event_Weight << std::endl;

    double iMultiplicityBin;
    if (fMultiplicityType != 4)
    {
        iMultiplicityBin = static_cast<double>(event->multiplicity());
    }
    else if (fMultiplicityType == 4)
    {
        iMultiplicityBin = static_cast<double>(event->hiBinWithShift());
    }

    double iVertexZ = event->vz();

    if (fSystem == CollisionSystem::pPb)
    {
        iVertexZ = FlipVertexZ(iVertexZ);
    }

    // int iRecoMult = RecoMultiplicity(fSystem == CollisionSystem::pPb, event);
    int iRecoMult = event->multiplicity();
    std::pair<int, float> iRecoCorrectedMult = RecoCorrectedMultiplicity(event, Event_Weight, iMultiplicityBin);
    std::pair<int, int> iGenSubeMult = {0.0, 0.0};
    if (fIsMC)
    {
        iGenSubeMult = GenSubeMultiplicity(event, Event_Weight, iMultiplicityBin);
    }

    if (fSystem == CollisionSystem::OO)
    {
        iRecoMult = event->multiplicity();
        iRecoCorrectedMult.first = event->multiplicity();
        iRecoCorrectedMult.second = event->correctedNtrkoff();
        iGenSubeMult.first = event->genMultiplicity();
        iGenSubeMult.second = event->subEventMultiplicity();
    }

    double iMultiplicity;
    iMultiplicity = (fMultiplicityType == 0)   ? static_cast<double>(iRecoMult)
                    : (fMultiplicityType == 1) ? static_cast<double>(iGenSubeMult.first)
                    : (fMultiplicityType == 2) ? static_cast<double>(iRecoCorrectedMult.second)
                    : (fMultiplicityType == 3) ? static_cast<double>(fSystem == CollisionSystem::pPb || fSystem == CollisionSystem::pp
                                                                         ? iGenSubeMult.first
                                                                         : (fSystem == CollisionSystem::PbPb ? iGenSubeMult.second : 0))
                    : (fMultiplicityType == 4) ? static_cast<double>(event->hiBinWithShift())
                                               : 0;

    if (fIsMC)
    {
        fHM->hPtHat->Fill(event->ptHat());
        fHM->hPtHat_W->Fill(event->ptHat(), Event_Weight);
    }

    fHM->hNEventsInMult->Fill(iMultiplicityBin);
    fHM->hHiBin->Fill(event->hiBinWithShift());
    fHM->hHiBin_W->Fill(event->hiBinWithShift(), Event_Weight);
    fHM->hHiHF_PF->Fill(event->hiHFPF());
    fHM->hHiHF_PF_W->Fill(event->hiHFPF(), Event_Weight);

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

    processRecoJets(event, Event_Weight, iMultiplicityBin, recoDijet, refDijet);

    if (fIsMC)
    {
        processGenJets(event, Event_Weight, iMultiplicityBin, genDijet, recoDijet);
    }
    // std::cout << "HiHFPlus : " << event->hiHFPlus() << " HiHFMinus : " << event->hiHFMinus() << std::endl;
    // std::cout << "Multiplicity : " << iMultiplicity << " Multiplicity Bins : " << iMultiplicityBin << std::endl;

    fHM->hVz->Fill(iVertexZ);
    fHM->hVz_W->Fill(iVertexZ, Event_Weight * fDijetWeight);

    double Multiplicities[7] = {static_cast<double>(iRecoMult),
                                static_cast<double>(iGenSubeMult.first),
                                static_cast<double>(iRecoCorrectedMult.first),
                                static_cast<double>(iRecoCorrectedMult.second),
                                static_cast<double>(iGenSubeMult.second),
                                static_cast<double>(event->hiBinWithShift()),
                                iMultiplicityBin};
    fHM->hMultiplicities_W->Fill(Multiplicities, Event_Weight);
    fHM->hHiHFPlusVsHiHFMinus->Fill(event->hiHFMinus(), event->hiHFPlus());
    fHM->hHiHFPlusVsHiHFMinus_W->Fill(event->hiHFMinus(), event->hiHFPlus(), Event_Weight);
    fHM->hHiHFPlusVsMultiplicity_W->Fill(iMultiplicity, event->hiHFPlus(), Event_Weight);
    fHM->hHiHFMinusVsMultiplicity_W->Fill(iMultiplicity, event->hiHFMinus(), Event_Weight);
    if (recoDijet.isValidDijet && recoDijet.deltaPhi > fDeltaPhi)
    {
        fHM->hMultiplicities_DiJet_W->Fill(Multiplicities, Event_Weight);
        fHM->hHiHFPlusVsHiHFMinus_WithDijet_W->Fill(event->hiHFMinus(), event->hiHFPlus(), Event_Weight * HiHFWeight(event->hiHFPlus()));
        fHM->hHiHFPlusVsMultiplicity_WithDijet_W->Fill(iRecoMult, event->hiHFPlus(), Event_Weight);
        fHM->hHiHFMinusVsMultiplicity_WithDijet_W->Fill(iRecoMult, event->hiHFMinus(), Event_Weight);
        if (fSystem == CollisionSystem::OO)
        {
            fHM->hHiBinVsMultiplicity_W->Fill(iRecoMult, event->hiBinWithShift());
            fHM->hHiBinVsCorrectedMultiplicity_W->Fill(iRecoCorrectedMult.second, event->hiBinWithShift());
        }
    }

    processRecoTracks(event, Event_Weight, iMultiplicityBin);
    if (fIsMC)
    {
        processGenTracks(event, Event_Weight, iMultiplicityBin);
        if (fDoUnfolding)
        {
            unfolding(event, Event_Weight, iMultiplicityBin, recoDijet, refDijet, genDijet);  // <--- Passed all 3 structs        }
        }
    }
}

void DiJetAnalysis::processRecoJets(const Event* event, const double& event_Weight, const double& multiplicityBin, const DijetInfo& recoDijet, const DijetInfo& refDijet)
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

    TrackIterator recoTrackIterator;

    for (auto recoJetIterator = event->recoJetCollection()->begin(); recoJetIterator != event->recoJetCollection()->end(); recoJetIterator++)
    {
        float jetPt = (*recoJetIterator)->ptJECCorr();
        float jetEta = (*recoJetIterator)->eta();
        float jetPhi = (*recoJetIterator)->phi();
        bool jetID = (*recoJetIterator)->JetID();
        float rawPt = (*recoJetIterator)->pt();
        double jetFlavor = (*recoJetIterator)->JetPartonFlavorForB();

        float refPt;
        float refEta;
        float refPhi;
        if (fIsMC)
        {
            refPt = (*recoJetIterator)->RefJetPt();
            refEta = (*recoJetIterator)->RefJetEta();
            refPhi = (*recoJetIterator)->RefJetPhi();

            // std::cout << Form("Raw Pt: %f, Jet Pt: %f, Jet Eta: %f, Jet Phi: %f", rawPt, jetPt,
            // jetEta, jetPhi) << std::endl;

            if (TMath::Abs(refEta) < 2.0 && refPt > 15)
            {
                // std::cout << Form("Ref Pt: %f, Ref Eta: %f, Ref Phi: %f", refPt, refEta, refPhi) <<
                // std::endl;

                fHM->hRecoJES_W->Fill(jetPt / refPt, jetPt, multiplicityBin, event_Weight);
                fHM->hRefJES_W->Fill(jetPt / refPt, refPt, multiplicityBin, event_Weight);
                if (refPt > 20.0)
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
            if (TMath::Abs(refEta) < 3.0 && refPt > 30)
            {
                double JetFractions[5] = {refPt, refEta, refPhi, static_cast<double>(TMath::Abs((*recoJetIterator)->JetPartonFlavorForB())), multiplicityBin};
                fHM->hJetFlavorFractions_W->Fill(JetFractions, event_Weight);
            }
        }
        if (fDoInJetMult && jetPt > fSubLeadJetPtLow)
        {
            int iInJetMult = 0;
            for (recoTrackIterator = event->trackCollection()->begin(); recoTrackIterator != event->trackCollection()->end(); recoTrackIterator++)
            {
                float trackPt = (*recoTrackIterator)->TrkPt();
                float trackEta = (*recoTrackIterator)->TrkEta();
                float trackPhi = (*recoTrackIterator)->TrkPhi();

                float dR = std::sqrt(std::pow(jetEta - trackEta, 2) + std::pow(DeltaPhi(jetPhi, trackPhi), 2));

                if (dR <= 0.4)
                {
                    iInJetMult++;
                }
            }
            fHM->hInJetMultiplicity_W->Fill(iInJetMult, event->multiplicity(), event_Weight);
        }

        float jetEtaCM = MoveToCMFrame(jetEta);
        // double jetFlavor = GetJetFlavor((*recoJetIterator)->JetPartonFlavorForB());

        double JetQuantities[5] = {jetPt, jetEtaCM, jetPhi, jetFlavor, multiplicityBin};
        double JetQuantitiesLab[5] = {jetPt, jetEta, jetPhi, jetFlavor, multiplicityBin};
        double UnCorrJetQuantities[5] = {rawPt, jetEta, jetPhi, jetFlavor, multiplicityBin};

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
        if (fSystem == CollisionSystem::pPb)
        {
            fHM->hInclusiveRecoJetsLabFrame->Fill(JetQuantitiesLab);
            fHM->hInclusiveRecoJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight);
            fHM->hInclusiveUnCorrectedRecoPtVsEtaLabFrame_W->Fill(jetEta, rawPt, event_Weight);
            fHM->hInclusiveRecoJetPtVsEtaLabFrame_W->Fill(jetEta, jetPt, event_Weight);
        }

        if (fIsMC)
        {
            double RefJetQuantities[5] = {refPt, MoveToCMFrame(refEta), refPhi, jetFlavor, multiplicityBin};
            double RefJetQuantitiesLab[5] = {refPt, MoveToLabFrame(refEta), refPhi, jetFlavor, multiplicityBin};

            fHM->hInclusiveRefJetsCMFrame->Fill(RefJetQuantities);
            fHM->hInclusiveRefJetsCMFrame_W->Fill(RefJetQuantities, event_Weight);
            if (fSystem == CollisionSystem::pPb)
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

    bool recoDijetPass = recoDijet.isValidDijet && recoDijet.deltaPhi > fDeltaPhi;
    if (recoDijet.lead.pt > fLeadJetPtLow && recoDijet.subLead.pt > fSubLeadJetPtLow)
    {
        double LeadSLeadJets[7] = {recoDijet.lead.pt,     recoDijet.lead.eta,    recoDijet.lead.phi, recoDijet.subLead.pt,
                                   recoDijet.subLead.eta, recoDijet.subLead.phi, multiplicityBin};
        fHM->hLeadSubLeadJets->Fill(LeadSLeadJets);
        fHM->hLeadSubLeadJets_W->Fill(LeadSLeadJets, event_Weight);
    }

    if (recoDijet.isValidDijet)
    {
        double LeadSLeadJetsMidRapidity[7] = {recoDijet.lead.pt,     recoDijet.lead.eta,    recoDijet.lead.phi, recoDijet.subLead.pt,
                                              recoDijet.subLead.eta, recoDijet.subLead.phi, multiplicityBin};
        fHM->hLeadSubLeadJets_MidRapidity_W->Fill(LeadSLeadJetsMidRapidity, event_Weight);
        fHM->hDeltaPhi_W->Fill(recoDijet.deltaPhi, event_Weight);

        double QuenchingQuantities[5] = {recoDijet.xj, recoDijet.deltaPhi, recoDijet.lead.pt, recoDijet.subLead.pt, multiplicityBin};
        fHM->hRecoQuenching_W->Fill(QuenchingQuantities, event_Weight);

        if (recoDijetPass)
        {
            // std::cout << "Ref Lead : " << leadRefPt << " Ref SLead : " << subLeadRefPt << std::endl;
            // std::cout << "Ref Matched Lead : " << leadMatchedJetPt << " Ref Matched SLead : " << subLeadMatchedJetPt << std::endl;
            // std::cout << " Lead Jet Pt : " << leadJetPt << " SubLead Jet Pt: " << subLeadJetPt << std::endl;
            // std::cout << "Lead Jet Eta : " << leadJetEtaCM << " SubLead Jet Eta : " << subLeadJetEtaCM << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Event Number : " << event->eventNumber() << std::endl;
            // std::cout << "Xj : " << Xj << " Delta Phi : " << deltaPhi << std::endl;
            // std::cout << "Lead Jet Pt: " << leadJetPt << " SubLead Jet Pt: " << subLeadJetPt << std::endl;
            // std::cout << "Lead Jet Eta: " << leadJetEtaCM << " SubLead Jet Eta: " << subLeadJetEtaCM << std::endl;
            // std::cout << "Lead Jet Phi: " << leadJetPhi << "SubLead Jet Phi : " << subLeadJetPhi << std::endl;
            // std::cout << std::endl;
            // std::cout << multiplicityBin << std::endl;
            double jetPt = (fUseAveragePt) ? averagePt(recoDijet.lead.pt, recoDijet.subLead.pt) : recoDijet.lead.pt;
            double leadPtWeight = jetPtWeight(recoDijet.lead.pt);
            fHM->hDeltaPhi_WithDiJet_W->Fill(recoDijet.deltaPhi, event_Weight);
            fHM->hMultVsXj_W->Fill(recoDijet.xj, multiplicityBin, jetPt, event_Weight * leadPtWeight);
            fHM->hMultVsXj_DiJetW->Fill(recoDijet.xj, multiplicityBin, jetPt, event_Weight * fDijetWeight);
            fHM->hMultVsXj_HiHFW->Fill(recoDijet.xj, multiplicityBin, event_Weight * HiHFWeight(event->hiHFPlus()));
            fHM->hHiHFVsXj_W->Fill(recoDijet.xj, event->hiHFPlus(), event_Weight);
            fHM->hHiHFVsXj_HiHFW->Fill(recoDijet.xj, event->hiHFPlus(), event_Weight * HiHFWeight(event->hiHFPlus()));
            fHM->hAverageRecoPt_W->Fill(averagePt(recoDijet.lead.pt, recoDijet.subLead.pt), event_Weight);
            double LeadSLeadJetsWithDijet[7] = {recoDijet.lead.pt,     recoDijet.lead.eta,    recoDijet.lead.phi, recoDijet.subLead.pt,
                                                recoDijet.subLead.eta, recoDijet.subLead.phi, multiplicityBin};
            fHM->hLeadSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight * leadPtWeight);
            fHM->hLeadSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadJetsWithDijet, event_Weight * fDijetWeight);

            fHM->hLeadPtvsSubLeadPt_PtHatW->Fill(recoDijet.subLead.pt, recoDijet.lead.pt, event_Weight);
            fHM->hLeadPtvsSubLeadPt_DiJetW->Fill(recoDijet.subLead.pt, recoDijet.lead.pt, event_Weight * fDijetWeight);
            fHM->hVzWithDijet_W->Fill(event->vz(), event_Weight);

            double QuenchingQuantitiesWithDijet[4] = {recoDijet.xj, recoDijet.lead.pt, recoDijet.subLead.pt, multiplicityBin};
            fHM->hRecoQuenching_WithDijet_W->Fill(QuenchingQuantitiesWithDijet, event_Weight);
            fHM->hNDijetEvent->Fill(1);
            if (fIsMC)
            {
                fHM->hLeadPtVsRecoXj_W->Fill(recoDijet.xj, recoDijet.lead.pt, event_Weight);
                double matchedRefXj = Asymmetry(recoDijet.lead.matchPt, recoDijet.subLead.matchPt);
                fHM->hMultVsUnflippedMatchedRefXj_W->Fill(matchedRefXj, multiplicityBin, recoDijet.lead.matchPt, event_Weight);
                fHM->hMultVsUnflippedMatchedRefXj_DiJetW->Fill(matchedRefXj, multiplicityBin, recoDijet.lead.matchPt, event_Weight * fDijetWeight);
                double maxMatchedPt = recoDijet.lead.matchPt;
                double minMatchedPt = recoDijet.subLead.matchPt;
                if (matchedRefXj > 1.0)
                {
                    matchedRefXj = 1.0 / matchedRefXj;
                    maxMatchedPt = recoDijet.subLead.matchPt;
                    minMatchedPt = recoDijet.lead.matchPt;
                }

                fHM->hMultVsMatchedRefXj_W->Fill(matchedRefXj, multiplicityBin, maxMatchedPt, event_Weight);
                fHM->hMultVsMatchedRefXj_DiJetW->Fill(matchedRefXj, multiplicityBin, maxMatchedPt, event_Weight * fDijetWeight);
                fHM->hRefLeadPtVsRefSubLeadPtMatched_PtHatW->Fill(minMatchedPt, maxMatchedPt, event_Weight);
                fHM->hRefLeadPtVsRefSubLeadPtMatched_DiJetW->Fill(minMatchedPt, maxMatchedPt, event_Weight * fDijetWeight);
                fHM->hLeadPtVsRefXj_W->Fill(matchedRefXj, maxMatchedPt, event_Weight);
            }
        }
        if (fIsMC)
        {
            if (recoDijet.lead.flavor == 0)
            {
                fHM->hFakeLeadXj_W->Fill(recoDijet.xj, multiplicityBin, recoDijet.lead.pt, event_Weight);
                recoDijetPass = false;
            }
            else if (recoDijet.subLead.flavor == 0)
            {
                fHM->hFakeSubLeadXj_W->Fill(recoDijet.xj, multiplicityBin, recoDijet.lead.pt, event_Weight);
                recoDijetPass = false;
            }
        }
    }
    bool refDijetPass = refDijet.isValidDijet && refDijet.deltaPhi > fDeltaPhi;
    if (fIsMC)
    {
        double LeadSLeadRefJets[7] = {refDijet.lead.pt,     refDijet.lead.eta,    refDijet.lead.phi, refDijet.subLead.pt,
                                      refDijet.subLead.eta, refDijet.subLead.phi, multiplicityBin};
        fHM->hRefLeadRefSubLeadJets->Fill(LeadSLeadRefJets);
        fHM->hRefLeadRefSubLeadJets_W->Fill(LeadSLeadRefJets, event_Weight);

        if (refDijet.isValidDijet)
        {
            fHM->hRefLeadRefSubLeadJets_MidRapidity_W->Fill(LeadSLeadRefJets, event_Weight);
            fHM->hRefDeltaPhi_W->Fill(refDijet.deltaPhi, event_Weight);

            // std::cout << "RefXj : " << refXj << " refDeltaPhi : " << refDeltaPhi << std::endl;
            // std::cout << Form("Ref Lead Pt : %f, Ref SubLead Pt : %f, Ref Lead Eta : %f, Ref SubLead Eta : %f", leadRefPt, subLeadRefPt, leadRefJetEtaCM,
            // subleadRefEtaCM)
            //           << std::endl;
            // std::cout << Form("Ref Lead Phi : %f, Ref SubLead Phi : %f, Ref DeltaPhi : %f", leadRefPhi, subLeadRefPhi, refDeltaPhi) << std::endl;

            if (refDijetPass)
            {
                fHM->hRefDeltaPhi_WithDiJet_W->Fill(refDijet.deltaPhi, event_Weight);
                fHM->hRefLeadRefSubLeadJets_WithDijet_W->Fill(LeadSLeadRefJets, event_Weight);
                fHM->hRefLeadRefSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadRefJets, event_Weight * fDijetWeight);

                fHM->hRefLeadPtvsRefSubLeadPt_PtHatW->Fill(refDijet.subLead.pt, refDijet.lead.pt, event_Weight);
                fHM->hRefLeadPtvsRefSubLeadPt_DiJetW->Fill(refDijet.subLead.pt, refDijet.lead.pt, event_Weight * fDijetWeight);

                double matchedRecoXj = Asymmetry(refDijet.lead.matchPt, refDijet.subLead.matchPt);
                fHM->hMultVsUnflippedMatchedRecoXj_W->Fill(matchedRecoXj, multiplicityBin, refDijet.lead.matchPt, event_Weight);
                double maxMatchedRecoPt = refDijet.lead.matchPt;
                if (matchedRecoXj > 1.0)
                {
                    matchedRecoXj = 1.0 / matchedRecoXj;
                    maxMatchedRecoPt = refDijet.subLead.matchPt;
                }
                fHM->hMultVsMatchedRecoXj_W->Fill(matchedRecoXj, multiplicityBin, maxMatchedRecoPt, event_Weight);
                fHM->hMultVsRefXj_W->Fill(refDijet.xj, multiplicityBin, refDijet.lead.pt, event_Weight);
                fHM->hMultVsRefXj_DiJetW->Fill(refDijet.xj, multiplicityBin, refDijet.lead.pt, event_Weight * fDijetWeight);
            }
        }
    }

    if (fIsMC)
    {
        double rndm = uniform01();
        double matchedRefXj = Asymmetry(recoDijet.lead.matchPt, recoDijet.subLead.matchPt);
        double matchedRecoXj = Asymmetry(refDijet.lead.matchPt, refDijet.subLead.matchPt);
        double unfoldingQuantities[4] = {recoDijet.xj, matchedRefXj, multiplicityBin, recoDijet.lead.pt};
        if (rndm <= 0.5)
        {
            if (recoDijetPass)
            {
                fHM->hUnfoldingRefXjVsRecoXjVsMultiplicityForTesting_W->Fill(unfoldingQuantities, event_Weight);
                if (!refDijetPass)
                {
                    fHM->hMultVsFakeRecoXjForTesting_W->Fill(recoDijet.xj, multiplicityBin, event_Weight);
                    fHM->hMultVsFakeRefXjForTesting_W->Fill(matchedRefXj, multiplicityBin, event_Weight);
                }
            }

            if (!recoDijetPass && refDijetPass)
            {
                // std::cout << "Is Reco Dijet : " << fIsRecoDiJetFound << std::endl;
                // std::cout << "Matched Reco - Reco : " << matchedRecoXj << " " << Xj << std::endl;
                // std::cout << leadMatchedRecoJetPt << "  " << leadJetPt << " " << leadJetEtaCM << "   " << leadJetEta << "   " << leadJetPhi << std::endl;
                // std::cout << subLeadMatchedRecoJetPt << "   " << subLeadJetPt << "  " << subLeadJetEtaCM << "  " << subLeadJetEta << "  " << subLeadJetPhi <<
                // std::endl; std::cout << leadJetID << "     " << subLeadJetID << std::endl; std::cout << "Delta Phi Diff : " << deltaPhi << std::endl; std::cout <<
                // "Matched Ref - Ref : " << matchedRefXj << " " << refXj << std::endl; std::cout << leadMatchedJetPt << "  " << leadRefPt << "     " << leadRefEta <<
                // " "
                // << leadRefPhi << std::endl; std::cout << subLeadMatchedJetPt << "   " << subLeadRefPt << "   " << subLeadRefEta << "  " << subLeadRefPhi <<
                // std::endl;
                // std::cout << "Delta Ref Phi Diff : " << refDeltaPhi << std::endl;
                // std::cout << std::endl;
                fHM->hMultVsMissingRefXjForTesting_W->Fill(refDijet.xj, multiplicityBin, event_Weight);
            }
        }
        else
        {
            if (recoDijetPass)
            {
                fHM->hUnfoldingRefXjVsRecoXjVsMultiplicityToBeUnfolded_W->Fill(unfoldingQuantities, event_Weight);
                if (!refDijetPass)
                {
                    fHM->hMultVsFakeRecoXjToBeUnfolded_W->Fill(recoDijet.xj, multiplicityBin, event_Weight);
                    fHM->hMultVsFakeRefXjToBeUnfolded_W->Fill(matchedRefXj, multiplicityBin, event_Weight);
                }
            }
            if (!recoDijetPass && refDijetPass)
            {
                // fHM->hMultVsRefXjToBeUnfolded_W->Fill(refXj, multiplicityBin, event_Weight);
                fHM->hMultVsMissingRefXjToBeUnfolded_W->Fill(refDijet.xj, multiplicityBin, event_Weight);
            }
        }

        if (recoDijetPass && matchedRefXj < 0.0)
        {
            // std::cout << matchedRefXj << std::endl;
            matchedRefXj = 0.5;
            fHM->hUnfoldingRefXjVsRecoXjVsMultiplicity_FakeJets_W->Fill(recoDijet.xj, matchedRefXj, multiplicityBin, event_Weight);
        }

        if (!recoDijetPass && refDijetPass)
        {
            if (matchedRecoXj > 1.0) matchedRecoXj = 1.0 / matchedRecoXj;  // Ensure valid bounded Xj
            fHM->hUnfoldingRefXjVsRecoXjVsMultiplicity_MissingJets_W->Fill(matchedRecoXj, refDijet.xj, multiplicityBin, event_Weight);
        }
    }
}

void DiJetAnalysis::processGenJets(const Event* event, const double& event_Weight, const double& multiplicityBin, const DijetInfo& genDijet, const DijetInfo& recoDijet)
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

    GenTrackIterator genTrackIterator;
    for (auto genJetIterator = event->genJetCollection()->begin(); genJetIterator != event->genJetCollection()->end(); genJetIterator++)
    {
        float genJetPt = (*genJetIterator)->pt();
        float genJetEta = (*genJetIterator)->eta();
        float genJetPhi = (*genJetIterator)->phi();

        if (fDoInJetMult)
        {
            int iInJetMult = 0;
            for (genTrackIterator = event->genTrackCollection()->begin(); genTrackIterator != event->genTrackCollection()->end(); genTrackIterator++)
            {
                float trackPt = (*genTrackIterator)->TrkPt();
                float trackEta = (*genTrackIterator)->TrkEta();
                float trackPhi = (*genTrackIterator)->TrkPhi();

                float dR = std::sqrt(std::pow(genJetEta - trackEta, 2) + std::pow(DeltaPhi(genJetPhi, trackPhi), 2));

                if (dR <= 0.4)
                {
                    iInJetMult++;
                }
            }
            fHM->hGenInJetMultiplicity_W->Fill(iInJetMult, event->multiplicity(), event_Weight);
        }

        float genJetEtaCM = MoveToCMFrame(genJetEta);
        double_t jetFlavor = 1.0;  // Placeholder for jet flavor in gen jets
        double JetQuantities[5] = {genJetPt, genJetEtaCM, genJetPhi, jetFlavor, multiplicityBin};
        double JetQuantitiesLab[5] = {genJetPt, MoveToLabFrame(genJetEta), genJetPhi, jetFlavor, multiplicityBin};
        fHM->hInclusiveGenJetsCMFrame->Fill(JetQuantities);
        fHM->hInclusiveGenJetsCMFrame_W->Fill(JetQuantities, event_Weight);
        if (fSystem == CollisionSystem::pPb)
        {
            fHM->hInclusiveGenJetsLabFrame->Fill(JetQuantitiesLab);
            fHM->hInclusiveGenJetsLabFrame_W->Fill(JetQuantitiesLab, event_Weight);
        }
        if (genJetPt > fInclusiveCorrectedJetPtMin && genJetEtaCM < fInclusiveJetEtaRange[1] && genJetEtaCM > fInclusiveJetEtaRange[0])
        {
            fHM->hSelectedInclusiveGenJetsMidRapidity_W->Fill(JetQuantities, event_Weight);
        }
    }
    bool recoDijetPass = recoDijet.isValidDijet && recoDijet.deltaPhi > fDeltaPhi;
    if (recoDijetPass)
    {
        fHM->hGenLeadPtvsGenSubLeadPt_PtHatW->Fill(genDijet.subLead.pt, genDijet.lead.pt, event_Weight);
        fHM->hGenLeadPtvsGenSubLeadPt_DiJetW->Fill(genDijet.subLead.pt, genDijet.lead.pt, event_Weight * fDijetWeight);
    }

    bool genDijetPass = genDijet.isValidDijet && genDijet.deltaPhi > fDeltaPhi;

    if (genDijet.lead.pt > fLeadJetPtLow && genDijet.subLead.pt > fSubLeadJetPtLow)
    {
        double LeadSLeadGenJets[7] = {genDijet.lead.pt,     genDijet.lead.eta,    genDijet.lead.phi, genDijet.subLead.pt,
                                      genDijet.subLead.eta, genDijet.subLead.phi, multiplicityBin};
        fHM->hGenLeadGenSubLeadJets->Fill(LeadSLeadGenJets);
        fHM->hGenLeadGenSubLeadJets_W->Fill(LeadSLeadGenJets, event_Weight);
    }
    // if (!isGenDiJet && fIsRefDijetFound)
    // {
    //     std::cout << Form("Gen Lead Pt : %f, Gen SubLead Pt : %f, Gen Lead Eta : %f, Gen SubLead Eta : %f", genLeadJetPt, genSubLeadJetPt, genLeadJetEtaCM,
    //                       genSubLeadJetEtaCM)
    //               << std::endl;
    //     std::cout << Form("Gen Lead Phi : %f, Gen SubLead Phi : %f", genLeadJetPhi, genSubLeadJetPhi) << std::endl;
    // }

    if (genDijet.isValidDijet)
    {
        double LeadSLeadGenJetsMidRapidity[7] = {genDijet.lead.pt,     genDijet.lead.eta,    genDijet.lead.phi, genDijet.subLead.pt,
                                                 genDijet.subLead.eta, genDijet.subLead.phi, multiplicityBin};
        fHM->hGenLeadGenSubLeadJets_MidRapidity_W->Fill(LeadSLeadGenJetsMidRapidity, event_Weight);
        fHM->hGenDeltaPhi_W->Fill(genDijet.deltaPhi, event_Weight);

        double QuenchingQuantities[5] = {genDijet.xj, genDijet.deltaPhi, genDijet.lead.pt, genDijet.subLead.pt, multiplicityBin};
        fHM->hGenQuenching_W->Fill(QuenchingQuantities, event_Weight);

        // std::cout << "Gen Xj : " << Xj << std::endl;
        // std::cout << Form("Gen Lead Pt : %f, Gen SubLead Pt : %f, Gen Lead Eta : %f, Gen SubLead Eta : %f", genLeadJetPt, genSubLeadJetPt, genLeadJetEtaCM,
        //                   genSubLeadJetEtaCM)
        //           << std::endl;
        // std::cout << Form("Gen Lead Phi : %f, Gen SubLead Phi : %f, Gen DeltaPhi : %f", genLeadJetPhi, genSubLeadJetPhi, deltaPhi) << std::endl;
        // std::cout << std::endl;
        if (genDijetPass)
        {
            fHM->hGenDeltaPhi_WithDiJet_W->Fill(genDijet.deltaPhi, event_Weight);
            fHM->hMultVsGenXj_W->Fill(genDijet.xj, multiplicityBin, genDijet.lead.pt, event_Weight);
            fHM->hMultVsGenXj_DiJetW->Fill(genDijet.xj, multiplicityBin, genDijet.lead.pt, event_Weight * fDijetWeight);
            fHM->hNGenDijetEvent->Fill(1);

            double QuenchingQuantitiesWithDijet[4] = {genDijet.xj, genDijet.lead.pt, genDijet.subLead.pt, multiplicityBin};
            fHM->hGenQuenching_WithDijet_W->Fill(QuenchingQuantitiesWithDijet, event_Weight);
            fHM->hLeadPtVsGenXj_W->Fill(genDijet.xj, genDijet.lead.pt, event_Weight);

            double LeadSLeadJetsWithDijet[7] = {genDijet.lead.pt,     genDijet.lead.eta,    genDijet.lead.phi, genDijet.subLead.pt,
                                                genDijet.subLead.eta, genDijet.subLead.phi, multiplicityBin};
            fHM->hGenLeadGenSubLeadJets_WithDijet_W->Fill(LeadSLeadJetsWithDijet, event_Weight);
            fHM->hGenLeadGenSubLeadJets_WithDijet_DiJetW->Fill(LeadSLeadJetsWithDijet, event_Weight * fDijetWeight);
        }
    }
}

void DiJetAnalysis::processRecoTracks(const Event* event, const double& event_Weight, const double& multiplicityBin)
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
        float trackPt = (*trackIterator)->TrkPt();
        float trackEta = (*trackIterator)->TrkEta();
        float trackPhi = (*trackIterator)->TrkPhi();

        double trackQuantities[4] = {trackPt, trackEta, trackPhi, multiplicityBin};

        fHM->hRecoTracks->Fill(trackQuantities);
        fHM->hRecoTracks_W->Fill(trackQuantities, event_Weight);
        bool isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1]);
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

void DiJetAnalysis::processGenTracks(const Event* event, const double& event_Weight, const double& multiplicityBin)
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
        double trackPt = (*genTrackIterator)->TrkPt();
        double trackEta = (*genTrackIterator)->TrkEta();
        double trackPhi = (*genTrackIterator)->TrkPhi();
        int trackCharge = (*genTrackIterator)->TrkChg();

        double trackQuantities[4] = {trackPt, trackEta, trackPhi, multiplicityBin};
        fHM->hGenTracks->Fill(trackQuantities);
        fHM->hGenTracks_W->Fill(trackQuantities, event_Weight);

        bool isGoodTrack = (trackPt > fMinTrkPt && trackEta >= fTrkEtaRange[0] && trackEta <= fTrkEtaRange[1] && trackCharge != 0);
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

void DiJetAnalysis::unfolding(const Event* event, const double& eventWeight, const double& multBin, const DijetInfo& recoDijet, const DijetInfo& refDijet,
                              const DijetInfo& genDijet)
{
    bool genDiJetEvent = false;
    int genFlatBin = -1;
    if (genDijet.isValidDijet && genDijet.deltaPhi > fDeltaPhi)
    {
        genFlatBin = getFlattenedIndex(genDijet.xj, genDijet.lead.pt, fXjBins, fPtBins);
        if (genFlatBin != -1) genDiJetEvent = true;
    }

    bool recoDijetEvent = false;
    int recoFlatBin = -1;
    if (recoDijet.isValidDijet && recoDijet.deltaPhi > fDeltaPhi)
    {
        recoFlatBin = getFlattenedIndex(recoDijet.xj, recoDijet.lead.pt, fXjBins, fPtBins);
        if (recoFlatBin != -1) recoDijetEvent = true;
    }

    bool oneOneMatching = false;
    bool oneTwoMatching = false;
    if (genDiJetEvent && recoDijetEvent)
    {
        oneOneMatching = (jetMatching(recoDijet.lead.eta, recoDijet.lead.phi, genDijet.lead.eta, genDijet.lead.phi) &&
                          jetMatching(recoDijet.subLead.eta, recoDijet.subLead.phi, genDijet.subLead.eta, genDijet.subLead.phi));

        if (!oneOneMatching)
        {
            oneTwoMatching = (jetMatching(recoDijet.lead.eta, recoDijet.lead.phi, genDijet.subLead.eta, genDijet.subLead.phi) &&
                              jetMatching(recoDijet.subLead.eta, recoDijet.subLead.phi, genDijet.lead.eta, genDijet.lead.phi));
        }
    }

    double rndm = uniform01();

    if (oneOneMatching || oneTwoMatching)
    {
        fHM->hResponseMatrix_W->Fill(recoFlatBin, genFlatBin, multBin, eventWeight);
        fHM->hMatchedReco_W->Fill(recoFlatBin, multBin, eventWeight);
        fHM->hMatchedGen_W->Fill(genFlatBin, multBin, eventWeight);
        if (rndm <= 0.5)
        {
            fHM->hResponseMatrixA_W->Fill(recoFlatBin, genFlatBin, multBin, eventWeight);
            fHM->hMatchedGenA_W->Fill(genFlatBin, multBin, eventWeight);
            fHM->hMatchedRecoA_W->Fill(recoFlatBin, multBin, eventWeight);
        }
        else
        {
            fHM->hResponseMatrixB_W->Fill(recoFlatBin, genFlatBin, multBin, eventWeight);
            fHM->hMatchedGenB_W->Fill(genFlatBin, multBin, eventWeight);
            fHM->hMatchedRecoB_W->Fill(recoFlatBin, multBin, eventWeight);
        }
    }
    if (recoDijetEvent)
    {
        fHM->hTotalReco_W->Fill(recoFlatBin, multBin, eventWeight);
        if (rndm <= 0.5)
        {
            fHM->hTotalRecoA_W->Fill(recoFlatBin, multBin, eventWeight);
        }
        else
        {
            fHM->hTotalRecoB_W->Fill(recoFlatBin, multBin, eventWeight);
        }
    }
    if (genDiJetEvent)
    {
        fHM->hTotalTruth_W->Fill(genFlatBin, multBin, eventWeight);
        if (rndm <= 0.5)
        {
            fHM->hTotalTruthA_W->Fill(genFlatBin, multBin, eventWeight);
        }
        else
        {
            fHM->hTotalTruthB_W->Fill(genFlatBin, multBin, eventWeight);
        }
    }
}

bool DiJetAnalysis::areDoublesEqual(const double& a, const double& b)
{
    return std::fabs(a - b) <= fEpsilon * std::max(std::fabs(a), std::fabs(b));
}

double DiJetAnalysis::averagePt(const double& leadpt, const double& subleadpt)
{
    return (leadpt + subleadpt) / 2.0;
}

int DiJetAnalysis::getBinIndex(const double value, const std::vector<double>& bins)
{
    if (bins.empty()) return -1;
    auto it = std::upper_bound(bins.begin(), bins.end(), value);
    int binIndex = std::distance(bins.begin(), it);
    return binIndex;
}

int DiJetAnalysis::getFlattenedIndex(const double xj, const double pt, const std::vector<double>& xjBins, const std::vector<double>& ptBins)
{
    int xjBinIndex = getBinIndex(xj, xjBins);
    int ptBinIndex = getBinIndex(pt, ptBins);

    int nXjBins = xjBins.size() - 1;
    int nPtBins = ptBins.size() - 1;

    if (xjBinIndex == 0 || xjBinIndex > nXjBins || ptBinIndex == 0 || ptBinIndex > nPtBins) return -1;
    int flatBin = (xjBinIndex - 1) * nPtBins + ptBinIndex;

    return flatBin;
}

bool DiJetAnalysis::jetMatching(const double& recoEta, const double& recoPhi, const double& genEta, const double& genPhi)
{
    double dist = sqrt(pow(recoEta - genEta, 2) + pow((recoPhi - genPhi), 2));
    if (dist < 0.2)
        return true;
    else
        return false;
}

float DiJetAnalysis::jetPtWeight(const double& recoLeadPt)
{
    if (!fIsMC) return 1.0;
    if (fSystem != CollisionSystem::pp) return 1.0;
    if (fJetPtWeight == nullptr) return 1.0;
    if (recoLeadPt < 50 || recoLeadPt > 500) return 1.0;

    return fJetPtWeight->Eval(recoLeadPt);
}
double DiJetAnalysis::getWeightMultiplier(double xj)
{
    return 1.0 - (0.20 / (1.0 + std::exp(-37. * (xj - 1.0))));
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