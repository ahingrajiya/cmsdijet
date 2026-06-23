/**
 * @file DataExtractor.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Extract projections from given histograms
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef DATA_EXTRACTOR_H
#define DATA_EXTRACTOR_H

#include <iostream>
#include <map>
#include <string>

#include "TAxis.h"
#include "TH1D.h"
#include "TH2.h"
#include "TH3.h"
#include "THnSparse.h"

class DataExtractor
{
   private:
    THnSparseD* fSparse = nullptr;
    TH1* fHist = nullptr;
    std::map<std::string, int> fAxisMap;

   public:
    DataExtractor(THnSparseD* sparse, const std::map<std::string, int>& axisMap) : fSparse(sparse), fAxisMap(axisMap) {}

    DataExtractor(TH1* hist, const std::map<std::string, int>& axisMap) : fHist(hist), fAxisMap(axisMap) {}

    ~DataExtractor() {}

    void SetAxisRange(const std::string& axisName, double minVal, double maxVal)
    {
        if (fAxisMap.find(axisName) == fAxisMap.end())
        {
            std::cerr << "Error: Axis '" << axisName << "' not found in registry." << std::endl;
            return;
        }

        int axisIndex = fAxisMap[axisName];
        int bins[2];
        TAxis* axis = nullptr;
        if (fSparse)
        {
            axis = fSparse->GetAxis(axisIndex);
            FindBinRange(axis, minVal, maxVal, bins);
            fSparse->GetAxis(axisIndex)->SetRange(bins[0], bins[1]);
        }
        else if (fHist)
        {
            // Translate the registry integer to standard ROOT XYZ axes
            if (axisIndex == 0)
            {
                axis = fHist->GetXaxis();
                FindBinRange(axis, minVal, maxVal, bins);
                fHist->GetXaxis()->SetRange(bins[0], bins[1]);
            }
            else if (axisIndex == 1)
            {
                axis = fHist->GetYaxis();
                FindBinRange(axis, minVal, maxVal, bins);
                fHist->GetYaxis()->SetRange(bins[0], bins[1]);
            }
            else if (axisIndex == 2)
            {
                axis = fHist->GetZaxis();
                FindBinRange(axis, minVal, maxVal, bins);
                fHist->GetZaxis()->SetRange(bins[0], bins[1]);
            }
        }
    }

    void FindBinRange(TAxis* axis, double minVal, double maxVal, int arr[])
    {
        double epsilon = 1e-4;
        arr[0] = axis->FindBin(minVal + epsilon);
        arr[1] = axis->FindBin(maxVal - epsilon);
    }

    void ResetCuts()
    {
        if (fSparse)
        {
            for (int i = 0; i < fSparse->GetNdimensions(); ++i)
            {
                fSparse->GetAxis(i)->SetRange(0, 0);
            }
        }
        else if (fHist)
        {
            fHist->GetXaxis()->SetRange(0, 0);
            fHist->GetYaxis()->SetRange(0, 0);
            if (fHist->GetZaxis()) fHist->GetZaxis()->SetRange(0, 0);
        }
    }

    // ------------------------------------------------------------------------
    // 1D Projection Engine
    // ------------------------------------------------------------------------
    TH1D* ProjectTo1D(const std::string& axisName, const std::string& newHistName)
    {
        if (fAxisMap.find(axisName) == fAxisMap.end())
        {
            std::cerr << "Error: Axis '" << axisName << "' not found." << std::endl;
            return nullptr;
        }

        int axisIndex = fAxisMap[axisName];
        TH1D* hProj = nullptr;

        // Route A: THnSparse Projection
        if (fSparse)
        {
            hProj = (TH1D*)fSparse->Projection(axisIndex, "E");
        }
        // Route B: TH2 / TH3 Projection
        else if (fHist)
        {
            TH3* h3 = dynamic_cast<TH3*>(fHist);
            TH2* h2 = dynamic_cast<TH2*>(fHist);

            if (h3)
            {
                if (axisIndex == 0)
                    hProj = h3->ProjectionX(newHistName.c_str());
                else if (axisIndex == 1)
                    hProj = h3->ProjectionY(newHistName.c_str());
                else if (axisIndex == 2)
                    hProj = h3->ProjectionZ(newHistName.c_str());
            }
            else if (h2)
            {
                if (axisIndex == 0)
                    hProj = h2->ProjectionX(newHistName.c_str());
                else if (axisIndex == 1)
                    hProj = h2->ProjectionY(newHistName.c_str());
            }
        }

        if (hProj)
        {
            hProj->SetName(newHistName.c_str());
            hProj->SetDirectory(0);
        }
        else
        {
            std::cerr << "Error: Projection failed. Check your axis dimensions." << std::endl;
        }

        return hProj;
    }
};

#endif