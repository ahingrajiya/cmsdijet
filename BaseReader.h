/**
 * @file BaseReader.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief Base class for event readers
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BASE_READER_H
#define BASE_READER_H

// JetAnalysis headers
#include "Event.h"
// C++ headers
#include <iostream>
#include <memory>

//_________________
class BaseReader
{
   public:
    /// @brief Default constructor
    BaseReader() : fReaderStatus{0} {};
    /// @brief Destructor
    virtual ~BaseReader() noexcept = default;

    /// @brief Read and return a pointer to the Event from the given event
    /// @return Instance of Event class
    virtual std::unique_ptr<Event> returnEvent() = 0;

    /// @brief Initialize event reader
    /// @return Base return function
    virtual int init()
    {
        std::cout << "BaseReader::init() - Do nothing\n";
        return 0;
    }

    /// @brief Finish reading
    virtual void finish() { /* empty*/ }

    /// @brief Return reader status
    /// @return 0 - good, else - bad
    int status() const noexcept { return fReaderStatus; }

    /// @brief Report reader status including cuts
    virtual void report() { std::cout << "\nReporting from the BaseReader class\n" << std::endl; }

    virtual long long nEventsTotal() const noexcept { return 0; }

   protected:
    /// @brief Reader status. 0 - good, 1 - error, 2 - EOF
    int fReaderStatus;
};

#endif  // #define BASE_READER_H