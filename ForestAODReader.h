/**
 * @file ForestAODReader.h
 * @author Grigory Nigmatkulov (gnigmat@uic.edu)
 * @brief CMS ForestAOD reader
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef ForestAODReader_h
#define ForestAODReader_h

// ROOT headers
#include "Rtypes.h"
#include "TChain.h"
#include "TString.h"
#include "TRandom3.h"
// JetAnalysis headers
#include "BaseReader.h"
#include "Event.h"
#include "EventCut.h"
#include "JetCut.h"
#include "TrackCut.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"

// C++ headers
#include <list>

//_________________
class ForestAODReader : public BaseReader
{

public:
  /// @brief Default constructor
  ForestAODReader();
  /// @brief Constructor for ForestAODReader
  /// @param inputStream Input file (.root) or list of ROOT files that contain CMS ForestAOD
  ForestAODReader(const Char_t *inputStream,
                  const Bool_t &useHltBranch = kFALSE, const Bool_t &useSkimmingBranch = kFALSE,
                  const Char_t *jetCollection = "ak4PFJetAnalyzer", const Bool_t &useJets = kFALSE,
                  const Bool_t &useTrackBranch = kFALSE, const Bool_t &useGenTrackBranch = kFALSE,
                  const Bool_t &isMc = kFALSE, const Bool_t &setStoreLocation = kFALSE, const Bool_t &useMatchedJets = kFALSE);
  /// @brief Destructor
  virtual ~ForestAODReader();

  /// @brief  Initialize input
  Int_t init();
  /// @brief Finish (print final information)
  void finish();
  /// Read event and fill objects
  Event *returnEvent();
  /// @brief Report event from reader
  void report();

  /// Turn-on HLT branch to be read
  void useHltBranch() { fUseHltBranch = {kTRUE}; }

  void useSkimmingBranch() { fUseSkimmingBranch = {kTRUE}; }
  /// Turn-on particle flow branch to be read
  ///@brief Set Jet Collection name
  void setJetCollectionBranchName(const Char_t *name = "ak4PFJetAnalyzer")
  {
    fJetCollection = name;
  }
  /// @brief Turn on the usage of jets for the analysis
  void useJets()
  {
    fUseJets = {kTRUE};
  }
  /// @brief Uswe gen track branch
  void useGenTrackBranch() { fUseGenTrackBranch = {kTRUE}; }
  /// Turn-on calorimeter jet branch to be read
  void useTrackBranch() { fUseTrackBranch = {kTRUE}; }

  /// @brief Set colliding system
  void setCollidingSystem(const Char_t *sys = "PbPb")
  {
    fCollidingSystem = sys;
    fIs_pp = kFALSE;
    fIs_pPb = kFALSE;
    fIs_PbPb = kFALSE;

    // Set only the matching flag
    std::string systemStr(sys);

    if (systemStr == "pp")
    {
      fIs_pp = kTRUE;
    }
    else if (systemStr == "pPb")
    {
      fIs_pPb = kTRUE;
    }
    else if (systemStr == "PbPb")
    {
      fIs_PbPb = kTRUE;
    }
    else
    {
      std::cerr << "Unknown colliding system: " << systemStr << std::endl;
    }
  }
  /// @brief Set colliding energy
  void setCollidingEnergy(const Int_t &ene = 5020) { fCollidingEnergyGeV = {ene}; }
  /// @brief Set year of data taking
  void setYearOfDataTaking(const Int_t &year = 2018) { fYearOfDataTaking = {year}; }
  ///@brief Set Path to jet analysis directory
  void setPath2JetAnalysis(const Char_t *name = "../") { fJECPath = name; }
  ///@brief Add JEC files to the list of JEC files
  void addJECFile(const Char_t *name = "Autumn18_HI_V8_MC_L2Relative_AK4PF") { fJECFiles.push_back(name); }
  ///@brief Add JEU files to the list of JEU files
  void addJEUFile(const Char_t *name = "Autumn18_HI_V8_MC_L2Relative_AK4PF")
  {
    fJEUFiles.push_back(name);
  }
  /// @brief Apply jet pT-smearing
  void setJetPtSmearing(const Bool_t &isSmear = kFALSE, const Int_t &smearType = 0)
  {
    fDoJetPtSmearing = {isSmear};
    fSmearType = {smearType};
  }
  /// @brief Set event cut
  void setEventCut(EventCut *cut) { fEventCut = {cut}; }
  /// @brief Set jet cut
  void setJetCut(JetCut *cut) { fJetCut = {cut}; }
  /// @brief Is the dataset from MC
  void setIsMc(const Bool_t &isMc) { fIsMc = {isMc}; }
  /// @brief Fix jet arrays
  void fixJetArrays() { fFixJetArrays = {kTRUE}; }
  ///@brief Set Track Cut
  void setTrackCut(TrackCut *cut) { fTrackCut = {cut}; }
  ///@brief Set Use Matched Jets
  void setMatchedJets() { fUseMatchedJets = {kTRUE}; }

  ///@brief Events to process
  void eventsToProcess(const Long64_t &nEvents)
  {
    fEventsToProcess = {nEvents};
  }
  /// @brief Return amount of events to read
  Long64_t nEventsTotal() const { return fEvents2Read; }

  void setStoreLocation(const Bool_t isInStore)
  {
    fIsInStore = {isInStore};
  }
  /// @brief  Seet to use Jet ID
  /// @param useJetID True when using JetID selection
  void setUseJetID() { fUseJetID = {kTRUE}; }

  /// @brief Set Jet ID Type
  void setJetIDType(const Int_t &jetIDType) { fJetIDType = {jetIDType}; }

  ///@brief Set Shift in HiBin
  void setShiftInHiBin(const Int_t &shift) { fHiBinShift = {shift}; }

  ///@brief Set Filter names
  void setFilters(const std::vector<std::string> &filters) { fFilters = filters; }

  ///@brief Set Trigger names
  void setTriggers(const std::vector<std::string> &triggers) { fTriggers = triggers; }

  /// @brief Set JES corrections
  void setJESCorrections()
  {
    fApplyJetJESCorrections = kTRUE;
  }

  void setJEU(const Bool_t &doJEU = kFALSE, const Int_t &useJEU = 0)
  {
    fDoJEU = {doJEU};
    fJEUType = {useJEU};
  }

private:
  /// @brief Setup input stream (either single file or a list of files)
  void
  setInputStream(const Char_t *inputStream)
  {
    fInFileName = {inputStream};
  }

  /// Setup input all input
  void setupInput(TString input, TChain *hltChain, TChain *eveChain, TChain *partFlowChain,
                  TChain *trkChain, Bool_t useMC, TChain *genTrkChain);
  /// Setup chains to be filled
  Int_t setupChains();
  /// Setup branches
  void setupBranches();

  /// @brief Clear variables for reading
  void clearVariables();
  /// @brief Fix jet arrays
  void fixIndices();

  /// @brief Call read event
  void readEvent();

  /// @brief Setup JEC
  void setupJEC();
  /// @brief Setup JEU
  void setupJEU();

  /// @brief Calculate event weight
  /// @param isMC Is MC sample
  /// @param use_centrality If use centrality instead of multiplicity
  /// @param system Colliding system (pp, pPb or PbPb)
  /// @param year Year of the data taking
  /// @param energy Colliding energy (in GeV)
  /// @param vz Vertex Z position
  /// @param mult Charge particle multiplicity
  /// @param weighttree PtHat of the event (for MC only)
  /// @param leadjetpt Leading jet pT
  Float_t eventWeight(const Bool_t &isMC, const Bool_t &use_centrality, const std::string &system,
                      const Int_t &year, const Int_t &energy, const Float_t &vz,
                      const Int_t mult, const Float_t &weighttree, const Float_t &leadjetpt) const;
  /// @brief For compatibility between MC reco and data
  /// @param isMC
  /// @param system
  /// @param year
  /// @param energy
  /// @param jetpt
  Float_t jetPtWeight(const Bool_t &isMC, const std::string &system, const Int_t &year,
                      const Int_t &energy, float jetpt) const;
  /// @brief For compatibility between MC RECO and Data
  /// @param isMC Is MC sample
  /// @param system Colliding system (pp, pPb or PbPb)
  /// @param year Year of the data taking
  /// @param energy Colliding energy (in GeV)
  /// @param leadjetpt Leading jet pT
  Float_t leadJetPtWeight(const Bool_t &isMC, const std::string &system, const Int_t &year,
                          const Int_t &energy, const Float_t &leadjetpt) const;
  /// @brief For compatibility between MC RECO and Data
  /// @param isMC Is MC sample
  /// @param system Colliding system (pp, pPb or PbPb)
  /// @param year Year of the data taking
  /// @param energy Colliding energy (in GeV)
  /// @param subleadjetpt Leading jet pT
  Float_t subleadJetPtWeight(const Bool_t &isMC, const std::string &system, const Int_t &year,
                             const Int_t &energy, const Float_t &subleadjetpt) const;
  /// @brief Jet smearing resolution effect
  /// @param refPt RefPt for the reco Jet Pt
  /// @param jeteta Jet eta
  /// @param dosmearing Apply smearing
  Float_t jetPtSmering(const Float_t &refPt, const Float_t &jeteta, const Bool_t &dosmearing) const;
  /// @brief Track mixing effect (Seagull)
  /// @param isMC True for MC and false for Data
  /// @param system Colliding system (pp, pPb or PbPb)
  /// @param year Year of the data taking
  /// @param energy Colliding energy (in GeV)
  /// @param trketa Track eta
  /// @param reco Is reco track
  Float_t trkEtaMixWeight(const Bool_t &isMC, const std::string &system, const Int_t &year,
                          const Int_t &energy, const Float_t &trketa, const Bool_t &reco) const;

  /// @brief ppJetID Functions
  /// @param jtNHF Neutral Hadron Fraction
  /// @param jtNEF Neutral EM Fraction
  /// @param jtCHF Charged Hadron Fraction
  /// @param jtMUF Muon Fraction
  /// @param jtCEF Charged EM Fraction
  /// @param jtCHM Charged Hadron Multiplicity
  /// @param jtCEM Charged EM Multiplicity
  /// @param jtNHM Neutral Hadron Multiplicity
  /// @param jtNEM Neutral EM Multiplicity
  /// @param jtMUM Muon Multiplicity
  /// @param jetEta Jet Eta
  /// @return Return True if jet passes the ID
  Bool_t JetIDType2(const Float_t &jtNHF, const Float_t &jtNEF, const Float_t &jtCHF, const Float_t &jtMUF, const Float_t &jtCEF,
                    const Int_t &jtCHM, const Int_t &jtCEM, const Int_t &jtNHM, const Int_t &jtNEM, const Int_t &jtMUM, const Float_t &jetEta);
  /// @brief PbPbJetID Functions
  /// @param jetTrackMax pt track in the jet
  /// @param jetRawPt raw jet pt
  Bool_t JetIDType1(const Float_t &jetTrackMax, const Float_t &jetRawPt);
  /// @brief Jet JES Correction applied to akCs4PF ONLY to pPb
  /// @param jetPt corrected jet pT
  /// @return A correction factor that needs to be applied to the jet pT
  Float_t JetJESCorrections(const Float_t &jetPt);
  /// @brief Set Up all the functions for weighting
  void SetUpWeightFunctions();
  /// @brief Setting Up jet Smearing
  void setUpJER();
  /// @brief JER resolution factor retrival
  /// @param jeteta Jet Eta
  Double_t retriveResolutionFactor(const Float_t &jeteta) const;

  /// @brief Event with jets and other variables
  Event *fEvent;
  /// @brief Input filename (name.root) or file with list of ROOT files
  const Char_t *fInFileName;
  ///@brief If input file is in store/user location then add the string to file path to open the file
  Bool_t fIsInStore;
  /// @brief Number of events to process from input file(s)
  Long64_t fEvents2Read;
  /// @brief How many events were processed
  Long64_t fEventsProcessed;
  /// @brief How many events to process
  Long64_t fEventsToProcess;

  /// @brief Is file with MC information
  Bool_t fIsMc;

  /// @brief Switch HLT branch ON
  Bool_t fUseHltBranch;
  /// @brief Switch skimming branch ON
  Bool_t fUseSkimmingBranch;
  /// @brief Switch particle flow jet branch ON
  Bool_t fUseJets;
  ///@brief Use matched jets (Only applicable for MC)
  Bool_t fUseMatchedJets;
  /// @brief Switch track branch ON
  Bool_t fUseTrackBranch;
  /// @brief Switch MC track branch ON
  Bool_t fUseGenTrackBranch;

  /// @brief Chain conaining HLT information (used to friend other trees)
  TChain *fHltTree;
  /// @brief Chain containing skimming information
  TChain *fSkimTree;
  /// @brief Chain containing event information
  TChain *fEventTree;
  /// @brief Chain containing jets
  TChain *fJetTree;
  /// @brief Chain containing tracks
  TChain *fTrkTree;
  /// @brief Chain containing Monte Carlo tracks
  TChain *fGenTrkTree;

  /// @brief Name of the particle flow tree (e.g. akCs4PFJetAnalyzer for PbPb or ak4PFJetAnalyzer for pp)
  TString fJetCollection;

  //
  // Variables to store information from TTree
  //

  //
  // Event quantities
  //

  /// @brief Run ID
  UInt_t fRunId;
  /// @brief Event ID
  ULong64_t fEventId;
  /// @brief Luminosity
  UInt_t fLumi;
  /// @brief Vertex position z
  Float_t fVertexZ;
  /// @brief Collision centrality (0-200)
  Int_t fHiBin;
  /// @brief Collision Centrality Shift
  Int_t fHiBinShift;
  /// @brief Event weight (prescale from generator level)
  Float_t fPtHatWeight;
  /// @brief ptHat (initial parton pT) - from generator level
  Float_t fPtHat;

  //
  // Trigger and skimming information

  std::vector<std::string> fTriggers;
  Int_t *fTriggerPointers;

  // Skimanalysis part
  std::vector<std::string> fFilters;
  Int_t *fFilterPointers;

  //
  // Jet information
  //

  /// @brief Number of reconstructed jets
  Int_t fNRecoJets;
  /// @brief Reconstructed jet transverse momentum (with JEC)
  Float_t fRecoJetPt[1000];
  /// @brief Reconstructed jet uncorrected transverse momentume  (without JEC)
  Float_t fRawJetPt[1000];
  /// @brief Pseudorapidity of reconstructed jet
  Float_t fRecoJetEta[1000];
  /// @brief Azimuthal angle of reconstructed jet
  Float_t fRecoJetPhi[1000];
  /// @brief WTA eta of reconstructed jet
  Float_t fRecoJetWTAEta[1000];
  /// @brief WTA phi of reconstructed jet
  Float_t fRecoJetWTAPhi[1000];
  /// @brief Track with maximum pT in reconstructed jet
  Float_t fRecoJetTrackMax[1000];
  /// @brief Neutron hadron fraction in the jet
  Float_t fRecoPfNHF[1000];
  /// @brief Neutron EM fraction in the jet
  Float_t fRecoPfNEF[1000];
  ///@brief Charged hadron fraction in the jet
  Float_t fRecoPfCHF[1000];
  ///@brief Charged mu fraction in the jet
  Float_t fRecoPfMUF[1000];
  ///@brief Charged EM fraction in the jet
  Float_t fRecoPfCEF[1000];
  /// @brief Charged hadron multiplicity in the jet
  Int_t fRecoPfCHM[1000];
  /// @brief Charged EM multiplicity in the jet
  Int_t fRecoPfCEM[1000];
  /// @brief Neutron hadron multiplicity in the jet
  Int_t fRecoPfNHM[1000];
  /// @brief Neutron EM multiplicity in the jet
  Int_t fRecoPfNEM[1000];
  /// @brief Muon multiplicity in the jet
  Int_t fRecoPfMUM[1000];

  /// @brief Transverse momentum of generated jet that was matched with
  /// reconstructed jet
  Float_t fRefJetPt[1000];
  /// @brief Pseudorapidity of generated jet that was matched with
  /// reconstructed jet
  Float_t fRefJetEta[1000];
  /// @brief Azimuthal angle of generated jet that was matched with
  /// reconstructed jet
  Float_t fRefJetPhi[1000];
  /// @brief WTA eta of generated jet that was matched with reconstructed jet
  Float_t fRefJetWTAEta[1000];
  /// @brief WTA phi of generated jet that was matched with reconstructed jet
  Float_t fRefJetWTAPhi[1000];
  /// @brief Parton flavor of generated jet that was matched with reconstructed
  /// jet
  Int_t fRefJetPartonFlavor[1000];
  /// @brief Parton flavor for B of generated jet that was matched with
  /// reconstructed jet
  Int_t fRefJetPartonFlavorForB[1000];

  /// @brief Number of generated jets
  Int_t fNGenJets;
  /// @brief Generated jet transverse momentum
  Float_t fGenJetPt[1000];
  /// @brief Pseudorapidity of generated jet
  Float_t fGenJetEta[1000];
  /// @brief Azimuthal angle of generated jet
  Float_t fGenJetPhi[1000];
  /// @brief WTA eta of generated jet
  Float_t fGenJetWTAEta[1000];
  /// @brief WTA phi of generated jet
  Float_t fGenJetWTAPhi[1000];

  //
  // Reconstructed tracks
  //

  /// @brief Number of tracks
  Int_t fNTracks;
  /// @brief Track transverse momentum
  Float_t fTrackPt[29999];
  /// @brief Track pseudorapidity
  Float_t fTrackEta[29999];
  /// @brief Track azimuthal angle
  Float_t fTrackPhi[29999];
  /// @brief Track pT error (uncertainty)
  Float_t fTrackPtErr[29999];
  /// @brief Track distance of closest approach in transverse plane (XY)
  Float_t fTrackDcaXY[29999];
  /// @brief Track distance of closest approach in beam direction (z)
  Float_t fTrackDcaZ[29999];
  /// @brief Track distance of closest approach error in transverse plane (XY)
  Float_t fTrackDcaXYErr[29999];
  /// @brief Track distance of closest approach error in beam direction (z)
  Float_t fTrackDcaZErr[29999];
  /// @brief Track fitting (reconstruction) chi2
  Float_t fTrackChi2[29999];
  /// @brief Track number of degrees of freedom in the fitting
  UChar_t fTrackNDOF[29999];
  /// @brief Particle flow energy deposited in ECAL from the given track
  Float_t fTrackPartFlowEcal[29999];
  /// @brief Particle flow energy deposited in HCAL from the given track
  Float_t fTrackPartFlowHcal[29999];
  /// @brief Track MVA for each step
  Float_t fTrackMVA[29999];
  /// @brief Track algorithm/step
  UChar_t fTrackAlgo[29999];
  /// @brief Track charge
  Int_t fTrackCharge[29999];
  /// @brief Number of hits in the tracker
  UChar_t fTrackNHits[29999];
  /// @brief Number of layers with measurement in the tracker
  UChar_t fTrackNLayers[29999];
  /// @brief Tracker steps MVA selection
  Bool_t fTrackHighPurity[29999];

  //
  // Monte Carlo tracks
  //

  /// @brief Generated particle transverse momentum
  std::vector<Float_t> *fGenTrackPt = new std::vector<Float_t>();
  /// @brief Generated particle pseudorapidity
  std::vector<Float_t> *fGenTrackEta = new std::vector<Float_t>();
  /// @brief Generated particle azimuthal angle
  std::vector<Float_t> *fGenTrackPhi = new std::vector<Float_t>();
  /// @brief Generated particle charge
  std::vector<Int_t> *fGenTrackCharge = new std::vector<Int_t>();
  /// @brief Generated particle PID
  std::vector<Int_t> *fGenTrackPid = new std::vector<Int_t>();
  /// @brief Generated particle sube (?)
  std::vector<Int_t> *fGenTrackSube = new std::vector<Int_t>();

  /// @brief Jet Energy Corrector instance
  JetCorrector *fJEC;
  /// @brief Path to jetAnalysis directory
  TString fJECPath;
  /// @brief List of files with JEC
  std::vector<std::string> fJECFiles;

  /// @brief Jet Energy Uncertainty instance
  JetUncertainty *fJEU;
  /// @brief List of files with JEU
  std::vector<std::string> fJEUFiles;

  /// @brief Colliding system: pp, pPb or PbPb
  TString fCollidingSystem;
  /// @brief Colliding energy
  Int_t fCollidingEnergyGeV;
  /// @brief Year of data taking
  Int_t fYearOfDataTaking;
  /// @brief Fix indices
  Bool_t fFixJetArrays;
  /// @brief Event cut
  EventCut *fEventCut;
  /// @brief Jet cut
  JetCut *fJetCut;
  ///@brief Track cut
  TrackCut *fTrackCut;

  ///@brief Use Jet ID cut
  Bool_t fUseJetID;
  ///@brief Jet ID Type
  /// 1 = Track Max and Track Min cut
  /// 2 = pp Jet ID Cuts provided by CMS
  Int_t fJetIDType;
  /// @brief Vector that contains indices of generated jets that matched to the
  /// reconsructed jet (should be of the reco/red size)
  std::vector<Int_t> fRecoJet2GenJetId;
  /// @brief Vector that contains indices of the reconstructed
  /// jets that macthed to generated jet
  std::vector<Int_t> fGenJet2RecoJet;

  /// @brief Booleans to set colliding systems.
  Bool_t fIs_pPb;
  Bool_t fIs_pp;
  Bool_t fIs_PbPb;

  /// @brief Jet JES Corrections function applied only to AKCS4PF jets in pPb systems
  TF1 *fJetJESCorrectionsFunction;

  /// @brief Boolean to set if jet energy scale corrections needs to be applied
  Bool_t fApplyJetJESCorrections;

  ///@brief JER Smearing Eta Edges
  std::vector<Float_t> fJERSmearingEtaEdges;
  ///@brief JER Smearing Nominal Factors
  std::vector<Float_t> fJERSmearingNomial;
  ///@brief JER Smearing Up Factors
  std::vector<Float_t> fJERSmearingUp;
  ///@brief JER Smearing Down Factors
  std::vector<Float_t> fJERSmearingDown;
  /// @brief Apply jet pT-smearing
  Bool_t fDoJetPtSmearing;
  ///@brief Smearing resolution factor up, down or nominal
  Int_t fSmearType;
  ///@brief Smear Function
  TF1 *fJetPtSmearingFunction;
  ///@brief Trandom number generator
  TRandom3 *fRandom;

  /// @brief Use JEU
  Int_t fJEUType; // 0 - no, 1 - Up, -1 - down
  /// @brief Do JEU
  Bool_t fDoJEU;

  ClassDef(ForestAODReader, 1)
};

#endif // #define ForestAODReader_h