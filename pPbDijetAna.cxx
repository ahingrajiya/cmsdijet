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
#include "ForestAODReader.h"
#include "DiJetAnalysis.h"
#include "HistoManagerDiJet.h"
#include "Manager.h"
#include "EventCut.h"
#include "TrackCut.h"
#include "JetCut.h"

// ROOT headers
#include "TFile.h"
#include "TMath.h"

using namespace std;

void usage()
{
    std::cout << "./programName inputFileList oFileName isMC isEmbedded isPbGoing ptHatLow ptHatHi \n";
}
int main(int argc, char *argv[])
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
    TString jetBranchName{"akCs4PFJetAnalyzer"};
    std::string dijetWeightType{"Gen"};
    TString oFileName{};
    TString JECFileName{};
    TString JECFileDataName{};
    TString path2JEC = "..";
    Double_t ptHatCut[2]{15., 30.};
    Bool_t isEmbedded{kTRUE};
    std::vector<float> multiplicityBins{-1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::string path2DijetWeight = "../aux_files/pPb_8160/Dijet_Weight/DijetWeight10_New.root";

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
    }

    // Initialize package manager
    Manager *manager = new Manager{};

    // Initialize event cuts
    EventCut *eventCut = new EventCut{};
    eventCut->setVz(-15., 15.);
    eventCut->useHBHENoiseFilterResultRun2Loose();
    eventCut->usePBeamScrapingFilter();
    eventCut->usePvertexFilterCutdz1p0();
    eventCut->usePPAprimaryVertexFilter();
    eventCut->usePhfCoincFilter2Th4();
    eventCut->setMultiplicty(10, 400);
    if (isMC && !isEmbedded)
    {
        eventCut->setMultiplicty(0, 400);
    }
    if (isMC)
    {
        eventCut->setPtHat(ptHatCut[0], ptHatCut[1]);
    }
    // eventCut->setVerbose();

    // Initialize jet cuts
    JetCut *jetCut = new JetCut{};
    jetCut->setEta(-5.0, 5.0);
    jetCut->setPt(0., 8160.);
    // jetCut->setVerbose();

    // Initiazlize Track Cuts

    TrackCut *trackCut = new TrackCut{};
    trackCut->setPt(0.4, 1000.);
    trackCut->setEta(-2.4, 2.4);
    trackCut->setPtErr(0.1);
    trackCut->setDXY(3.0);
    trackCut->setDZ(3.0);
    trackCut->setHighPurity();
    trackCut->setCharge();
    // trackCut->setVerbose();

    // Initialize Forest Reader

    ForestAODReader *reader = new ForestAODReader{inFileName};
    if (isMC)
    {
        reader->setIsMc(isMC);
    }
    // reader->useHltBranch();
    reader->useSkimmingBranch();
    reader->useTrackBranch();
    reader->useJets();
    reader->setJetCollectionBranchName(jetBranchName.Data());
    reader->setCollidingEnergy(collEnergyGeV);
    reader->setCollidingSystem(collSystem.Data());
    reader->setYearOfDataTaking(collYear);
    reader->addJECFile(JECFileName.Data());
    reader->setPath2JetAnalysis(path2JEC.Data());
    reader->setUseJetID();
    reader->setJetIDType(2);
    // reader->setMatchedJets();
    if (isMC)
    {
        reader->useGenTrackBranch();
    }
    reader->eventsToProcess(-1);
    reader->setJetCut(jetCut);
    reader->setTrackCut(trackCut);
    reader->setEventCut(eventCut);
    if (!isMC)
    {
        reader->addJECFile(JECFileDataName.Data());
    }

    manager->setEventReader(reader);

    // Dijet Analysis
    DiJetAnalysis *analysis = new DiJetAnalysis{};
    analysis->setIsMC(isMC);
    analysis->setIspPb();
    if (isPbGoing)
    {
        analysis->setIsPbGoing();
    }
    else if (!isPbGoing)
    {
        analysis->setIspGoing();
    }
    analysis->setMultiplicityRange(10, 400);
    if (isMC)
    {
        analysis->setUseDijetWeight();
        analysis->setDijetWeightType(dijetWeightType);
        analysis->setDijetWeightTable(path2DijetWeight);
        if (!isEmbedded)
        {
            analysis->setMultiplicityRange(0, 400);
        }
    }
    analysis->setMultiplicityType(0);
    analysis->setMinTrkPt(1.0);
    analysis->setDeltaPhi(5 * TMath::Pi() / 6);
    analysis->setUseCMFrame();
    analysis->setEtaBoost(etaBoost);
    analysis->setLeadJetPt(100.);
    analysis->setSubLeadJetPt(50.);
    analysis->setLeadJetEtaRange(-2.4, 2.4);
    analysis->setSubLeadJetEtaRange(-2.4, 2.4);
    analysis->doInJetMultiplicity();

    // analysis->setVerbose();

    analysis->setTrackingTable("../aux_files/pPb_8160/trk_eff_table/Hijing_8TeV_dataBS.root");
    // Initialize Histomanager
    HistoManagerDiJet *hm = new HistoManagerDiJet{};
    hm->setMultiplicityBins(multiplicityBins);
    hm->setIsMC(isMC);
    hm->init();

    analysis->addHistoManager(hm);
    manager->addAnalysis(analysis);
    manager->init();
    analysis->setNEventsInSample(reader->nEventsTotal());

    manager->performAnalysis();
    manager->finish();

    TFile *oFile = new TFile(oFileName, "RECREATE");
    hm->projectHistograms();
    hm->writeOutput();
    oFile->Close();

    return 0;
}
