/**
 * @file TrackCut.cc
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Track cuts
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

// Jet Analysis headers
#include "TrackCut.h"

// ROOT Headers
#include "TMath.h"
#include "TString.h"

// C++ headers
#include <iostream>

ClassImp(TrackCut)

    TrackCut::TrackCut() : fTrackPt{0., 1e8}, fTrackEta{-2.4, 2.4}, fTrackDXY{3.0},
                           fTrackDZ{3.}, fPtError{0.1}, fCharge{kTRUE}, fHighPurity{kTRUE},
                           fCaloMatching{kFALSE}, fChi2{kFALSE}, fNHits{kFALSE}, fVerbose{kFALSE}
{
    /* Empty*/
}

TrackCut::~TrackCut()
{
    /* Empty */
}

void TrackCut::report()
{
    TString report = "\nReporting From TrackCut";
    report += TString::Format("Track Pt         :\t %f - %f\n", fTrackPt[0], fTrackPt[1]);
    report += TString::Format("Track Eta        :\t %f - %f\n", fTrackEta[0], fTrackEta[1]);
    report += TString::Format("Track DXY        :\t >=%f\n", fTrackDXY);
    report += TString::Format("Track DZ         :\t >=%f\n", fTrackDZ);
    report += TString::Format("Track PtErr      :\t >=%f\n", fPtError);
    report += TString::Format("Track Charge     :\t %d\n", fCharge);
    report += TString::Format("Track HighPurity :\t %d\n", fHighPurity);
    report += TString::Format("Track Chi2 Cut   :\t %d\n", fChi2);
    report += TString::Format("Track CaloMatch  :\t %d\n", fCaloMatching);
    report += TString::Format("Track NHits      :\t %d\n", fNHits);
    std::cout << report.Data() << std::endl;
}

