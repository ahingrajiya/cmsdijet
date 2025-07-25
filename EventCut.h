/**
 * @file EventCut.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Example of the event cut
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef EventCut_h
#define EventCut_h

// Jet analysis headers
#include "Event.h"

// ROOT headers
#include "Rtypes.h"

// C++ headers
#include <limits>

//________________
class EventCut
{
public:
  /// @brief Base constructor
  EventCut();
  /// @brief Destructor
  virtual ~EventCut();

  //
  // Setters
  //

  /// @brief Set limits on Vz
  void setVz(const Double_t &lo = -1e9, const Double_t &hi = 1e9)
  {
    fVz[0] = lo;
    fVz[1] = hi;
  }
  /// @brief Shift of the nominal beam position in x direction
  void setShiftVx(const Double_t &x = 0.) { fShiftVx = x; }
  /// @brief Shift of the nominal beam position in y direction
  void setShiftVy(const Double_t &y = 0.) { fShiftVy = y; }
  /// @brief Set cut on maximal radial vertex displacement
  void setVertexR(const Double_t &r = 1e9) { fVR = r; }
  /// @brief Set limits on HiBin
  void setHiBin(const Short_t &lo = -10000, const Short_t &hi = 10000)
  {
    fHiBin[0] = lo;
    fHiBin[1] = hi;
  }
  /// @brief Set limits on centrality
  void setCentrality(const Double_t &lo = -1000, const Double_t &hi = 1000)
  {
    fCentVal[0] = lo;
    fCentVal[1] = hi;
  }
  /// @brief Set limits on luminosity
  void setLumi(const UInt_t &lo = 0, const UInt_t &hi = std::numeric_limits<unsigned int>::max())
  {
    fLumi[0] = lo;
    fLumi[1] = hi;
  }
  /// @brief Set limits on pT hat
  void setPtHat(const Double_t &lo = -1e9, const Double_t &hi = 1e9)
  {
    fPtHat[0] = lo;
    fPtHat[1] = hi;
  }
  /// @brief Set limits on event weight
  void setPtHatWeight(const Double_t &lo = -1e9, const Double_t &hi = 1e9)
  {
    fPtHatWeight[0] = lo;
    fPtHatWeight[1] = hi;
  }
  ///@brief Set limits on multiplicity
  void setMultiplicty(const Int_t &low = 0, const Int_t hi = 5000)
  {
    fMultiplicity[0] = low;
    fMultiplicity[1] = hi;
  }
  /// @brief Print information each event
  void setVerbose()
  {
    fVerbose = kTRUE;
  }

  /// @brief Report information about
  void report();
  /// @brief Check if evn
  virtual Bool_t pass(const Event *ev);

private:
  /// @brief Vertex z interval
  Double_t fVz[2];

  /// @brief Beam nominal shift in X direction
  Double_t fShiftVx;
  /// @brief Beam nominal shift in Y direction
  Double_t fShiftVy;
  /// @brief Cut on radial displacement
  Double_t fVR;
  /// @brief Cut on HiBin
  Short_t fHiBin[2];
  /// @brief Cut on centrality values (assuming 0.5% centrality step from 0-100%)
  Double_t fCentVal[2];
  /// @brief Cut on luminosity value
  UInt_t fLumi[2];
  /// @brief PtHat cut
  Double_t fPtHat[2];
  /// @brief Event weight cut
  Double_t fPtHatWeight[2];
  /// @brief  Print information each time
  Bool_t fVerbose;
  /// @brief Multiplicitu cits
  Int_t fMultiplicity[2];

  /// @brief Number of events passed cut
  Long64_t fEventsPassed;
  /// @brief Number of events failed cut
  Long64_t fEventsFailed;

  ClassDef(EventCut, 0)
};

#endif // #define EventCut_h