/**
 * @file RecoJet.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Class describes reconstructed jet parameters
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// Jet analysis headers
#include "RecoJet.h"

// ROOT headers
#include "TString.h"

// C++ headers
#include <iostream>

ClassImp(RecoJet)

    //________________
    RecoJet::RecoJet() : BaseJet{}, fPtJECCorr{0}, fRefJetPt{0}, fRefJetEta{0}, fRefJetPhi{0}, fJetPartonFlavor{0}, fJetPartonFlavorForB{0}
{
    /* Empty */
}

//________________
void RecoJet::print()
{
    std::cout << Form("--  Reconstructed jet info  --\n")
              << Form("pT: %5.2f  eta: %3.2f  phi: %3.2f  pTcorr: %5.2f  WTAeta: %3.2f  WTAphi: %3.2f  GenJetId: %d\n",
                      this->pt(), this->eta(), this->phi(), fPtJECCorr, this->WTAEta(), this->WTAPhi());
}
