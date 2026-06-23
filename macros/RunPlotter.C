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

void RunPlotter()
{
    StyleFormatter::SetGlobalStyle();
    CanvasBuilder builder;
    HistNormalizer histNrml;
    CanvasBuilder::PlotConfig cfgXj;
    cfgXj.setLogY = false;
    cfgXj.xMin = 0.3;  // Zoom the X-axis to only show 0.0 to 1.0
    cfgXj.xMax = 1.0;
    cfgXj.ratioYMin = 0.8;  // Hardcode the ratio to 0.8 - 1.2
    cfgXj.ratioYMax = 1.2;

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
    // Project down to 1D
    TH1D* hData_Xj = extData.ProjectTo1D("xj", "hData_Xj_185_250");
    TH1D* hMC_Xj = extMC.ProjectTo1D("xj", "hMC_Xj_185_250");

    histNrml.NormalizeArea(hData_Xj);
    histNrml.NormalizeArea(hMC_Xj);

    if (!hData_Xj || !hMC_Xj)
    {
        std::cerr << "Fatal Error: Projection failed." << std::endl;
        return;
    }

    // Apply marker styles: Data = Black Circles (20), MC = Red Open Circles (24)
    StyleFormatter::FormatHist(hData_Xj, kBlack, 20);
    StyleFormatter::FormatHist(hMC_Xj, kRed, 24);

    // ------------------------------------------------------------------------
    // 5. Canvas Building & Rendering
    // ------------------------------------------------------------------------
    TCanvas* cXj = builder.DrawRatio(hData_Xj, hMC_Xj, "cXj_Ratio_185_250", "Data pPb", "PYTHIA8 + EPOS", "x_{j} = p_{T,2} / p_{T,1}", cfgXj);

    // Save the output
    if (cXj)
    {
        cXj->SaveAs("Xj_Ratio_Mult_185_250.pdf");
        std::cout << "Successfully generated plots/Xj_Ratio_Mult_185_250.pdf" << std::endl;
    }
}