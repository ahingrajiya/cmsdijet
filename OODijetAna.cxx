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
    std::cout << "./programName inputFileList oFileName isMC isEmbedded \n";
}
int main(int argc, char* argv[])
{
    Bool_t isMC{kTRUE};
    TString inFileName;
    Int_t collEnergyGeV{5360};
    TString collSystem{"OO"};
    Int_t collYear{2025};
    Bool_t useCentWeight{kFALSE};
    Bool_t useMultWeight{kFALSE};
    TString jetBranchNameEmbedded{"akCs4PFJetAnalyzer"};
    TString jetBranchNameUnembedded{"ak4PFJetAnalyzer"};
    std::string dijetWeightType{"Gen"};
    TString oFileName{};
    TString JECFileName{};
    TString JECFileDataName{};
    TString JEUFileName{};
    TString path2JEC = "..";
    Double_t ptHatCut[2]{15., 10000.};
    Bool_t isEmbedded{kTRUE};
    bool unfold = true;
    // std::vector<std::pair<double, double>> multiplicityBins = {{0, 0.0}, {10, 1.0}, {60, 2.0}, {120, 3.0}, {185, 4.0}, {250, 5.0}, {400, 6.0}, {500, 7.0}};
    std::vector<double> multiplicityBins = {0.0, 10., 20., 30., 40., 50., 60., 70., 80., 90., 100., 110., 120., 130., 140., 150., 160., 170., 180., 190., 200.};
    std::vector<double> hiHFBins = {0., 10., 20., 30., 40., 50., 70., 90., 120., 150., 180., 210., 250., 300., 350., 400., 450., 500., 550., 1000.};
    std::vector<double> ptBins = {50.0, 55., 60., 65., 70., 80., 90., 200.};
    std::vector<double> xjBins = {0.0,  0.025, 0.05, 0.075, 0.1,  0.125, 0.15, 0.175, 0.2,  0.225, 0.25, 0.275, 0.3,  0.325,
                                  0.35, 0.375, 0.4,  0.425, 0.45, 0.475, 0.5,  0.525, 0.55, 0.575, 0.6,  0.625, 0.65, 0.675,
                                  0.7,  0.725, 0.75, 0.775, 0.8,  0.825, 0.85, 0.875, 0.9,  0.925, 0.95, 0.975, 1.0};
    std::vector<std::string> filters{"pprimaryVertexFilter", "pphfCoincFilter2Th4"};  // pphfCoincFilterPF2Th4 pphfCoincFilter2Th4
    std::vector<std::string> filtersmc{"pprimaryVertexFilter"};
    std::string UEType{"HIJING"};
    Int_t smearType{0};             // 0 - Nominal Smearing, 1 - JER Smearing, 2 - JEC Smearing
    Bool_t useJERSmearing{kFALSE};  // Use JER Smearing for MC
    Bool_t useJEU{kFALSE};          // 0 - No JEC Uncertainty, 1 - JEC Uncertainty Up, -1 - JEC Uncertainty Down
    Int_t JEUType{-1};              // 0 - No JEU, 1 - JEU Up, -1 - JEU Down
    // Command line arguments
    /*
    inputFileList               - input file list with forest file paths
    outputFileName.root         - Output file name
    isMC                        - if it is Monte Carlo or Data
    isPbGoing                   - If it is PbGoing side or pGoing Side
    ptHatLow                    - Low PtHat cut (For MC Only)
    ptHatHigh                   - High PtHat cut (For MC Only)
    */

    if (argc <= 4)
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
    }

    if (isMC)
    {
        JECFileName = "Winter25Prompt25_V1_MC_L2Relative_AK4PFPuppi.txt";
    }

    else
    {
        JECFileName = "Winter25Prompt25_V1_MC_L2Relative_AK4PFPuppi.txt";
        // JECFileDataName = "Summer16_23Sep2016HV4_DATA_L2L3Residual_AK4PF.txt";
        // JEUFileName = "Summer16_23Sep2016HV4_DATA_Uncertainty_AK4PF.txt";
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
    jetCut->setPt(0., 5360.);
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
    reader->setForestFileType(ForestReader::ForestFileType::MiniAOD);
    reader->setIsSkim(true);
    reader->setIsMc(isMC);

    if (isMC)
    {
        // reader->useGenTrackBranch();
        reader->setFilters(filtersmc);
        // reader->setStoreLocation(kTRUE);

        if (isEmbedded)
        {
            reader->setJetCollectionBranchName(jetBranchNameEmbedded.Data());
            reader->setMatchedJets();
        }
        else
        {
            reader->setJetCollectionBranchName(jetBranchNameUnembedded.Data());
            // reader->useTrackBranch();
        }
    }
    if (!isMC)
    {
        reader->setFilters(filters);
    }
    reader->useSkimmingBranch();
    reader->useJets();
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(ForestReader::CollidingSystemType::OO);
    reader->setYearOfDataTaking(collYear);
    reader->addJECFile(JECFileName.Data());
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setUseJetID();
    reader->setJetIDType(2);
    reader->eventsToProcess(-1);
    reader->setJetCut(jetCut);
    reader->setTrackCut(trackCut);
    reader->setEventCut(eventCut);
    if (!isMC)
    {
        reader->setJetCollectionBranchName(jetBranchNameEmbedded.Data());
        reader->setFilters(filters);
    }

    manager->setEventReader(reader);

    // Dijet Analysis
    DiJetAnalysis* analysis = new DiJetAnalysis{};
    analysis->setIsMC(isMC);

    analysis->setReader(reader);
    analysis->setMultiplicityRange(10, 500);
    analysis->setMultiplicityType(4);
    analysis->setMinTrkPt(0.40);
    analysis->setDeltaPhi(2.7);
    analysis->setLeadJetPt(60.);
    analysis->setSubLeadJetPt(40.);
    analysis->setLeadJetEtaRange(-2.1, 2.1);
    analysis->setSubLeadJetEtaRange(-2.1, 2.1);
    analysis->setUEType(UEType);
    analysis->setInclusiveCorrectedJetPtMin(20.);
    analysis->setInclusiveJetEtaRange(-2.1, 2.1);
    analysis->useAveragePt(false);
    if (isMC)
    {
        // analysis->setUseCentralityWeight();
        analysis->setUnfolding(unfold, ptBins, xjBins);
    }
    // Initialize Histomanager
    HistoManagerDiJet* hm = new HistoManagerDiJet{};
    hm->setMultiplicityBins(multiplicityBins);
    hm->setHiHFEnergyBins(hiHFBins);
    hm->setPtBins(ptBins);
    hm->setXjBins(xjBins);
    hm->setCollSystem(collSystem);
    hm->setIsMC(isMC);
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
