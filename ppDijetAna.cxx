/**
 * @file ppDijetAnalysis.cxx
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Dijet Analyzer for ppRef Data and PYTHIA MC
 * @version 0.1
 * @date 2025-02-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "BaseAnalysis.h"
#include "DiJetAnalysis.h"
#include "Event.h"
#include "EventCut.h"
#include "ForestReader.h"
#include "HistoManagerDiJet.h"
#include "JetCut.h"
#include "Manager.h"
#include "TrackCut.h"

int main(int argc, char* argv[])
{
    Bool_t isMC{kTRUE};
    Bool_t ispPb{kFALSE};
    Bool_t useMultWeight{kFALSE};
    Bool_t useCMFrame{kFALSE};
    Double_t etaBoost{0.0};
    TString inFileName;
    TString oFileName;
    TString JECFileName;
    TString JECFileDataName;
    TString path2JEC = "..";
    Int_t collEnergyGeV{5020};
    TString collSystem{"pp"};
    Int_t collYear{2018};
    Bool_t useCentWeight{kFALSE};
    TString jetBranchName{"ak4PFJetAnalyzer"};
    std::vector<double> multiplicityBins = {0.0, 10.0, 60., 120., 185., 250., 400.};
    std::vector<double> hiHFBins = {0., 10., 20., 30., 40., 50., 70., 90., 120., 150., 1000.};
    std::vector<double> ptBins = {50.0, 55., 60., 65., 70., 80., 90., 200.};
    std::vector<double> xjBins = {0.0,  0.025, 0.05, 0.075, 0.1,  0.125, 0.15, 0.175, 0.2,  0.225, 0.25, 0.275, 0.3,  0.325,
                                  0.35, 0.375, 0.4,  0.425, 0.45, 0.475, 0.5,  0.525, 0.55, 0.575, 0.6,  0.625, 0.65, 0.675,
                                  0.7,  0.725, 0.75, 0.775, 0.8,  0.825, 0.85, 0.875, 0.9,  0.925, 0.95, 0.975, 1.0};
    // std::vector<std::string> filters{"pprimaryVertexFilter"};
    std::vector<std::string> filters{"pBeamScrapingFilter", "pPAprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose"};
    std::string path2DijetWeight = "../aux_files/pp_5020/Dijet_Weight/PYTHIA_DiJetWeight_Table.root";
    std::string dijetWeightType{"Gen"};

    if (argc <= 1)
    {
        std::cerr << "Too few arguments passed. Terminating !" << std::endl;
        std::cerr << "Usage: " << "./ppDijetAna inputFileList outputFileName isMC" << std::endl;
        return -1;
    }

    inFileName = argv[1];
    oFileName = argv[2];
    isMC = atoi(argv[3]);
    collEnergyGeV = atoi(argv[4]);

    if (collEnergyGeV == 5360)
    {
        collYear = 2025;
    }
    else
    {
        collYear = 2018;
    }

    if (isMC)
    {
        if (collYear == 2025)
        {
            JECFileName = "2024ppRef_withPU_L2Relative_AK4PF.txt";
        }
        else
        {
            JECFileName = "Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt";
        }
    }
    else
    {
        if (collYear == 2025)
        {
            JECFileName = "2024ppRef_withPU_L2Relative_AK4PF.txt";
        }
        else
        {
            JECFileName = "Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt";
            JECFileDataName = "Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txt";
        }
    }

    // Initialize package manager
    Manager* manager = new Manager{};

    // Initialize event cuts
    EventCut* eventCut = new EventCut{};
    eventCut->setVz(-15., 15.);
    eventCut->setMultiplicty(0, 10000);
    // if (isMC)
    // {
    //     eventCut->setPtHat(10., 10000.);
    // }
    // eventCut->setVerbose();

    // Initialize jet cuts
    JetCut* jetCut = new JetCut{};
    jetCut->setEta(-5.0, 5.0);
    jetCut->setPt(0., 5360.);
    // jetCut->setVerbose();

    // Initialize track cuts
    TrackCut* trackCut = new TrackCut{};
    trackCut->setPt(0.5, 1000.);
    trackCut->setEta(-2.4, 2.4);
    trackCut->setPtErr(0.1);
    trackCut->setDXY(3.0);
    trackCut->setDZ(3.0);
    trackCut->setHighPurity();

    ForestReader* reader = new ForestReader{inFileName};
    reader->setForestFileType(ForestReader::ForestFileType::MiniAOD);
    if (isMC)
    {
        reader->setIsMc(isMC);
        if (collEnergyGeV == 5360)
        {
            reader->setStoreLocation(kTRUE);
        }
        // reader->useGenTrackBranch();
    }

    // reader->useTrackBranch();
    reader->useJets();
    reader->setJetCollectionBranchName(jetBranchName.Data());
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(ForestReader::CollidingSystemType::pp);
    reader->setYearOfDataTaking(collYear);
    reader->setUseJetID();
    reader->setJetIDType(2);
    reader->addJECFile(JECFileName.Data());
    if (!isMC)
    {
        // reader->addJECFile(JECFileDataName.Data());
        // reader->setStoreLocation(kTRUE);
        reader->useSkimmingBranch();
        reader->setFilters(filters);
        if (collEnergyGeV == 5360)
        {
            filters.clear();
            filters.push_back("pprimaryVertexFilter");
            reader->setFilters(filters);
            reader->setStoreLocation(true);
        }
    }
    if (isMC && collEnergyGeV == 5020)
    {
        reader->useSkimmingBranch();
        reader->setFilters(filters);
    }
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setTrackCut(trackCut);
    reader->setJetCut(jetCut);
    reader->setEventCut(eventCut);
    reader->eventsToProcess(-1);

    manager->setEventReader(reader);

    HistoManagerDiJet* hm = new HistoManagerDiJet{};
    hm->setIsMC(isMC);
    hm->setMultiplicityBins(multiplicityBins);
    hm->setCollSystem(collSystem);
    hm->setHiHFEnergyBins(hiHFBins);
    hm->setPtBins(ptBins);
    hm->setXjBins(xjBins);
    hm->init();

    // Initialize analysis
    DiJetAnalysis* analysis = new DiJetAnalysis{};
    analysis->addHistoManager(hm);
    analysis->setReader(reader);
    analysis->setIsMC(isMC);
    analysis->setLeadJetEtaRange(-2.1, 2.1);
    analysis->setSubLeadJetEtaRange(-2.1, 2.1);
    analysis->setMultiplicityRange(0., 10000.);
    analysis->setMultiplicityType(0);
    analysis->setLeadJetPt(60.);
    analysis->setSubLeadJetPt(40.);
    analysis->setDeltaPhi(2.7);
    analysis->setInclusiveCorrectedJetPtMin(20.);
    analysis->setInclusiveJetEtaRange(-2.1, 2.1);
    analysis->setMinTrkPt(0.5);
    analysis->setTrkEtaRange(-2.4, 2.4);
    analysis->doInJetMultiplicity();
    if (isMC)
    {
        analysis->setUnfolding(true, ptBins, xjBins);
    }

    // if (isMC)
    // {
    //     analysis->setUseDijetWeight();
    //     analysis->setDijetWeightType(dijetWeightType);
    //     analysis->setDijetWeightTable(path2DijetWeight);
    // }

    manager->addAnalysis(analysis);
    manager->init();
    manager->performAnalysis();
    manager->finish();

    TFile* outFile = new TFile{oFileName, "RECREATE"};
    hm->projectHistograms();
    hm->writeOutput();
    outFile->Close();

    return 0;
}