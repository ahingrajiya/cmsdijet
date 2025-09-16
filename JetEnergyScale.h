/**
 * @file JetEnergyScale.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Derive Jet Energy Scale and Jet Energy Resolution
 * @version 0.1
 * @date 2025-09-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef JETENERGYSCALE_H
#define JETENERGYSCALE_H

#include "common.hpp"

class JetEnergyScale
{
   public:
    JetEnergyScale();
    virtual ~JetEnergyScale();

   private:
    TFile *file_input;
    TFile *file_output;
};

#endif  // JETENERGYSCALE_H