/**
 * @file BaseJet.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Base class for jet description
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_JET_H
#define BASE_JET_H

// ROOT headers
#include "TObject.h"
#include "TVector3.h"

//________________
class BaseJet
{
   public:
    /// @brief Constructor
    BaseJet() noexcept = default;
    /// @brief Destructor
    ~BaseJet() noexcept = default;

    //
    // Setters
    //

    /// @brief Set jet-matched generated jet transverse momentum
    void setPt(float pt) noexcept { fPt = pt; }
    /// @brief Set jet-matched generated jet eta
    void setEta(float eta) noexcept { fEta = eta; }
    /// @brief Set jet-matched generated jet phi
    void setPhi(float phi) noexcept { fPhi = phi; }
    /// @brief Set jet-matched generated jet WTA eta
    void setWTAEta(float eta) noexcept { fWTAEta = eta; }
    /// @brief Set jet-matched generated jet WTA phi
    void setWTAPhi(float phi) noexcept { fWTAPhi = phi; }

    //
    // Getters
    //

    /// @brief Transverse momentum
    float pt() const noexcept { return fPt; }
    /// @brief Pseudorapidity
    float eta() const noexcept { return fEta; }
    /// @brief Azimuthal angle
    float phi() const noexcept { return fPhi; }

    /// @brief Pseudorapidity of the WTA axis
    float WTAEta() const noexcept { return fWTAEta; }
    /// @brief Azimuthal angle of the WTA axis
    float WTAPhi() const noexcept { return fWTAPhi; }

   private:
    /// @brief  Transverse momentum
    float fPt{0.f};
    /// @brief Pseudorapidity
    float fEta{0.f};
    /// @brief Azimuthal angle
    float fPhi{0.f};
    /// @brief Pseudorapidity of the WTA axis
    float fWTAEta{0.f};
    /// @brief Azimuthal angle of the WTA axis
    float fWTAPhi{0.f};
};

#endif