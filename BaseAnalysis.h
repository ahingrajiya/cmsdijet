/**
 * @file BaseAnalysis.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Base class for physics analysis
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_ANALYSIS_H
#define BASE_ANALYSIS_H

#include <memory>
#include <string>
// ROOT headers
#include "TList.h"
#include "TObject.h"

// Forward declaration
class Event;

//_________________
class BaseAnalysis
{
   public:
    /// @brief Default constructor
    BaseAnalysis() = default;
    /// @brief Destructor
    virtual ~BaseAnalysis() = default;

    /// @brief Initialize analysis
    virtual void init() = 0;  ///<

    /// @brief Returns reports of all cuts
    virtual void report() = 0;  //!<

    /// @brief Obtain number of objects to be written as an output
    virtual TList* getOutputList() = 0;  ///<

    /// @brief Event processing
    virtual void processEvent(std::unique_ptr<Event>) = 0;  ///<

    /// @brief Finish analysis
    virtual void finish() = 0;  ///<
};

#endif  // #define BaseAnalysis_h
