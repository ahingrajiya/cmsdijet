/**
 * @file Unfolding.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Unfolding  of data
 * @version 0.1
 * @date 2026-06-18
 *
 * @copyright Copyright (c) 2026
 *
 */

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>

#include "../../Unfoilding/RooUnfold/build/RooUnfoldBayes.h"
#include "../../Unfoilding/RooUnfold/build/RooUnfoldResponse.h"
#endif

#ifndef UNFOLDING_H
#define UNFOLDING_H

#include "common.hpp"

class RooUnfoldResponse;

class Unfolding
{
   public:
    Unfolding(/* args */);
    virtual ~Unfolding();

    void doValidation(bool validation) { performValidation = validation; }

    void setBins(std::vector<double> ptBins, std::vector<double> xjBins, std::vector<double> multCentBins)
    {
        fPtBins = ptBins;
        fXjBins = xjBins;
        fMultCentBins = multCentBins;
    }

    void setIterations(int iter) { iterations = iter; }

    void initialize(TString fileInMC, TString fileInData)
    {
        if (fileInMC.IsNull())
        {
            std::runtime_error("No MC File. Can not perform Unfolding!");
        }
        fMCIn = TFile::Open(fileInMC, "READ");

        if (!fileInData.IsNull())
        {
            fDataIn = TFile::Open(fileInData, "READ");
        }
    }

    void outputFileName(TString fileOut) { outputFile = fileOut; }

    void performUnfolding();

   private:
    std::vector<TH1D*> unflattenHistogram(std::vector<double> ptBins, std::vector<double> xjBins, TH1D* flattenedHist, std::string name);

    TH1D* unfold(RooUnfoldResponse* response, TH1D* measured, TH1D* hPurity, TH1D* hEfficiency, int iteration);

    TH1D* purity(TH1D* totalReco, TH1D* matchedReco);

    TH1D* efficiency(TH1D* totalGen, TH1D* matchedGen);

    void readHistograms(TFile* inputMC, TFile* dataMac, bool validation = true);

    void projections(bool validation, float centMin, float centMax);

    void writeHisto(TFile* out, std::vector<TH1D*> histos);
    std::vector<double> fPtBins;
    std::vector<double> fXjBins;
    std::vector<double> fMultCentBins;

    bool performValidation = false;
    TString outputFile{""};

    TFile* fDataIn{nullptr};
    TFile* fMCIn{nullptr};
    TFile* fOut{nullptr};
    TH3D* hResponseMatrix3D[2]{nullptr};
    TH2D* hResponseMatrix[2]{nullptr};
    TH2D* hTotalTruth2D[2]{nullptr};
    TH1D* hTotalTruth[2]{nullptr};
    TH2D* hTotalReco2D[2]{nullptr};
    TH1D* hTotalReco[2]{nullptr};
    TH2D* hDataReco2D{nullptr};
    TH1D* hDataReco{nullptr};
    TH1D* hMatchedReco[2]{nullptr};
    TH1D* hMatchedTruth[2]{nullptr};
    TH1D* hPurity[2]{nullptr};
    TH1D* hEfficiency[2]{nullptr};
    int iterations = 1;
};

#endif
