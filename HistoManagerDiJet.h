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

    TH1D *hRecoMultiplicity_W;
    TH1D *hCorrectedMultiplicity_W;
    TH1D *hGenMultiplicity_W;
    TH1D *hSubEventMultiplicity_W;
    TH1D *hSelectedMultiplicity_W;
    TH1D *hPtHat;
    TH1D *hPtHat_W;
    TH1D *hHiBin;
    TH1D *hHiBin_W;
    TH1D *hVz;
    TH1D *hVz_W;
    TH1D *hVzWithDijet_W;
    TH1D *hDeltaPhi_W;
    TH1D *hGenDeltaPhi_W;
    TH1D *hXj_W;
    TH1D *hGenXj_W;
    TH1I *hNDijetEvent;
    TH1D *hNGenDijetEvent;
    TH1D *hNEventsInMult;

    TH2D *hInJetMultiplicity_W;
    TH2D *hGenInJetMultiplicity_W;

    TH2D *hLeadPtvsSubLeadPt;
    TH2D *hLeadPtvsSubLeadPt_W;
    TH2D *hGenLeadPtvsGenSubLeadPt;
    TH2D *hGenLeadPtvsGenSubLeadPt_W;

    THnSparseD *hMultiplicities;
    THnSparseD *hMultiplicities_W;
    THnSparseD *hRecoJets;
    THnSparseD *hRecoJets_W;
    THnSparseD *hGenJets;
    THnSparseD *hGenJets_W;
    THnSparseD *hLeadingJet_W;
    THnSparseD *hGenLeadingJet_W;
    THnSparseD *hSubLeadingJet_W;
    THnSparseD *hGenSubLeadingJet_W;
    THnSparseD *hMultiplicities_DiJet_W;

    THnSparseD *hRecoQuenching_W;
    THnSparseD *hGenQuenching_W;

private:
    Bool_t fIsMC;

    std::vector<float> fMultiplicityBins;

    ClassDef(HistoManagerDiJet, 0)
};

#endif