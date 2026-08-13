/**
 * @file StyleFormatter.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram style formatter
 * @version 0.2
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef STYLE_FORMATTER_H
#define STYLE_FORMATTER_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>

#include "TColor.h"
#include "TGaxis.h"
#include "TH1.h"
#include "TH2.h"
#include "TLatex.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TVirtualPad.h"

class StyleFormatter
{
   public:
    // ------------------------------------------------------------------------
    // Global CMS Style Initialization
    // ------------------------------------------------------------------------
    static void SetGlobalStyle()
    {
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(0);

        gStyle->SetTextFont(42);

        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);

        gStyle->SetLegendBorderSize(0);
        gStyle->SetLegendFont(42);

        gStyle->SetErrorX(0.0);

        TGaxis::SetMaxDigits(3);

        gStyle->SetPalette(kBird);

        gROOT->ForceStyle();
    }

    // ------------------------------------------------------------------------
    // Marker styles addressed by name (CMS-style full/open marker set)
    // ------------------------------------------------------------------------
    static int GetMarkerStyle(const std::string& name)
    {
        static const std::map<std::string, int> markerMap = {{"dot", 1},     {"plus", 68},    {"circle", 71},        {"fcircle", 20},
                                                             {"square", 72}, {"fsquare", 21}, {"diamond", 74},       {"fdiamond", 33},
                                                             {"cross", 75},  {"fcross", 34},  {"doublediamond", 83}, {"fdoublediamond", 43}};

        std::string key = name;
        std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });

        auto it = markerMap.find(key);
        if (it != markerMap.end()) return it->second;

        std::cerr << "Warning: Unknown marker style name '" << name << "'. Defaulting to 'filled circle'." << std::endl;
        return 20;
    }

    // ------------------------------------------------------------------------
    // Colors addressed by name (CMS-style palette)
    // ------------------------------------------------------------------------
    static int GetColorByName(const std::string& name)
    {
        static const std::map<std::string, int> colorMap = {
            {"black", kBlack},       {"red", kRed},         {"blue", kBlue},     {"green", kGreen + 2}, {"magenta", kMagenta},   {"cyan", kCyan + 1},
            {"orange", kOrange + 7}, {"violet", kViolet},   {"gray", kGray + 2}, {"grey", kGray + 2},   {"yellow", kYellow + 2}, {"spring", kSpring + 4},
            {"teal", kTeal + 2},     {"azure", kAzure + 2}, {"pink", kPink + 2}, {"white", kWhite},
        };

        std::string key = name;
        std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return std::tolower(c); });

        auto it = colorMap.find(key);
        if (it != colorMap.end()) return it->second;

        std::cerr << "Warning: Unknown color name '" << name << "'. Defaulting to 'black'." << std::endl;
        return kBlack;
    }

    static void FormatHist(TH1* h, const int color, const std::string& markerStyleName, double markerSize = 1.2)
    {
        if (!h) return;
        h->SetLineColor(color);
        h->SetMarkerColor(color);
        h->SetMarkerStyle(GetMarkerStyle(markerStyleName));
        h->SetMarkerSize(markerSize);
        h->SetLineWidth(2);
    }

    static void FormatHist(TH1* h, const std::string& colorName, const std::string& markerStyleName, double markerSize = 1.2)
    {
        FormatHist(h, GetColorByName(colorName), markerStyleName, markerSize);
    }

    // ------------------------------------------------------------------------
    // Axis labels + optional axis limits, settable per-plot
    // (xMin/xMax/yMin/yMax = -999.0 means "leave automatic")
    // ------------------------------------------------------------------------
    static void FormatAxes(TH1* h, const std::string& xTitle, const std::string& yTitle, double xMin = -999.0, double xMax = -999.0, double yMin = -999.0,
                           double yMax = -999.0)
    {
        if (!h) return;
        h->GetXaxis()->SetTitle(xTitle.c_str());
        h->GetYaxis()->SetTitle(yTitle.c_str());

        h->GetXaxis()->SetTitleSize(0.05);
        h->GetYaxis()->SetTitleSize(0.05);
        h->GetXaxis()->SetLabelSize(0.045);
        h->GetYaxis()->SetLabelSize(0.045);

        h->GetXaxis()->SetTitleOffset(1.1);
        h->GetYaxis()->SetTitleOffset(1.2);

        if (xMin != -999.0 && xMax != -999.0) h->GetXaxis()->SetRangeUser(xMin, xMax);
        if (yMin != -999.0 && yMax != -999.0)
        {
            h->SetMinimum(yMin);
            h->SetMaximum(yMax);
        }
    }

    // ------------------------------------------------------------------------
    // CMS header: "CMS <tag>" on the left, "<system> (<energy>)" on the right.
    // Draws on the current pad (gPad) - call after the pad you want it on is cd()'d.
    // tag examples: "Preliminary", "Work in Progress", "Simulation", "" (CMS only)
    // ------------------------------------------------------------------------
    static void DrawCMSHeader(const std::string& tag = "Preliminary", const std::string& systemLabel = "pPb", const std::string& energyLabel = "#sqrt{s_{NN}} = 8.16 TeV",
                              double xCMS = 0.15, double yCMS = 0.94, double textSize = 0.05)
    {
        TLatex latex;
        latex.SetNDC();

        latex.SetTextFont(61);  // bold
        latex.SetTextSize(textSize);
        latex.SetTextAlign(11);
        latex.DrawLatex(xCMS, yCMS, "CMS");

        if (!tag.empty())
        {
            double cmsWidth = latex.GetXsize();
            latex.SetTextFont(52);  // italic
            latex.SetTextSize(textSize * 0.76);
            latex.DrawLatex(xCMS + cmsWidth + 0.01, yCMS, tag.c_str());
        }

        std::string rightLabel = systemLabel;
        if (!energyLabel.empty()) rightLabel += (rightLabel.empty() ? "" : ", ") + energyLabel;

        if (!rightLabel.empty() && gPad)
        {
            latex.SetTextFont(42);
            latex.SetTextSize(textSize);
            latex.SetTextAlign(31);  // right-aligned, top
            latex.DrawLatex(1.0 - gPad->GetRightMargin(), yCMS, rightLabel.c_str());
        }
    }
};

#endif
