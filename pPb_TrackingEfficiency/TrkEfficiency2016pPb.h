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
    TrkEfficiency2016pPb(const std::string filePath = "", const std::string underlyingEventTypeName = "");
    /// @brief Destructor
    virtual ~TrkEfficiency2016pPb()
    {
        std::cout << "This is destructor " << std::endl;
        fTrkEffFile->Close();
    };
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

    ///@brief Tracking fake rate histogram
    TH2D *fTrkFakeHist;

    ///@brief Tracking correction histogram
    TH2D *fTrkCorrHist;

    /// @brief Boolean to set using hijing
    Bool_t fuseHIJING = kFALSE;

    /// @brief Boolean to set using epos
    Bool_t fuseEPOS = kFALSE;
};

inline Bool_t
TrkEfficiency2016pPb::checkBound(const Float_t &pt, const Float_t &eta)
{
    Bool_t isBounded = (TMath::Abs(eta) <= 2.4 && pt > 0 && pt <= 500);

    return isBounded;
}
inline TrkEfficiency2016pPb::TrkEfficiency2016pPb(const std::string filePath, const std::string underlyingEventTypeName)
{

    if (underlyingEventTypeName == "HIJING")
    {
        std::cout << "HIJING generator is used for tracking efficiency correction." << std::endl;
        fuseHIJING = kTRUE;
        TFile *fTrkEffFile = TFile::Open(filePath.c_str(), "READ");
        fTrkCorrHist = (TH2D *)fTrkEffFile->Get("rTotalEff3D_0");
    }
    else if (underlyingEventTypeName == "EPOS")
    {
        std::cout << "EPOS generator is used for tracking efficiency correction." << std::endl;
        fuseEPOS = kTRUE;
        TFile *fTrkEffFile = TFile::Open(filePath.c_str(), "READ");
        fTrkEffHist = (TH2D *)fTrkEffFile->Get("rTotalEff3D_0");
        fTrkFakeHist = (TH2D *)fTrkEffFile->Get("rTotalFake3D_0");
    }
    else
    {
        std::cerr << "Generator name not found. Please check the generator name. No tracking effciency table is loaded." << std::endl;
    }
}

inline Double_t TrkEfficiency2016pPb::getCorrection(const Float_t &pt, const Float_t &eta)
{
    if (!checkBound(pt, eta))
    {
        // std::cout << "Track outside |eta|<2.4 or pT < 0 or pT > 500. Returning a correction factor of 0 for this track for now." << std::endl;
        return 0;
    }

    if (fuseHIJING)
    {
        Double_t CorrectionFactor = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt));
        if (CorrectionFactor >= 0.9999 || CorrectionFactor <= 0.0001)
            CorrectionFactor = 1;
        return 1. / CorrectionFactor;
    }
    else if (fuseEPOS)
    {
        Double_t Efficiency = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt));
        Double_t FakeRate = fTrkFakeHist->GetBinContent(fTrkFakeHist->GetXaxis()->FindBin(eta), fTrkFakeHist->GetYaxis()->FindBin(pt));
        Double_t CorrectionFactor = Efficiency / (1 - FakeRate);
        if (CorrectionFactor >= 0.9999 || CorrectionFactor <= 0.0001)
            CorrectionFactor = 1;
        return 1. / CorrectionFactor;
    }
    else
    {
        return 0;
    }
}

#endif