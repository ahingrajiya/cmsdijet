/**
 * @file AxisRegistry.h
 * @author Abhishek Hingrajiya (abhi.h123@gmail.com)
 * @brief Axis registry to keep tab of which axis is what in the histograms
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef AXIS_REGISTRY_H
#define AXIS_REGISTRY_H

#include <map>
#include <string>

namespace AxisRegistry
{

const std::map<std::string, int> Quenching = {{"xj", 0}, {"dphi", 1}, {"lead_pt", 2}, {"sublead_pt", 3}, {"multiplicity", 4}};

const std::map<std::string, int> LeadSubLeadJets = {{"lead_pt", 0},     {"lead_eta", 1},    {"lead_phi", 2},    {"sublead_pt", 3},
                                                    {"sublead_eta", 4}, {"sublead_phi", 5}, {"multiplicity", 6}};

const std::map<std::string, int> InclusiveJets = {{"pt", 0},
                                                  {"eta", 1},
                                                  {"phi", 2},
                                                  {"flavor", 3},  // Spans -2 to 2
                                                  {"multiplicity", 4}};

const std::map<std::string, int> Tracks = {{"pt", 0}, {"eta", 1}, {"phi", 2}, {"multiplicity", 3}};

const std::map<std::string, int> Unfolding = {{"ref_xj", 0}, {"reco_xj", 1}, {"multiplicity", 2}, {"lead_pt", 3}};

const std::map<std::string, int> Xj = {{"xj", 0}, {"multiplicity", 1}, {"pt", 2}};
}  // namespace AxisRegistry

#endif