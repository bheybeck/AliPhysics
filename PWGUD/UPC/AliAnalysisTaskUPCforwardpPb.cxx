/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// c++ headers
#include <iostream>
#include <fstream>
// #include <vector>
// #include <algorithm>


// root headers
#include <TMath.h>
#include "TH1I.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH1.h"
#include <TFile.h>
#include <TF2.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TTree.h>
#include <TGraph2D.h>
#include <TStopwatch.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TLatex.h>
#include "TClonesArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TParticle.h"
#include "TObjString.h"
#include "TList.h"
#include "TChain.h"


// aliroot headers
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliAODEvent.h"
#include "AliAODInputHandler.h"
#include "AliMuonTrackCuts.h"
#include "AliAODVertex.h"         // My addition, to use Eugeny Krishen's format


// my headers
#include "AliAnalysisTaskUPCforwardpPb.h"



class AliAnalysisTaskUPCforwardpPb;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskUPCforwardpPb) // classimp: necessary for root

//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::AliAnalysisTaskUPCforwardpPb()
    : AliAnalysisTaskSE(),
      fAOD(0),
      fOutputList(0),
      fNumberMuonsH(0),
      fCounterH(0),
      fEtaMuonH(0),
      fEtaDimuonH(0),
      fRAbsMuonH(0),
      fInvariantMassDistributionH(0),
      fInvariantMassDistributionRapidityBinsH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBinsH{ 0, 0, 0 },
      fInvariantMassDistribution0N0NH(0),
      fInvariantMassDistributionRapidityBins0N0NH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBins0N0NH{ 0, 0, 0 },
      fInvariantMassDistributionSmall0N0NH(0),
      fInvariantMassDistributionRapidityBinsSmall0N0NH{ 0, 0 },
      fEntriesAgainstRunNumberH(0),
      fEntriesAgainstRunNumberProperlyH(0),
      fRunNumberTriggerCMUP11ClassH(0),
      fRunNumberTriggerCMUP11ClassProperlyH(0),
      fRunNumberTriggerCMUP26ClassH(0),
      fRunNumberTriggerCMUP26ClassProperlyH(0),
      fRunNumberTriggerCMUP6ClassH(0),
      fRunNumberTriggerCMUP6ClassProperlyH(0),
      fRunNumberTriggerCMUP10ClassH(0),
      fRunNumberTriggerCMUP10ClassProperlyH(0),
      fRunNumberTriggerCMUP13ClassH(0),
      fRunNumberTriggerCMUP13ClassProperlyH(0),
      fTriggersVsRunH(0),
      fInvariantMassDistributionCoherentH(0),
      fInvariantMassDistributionCoherentRapidityBinsH{ 0, 0, 0, 0, 0, 0 },
      fInvariantMassDistributionCoherentShiftMinusTwoH(0),
      fInvariantMassDistributionCoherentShiftMinusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusTwoH(0),
      fInvariantMassDistributionIncoherentH(0),
      fInvariantMassDistributionIncoherentShiftMinusTwoH(0),
      fInvariantMassDistributionIncoherentShiftMinusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusTwoH(0),
      fDimuonPtDistributionH(0),
      fDimuonPtDistributionRestrictedRapidity0N0NH(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31H(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26H(0),
      fInvariantMassDistributionExtendedH(0),
      fInvariantMassDistributionCoherentExtendedH(0),
      fInvariantMassDistributionIncoherentExtendedH(0),
      fZNCEnergyAgainstEntriesH(0),
      fZNAEnergyAgainstEntriesH(0),
      fZNCEnergyBeforeTimingSelectionH(0),
      fZNAEnergyBeforeTimingSelectionH(0),
      fZNCEnergyAgainstEntriesExtendedH(0),
      fZNAEnergyAgainstEntriesExtendedH(0),
      fZNCEnergyAgainstEntriesExtendedHv2(0),
      fZNAEnergyAgainstEntriesExtendedHv2(0),
      fZNCEnergyBeforeTimingSelectionExtendedH(0),
      fZNAEnergyBeforeTimingSelectionExtendedH(0),
      fMuonTrackCuts(0x0),
      fRunNum(0),
      fTracklets(0),
      fL0inputs(0),
      fL1inputs(0),
      fZem1Energy(0),
      fZem2Energy(0),
      fZNCEnergy(0),
      fZNAEnergy(0),
      fZPCEnergy(0),
      fZPAEnergy(0),
      fZNATime(0),
      fZNCTime(0),
      fV0ADecision(-10),
      fV0CDecision(-10),
      fADADecision(-10),
      fADCDecision(-10),
      fIR1Map(0),
      fIR2Map(0),
      fZNATDC{0, 0, 0, 0},
      fZNCTDC{0, 0, 0, 0},
      fZPATDC{0, 0, 0, 0},
      fZPCTDC{0, 0, 0, 0},
      fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      fV0TotalNCells(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}

//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::AliAnalysisTaskUPCforwardpPb(const char* name)
    : AliAnalysisTaskSE(name),
      fAOD(0),
      fOutputList(0),
      fNumberMuonsH(0),
      fCounterH(0),
      fEtaMuonH(0),
      fEtaDimuonH(0),
      fRAbsMuonH(0),
      fInvariantMassDistributionH(0),
      fInvariantMassDistributionRapidityBinsH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBinsH{ 0, 0, 0 },
      fInvariantMassDistribution0N0NH(0),
      fInvariantMassDistributionRapidityBins0N0NH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBins0N0NH{ 0, 0, 0 },
      fInvariantMassDistributionSmall0N0NH(0),
      fInvariantMassDistributionRapidityBinsSmall0N0NH{ 0, 0 },
      fEntriesAgainstRunNumberH(0),
      fEntriesAgainstRunNumberProperlyH(0),
      fRunNumberTriggerCMUP11ClassH(0),
      fRunNumberTriggerCMUP11ClassProperlyH(0),
      fRunNumberTriggerCMUP26ClassH(0),
      fRunNumberTriggerCMUP26ClassProperlyH(0),
      fRunNumberTriggerCMUP6ClassH(0),
      fRunNumberTriggerCMUP6ClassProperlyH(0),
      fRunNumberTriggerCMUP10ClassH(0),
      fRunNumberTriggerCMUP10ClassProperlyH(0),
      fRunNumberTriggerCMUP13ClassH(0),
      fRunNumberTriggerCMUP13ClassProperlyH(0),
      fTriggersVsRunH(0),
      fInvariantMassDistributionCoherentH(0),
      fInvariantMassDistributionCoherentRapidityBinsH{ 0, 0, 0, 0, 0, 0 },
      fInvariantMassDistributionCoherentShiftMinusTwoH(0),
      fInvariantMassDistributionCoherentShiftMinusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusTwoH(0),
      fInvariantMassDistributionIncoherentH(0),
      fInvariantMassDistributionIncoherentShiftMinusTwoH(0),
      fInvariantMassDistributionIncoherentShiftMinusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusTwoH(0),
      fDimuonPtDistributionH(0),
      fDimuonPtDistributionRestrictedRapidity0N0NH(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31H(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26H(0),
      fInvariantMassDistributionExtendedH(0),
      fInvariantMassDistributionCoherentExtendedH(0),
      fInvariantMassDistributionIncoherentExtendedH(0),
      fZNCEnergyAgainstEntriesH(0),
      fZNAEnergyAgainstEntriesH(0),
      fZNCEnergyBeforeTimingSelectionH(0),
      fZNAEnergyBeforeTimingSelectionH(0),
      fZNCEnergyAgainstEntriesExtendedH(0),
      fZNAEnergyAgainstEntriesExtendedH(0),
      fZNCEnergyAgainstEntriesExtendedHv2(0),
      fZNAEnergyAgainstEntriesExtendedHv2(0),
      fZNCEnergyBeforeTimingSelectionExtendedH(0),
      fZNAEnergyBeforeTimingSelectionExtendedH(0),
      fMuonTrackCuts(0x0),
      fRunNum(0),
      fTracklets(0),
      fL0inputs(0),
      fL1inputs(0),
      fZem1Energy(0),
      fZem2Energy(0),
      fZNCEnergy(0),
      fZNAEnergy(0),
      fZPCEnergy(0),
      fZPAEnergy(0),
      fZNATime(0),
      fZNCTime(0),
      fV0ADecision(-10),
      fV0CDecision(-10),
      fADADecision(-10),
      fADCDecision(-10),
      fIR1Map(0),
      fIR2Map(0),
      fZNATDC{0, 0, 0, 0},
      fZNCTDC{0, 0, 0, 0},
      fZPATDC{0, 0, 0, 0},
      fZPCTDC{0, 0, 0, 0},
      fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      fV0TotalNCells(0)
{

    // constructor
    DefineInput(0, TChain::Class());    // define the input of the analysis: in this case we take a 'chain' of events
                                        // this chain is created by the analysis manager, so no need to worry about it,
                                        // it does its work automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms
                                        // you can add more output objects by calling DefineOutput(2, classname::Class())
                                        // if you add more output objects, make sure to call PostData for all of them, and to
                                        // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::~AliAnalysisTaskUPCforwardpPb()
{
    // destructor
    if(fOutputList)    {delete fOutputList;}     	// at the end of your task, it is deleted
    if(fMuonTrackCuts) {delete fMuonTrackCuts;}   // from memory by calling this function
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::UserCreateOutputObjects()
{
  // create output objects
  //
  // this function is called ONCE at the start of your analysis (RUNTIME)
  // here you ceate the histograms that you want to use
  //
  // the histograms are in this case added to a tlist, this list is in the end saved
  // to an output file
  //

  //muon track cuts
  fMuonTrackCuts = new AliMuonTrackCuts("StdMuonCuts", "StdMuonCuts");
  fMuonTrackCuts->SetFilterMask(    AliMuonTrackCuts::kMuEta     |
                                    AliMuonTrackCuts::kMuThetaAbs|
                                    AliMuonTrackCuts::kMuPdca    |
                                    AliMuonTrackCuts::kMuMatchLpt   );
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->Print("mask");



  fOutputList = new TList();          // this is a list which will contain all
                                      // of your histograms at the end of the
                                      // analysis, the contents of this list
                                      // are written to the output file

  fOutputList->SetOwner(kTRUE);       // memory management: the list is owner
                                      // of all objects it contains and will
                                      // delete them if requested

  //_______________________________
  // - Adding histograms
  fNumberMuonsH = new TH1F("fNumberMuonsH", "fNumberMuonsH", 12, -0.5, 11.5);
  fOutputList->Add(fNumberMuonsH);    // don't forget to add it to the list!

  fCounterH = new TH1F("fCounterH", "fCounterH", 24, -0.5, 23.5);
  fOutputList->Add(fCounterH);

  fEtaMuonH = new TH1F("fEtaMuonH", "fEtaMuonH", 160, -1, -5);
  fOutputList->Add(fEtaMuonH);

  fEtaDimuonH = new TH1F("fEtaDimuonH", "fEtaDimuonH", 160, -1, -5);
  fOutputList->Add(fEtaDimuonH);

  fRAbsMuonH = new TH1F("fRAbsMuonH", "fRAbsMuonH", 100, 0, 100);
  fOutputList->Add(fRAbsMuonH);

  fInvariantMassDistributionH = new TH1F("fInvariantMassDistributionH", "fInvariantMassDistributionH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionMoreRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionMoreRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionMoreRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionMoreRapidityBinsH[iRapidity]);
  }

  fInvariantMassDistribution0N0NH = new TH1F("fInvariantMassDistribution0N0NH", "fInvariantMassDistribution0N0NH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistribution0N0NH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBins0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBins0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBins0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBins0N0NH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionMoreRapidityBins0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionMoreRapidityBins0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionMoreRapidityBins0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionMoreRapidityBins0N0NH[iRapidity]);
  }

  fInvariantMassDistributionSmall0N0NH = new TH1F("fInvariantMassDistributionSmall0N0NH", "fInvariantMassDistributionSmall0N0NH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionSmall0N0NH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsSmall0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsSmall0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsSmall0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsSmall0N0NH[iRapidity]);
  }


  fEntriesAgainstRunNumberH = new TH1F("fEntriesAgainstRunNumberH", "fEntriesAgainstRunNumberH", 10000, 290000, 300000);
  fOutputList->Add(fEntriesAgainstRunNumberH);

  /* - Trying to reproduce the histogram for the RunNumbers as they always
     - show it, properly labelled. Inspiration has come from the website:
     - https://root.cern.ch/doc/master/hlabels1_8C.html
     - Let us see if it works properly.
     -
   */
  fEntriesAgainstRunNumberProperlyH = new TH1F("fEntriesAgainstRunNumberProperlyH", "fEntriesAgainstRunNumberProperlyH", 10000, 290000, 300000);
  fEntriesAgainstRunNumberProperlyH->SetStats(0);
  fEntriesAgainstRunNumberProperlyH->SetFillColor(38);
  // fEntriesAgainstRunNumberProperlyH->SetCanExtend(TH1::kAllAxes);
  fEntriesAgainstRunNumberProperlyH->LabelsDeflate();
  fOutputList->Add(fEntriesAgainstRunNumberProperlyH);

  fRunNumberTriggerCMUP11ClassH = new TH1F("fRunNumberTriggerCMUP11ClassH", "fRunNumberTriggerCMUP11ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP11ClassH);

  fRunNumberTriggerCMUP11ClassProperlyH = new TH1F("fRunNumberTriggerCMUP11ClassProperlyH", "fRunNumberTriggerCMUP11ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP11ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP11ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP11ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP11ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP11ClassProperlyH);

  fRunNumberTriggerCMUP26ClassH = new TH1F("fRunNumberTriggerCMUP26ClassH", "fRunNumberTriggerCMUP26ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP26ClassH);

  fRunNumberTriggerCMUP26ClassProperlyH = new TH1F("fRunNumberTriggerCMUP26ClassProperlyH", "fRunNumberTriggerCMUP26ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP26ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP26ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP26ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP26ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP26ClassProperlyH);

  fRunNumberTriggerCMUP6ClassH = new TH1F("fRunNumberTriggerCMUP6ClassH", "fRunNumberTriggerCMUP6ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP6ClassH);

  fRunNumberTriggerCMUP6ClassProperlyH = new TH1F("fRunNumberTriggerCMUP6ClassProperlyH", "fRunNumberTriggerCMUP6ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP6ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP6ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP6ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP6ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP6ClassProperlyH);

  fRunNumberTriggerCMUP10ClassH = new TH1F("fRunNumberTriggerCMUP10ClassH", "fRunNumberTriggerCMUP10ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP10ClassH);

  fRunNumberTriggerCMUP10ClassProperlyH = new TH1F("fRunNumberTriggerCMUP10ClassProperlyH", "fRunNumberTriggerCMUP10ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP10ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP10ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP10ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP10ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP10ClassProperlyH);

  fRunNumberTriggerCMUP13ClassH = new TH1F("fRunNumberTriggerCMUP13ClassH", "fRunNumberTriggerCMUP13ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP13ClassH);

  fRunNumberTriggerCMUP13ClassProperlyH = new TH1F("fRunNumberTriggerCMUP13ClassProperlyH", "fRunNumberTriggerCMUP13ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP13ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP13ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP13ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP13ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP13ClassProperlyH);

  fTriggersVsRunH = new TH2F("fTriggersVsRunH","",5,0,5,60000,240000,300000);
  fOutputList->Add(fTriggersVsRunH);

  fInvariantMassDistributionCoherentH = new TH1F("fInvariantMassDistributionCoherentH", "fInvariantMassDistributionCoherentH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentH);

  for( Int_t iRapidity = 0; iRapidity < 6; iRapidity++ ) {
    fInvariantMassDistributionCoherentRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionCoherentRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionCoherentRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionCoherentRapidityBinsH[iRapidity]);
  }


  fInvariantMassDistributionCoherentShiftMinusTwoH = new TH1F("fInvariantMassDistributionCoherentShiftMinusTwoH", "fInvariantMassDistributionCoherentShiftMinusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftMinusTwoH);

  fInvariantMassDistributionCoherentShiftMinusOneH = new TH1F("fInvariantMassDistributionCoherentShiftMinusOneH", "fInvariantMassDistributionCoherentShiftMinusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftMinusOneH);

  fInvariantMassDistributionCoherentShiftPlusOneH = new TH1F("fInvariantMassDistributionCoherentShiftPlusOneH", "fInvariantMassDistributionCoherentShiftPlusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftPlusOneH);

  fInvariantMassDistributionCoherentShiftPlusTwoH = new TH1F("fInvariantMassDistributionCoherentShiftPlusTwoH", "fInvariantMassDistributionCoherentShiftPlusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftPlusTwoH);

  fInvariantMassDistributionIncoherentH = new TH1F("fInvariantMassDistributionIncoherentH", "fInvariantMassDistributionIncoherentH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentH);

  fInvariantMassDistributionIncoherentShiftMinusTwoH = new TH1F("fInvariantMassDistributionIncoherentShiftMinusTwoH", "fInvariantMassDistributionIncoherentShiftMinusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftMinusTwoH);

  fInvariantMassDistributionIncoherentShiftMinusOneH = new TH1F("fInvariantMassDistributionIncoherentShiftMinusOneH", "fInvariantMassDistributionIncoherentShiftMinusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftMinusOneH);

  fInvariantMassDistributionIncoherentShiftPlusOneH = new TH1F("fInvariantMassDistributionIncoherentShiftPlusOneH", "fInvariantMassDistributionIncoherentShiftPlusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftPlusOneH);

  fInvariantMassDistributionIncoherentShiftPlusTwoH = new TH1F("fInvariantMassDistributionIncoherentShiftPlusTwoH", "fInvariantMassDistributionIncoherentShiftPlusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftPlusTwoH);

  fDimuonPtDistributionH = new TH1F("fDimuonPtDistributionH", "fDimuonPtDistributionH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionH);

  fDimuonPtDistributionShiftPlusOneH = new TH1F("fDimuonPtDistributionShiftPlusOneH", "fDimuonPtDistributionShiftPlusOneH", 4000, 0.02, 20.02);
  fOutputList->Add(fDimuonPtDistributionShiftPlusOneH);

  fDimuonPtDistributionRestrictedRapidity0N0NH = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0NH", "fDimuonPtDistributionRestrictedRapidity0N0NH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0NH);

  fDimuonPtDistributionRestrictedRapidity0N0N36to31H = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N36to31H", "fDimuonPtDistributionRestrictedRapidity0N0N36to31H", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N36to31H);

  fDimuonPtDistributionRestrictedRapidity0N0N31to26H = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N31to26H", "fDimuonPtDistributionRestrictedRapidity0N0N31to26H", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N31to26H);

  /* - These histograms have an EXTENDED range (0,20)->(0,40)
     -
   */
  fInvariantMassDistributionExtendedH = new TH1F("fInvariantMassDistributionExtendedH", "fInvariantMassDistributionExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionExtendedH);

  fInvariantMassDistributionCoherentExtendedH = new TH1F("fInvariantMassDistributionCoherentExtendedH", "fInvariantMassDistributionCoherentExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionCoherentExtendedH);

  fInvariantMassDistributionIncoherentExtendedH = new TH1F("fInvariantMassDistributionIncoherentExtendedH", "fInvariantMassDistributionIncoherentExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionIncoherentExtendedH);

  fZNCEnergyAgainstEntriesH = new TH1F("fZNCEnergyAgainstEntriesH", "fZNCEnergyAgainstEntriesH", 20000, -10000, 40000);
  fOutputList->Add(fZNCEnergyAgainstEntriesH);

  fZNAEnergyAgainstEntriesH = new TH1F("fZNAEnergyAgainstEntriesH", "fZNAEnergyAgainstEntriesH", 20000, -10000, 40000);
  fOutputList->Add(fZNAEnergyAgainstEntriesH);

  fZNCEnergyBeforeTimingSelectionH = new TH1F("fZNCEnergyBeforeTimingSelectionH", "fZNCEnergyBeforeTimingSelectionH", 20000, -10000, 40000);
  fOutputList->Add(fZNCEnergyBeforeTimingSelectionH);

  fZNAEnergyBeforeTimingSelectionH = new TH1F("fZNAEnergyBeforeTimingSelectionH", "fZNAEnergyBeforeTimingSelectionH", 20000, -10000, 40000);
  fOutputList->Add(fZNAEnergyBeforeTimingSelectionH);

  fZNCEnergyAgainstEntriesExtendedH = new TH1F("fZNCEnergyAgainstEntriesExtendedH", "fZNCEnergyAgainstEntriesExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyAgainstEntriesExtendedH);

  fZNAEnergyAgainstEntriesExtendedH = new TH1F("fZNAEnergyAgainstEntriesExtendedH", "fZNAEnergyAgainstEntriesExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyAgainstEntriesExtendedH);

  fZNCEnergyAgainstEntriesExtendedHv2 = new TH1F("fZNCEnergyAgainstEntriesExtendedHv2", "fZNCEnergyAgainstEntriesExtendedHv2", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyAgainstEntriesExtendedHv2);

  fZNAEnergyAgainstEntriesExtendedHv2 = new TH1F("fZNAEnergyAgainstEntriesExtendedHv2", "fZNAEnergyAgainstEntriesExtendedHv2", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyAgainstEntriesExtendedHv2);

  fZNCEnergyBeforeTimingSelectionExtendedH = new TH1F("fZNCEnergyBeforeTimingSelectionExtendedH", "fZNCEnergyBeforeTimingSelectionExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyBeforeTimingSelectionExtendedH);

  fZNAEnergyBeforeTimingSelectionExtendedH = new TH1F("fZNAEnergyBeforeTimingSelectionExtendedH", "fZNAEnergyBeforeTimingSelectionExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyBeforeTimingSelectionExtendedH);




  //_______________________________
  // - End of the function
  PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the
  // fOutputList object. the manager will in the end take care of writing your output to file
  // so it needs to know what's in the output
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::NotifyRun()
{
  /// Set run number for cuts
  fMuonTrackCuts->SetRun(fInputHandler);
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::UserExec(Option_t *)
{
  /* - This iSelectionCounter is used as a token. So at every passing step it is
     - increased by one. All the events are supposed to pass the first step
     - obviously, but only a few get to the end. This is effect is clearly
     - noticeable in fCounterH event with the small trial local sample.
     - Almost 160k possible events at the 0-th step, while only 2k at the 4th step.
   */
  Int_t iSelectionCounter = 0; // no selection applied yet
  fCounterH->Fill(iSelectionCounter); // entering UserExec
  iSelectionCounter++;

  // get AOD event
  fAOD = dynamic_cast<AliAODEvent*>(InputEvent());
  if(!fAOD) {
      PostData(1, fOutputList);
      return;
  }
  fCounterH->Fill(iSelectionCounter); // AOD event found
  iSelectionCounter++;

  /* - Is it the right trigger?
   * -
   * - LHC16r (p-Pb @ 8 TeV):
   * - CMUP14-B-NOPF-MUFAST:   !VBA & !UBA & MSL
   * - CMUP15-B-NOPF-ALLNOTRD: !VBA & !UBA & !VC5 & !SH2 & SMB & MSL
   * -
   * -
   * -
   * - LHC16s (Pb-p @ 8 TeV):
   * - CMUP23-B-NOPF-MUFAST:   !VBA & !VGA & !UBC & !UGC & !SH2 & !VC5 & MUL
   * - CMUP22-B-NOPF-ALLNOTRD: !VBA & !VGA & !UBC & !UGC & !VC5 & !SH2 & SMB & MSL
   * -
   */
  TString trigger = fAOD->GetFiredTriggerClasses();
  if (    !(trigger.Contains("CMUP14-B-NOPF-MUFAST")   ||
	          trigger.Contains("CMUP15-B-NOPF-ALLNOTRD") ||
	          trigger.Contains("CMUP23-B-NOPF-MUFAST")   ||
            trigger.Contains("CMUP22-B-NOPF-ALLNOTRD") /*||
            trigger.Contains("CMUP11-B-NOPF-MUFAST")*/
            )
          )  {
                    PostData(1, fOutputList);
                    return;
  }
  fCounterH->Fill(iSelectionCounter); // right trigger found
  iSelectionCounter++;


  /* - The following lines concern the LUMI computation.
   * - What is being done is that we fill the histograms
   * - with the number of events which pass the relative
   * - trigger conditions.
   * -
   */
  // Int_t  counterForTrigger = 0;
  fRunNum    = fAOD->GetRunNumber();
  if ( trigger.Contains("CMUP14-B-NOPF-MUFAST") )  {
    fTriggersVsRunH->Fill( 0.5, fRunNum );
  }
  if ( trigger.Contains("CMUP23-B-NOPF-MUFAST") )  {
    fTriggersVsRunH->Fill( 1.5, fRunNum );
  }
  if ( trigger.Contains("CMUP15-B-NOPF-ALLNOTRD") )  {
    fTriggersVsRunH->Fill( 2.5, fRunNum );
  }
  if ( trigger.Contains("CMUP22-B-NOPF-ALLNOTRD") )  {
    fTriggersVsRunH->Fill( 3.5, fRunNum );
  }


  /* - We are now checking if there were any tracks. If there were at least one,
     - then the histogram gets filled again. If not we are returning. There
     - would be no point in going further.
   */
  Int_t nTracks(fAOD->GetNumberOfTracks());
  if(nTracks<1) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter); // At least one track
  iSelectionCounter++;


  //_______________________________
  // EVENT DATA EXTRACTION
  /* - Eugeny Krishen's event data extraction. I am trying to implement it.
     - The only thing I am a bit worried about is whether it should go before or
     - after the "nTracks<1" check... I will try and switch it if it sounds
     - better. These data are used for the event selection and maybe later on
     - for track selection, but I did not get to that part yet. If after all of
     - this I remember to do so, I will come back to this point and correct this
     - statement. If you find this part, please, keep in mind to check the
     - following.
   */

  /* - Event information:
     - Run Number, maybe to select the GOOD Runs and discard the others;
     - Number of Tracklets, these are in this case the SPD tracklets, so the
     - almost unit vector roughly 2 cm between two pixels of the SPD in different
     - layers.
   */
  // fRunNum    = fAOD->GetRunNumber();
  fTracklets = fAOD->GetTracklets()->GetNumberOfTracklets();

  /* - Trigger Inputs:
     - L0: ..... ;
     - L1: ..... .
   */
  fL0inputs = fAOD->GetHeader()->GetL0TriggerInputs();
  fL1inputs = fAOD->GetHeader()->GetL1TriggerInputs();

  /* - Past-future protection maps:
     - IR1: .... ;
     - IR2: .... .
   */
  fIR1Map = fAOD->GetHeader()->GetIRInt1InteractionMap();
  fIR2Map = fAOD->GetHeader()->GetIRInt2InteractionMap();

  /* - ZDC: we try to find the ZDC object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without ZDC's information. Or at least, this
     - is my impression of it (filling fCounterH). ZDC information:
     - fZem1Energy:
     - fZem2Energy:
     - fZNAEnergy:
     - fZNCEnergy:
     - fZPAEnergy:
     - fZPCEnergy:
     - fZNATime:
     - fZNCTime:
     - fZNATDC[i]:
     - fZNCTDC[i]:
     - fZPATDC[i]:
     - fZPCTDC[i]:
   */
  AliAODZDC *dataZDC = dynamic_cast<AliAODZDC*>(fAOD->GetZDCData());
  if(!dataZDC) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter);
  iSelectionCounter++;

  fZem1Energy = dataZDC->GetZEM1Energy();
  fZem2Energy = dataZDC->GetZEM2Energy();

  /* - Reset Event information.
   * -
   */
  fZNAEnergy  = -8999;
  fZNCEnergy  = -8999;
  fZPAEnergy  = -8999;
  fZPCEnergy  = -8999;

  fZNAEnergy  = dataZDC->GetZNATowerEnergy()[0];
  fZNCEnergy  = dataZDC->GetZNCTowerEnergy()[0];
  fZPAEnergy  = dataZDC->GetZPATowerEnergy()[0];
  fZPCEnergy  = dataZDC->GetZPCTowerEnergy()[0];

  fZNATime    = dataZDC->GetZNATime();
  fZNCTime    = dataZDC->GetZNCTime();

  /* - Reset Event information.
   * -
   */
  for (Int_t i=0;i<4;i++) fZNATDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZPATDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZPCTDC[i] = -999;

  for (Int_t i=0;i<4;i++) fZNATDC[i] = dataZDC->GetZNATDCm(i);
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = dataZDC->GetZNCTDCm(i);
  for (Int_t i=0;i<4;i++) fZPATDC[i] = dataZDC->GetZPATDCm(i);
  for (Int_t i=0;i<4;i++) fZPCTDC[i] = dataZDC->GetZPCTDCm(i);

  /* - These lines are the calibration for the ZDC as provided by Evgeny Kryshen.
     -
   */
  Bool_t calibrated = 0;
  // if ( fRunNum <= 245068 ) {
  //   calibrated = 1;
  // } else if ( ( fRunNum > 245068 ) && ( fRunNum <  246995 ) ){
  //   calibrated = 0;
  // } else {
  //   calibrated = 1;
  // }

  // if ( calibrated == 0 ) {
  //   if( fRunNum <= 246994 ) {
  //     fZNAEnergy *= (2500./250.);
  //     fZNCEnergy *= (2500./250.);
  //   }
  // }

  /* - V0: we try to find the V0 object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without V0's information. Or at least, this
     - is my impression of it (filling fCounterH). V0 information:
     - fV0ADecision: ..... ;
     - fV0CDecision: ..... .
     -
     -
     -
     - Plot the V0 variables to try to understand whether it is cells we are
     - talking about or boolean responses or something else altogether.
  */
  AliVVZERO *dataVZERO = dynamic_cast<AliVVZERO*>(fAOD->GetVZEROData());
  if(!dataVZERO) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter);
  iSelectionCounter++;
  fCounterH->Fill(12);


  fV0ADecision = dataVZERO->GetV0ADecision();
  fCounterH->Fill(13);
  fV0CDecision = dataVZERO->GetV0CDecision();
  fCounterH->Fill(14);


  //_____________________________________
  // RUN SELECTION
  /* - NOTE: total run selection.
   * -
   */
  fCounterH->Fill(15);
  Int_t listOfGoodRunNumbersLHC16r[]  = { 266318, 266316, 266312, 266305, 266304, 266300, 266299, 266296, 266235, 266234,
                                          266208, 266197, 266196, 266193, 266190, 266189, 266187, 266117, 266086, 266085,
                                          266084, 266081, 266076, 266074, 266034, 266025, 266023, 266022, 265841, 265840,
                                          265797, 265795, 265792, 265789, 265788, 265787, 265785, 265756, 265754, 265746,
                                          265744, 265742, 265741, 265740, 265714, 265713, 265709, 265701, 265700, 265698,
                                          265697, 265696, 265694, 265691, 265607, 265596, 265594 };
  Int_t listOfGoodRunNumbersLHC16s[]  = { 267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
                                          267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
                                          266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
                                          266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
                                          266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
                                          /*266615,*/ 266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
                                          266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518, 266516,
                                          266514, 266487, 266480, 266479, 266472, 266441, 266439/*, 296552, 296510, 296549, 296618, 296551, 296553, 296623, 296511, 296552*/ };
  Bool_t checkIfGoodRun = kFALSE;
  // for( Int_t iRunLHC16r = 0; iRunLHC16r <  57; iRunLHC16r++){
  //   if( fRunNum == listOfGoodRunNumbersLHC16r[iRunLHC16r] ) checkIfGoodRun = kTRUE;
  // }
  for( Int_t iRunLHC16s = 0; iRunLHC16s <  76 /*86*/; iRunLHC16s++){
    if( fRunNum == listOfGoodRunNumbersLHC16s[iRunLHC16s] ) checkIfGoodRun = kTRUE;
  }
  if(checkIfGoodRun != 1) {
       PostData(1, fOutputList);
       // cout << "OPS!" << endl;
       return;
  }
  fCounterH->Fill(17);



  // END RUN SELECTION
  //_____________________________________



  /* - We have to get the number of fired V0C cells. So firstly, we get the
     - boolean information about the hit cells for all V0. This is done through
     - the GetBBFlag(i) method, where 0<i<32 stands for the V0C cells and
     - 32<i<64 for the V0A cells. Then I thought the easiest way to check
     - whether the number of fired V0C cells is above 2 is just to add up the
     - boolean numbers for 0<i<32. Let's see.
     -
     - Weird fact: this doesn't seem to work... I have changed it so that if
     - the single cell has recorded a signal (kTRUE) then it adds up to the
     - total number of cells. Hope for the best.
     -
     - I am an idiot!!!!!! I have to reset the variable everytime!!!!
   */
  fV0TotalNCells = 0;
  for(Int_t iV0Hits = 0; iV0Hits < 64; iV0Hits++) {
        fV0Hits[iV0Hits] = dataVZERO->GetBBFlag(iV0Hits);
        if(fV0Hits[iV0Hits] == kTRUE) {
              // if(iV0Hits < 32) fV0TotalNCells += fV0Hits[iV0Hits];
              if(iV0Hits < 32) fV0TotalNCells += 1;
        }
        // std::cout << "fV0Hits[iV0Hits = " << iV0Hits << ", fRunNum=" << fRunNum << "] = " << fV0Hits[iV0Hits] << endl;
        // std::cout << "fV0TotalNCells (fRunNum = " << fRunNum << ") = " << fV0TotalNCells << endl;
  }
  fCounterH->Fill(18);

  /* - AD: we try to find the AD object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without AD's information. Or at least, this
     - is my impression of it (filling fCounterH). AD information:
     - fADADecision: small detector in ALICE, ADA and ADC at large distances;
     - fADCDecision: again, maybe check whether it is cells or boolean, same as V0.
  */
  // AD
  AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  fCounterH->Fill(19);
  if(dataAD) {
        fCounterH->Fill(iSelectionCounter);
        iSelectionCounter++;
        fCounterH->Fill(20);

        fADADecision = dataAD->GetADADecision();
        fADCDecision = dataAD->GetADCDecision();
        fCounterH->Fill(21);
  }
  fCounterH->Fill(22);

  // END EVENT DATA EXTRACTION
  //_______________________________
  // EVENT SELECTION
  /* - This is Eugeny Krishen's event selection from the talk in 14/1/2019 for
     - the PWG-UD (UPC oriented) meeting. The event selection requires:
     - CMUP11-B triggers;
     - Maximum 2 V0C cells fired;
     - Empty V0A decision;
     - Empty ADA decision;
     - Empty ADC decision;
     - 0 tracklets in SPD;
     - Exactly 2 unlike-sign muons;
   */
  /* - CMUP11-B triggers: I have to check with my supervisor, but this requirement
     - may have already been satisfied with the requirements for the trigger info
   */
  /* - Maximum 2 V0C cells fired:
     -
   */
  /* - Empty V0A decision
     - Empty ADA decision
     - Empty ADC decision
   */
  if(fV0ADecision != 0) {
       PostData(1, fOutputList);
       return;
  }
  if(fADADecision != 0) {
       PostData(1, fOutputList);
       return;
  }
  if(fADCDecision != 0) {
       PostData(1, fOutputList);
       return;
  }
  /* - Empty V0C decision
   * - or at least in beam timing.
   */
  if( !(fV0CDecision == 0 || fV0CDecision == 1) ) {
       PostData(1, fOutputList);
       return;
  }
  /* - 0 tracklets in SPD
     - Is it like this?? Not too sure what fTracklets was!
   */
  // if(fTracklets != 0) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  /* - Maximum 2 V0C cells fired.
     -
     - Trying a more readable and immediate approach.
   */
  // if( !(fV0TotalNCells < 2) ) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  if( fV0TotalNCells > 2 ) {
       PostData(1, fOutputList);
       return;
  }



  /* - We are finally at the starting point. We loop over the tracks and select
     - the good muons. Later on everything should happen in this loop. Let us
     - see what the future has in hold.
     -
     - Saturday: I moved the creation of the AliAODTrack* track outside of the
     - loop as it would have been otherwise created for each single iteration.
     - This could have caused massive memory issues especially to grid. I have
     - added a second AliAODTrack* track[2] to hold the second supposed muon.
     - Now this is ready to send the information to two TLorentzVectors to
     - obtain the invariant mass of the J/Psi through the Mag() method of the
     - class. Hope for the best.
   */
  Int_t nGoodMuons = 0;
  AliAODTrack* track[2];
  track[0]         = 0x0;
  track[1]         = 0x0;
  for(Int_t iTrack(0); iTrack < nTracks; iTrack++) {
    /* - This should be another form of event selection.
       - I am basically requesting the presence of TWO good muons only.
       - Later I will be checking whether of they are likesign or unlikesign.
     */
    if(nGoodMuons > 2) {
         PostData(1, fOutputList);
         return;
    }
    // get track
    // AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
    // if(!track) return;
    //
    // // is it a good muon track?
    // if(!track->IsMuonTrack()) continue;
    // if(!fMuonTrackCuts->IsSelected(track)) continue;

    track[nGoodMuons] = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
    if(!track[nGoodMuons]) return;

    // is it a good muon track?
    if(!track[nGoodMuons]->IsMuonTrack()) {
        // track[nGoodMuons] = 0x0;
        continue;
    }
    if(!fMuonTrackCuts->IsSelected(track[nGoodMuons])) {
        // track[nGoodMuons] = 0x0;
        continue;
    }


    /* -
     * - Compatibility with Run 1 analysis.
     * -
     */
    if ( !( (track[nGoodMuons]->Eta() < -2.5) && (track[nGoodMuons]->Eta() > -3.7) ) ) {
      continue;
    }

    // MUON SELECTION
    /* - This is Eugeny Krishen's MUON selection from the talk in 14/1/2019 for
       - the PWG-UD (UPC oriented) meeting. The event selection requires:
       - Muon trigger matching >=2 (1 GeV/c threshold);
       - (-4) < eta < (-2.5);
       - (17.5 cm) < R_{abs} < (89.5 cm);
       - p \times DCA cut;
    */

    // increase counter
    nGoodMuons++;

    // fill muon info
    // fEtaMuonH->Fill(track->Eta());
    // fRAbsMuonH->Fill(track->GetRAtAbsorberEnd());

  }
  /* - We need EXACTLY 2 good muons !!!!!
     -
   */
  if( nGoodMuons != 2 ) {
        PostData(1, fOutputList);
        return;
  }
  /* - Implementing the track cut on the unlike muons
   * -
   */
  if( (track[0]->Charge()) == (track[1]->Charge()) ) {
        PostData(1, fOutputList);
        return;
  }
  for(Int_t iFilling = 0; iFilling < nGoodMuons; iFilling++) {
        fEtaMuonH ->Fill(track[iFilling]->Eta());
        fRAbsMuonH->Fill(track[iFilling]->GetRAtAbsorberEnd());
  }
  // store muons
  fNumberMuonsH->Fill(nGoodMuons);
  fEntriesAgainstRunNumberH->Fill(fRunNum);
  /* - This is the last part of my try to obtain a proper RunNumbers histogram...
     -
   */
  fEntriesAgainstRunNumberProperlyH->Fill( Form("%d", fRunNum) , 1 );
  if (nGoodMuons>0) fCounterH->Fill(iSelectionCounter); // At least one good muon
  iSelectionCounter++;



  /* - Finally the core!!!
   * - What will be happening is that we will instantiate TLorentzVectors to
   * - obtain the invariant mass of the dimuon system. If everything goes fine
   * - after this we should be able to obtain the peak of the J/Psi. But
   * - things never go as expected, so who knows!
   */
  TLorentzVector muons[2];
  TLorentzVector possibleJPsi;
  Double_t       chargeOfMuons[2];
  for(int indexMuon = 0; indexMuon < 2; indexMuon++) {
        muons[indexMuon].SetPtEtaPhiM(   track[indexMuon]->Pt(),
                                         track[indexMuon]->Eta(),
                                         track[indexMuon]->Phi(),
                                         TDatabasePDG::Instance()->GetParticle(13)->Mass()
                                       );
        possibleJPsi += muons[indexMuon];
        chargeOfMuons[indexMuon] = track[indexMuon]->Charge();
  }
  fEtaDimuonH->Fill(possibleJPsi.Rapidity());
  fInvariantMassDistributionH->Fill(possibleJPsi.Mag());
  fInvariantMassDistributionExtendedH->Fill(possibleJPsi.Mag());

  /**
   * - Pt-integrated analysis
   * - in 2 rapidity bins.
   * -
   */
  if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -3.25 ) {
    fInvariantMassDistributionRapidityBinsH[0]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -2.50 ) {
    fInvariantMassDistributionRapidityBinsH[1]->Fill(possibleJPsi.Mag());
  }

  /**
   * - Pt-integrated analysis
   * - in 3 rapidity bins.
   * -
   */
  if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.50 ) {
    fInvariantMassDistributionMoreRapidityBinsH[0]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.00 ) {
    fInvariantMassDistributionMoreRapidityBinsH[1]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.50 ) {
    fInvariantMassDistributionMoreRapidityBinsH[2]->Fill(possibleJPsi.Mag());
  }



  /* - Now we are evaluating the pt of the dimuon pair. Generally speaking,
     - if such a pt is less than 0.25 GeV/c then it fills the coherent
     - component, otherwise the incoherent component. At this point we may fill
     - even the dimuon pt distribution histogram and see if it looks like Kay's.
     -
   */
  Double_t ptOfTheDimuonPair = possibleJPsi.Pt();
  if( ptOfTheDimuonPair < 0.25) {
        fInvariantMassDistributionCoherentH->Fill(possibleJPsi.Mag());
        fInvariantMassDistributionCoherentExtendedH->Fill(possibleJPsi.Mag());
        if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.75 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[0]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.75 && possibleJPsi.Rapidity() <= -3.50 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[1]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.25 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[2]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -3.00 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[3]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.75 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[4]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -2.75 && possibleJPsi.Rapidity() <= -2.50 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[5]->Fill(possibleJPsi.Mag());
        }
  } else {
        fInvariantMassDistributionIncoherentH->Fill(possibleJPsi.Mag());
        fInvariantMassDistributionIncoherentExtendedH->Fill(possibleJPsi.Mag());
  }
  // fDimuonPtDistributionH->Fill(ptOfTheDimuonPair);
  if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
    fDimuonPtDistributionH            ->Fill(ptOfTheDimuonPair);
    fDimuonPtDistributionShiftPlusOneH->Fill(ptOfTheDimuonPair);
  }

  if( ptOfTheDimuonPair < 0.200 ) {
    fInvariantMassDistributionCoherentShiftMinusTwoH->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftMinusTwoH->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.225 ) {
    fInvariantMassDistributionCoherentShiftMinusOneH->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftMinusOneH->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.275 ) {
    fInvariantMassDistributionCoherentShiftPlusOneH ->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftPlusOneH ->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.300 ) {
    fInvariantMassDistributionCoherentShiftPlusTwoH ->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftPlusTwoH ->Fill(possibleJPsi.Mag());
  }




  /* - Now this is a critical part of  the analysis. What happens next is a
     - differential analysis in terms of the energy perceived by the neutron ZDC.
     - What it means is that now we may cut on those sensible values to select
     - only those J/Psi candidates falling under a certain peak of the neutron
     - ZNC energy distribution. It will be seen that the fZNCEnergyAgainstEntriesH
     - plot will present many gaussian-like peaks. Each peak represent an
     - increasingly large number of neutrons seen by the ZNC.
     -
     - Starting from the first peak, 0n, then 1n, hopefully 2n, but anything
     - else is more like a guess. If my understanding is good enough, even the
     - 2n peak requires user input to facilitate the minimizer's job.
     -
     - So, first thing first, Guillermo Contreras has suggested the preliminary
     - cut on the ZDC time, quoting:
     - "The energy value makes sense only when the time information is not
     - -999... You can choose times |t|<5 ns to plot the energy distributions
     - in the neutron ZDC".
     -
     - This happens with the request |fZNCTime|<5 if I have understood correctly.
     - After this we can fill whatever histogram we want to.
     -
     -
     -
     - NEW: after UPC meeting 5/3/2019
     - On ZDC timing. Usually we use time information from TDCs corresponding to
     - the common PMT (reads all four ZN sectors) on both sides. Each AOD event
     - contains information on up to four consecutive timing hits from these
     - TDCs within +/-12 bcs around the trigger bunch crossing. These hits are
     - stored in fZNATDCm and fZNCTDCm arrays:
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L153
     - and can be accessed as in:
     -
     - AliAODZDC* aodZDC = aod->GetZDCData();
     - for (Int_t i=0;i<4;i++) fZNATDC[i] = aodZDC->GetZNATDCm(i);
     - for (Int_t i=0;i<4;i++) fZNCTDC[i] = aodZDC->GetZNCTDCm(i);
     -
     - These hits may come from hadronic or EMD processes in neighbouring bcs.
     - In Pb-Pb we usually have 0-2 hits within +/-12 bcs mainly due to EMD.
     - Unused timing slots in these arrays are filled with large negative value
     - (-999). In order to check if there was a timing hit in the trigger bc,
     - you have to check if at least one timing hit out of four is within +/-2
     - ns around 0.
     -
     - Regarding these getters GetZNATime() and GetZNCTime(), defined here:
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L51
     - They are outdated because, as mentioned here, they return timing
     - information from the first slot in those arrays (fZNATDCm[0], fZNCTDCm[0]):
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L145
     - The first hit often corresponds to previous bunch crossings (e.g. EMD),
     - while interesting hit around 0 may be stored in the next slots.
     -
     -
   */
  Bool_t isZNAfired = kFALSE;
  Bool_t isZNCfired = kFALSE;
  Bool_t isZNAfiredStrict = kFALSE;
  Bool_t isZNCfiredStrict = kFALSE;
  Int_t  counterZNA = 0;
  Int_t  counterZNC = 0;
  /* - Note that in C++ the && and || operators "short-circuit". That means that
     - they only evaluate a parameter if required. If the first parameter to &&
     - is false, or the first to || is true, the rest will not be evaluated.
     - That means that writing:
     - if ( (isZNAfired == 0) && (...) )
     - should mean effectively
     - if ( isZNAfired != 0 ) continue;
     - hence it should be *at least* one hit!!!
     -
   */
  for(Int_t iZDC = 0; iZDC < 4 ; iZDC++) {
    if ( (isZNAfired == 0) && (fZNATDC[iZDC] > -2.) && (fZNATDC[iZDC] < 2.) ) {
      isZNAfired = kTRUE;
      /* - After mail with Chiara Oppedisano, it seems like the best way
         - to proceed is to firstly call the IsZNAfired() and then filling...
         -
         - If this doesn't appear in later pulls it is because this
         - doesn't seem to suit my case...
         -
       */
      // if( dataZDC->IsZNAfired() ) {
      //   if ( (possibleJPsi.Mag() > 2.85) && (possibleJPsi.Mag() < 3.35) ){
      //     fZNATimeAgainstEntriesH->Fill(fZNATDC[iZDC]);
      //   }
      // }
      // fCounterZNAH->Fill(counterZNA);
    }
    if ( (isZNCfired == 0) && (fZNCTDC[iZDC] > -2.) && (fZNCTDC[iZDC] < 2.) ) {
      isZNCfired = kTRUE;
      // if( dataZDC->IsZNCfired() ) {
      //   if ( (possibleJPsi.Mag() > 2.85) && (possibleJPsi.Mag() < 3.35) ){
      //     fZNCTimeAgainstEntriesH->Fill(fZNCTDC[iZDC]);
      //   }
      // }
      // fCounterZNCH->Fill(counterZNC);
    }
    counterZNA++;
    counterZNC++;
  }

  if ( isZNCfired != 0 ) {
    fZNCEnergyAgainstEntriesH        ->Fill(fZNCEnergy);
    fZNCEnergyAgainstEntriesExtendedH->Fill(fZNCEnergy);
    // if ( calibrated == 0 ) fZNCEnergyUncalibratedH->Fill(fZNCEnergy);
    // if ( calibrated == 1 ) {
    //   fZNCEnergyCalibratedH          ->Fill( fZNCEnergy );
    //   fZNCEnergyCalibratedHigherGainH->Fill( dataZDC->GetZNCTowerEnergyLR()[0] );
    // }
  }
  fZNCEnergyBeforeTimingSelectionH        ->Fill(fZNCEnergy);
  fZNCEnergyBeforeTimingSelectionExtendedH->Fill(fZNCEnergy);
  if ( dataZDC->IsZNCfired() && ( isZNCfired != 0 ) ) {
    fZNCEnergyAgainstEntriesExtendedHv2->Fill(fZNCEnergy);
  }
  if ( dataZDC->IsZNAfired() && ( isZNAfired != 0 ) ) {
    fZNAEnergyAgainstEntriesExtendedHv2->Fill(fZNAEnergy);
  }
  if ( isZNAfired != 0 ) {
    fZNAEnergyAgainstEntriesH        ->Fill(fZNAEnergy);
    fZNAEnergyAgainstEntriesExtendedH->Fill(fZNAEnergy);
    // if ( calibrated == 0 ) fZNAEnergyUncalibratedH->Fill(fZNAEnergy);
    // if ( calibrated == 1 ) {
    //   fZNAEnergyCalibratedH          ->Fill( fZNAEnergy );
    //   fZNAEnergyCalibratedHigherGainH->Fill( dataZDC->GetZNATowerEnergyLR()[0] );
    // }
  }
  fZNAEnergyBeforeTimingSelectionH        ->Fill(fZNAEnergy);
  fZNAEnergyBeforeTimingSelectionExtendedH->Fill(fZNAEnergy);



  if( isZNCfired == 0 ) {
        if( isZNAfired == 0 ) {
            if ( ptOfTheDimuonPair < 1.00 ) {
                fInvariantMassDistribution0N0NH->Fill(possibleJPsi.Mag());
                /**
                 * - Pt-integrated analysis
                 * - in 2 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -3.25 ) {
                  fInvariantMassDistributionRapidityBins0N0NH[0]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -2.50 ) {
                  fInvariantMassDistributionRapidityBins0N0NH[1]->Fill(possibleJPsi.Mag());
                }
                /**
                 * - Pt-integrated analysis
                 * - in 3 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.50 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[0]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.00 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[1]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.50 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[2]->Fill(possibleJPsi.Mag());
                }
                /**
                 * - Pt-integrated analysis
                 * - in 2 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -3.10 ) {
                  fInvariantMassDistributionSmall0N0NH               ->Fill(possibleJPsi.Mag());
                  fInvariantMassDistributionRapidityBinsSmall0N0NH[0]->Fill(possibleJPsi.Mag());
                  // fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
                  // fDimuonPtDistributionRestrictedRapidity0N0N36to31H ->Fill(ptOfTheDimuonPair);
                } else if ( possibleJPsi.Rapidity() > -3.10 && possibleJPsi.Rapidity() <= -2.60 ) {
                  fInvariantMassDistributionSmall0N0NH               ->Fill(possibleJPsi.Mag());
                  fInvariantMassDistributionRapidityBinsSmall0N0NH[1]->Fill(possibleJPsi.Mag());
                  // fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
                  // fDimuonPtDistributionRestrictedRapidity0N0N31to26H ->Fill(ptOfTheDimuonPair);
                }

            }

            if (        (possibleJPsi.Rapidity() > -3.60) && (possibleJPsi.Rapidity() <= -3.10) && (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
              fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
              fDimuonPtDistributionRestrictedRapidity0N0N36to31H ->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Rapidity() > -3.10) && (possibleJPsi.Rapidity() <= -2.60) && (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
              fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
              fDimuonPtDistributionRestrictedRapidity0N0N31to26H ->Fill(ptOfTheDimuonPair);
            }

        }
  }



  /* -
     - Now we are ordering the muons. The first muon will always be positive.
     - This is useful for the histograms...
   */
  TLorentzVector muonsCopy[2];
  TLorentzVector muonsCopy2[2];
  TLorentzVector possibleJPsiCopy;
  if( chargeOfMuons[0] > 0 ){
    muonsCopy[0]     = muons[0];
    muonsCopy[1]     = muons[1];
  } else if( chargeOfMuons[0] < 0 ){
    muonsCopy[0]     = muons[1];
    muonsCopy[1]     = muons[0];
  }
  muonsCopy2[0] = muonsCopy[0];
  muonsCopy2[1] = muonsCopy[1];
  possibleJPsiCopy = possibleJPsi;
  /* - If we are in the J/Psi peak, hence 2.8 < M < 3.3 GeV/c, AND if we are
     - in the coherent regime, so if the Pt < 0.25 GeV/c, we fill the plots.
     -
     - In the following note that the rapidity is well computed, so we are
     - dealing with negative values... -4.0 < Y < -2.5 !!!
     -
   */
  Double_t possibleJPsiCopyMag =possibleJPsiCopy.Mag();





  // post the data
  PostData(1, fOutputList);
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::Terminate(Option_t *)
{
    cout << endl;
    // terminate
    // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
