/**
 * File              : AliAnalysisTaskAR.h
 * Author            : Anton Riedel <anton.riedel@tum.de>
 * Date              : 07.05.2021
 * Last Modified Date: 27.07.2021
 * Last Modified By  : Anton Riedel <anton.riedel@tum.de>
 */

/*
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved.
 * See cxx source for full Copyright notice
 * $Id$
 */

#ifndef ALIANALYSISTASKAR_H
#define ALIANALYSISTASKAR_H

#include "AliAODEvent.h"
#include "AliAODTrack.h"
#include "AliAnalysisTaskSE.h"
#include "AliVEvent.h"
#include <Riostream.h>
#include <TComplex.h>
#include <TDataType.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TRandom3.h>
#include <TString.h>

// global constants
const Int_t kMaxHarmonic = 20;
const Int_t kMaxCorrelator = 20;
const Int_t kMaxPower = 20;
const Int_t kMaxFilterbit = 11; // 2^(11-1)=1024
const Int_t kNumberofTestFilterBit = 5;
const Int_t kTestFilterbit[5] = {1, 128, 256, 512, 768};
// enumerations
enum kCenEstimators { kV0M, kCL0, kCL1, kSPDTRACKLETS, LAST_ECENESTIMATORS };
enum kEvent { kCEN, kMUL, kNCONTRIB, LAST_EEVENT };
enum kTrack {
  kPT,
  kPHI,
  kETA,
  kTPCNCLS,
  kITSNCLS,
  kCHI2PERNDF,
  kDCAZ,
  kDCAXY,
  LAST_ETRACK
};
const Int_t kKinematic = kETA + 1;
enum kXYZ { kX, kY, kZ, LAST_EXYZ };
enum kFinalHist { kPHIAVG, LAST_EFINALHIST };
enum kFinalProfile { kHARDATA, kHARDATARESET, kHARTHEO, LAST_EFINALPROFILE };
enum kBins { kBIN, kLEDGE, kUEDGE, LAST_EBINS };
enum kName { kNAME, kTITLE, kXAXIS, kYAXIS, LAST_ENAME };
enum kBeforeAfter { kBEFORE, kAFTER, LAST_EBEFOREAFTER };
const TString kBAName[LAST_EBEFOREAFTER] = {"[kBEFORE]", "[kAFTER]"};
const Color_t kFillColor[LAST_EBEFOREAFTER] = {kRed - 10, kGreen - 10};
enum kMinMax { kMIN, kMAX, LAST_EMINMAX };

