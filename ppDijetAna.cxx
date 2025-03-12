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

#include "HistoManagerDiJet.h"
#include "JetCut.h"
#include "EventCut.h"
#include "BaseAnalysis.h"
#include "JetCut.h"
#include "Event.h"
#include "ForestminiAODReader.h"
#include "TrackCut.h"
#include "Manager.h"
#include "DiJetAnalysis.h"

int main(int argc, char *argv[])
{
    Bool_t isMC{kTRUE};
    Bool_t ispPb{kFALSE};
    TString inFileName;
    TString oFileName;
    TString JECFileName;
    TString JECFileDataName;
    TString path2JEC = "..";
    Int_t collEnergyGeV{5020};
    TString collSystem{"pp"};
    Int_t collYear{2018};
    TString jetBranchName{"ak4PFJetAnalyzer"};
    std::vector<std::pair<Int_t, Double_t>> multiplicityBins = {{10, 0.0}, {60, 1.0}, {120, 2.0}, {185, 3.0}, {400, 4.0}};
    std::vector<std::string> filters{"pPAprimaryVertexFilter", "pBeamScrapingFilter", "HBHENoiseFilterResultRun2Loose"};

    if (argc <= 1)
    {
        std::cerr << "Too few arguments passed. Terminating !" << std::endl;
        std::cerr << "Usage: " << "./ppDijetAna inputFileList outputFileName isMC" << std::endl;
        return -1;
    }

    inFileName = argv[1];
    oFileName = argv[2];
    isMC = atoi(argv[3]);

    if (isMC)
    {
        JECFileName = "Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt";
    }
    else
    {

        JECFileName = "Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt";
        JECFileDataName = "Spring18_ppRef5TeV_V6_DATA_L2L3Residual_AK4PF.txtt";
    }

    // Initialize package manager
    Manager *manager = new Manager{};

    // Initialize event cuts
    EventCut *eventCut = new EventCut{};
    eventCut->setVz(-15., 15.);
    if (isMC)
    {
        eventCut->setPtHat(30., 1000.);
    }
    eventCut->usePPAprimaryVertexFilter();
    eventCut->usePBeamScrapingFilter();
    eventCut->useHBHENoiseFilterResultRun2Loose();
    // eventCut->setVerbose();

    // Initialize jet cuts
    JetCut *jetCut = new JetCut{};
    jetCut->setEta(-5.0, 5.0);
    jetCut->setPt(0., 5020.);
    // jetCut->setVerbose();

    // Initialize track cuts
    TrackCut *trackCut = new TrackCut{};
    trackCut->setPt(0.5, 1000.);
    trackCut->setEta(-2.4, 2.4);
    trackCut->setPtErr(0.1);
    trackCut->setDXY(3.0);
    trackCut->setDZ(3.0);
    trackCut->setHighPurity();

    ForestAODReader *reader = new ForestAODReader{inFileName};
    if (isMC)
    {
        reader->setIsMc(isMC);
        reader->useGenTrackBranch();
    }
    reader->useSkimmingBranch();
    reader->useTrackBranch();
    reader->useJets();
    reader->setJetCollectionBranchName(jetBranchName.Data());
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(collSystem.Data());
    reader->setYearOfDataTaking(collYear);
    reader->setUseJetID();
    reader->setJetIDType(2);
    reader->addJECFile(JECFileName.Data());
    if (!isMC)
    {
        reader->addJECFile(JECFileDataName.Data());
    }
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setTrackCut(trackCut);
    reader->setJetCut(jetCut);
    reader->setEventCut(eventCut);
    reader->eventsToProcess(-1);

    manager->setEventReader(reader);

    HistoManagerDiJet *hm = new HistoManagerDiJet{};
    hm->setIsMC(isMC);
    hm->setMultiplicityBins(multiplicityBins);
    hm->setCollSystem(collSystem);
    hm->init();

    // Initialize analysis
    DiJetAnalysis *analysis = new DiJetAnalysis{};
    analysis->addHistoManager(hm);
    analysis->setIsMC(isMC);
    analysis->setLeadJetEtaRange(-1.5, 1.5);
    analysis->setSubLeadJetEtaRange(-1.5, 1.5);
    analysis->setMultiplicityRange(0., 10000.);
    analysis->setMultiplicityType(0);
    analysis->setLeadJetPt(100.);
    analysis->setSubLeadJetPt(40.);
    analysis->setDeltaPhi(2. * TMath::Pi() / 3);
    analysis->setMinTrkPt(0.5);
    analysis->setTrkEtaRange(-2.4, 2.4);
    analysis->doInJetMultiplicity();
    analysis->setBins(multiplicityBins);
    analysis->setCollSystem(collSystem);
    analysis->init();

    manager->addAnalysis(analysis);
    manager->init();
    manager->performAnalysis();
    manager->finish();

    TFile *outFile = new TFile{oFileName, "RECREATE"};
    hm->projectHistograms();
    hm->writeOutput();
    outFile->Close();

    return 0;
}