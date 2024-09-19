/**
 * @file GenJet.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Class describes jet from the MC level
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

// JetAnalysis headers
#include "GenJet.h"

// ROOT headers
#include "TString.h"

// C++ headers
#include <iostream>

ClassImp(GenJet)

    //________________
    GenJet::GenJet() : BaseJet{}, fPtWeight{0}
{
    /* Emtpy */
}

//________________
void GenJet::print()
{
    std::cout << "--  Generated jet info  --\n"
              << Form("pT: %5.2f  eta: %3.2f  phi: %3.2f  WTAeta: %3.2f  WTAphi: %3.2f  flavor: %d  flavForB: %d\n",
                      this->pt(), this->eta(), this->phi(), this->WTAEta(), this->WTAPhi());
}