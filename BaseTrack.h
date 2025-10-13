/**
 * @file BaseTrack.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Base class for track descriptions
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef BASE_TRACK_H
#define BASE_TRACK_H

// ROOT Headers

class BaseTrack
{
   public:
    ///@brief Constructor
    BaseTrack() noexcept = default;
    ///@brief Destructor
    ~BaseTrack() noexcept = default;

    ///
    /// Setters
    ///
    ///@brief  Set track transverse momentum
    void setTrackPt(float pt) noexcept { fTrkPt = pt; }
    ///@brief Set track pseudorapidity
    void setTrackEta(float eta) noexcept { fTrkEta = eta; }
    ///@brief Set track phi
    void setTrackPhi(float phi) noexcept { fTrkPhi = phi; }
    ///@brief Set Track Charge
    void setTrackChg(int chg) noexcept { fTrkChg = chg; }
    ///
    /// Getter
    ///
    ///@brief Transverse momentum
    float TrkPt() const noexcept { return fTrkPt; }
    ///@brief Pseudorapidity
    float TrkEta() const noexcept { return fTrkEta; }
    ///@brief Azimuthal Angle
    float TrkPhi() const noexcept { return fTrkPhi; }
    ///@brief Track Charge
    int TrkChg() const noexcept { return fTrkChg; }
    ///@brief Return three vectors of tracks

   private:
    ///@brief  Track  Transverse Momentum
    float fTrkPt{0.0f};
    ///@brief Track Pseudorapidity
    float fTrkEta{0.0f};
    ///@brief Track azimuthal angle
    float fTrkPhi{0.0f};
    ///@brief Track Charge
    int fTrkChg{0};
};
#endif