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
  virtual ~Track() {}

  /// Setter

  /// @brief Set High Purity
  void setHighPurity(const Bool_t &highpurity) { fHighPurity = {highpurity}; }
  ///@brief Set AssociatedVertex XY
  void setDxy(const Float_t &vertexDxy) { fVertexDxy = {vertexDxy}; }
  ///@brief Set Associated Vertex XY Errors
  void setDxyErr(const Float_t &vertexDxyErr) { fVertexDxyErr = {vertexDxyErr}; }
  ///@brief Set Associated Vertex Z
  void setDz(const Float_t &vertexDz) { fVertexDz = {vertexDz}; }
  ///@brief Set Associated Vertex Z Errors
  void setDzErr(const Float_t &vertexDzErr) { fVertexDzErr = {vertexDzErr}; }
  ///@brief Set Hadronic Calorimeter energy
  void setpfHcal(const Float_t &trkpfHcal) { fTrkpfHcal = {trkpfHcal}; }
  ///@brief Set Electromagnetic Calorimeter Energy
  void setpfEcal(const Float_t &trkpfEcal) { fTrkpfEcal = {trkpfEcal}; }
  ///@brief Set Number of Hits
  void setNHits(const Char_t &trkNHits) { fTrkNHits = {fTrkNHits}; }
  ///@brief Set Normalized Chi2
  void setChi2(const Float_t &trkNormChi2) { fTrkNormChi2 = {trkNormChi2}; }
  ///@brief Set Number of Layers
  void setNLayers(const Char_t &trkNLayers) { fTrkNLayers = {trkNLayers}; }

  /// Getter

  /// Get High Purity
  Bool_t HighPurity() const { return fHighPurity; }
  /// Get Associated vertex XY
  Float_t VertexDxy() const { return fVertexDxy; }
  /// Get Associated vertex XY Error
  Float_t VertexDxyErr() const { return fVertexDxyErr; }
  /// Get Associated vertex Z
  Float_t VertexDz() const { return fVertexDz; }
  /// Get Associated vertex Z Error
  Float_t VertexDzErr() const { return fVertexDzErr; }
  /// Get Hadronic Calorimeter Energy
  Float_t pfHcal() const { return fTrkpfHcal; }
  /// Get Electromagentic Calorimeter Energy
  Float_t pfEcal() const { return fTrkpfEcal; }
  /// Get Number of Hits
  Char_t Nhits() const { return fTrkNHits; }
  /// Get Normalized Chi2
  Float_t Chi2() const { return fTrkNormChi2; }
  /// Get Number of Layers
  Char_t NLayers() const { return fTrkNLayers; }

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
  Float_t fTrkpfHcal;
  ///@brief ElectroMagnetic Calorimeter
  Float_t fTrkpfEcal;
  ///@brief Number of hits
  Char_t fTrkNHits;
  ///@brief Normalized Chi2
  Float_t fTrkNormChi2;
  ///@brief Number of Layers
  Char_t fTrkNLayers;

  ClassDef(Track, 1)
};

#endif // #define Track_h