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

    HistoManagerDiJet::HistoManagerDiJet() : BaseHistoManager(), fIsMC{kFALSE},
                                             hRecoMultiplicity{nullptr}, hCorrectedMultiplicity{nullptr}, hGenMultiplicity{nullptr}, hSubEventMultiplicity{nullptr},
                                             hSelectedMultiplicity{nullptr}
{
    /* Empty*/
}

HistoManagerDiJet::~HistoManagerDiJet()
{
    if (hRecoMultiplicity)
        delete hRecoMultiplicity;
    if (hCorrectedMultiplicity)
        delete hCorrectedMultiplicity;
    if (hGenMultiplicity)
        delete hGenMultiplicity;
    if (hSubEventMultiplicity)
        delete hSubEventMultiplicity;
    if (hSelectedMultiplicity)
        delete hSelectedMultiplicity;
}

void HistoManagerDiJet::init(const Bool_t &isMC)
{
    hRecoMultiplicity = new TH1D("hRecoMultiplicity", "Reco Multiplicity", 700, 0.0, 700.0);
    hRecoMultiplicity->Sumw2();
    hCorrectedMultiplicity = new TH1D("hCorrectedMultiplicity", "Corrected Multiplicity", 700, 0.0, 700.0);
    hCorrectedMultiplicity->Sumw2();
    hGenMultiplicity = new TH1D("hGenMultiplicity", "Gen Multiplicity", 700, 0.0, 700.0);
    hGenMultiplicity->Sumw2();
    hSubEventMultiplicity = new TH1D("hSubEventMultiplicity", "Underlying Event Multiplicity", 700, 0., 700.);
    hSubEventMultiplicity->Sumw2();
    hSelectedMultiplicity = new TH1D("hSelectedMultiplicity", "Multiplicity Distribution after selection", 700, 0., 700.);
    hSelectedMultiplicity->Sumw2();
}

void HistoManagerDiJet ::writeOutput(const Bool_t &isMC)
{

    hRecoMultiplicity->Write();
    hCorrectedMultiplicity->Write();
    hGenMultiplicity->Write();
    hSubEventMultiplicity->Write();
    hSelectedMultiplicity->Write();
}
