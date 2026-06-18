/**
 * @file JetEnergyScale.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Derive Jet Energy Scale and Jet Energy Resolution
 * @version 0.1
 * @date 2025-09-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef JETENERGYSCALE_H
#define JETENERGYSCALE_H

#include "common.hpp"

class JetEnergyScale
{
   public:
    JetEnergyScale();
    virtual ~JetEnergyScale();

    void loadInputFile(std::string location) { fInputLocation = location; }
    void setBins(std::vector<double> ptBins, std::vector<double> etaBins, std::vector<double> multCentBins)
    {
        fPtBins = ptBins;
        fEtaBins = etaBins;
        fMultCentBins = multCentBins;
    }

    void init();

   private:
    TFile* file_input = nullptr;

    std::string fInputLocation = "";
    std::vector<TH3D*> hEtaJES{};
    std::vector<TH3D*> hPtJES{};
    std::vector<double> fPtBins{};
    std::vector<double> fEtaBins{};
    std::vector<double> fMultCentBins{};

    TH3D* hPtJES = nullptr;
    TH3D* hEtaJES = nullptr;

    void loadHistograms(TFile* f);

    std::tuple<TGraphErrors*, TGraphErrors*, TGraphErrors*> fitJetPtResponseCustomBins(TH2D* h2d, const std::vector<double>& pt_bins, TDirectory* out_dir = nullptr);
    std::tuple<TGraphErrors*, TGraphErrors*, TGraphErrors*> fitJetEtaResponseCustomBins(TH2D* h2d_eta, const std::vector<double>& eta_bins,
                                                                                        TDirectory* out_dir = nullptr);

    void jetEnergyResponse();
};

#endif  // JETENERGYSCALE_H