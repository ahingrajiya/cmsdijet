
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>

#include "../../Unfoilding/build/RooUnfoldBayes.h"
#include "../../Unfoilding/build/RooUnfoldResponse.h"
#endif

#include "../interface/Unfolding.h"

// gSystem->Load("../build/libJetAnalysis.so");
#include "../interface/Unfolding.h"

int main()
{
    Unfolding unfoldData;

    std::vector<double> xjBins = {0.0,  0.025, 0.05, 0.075, 0.1,  0.125, 0.15, 0.175, 0.2,  0.225, 0.25, 0.275, 0.3,  0.325,
                                  0.35, 0.375, 0.4,  0.425, 0.45, 0.475, 0.5,  0.525, 0.55, 0.575, 0.6,  0.625, 0.65, 0.675,
                                  0.7,  0.725, 0.75, 0.775, 0.8,  0.825, 0.85, 0.875, 0.9,  0.925, 0.95, 0.975, 1.0};

    // std::vector<double> multiplicityBins = {0.0, 20., 40., 80., 120.};
    std::vector<double> multiplicityBins = {0.0, 100.};
    std::vector<double> ptBins = {0.0, 20.0, 30.0, 40.0, 50.0, 60., 70., 80., 90., 100., 120., 140., 160., 200.};

    unfoldData.setBins(ptBins, xjBins, multiplicityBins, multiplicityBins);
    unfoldData.initialize("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA5360_Unfolding_Data.root",
                          "/home/abhishek/analysis/pPb/Summed_Files/ppRef5360_Unfolding_Data.root");
    unfoldData.outputFileName("ppRef_Data_Unfolded_3iter.root");
    unfoldData.setIterations(3);

    unfoldData.doValidation(false);
    unfoldData.performUnfolding();

    Unfolding unfoldOOData;
    std::vector<double> centBins = {0.0, 20.0, 40.0, 80.0, 120.0, 160.0, 200.};

    unfoldOOData.setBins(ptBins, xjBins, centBins, centBins);
    unfoldOOData.initialize("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA_HIJING_Unfolding_Data.root",
                            "/home/abhishek/analysis/pPb/Summed_Files/OOData_Unfolding_Data.root");
    unfoldOOData.outputFileName("OOData_Unfold_3iter.root");
    unfoldOOData.setIterations(3);
    unfoldOOData.doValidation(false);
    unfoldOOData.performUnfolding();

    // Unfolding unfoldpPbData;

    // unfoldpPbData.setBins(ptBins, xjBins, multiplicityBins, multiplicityBins);
    // unfoldpPbData.initialize("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA_EPOS_Unfolding_Data.root",
    //                          "/home/abhishek/analysis/pPb/Summed_Files/pPbMB_Unfolding_Data.root");
    // unfoldpPbData.outputFileName("pPbMBData_Unfold_3iter.root");
    // unfoldpPbData.setIterations(3);
    // unfoldpPbData.doValidation(false);
    // unfoldpPbData.performUnfolding();

    // std::vector<double> multiplicityBinsHM185 = {0., 100.};

    // Unfolding unfoldpPbHM185Data;

    // unfoldpPbHM185Data.setBins(ptBins, xjBins, multiplicityBinsHM185, multiplicityBins);
    // unfoldpPbHM185Data.initialize("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA_EPOS_Unfolding_Data.root",
    //                               "/home/abhishek/analysis/pPb/Summed_Files/pPbHM185_Unfolding_Data.root");
    // unfoldpPbHM185Data.outputFileName("pPbHM185Data_Unfold_3iter.root");
    // unfoldpPbHM185Data.setIterations(3);
    // unfoldpPbHM185Data.doValidation(false);
    // unfoldpPbHM185Data.performUnfolding();

    // std::vector<double> multiplicityBinsHM250 = {0.0, 100.};

    // Unfolding unfoldpPbHM250Data;

    // unfoldpPbHM250Data.setBins(ptBins, xjBins, multiplicityBinsHM250, multiplicityBins);
    // unfoldpPbHM250Data.initialize("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA_EPOS_Unfolding_Data.root",
    //                               "/home/abhishek/analysis/pPb/Summed_Files/pPbHM250_Unfolding_Data.root");
    // unfoldpPbHM250Data.outputFileName("pPbHM250Data_Unfold_3iter.root");
    // unfoldpPbHM250Data.setIterations(3);
    // unfoldpPbHM250Data.doValidation(false);
    // unfoldpPbHM250Data.performUnfolding();

    return 0;
}