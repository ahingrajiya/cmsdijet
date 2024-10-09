/**
 * @file HistoManagerDiJet.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Manager for Dijet Analysis
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HistoManagerDiJet_h
#define HistoManagerDiJet_h

// Jet Analysis headers

#include "BaseHistoManager.h"

// ROOT Headers

#include "TObject.h"
#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THnSparse.h"
#include "TProfile.h"
#include "TMath.h"
#include "TString.h"
#include "TDirectory.h"

class HistoManagerDiJet : public BaseHistoManager
{
public:
    ///@brief Constructor
    HistoManagerDiJet();
    ///@brief Destructor
    virtual ~HistoManagerDiJet();

    ///@brief Initialize Histograms
    void init(const Bool_t &isMC = kFALSE);
    ///@brief Use MC histograms
    void setIsMC(const Bool_t &isMC = kTRUE) { fIsMC = isMC; }
    ///@brief Write all historgams to output file
    void writeOutput(const Bool_t &isMC = kFALSE);
    ///@brief Set Multiplicity bins
    void setMultiplicityBins(const std::vector<float> &bins) { fMultiplicityBins = bins; }

    TH1D *hRecoMultiplicity;
    TH1D *hCorrectedMultiplicity;
    TH1D *hGenMultiplicity;
    TH1D *hSubEventMultiplicity;
    TH1D *hSelectedMultiplicity;
    TH1D *hPtHat;
    TH1D *hPtHat_W;
    TH1D *hHiBin;
    TH1D *hHiBin_W;
    TH1D *hVz;
    TH1D *hVz_W;

    THnSparseD *hMultiplicities;
    THnSparseD *hMultiplicities_W;
    THnSparseD *hRecoJets;
    THnSparseD *hRecoJets_W;
    THnSparseD *hGenJets;
    THnSparseD *hGenJets_W;
    THnSparseD *hLeadingJet;
    THnSparseD *hSubLeadingJet;
    THnSparseD *hMultiplicities_DiJet_W;

    THnSparseD *hRecoQuenching_W;
    THnSparseD *hGenQuenching_W;

private:
    Bool_t fIsMC;

    std::vector<float> fMultiplicityBins;

    ClassDef(HistoManagerDiJet, 0)
};

#endif