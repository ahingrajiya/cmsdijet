/**
 * @file GenJet.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Class describes jet from the MС level
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GenJet_h
#define GenJet_h

// ROOT headers
#include "TObject.h"
#include "TVector3.h"

// JetAnalysis headers
#include "BaseJet.h"

//________________
class GenJet : public BaseJet
{
   public:
    /// @brief Constructor
    GenJet();
    /// @brief Destructor
    virtual ~GenJet() { /* Empty*/ }

    //
    // Setters
    //

    void setPtWeight(const Float_t &w) { fPtWeight = {w}; }
    /// @brief Print parameters of the given jet
    void print();

    //
    // Getters
    //
    Float_t ptWeight() const { return fPtWeight; }

   private:
    /// @brief Transverse momentum weight
    Float_t fPtWeight;

    ClassDef(GenJet, 1)
};

#endif