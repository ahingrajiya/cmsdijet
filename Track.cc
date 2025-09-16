/**
 * @file Track.cc
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Track class description
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

// Jet analysis headers
#include "Track.h"

ClassImp(Track)

    //________________
    Track::Track() :
    BaseTrack{}, fHighPurity{kFALSE}, fTrkPtErr{0.}, fVertexDxy{0.}, fVertexDxyErr{0.}, fVertexDz{0.}, fVertexDzErr{0.}, fTrkpfHcal{0.}, fTrkpfEcal{0.}, fTrkNHits{0},
    fTrkNormChi2{0.}, fTrkNLayers{0}, fTrkNDOF{0}, fTrkMVA{0.}, fTrkAlgo{0}
{
}
