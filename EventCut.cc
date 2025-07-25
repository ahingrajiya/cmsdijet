/**
 * @file EventCut.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Example of the event cut
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// Jet analysis headers
#include "EventCut.h"

// ROOT headers
#include "TMath.h"
#include "TString.h"

// C++ headers
#include <iostream>

ClassImp(EventCut)

    //________________
    EventCut::EventCut() : fVz{-1e9, 1e9},
                           fShiftVx{0}, fShiftVy{0}, fVR{1e9},
                           fHiBin{-1000, 1000},
                           fPtHat{-1e9, 1e9}, fPtHatWeight{-1e9, 1e9}, fVerbose{kFALSE},
                           fEventsPassed{0}, fEventsFailed{0},
                           fMultiplicity{-5000, 5000}
{
    fLumi[0] = 0;
    fLumi[1] = std::numeric_limits<unsigned int>::max();
}

//________________
EventCut::~EventCut()
{
    /* Empty */
}

//________________
void EventCut::report()
{
    TString report = "\n==============EventCut::Reporting Event Selections in Reader================\n";
    report += TString::Format("Vz              :\t %f - %f\n", fVz[0], fVz[1]);
    report += TString::Format("HiBin           :\t %d - %d\n", fHiBin[0], fHiBin[1]);
    report += TString::Format("Multiplicity    :\t %d - %d\n", fMultiplicity[0], fMultiplicity[1]);
    report += TString::Format("pThat           :\t %f - %f\n", fPtHat[0], fPtHat[1]);

    std::cout << report.Data() << std::endl;
}

//________________
Bool_t EventCut::pass(const Event *ev)
{

    if (fVerbose)
    {
        std::cout << "\n----- Event cut -----\n";
    }

    const Bool_t goodVz = (fVz[0] <= ev->vz()) &&
                          (ev->vz() <= fVz[1]);
    if (fVerbose)
    {
        std::cout << Form("vz        : %5.2f <= %5.2f < %5.2f \t %s \n",
                          fVz[0], ev->vz(), fVz[1], (goodVz) ? "true" : "false");
    }

    const Bool_t goodHiBin = (fHiBin[0] <= ev->hiBin()) &&
                             (ev->hiBin() <= fHiBin[1]);
    if (fVerbose)
    {
        std::cout << Form("hiBin        : %d <= %d <= %d \t %s \n",
                          fHiBin[0], ev->hiBin(), fHiBin[1], (goodHiBin) ? "true" : "false");
    }

    const Bool_t goodHiBinShifted = (fHiBin[0] <= ev->hiBinWithShift()) &&
                                    (ev->hiBinWithShift() <= fHiBin[1]);
    if (fVerbose)
    {
        std::cout << Form("hiBin With Shift        : %d <= %d <= %d \t %s \n",
                          fHiBin[0], ev->hiBinWithShift(), fHiBin[1], (goodHiBin) ? "true" : "false");
    }

    const Bool_t goodPtHat = ((fPtHat[0] < ev->ptHat()) &&
                              (ev->ptHat() <= fPtHat[1])) ||
                             (ev->ptHat() < 0);

    if (fVerbose)
    {
        std::cout << Form("ptHat        : %9.2f <= %9.2f < %9.2f or ptHat < 0 \t %s \n",
                          fPtHat[0], ev->ptHat(), fPtHat[1], (goodPtHat) ? "true" : "false");
    }

    const Bool_t goodMultiplicity = (fMultiplicity[0] <= ev->multiplicity()) &&
                                    (ev->multiplicity() <= fMultiplicity[1]);

    if (fVerbose)
    {
        std::cout << Form("multiplicty   : %i <= %i <= %i  \t %s \n",
                          fMultiplicity[0], ev->multiplicity(), fMultiplicity[1], (goodMultiplicity) ? "true" : "false");
    }

    Bool_t goodFilter = kTRUE;

    for (size_t i = 0; i < ev->skimFilterNamesAndValues().size(); i++)
    {
        if (ev->skimFilterNamesAndValues()[i].second == 0)
        {
            goodFilter = kFALSE;
            if (fVerbose)
            {
                std::cout << Form("Event filter failed: %s\n", ev->skimFilterNamesAndValues()[i].first.c_str());
            }
            break;
        }
    }
    Bool_t goodTrigger = kTRUE;
    for (size_t i = 0; i < ev->triggerNamesAndValues().size(); i++)
    {
        if (ev->triggerNamesAndValues()[i].second == 0)
        {
            goodTrigger = kFALSE;
            if (fVerbose)
            {
                std::cout << Form("Event trigger failed: %s\n", ev->triggerNamesAndValues()[i].first.c_str());
            }
            break;
        }
    }

    Bool_t passEvent = goodVz && goodHiBin && goodPtHat && goodMultiplicity && goodFilter && goodHiBinShifted && goodTrigger;
    (passEvent) ? fEventsPassed++ : fEventsFailed++;

    return passEvent;
}