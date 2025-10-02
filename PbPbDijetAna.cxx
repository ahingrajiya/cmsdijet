/**
 * @file PbPbDijetAna.cxx
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Dijet Analysis for the PbPb dataset
 * @version 0.1
 * @date 2024-10-14
 *
 * @copyright Copyright (c) 2024
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
    TString collSystem{"PbPb"};
    Int_t collYear{2018};
    Bool_t useCentWeight{kFALSE};
    TString jetBranchName{"akCs4PFJetAnalyzer"};
    Double_t ptHatCut[2]{15., 30.};
    // std::vector<std::pair<Int_t, Double_t>> multiplicityBins = {{10, 0.0}, {60, 1.0}, {120, 2.0}, {185, 3.0}, {250, 4.0}, {400, 5.0}};
    std::vector<std::pair<Int_t, Double_t>> multiplicityBins = {{-10, 0.0}, {0, 1.}, {20, 2.0}, {60, 3.0}, {100, 4.0}, {160, 5.0}, {180, 6.0}, {200, 7.0}};
    std::vector<std::string> filters{"collisionEventSelectionAOD", "phfCoincFilter2Th4", "pclusterCompatibilityFilter", "pprimaryVertexFilter",
                                     "HBHENoiseFilterResultRun2Loose"};
    std::vector<std::string> triggers{"HLT_HIPuAK4CaloJet80Eta5p1_v1"};
    std::string path2MultWeight = "../aux_files/PbPb_5020/Multiplicity_Weight/mult_weight_1p0.root";
    std::string path2DijetWeight = "../aux_files/pp_5020/Dijet_Weight/PYTHIA_DiJetWeight_Table.root";
    std::string dijetWeightType{"Gen"};

    if (argc <= 1)
    {
        std::cerr << "Too few arguments passed. Terminating !" << std::endl;
        std::cerr << "Usage: " << "./PbPbDijetAna inputFileList outputFileName isMC" << std::endl;
        return -1;
    }

    inFileName = argv[1];
    oFileName = argv[2];
    isMC = atoi(argv[3]);

    if (isMC)
    {
        JECFileName = "Autumn18_HI_V8_MC_L2Relative_AK4PF.txt";
    }
    else
    {
        JECFileName = "Autumn18_HI_V8_MC_L2Relative_AK4PF.txt";
        JECFileDataName = "Autumn18_HI_V8_DATA_L2L3Residual_AK4PF.txt";
    }

    // Initialize analysis manager
    Manager* manager = new Manager{};

    // Initialize event cuts
    EventCut* eventCut = new EventCut{};
    eventCut->setVz(-15., 15.);
    eventCut->setMultiplicty(0, 10000);
    if (isMC)
    {
        eventCut->setPtHat(30., 1000.);
    }
    eventCut->setHiBin(0, 200);
    // eventCut->setVerbose();
    JetCut* jetCut = new JetCut{};
    jetCut->setPt(0., 1000.);
    jetCut->setEta(-5., 5.);

    // Initialize track cuts
    TrackCut* trackCut = new TrackCut{};
    trackCut->setPt(0.5, 1000.);
    trackCut->setEta(-2.4, 2.4);
    trackCut->setPtErr(0.1);
    trackCut->setDXY(3.0);
    trackCut->setDZ(3.0);
    trackCut->setHighPurity();
    trackCut->setCharge();
    trackCut->setNHits();
    trackCut->setChi2();
    trackCut->setCaloMatching();
    trackCut->setMVAAlgo();
    // trackCut->setVerbose();

    ForestReader* reader = new ForestReader{inFileName};
    reader->setForestFileType(ForestReader::ForestFileType::AOD);
    if (isMC)
    {
        reader->setIsMc(isMC);
        reader->useGenTrackBranch();
        reader->setShiftInHiBin(-10);
        // reader->setStoreLocation(kTRUE);
    }
    reader->useSkimmingBranch();
    reader->useTrackBranch();
    reader->useJets();
    reader->useHltBranch();
    reader->setTriggers(triggers);
    reader->setFilters(filters);
    reader->setJetCollectionBranchName(jetBranchName.Data());
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(ForestReader::CollidingSystemType::PbPb);
    reader->setYearOfDataTaking(collYear);
    reader->addJECFile(JECFileName.Data());
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setUseJetID();
    reader->setJetIDType(1);
    reader->eventsToProcess(-1);
    reader->setEventCut(eventCut);
    reader->setJetCut(jetCut);
    reader->setTrackCut(trackCut);
    if (!isMC)
    {
        reader->addJECFile(JECFileDataName.Data());
    }
    manager->setEventReader(reader);

    HistoManagerDiJet* hm = new HistoManagerDiJet{};
    hm->setIsMC(isMC);
    hm->setMultiplicityBins(multiplicityBins);
    hm->setCollSystem(collSystem);
    hm->init();

    DiJetAnalysis* analysis = new DiJetAnalysis{};
    analysis->setReader(reader);
    analysis->addHistoManager(hm);
    analysis->setIsMC(isMC);
    analysis->setLeadJetEtaRange(-1.6, 1.6);
    analysis->setSubLeadJetEtaRange(-1.6, 1.6);
    analysis->setMultiplicityRange(0., 10000.);
    analysis->setMultiplicityType(4);
    analysis->setDeltaPhi(2. * TMath::Pi() / 3);
    analysis->setLeadJetPt(100.);
    analysis->setSubLeadJetPt(50.);
    analysis->setTrackingTable("../PbPb_TrackingEfficiencies/");
    analysis->setMinTrkPt(1.0);
    analysis->setTrkEtaRange(-2.4, 2.4);
    analysis->doInJetMultiplicity();
    analysis->setBins(multiplicityBins);
    analysis->setInclusiveCorrectedJetPtMin(50.);
    analysis->setInclusiveJetEtaRange(-1.6, 1.6);

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