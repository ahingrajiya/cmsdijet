/**
 * @file RecoJet.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Class describes reconstructed jet parameters
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef RecoJet_h
#define RecoJet_h

// ROOT headers
#include "TObject.h"
#include "TVector3.h"

// JetAnalysis headers
#include "BaseJet.h"

//________________
class RecoJet : public BaseJet
{
   public:
    /// @brief Default constructor
    RecoJet();
    /// @brief Destructor
    virtual ~RecoJet() { /* empty */ }

    //
    // Setters
    //

    /// @brief Set reconstructed jet JEC-corrected pt
    void setPtJECCorr(const Float_t &pt) { fPtJECCorr = {pt}; }
    ///@brief Set Ref Jet Pt
    void setRefJetPt(const Float_t &pt) { fRefJetPt = {pt}; }
    ///@brief Set Ref Jet Eta
    void setRefJetEta(const Float_t &eta) { fRefJetEta = {eta}; }
    ///@brief Set Ref Jet Phi
    void setRefJetPhi(const Float_t &phi) { fRefJetPhi = {phi}; }
    ///@brief Set Ref Parton Flavor
    void setJetPartonFlavor(const Int_t &flavor) { fJetPartonFlavor = {flavor}; }
    ///@brief Set Ref Parton FlavorForB
    void setJetPartonFlavorForB(const Int_t &flavor) { fJetPartonFlavorForB = {flavor}; }
    ///@brief Set Jet ID
    void setJetID(const Bool_t &id) { fJetID = {id}; }
    /// @brief Print parameters of the given jet
    void print();

    //
    // Getters
    //

    /// @brief Transverse momentum after JEC
    Float_t ptJECCorr() const { return fPtJECCorr; }
    /// @brief Return reconstructed jet parameters
    TVector3 vecJECCorr() const
    {
        TVector3 v;
        v.SetPtEtaPhi(fPtJECCorr, this->eta(), this->phi());
        return v;
    }
    ///@brief Ref Jet Pt
    Float_t RefJetPt() const { return fRefJetPt; }
    ///@brief Ref Jet Eta
    Float_t RefJetEta() const { return fRefJetEta; }
    ///@brief Ref Jet Phi
    Float_t RefJetPhi() const { return fRefJetPhi; }
    ///@brief Ref Parton Flavor
    Int_t JetPartonFlavor() const { return fJetPartonFlavor; }
    ///@brief Ref Parton FlavorForB
    Int_t JetPartonFlavorForB() const { return fJetPartonFlavorForB; }
    ///@brief Return if Jet ID Passed
    Bool_t JetID() const { return fJetID; }

   private:
    /// @brief Transverse momentum after JEC
    Float_t fPtJECCorr;
    ///@brief Ref Jet Pt
    Float_t fRefJetPt;
    ///@brief fRefJetEta
    Float_t fRefJetEta;
    ///@brief fRefJetPhi
    Float_t fRefJetPhi;
    ///@brief Ref Parton Flavor
    Int_t fJetPartonFlavor;
    /// @brief Flavor for B (-5 - antib, -4 - antic, -3 - antis, -2 - antiu,
    /// -1 - antid, 0 - unknown, 1 - d, 2 - u, 3 - s, 4 - c, 5 - b,
    /// 21 - gluon, -99 for non-matched to RecoJet)
    Int_t fJetPartonFlavorForB;
    /// @brief Jet ID
    Bool_t fJetID;

    ClassDef(RecoJet, 1)
};

#endif  // #define RecoJet_h
