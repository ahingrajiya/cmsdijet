#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class BaseAnalysis + ;
#pragma link C++ class BaseHistoManager + ;
#pragma link C++ class BaseReader + ;
#pragma link C++ class BaseJet + ;
#pragma link C++ class BaseTrack + ;

#pragma link C++ class Event + ;
#pragma link C++ class RecoJet + ;
#pragma link C++ class GenJet + ;
#pragma link C++ class Track + ;
#pragma link C++ class GenTrack + ;

#pragma link C++ class SingleJetCorrector + ;
#pragma link C++ class JetCorrector + ;
#pragma link C++ class JetUncertainty + ;

#pragma link C++ class EventCut + ;
#pragma link C++ class JetCut + ;
#pragma link C++ class TrackCut + ;
#pragma link C++ class DiJetAnalysis + ;
#pragma link C++ class Manager + ;
#pragma link C++ class HistoManagerDiJet + ;
#pragma link C++ class TriggerAndSkim + ;
#pragma link C++ class TrkEff2018PbPb + ;
#pragma link C++ class TrkEfficiency2016pPb + ;

// User-defined classes
#pragma link C++ class ForestAODReader + ;
#pragma link C++ class ForestminiAODReader + ;

#endif