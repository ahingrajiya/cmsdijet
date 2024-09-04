/**
 * @file HistoManagerDiJet.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-29
 *
 * @copyright Copyright (c) 2024
 *
 */

// Jet Analysis headers
#include "HistoManagerDiJet.h"

// ROOT headers
#include "TString.h"

// C++ Headers
#include <iostream>

ClassImp(HistoManagerDiJet)

    HistoManagerDiJet::HistoManagerDiJet() : BaseHistoManager(), fIsMC{kFALSE}, hRecoMultiplicity{nullptr}
{
    /* Empty*/
}

HistoManagerDiJet::~HistoManagerDiJet()
{
    if (hRecoMultiplicity)
        delete hRecoMultiplicity;
}

void HistoManagerDiJet::init(const Bool_t &isMC)
{
    hRecoMultiplicity = new TH1D("hRecoMultiplicity", "Reco Multiplicity", 400, 0.0, 400.0);
    hRecoMultiplicity->Sumw2();
}

void HistoManagerDiJet ::writeOutput(const Bool_t &isMC)
{

    hRecoMultiplicity->Write();
}
