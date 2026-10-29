// pT-hat weight for PYTHIA+HIJING (OO) events so that their weighted pT-hat distribution matches
// PYTHIA (pp). Multiplies the forest pT-hat weight; 1 above 80 GeV, where the shapes agree.
// Derived by ptHatReweight.cpp from Events/hPtHat_W in PYTHIA_HIJING_NewPtBins.root and PYTHIA5360_L50SL20_PtHatHisto.root.
#pragma once

#include <cmath>

inline double OOPtHatReweight(double ptHat)
{
    // 10 GeV bins starting at 0 GeV
    static const double kWeight[8] = {1, 1.0274, 1.2616, 1.1426, 1.0566, 1.021, 1.0061, 1.0013};
    const int bin = static_cast<int>(std::floor((ptHat - 0) / 10));
    if (bin < 0 || bin >= 8) return 1.;
    return kWeight[bin];
}
