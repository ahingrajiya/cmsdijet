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

#include "../../Unfoilding/build/RooUnfoldBayes.h"
#include "../../Unfoilding/build/RooUnfoldResponse.h"
#endif

#ifndef UNFOLDING_H
#define UNFOLDING_H

#include "common.hpp"

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

    void initialize(TFile* fileIn, TFile* fileOut);

   private:
    std::vector<TH1D*> unflattenHistogram(std::vector<double> ptBins, std::vector<double> xjBins, TH1D* flattenedHist, std::string name);

    TH1D* performUnfolding(RooUnfoldResponse* response, TH1D* measured, TH1D* hPurity, TH1D* hEfficiency, int iteration);

    bool performValidation = false;

    std::vector<double> fPtBins;
    std::vector<double> fXjBins;
    std::vector<double> fMultCentBins;
};

#endif
