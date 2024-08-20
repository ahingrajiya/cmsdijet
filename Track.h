/**
 * @file Track.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Track class description
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef Track_h
#define Track_h

// ROOT headers
#include "TObject.h"
#include "BaseTrack.h"

//________________
class Track : public BaseTrack
{
public:
  /// @brief constructor
  Track();
  /// @brief destrucor
  virtual ~Track();

  /// Setter

  /// @brief Set High Purity
  void setHighPurity(const Bool_t &highpurity) { fHighPurity = {highpurity}; }
  ///@brief Set Vertex XY
  void setDxy(const Float_t &vertexDxy) { fVertexDXY = {vertexDxy}; }

  /// Getter
  Bool_t HighPurity() const { return fHighPurity; }

private:
  ///@brief High Purity tracks
  Bool_t fHighPurity;
  ///@brief Associated Vertex XY
  Float_t fVertexDxy;
  /// @brief Assocoaited Vertex XY Error
  Float_t fVertexDxyErr;
  /// @brief Associated Vertex Z
  Float_t fVertexDz;
  ///@brief Associated Vertex Z Error
  Float_t fVertexDzErr;
  ///@brief Hadronic Calorimeter energy
  Float_t fPfHcal;
  ///@brief ElectroMagnetic Calorimeter
  Float_t fPfEcal;
  ///@brief Number of hits
  ClassDef(Track, 1)
};

#endif // #define Track_h