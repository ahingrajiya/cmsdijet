/**
 * @file TrackingEfficiency.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Tracking Efficiency classes for three different collision systems
 * @version 0.1
 * @date 2026-08-03
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef TrackingEfficiency_H
#define TrackingEfficiency_H

#include "TFile.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"
// C++ headers
#include <iostream>

class TrkEfficiencypPb
{
   public:
    TrkEfficiencypPb(const std::string filePath = "", const std::string underlyingEventTypeName = "");
    ~TrkEfficiencypPb();

    /// @brief Get correction factor for tracking efficiency
    double getCorrection(const float& pt, const float& eta);

   private:
    /// @brief Check if the track is within bounds
    /// @param pt Pt bound is between 0 and 500
    /// @param eta Eta bound is between -2.4 and 2.4
    /// @return Return true if the track is within bounds
    bool checkBound(const float& pt, const float& eta);

    /// @brief Tracking efficiency table
    TFile* fTrkEffFile = nullptr;

    /// @brief Tracking efficiency histogram
    TH2D* fTrkEffHist = nullptr;

    ///@brief Tracking fake rate histogram
    TH2D* fTrkFakeHist = nullptr;

    ///@brief Tracking correction histogram
    TH2D* fTrkCorrHist = nullptr;

    /// @brief Boolean to set using hijing
    bool fuseHIJING = kFALSE;

    /// @brief Boolean to set using epos
    bool fuseEPOS = kFALSE;
};

class TrkEfficiencyOO
{
   public:
    TrkEfficiencyOO(const std::string mbFile = "", const std::string qcdFile = "");
    ~TrkEfficiencyOO();

    double getCorrection(const float& pt, const float& eta, const float& hiBin);

   private:
    TFile* fMBFile = nullptr;
    TFile* fQCDFile = nullptr;
    TH3F* fTrkEffHist = nullptr;
    TH3F* fTrkFakeHist = nullptr;

    bool checkBound(const float& pt, const float& eta, const float& hiBin);
};

#endif
