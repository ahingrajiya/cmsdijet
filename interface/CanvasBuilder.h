/**
 * @file CanvasBuilder.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Canvas Builder to make plots
 * @version 0.3
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef CANVAS_BUILDER_H
#define CANVAS_BUILDER_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "StyleFormatter.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TSystem.h"

class CanvasBuilder
{
   public:
    struct PlotConfig
    {
        // CMS header, set per-plot: "CMS <tag>" left, "<system>, <energy>" right
        std::string cmsTag;
        std::string systemLabel;
        std::string energyLabel;

        std::string yAxisTitle;       // main pad
        std::string ratioYAxisTitle;  // ratio pad / ratio canvas

        bool setLogY;

        // Manual Axis Overrides (-999.0 means "use automatic scaling")
        double xMin;
        double xMax;
        double ratioYMin;
        double ratioYMax;

        PlotConfig()
            : cmsTag("Preliminary"),
              systemLabel("pPb"),
              energyLabel("#sqrt{s_{NN}} = 8.16 TeV"),
              yAxisTitle("1/N_{evt} dN/dx"),
              ratioYAxisTitle("Ratio"),
              setLogY(true),
              xMin(-999.0),
              xMax(-999.0),
              ratioYMin(-999.0),
              ratioYMax(-999.0)
        {
        }
    };

    // ------------------------------------------------------------------------
    // Which histogram divides which: indices into the histogram vector passed
    // to the drawing functions. legend is optional (shown in the ratio panel).
    // ------------------------------------------------------------------------
    struct RatioSpec
    {
        int numerator;
        int denominator;
        std::string legend;

        RatioSpec(int num, int den, const std::string& leg = "") : numerator(num), denominator(den), legend(leg) {}
    };

    CanvasBuilder() {}
    ~CanvasBuilder() {}

    // ------------------------------------------------------------------------
    // Build one ratio histogram. The ratio inherits marker color, style and
    // size (and line color/width) from its numerator.
    // ------------------------------------------------------------------------
    static TH1D* MakeRatio(TH1D* hNum, TH1D* hDen, const std::string& name)
    {
        if (!hNum || !hDen)
        {
            std::cerr << "Error in MakeRatio: Null histogram pointer passed." << std::endl;
            return nullptr;
        }

        TH1D* hRatio = (TH1D*)hNum->Clone(name.c_str());
        hRatio->SetDirectory(0);
        hRatio->Divide(hDen);

        // Explicitly inherit the numerator's styling
        hRatio->SetMarkerColor(hNum->GetMarkerColor());
        hRatio->SetMarkerStyle(hNum->GetMarkerStyle());
        hRatio->SetMarkerSize(hNum->GetMarkerSize());
        hRatio->SetLineColor(hNum->GetLineColor());
        hRatio->SetLineWidth(hNum->GetLineWidth());

        return hRatio;
    }

    // ------------------------------------------------------------------------
    // Option 1: main plot on top, ratio panel underneath in its own pad.
    // Supports any number of ratios, each with its own numerator/denominator.
    // ------------------------------------------------------------------------
    TCanvas* DrawWithRatioPad(const std::vector<TH1D*>& hists, const std::vector<std::string>& legends, const std::vector<std::string>& drawOpts,
                              const std::vector<RatioSpec>& ratioSpecs, const std::string& canvasName, const std::string& xAxisTitle,
                              const PlotConfig& cfg = PlotConfig())
    {
        if (hists.empty() || hists.size() != legends.size() || hists.size() != drawOpts.size())
        {
            std::cerr << "Error: Vectors must be non-empty and of equal size." << std::endl;
            return nullptr;
        }

        TCanvas* c = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 800);
        c->cd();

        TPad* pad1 = new TPad(Form("%s_pad1", canvasName.c_str()), "pad1", 0.0, 0.3, 1.0, 1.0);
        pad1->SetBottomMargin(0.0);
        pad1->SetTopMargin(0.08);
        pad1->SetLeftMargin(0.15);
        pad1->SetRightMargin(0.05);
        if (cfg.setLogY) pad1->SetLogy();
        pad1->Draw();

        TPad* pad2 = new TPad(Form("%s_pad2", canvasName.c_str()), "pad2", 0.0, 0.0, 1.0, 0.3);
        pad2->SetTopMargin(0.0);
        pad2->SetBottomMargin(0.35);
        pad2->SetLeftMargin(0.15);
        pad2->SetRightMargin(0.05);
        pad2->SetGridy();
        pad2->Draw();

        // --- Top pad ---
        pad1->cd();

        double globalMax = -999.0;
        for (auto h : hists)
        {
            if (h && h->GetMaximum() > globalMax) globalMax = h->GetMaximum();
        }

        hists[0]->SetMaximum(cfg.setLogY ? globalMax * 50.0 : globalMax * 1.5);
        hists[0]->SetMinimum(cfg.setLogY ? 0.5 : 0.0);

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            hists[0]->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        hists[0]->GetXaxis()->SetLabelSize(0);
        hists[0]->GetXaxis()->SetTitleSize(0);
        hists[0]->GetYaxis()->SetTitle(cfg.yAxisTitle.c_str());
        hists[0]->GetYaxis()->SetTitleSize(0.06);
        hists[0]->GetYaxis()->SetLabelSize(0.05);
        hists[0]->GetYaxis()->SetTitleOffset(1.1);

        TLegend* leg = new TLegend(0.55, 0.65, 0.90, 0.88);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->SetTextSize(0.045);

        for (size_t i = 0; i < hists.size(); ++i)
        {
            std::string opt = drawOpts[i] + (i == 0 ? "" : " SAME");
            hists[i]->Draw(opt.c_str());

            std::string legOpt = (drawOpts[i].find("P") != std::string::npos) ? "p" : "l";
            leg->AddEntry(hists[i], legends[i].c_str(), legOpt.c_str());
        }
        leg->Draw();

        StyleFormatter::DrawCMSHeader(cfg.cmsTag, cfg.systemLabel, cfg.energyLabel);

        // --- Ratio pad ---
        pad2->cd();
        if (ratioSpecs.empty()) return c;

        std::vector<TH1D*> ratios = BuildRatios(hists, ratioSpecs, canvasName);
        if (ratios.empty()) return c;

        ApplyRatioYRange(ratios, cfg);

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            ratios[0]->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        ratios[0]->GetYaxis()->SetTitle(cfg.ratioYAxisTitle.c_str());
        ratios[0]->GetYaxis()->SetNdivisions(505);
        ratios[0]->GetYaxis()->SetTitleSize(0.12);
        ratios[0]->GetYaxis()->SetLabelSize(0.10);
        ratios[0]->GetYaxis()->SetTitleOffset(0.5);

        ratios[0]->GetXaxis()->SetTitle(xAxisTitle.c_str());
        ratios[0]->GetXaxis()->SetTitleSize(0.14);
        ratios[0]->GetXaxis()->SetLabelSize(0.12);
        ratios[0]->GetXaxis()->SetTitleOffset(1.0);

        for (size_t i = 0; i < ratios.size(); ++i)
        {
            ratios[i]->Draw(i == 0 ? "PE" : "PE SAME");
        }

        DrawUnityLine(ratios[0], cfg);
        DrawRatioLegend(ratioSpecs, ratios, 0.18, 0.80, 0.55, 0.95, 0.10);

        return c;
    }

    // ------------------------------------------------------------------------
    // Option 2: the ratio (or several ratios) alone on its own canvas.
    // ------------------------------------------------------------------------
    TCanvas* DrawRatioCanvas(const std::vector<TH1D*>& hists, const std::vector<RatioSpec>& ratioSpecs, const std::string& canvasName,
                             const std::string& xAxisTitle, const PlotConfig& cfg = PlotConfig())
    {
        if (hists.empty() || ratioSpecs.empty())
        {
            std::cerr << "Error in DrawRatioCanvas: Need at least one histogram and one ratio." << std::endl;
            return nullptr;
        }

        TCanvas* c = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 800);
        c->cd();
        gPad->SetTopMargin(0.08);
        gPad->SetBottomMargin(0.13);
        gPad->SetLeftMargin(0.15);
        gPad->SetRightMargin(0.05);
        gPad->SetGridy();

        std::vector<TH1D*> ratios = BuildRatios(hists, ratioSpecs, canvasName);
        if (ratios.empty()) return c;

        ApplyRatioYRange(ratios, cfg);

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            ratios[0]->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        StyleFormatter::FormatAxes(ratios[0], xAxisTitle, cfg.ratioYAxisTitle);

        for (size_t i = 0; i < ratios.size(); ++i)
        {
            ratios[i]->Draw(i == 0 ? "PE" : "PE SAME");
        }

        DrawUnityLine(ratios[0], cfg);
        DrawRatioLegend(ratioSpecs, ratios, 0.55, 0.72, 0.92, 0.88, 0.04);

        StyleFormatter::DrawCMSHeader(cfg.cmsTag, cfg.systemLabel, cfg.energyLabel);

        return c;
    }

    // ------------------------------------------------------------------------
    // Convenience wrapper: two histograms, one ratio (numerator / denominator),
    // drawn with the ratio in a bottom pad.
    // ------------------------------------------------------------------------
    TCanvas* DrawRatio(TH1D* hNumerator, TH1D* hDenominator, const std::string& canvasName, const std::string& numeratorLegend,
                       const std::string& denominatorLegend, const std::string& xAxisTitle, const PlotConfig& cfg = PlotConfig(),
                       const std::string& numeratorDrawOpt = "PE", const std::string& denominatorDrawOpt = "PE")
    {
        if (!hNumerator || !hDenominator)
        {
            std::cerr << "Error in DrawRatio: Null histogram pointer passed." << std::endl;
            return nullptr;
        }

        std::vector<TH1D*> hists = {hNumerator, hDenominator};
        std::vector<std::string> legends = {numeratorLegend, denominatorLegend};
        std::vector<std::string> drawOpts = {numeratorDrawOpt, denominatorDrawOpt};
        std::vector<RatioSpec> ratios = {RatioSpec(0, 1)};

        return DrawWithRatioPad(hists, legends, drawOpts, ratios, canvasName, xAxisTitle, cfg);
    }

    TCanvas* DrawGrid(const std::vector<TH1D*>& hists, const std::vector<std::string>& titles, const std::string& canvasName, int nCols, int nRows,
                      const std::string& xAxisTitle, bool setLogY = true, const PlotConfig& cfg = PlotConfig())
    {
        if (hists.empty()) return nullptr;

        int canvasWidth = 400 * nCols;
        int canvasHeight = 400 * nRows;
        TCanvas* c = new TCanvas(canvasName.c_str(), canvasName.c_str(), canvasWidth, canvasHeight);

        c->Divide(nCols, nRows, 0.0, 0.0);

        for (size_t i = 0; i < hists.size() && i < static_cast<size_t>(nCols * nRows); ++i)
        {
            c->cd(i + 1);
            if (setLogY) gPad->SetLogy();

            gPad->SetBottomMargin(0.15);
            gPad->SetTopMargin(0.08);

            if (i % nCols == 0)
            {
                gPad->SetLeftMargin(0.15);
                gPad->SetRightMargin(0.0);
                hists[i]->GetYaxis()->SetTitleSize(0.06);
                hists[i]->GetYaxis()->SetLabelSize(0.05);
                hists[i]->GetYaxis()->SetTitleOffset(1.2);
            }
            else
            {
                gPad->SetLeftMargin(0.0);
                gPad->SetRightMargin(0.02);
                hists[i]->GetYaxis()->SetLabelSize(0);
                hists[i]->GetYaxis()->SetTitleSize(0);
            }

            hists[i]->GetXaxis()->SetTitle(xAxisTitle.c_str());
            hists[i]->GetXaxis()->SetTitleSize(0.06);
            hists[i]->GetXaxis()->SetLabelSize(0.05);

            hists[i]->SetMaximum(setLogY ? hists[i]->GetMaximum() * 10.0 : hists[i]->GetMaximum() * 1.3);
            hists[i]->Draw("PE");

            TLegend* leg = new TLegend(0.2, 0.8, 0.9, 0.9);
            leg->SetBorderSize(0);
            leg->SetFillStyle(0);
            leg->SetTextSize(0.055);
            leg->AddEntry((TObject*)0, titles[i].c_str(), "");
            leg->Draw();
        }

        c->cd();
        StyleFormatter::DrawCMSHeader(cfg.cmsTag, cfg.systemLabel, cfg.energyLabel, 0.02, 0.98, 0.035);

        return c;
    }

    // ------------------------------------------------------------------------
    // Save a canvas as both PDF and PNG, each in its own output folder.
    // Directories are created if they don't already exist.
    // ------------------------------------------------------------------------
    static void SaveCanvas(TCanvas* c, const std::string& outputName, const std::string& pdfDir = "plots/pdf", const std::string& pngDir = "plots/png")
    {
        if (!c)
        {
            std::cerr << "Error in SaveCanvas: Null canvas pointer." << std::endl;
            return;
        }

        gSystem->mkdir(pdfDir.c_str(), true);
        gSystem->mkdir(pngDir.c_str(), true);

        c->SaveAs((pdfDir + "/" + outputName + ".pdf").c_str());
        c->SaveAs((pngDir + "/" + outputName + ".png").c_str());
    }

   private:
    // Build every requested ratio, skipping any spec with bad indices.
    static std::vector<TH1D*> BuildRatios(const std::vector<TH1D*>& hists, const std::vector<RatioSpec>& ratioSpecs, const std::string& canvasName)
    {
        std::vector<TH1D*> ratios;

        for (size_t i = 0; i < ratioSpecs.size(); ++i)
        {
            int numIdx = ratioSpecs[i].numerator;
            int denIdx = ratioSpecs[i].denominator;

            if (numIdx < 0 || denIdx < 0 || numIdx >= static_cast<int>(hists.size()) || denIdx >= static_cast<int>(hists.size()))
            {
                std::cerr << "Error: Ratio " << i << " has out-of-range indices (" << numIdx << "/" << denIdx << "). Skipping." << std::endl;
                continue;
            }

            TH1D* hRatio = MakeRatio(hists[numIdx], hists[denIdx], Form("%s_Ratio_%zu", canvasName.c_str(), i));
            if (hRatio) ratios.push_back(hRatio);
        }

        return ratios;
    }

    // Fix the y-range of the ratio panel: explicit config wins, else auto-scale
    // to the spread of all ratios (including their errors).
    static void ApplyRatioYRange(std::vector<TH1D*>& ratios, const PlotConfig& cfg)
    {
        if (ratios.empty()) return;

        if (cfg.ratioYMin != -999.0 && cfg.ratioYMax != -999.0)
        {
            ratios[0]->SetMinimum(cfg.ratioYMin);
            ratios[0]->SetMaximum(cfg.ratioYMax);
            return;
        }

        double autoMin = 999.0;
        double autoMax = -999.0;

        for (auto hRatio : ratios)
        {
            for (int bin = 1; bin <= hRatio->GetNbinsX(); ++bin)
            {
                double val = hRatio->GetBinContent(bin);
                double err = hRatio->GetBinError(bin);
                if (val > 0.001)
                {
                    if (val + err > autoMax) autoMax = val + err;
                    if (val - err < autoMin) autoMin = val - err;
                }
            }
        }

        if (autoMin < 999.0 && autoMax > -999.0)
        {
            ratios[0]->SetMinimum(autoMin * 0.8);
            ratios[0]->SetMaximum(autoMax * 1.2);
        }
    }

    // Dotted reference line at y = 1
    static void DrawUnityLine(TH1D* hRatio, const PlotConfig& cfg)
    {
        if (!hRatio) return;

        double x1 = hRatio->GetXaxis()->GetXmin();
        double x2 = hRatio->GetXaxis()->GetXmax();
        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            x1 = cfg.xMin;
            x2 = cfg.xMax;
        }

        TLine* line = new TLine(x1, 1.0, x2, 1.0);
        line->SetLineColor(kBlack);
        line->SetLineStyle(3);  // dotted
        line->SetLineWidth(2);
        line->Draw("SAME");
    }

    // Legend for the ratio panel, drawn only if at least one ratio was labelled.
    static void DrawRatioLegend(const std::vector<RatioSpec>& ratioSpecs, const std::vector<TH1D*>& ratios, double x1, double y1, double x2, double y2,
                                double textSize)
    {
        bool anyLegend = false;
        for (const auto& spec : ratioSpecs)
        {
            if (!spec.legend.empty()) anyLegend = true;
        }
        if (!anyLegend) return;

        TLegend* leg = new TLegend(x1, y1, x2, y2);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->SetTextSize(textSize);

        for (size_t i = 0; i < ratios.size() && i < ratioSpecs.size(); ++i)
        {
            if (!ratioSpecs[i].legend.empty()) leg->AddEntry(ratios[i], ratioSpecs[i].legend.c_str(), "p");
        }
        leg->Draw();
    }
};

#endif
