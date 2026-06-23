/**
 * @file HistNormalizer.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Histogram Normalizer fto normalize histograms different way
 * @version 0.1
 * @date 2026-06-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef HIST_NORMALIZER_H
#define HIST_NORMALIZER_H

#include <iostream>

#include "TAxis.h"
#include "TH1.h"

class HistNormalizer
{
   public:
    static void NormalizeArea(TH1* h, double targetArea = 1.0, bool equalWidth = true)
    {
        if (!h) return;
        double integral = h->Integral("WIDTH");
        if (integral > 0)
        {
            h->Scale(targetArea / integral);
        }
        else
        {
            std::cerr << "Warning: Histogram " << h->GetName() << " has 0 integral." << std::endl;
        }
        if (!equalWidth)
        {
            NormalizeByBinWidth(h);
        }
    }

    static void NormalizeAreaInRange(TH1* h, double minVal, double maxVal, double targetArea = 1.0, bool equalWidth = true)
    {
        if (!h) return;

        double epsilon = 1e-4;
        int binMin = h->GetXaxis()->FindBin(minVal + epsilon);
        int binMax = h->GetXaxis()->FindBin(maxVal - epsilon);

        double integral = h->Integral(binMin, binMax, "WIDTH");
        if (integral > 0)
        {
            h->Scale(targetArea / integral);
        }
        else
        {
            std::cerr << "Warning: Integral in range [" << minVal << ", " << maxVal << "] is 0." << std::endl;
        }
        if (!equalWidth)
        {
            NormalizeByBinWidth(h);
        }
    }

    static void NormalizePerQuantity(TH1* h, bool equalWidth = true)
    {
        if (!h) return;

        double integral = h->Integral();
        if (integral > 0)
        {
            h->Scale(1. / integral);
        }
        else
        {
            std::cerr << "Warning : Integral of histogram " << h->GetName() << " is 0." << std::endl;
        }
        if (!equalWidth)
        {
            NormalizeByBinWidth(h);
        }
    }

    static void NormalizePerQuantityInRange(TH1* h, double minVal, double maxVal, bool equalWidth = true)
    {
        if (!h) return;

        double epsilon = 1e-4;
        int binMin = h->GetXaxis()->FindBin(minVal + epsilon);
        int binMax = h->GetXaxis()->FindBin(maxVal - epsilon);

        double integral = h->Integral(binMin, binMax);
        if (integral > 0)
        {
            h->Scale(1.0 / integral);
        }
        else
        {
            std::cerr << "Warning: Integral in range [" << minVal << ", " << maxVal << "] is 0." << std::endl;
        }
        if (!equalWidth)
        {
            NormalizeByBinWidth(h);
        }
    }

    static void NormalizePerEvent(TH1* h, double nEvents)
    {
        if (!h) return;
        if (nEvents > 0)
        {
            h->Scale(1.0 / nEvents);
        }
        else
        {
            std::cerr << "Error: Cannot normalize by " << nEvents << " events." << std::endl;
        }
    }

    static void NormalizeByBinWidth(TH1* h)
    {
        if (!h) return;
        for (int i = 1; i <= h->GetNbinsX(); ++i)
        {
            double width = h->GetBinWidth(i);
            if (width > 0)
            {
                double content = h->GetBinContent(i);
                double error = h->GetBinError(i);

                h->SetBinContent(i, content / width);
                h->SetBinError(i, error / width);
            }
        }
    }

    static void NormalizeInvariantYield(TH1* h, double nEvents)
    {
        if (!h) return;
        NormalizePerEvent(h, nEvents);
        NormalizeByBinWidth(h);
    }
};

#endif