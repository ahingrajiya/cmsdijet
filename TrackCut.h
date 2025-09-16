/**
 * @file TrackCut.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Track cuts
 * @version 0.1
 * @date 2024-08-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef TrackCut_h
#define TrackCut_h

// Jet Analysis header
#include "GenTrack.h"
#include "Track.h"

// ROOT Headers
#include "Rtypes.h"

// C++ Headers
#include <limits>

class TrackCut
{
   public:
    ///@brief Constructor
    TrackCut();
    ///@brief Destructor
    virtual ~TrackCut();

    //
    // Setters
    //

    ///@brief Track mopmentum cuts
    void setPt(const Double_t &low, const Double_t &hi)
    {
        fTrackPt[0] = low;
        fTrackPt[1] = hi;
    }
    ///@brief Track eta cut
    void setEta(const Double_t &low, const Double_t &hi)
    {
        fTrackEta[0] = low;
        fTrackEta[1] = hi;
    }
    ///@brief Associated vertex xy cut
    void setDXY(const Double_t &dxy) { fTrackDXY = dxy; }
    ///@brief Associated vertex z cut
    void setDZ(const Double_t &dz) { fTrackDZ = dz; }
    ///@brief Track Pt Error cut
    void setPtErr(const Double_t &pterr) { fPtError = pterr; }
    ///@brief Use Charged tracks
    void setCharge() { fCharge = kTRUE; }
    ///@brief Use High Purity tracks
    void setHighPurity() { fHighPurity = kTRUE; }
    ///@brief Use Calo Matching
    void setCaloMatching() { fCaloMatching = kTRUE; }
    ///@brief Use Chi2 cut
    void setChi2() { fChi2 = kTRUE; }
    ///@brief Use Nhits cut
    void setNHits() { fNHits = kTRUE; }
    ///@brief Use MVA and Algo
    void setMVAAlgo() { fMVAAlgo = kTRUE; }
    ///@brief Set Verbose mode
    void setVerbose() { fVerbose = kTRUE; }
    ///@brief Report all the cuts and pass/fail statistics
    void report();
    ///@brief Check if reco track passes the cut
    virtual Bool_t RecoPass(const Track *track);
    ///@brief Check if gen track passes the cut
    virtual Bool_t GenPass(const GenTrack *track);

   private:
    ///@brief Track Pt
    Double_t fTrackPt[2];
    ///@brief Track Eta
    Double_t fTrackEta[2];
    ///@brief Associated vertex xy cut
    Double_t fTrackDXY;
    ///@brief Associated vertex z cut
    Double_t fTrackDZ;
    ///@brief High Purity Tracks
    Bool_t fHighPurity;
    ///@brief Track Pt Error
    Double_t fPtError;
    ///@brief Only Changed Track
    Bool_t fCharge;
    ///@brief Calorimeter cuts
    Bool_t fCaloMatching;
    ///@brief Chisqure cut
    Bool_t fChi2;
    ///@brief NHits cut
    Bool_t fNHits;
    ///@brief Verbose Mode
    Bool_t fVerbose;
    ///@brief Use Track MVA and Algo
    Bool_t fMVAAlgo;

    ClassDef(TrackCut, 0)
};

#endif