class AliAnalysisTaskAR : public AliAnalysisTaskSE {
public:
  AliAnalysisTaskAR();
  AliAnalysisTaskAR(const char *name, Bool_t useParticleWeights = kFALSE);
  virtual ~AliAnalysisTaskAR();
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *);
  virtual void Terminate(Option_t *);

  // Methods called in the constructor:
  virtual void InitializeArrays();
  virtual void InitializeArraysForQAHistograms();
  virtual void InitializeArraysForTrackControlHistograms();
  virtual void InitializeArraysForEventControlHistograms();
  virtual void InitializeArraysForCuts();
  virtual void InitializeArraysForQvectors();
  virtual void InitializeArraysForFinalResultHistograms();
  virtual void InitializeArraysForFinalResultProfiles();
  virtual void InitializeArraysForMCAnalysis();

  // Methods called in UserCreateOutputObjects():
  virtual void BookAndNestAllLists();
  virtual void BookQAHistograms();
  virtual void BookControlHistograms();
  virtual void BookFinalResultHistograms();
  virtual void BookFinalResultProfiles();
  virtual void BookMCObjects();

  // functions called in UserExec()
  virtual void FillEventQAHistograms(kBeforeAfter BA, AliAODEvent *event);
  virtual void FillFBScanQAHistograms(AliAODTrack *track);
  virtual void FillEventControlHistograms(kBeforeAfter BA, AliAODEvent *event);
  virtual void FillTrackControlHistograms(kBeforeAfter BA, AliAODTrack *track);
  virtual void FillFinalResultProfile(kFinalProfile fp);
  virtual void MCOnTheFlyExec();

  // methods called in AODExec():
  virtual Bool_t SurviveEventCut(AliVEvent *ave);
  virtual Bool_t SurviveTrackCut(AliAODTrack *aTrack);

  // methods called MCOnTheFlyExec()
  virtual void MCPdfSymmetryPlanesSetup();
  virtual Int_t GetMCNumberOfParticlesPerEvent();

  // Methods for computing qvectors
  void CalculateQvectors();
  TComplex Q(Int_t n, Int_t p);
  TComplex Two(Int_t n1, Int_t n2);
  TComplex Three(Int_t n1, Int_t n2, Int_t n3);
  TComplex Four(Int_t n1, Int_t n2, Int_t n3, Int_t n4);
  TComplex Five(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5);
  TComplex Six(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5, Int_t n6);
  TComplex Recursion(Int_t n, Int_t *harmonic, Int_t mult = 1, Int_t skip = 0);

  // methods for computing nested loops
  TComplex TwoNestedLoops(Int_t n1, Int_t n2);
  TComplex ThreeNestedLoops(Int_t n1, Int_t n2, Int_t n3);
  TComplex FourNestedLoops(Int_t n1, Int_t n2, Int_t n3, Int_t n4);
  // TComplex FiveNestedLoops(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5);
  // TComplex SixNestedLoops(Int_t n1, Int_t n2, Int_t n3, Int_t n4, Int_t n5,
  // Int_t n6);
  Double_t CombinatorialWeight(Int_t n);

  // GetPointers Methods in case we need to manually trigger Terminate()
  virtual void GetPointers(TList *list);
  virtual void GetPointersForControlHistograms();
  virtual void GetPointersForFinalResultHistograms();
  virtual void GetPointersForFinalResultProfiles();

  // Setters and getters for list objects
  void SetControlHistogramsList(TList *const chl) {
    this->fControlHistogramsList = chl;
  };
  TList *GetControlHistogramsList() const {
    return this->fControlHistogramsList;
  }
  void SetFinalResultsList(TList *const frl) { this->fFinalResultsList = frl; };
  TList *GetFinalResultsList() const { return this->fFinalResultsList; }

  // setters for QA histograms
  void SetFillQAHistograms(Bool_t option) { fFillQAHistograms = option; }
  // generic setter for centrality correlation QA histogram binning
  void SetCenCorQAHistogramBinning(Int_t index, Int_t xnbins,
                                   Double_t xlowerEdge, Double_t xupperEdge,
                                   Int_t ynbins, Double_t ylowerEdge,
                                   Double_t yupperEdge) {
    if (index > LAST_ECENESTIMATORS * (LAST_ECENESTIMATORS - 1) / 2) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetCenCorQAHistogramBinning",
            "Running out of bounds in SetCenCorQAHistogramBinning");
    }
    this->fCenCorQAHistogramBins[index][kBIN] = xnbins;
    this->fCenCorQAHistogramBins[index][kLEDGE] = xlowerEdge;
    this->fCenCorQAHistogramBins[index][kUEDGE] = xupperEdge;
    this->fCenCorQAHistogramBins[index][kBIN + LAST_EBINS] = ynbins;
    this->fCenCorQAHistogramBins[index][kLEDGE + LAST_EBINS] = ylowerEdge;
    this->fCenCorQAHistogramBins[index][kUEDGE + LAST_EBINS] = yupperEdge;
  }
  // generic setter for self correlation QA histogram binning
  void SetSelfCorQAHistogramBinning(kTrack Track, Int_t nbins,
                                    Double_t lowerEdge, Double_t upperEdge) {
    if (Track > LAST_ETRACK) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetSelfCorQAHistogramBinning",
            "Running out of bounds in SetSelfCorQAHistogramBinning");
    }
    this->fSelfCorQAHistogramBins[Track][kBIN] = nbins;
    this->fSelfCorQAHistogramBins[Track][kLEDGE] = lowerEdge;
    this->fSelfCorQAHistogramBins[Track][kUEDGE] = upperEdge;
  }
  // generic setter for track control histogram binning
  void SetTrackControlHistogramBinning(kTrack Track, Int_t nbins,
                                       Double_t lowerEdge, Double_t upperEdge) {
    if (Track > LAST_ETRACK) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetTrackControlHistogramBinning",
            "Running out of bounds in SetTrackControlHistogramBinning");
    }
    this->fTrackControlHistogramBins[Track][kBIN] = nbins;
    this->fTrackControlHistogramBins[Track][kLEDGE] = lowerEdge;
    this->fTrackControlHistogramBins[Track][kUEDGE] = upperEdge;
  }
  // generic setter for event histogram binning
  void SetEventControlHistogramBinning(kEvent Event, Int_t nbins,
                                       Double_t lowerEdge, Double_t upperEdge) {
    if (Event > LAST_EEVENT) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetEventControlHistogramBinning",
            "Running out of bounds in SetEventControlHistogramBinning");
    }
    this->fEventControlHistogramBins[Event][kBIN] = nbins;
    this->fEventControlHistogramBins[Event][kLEDGE] = lowerEdge;
    this->fEventControlHistogramBins[Event][kUEDGE] = upperEdge;
  }

  // setters for cuts
  // centrality selection criterion
  // only use V0M, CL0/1, SPDTracklets
  void SetCentralitySelCriterion(TString SelCriterion) {
    this->fCentralitySelCriterion = SelCriterion;
  }
  // generic setter for track cuts
  void SetTrackCuts(kTrack Track, Double_t min, Double_t max) {
    if (Track > LAST_ETRACK) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetTrackCuts", "Running out of bounds in SetTrackCuts");
    }
    this->fTrackCuts[Track][kMIN] = min;
    this->fTrackCuts[Track][kMAX] = max;
  }
  // generic setter for event cuts
  void SetEventCuts(kEvent Event, Double_t min, Double_t max) {
    if (Event > LAST_EEVENT) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetEventCuts", "Running out of bounds in SetEventCuts");
    }
    this->fEventCuts[Event][kMIN] = min;
    this->fEventCuts[Event][kMAX] = max;
  }
  // generic setter primary vertex cut
  void SetPrimaryVertexCuts(kXYZ xyz, Double_t min, Double_t max) {
    if (xyz > LAST_EXYZ) {
      std::cout << __LINE__ << ": running out of bounds" << std::endl;
      Fatal("SetPrimaryVertexCuts",
            "Running out of bounds in SetPrimaryVertexCuts");
    }
    this->fPrimaryVertexCuts[xyz][kMIN] = min;
    this->fPrimaryVertexCuts[xyz][kMAX] = max;
  }
  // filterbit
  // depends strongly on the data set
  // typical choices are 1,128,256,768
  void SetFilterbit(Int_t Filterbit) { this->fFilterbit = Filterbit; }
  // cut all non-primary particles
  void SetPrimaryOnlyCut(Bool_t option) { this->fPrimaryOnly = option; }

  // setters for MC analsys
  void SetMCAnalysis(Bool_t option) { this->fMCAnalaysis = option; }
  void SetMCClosure(Bool_t option) { this->fMCClosure = option; }
  void SetUseWeights(Bool_t option) { this->fUseWeights = option; }
  void SetResetWeights(Bool_t option) { this->fResetWeights = option; }
  void SetUseCustomSeed(const UInt_t seed) {
    this->fSeed = seed;
    this->fUseCustomSeed = kTRUE;
  }
  void SetMCFlowHarmonics(TArrayD *array) {
    if (array->GetSize() > kMaxHarmonic) {
      std::cout << __LINE__ << ": Array exceeds maximum allowed harmonic"
                << std::endl;
      Fatal("SetFlowHarmonics", "Too many harmonics");
    }
    fMCFlowHarmonics = array;
  }
  void SetMCPdfRange(Double_t min, Double_t max) {
    fMCPdfRange[kMIN] = min;
    fMCPdfRange[kMAX] = max;
  }
  void SetMCNumberOfParticlesPerEvent(Int_t n) {
    fMCNumberOfParticlesPerEvent = n;
  }
  void SetMCNumberOfParticlesPerEventRange(Int_t min, Int_t max) {
    fMCNumberOfParticlesPerEventFluctuations = kTRUE;
    fMCNumberOfParticlesPerEventRange[kMIN] = min;
    fMCNumberOfParticlesPerEventRange[kMAX] = max;
  }
  void SetAcceptanceHistogram(TH1D *AcceptanceHistogram) {
    if (!AcceptanceHistogram) {
      std::cout << __LINE__ << ": Did not get acceptance histogram"
                << std::endl;
      Fatal("SetAccpetanceHistogram", "Invalid pointer");
    }
    this->fAcceptanceHistogram = AcceptanceHistogram;
  }
  void SetAcceptanceHistogram(const char *Filename, const char *Histname);
  void SetWeightHistogram(TH1D *WeightHistogram) {
    if (!WeightHistogram) {
      std::cout << __LINE__ << ": Did not get weight histogram" << std::endl;
      Fatal("SetWeightHistogram", "Invalid pointer");
    }
    this->fWeightHistogram = WeightHistogram;
  }
  void SetWeightHistogram(const char *Filename, const char *Histname);

  // set correlators we want to compute
  void SetCorrelators(std::vector<std::vector<Int_t>> correlators) {
    this->fCorrelators = correlators;
    for (int i = 0; i < LAST_EFINALPROFILE; ++i) {
      fFinalResultProfileBins[i][kBIN] = fCorrelators.size();
      fFinalResultProfileBins[i][kLEDGE] = 0;
      fFinalResultProfileBins[i][kUEDGE] = fCorrelators.size();
    }
  }

