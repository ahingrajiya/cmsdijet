#include <iostream>

#include "../interface/AxisRegistry.h"
#include "../interface/CanvasBuilder.h"
#include "../interface/DataExtractor.h"
#include "../interface/HistNormalizer.h"
#include "../interface/HistReader.h"
#include "../interface/StyleFormatter.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"

// ----------------------------------------------------------------------------
// Figure 1: x_j ratio (Data / PYTHIA8+EPOS), 70 < p_{T,1} < 80 GeV, mult 0-1000
//
// Each analysis-note figure gets its own function. Only figures called from
// RunPlotter() below are produced; comment a call out to skip that figure.
// ----------------------------------------------------------------------------
void Figure1()
{
    TFile* fData = TFile::Open("/home/abhishek/analysis/pPb/Summed_Files/PYTHIA5360_unfolding.root", "READ");
    TFile* fMC = TFile::Open("/home/abhishek/analysis/pPb/Summed_Files/ppRef5360_L50SL30_NewJEC_FinerPtBins.root", "READ");

    if (!fData || fData->IsZombie() || !fMC || fMC->IsZombie())
    {
        std::cerr << "Fatal Error: Could not open ROOT files." << std::endl;
        return;
    }

    HistReader readerData, readerMC;
    readerData.ReadAll(fData);
    readerMC.ReadAll(fMC);

    DataExtractor extData(readerData.Quenching.hMultVsXj_W, AxisRegistry::Xj);
    DataExtractor extMC(readerMC.Quenching.hMultVsXj_W, AxisRegistry::Xj);

    extData.SetAxisRange("multiplicity", 0.0, 1000.0);
    extData.SetAxisRange("pt", 70., 80.);
    extMC.SetAxisRange("multiplicity", 0.0, 1000.0);
    extMC.SetAxisRange("pt", 70., 80.);

    TH1D* hData_Xj = extData.ProjectTo1D("xj", "hData_Xj_70_80");
    TH1D* hMC_Xj = extMC.ProjectTo1D("xj", "hMC_Xj_70_80");

    if (!hData_Xj || !hMC_Xj)
    {
        std::cerr << "Fatal Error: Projection failed." << std::endl;
        return;
    }

    HistNormalizer::NormalizeArea(hData_Xj);
    HistNormalizer::NormalizeArea(hMC_Xj);

    // Style this figure's histograms: color + marker by name, axis labels + limits on the fly
    StyleFormatter::FormatHist(hData_Xj, "black", "filled circle", 2);
    StyleFormatter::FormatHist(hMC_Xj, "red", "circle", 2);
    StyleFormatter::FormatAxes(hData_Xj, "x_{j} = p_{T,2} / p_{T,1}", "1/N_{evt} dN/dx", 0.3, 1.0);

    // CMS header + canvas config, set on the fly for this figure
    CanvasBuilder::PlotConfig cfg;
    cfg.cmsTag = "Preliminary";
    cfg.systemLabel = "pPb";
    cfg.energyLabel = "#sqrt{s_{NN}} = 8.16 TeV";
    cfg.yAxisTitle = "1/N_{evt} dN/dx";
    cfg.ratioYAxisTitle = "Data / MC";
    cfg.setLogY = false;
    cfg.xMin = 0.3;
    cfg.xMax = 1.0;
    cfg.ratioYMin = 0.8;
    cfg.ratioYMax = 1.2;

    CanvasBuilder builder;

    // Ratio option 1: spectra on top, ratio in a bottom pad.
    // RatioSpec(numerator index, denominator index, optional legend) -> here Data / MC.
    std::vector<TH1D*> hists = {hData_Xj, hMC_Xj};
    std::vector<std::string> legends = {"Data pPb", "PYTHIA8 + EPOS"};
    std::vector<std::string> drawOpts = {"PE", "PE"};
    std::vector<CanvasBuilder::RatioSpec> ratios = {CanvasBuilder::RatioSpec(0, 1, "Data / PYTHIA8")};

    TCanvas* c = builder.DrawWithRatioPad(hists, legends, drawOpts, ratios, "cXj_Ratio_70_80", "x_{j} = p_{T,2} / p_{T,1}", cfg);
    if (c) CanvasBuilder::SaveCanvas(c, "Xj_Ratio_Mult_70_80");

    // Ratio option 2: the same ratio alone on its own canvas.
    TCanvas* cRatioOnly = builder.DrawRatioCanvas(hists, ratios, "cXj_RatioOnly_70_80", "x_{j} = p_{T,2} / p_{T,1}", cfg);
    if (cRatioOnly) CanvasBuilder::SaveCanvas(cRatioOnly, "Xj_RatioOnly_Mult_70_80");
}

// ----------------------------------------------------------------------------
// Figure 2: (add the next analysis-note figure here as its own function)
// ----------------------------------------------------------------------------
// void Figure2()
// {
// }

void RunPlotter()
{
    StyleFormatter::SetGlobalStyle();

    // Call only the figures you want generated for this run.
    Figure1();
    // Figure2();
}
