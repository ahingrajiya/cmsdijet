/**
 * @file CanvasBuilder.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Canvas Builder to make plots
 * @version 0.1
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

#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"

class CanvasBuilder
{
   public:
    struct PlotConfig
    {
        std::string lumiText;
        bool setLogY;

        // Manual Axis Overrides (-999.0 means "use automatic scaling")
        double xMin;
        double xMax;
        double ratioYMin;
        double ratioYMax;

        PlotConfig() : lumiText("CMS Preliminary pPb (8.16 TeV)"), setLogY(true), xMin(-999.0), xMax(-999.0), ratioYMin(-999.0), ratioYMax(-999.0) {}
    };

    CanvasBuilder() {}
    ~CanvasBuilder() {}

    TCanvas* DrawRatio(TH1D* hData, TH1D* hMC, const std::string& canvasName, const std::string& dataLegend, const std::string& mcLegend, const std::string& xAxisTitle,
                       const PlotConfig& cfg = PlotConfig())
    {
        if (!hData || !hMC)
        {
            std::cerr << "Error in DrawRatio: Null histogram pointer passed." << std::endl;
            return nullptr;
        }

        TCanvas* c = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 800);
        c->cd();

        TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
        pad1->SetBottomMargin(0.0);
        pad1->SetTopMargin(0.08);
        pad1->SetLeftMargin(0.15);
        pad1->SetRightMargin(0.05);
        if (cfg.setLogY) pad1->SetLogy();
        pad1->Draw();

        TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
        pad2->SetTopMargin(0.0);
        pad2->SetBottomMargin(0.35);
        pad2->SetLeftMargin(0.15);
        pad2->SetRightMargin(0.05);
        pad2->SetGridy();
        pad2->Draw();

        pad1->cd();
        double maxVal = std::max(hData->GetMaximum(), hMC->GetMaximum());
        hData->SetMaximum(cfg.setLogY ? maxVal * 50.0 : maxVal * 1.5);
        hData->SetMinimum(cfg.setLogY ? 0.5 : 0.0);

        // Hide X-axis labels on top to prevent overlap
        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            hData->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        hData->GetXaxis()->SetLabelSize(0);
        hData->GetXaxis()->SetTitleSize(0);

        hData->GetYaxis()->SetTitle("1/N_{evt} dN/dx");
        hData->GetYaxis()->SetTitleSize(0.06);
        hData->GetYaxis()->SetLabelSize(0.05);
        hData->GetYaxis()->SetTitleOffset(1.1);

        hData->Draw("PE");
        hMC->Draw("HME SAME");  // Smooth line with errors

        TLegend* leg = new TLegend(0.55, 0.70, 0.90, 0.88);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);
        leg->SetTextSize(0.045);
        leg->AddEntry(hData, dataLegend.c_str(), "p");
        leg->AddEntry(hMC, mcLegend.c_str(), "l");
        leg->Draw();

        TLatex latex;
        latex.SetNDC();
        latex.SetTextFont(42);
        latex.SetTextSize(0.05);
        latex.DrawLatex(0.15, 0.94, cfg.lumiText.c_str());

        // --- Render Bottom Pad ---
        pad2->cd();
        TH1D* hRatio = (TH1D*)hData->Clone(Form("%s_Ratio", canvasName.c_str()));
        hRatio->Divide(hMC);

        if (cfg.ratioYMin != -999.0 && cfg.ratioYMax != -999.0)
        {
            hRatio->SetMinimum(cfg.ratioYMin);
            hRatio->SetMaximum(cfg.ratioYMax);
        }
        else
        {
            hRatio->SetMinimum(0.5);
            hRatio->SetMaximum(1.5);
        }

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            hRatio->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        hRatio->GetYaxis()->SetTitle("Data / MC");
        hRatio->GetYaxis()->SetNdivisions(505);
        hRatio->GetYaxis()->SetTitleSize(0.12);
        hRatio->GetYaxis()->SetLabelSize(0.10);
        hRatio->GetYaxis()->SetTitleOffset(0.5);

        hRatio->GetXaxis()->SetTitle(xAxisTitle.c_str());
        hRatio->GetXaxis()->SetTitleSize(0.14);
        hRatio->GetXaxis()->SetLabelSize(0.12);
        hRatio->GetXaxis()->SetTitleOffset(1.0);

        hRatio->Draw("PE");

        TLine* line = new TLine(hRatio->GetXaxis()->GetXmin(), 1.0, hRatio->GetXaxis()->GetXmax(), 1.0);
        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            line->SetX1(cfg.xMin);
            line->SetX2(cfg.xMax);
        }
        line->SetLineColor(kBlack);
        line->SetLineStyle(2);
        line->Draw("SAME");

        return c;
    }

    TCanvas* DrawGrid(const std::vector<TH1D*>& hists, const std::vector<std::string>& titles, const std::string& canvasName, int nCols, int nRows,
                      const std::string& xAxisTitle, bool setLogY = true)
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

        return c;
    }

    TCanvas* DrawMultiRatio(const std::vector<TH1D*>& hists, const std::vector<std::string>& legends, const std::vector<std::string>& drawOpts,
                            const std::vector<std::pair<int, int>>& ratioPairs,  // {Numerator Index, Denominator Index}
                            const std::string& canvasName, const std::string& xAxisTitle, const PlotConfig& cfg = PlotConfig())
    {
        if (hists.empty() || hists.size() != legends.size() || hists.size() != drawOpts.size())
        {
            std::cerr << "Error: Vectors must be non-empty and of equal size." << std::endl;
            return nullptr;
        }

        TCanvas* c = new TCanvas(canvasName.c_str(), canvasName.c_str(), 800, 800);
        c->cd();

        TPad* pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
        pad1->SetBottomMargin(0.0);
        pad1->SetTopMargin(0.08);
        pad1->SetLeftMargin(0.15);
        pad1->SetRightMargin(0.05);
        if (cfg.setLogY) pad1->SetLogy();
        pad1->Draw();

        TPad* pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
        pad2->SetTopMargin(0.0);
        pad2->SetBottomMargin(0.35);
        pad2->SetLeftMargin(0.15);
        pad2->SetRightMargin(0.05);
        pad2->SetGridy();
        pad2->Draw();

        pad1->cd();

        double globalMax = -999.0;
        for (auto h : hists)
        {
            if (h->GetMaximum() > globalMax) globalMax = h->GetMaximum();
        }

        hists[0]->SetMaximum(cfg.setLogY ? globalMax * 50.0 : globalMax * 1.5);
        hists[0]->SetMinimum(cfg.setLogY ? 0.5 : 0.0);

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            hists[0]->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        hists[0]->GetXaxis()->SetLabelSize(0);
        hists[0]->GetXaxis()->SetTitleSize(0);
        hists[0]->GetYaxis()->SetTitle("1/N_{evt} dN/dx");
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

        TLatex latex;
        latex.SetNDC();
        latex.SetTextFont(42);
        latex.SetTextSize(0.05);
        latex.DrawLatex(0.15, 0.94, cfg.lumiText.c_str());

        pad2->cd();
        if (ratioPairs.empty()) return c;  // Safety check

        std::vector<TH1D*> ratios;
        double autoMin = 999.0;
        double autoMax = -999.0;

        for (size_t i = 0; i < ratioPairs.size(); ++i)
        {
            int numIdx = ratioPairs[i].first;
            int denIdx = ratioPairs[i].second;

            TH1D* hRatio = (TH1D*)hists[numIdx]->Clone(Form("%s_Ratio_%zu", canvasName.c_str(), i));
            hRatio->Divide(hists[denIdx]);

            ratios.push_back(hRatio);

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

        if (cfg.ratioYMin != -999.0 && cfg.ratioYMax != -999.0)
        {
            ratios[0]->SetMinimum(cfg.ratioYMin);
            ratios[0]->SetMaximum(cfg.ratioYMax);
        }
        else if (autoMin < 999.0 && autoMax > -999.0)
        {
            ratios[0]->SetMinimum(autoMin * 0.8);
            ratios[0]->SetMaximum(autoMax * 1.2);
        }

        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            ratios[0]->GetXaxis()->SetRangeUser(cfg.xMin, cfg.xMax);
        }

        ratios[0]->GetYaxis()->SetTitle("Ratio");
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

        TLine* line = new TLine(ratios[0]->GetXaxis()->GetXmin(), 1.0, ratios[0]->GetXaxis()->GetXmax(), 1.0);
        if (cfg.xMin != -999.0 && cfg.xMax != -999.0)
        {
            line->SetX1(cfg.xMin);
            line->SetX2(cfg.xMax);
        }
        line->SetLineColor(kBlack);
        line->SetLineStyle(2);
        line->Draw("SAME");

        return c;
    }
};

#endif