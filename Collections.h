/**
 * @file Collections.h
 * @author Grigory Nigmatkulov (you@domain.com)
 * @brief Header that contains definition of collection wrappers
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef COLLECTIONS_H
#define COLLECTIONS_H

// Jeta analysis headers
#include "BaseAnalysis.h"
#include "GenJet.h"
#include "GenTrack.h"
#include "RecoJet.h"
#include "Track.h"

// C++ headers
#include <memory>
#include <vector>

// ============================================================================
// Analysis collections
// ============================================================================
using AnalysisCollection = std::vector<std::unique_ptr<BaseAnalysis>>;

// ============================================================================
// Jet collections
// ============================================================================
using RecoJetCollection = std::vector<std::unique_ptr<RecoJet>>;
using GenJetCollection = std::vector<std::unique_ptr<GenJet>>;

// ============================================================================
// Track collections
// ============================================================================
using TrackCollection = std::vector<std::unique_ptr<Track>>;
using GenTrackCollection = std::vector<std::unique_ptr<GenTrack>>;

#endif  // #define COLLECTIONS_H