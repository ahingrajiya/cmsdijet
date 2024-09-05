/**
 * @file TrkEfficiency.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief A tracking efficiency class for pPb
 * @version 0.1
 * @date 2024-09-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TrkEfficiency2016pPb_h
#define TrkEfficiency2016pPb_h

// ROOT Headers
#include "TFile.h"
#include "TH2.h"
#include "TMath.h"
#include "TObject.h"
// C++ headers
#include <iostream>

class TrkEfficiency2016pPb
{

public:
    /// @brief Default constructor
    TrkEfficiency2016pPb(std::string filePath = "");
    /// @brief Destructor
    virtual ~TrkEfficiency2016pPb();
    /// @brief Get correction factor for tracking efficiency
    Double_t getCorrection(const Float_t &pt, const Float_t &eta);

private:
    /// @brief Check if the track is within bounds
    /// @param pt Pt bound is between 0 and 500
    /// @param eta Eta bound is between -2.4 and 2.4
    /// @return Return true if the track is within bounds
    Bool_t checkBound(const Float_t &pt, const Float_t &eta);

    /// @brief Tracking efficiency table
    TFile *fTrkEffFile;

    /// @brief Tracking efficiency histogram
    TH2D *fTrkEffHist;
};

inline Bool_t TrkEfficiency2016pPb::checkBound(const Float_t &pt, const Float_t &eta)
{
    Bool_t isBounded = (TMath::Abs(eta) <= 2.4 && pt > 0 && pt <= 500);

    return isBounded;
}
inline TrkEfficiency2016pPb::TrkEfficiency2016pPb(std::string filePath)
{
    TFile *fTrkEffFile = TFile::Open(filePath.c_str(), "READ");
    fTrkEffHist = (TH2D *)fTrkEffFile->Get("rTotalEff3D_0");
}

inline Double_t TrkEfficiency2016pPb::getCorrection(const Float_t &pt, const Float_t &eta)
{
    if (!checkBound(pt, eta))
    {
        std::cout << "Track outside |eta|<2.4 or pT < 0 or pT > 500. Returning a correction factor of 0 for this track for now." << std::endl;
        return 0;
    }

    Double_t CorrectionFactor = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt));
    if (CorrectionFactor >= 0.9999 || CorrectionFactor <= 0.0001)
        CorrectionFactor = 1;

    return 1. / CorrectionFactor;
}
inline TrkEfficiency2016pPb::~TrkEfficiency2016pPb()
{
    fTrkEffFile->Close();
}

#endif