private:
  AliAnalysisTaskAR(const AliAnalysisTaskAR &aatmpf);
  AliAnalysisTaskAR &operator=(const AliAnalysisTaskAR &aatmpf);

  // base list holding all output object (a.k.a. grandmother of all lists)
  TList *fHistList;
  TString fHistListName;

  // QA histograms
  TList *fQAHistogramsList;
  TString fQAHistogramsListName;
  Bool_t fFillQAHistograms;

  // centrality correlation histograms
  TList *fCenCorQAHistogramsList;
  TString fCenCorQAHistogramsListName;
  TH2D *fCenCorQAHistograms[LAST_ECENESTIMATORS * (LAST_ECENESTIMATORS - 1) / 2]
                           [LAST_EBEFOREAFTER];
  TString fCenCorQAHistogramNames[LAST_ECENESTIMATORS *
                                  (LAST_ECENESTIMATORS - 1) /
                                  2][LAST_EBEFOREAFTER][LAST_ENAME];
  Double_t fCenCorQAHistogramBins[LAST_ECENESTIMATORS *
                                  (LAST_ECENESTIMATORS - 1) /
                                  2][2 * LAST_EBINS];
  // filterbit scans histograms
  TList *fFBScanQAHistogramsList;
  TString fFBScanQAHistogramsListName;
  TH1D *fFBScanQAHistogram;
  TString fFBScanQAHistogramName[LAST_ENAME];
  Double_t fFBScanQAHistogramBin[LAST_EBINS];
  TH1D *fFBTrackScanQAHistograms[LAST_ETRACK][kNumberofTestFilterBit];
  TString fFBTrackScanQAHistogramNames[LAST_ETRACK][kNumberofTestFilterBit]
                                      [LAST_ENAME];
  Double_t fFBTrackScanQAHistogramBins[LAST_ETRACK][LAST_EBINS];
  // self correlations
  TList *fSelfCorQAHistogramsList;
  TString fSelfCorQAHistogramsListName;
  TH1D *fSelfCorQAHistograms[kKinematic][LAST_EBEFOREAFTER];
  TString fSelfCorQAHistogramNames[kKinematic][LAST_EBEFOREAFTER][LAST_ENAME];
  Double_t fSelfCorQAHistogramBins[kKinematic][LAST_EBINS];

  // control histograms
  TList *fControlHistogramsList;
  TString fControlHistogramsListName;

  // track control histograms
  TList *fTrackControlHistogramsList;
  TString fTrackControlHistogramsListName;
  TH1D *fTrackControlHistograms[LAST_ETRACK][LAST_EBEFOREAFTER];
  TString fTrackControlHistogramNames[LAST_ETRACK][LAST_EBEFOREAFTER]
                                     [LAST_ENAME];
  Double_t fTrackControlHistogramBins[LAST_ETRACK][LAST_EBINS];

  // event control historams
  TList *fEventControlHistogramsList;
  TString fEventControlHistogramsListName;
  TH1D *fEventControlHistograms[LAST_EEVENT][LAST_EBEFOREAFTER];
  TString fEventControlHistogramNames[LAST_EEVENT][LAST_EBEFOREAFTER]
                                     [LAST_ENAME];
  Double_t fEventControlHistogramBins[LAST_EEVENT][LAST_EBINS];

  // cuts
  TString fCentralitySelCriterion;
  Double_t fTrackCuts[LAST_ETRACK][LAST_EMINMAX];
  Double_t fEventCuts[LAST_EEVENT][LAST_EMINMAX];
  Double_t fPrimaryVertexCuts[LAST_EXYZ][LAST_EMINMAX];
  Int_t fFilterbit;
  Bool_t fPrimaryOnly;

  // Final results
  TList *fFinalResultsList;
  TString fFinalResultsListName;
  // array holding final result histograms
  TH1D *fFinalResultHistograms[LAST_EFINALHIST];
  TString fFinalResultHistogramNames[LAST_EFINALHIST][LAST_ENAME];
  Double_t fFinalResultHistogramBins[LAST_EFINALHIST][LAST_EBINS];
  // arayy holding final resutl profiles
  TProfile *fFinalResultProfiles[LAST_EFINALPROFILE];
  TString fFinalResultProfileNames[LAST_EFINALPROFILE][LAST_ENAME];
  Double_t fFinalResultProfileBins[LAST_EFINALPROFILE][LAST_EBINS];

  // Monte Carlo analysis
  TList *fMCAnalysisList;
  TString fMCAnalysisListName;
  Bool_t fMCAnalaysis;
  Bool_t fMCClosure;
  UInt_t fSeed;
  Bool_t fUseCustomSeed;
  TF1 *fMCPdf;
  TString fMCPdfName;
  Double_t fMCPdfRange[LAST_EMINMAX];
  TArrayD *fMCFlowHarmonics;
  Bool_t fMCNumberOfParticlesPerEventFluctuations;
  Int_t fMCNumberOfParticlesPerEvent;
  Int_t fMCNumberOfParticlesPerEventRange[LAST_EMINMAX];

  // qvectors
  TList *fQvectorList;
  TComplex fQvector[kMaxHarmonic][kMaxPower];
  std::vector<Double_t> fPhi;
  std::vector<Double_t> fWeights;
  TH1D *fAcceptanceHistogram;
  TH1D *fWeightHistogram;
  Bool_t fUseWeights;
  Bool_t fResetWeights;
  std::vector<std::vector<Int_t>> fCorrelators;

  // Increase this counter in each new version:
  ClassDef(AliAnalysisTaskAR, 6);
};

#endif
