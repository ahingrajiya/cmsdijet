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
#include "BaseTrack.h"
#include "TObject.h"

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
    void setTrackHighPurity(const Bool_t &highpurity) { fHighPurity = {highpurity}; }
    ///@brief Set AssociatedVertex XY
    void setTrackDxy(const Float_t &vertexDxy) { fVertexDxy = {vertexDxy}; }
    ///@brief Set Associated Vertex XY Errors
    void setTrackDxyErr(const Float_t &vertexDxyErr) { fVertexDxyErr = {vertexDxyErr}; }
    ///@brief Set Associated Vertex Z
    void setTrackDz(const Float_t &vertexDz) { fVertexDz = {vertexDz}; }
    ///@brief Set Associated Vertex Z Errors
    void setTrackDzErr(const Float_t &vertexDzErr) { fVertexDzErr = {vertexDzErr}; }
    ///@brief Set Hadronic Calorimeter energy
    void setTrackpfHcal(const Float_t &trkpfHcal) { fTrkpfHcal = {trkpfHcal}; }
    ///@brief Set Electromagnetic Calorimeter Energy
    void setTrackpfEcal(const Float_t &trkpfEcal) { fTrkpfEcal = {trkpfEcal}; }
    ///@brief Set Number of Hits
    void setTrackNHits(const UChar_t &trkNHits) { fTrkNHits = {trkNHits}; }
    ///@brief Set Normalized Chi2
    void setTrackChi2(const Float_t &trkNormChi2) { fTrkNormChi2 = {trkNormChi2}; }
    ///@brief Set Number of Layers
    void setTrackNLayers(const UChar_t &trkNLayers) { fTrkNLayers = {trkNLayers}; }
    ///@brief Set Number of degrees of freedom in track fitting
    void setTrackNDOF(const UChar_t &trkNDOF) { fTrkNDOF = {trkNDOF}; }
    ///@brief Set Track MVA
    void setTrackMVA(const Float_t &trkMVA) { fTrkMVA = {trkMVA}; }
    ///@brief Set Track Algortihms
    void setTrackAlgo(const UChar_t &trkAlgo) { fTrkAlgo = {trkAlgo}; }
    ///@brief Set Track Pt Error
    void setTrackPtErr(const Float_t &trkPtErr) { fTrkPtErr = {trkPtErr}; }

    /// Getter

    /// Get High Purity
    Bool_t TrackHighPurity() const { return fHighPurity; }
    /// Get Track Pt Error
    Float_t TrackPtErro() const { return fTrkPtErr; }
    /// Get Associated vertex XY
    Float_t TrackVertexDxy() const { return fVertexDxy; }
    /// Get Associated vertex XY Error
    Float_t TrackVertexDxyErr() const { return fVertexDxyErr; }
    /// Get Associated vertex Z
    Float_t TrackVertexDz() const { return fVertexDz; }
    /// Get Associated vertex Z Error
    Float_t TrackVertexDzErr() const { return fVertexDzErr; }
    /// Get Hadronic Calorimeter Energy
    Float_t TrackpfHcal() const { return fTrkpfHcal; }
    /// Get Electromagentic Calorimeter Energy
    Float_t TrackpfEcal() const { return fTrkpfEcal; }
    /// Get Number of Hits
    Char_t TrackNhits() const { return fTrkNHits; }
    /// Get Normalized Chi2
    Float_t TrackChi2() const { return fTrkNormChi2; }
    /// Get Number of Layers
    Char_t TrackNLayers() const { return fTrkNLayers; }
    /// Get Track NDOF
    UChar_t TrackNDOF() const { return fTrkNDOF; }
    /// Get Track MVA
    Float_t TrackMVA() const { return fTrkMVA; }
    /// Get Track Algo
    UChar_t TrackAlgo() const { return fTrkAlgo; }

   private:
    ///@brief High Purity tracks
    Bool_t fHighPurity;
    ///@brief Track Pt Error
    Float_t fTrkPtErr;
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
    UChar_t fTrkNHits;
    ///@brief Normalized Chi2
    Float_t fTrkNormChi2;
    ///@brief Number of Layers
    UChar_t fTrkNLayers;
    ///@brief Number of degrees of freedom
    UChar_t fTrkNDOF;
    ///@brief Track MVA for each step
    Float_t fTrkMVA;
    ///@brief Track algorithms/step
    UChar_t fTrkAlgo;
    ClassDef(Track, 1)
};

#endif  // #define Track_h