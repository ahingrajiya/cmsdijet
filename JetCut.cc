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
    JetCut::JetCut() : fPt{0., 1e6}, fConeR{1e6},
                       fMustHaveGenMatching{kFALSE}, fEta{-1e6, 1e6},
                       fJetsPassed{0}, fJetsFailed{0}, fVerbose{kFALSE}
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
    TString report = "\nReporting from JetCut";
    report += TString::Format("pT              :\t %f - %f\n", fPt[0], fPt[1]);
    report += TString::Format("cone R          :\t %f\n", fConeR);
    report += TString::Format("match to gen    :\t %d\n", fMustHaveGenMatching);
    report += TString::Format("eta             :\t %f - %f\n", fEta[0], fEta[1]);
    report += TString::Format("Jets passed     :\t %lld\n", fJetsPassed);
    report += TString::Format("Jets failed     :\t %lld\n", fJetsFailed);
    std::cout << report.Data() << std::endl;
}

//________________
Bool_t JetCut::pass(const RecoJet *jet)
{
    if (fVerbose)
    {
        std::cout << "\n----- Reco jet cut -----\n";
    }

    Bool_t goodPt = (fPt[0] <= jet->pt() &&
                     jet->pt() <= fPt[1]);
    if (fVerbose)
    {
        std::cout << Form("pT raw : %5.2f <= %5.2f <= %5.2f \t %s \n",
                          fPt[0], jet->pt(), fPt[1], (goodPt) ? "true" : "false");
    }

    Float_t recoR = TMath::Sqrt(jet->phi() * jet->phi() +
                                jet->eta() * jet->eta());
    Bool_t goodConeR = (recoR <= fConeR);
    if (fVerbose)
    {
        std::cout << Form("cone R: %5.2f <= %5.2f \t %s \n",
                          recoR, fConeR, (goodConeR) ? "true" : "false");
    }

    Bool_t goodEta = (fEta[0] <= jet->eta() &&
                      jet->eta() <= fEta[1]);
    if (fVerbose)
    {
        std::cout << Form("eta : %5.2f <= %5.2f <= %5.2f \t %s \n",
                          fEta[0], jet->eta(), fEta[1], (goodEta) ? "true" : "false");
    }

    // if ( goodMatching )
    // Bool_t goodRefPt = (fRefPt[0] <= jet->refJetPt() &&
    //                            jet->refJetPt() <= fRefPt[1]);
    // if (fVerbose) {
    //     std::cout << Form("gen pT    : %5.2f <= %5.2f <= %5.2f \t %s \n",
    //                       fRefPt[0], jet->refJetPt(), fRefPt[1], ( goodRefPt ) ? "true" : "false" );
    // }

    // Float_t refR = TMath::Sqrt( jet->refJetPhi() * jet->refJetPhi() +
    //                             jet->refJetEta() * jet->refJetEta() );
    // Bool_t goodRefConeR = (refR <= fRefConeR);
    // if (fVerbose) {
    //     std::cout << Form("ref cone R: %5.2f <= %5.2f \t %s \n",
    //                       refR, fRefConeR, ( goodRefConeR ) ? "true" : "false" );
    // }

    // Bool_t goodFlavorForB = ( fRefFlavorForB[0] <= jet->refFlavorForB() &&
    //                                 jet->refFlavorForB() <= fRefFlavorForB[1] );
    // if (fVerbose) {
    //     std::cout << Form("ref flavorB: %d <= %d <= %d \t %s \n",
    //                       fRefFlavorForB[0], jet->refFlavorForB(), fRefFlavorForB[1], ( goodFlavorForB ) ? "true" : "false" );
    // }

    Bool_t isGood = goodPt && goodConeR && goodEta;

    // Bool_t isGood = goodRecoPt && goodRecoConeR && goodMatching &&
    //                       goodRefPt && goodRefConeR && goodFlavorForB;

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

    Bool_t goodPt = (fPt[0] <= jet->pt() &&
                     jet->pt() <= fPt[1]);
    if (fVerbose)
    {
        std::cout << Form("pT raw : %5.2f <= %5.2f <= %5.2f \t %s \n",
                          fPt[0], jet->pt(), fPt[1], (goodPt) ? "true" : "false");
    }

    Bool_t goodEta = (fEta[0] <= jet->eta() &&
                      jet->eta() <= fEta[1]);
    if (fVerbose)
    {
        std::cout << Form("eta : %5.2f <= %5.2f <= %5.2f \t %s \n",
                          fEta[0], jet->eta(), fEta[1], (goodEta) ? "true" : "false");
    }

    Bool_t isGood = goodPt && goodEta;

    if (fVerbose)
    {
        std::cout << Form("good jet     : \t %s \n", (isGood) ? "true" : "false");
    }

    return isGood;
}