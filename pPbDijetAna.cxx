/**
 * @file pPbDijetAna.cxx
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Dijet Analysis for pPb MC and Data
 * @version 0.1
 * @date 2024-09-12
 *
 * @copyright Copyright (c) 2024
 *
 */

// Jet Analysis Headers
#include "DiJetAnalysis.h"
#include "EventCut.h"
#include "ForestReader.h"
#include "HistoManagerDiJet.h"
#include "JetCut.h"
#include "Manager.h"
#include "TrackCut.h"

// ROOT headers
#include "TFile.h"
#include "TMath.h"

using namespace std;

void usage()
{
    std::cout << "./programName inputFileList oFileName isMC isEmbedded isPbGoing ptHatLow ptHatHi \n";
}
int main(int argc, char* argv[])
{
    Bool_t isMC{kTRUE};
    Bool_t isPbGoing{};
    TString inFileName;
    Int_t collEnergyGeV{8160};
    TString collSystem{"pPb"};
    Int_t collYear{2016};
    Bool_t useCentWeight{kFALSE};
    Bool_t useMultWeight{kFALSE};
    Bool_t ispPb{kTRUE};
    Bool_t useCMFrame{kFALSE};
    Double_t etaBoost{0.4654094531};
    TString jetBranchNameEmbedded{"ak4PFJetAnalyzer"};
    TString jetBranchNameUnembedded{"ak4PFJetAnalyzer"};
    std::string dijetWeightType{"Gen"};
    TString oFileName{};
    TString JECFileName{};
    TString JECFileDataName{};
    TString JEUFileName{};
    TString path2JEC = "..";
    Double_t ptHatCut[2]{15., 30.};
    Bool_t isEmbedded{kTRUE};
    std::vector<double> multiplicityBins = {0.0, 10.0, 60., 120., 185., 250., 400.};
    std::vector<double> hiHFBins = {0., 10., 20., 30., 40., 50., 70., 90., 120., 150., 1000.};
    std::vector<double> ptBins = {50.0, 55., 60., 65., 70., 80., 90., 200.};
    std::vector<double> xjBins = {0.0,  0.025, 0.05, 0.075, 0.1,  0.125, 0.15, 0.175, 0.2,  0.225, 0.25, 0.275, 0.3,  0.325,
                                  0.35, 0.375, 0.4,  0.425, 0.45, 0.475, 0.5,  0.525, 0.55, 0.575, 0.6,  0.625, 0.65, 0.675,
                                  0.7,  0.725, 0.75, 0.775, 0.8,  0.825, 0.85, 0.875, 0.9,  0.925, 0.95, 0.975, 1.0};
    std::string path2DijetWeight = "../aux_files/pPb_8160/Dijet_Weight/DJWEPOS.root";
    std::vector<std::string> filters{"pBeamScrapingFilter", "pPAprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "phfCoincFilter", "pVertexFilterCutdz1p0"};
    std::vector<std::string> triggers{"HLT_PAAK4PFJet80_Eta5p1_v3"};
    std::string UEType{"EPOS"};
    Int_t smearType{0};            // 0 - Nominal Smearing, 1 - JER Smearing, 2 - JEC Smearing
    Bool_t useJERSmearing{kTRUE};  // Use JER Smearing for MC
    Bool_t useJEU{kFALSE};         // 0 - No JEC Uncertainty, 1 - JEC Uncertainty Up, -1 - JEC Uncertainty Down
    Int_t JEUType{0};              // 0 - No JEU, 1 - JEU Up, -1 - JEU Down
    // Command line arguments
    /*
    inputFileList               - input file list with forest file paths
    outputFileName.root         - Output file name
    isMC                        - if it is Monte Carlo or Data
    isPbGoing                   - If it is PbGoing side or pGoing Side
    ptHatLow                    - Low PtHat cut (For MC Only)
    ptHatHigh                   - High PtHat cut (For MC Only)
    */

    if (argc <= 1)
    {
        std::cout << "Too few arguments passed. Terminating !" << std::endl;
        usage();
        return -1;
    }
    else
    {
        inFileName = argv[1];
        oFileName = argv[2];
        isMC = atoi(argv[3]);
        isEmbedded = atoi(argv[4]);
        isPbGoing = atoi(argv[5]);
        ptHatCut[0] = atoi(argv[6]);
        ptHatCut[1] = atoi(argv[7]);
    }

    if (isMC)
    {
        if (isPbGoing)
        {
            if (isEmbedded)
            {
                JECFileName = "Autumn16_HI_pPb_Pbgoing_Embedded_MC_L2Relative_AK4PF.txt";
            }
            else
            {
                JECFileName = "Autumn16_HI_pPb_Pbgoing_Unembedded_MC_L2Relative_AK4PF.txt";
            }
        }
        else
        {
            if (isEmbedded)
            {
                JECFileName = "Autumn16_HI_pPb_pgoing_Embedded_MC_L2Relative_AK4PF.txt";
            }
            else
            {
                JECFileName = "Autumn16_HI_pPb_pgoing_Unembedded_MC_L2Relative_AK4PF.txt";
            }
        }
    }
    else
    {
        if (isPbGoing)
        {
            JECFileName = "Autumn16_HI_pPb_pgoing_Embedded_MC_L2Relative_AK4PF.txt";
        }
        else
        {
            JECFileName = "Autumn16_HI_pPb_Pbgoing_Embedded_MC_L2Relative_AK4PF.txt";
        }
        JECFileDataName = "Summer16_23Sep2016HV4_DATA_L2L3Residual_AK4PF.txt";
        JEUFileName = "Summer16_23Sep2016HV4_DATA_Uncertainty_AK4PF.txt";
    }

    // Initialize package manager
    Manager* manager = new Manager{};

    // Initialize event cuts
    EventCut* eventCut = new EventCut{};
    eventCut->setVz(-15., 15.);
    if (isMC)
    {
        eventCut->setPtHat(ptHatCut[0], ptHatCut[1]);
    }
    // eventCut->setVerbose();

    // Initialize jet cuts
    JetCut* jetCut = new JetCut{};
    jetCut->setEta(-5.0, 5.0);
    jetCut->setPt(0., 8160.);
    // jetCut->setVerbose();

    // Initiazlize Track Cuts

    TrackCut* trackCut = new TrackCut{};
    trackCut->setPt(0.4, 1000.);
    trackCut->setEta(-2.4, 2.4);
    trackCut->setPtErr(0.1);
    trackCut->setDXY(3.0);
    trackCut->setDZ(3.0);
    trackCut->setHighPurity();
    trackCut->setCharge();
    // trackCut->setVerbose();

    // Initialize Forest Reader

    ForestReader* reader = new ForestReader{inFileName};
    reader->setForestFileType(ForestReader::ForestFileType::AOD);
    if (isMC)
    {
        reader->setIsMc(isMC);
        reader->useGenTrackBranch();
        if (isEmbedded)
        {
            reader->setJetCollectionBranchName(jetBranchNameEmbedded.Data());
            reader->setJetPtSmearing(useJERSmearing, smearType);
            reader->setMatchedJets();
            reader->setJESCorrections();
        }
        else
        {
            reader->setJetCollectionBranchName(jetBranchNameUnembedded.Data());
        }
    }
    reader->useSkimmingBranch();
    reader->useTrackBranch();
    reader->useJets();
    // reader->useHltBranch();
    // reader->setTriggers(triggers);
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(ForestReader::CollidingSystemType::pPb, isPbGoing);
    reader->setYearOfDataTaking(collYear);
    reader->addJECFile(JECFileName.Data());
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setUseJetID();
    reader->setJetIDType(2);
    reader->eventsToProcess(-1);
    reader->setJetCut(jetCut);
    reader->setTrackCut(trackCut);
    reader->setEventCut(eventCut);
    reader->setFilters(filters);
    if (!isMC)
    {
        reader->addJECFile(JECFileDataName.Data());
        reader->setJetCollectionBranchName(jetBranchNameEmbedded.Data());
        reader->setJESCorrections();
        reader->setJEU(useJEU, JEUType);
        reader->addJEUFile(JEUFileName.Data());
    }

    manager->setEventReader(reader);

    // Dijet Analysis
    DiJetAnalysis* analysis = new DiJetAnalysis{};
    analysis->setIsMC(isMC);
    if (isPbGoing)
    {
        analysis->setIsPbGoing();
    }
    else if (!isPbGoing)
    {
        analysis->setIspGoing();
    }
    if (isMC)
    {
        analysis->setUnfolding(true, ptBins, xjBins);
        if (!isEmbedded)
        {
            analysis->setMultiplicityRange(0, 400);
            // analysis->setUseDijetWeight();
            // analysis->setDijetWeightType(dijetWeightType);
            // analysis->setDijetWeightTable(path2DijetWeight);
        }
        if (isEmbedded)
        {
            analysis->setMultiplicityRange(10, 400);
            analysis->setUseMultiplicityWeigth();
            // analysis->doTrackingClosure();
            // analysis->setUseDijetWeight();
            // analysis->setDijetWeightType(dijetWeightType);
            // analysis->setDijetWeightTable(path2DijetWeight);
        }
    }
    analysis->setMultiplicityType(0);
    analysis->setMinTrkPt(0.40);
    analysis->setDeltaPhi(5 * TMath::Pi() / 6);
    analysis->setUseCMFrame();
    analysis->setEtaBoost(etaBoost);
    analysis->setLeadJetPt(100.);
    analysis->setSubLeadJetPt(50.);
    analysis->setLeadJetEtaRange(-2.1, 2.1);
    analysis->setSubLeadJetEtaRange(-2.1, 2.1);
    analysis->setInclusiveJetEtaRange(-2.1, 2.1);
    analysis->setInclusiveCorrectedJetPtMin(50.0);
    // analysis->doInJetMultiplicity();
    analysis->setUEType(UEType);
    analysis->setTrackingTable("../aux_files/pPb_8160/trk_eff_table/pPb_EPOS_2D_efftables.root");
    // analysis->setDebug(kTRUE);
    // analysis->setVzWeight();
    // analysis->useAveragePt(true);
    analysis->setReader(reader);

    // Initialize Histomanager
    HistoManagerDiJet* hm = new HistoManagerDiJet{};
    hm->setMultiplicityBins(multiplicityBins);
    hm->setHiHFEnergyBins(hiHFBins);
    hm->setCollSystem(collSystem);
    hm->setIsMC(isMC);
    hm->setPtBins(ptBins);
    hm->setXjBins(xjBins);
    hm->init();

    analysis->addHistoManager(hm);
    manager->addAnalysis(analysis);
    manager->init();
    analysis->setNEventsInSample(reader->nEventsTotal());

    manager->performAnalysis();
    manager->finish();

    TFile* oFile = new TFile(oFileName, "RECREATE");
    hm->projectHistograms();
    hm->writeOutput();
    oFile->Close();

    return 0;
}
