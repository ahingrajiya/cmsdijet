/**
 * @file StyleFormatter.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram style formatter
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef STYLE_FORMATTER_H
#define STYLE_FORMATTER_H

#include "TColor.h"
#include "TGaxis.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TStyle.h"

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

    static void FormatHist(TH1* h, int color, int markerStyle, double markerSize = 1.2)
    {
        if (!h) return;
        h->SetLineColor(color);
        h->SetMarkerColor(color);
        h->SetMarkerStyle(markerStyle);
        h->SetMarkerSize(markerSize);
        h->SetLineWidth(2);
    }

    static void FormatAxes(TH1* h, const char* xTitle, const char* yTitle)
    {
        if (!h) return;
        h->GetXaxis()->SetTitle(xTitle);
        h->GetYaxis()->SetTitle(yTitle);

        h->GetXaxis()->SetTitleSize(0.05);
        h->GetYaxis()->SetTitleSize(0.05);
        h->GetXaxis()->SetLabelSize(0.045);
        h->GetYaxis()->SetLabelSize(0.045);

        h->GetXaxis()->SetTitleOffset(1.1);
        h->GetYaxis()->SetTitleOffset(1.2);
    }
};

#endif