Bool_t TrackCut::RecoPass(const Track *track)
{
    if (fVerbose)
    {
        std::cout << "\n----- Reco Track Cut -----\n";
    }

    Bool_t goodPt = (fTrackPt[0] <= track->TrkPt() && track->TrkPt() <= fTrackPt[1]);
    if (fVerbose)
    {
        std::cout << Form("Track Pt : %5.2f <= %5.2f <= %5.2f \t %s \n", fTrackPt[0], track->TrkPt(), fTrackPt[1], (goodPt) ? "True" : "False");
    }

    Bool_t goodEta = (fTrackEta[0] <= track->TrkEta() && track->TrkEta() <= fTrackEta[1]);
    if (fVerbose)
    {
        std::cout << Form("Track Eta : %5.2f <= %5.2f <= %5.2f \t %s \n", fTrackEta[0], track->TrkEta(), fTrackEta[1], (goodEta) ? "True" : "False");
    }

    Bool_t goodPtErr = ((track->TrackPtErro() / track->TrkPt()) < fPtError);
    if (fVerbose)
    {
        std::cout << Form("Track Pt Error : %5.2f < %5.2f \t %s \n", (track->TrackPtErro() / track->TrkPt()), fPtError, (goodPtErr) ? "True" : "False");
    }

    Bool_t goodDXY = ((track->TrackVertexDxy() / track->TrackVertexDxyErr()) < fTrackDXY);
    if (fVerbose)
    {
        std::cout << Form("Track Vertex DXY : %5.2f < %5.2f \t %s \n", (track->TrackVertexDxy() / track->TrackVertexDxyErr()), fTrackDXY, (goodDXY) ? "True" : "False");
    }

    Bool_t goodDZ = ((track->TrackVertexDz() / track->TrackVertexDzErr()) < fTrackDZ);
    if (fVerbose)
    {
        std::cout << Form("Track Vertex DZ : %5.2f < %5.2f \t %s \n", (track->TrackVertexDz() / track->TrackVertexDzErr()), fTrackDZ, (goodDZ) ? "True" : "False");
    }

    Bool_t goodCharge = kTRUE;
    if (fCharge)
    {
        goodCharge = (track->TrkChg() != 0);
        if (fVerbose)
        {
            std::cout << Form("Track Charge : %i \t %s \n", track->TrkChg(), (goodCharge) ? "True" : "False");
        }
    }

    Bool_t goodHP = kTRUE;
    if (fHighPurity)
    {
        goodHP = track->TrackHighPurity();
        if (fVerbose)
        {
            std::cout << Form("Track High Purity : %d \t %s \n", track->TrackHighPurity(), (goodHP) ? "True" : "False");
        }
    }

    Bool_t goodCaloMatch = kTRUE;
    if (fCaloMatching)
    {
        goodCaloMatch = (track->TrkPt() > 20.0 && ((track->TrackpfEcal() + track->TrackpfHcal()) / (TMath::CosH(track->TrkEta()) * track->TrkPt())) > 0.5);
        if (fVerbose)
        {
            std::cout << Form("Track Calo Matching : Track Pt = %5.2f Calo Matching = %5.2f \t %s \n", track->TrkPt(), ((track->TrackpfEcal() + track->TrackpfHcal()) / (TMath::CosH(track->TrkEta()) * track->TrkPt())), (goodCaloMatch) ? "True" : "False");
        }
    }

    Bool_t goodChi2 = kTRUE;
    if (fChi2)
    {
        goodChi2 = (track->TrackChi2() / track->TrackNDOF() / track->TrackNLayers() < 0.18);
        if (fVerbose)
        {
            std::cout << Form("Track Chi2 : %5.2f < 0.18 \t %s \n", (track->TrackChi2() / track->TrackNDOF() / track->TrackNLayers()), (goodChi2) ? "True" : "False");
        }
    }

    Bool_t goodNhits = kTRUE;
    if (fNHits)
    {
        goodNhits = (track->TrackNhits() >= 11);
        if (fVerbose)
        {
            std::cout << Form("Track NHits : %i > 11 \t %s \n", track->TrackNhits(), (goodNhits) ? "True" : "False");
        }
    }

    Bool_t isGood = goodPt && goodEta && goodPtErr && goodCharge && goodHP && goodCaloMatch && goodDXY && goodDZ && goodNhits && goodChi2;

    if (fVerbose)
    {
        std::cout << Form("Good Track     : \t %s \n", (isGood) ? "True" : "False");
    }

    return isGood;
}

Bool_t TrackCut::GenPass(const GenTrack *track)
{
    if (fVerbose)
    {
        std::cout << "\n----- Gen Track Cut -----\n";
    }

    Bool_t goodPt = (fTrackPt[0] <= track->TrkPt() && track->TrkPt() <= fTrackPt[1]);
    if (fVerbose)
    {
        std::cout << Form("Track Pt : %5.2f <= %5.2f <= %5.2f \t %s \n", fTrackPt[0], track->TrkPt(), fTrackPt[1], (goodPt) ? "True" : "False");
    }

    Bool_t goodEta = (fTrackEta[0] <= track->TrkEta() && track->TrkEta() <= fTrackEta[1]);
    if (fVerbose)
    {
        std::cout << Form("Track Eta : %5.2f <= %5.2f <= %5.2f \t %s \n", fTrackEta[0], track->TrkEta(), fTrackEta[1], (goodEta) ? "True" : "False");
    }

    Bool_t goodCharge = kTRUE;
    if (fCharge)
    {
        goodCharge = (track->TrkChg() != 0);
        if (fVerbose)
        {
            std::cout << Form("Track Charge : %i \t %s \n", track->TrkChg(), (goodCharge) ? "True" : "False");
        }
    }

    Bool_t isGood = goodPt && goodEta && goodCharge;

    if (fVerbose)
    {
        std::cout << Form("Good Track     : \t %s \n", (isGood) ? "True" : "False");
    }

    return isGood;
}