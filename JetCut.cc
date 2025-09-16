/**
 * @file JetCut.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Example of jet cut
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// Jet analysis headers
#include "JetCut.h"

#include "GenJet.h"

// ROOT headers
#include "TMath.h"
#include "TString.h"

// C++ headers
#include <iostream>

ClassImp(JetCut)

    //________________
    JetCut::JetCut() : fPt{0., 1e6}, fEta{-1e6, 1e6}, fJetsPassed{0}, fJetsFailed{0}, fVerbose{kFALSE}
{
    /* Empty */
}

//________________
JetCut::~JetCut()
{
    /* Empty */
}

//________________
void JetCut::report()
{
    TString report = "\n====================JetCut::Reporting Jet Selections in Reader=================\n";
    report += TString::Format("Jet Transverse Momentum (pT)              :\t %f <= Jet pT <= %f\n", fPt[0], fPt[1]);
    report += TString::Format("Jet Pseudorapidity (#eta)                 :\t %f <= Jet #eta <= %f\n", fEta[0], fEta[1]);
    std::cout << report.Data() << std::endl;
}

//________________
Bool_t JetCut::pass(const RecoJet *jet)
{
    if (fVerbose)
    {
        std::cout << "\n----- Reco jet cut -----\n";
    }

    Bool_t goodPt = (fPt[0] <= jet->pt() && jet->pt() <= fPt[1]);
    if (fVerbose)
    {
        std::cout << Form("pT raw : %5.2f <= %5.2f <= %5.2f \t %s \n", fPt[0], jet->pt(), fPt[1], (goodPt) ? "true" : "false");
    }

    Bool_t goodEta = (fEta[0] <= jet->eta() && jet->eta() <= fEta[1]);
    if (fVerbose)
    {
        std::cout << Form("eta : %5.2f <= %5.2f <= %5.2f \t %s \n", fEta[0], jet->eta(), fEta[1], (goodEta) ? "true" : "false");
    }

    Bool_t isGood = goodPt && goodEta;

    if (fVerbose)
    {
        std::cout << Form("good jet     : \t %s \n", (isGood) ? "true" : "false");
    }

    return isGood;
}

//________________
Bool_t JetCut::pass(const GenJet *jet)
{
    if (fVerbose)
    {
        std::cout << "\n----- Gen jet cut -----\n";
    }

    Bool_t goodPt = (fPt[0] <= jet->pt() && jet->pt() <= fPt[1]);
    if (fVerbose)
    {
        std::cout << Form("pT raw : %5.2f <= %5.2f <= %5.2f \t %s \n", fPt[0], jet->pt(), fPt[1], (goodPt) ? "true" : "false");
    }

    Bool_t goodEta = (fEta[0] <= jet->eta() && jet->eta() <= fEta[1]);
    if (fVerbose)
    {
        std::cout << Form("eta : %5.2f <= %5.2f <= %5.2f \t %s \n", fEta[0], jet->eta(), fEta[1], (goodEta) ? "true" : "false");
    }

    Bool_t isGood = goodPt && goodEta;

    if (fVerbose)
    {
        std::cout << Form("good jet     : \t %s \n", (isGood) ? "true" : "false");
    }

    return isGood;
}