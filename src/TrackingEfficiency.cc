#include "../interface/TrackingEfficiency.h"

TrkEfficiencypPb::TrkEfficiencypPb(const std::string filePath, const std::string underlyingEventTypeName)
{
    if (underlyingEventTypeName == "HIJING")
    {
        std::cout << "HIJING generator is used for tracking efficiency correction." << std::endl;
        fuseHIJING = true;
        fTrkEffFile = TFile::Open(filePath.c_str(), "READ");
        fTrkCorrHist = (TH2D*)fTrkEffFile->Get("rTotalEff3D_0");
    }
    else if (underlyingEventTypeName == "EPOS")
    {
        std::cout << "EPOS generator is used for tracking efficiency correction." << std::endl;
        fuseEPOS = true;
        fTrkEffFile = TFile::Open(filePath.c_str(), "READ");
        fTrkEffHist = (TH2D*)fTrkEffFile->Get("rTotalEff3D_0");
        fTrkFakeHist = (TH2D*)fTrkEffFile->Get("rTotalFake3D_0");
    }
    else
    {
        std::cerr << "Generator name not found. Please check the generator name. No tracking effciency table is loaded." << std::endl;
    }
}
TrkEfficiencypPb::~TrkEfficiencypPb()
{
    if (fTrkEffFile && fTrkEffFile->IsOpen()) fTrkEffFile->Close();
}

bool TrkEfficiencypPb::checkBound(const Float_t& pt, const Float_t& eta)
{
    bool isBounded = (TMath::Abs(eta) <= 2.4 && pt > 0 && pt <= 500);

    return isBounded;
}

double TrkEfficiencypPb::getCorrection(const Float_t& pt, const Float_t& eta)
{
    if (!checkBound(pt, eta))
    {
        // std::cout << "Track outside |eta|<2.4 or pT < 0 or pT > 500. Returning a correction factor of 0 for this track for now." << std::endl;
        return 0;
    }

    if (fuseHIJING)
    {
        double CorrectionFactor = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt));
        if (CorrectionFactor >= 0.9999 || CorrectionFactor <= 0.0001) CorrectionFactor = 1;
        return 1. / CorrectionFactor;
    }
    else if (fuseEPOS)
    {
        double Efficiency = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt));
        double FakeRate = fTrkFakeHist->GetBinContent(fTrkFakeHist->GetXaxis()->FindBin(eta), fTrkFakeHist->GetYaxis()->FindBin(pt));
        double CorrectionFactor = Efficiency / (1 - FakeRate);
        if (CorrectionFactor >= 0.9999 || CorrectionFactor <= 0.0001) CorrectionFactor = 1;
        return 1. / CorrectionFactor;
    }
    else
    {
        return 0;
    }
}

TrkEfficiencyOO::TrkEfficiencyOO(const std::string mbFile, const std::string qcdFile)
{
    fMBFile = TFile::Open(mbFile.c_str(), "READ");
    fQCDFile = TFile::Open(qcdFile.c_str(), "READ");
    fTrkEffHist = (TH3F*)fQCDFile->Get("hEff_3D");
    fTrkFakeHist = (TH3F*)fMBFile->Get("hFak_3D");
}

TrkEfficiencyOO::~TrkEfficiencyOO()
{
    if (fMBFile && fMBFile->IsOpen()) fMBFile->Close();
    if (fQCDFile && fQCDFile->IsOnHeap()) fQCDFile->Close();
}

bool TrkEfficiencyOO::checkBound(const float& pt, const float& eta, const float& hiBin)
{
    if (pt > 0.4 && pt < 300 && abs(eta) < 2.4 && hiBin >= 0 && hiBin <= 200)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double TrkEfficiencyOO::getCorrection(const float& pt, const float& eta, const float& hiBin)
{
    if (!checkBound(pt, eta, hiBin))
    {
        return 0;
    }

    double fakeRate =
        fTrkFakeHist->GetBinContent(fTrkFakeHist->GetXaxis()->FindBin(eta), fTrkFakeHist->GetYaxis()->FindBin(pt), fTrkFakeHist->GetZaxis()->FindBin(hiBin));
    double efficiency = fTrkEffHist->GetBinContent(fTrkEffHist->GetXaxis()->FindBin(eta), fTrkEffHist->GetYaxis()->FindBin(pt), fTrkEffHist->GetZaxis()->FindBin(hiBin));

    double correction = efficiency / (1 - fakeRate);

    if (correction < 0.9999 && correction > 0.0001)
        return 1. / correction;
    else
        return 1.0;
}