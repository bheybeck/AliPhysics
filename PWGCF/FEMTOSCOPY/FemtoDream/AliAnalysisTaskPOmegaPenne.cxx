// /*
//  * AliAnalysisTaskPOmegaPenne.cxx
//  *
//  *  Created on: 11 Dec 2019
//  *      Author: Boris Bajtl
//  */



#include "AliAnalysisTaskPOmegaPenne.h"
#include <string.h>
#include "AliNanoAODTrack.h"
#include "TDatabasePDG.h"

ClassImp(AliAnalysisTaskPOmegaPenne)

    AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne() :  AliAnalysisTaskSE(),
                                                                fIsMC(false),
                                                                bIsMixing(true),
                                                                bPCinvMass(false),
                                                                VEvent(0),
                                                                VTrack(0),
                                                                fEvent(0),
                                                                fTrack(0),
                                                                fEventCuts(0),
                                                                fEventCuts2(0),
                                                                fv0(0),
                                                                fv0_2(0),
                                                                fCascade(0),
                                                                fCascade2(0),
                                                                fLambdaV0Cuts(0),
                                                                fLambdaV0Cuts2(0),
                                                                fAntiLambdaV0Cuts(0),
                                                                fAntiLambdaV0Cuts2(0),
                                                                fCascadeCutsXi(0),
                                                                fCascadeCutsXi2(0),
                                                                fCascadeCutsAntiXi(0),
                                                                fCascadeCutsAntiXi2(0),
                                                                fConfig(0),
                                                                fPairCleaner(0),
                                                                fPairCleaner2(0),
                                                                fPartColl(0),
                                                                fPartColl2(0),
                                                                fGTI(0),
                                                                fTrackBufferSize(10000),
                                                                tlEventCuts(0),
                                                                tlLambdaList(0),
                                                                tlAntiLambdaList(0),
                                                                tlCascadeCutsXi(0),
                                                                tlAntiCascadeCutsXi(0),
                                                                tlEventCuts2(0),
                                                                tlLambdaList2(0),
                                                                tlAntiLambdaList2(0),
                                                                tlCascadeCutsXi2(0),
                                                                tlAntiCascadeCutsXi2(0),
                                                                tlResults(0),
                                                                tlResults2(0),
                                                                tlResultsQA(0),
                                                                tlResultsQA2(0),
                                                                tlLambdaMC(0),
                                                                tlAntiLambdaMC(0),
                                                                tlRecombination_before(0),  // recombination TList before
                                                                tlRecombination_after(0),  // recombination TList after
                                                                // mixing before
                                                                hInvMassLambda_sanityCheck_before(0),
                                                                hInvMassLambda_total_before(0),
                                                                hInvMassLambda_shared_pion_before(0),
                                                                hInvMassLambda_shared_proton_before(0),
                                                                hInvMassLambda_shared_lambda_before(0),
                                                                hInvMassXi_sanityCheck_before(0),
                                                                hInvMassXi_total_before(0),
                                                                hInvMassXi_shared_bach_before(0),
                                                                hInvMassXi_shared_pi_daugh_before(0),
                                                                hInvMassXi_shared_prot_daugh_before(0),
                                                                hInvMassXi_shared_Lambda_before(0),
                                                                hInvMassXi_shared_pion_bach_prot_daugh_before(0),
                                                                hInvMassXi_nothing_shared(0),
                                                                hInvMassAntiLambda_sanityCheck_before(0),
                                                                hInvMassAntiLambda_total_before(0),
                                                                hInvMassAntiLambda_shared_pion_before(0),
                                                                hInvMassAntiLambda_shared_proton_before(0),
                                                                hInvMassAntiXi_sanityCheck_before(0),
                                                                hInvMassAntiXi_total_before(0),
                                                                hInvMassAntiXi_shared_bach_before(0),
                                                                hInvMassAntiXi_shared_pi_daugh_before(0),
                                                                hInvMassAntiXi_shared_prot_daugh_before(0),
                                                                hInvMassAntiXi_shared_Lambda_before(0),
                                                                hInvMassAntiXi_shared_pion_bach_prot_daugh_before(0),
                                                                hInvMassAntiXi_nothing_shared(0),
                                                                fEvtCounterBefore(0),
                                                                // mixing after
                                                                hInvMassLambda_sanityCheck_after(0),
                                                                hInvMassLambda_pi_bach_Xi_after(0),
                                                                hInvMassLambda_pi_daugh_Xi_after(0),
                                                                hInvMassLambda_prot_Xi_after(0),
                                                                hInvMassLambda_full_lambda_from_Xi_after(0),
                                                                hInvMassXi_sanityCheck_after(0),
                                                                hInvMassXi_Lamda_pi_daugh_after(0),
                                                                hInvMassXi_Lamda_prot_daugh_after(0),
                                                                hInvMassXi_Lamda_pi_bach_after(0),
                                                                hInvMassXi_Lamda_full_after(0),
                                                                hInvMassXi_Lamda_pi_bach_prot_daugh_after(0),
                                                                hInvMassAntiLambda_sanityCheck_after(0),
                                                                hInvMassAntiLambda_pi_bach_Xi_after(0),
                                                                hInvMassAntiLambda_pi_daugh_Xi_after(0),
                                                                hInvMassAntiLambda_prot_Xi_after(0),
                                                                hInvMassAntiLambda_full_lambda_from_Xi_after(0),
                                                                hInvMassAntiXi_sanityCheck_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_daugh_after(0),
                                                                hInvMassAntiXi_AntiLamda_antiprot_daugh_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_bach_after(0),
                                                                hInvMassAntiXi_AntiLamda_full_after(0),
                                                                hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after(0),
                                                                fEvtCounterAfter(0)
{
}
AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne(const char *name, bool isMC, bool bMixing, bool bPairCleanInvMass) : AliAnalysisTaskSE(name),
                                                                                      fIsMC(isMC),
                                                                                      bIsMixing(bMixing),
                                                                                      bPCinvMass(bPairCleanInvMass),
                                                                                      VEvent(0),
                                                                                      VTrack(0),
                                                                                      fEvent(0),
                                                                                      fTrack(0),
                                                                                      fEventCuts(0),
                                                                                      fEventCuts2(0),
                                                                                      fv0(0),
                                                                                      fv0_2(0),
                                                                                      fCascade(0),
                                                                                      fCascade2(0),
                                                                                      fLambdaV0Cuts(0),
                                                                                      fAntiLambdaV0Cuts(0),
                                                                                      fCascadeCutsXi(0),
                                                                                      fCascadeCutsAntiXi(0),
                                                                                      fLambdaV0Cuts2(0),
                                                                                      fAntiLambdaV0Cuts2(0),
                                                                                      fCascadeCutsXi2(0),
                                                                                      fCascadeCutsAntiXi2(0),
                                                                                      fConfig(0),
                                                                                      fPairCleaner(0),
                                                                                      fPairCleaner2(0),
                                                                                      fPartColl(0),
                                                                                      fPartColl2(0),
                                                                                      fGTI(0),
                                                                                      fTrackBufferSize(10000),
                                                                                      tlEventCuts(0),
                                                                                      tlLambdaList(0),
                                                                                      tlAntiLambdaList(0),
                                                                                      tlCascadeCutsXi(0),
                                                                                      tlAntiCascadeCutsXi(0),
                                                                                      tlEventCuts2(0),
                                                                                      tlLambdaList2(0),
                                                                                      tlAntiLambdaList2(0),
                                                                                      tlCascadeCutsXi2(0),
                                                                                      tlAntiCascadeCutsXi2(0),
                                                                                      tlResults(0),
                                                                                      tlResults2(0),
                                                                                      tlResultsQA(0),
                                                                                      tlResultsQA2(0),
                                                                                      tlLambdaMC(0),
                                                                                      tlAntiLambdaMC(0),
                                                                                      tlRecombination_before(0),  // recombination TList before
                                                                                      tlRecombination_after(0),  // recombination TList after
                                                                                      // mixing before
                                                                                      hInvMassLambda_sanityCheck_before(0),
                                                                                      hInvMassLambda_total_before(0),
                                                                                      hInvMassLambda_shared_pion_before(0),
                                                                                      hInvMassLambda_shared_proton_before(0),
                                                                                      hInvMassLambda_shared_lambda_before(0),
                                                                                      hInvMassXi_sanityCheck_before(0),
                                                                                      hInvMassXi_total_before(0),
                                                                                      hInvMassXi_shared_bach_before(0),
                                                                                      hInvMassXi_shared_pi_daugh_before(0),
                                                                                      hInvMassXi_shared_prot_daugh_before(0),
                                                                                      hInvMassXi_shared_Lambda_before(0),
                                                                                      hInvMassXi_shared_pion_bach_prot_daugh_before(0),
                                                                                      hInvMassXi_nothing_shared(0),
                                                                                      hInvMassAntiLambda_sanityCheck_before(0),
                                                                                      hInvMassAntiLambda_total_before(0),
                                                                                      hInvMassAntiLambda_shared_pion_before(0),
                                                                                      hInvMassAntiLambda_shared_proton_before(0),
                                                                                      hInvMassAntiXi_sanityCheck_before(0),
                                                                                      hInvMassAntiXi_total_before(0),
                                                                                      hInvMassAntiXi_shared_bach_before(0),
                                                                                      hInvMassAntiXi_shared_pi_daugh_before(0),
                                                                                      hInvMassAntiXi_shared_prot_daugh_before(0),
                                                                                      hInvMassAntiXi_shared_Lambda_before(0),
                                                                                      hInvMassAntiXi_shared_pion_bach_prot_daugh_before(0),
                                                                                      hInvMassAntiXi_nothing_shared(0),
                                                                                      fEvtCounterBefore(0),
                                                                                      // mixing after
                                                                                      hInvMassLambda_sanityCheck_after(0),
                                                                                      hInvMassLambda_pi_bach_Xi_after(0),
                                                                                      hInvMassLambda_pi_daugh_Xi_after(0),
                                                                                      hInvMassLambda_prot_Xi_after(0),
                                                                                      hInvMassLambda_full_lambda_from_Xi_after(0),
                                                                                      hInvMassXi_sanityCheck_after(0),
                                                                                      hInvMassXi_Lamda_pi_daugh_after(0),
                                                                                      hInvMassXi_Lamda_prot_daugh_after(0),
                                                                                      hInvMassXi_Lamda_pi_bach_after(0),
                                                                                      hInvMassXi_Lamda_full_after(0),
                                                                                      hInvMassXi_Lamda_pi_bach_prot_daugh_after(0),
                                                                                      hInvMassAntiLambda_sanityCheck_after(0),
                                                                                      hInvMassAntiLambda_pi_bach_Xi_after(0),
                                                                                      hInvMassAntiLambda_pi_daugh_Xi_after(0),
                                                                                      hInvMassAntiLambda_prot_Xi_after(0),
                                                                                      hInvMassAntiLambda_full_lambda_from_Xi_after(0),
                                                                                      hInvMassAntiXi_sanityCheck_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_daugh_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antiprot_daugh_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_bach_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_full_after(0),
                                                                                      hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after(0),
                                                                                      fEvtCounterAfter(0)
                                                                                      
{
    DefineOutput(1, TList::Class());    // Event Cuts
    DefineOutput(2, TList::Class());    // Lambda Track Cuts
    DefineOutput(3, TList::Class());    // Anti Lambda Track Cuts
    DefineOutput(4, TList::Class());    // Xi Track Cuts
    DefineOutput(5, TList::Class());    // Anti Xi Track Cuts
    DefineOutput(6, TList::Class());    // Results - PairCleaner  - Keep Lambda
    DefineOutput(7, TList::Class());    // QA Results             - Keep Lambda

    DefineOutput(8, TList::Class());    // Event Cuts             - Keep Xi
    DefineOutput(9, TList::Class());    // Lambda Track Cuts      - Keep Xi
    DefineOutput(10, TList::Class());   // Anti Lambda Track Cuts - Keep Xi
    DefineOutput(11, TList::Class());   // Xi Track Cuts          - Keep Xi
    DefineOutput(12, TList::Class());   // Anti Xi Track Cuts     - Keep Xi
    DefineOutput(13, TList::Class());   // Results2 - PairCleaner - Keep Xi
    DefineOutput(14, TList::Class());   // QA Results2            - Keep Xi
    DefineOutput(15, TList::Class());       // reconstruction from daugthers histograms BEFORE Paricleaner
    DefineOutput(16, TList::Class());       // reconstruction from daugthers histograms AFTER PairCleaner

    if (isMC)
    {
        DefineOutput(17, TList::Class());    // MC V0 - Lamba
        DefineOutput(18, TList::Class());    // MC AntiV0 - AntiLambda
    }
}
AliAnalysisTaskPOmegaPenne::~AliAnalysisTaskPOmegaPenne()       // Destructor
{
    delete VEvent;
    delete VTrack;
    delete fEvent;
    delete fTrack;
    delete fEventCuts;
    delete fEventCuts2;
    delete fv0;
    delete fv0_2;
    delete fCascade;
    delete fCascade2;
    delete fLambdaV0Cuts;
    delete fAntiLambdaV0Cuts;
    delete fCascadeCutsXi;
    delete fCascadeCutsAntiXi;
    delete fLambdaV0Cuts2;
    delete fAntiLambdaV0Cuts2;
    delete fCascadeCutsXi2;
    delete fCascadeCutsAntiXi2;
    delete fConfig;
    delete fPairCleaner;
    delete fPairCleaner2;
    delete fPartColl;
    delete fPairCleaner2;
    delete *fGTI;
    delete tlEventCuts;
    delete tlLambdaList;
    delete tlAntiLambdaList;
    delete tlCascadeCutsXi;
    delete tlAntiCascadeCutsXi;
    delete tlEventCuts2;
    delete tlLambdaList2;
    delete tlAntiLambdaList2;
    delete tlCascadeCutsXi2;
    delete tlAntiCascadeCutsXi2;
    delete tlResults;
    delete tlResults2;
    delete tlResultsQA;
    delete tlResultsQA2;
    delete tlLambdaMC;
    delete tlAntiLambdaMC;
    delete tlRecombination_before;      // recombination TList
    delete tlRecombination_after;       // recombination TList
    // mixing before
    delete hInvMassLambda_sanityCheck_before;
    delete hInvMassLambda_total_before;
    delete hInvMassLambda_shared_pion_before;
    delete hInvMassLambda_shared_proton_before;
    delete hInvMassLambda_shared_lambda_before;
    delete hInvMassXi_sanityCheck_before;
    delete hInvMassXi_total_before;
    delete hInvMassXi_shared_bach_before;
    delete hInvMassXi_shared_pi_daugh_before;
    delete hInvMassXi_shared_prot_daugh_before;
    delete hInvMassXi_shared_Lambda_before;
    delete hInvMassXi_shared_pion_bach_prot_daugh_before;
    delete hInvMassXi_nothing_shared;
    delete hInvMassAntiLambda_sanityCheck_before;
    delete hInvMassAntiLambda_total_before;
    delete hInvMassAntiLambda_shared_pion_before;
    delete hInvMassAntiLambda_shared_proton_before;
    delete hInvMassAntiXi_sanityCheck_before;
    delete hInvMassAntiXi_total_before;
    delete hInvMassAntiXi_shared_bach_before;
    delete hInvMassAntiXi_shared_pi_daugh_before;
    delete hInvMassAntiXi_shared_prot_daugh_before;
    delete hInvMassAntiXi_shared_Lambda_before;
    delete hInvMassAntiXi_shared_pion_bach_prot_daugh_before;
    delete hInvMassAntiXi_nothing_shared;
    delete fEvtCounterBefore;
    // mixing after
    delete hInvMassLambda_sanityCheck_after;
    delete hInvMassLambda_pi_bach_Xi_after;
    delete hInvMassLambda_pi_daugh_Xi_after;
    delete hInvMassLambda_prot_Xi_after;
    delete hInvMassLambda_full_lambda_from_Xi_after;
    delete hInvMassXi_sanityCheck_after;
    delete hInvMassXi_Lamda_pi_daugh_after;
    delete hInvMassXi_Lamda_prot_daugh_after;
    delete hInvMassXi_Lamda_pi_bach_after;
    delete hInvMassXi_Lamda_full_after;
    delete hInvMassXi_Lamda_pi_bach_prot_daugh_after;
    delete hInvMassAntiLambda_sanityCheck_after;
    delete hInvMassAntiLambda_pi_bach_Xi_after;
    delete hInvMassAntiLambda_pi_daugh_Xi_after;
    delete hInvMassAntiLambda_prot_Xi_after;
    delete hInvMassAntiLambda_full_lambda_from_Xi_after;
    delete hInvMassAntiXi_sanityCheck_after;
    delete hInvMassAntiXi_AntiLamda_antipi_daugh_after;
    delete hInvMassAntiXi_AntiLamda_antiprot_daugh_after;
    delete hInvMassAntiXi_AntiLamda_antipi_bach_after;
    delete hInvMassAntiXi_AntiLamda_full_after;
    delete hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after;
    delete fEvtCounterAfter;

    if (fGTI) delete fGTI;
}

// // Copy Constructor
AliAnalysisTaskPOmegaPenne::AliAnalysisTaskPOmegaPenne(const AliAnalysisTaskPOmegaPenne &obj) : AliAnalysisTaskSE(obj),
                                                                                                fIsMC(obj.fIsMC),
                                                                                                bIsMixing(obj.bIsMixing),
                                                                                                bPCinvMass(obj.bPCinvMass),
                                                                                                VEvent(obj.VEvent),
                                                                                                VTrack(obj.VTrack),
                                                                                                fEvent(obj.fEvent),
                                                                                                fTrack(obj.fTrack),
                                                                                                fEventCuts(obj.fEventCuts),
                                                                                                fEventCuts2(obj.fEventCuts2),
                                                                                                fv0(obj.fv0),
                                                                                                fv0_2(obj.fv0_2),
                                                                                                fCascade(obj.fCascade),
                                                                                                fCascade2(obj.fCascade2),
                                                                                                fLambdaV0Cuts(obj.fLambdaV0Cuts),
                                                                                                fAntiLambdaV0Cuts(obj.fAntiLambdaV0Cuts),
                                                                                                fCascadeCutsXi(obj.fCascadeCutsXi),
                                                                                                fCascadeCutsAntiXi(obj.fCascadeCutsAntiXi),
                                                                                                fLambdaV0Cuts2(obj.fLambdaV0Cuts2),
                                                                                                fAntiLambdaV0Cuts2(obj.fAntiLambdaV0Cuts2),
                                                                                                fCascadeCutsXi2(obj.fCascadeCutsXi2),
                                                                                                fCascadeCutsAntiXi2(obj.fCascadeCutsAntiXi2),
                                                                                                fConfig(obj.fConfig),
                                                                                                fPairCleaner(obj.fPairCleaner),
                                                                                                fPartColl(obj.fPartColl),
                                                                                                fPartColl2(obj.fPartColl2),
                                                                                                fPairCleaner2(obj.fPairCleaner2),
                                                                                                fGTI(obj.fGTI),
                                                                                                fTrackBufferSize(obj.fTrackBufferSize),
                                                                                                tlEventCuts(obj.tlEventCuts),
                                                                                                tlLambdaList(obj.tlLambdaList),
                                                                                                tlAntiLambdaList(obj.tlAntiLambdaList),
                                                                                                tlCascadeCutsXi(obj.tlCascadeCutsXi),
                                                                                                tlAntiCascadeCutsXi(obj.tlAntiCascadeCutsXi),
                                                                                                tlEventCuts2(obj.tlEventCuts2),
                                                                                                tlLambdaList2(obj.tlLambdaList2),
                                                                                                tlAntiLambdaList2(obj.tlAntiLambdaList2),
                                                                                                tlCascadeCutsXi2(obj.tlCascadeCutsXi2),
                                                                                                tlAntiCascadeCutsXi2(obj.tlAntiCascadeCutsXi2),
                                                                                                tlResults(obj.tlResults),
                                                                                                tlResults2(obj.tlResults2),
                                                                                                tlResultsQA(obj.tlResultsQA),
                                                                                                tlResultsQA2(obj.tlResultsQA2),
                                                                                                tlLambdaMC(obj.tlLambdaMC),
                                                                                                tlAntiLambdaMC(obj.tlAntiLambdaMC),
                                                                                                tlRecombination_before(obj.tlRecombination_before),     // recombination TList before
                                                                                                tlRecombination_after(obj.tlRecombination_after),       // recombination TList after
                                                                                                // mixing before
                                                                                                hInvMassLambda_sanityCheck_before(obj.hInvMassLambda_sanityCheck_before),
                                                                                                hInvMassLambda_total_before(obj.hInvMassLambda_total_before),
                                                                                                hInvMassLambda_shared_pion_before(obj.hInvMassLambda_shared_pion_before),
                                                                                                hInvMassLambda_shared_proton_before(obj.hInvMassLambda_shared_proton_before),
                                                                                                hInvMassLambda_shared_lambda_before(obj.hInvMassLambda_shared_lambda_before),
                                                                                                hInvMassXi_sanityCheck_before(obj.hInvMassXi_sanityCheck_before),
                                                                                                hInvMassXi_total_before(obj.hInvMassXi_total_before),
                                                                                                hInvMassXi_shared_bach_before(obj.hInvMassXi_shared_bach_before),
                                                                                                hInvMassXi_shared_pi_daugh_before(obj.hInvMassXi_shared_pi_daugh_before),
                                                                                                hInvMassXi_shared_prot_daugh_before(obj.hInvMassXi_shared_prot_daugh_before),
                                                                                                hInvMassXi_shared_Lambda_before(obj.hInvMassXi_shared_Lambda_before),
                                                                                                hInvMassXi_shared_pion_bach_prot_daugh_before(obj.hInvMassXi_shared_pion_bach_prot_daugh_before),
                                                                                                hInvMassXi_nothing_shared(obj.hInvMassXi_nothing_shared),
                                                                                                hInvMassAntiLambda_sanityCheck_before(obj.hInvMassAntiLambda_sanityCheck_before),
                                                                                                hInvMassAntiLambda_total_before(obj.hInvMassAntiLambda_total_before),
                                                                                                hInvMassAntiLambda_shared_pion_before(obj.hInvMassAntiLambda_shared_pion_before),
                                                                                                hInvMassAntiLambda_shared_proton_before(obj.hInvMassAntiLambda_shared_proton_before),
                                                                                                hInvMassAntiXi_sanityCheck_before(obj.hInvMassAntiXi_sanityCheck_before),
                                                                                                hInvMassAntiXi_total_before(obj.hInvMassAntiXi_total_before),
                                                                                                hInvMassAntiXi_shared_bach_before(obj.hInvMassAntiXi_shared_bach_before),
                                                                                                hInvMassAntiXi_shared_pi_daugh_before(obj.hInvMassAntiXi_shared_pi_daugh_before),
                                                                                                hInvMassAntiXi_shared_prot_daugh_before(obj.hInvMassAntiXi_shared_prot_daugh_before),
                                                                                                hInvMassAntiXi_shared_Lambda_before(obj.hInvMassAntiXi_shared_Lambda_before),
                                                                                                hInvMassAntiXi_shared_pion_bach_prot_daugh_before(obj.hInvMassAntiXi_shared_pion_bach_prot_daugh_before),
                                                                                                hInvMassAntiXi_nothing_shared(obj.hInvMassAntiXi_nothing_shared),
                                                                                                fEvtCounterBefore(obj.fEvtCounterBefore),
                                                                                                // mixing after
                                                                                                hInvMassLambda_sanityCheck_after(obj.hInvMassLambda_sanityCheck_after),
                                                                                                hInvMassLambda_pi_bach_Xi_after(obj.hInvMassLambda_pi_bach_Xi_after),
                                                                                                hInvMassLambda_pi_daugh_Xi_after(obj.hInvMassLambda_pi_daugh_Xi_after),
                                                                                                hInvMassLambda_prot_Xi_after(obj.hInvMassLambda_prot_Xi_after),
                                                                                                hInvMassLambda_full_lambda_from_Xi_after(obj.hInvMassLambda_full_lambda_from_Xi_after),
                                                                                                hInvMassXi_sanityCheck_after(obj.hInvMassXi_sanityCheck_after),
                                                                                                hInvMassXi_Lamda_pi_daugh_after(obj.hInvMassXi_Lamda_pi_daugh_after),
                                                                                                hInvMassXi_Lamda_prot_daugh_after(obj.hInvMassXi_Lamda_prot_daugh_after),
                                                                                                hInvMassXi_Lamda_pi_bach_after(obj.hInvMassXi_Lamda_pi_bach_after),
                                                                                                hInvMassXi_Lamda_full_after(obj.hInvMassXi_Lamda_full_after),
                                                                                                hInvMassXi_Lamda_pi_bach_prot_daugh_after(obj.hInvMassXi_Lamda_pi_bach_prot_daugh_after),
                                                                                                hInvMassAntiLambda_sanityCheck_after(obj.hInvMassAntiLambda_sanityCheck_after),
                                                                                                hInvMassAntiLambda_pi_bach_Xi_after(obj.hInvMassAntiLambda_pi_bach_Xi_after),
                                                                                                hInvMassAntiLambda_pi_daugh_Xi_after(obj.hInvMassAntiLambda_pi_daugh_Xi_after),
                                                                                                hInvMassAntiLambda_prot_Xi_after(obj.hInvMassAntiLambda_prot_Xi_after),
                                                                                                hInvMassAntiLambda_full_lambda_from_Xi_after(obj.hInvMassAntiLambda_full_lambda_from_Xi_after),
                                                                                                hInvMassAntiXi_sanityCheck_after(obj.hInvMassAntiXi_sanityCheck_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_daugh_after(obj.hInvMassAntiXi_AntiLamda_antipi_daugh_after),
                                                                                                hInvMassAntiXi_AntiLamda_antiprot_daugh_after(obj.hInvMassAntiXi_AntiLamda_antiprot_daugh_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_bach_after(obj.hInvMassAntiXi_AntiLamda_antipi_bach_after),
                                                                                                hInvMassAntiXi_AntiLamda_full_after(obj.hInvMassAntiXi_AntiLamda_full_after),
                                                                                                hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after(obj.hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after),
                                                                                                fEvtCounterAfter(obj.fEvtCounterAfter)
{
}

// AliAnalysisTaskPOmegaPenne& AliAnalysisTaskPOmegaPenne::operator=(const AliAnalysisTaskPOmegaPenne &other)
// {
//     AliAnalysisTaskSE::operator=(other);
//     this->fIsMC = other.fIsMC;
//     this->aaEvent = other.aaEvent;
//     this->aaTrack = other.aaTrack;
//     this->fOutput = other.fOutput;
//     this->fEvent = other.fEvent;
//     this->fTrack = other.fTrack;
//     this->fCascade = other.fCascade;
//     this->fEventCuts = other.fEventCuts;
//     this->fTrackCutsProton = other.fTrackCutsProton;
//     this->fTrackCutsAntiProton = other.fTrackCutsAntiProton;
//     this->fCascadeCutsXi = other.fCascadeCutsXi;
//     this->fCascadeCutsAntiXi = other.fCascadeCutsAntiXi;
//     this->fConfig = other.fConfig;
//     this->fPairCleaner = other.fPairCleaner;
//     this->fPartColl = other.fPartColl;
//     this->fGTI = other.fGTI;
//     this->fTrackBufferSize = other.fTrackBufferSize;

//     return *this;
// }

void AliAnalysisTaskPOmegaPenne::UserCreateOutputObjects()
{
   
    fEvent = new AliFemtoDreamEvent(true, true, GetCollisionCandidates(), false);
    fEvent->SetMultiplicityEstimator(fConfig->GetMultiplicityEstimator());


    fTrack = new AliFemtoDreamTrack();
    fTrack->SetUseMCInfo(fIsMC);
    fGTI = new AliVTrack *[fTrackBufferSize];
    
    fEventCuts->InitQA();
    
 
    // Lambda Cutys    ###########
    if (!fLambdaV0Cuts){AliFatal("Track Cuts for Particle Lambda not set!");}
    fLambdaV0Cuts->Init();
    fLambdaV0Cuts->SetName("Lambda");
    // ##

    // AntiLambda Cutys    ###########
    if (!fAntiLambdaV0Cuts){AliFatal("Track Cuts for Particle AntiLambda not set!");}
    fAntiLambdaV0Cuts->Init();
    fAntiLambdaV0Cuts->SetName("AntiLambda");
    // ##

    // V0 Candidates
    fv0 = new AliFemtoDreamv0();
    fv0->SetUseMCInfo(fIsMC);
    fv0->GetPosDaughter()->SetUseMCInfo(fIsMC); 
    fv0->GetNegDaughter()->SetUseMCInfo(fIsMC); 
    fv0->SetPDGCode(3122);
    fv0->SetPDGDaughterPos(2212);
    fv0->SetPDGDaughterNeg(211);
    // ##

    // Xi Cuts    ###########
    if (!fCascadeCutsXi){AliFatal("Track Cuts for Particle Xi not set!");}
    fCascadeCutsXi->Init();
    fCascadeCutsXi->SetName("Xi");
    // ##
    
    // AntiXi Cuts    ###########
    if (!fCascadeCutsAntiXi){AliFatal("Track Cuts for Particle AntiXi not set!");}
    fCascadeCutsAntiXi->Init();
    fCascadeCutsAntiXi->SetName("AntiXi");
    // ##

    // Cascade Cuts     #########
    fCascade = new AliFemtoDreamCascade();          // Initial Cascade Object
    fCascade->SetUseMCInfo(fIsMC);
    //PDG Codes should be set assuming Xi- to also work for Xi+
    fCascade->SetPDGCode(3312);
    fCascade->SetPDGDaugPos(2212);
    fCascade->GetPosDaug()->SetUseMCInfo(fIsMC);
    fCascade->SetPDGDaugNeg(211);
    fCascade->GetNegDaug()->SetUseMCInfo(fIsMC);
    fCascade->SetPDGDaugBach(211);
    fCascade->GetBach()->SetUseMCInfo(fIsMC);
    fCascade->Setv0PDGCode(3122);
    // ##

    fEventCuts2->InitQA();
    // ############################################# NUMMER 2 - only Xi left alive ############################
    // Lambda Cutys    ###########
    if (!fLambdaV0Cuts2){AliFatal("Track Cuts for Particle Lambda not set!");}
    fLambdaV0Cuts2->Init();
    fLambdaV0Cuts2->SetName("Lambda");
    // ##

    // AntiLambda Cutys    ###########
    if (!fAntiLambdaV0Cuts2){AliFatal("Track Cuts for Particle AntiLambda not set!");}
    fAntiLambdaV0Cuts2->Init();
    fAntiLambdaV0Cuts2->SetName("AntiLambda");
    // ##

    // V0 Candidates
    fv0_2 = new AliFemtoDreamv0();
    fv0_2->SetUseMCInfo(fIsMC);
    fv0_2->GetPosDaughter()->SetUseMCInfo(fIsMC); 
    fv0_2->GetNegDaughter()->SetUseMCInfo(fIsMC); 
    fv0_2->SetPDGCode(3122);
    fv0_2->SetPDGDaughterPos(2212);
    fv0_2->SetPDGDaughterNeg(211);
    // ##

    // Xi Cuts    ###########
    if (!fCascadeCutsXi2){AliFatal("Track Cuts for Particle Xi not set!");}
    fCascadeCutsXi2->Init();
    fCascadeCutsXi2->SetName("Xi");
    // ##
    
    // AntiXi Cuts    ###########
    if (!fCascadeCutsAntiXi2){AliFatal("Track Cuts for Particle AntiXi not set!");}
    fCascadeCutsAntiXi2->Init();
    fCascadeCutsAntiXi2->SetName("AntiXi");
    // ##

    // Cascade Cuts     #########
    fCascade2 = new AliFemtoDreamCascade();          // Initial Cascade Object
    fCascade2->SetUseMCInfo(fIsMC);
    //PDG Codes should be set assuming Xi- to also work for Xi+
    fCascade2->SetPDGCode(3312);
    fCascade2->SetPDGDaugPos(2212);
    fCascade2->GetPosDaug()->SetUseMCInfo(fIsMC);
    fCascade2->SetPDGDaugNeg(211);
    fCascade2->GetNegDaug()->SetUseMCInfo(fIsMC);
    fCascade2->SetPDGDaugBach(211);
    fCascade2->GetBach()->SetUseMCInfo(fIsMC);
    fCascade2->Setv0PDGCode(3122);
    // ##
    // ############################################# ENDE - NUMMER 2 - only Xi left alive ######################


    // ############################################# Recombination Cuts ######################
    // Lambda Cutys    ###########
    // if (!fLambdaV0Cuts_rec){AliFatal("Track Cuts for Particle Lambda_recombination not set!");}
    // fLambdaV0Cuts_rec->Init();
    // fLambdaV0Cuts_rec->SetName("Lambda_rec");
    // ##
    // AntiLambda Cutys    ###########
    // if (!fAntiLambdaV0Cuts_rec){AliFatal("Track Cuts for Particle AntiLambda_recombination not set!");}
    // fAntiLambdaV0Cuts_rec->Init();
    // fAntiLambdaV0Cuts_rec->SetName("AntiLambda_rec");
    // ##
    // ############################################# ENDE - Recombination Cuts ######################


    fPairCleaner = new AliFemtoDreamPairCleaner(0, 4, false);       // keep Lambdas
    fPairCleaner2 = new AliFemtoDreamPairCleaner(0, 4, false);      // keep Xi
    fPartColl = new AliFemtoDreamPartCollection(fConfig, false);
    fPartColl2 = new AliFemtoDreamPartCollection(fConfig, false);
    
    tlCascadeCutsXi = new TList();
    tlCascadeCutsXi->SetName("XiCascade");
    tlCascadeCutsXi->SetOwner();

    tlAntiCascadeCutsXi = new TList();
    tlAntiCascadeCutsXi->SetName("AntiXiCascade");
    tlAntiCascadeCutsXi->SetOwner();

    tlResultsQA = new TList();
    tlResultsQA->SetName("ResultsQA");
    tlResultsQA->SetOwner();

    tlResultsQA2 = new TList();
    tlResultsQA2->SetName("ResultsQA");
    tlResultsQA2->SetOwner();

    /////////////////////////////
    // BEFORE Paircleaning histos
    /////////////////////////////
    tlRecombination_before = new TList();        // Lambda and Xi recombination statistic histogramms for interchanged daughters
    tlRecombination_before->SetName("Recombination_before_pairclean");
    tlRecombination_before->SetOwner();
    
    // particles
    hInvMassLambda_sanityCheck_before = new TH1F("InvariantMassLambdaSanityCheck_before", "Invariant Mass LAMBDA Sanity Check before", 400, 1.00, 1.20);        // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassLambda_total_before = new TH1F("InvariantMassLambdatotal_before", "Invariant Mass LAMBDA total before", 500, 0.5, 2.5);                             // summe kombinationen mit shared tracks und non-shared
    hInvMassLambda_shared_pion_before = new TH1F("InvariantMassLambdaSharedPion_before", "Invariant Mass LAMBDA shared Pion before", 500, 0.5, 2.5);            // shared Pion - blödsinnig, hier hat man beim mixing einfach einmal das eine Lambda dann dass andere
    hInvMassLambda_shared_proton_before = new TH1F("InvariantMassLambdaSharedProton_before", "Invariant Mass LAMBDA shared Proton before", 500, 0.5, 2.5);      // shared Proton - blödsinnig, hier hat man beim mixing einfach einmal das eine Lambda dann dass andere
    hInvMassLambda_shared_lambda_before = new TH1F("InvariantMassLambdaSharedLambda_before", "Invariant Mass LAMBDA shared Lambda before", 500, 0.5, 2.5);      // fully shared Lambda - sollte leer sein
    hInvMassXi_sanityCheck_before = new TH1F("InvariantMassXiSanityCheck_before", "Invariant Mass XI Sanity Check before", 600, 1.200, 1.600);                  // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassXi_total_before = new TH1F("InvariantMassXiTotal_before", "Invariant Mass XI total before", 600, 0.700, 2.500);                                     // summe kombinationen aus shared tracks und non-shared
    hInvMassXi_shared_bach_before = new TH1F("InvariantMassXiSharedBach_before", "Invariant Mass XI shared Bachelor Pi before", 600, 0.700, 2.500);             // shared Bachelor Pion
    hInvMassXi_shared_pi_daugh_before = new TH1F("InvariantMassXiSharedPiDaugh_before", "Invariant Mass XI shared Pi Daugh before", 600, 0.700, 2.500);         // shared Daughter Pion
    hInvMassXi_shared_prot_daugh_before = new TH1F("InvariantMassXiSharedProtDaugh_before", "Invariant Mass XI shared Prot Daugh before", 600, 0.700, 2.500);   // shared Daughter Proton
    hInvMassXi_shared_Lambda_before = new TH1F("InvariantMassXiSharedLambda_before", "Invariant Mass XI shared Lambda before", 600, 0.700, 2.500);              // shared Daughter Pion and Proton - i.e. shared Lambda
    hInvMassXi_shared_pion_bach_prot_daugh_before = new TH1F("InvariantMassXiSharedPiBachProtDaugh_before", "Invariant Mass XI shared Pion Bach Prot Daugh before", 600, 0.700, 2.500);     // nur der vollständigkeitshalber (sollte nix drin sein) - geteiltes Bachelor Pion und gleichzeitig Proton Daughter
    hInvMassXi_nothing_shared = new TH1F("InvariantMassXiNothingShared_before", "Invariant Mass XI nothing shared before", 600, 0.700, 2.500);
    // anti particles
    hInvMassAntiLambda_sanityCheck_before = new TH1F("InvariantMassAntiLambdaSanityCheck_before", "Invariant Mass Anti LAMBDA Sanity Check before", 400, 1.00, 1.20);                       // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassAntiLambda_total_before = new TH1F("InvariantMassAntiLambdatotal_before", "Invariant Mass Anti LAMBDA total before", 500, 0.5, 2.5); 
    hInvMassAntiLambda_shared_pion_before = new TH1F("InvariantMassAntiLambdaSharedPion_before", "Invariant Mass Anti LAMBDA shared Pion before", 500, 0.5, 2.5);
    hInvMassAntiLambda_shared_proton_before = new TH1F("InvariantMassAntiLambdaSharedProton_before", "Invariant Mass Anti LAMBDA shared Proton before", 500, 0.5, 2.5);
    hInvMassAntiLambda_shared_lambda_before = new TH1F("InvariantMassAntiLambdaSharedLambda_before", "Invariant Mass Anti LAMBDA shared Lambda before", 500, 0.5, 2.5);
    hInvMassAntiXi_sanityCheck_before = new TH1F("InvariantMassAntiXiSanityCheck_before", "Invariant Mass Anti XI Sanity Check before", 600, 1.200, 1.600);                                 // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassAntiXi_total_before = new TH1F("InvariantMassAntiXiTotal_before", "Invariant Mass Anti XI total before", 600, 0.700, 2.500);                                      
    hInvMassAntiXi_shared_bach_before = new TH1F("InvariantMassAntiXiSharedBach_before", "Invariant Mass Anti XI shared Bachelor Pi before", 600, 0.700, 2.500); 
    hInvMassAntiXi_shared_pi_daugh_before = new TH1F("InvariantMassAntiXiSharedPiDaugh_before", "Invariant Mass Anti XI shared Pi Daugh before", 600, 0.700, 2.500); 
    hInvMassAntiXi_shared_prot_daugh_before = new TH1F("InvariantMassAntiXiSharedProtDaugh_before", "Invariant Mass Anti XI shared Prot Daugh before", 600, 0.700, 2.500); 
    hInvMassAntiXi_shared_Lambda_before = new TH1F("InvariantMassAntiXiSharedLambda_before", "Invariant Mass Anti XI shared Lambda before", 600, 0.700, 2.500); 
    hInvMassAntiXi_shared_pion_bach_prot_daugh_before = new TH1F("InvariantMassAntiXiSharedPiBachProtDaugh_before", "Invariant Mass Anti XI shared Pion Bach Prot Daugh before", 600, 0.700, 2.500);  // nur der vollständigkeitshalber (sollte nix drin sein) - geteiltes Bachelor Pion und gleichzeitig Proton Daughter
    hInvMassAntiXi_nothing_shared = new TH1F("InvariantMassAntiXiNothingShared_before", "Invariant Mass Anti XI nothing shared before", 600, 0.700, 2.500);
    //
    // Event counter for what happened how often
    fEvtCounterBefore = new TH1F("EventCounter", "Event Counter", 7, 0, 7);
    fEvtCounterBefore->GetXaxis()->SetBinLabel(1, "Prot_Lambda + pi_Xi1");        // reconstruct Lambda
    fEvtCounterBefore->GetXaxis()->SetBinLabel(2, "Prot_Lambda + pi_Xi2");        //
    fEvtCounterBefore->GetXaxis()->SetBinLabel(3, "Prot_Xi + pi_Lambda");         //
    fEvtCounterBefore->GetXaxis()->SetBinLabel(4, "Lambda + pi_Xi1");             // reconstruct Xi
    fEvtCounterBefore->GetXaxis()->SetBinLabel(5, "Lambda + pi_Xi2");             //
    fEvtCounterBefore->GetXaxis()->SetBinLabel(6, "Lambda + pi_Lambda");          //
    fEvtCounterBefore->GetXaxis()->SetBinLabel(7, "prot_Lambda + pi_Lambda");     //s reconstruct Lambda from other Lambda

    // connect to Output List
    tlRecombination_before->Add(hInvMassLambda_sanityCheck_before);
    tlRecombination_before->Add(hInvMassLambda_total_before);
    tlRecombination_before->Add(hInvMassLambda_shared_pion_before);
    tlRecombination_before->Add(hInvMassLambda_shared_proton_before);
    tlRecombination_before->Add(hInvMassLambda_shared_lambda_before);
    tlRecombination_before->Add(hInvMassXi_sanityCheck_before);
    tlRecombination_before->Add(hInvMassXi_total_before);
    tlRecombination_before->Add(hInvMassXi_shared_bach_before);
    tlRecombination_before->Add(hInvMassXi_shared_pi_daugh_before);
    tlRecombination_before->Add(hInvMassXi_shared_prot_daugh_before);
    tlRecombination_before->Add(hInvMassXi_shared_Lambda_before);
    tlRecombination_before->Add(hInvMassXi_shared_pion_bach_prot_daugh_before);
    tlRecombination_before->Add(hInvMassXi_nothing_shared);

    tlRecombination_before->Add(hInvMassAntiLambda_sanityCheck_before);
    tlRecombination_before->Add(hInvMassAntiLambda_total_before);
    tlRecombination_before->Add(hInvMassAntiLambda_shared_pion_before);
    tlRecombination_before->Add(hInvMassAntiLambda_shared_proton_before);
    tlRecombination_before->Add(hInvMassAntiLambda_shared_lambda_before);
    tlRecombination_before->Add(hInvMassAntiXi_sanityCheck_before);
    tlRecombination_before->Add(hInvMassAntiXi_total_before);
    tlRecombination_before->Add(hInvMassAntiXi_shared_bach_before);
    tlRecombination_before->Add(hInvMassAntiXi_shared_pi_daugh_before);
    tlRecombination_before->Add(hInvMassAntiXi_shared_prot_daugh_before);
    tlRecombination_before->Add(hInvMassAntiXi_shared_Lambda_before);
    tlRecombination_before->Add(hInvMassAntiXi_shared_pion_bach_prot_daugh_before);
    tlRecombination_before->Add(hInvMassAntiXi_nothing_shared);

    tlRecombination_before->Add(fEvtCounterBefore);
    // ###

    ////////////////////////////
    // AFTER Paircleaning histos
    ////////////////////////////
    tlRecombination_after = new TList();
    tlRecombination_after->SetName("Recombination_after_pairclean");
    tlRecombination_after->SetOwner();
    // particles
    hInvMassLambda_sanityCheck_after = new TH1F("InvariantMassLambdaSanityCheck_after", "Invariant Mass LAMBDA Sanity Check AFTER", 400, 1.00, 1.20);                                       // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassLambda_pi_bach_Xi_after = new TH1F("InvariantMassLambdaPiBachXi_after", "Invariant Mass Lambda - Pi Bachelor Xi AFTER", 500, 0.5, 2.5);
    hInvMassLambda_pi_daugh_Xi_after = new TH1F("InvMassLambda_Pi_daugh_Xi_after", "InvMassLambda_Pi_daugh_Xi_after", 500, 0.5, 2.5);
    hInvMassLambda_prot_Xi_after = new TH1F("InvMassLambda_Prot_Xi_after", "InvMassLambda_Prot_Xi_after", 500, 0.5, 2.5);
    hInvMassLambda_full_lambda_from_Xi_after = new TH1F("InvMassLambda_Full_Lambda_Xi_after", "InvMassLambda_Full_Lambda_from_Xi_after", 500, 0.5, 2.5);
    hInvMassXi_sanityCheck_after = new TH1F("InvariantMassXiSanityCheck_after", "Invariant_after Mass XI Sanity Check", 600, 1.200, 1.600);                                                 // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassXi_Lamda_pi_daugh_after = new TH1F("InvMassXi_Lamda_pi_daugh_after", "InvMassXi_Lamda_pi_daugh_after", 600, 0.700, 2.500); 
    hInvMassXi_Lamda_prot_daugh_after = new TH1F("InvMassXi_Lamda_prot_daugh_after", "InvMassXi_Lamda_prot_daugh_after", 600, 0.700, 2.500); 
    hInvMassXi_Lamda_pi_bach_after = new TH1F("InvMassXi_Lamda_pi_bach_after", "InvMassXi_Lamda_pi_bach_after", 600, 0.700, 2.500); 
    hInvMassXi_Lamda_full_after = new TH1F("InvMassXi_Lamda_full_after", "InvMassXi_Lamda_full_after", 600, 0.700, 2.500);                                                                  // komplettes Lambda ersetzten (ohne shared Track!!)
    hInvMassXi_Lamda_pi_bach_prot_daugh_after = new TH1F("InvMassXi_Lamda_pi_bach_prot_daugh_after", "InvMassXi_Lamda_pi_bach_prot_daugh_after", 600, 0.700, 2.500);                        // sollte nix beinhalten, quer zusammengestztes Lambda
    // anti particles
    hInvMassAntiLambda_sanityCheck_after = new TH1F("InvariantMassANTILambdaSanityCheck_after", "Invariant Mass ANTILAMBDA Sanity Check AFTER", 400, 1.00, 1.20);                           // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassAntiLambda_pi_bach_Xi_after = new TH1F("InvariantMassANTILambdaPiBachXi_after", "Invariant Mass ANTILambda - Pi Bachelor ANTIXi AFTER", 500, 0.5, 2.5); 
    hInvMassAntiLambda_pi_daugh_Xi_after = new TH1F("InvMassANTILambda_Pi_daugh_Xi_after", "InvMassANTILambda_Pi_daugh_ANTIXi_after", 500, 0.5, 2.5);
    hInvMassAntiLambda_prot_Xi_after = new TH1F("InvMassANTILambda_Prot_Xi_after", "InvMassANTILambda_Prot_ANTIXi_after", 500, 0.5, 2.5);
    hInvMassAntiLambda_full_lambda_from_Xi_after = new TH1F("InvMassANTILambda_Full_Lambda_Xi_after", "InvMassLambda_Full_Lambda_from_Xi_after", 500, 0.5, 2.5);
    hInvMassAntiXi_sanityCheck_after = new TH1F("InvariantMassANTIXiSanityCheck_after", "Invariant_after Mass ANTIXI Sanity Check", 600, 1.200, 1.600);                                     // mit meiner funktion ausgerechnete invariante masse aus den selektierten Teilchen
    hInvMassAntiXi_AntiLamda_antipi_daugh_after = new TH1F("InvMassANTIXi_ANTILamda_pi_after", "InvMassXi_ANTILamda_pi_after", 600, 0.700, 2.500); 
    hInvMassAntiXi_AntiLamda_antiprot_daugh_after = new TH1F("InvMassANTIXi_ANTILamda_prot_after", "InvMassXi_ANTILamda_prot_after", 600, 0.700, 2.500); 
    hInvMassAntiXi_AntiLamda_antipi_bach_after = new TH1F("InvMassANTIXi_ANTILamda_pi_bach_after", "InvMassANTIXi_ANTILamda_pi_bach_after", 600, 0.700, 2.500); 
    hInvMassAntiXi_AntiLamda_full_after = new TH1F("InvMassXi_AntiLamda_full_after", "InvMassXi_AntiLamda_full_after", 600, 0.700, 2.500);                                                  // komplettes Lambda ersetzten (ohne shared Track!!)
    hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after = new TH1F("InvMassANTIXi_ANTILamda_pi_bach_prot_daugh_after", "InvMassANTIXi_ANTILamda_pi_bach_prot_daugh_after", 600, 0.700, 2.500);      // sollte nix beinhalten, quer zusammengestztes Lambda

    // Event counter for what happened how often
    fEvtCounterAfter = new TH1F("EventCounterAfter", "Event Counter After", 7, 0, 7);
    fEvtCounterAfter->GetXaxis()->SetBinLabel(1, "Prot_Lambda + pi_Xi1");        // reconstruct Lambda
    fEvtCounterAfter->GetXaxis()->SetBinLabel(2, "Prot_Lambda + pi_Xi2");        //
    fEvtCounterAfter->GetXaxis()->SetBinLabel(3, "Prot_Xi + pi_Lambda");         //
    fEvtCounterAfter->GetXaxis()->SetBinLabel(4, "Lambda + pi_Xi1");             // reconstruct Xi
    fEvtCounterAfter->GetXaxis()->SetBinLabel(5, "Lambda + pi_Xi2");             //
    fEvtCounterAfter->GetXaxis()->SetBinLabel(6, "Lambda + pi_Lambda");          //
    fEvtCounterAfter->GetXaxis()->SetBinLabel(7, "prot_Lambda + pi_Lambda");     //s reconstruct Lambda from other Lambda

    tlRecombination_after->Add(hInvMassLambda_sanityCheck_after);
    tlRecombination_after->Add(hInvMassLambda_pi_bach_Xi_after);
    tlRecombination_after->Add(hInvMassLambda_pi_daugh_Xi_after);
    tlRecombination_after->Add(hInvMassLambda_prot_Xi_after);
    tlRecombination_after->Add(hInvMassLambda_full_lambda_from_Xi_after);
    tlRecombination_after->Add(hInvMassXi_sanityCheck_after);
    tlRecombination_after->Add(hInvMassXi_Lamda_pi_daugh_after);
    tlRecombination_after->Add(hInvMassXi_Lamda_prot_daugh_after);
    tlRecombination_after->Add(hInvMassXi_Lamda_pi_bach_after);
    tlRecombination_after->Add(hInvMassXi_Lamda_full_after);
    tlRecombination_after->Add(hInvMassXi_Lamda_pi_bach_prot_daugh_after);

    tlRecombination_after->Add(hInvMassAntiLambda_sanityCheck_after);
    tlRecombination_after->Add(hInvMassAntiLambda_pi_bach_Xi_after);
    tlRecombination_after->Add(hInvMassAntiLambda_pi_daugh_Xi_after);
    tlRecombination_after->Add(hInvMassAntiLambda_prot_Xi_after);
    tlRecombination_after->Add(hInvMassAntiLambda_full_lambda_from_Xi_after);
    tlRecombination_after->Add(hInvMassAntiXi_sanityCheck_after);
    tlRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_daugh_after);
    tlRecombination_after->Add(hInvMassAntiXi_AntiLamda_antiprot_daugh_after);
    tlRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_bach_after);
    tlRecombination_after->Add(hInvMassAntiXi_AntiLamda_full_after);
    tlRecombination_after->Add(hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after);

    tlRecombination_after->Add(fEvtCounterAfter);

    // Connect Cuts to OutputContainers
    tlEventCuts             = fEventCuts->GetHistList();
    tlLambdaList            = fLambdaV0Cuts->GetQAHists();
    tlAntiLambdaList        = fAntiLambdaV0Cuts->GetQAHists();
    tlCascadeCutsXi         = fCascadeCutsXi->GetQAHists();
    tlAntiCascadeCutsXi     = fCascadeCutsAntiXi->GetQAHists();
    tlResults               = fPartColl->GetHistList();
    tlResultsQA->Add(         fPartColl->GetQAList());
    tlResultsQA->Add(         fPairCleaner->GetHistList());
    tlResultsQA->Add(         fEvent->GetEvtCutList());
    
    tlEventCuts2             = fEventCuts2->GetHistList();
    tlLambdaList2            = fLambdaV0Cuts2->GetQAHists();
    tlAntiLambdaList2        = fAntiLambdaV0Cuts2->GetQAHists();
    tlCascadeCutsXi2         = fCascadeCutsXi2->GetQAHists();
    tlAntiCascadeCutsXi2     = fCascadeCutsAntiXi2->GetQAHists();
    tlResults2               = fPartColl2->GetHistList();
    tlResultsQA2->Add(        fPartColl2->GetQAList());
    tlResultsQA2->Add(        fPairCleaner2->GetHistList());
    tlResultsQA2->Add(        fEvent->GetEvtCutList());

    PostData(1, tlEventCuts);           // cuts keeping Lambda
    PostData(2, tlLambdaList);
    PostData(3, tlAntiLambdaList);
    PostData(4, tlCascadeCutsXi);
    PostData(5, tlAntiCascadeCutsXi);
    PostData(6, tlResults);
    PostData(7, tlResultsQA);

    PostData(8, tlEventCuts2);          //  cuts keeping Xi
    PostData(9, tlLambdaList2);
    PostData(10, tlAntiLambdaList2);
    PostData(11, tlCascadeCutsXi2);
    PostData(12, tlAntiCascadeCutsXi2);
    PostData(13, tlResults2);
    PostData(14, tlResultsQA2);

    PostData(15, tlRecombination_before);         // reconstruction from daugthers histograms
    PostData(16, tlRecombination_after);

    if (fLambdaV0Cuts->GetIsMonteCarlo())
    {
        tlLambdaMC = fLambdaV0Cuts->GetMCQAHists();
        PostData(17, tlLambdaMC);
    }
    if (fAntiLambdaV0Cuts->GetIsMonteCarlo())
    {
        tlAntiLambdaMC = fAntiLambdaV0Cuts->GetMCQAHists();
        PostData(18, tlAntiLambdaMC);
    }
}         


void AliAnalysisTaskPOmegaPenne::UserExec(Option_t *)
{
    // VEvent = dynamic_cast<AliVEvent *>(fInputEvent);
    VEvent = fInputEvent;
    
    if (!fInputEvent)
    {
        AliWarning("No Input VEvent");
        return;
    }

    fEvent->SetEvent(fInputEvent);
    if (fEventCuts->isSelected(fEvent))
    {
        ResetGlobalTrackReference();
        for (int iTrack = 0; iTrack < fInputEvent->GetNumberOfTracks(); ++iTrack)
        {
            VTrack = dynamic_cast<AliVTrack *>(fInputEvent->GetTrack(iTrack));
            if (!VTrack)
            {
                AliFatal("No Standard AOD");
                return;
            }
            StoreGlobalTrackReference(VTrack);
        }
        
        int counter = 0;

        std::vector<AliFemtoDreamBasePart> vLambda;         // keep Xi after OPairCleaner
        std::vector<AliFemtoDreamBasePart> vAntiLambda;
        std::vector<AliFemtoDreamBasePart> vXi;
        std::vector<AliFemtoDreamBasePart> vAntiXi;
        std::vector<AliFemtoDreamBasePart> vLambda2;        // keep Lambda after OPairCleaner
        std::vector<AliFemtoDreamBasePart> vAntiLambda2;
        std::vector<AliFemtoDreamBasePart> vXi2;
        std::vector<AliFemtoDreamBasePart> vAntiXi2;

    
        // irgendwie benötigt um GetV0s() und GetCascade() zu holen
        AliAODEvent *aodEvent = dynamic_cast<AliAODEvent *>(fInputEvent); // caste input event auf ein AODEvent

        //###########################################
        // Particle Selections
        //###########################################
        // ## Lambda Selection ## keep Lambdas
        fv0->SetGlobalTrackInfo(fGTI, fTrackBufferSize);
        fv0_2->SetGlobalTrackInfo(fGTI, fTrackBufferSize);

        for (int iv0 = 0; iv0 < dynamic_cast<TClonesArray *>(aodEvent->GetV0s())->GetEntriesFast(); ++iv0)
        {
            AliAODv0 *v0 = aodEvent->GetV0(iv0);
            fv0_2->Setv0(fInputEvent, v0, fEvent->GetMultiplicity());

            // ## Lambda Selection 1 ## keep Xi
            if (fLambdaV0Cuts2->isSelected(fv0_2))
            {
                vLambda2.push_back(*fv0_2);
                vLambda2[vLambda2.size() - 1].SetCPA(0.5);
            }
            if (fAntiLambdaV0Cuts2->isSelected(fv0_2))
            {
                vAntiLambda2.push_back(*fv0_2);
                vAntiLambda2[vAntiLambda2.size() - 1].SetCPA(0.5);
            }

            fv0->Setv0(fInputEvent, v0, fEvent->GetMultiplicity());
            // ## Lambda Selection 2 ## keep Lambda
            if (fLambdaV0Cuts->isSelected(fv0))
            {
                vLambda.push_back(*fv0);
                vLambda[vLambda.size() - 1].SetCPA(1.0);
            }
            if (fAntiLambdaV0Cuts->isSelected(fv0))
            {
                vAntiLambda.push_back(*fv0);
                vAntiLambda[vAntiLambda.size() - 1].SetCPA(1.0);
            }
        }
        // ## Xi selection
        for (int iCasc = 0; iCasc < dynamic_cast<TClonesArray *>(aodEvent->GetCascades())->GetEntriesFast(); ++iCasc)
        {
            AliAODcascade *casc = aodEvent->GetCascade(iCasc);
            fCascade2->SetCascade(fInputEvent, casc);

            // ## Xi selection 1 ### keep Xi
            if (fCascadeCutsXi2->isSelected(fCascade2))
            {
                vXi.push_back(*fCascade2);
                vXi[vXi.size() - 1].SetCPA(1.0);
            }
            if (fCascadeCutsAntiXi2->isSelected(fCascade2))
            {
                vAntiXi.push_back(*fCascade2);
                vAntiXi[vAntiXi.size() - 1].SetCPA(1.0);
            }

            fCascade->SetCascade(fInputEvent, casc);
            // ## Xi selection 2 ### keep Lambda
            if (fCascadeCutsXi->isSelected(fCascade))
            {
                vXi.push_back(*fCascade);
                vXi[vXi.size() - 1].SetCPA(0.5);
            }
            if (fCascadeCutsAntiXi->isSelected(fCascade))
            {
                vAntiXi.push_back(*fCascade);
                vAntiXi[vAntiXi.size() - 1].SetCPA(0.5);
            }
        }

        // initialize Vectors even when bIsMixing is false - compiler complains since they are used in two If statements
        std::vector<AliFemtoDreamBasePart> vLambda_recomb(0);
        std::vector<AliFemtoDreamBasePart> tmpLambda_recomb(0); // recombination Vector for the loop
        std::vector<AliFemtoDreamBasePart> tmpXi_recomb(0);     // temporary recombination vector to calculate new invMasses
        if (bIsMixing)
        {
            for (auto it : vLambda)
            {
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassLambda_sanityCheck_before->Fill(CalculateInvMassLambda(momP, 211, momN, 2212));
            }
            for (auto it : vAntiLambda)
            {
                TVector3 momN = it.GetMomentum(1);
                TVector3 momP = it.GetMomentum(2);
                hInvMassAntiLambda_sanityCheck_before->Fill(CalculateInvMassLambda(momN, 2212, momP, 211));
            }
            for (auto it : vXi)
            {
                TVector3 momB = it.GetMomentum(3);
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassXi_sanityCheck_before->Fill(CalculateInvMassXi(momB, 211, momP, 2212, momN, 211));
            }
            for (auto it : vAntiXi)
            {
                TVector3 momB = it.GetMomentum(3);
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassAntiXi_sanityCheck_before->Fill(CalculateInvMassXi(momB, 211, momP, 211, momN, 2212));
            }
            //###########################################
            // Lambda - Lambda recombinations
            //###########################################
            
            // ein lambda mit allen höheren kombinieren (siehe zweite schleife)
            for (size_t iterLamb = 0; iterLamb + 1 < vLambda.size(); iterLamb++) // schleife läuft nur bis zum vorletzten lambda
            {
                if (vLambda.size() == 1)
                    break; // abbrechen wenn Lambda nur ein Teilchen enthält 

                // recombiniere lambda[iterLamb] mit den darauf folgenden Lambdas
                // - dadurch werden nicht doppelt Lambdas aber im moment noch doppelt Tracks wenn sie sich zwei Lambdas teilen
                // tausche nur den Impuls der für die invariante Masse benötigt wird
                //
                // GetMomentum(0) - Lambda
                // GetMomentum(1) - Pion
                // GetMomentum(2) - Proton

                for (size_t iterUpwards = iterLamb + 1; iterUpwards < vLambda.size(); iterUpwards++)
                {
                    tmpLambda_recomb.clear();
                    // check for shared tracks
                    if (vLambda[iterLamb].GetIDTracks().size() < 2 || vLambda[iterUpwards].GetIDTracks().size() < 2)
                    {
                        continue; // failsafe if the Lambda has no 2 tracks
                    }

                    if (vLambda[iterLamb].GetIDTracks()[0] == vLambda[iterUpwards].GetIDTracks()[0]) // ## shared Pion
                    {
                        tmpLambda_recomb.push_back(vLambda[iterLamb]);
                        tmpLambda_recomb[0].SetMomentum(2, vLambda[iterUpwards].GetMomentum(2));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassLambda_shared_pion_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                           211,
                                                                                           vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                           2212));
                            hInvMassLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                     211,
                                                                                     vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                     2212));
                        }
                    }
                    else if (vLambda[iterLamb].GetIDTracks()[1] == vLambda[iterUpwards].GetIDTracks()[1]) // ## shared Proton
                    {
                        tmpLambda_recomb.push_back(vLambda[iterLamb]);
                        tmpLambda_recomb[0].SetMomentum(1, vLambda[iterUpwards].GetMomentum(1));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassLambda_shared_proton_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                             211,
                                                                                             vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                             2212));
                            hInvMassLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                     211,
                                                                                     vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                     2212));
                        }
                    }
                    else
                    {
                        // save recombination lambda twice for each for manipulation of each track
                        tmpLambda_recomb.push_back(vLambda[iterLamb]);
                        tmpLambda_recomb.push_back(vLambda[iterLamb]);
                        // take next lambdas (iterUpwards) and manipulate the two lambdas before
                        tmpLambda_recomb[0].SetMomentum(1, vLambda[iterUpwards].GetMomentum(1));
                        tmpLambda_recomb[1].SetMomentum(2, vLambda[iterUpwards].GetMomentum(2));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        vLambda_recomb.push_back(tmpLambda_recomb[1]);
                        fEvtCounterBefore->Fill(6);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                     211,
                                                                                     vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                     2212));
                        }
                    }
                }
            }

            vLambda_recomb.clear();

            //###########################################
            // Lambda - Xi recombinations
            //##########################################

            for (size_t iterLamb = 0; iterLamb < vLambda.size(); iterLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
            {
                if (!vLambda.size() || !vXi.size())
                    break; // abbrechen wenn lambda oder Xi leer ist/sind

                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                if (vLambda[iterLamb].GetIDTracks().size() < 2)
                {
                    continue; // failsafe if the Lambda has no 2 tracks
                }

                // recombiniere vLambda[iterLamb] mit jeder Tochter der Xi's
                // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
                // ## XI
                // GetMomentum(0) - Xi
                // GetMomentum(1) - Pi-Daughter
                // GetMomentum(2) - Proton-Daughter
                // GetMomentum(3) - Pi-Bachelor
                // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                // [2] - Bachelor
                for (size_t iterXi = 0; iterXi < vXi.size(); iterXi++)
                {
                    if (vXi[iterXi].GetMomenta().size() < 4)
                    {
                        continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                    }
                    // reset temporary recombination vectors
                    tmpLambda_recomb.clear();
                    tmpXi_recomb.clear();

                    // safe recombination lambda three times for each following lambda
                    // - for all combinations - Xi_1pi-Lambda_prot ; Xi_2pi-Lambda_prot ; Xi_prot-Lambda_pi
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);

                    if (tmpLambda_recomb.size() >= 3 && vXi[iterXi].GetMomenta().size() >= 3)
                    {
                        // take Xi's constituents and manipulate the three lambdas before
                        tmpLambda_recomb[0].SetMomentum(1, vXi[iterXi].GetMomentum(0)); // Bachelor Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[1].SetMomentum(1, vXi[iterXi].GetMomentum(2)); // Daughter Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[2].SetMomentum(2, vXi[iterXi].GetMomentum(3)); // Daughter Xi-Proton mit Lambda-Pion
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        vLambda_recomb.push_back(tmpLambda_recomb[1]);
                        vLambda_recomb.push_back(tmpLambda_recomb[2]);
                    }
                    // ## Xi pairing
                    if (vXi[iterXi].GetIDTracks()[2] == vLambda[iterLamb].GetIDTracks()[0]) // ## ## Bachelor shared ## ##
                    {
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                        tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        tmpXi_recomb[2].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set full Lambda
                        tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set full Lambda

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            float invMassToStore = CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                      tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                      tmpXi_recomb[j].GetMomentum(1), 211);
                            hInvMassXi_shared_bach_before->Fill(invMassToStore);
                            hInvMassXi_total_before->Fill(invMassToStore);
                        }
                    }
                    else if (vXi[iterXi].GetIDTracks()[0] == vLambda[iterLamb].GetIDTracks()[0]) // ## ## pion daughter shared ## ##
                    {
                        if (vXi[iterXi].GetIDTracks()[1] == vLambda[iterLamb].GetIDTracks()[1]) // ## ## and daughter proton shared -> full lambda shared ## ##
                        {
                            tmpXi_recomb.push_back(vXi[iterXi]);
                            tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set only Bachelor

                            hInvMassXi_shared_Lambda_before->Fill(CalculateInvMassXi(tmpXi_recomb[0].GetMomentum(3), 211,
                                                                                     tmpXi_recomb[0].GetMomentum(2), 2212,
                                                                                     tmpXi_recomb[0].GetMomentum(1), 211));
                        }
                        else // ## ## only daughter pion shared ## ##
                        {
                            tmpXi_recomb.push_back(vXi[iterXi]);
                            tmpXi_recomb.push_back(vXi[iterXi]);
                            tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                            tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter

                            for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                            {
                                float invMassToStore = CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                          tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                          tmpXi_recomb[j].GetMomentum(1), 211);

                                hInvMassXi_shared_pi_daugh_before->Fill(invMassToStore);
                                hInvMassXi_total_before->Fill(invMassToStore);
                            }
                        }
                    }
                    else if (vXi[iterXi].GetIDTracks()[1] == vLambda[iterLamb].GetIDTracks()[1] && vXi[iterXi].GetIDTracks()[0] != vLambda[iterLamb].GetIDTracks()[0]) // ## ## only daughter proton shared ## ##
                    {
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb.push_back(vXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            hInvMassXi_shared_prot_daugh_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                                         tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                                         tmpXi_recomb[j].GetMomentum(1), 211));
                            hInvMassXi_total_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                             tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                             tmpXi_recomb[j].GetMomentum(1), 211));
                        }
                    }
                    else // ## ## nothing shared ## ##
                    {
                        // get the Xi and manipulate the Bachelor and Daughters
                        for (int j = 0; j < 4; j++)
                        {
                            tmpXi_recomb.push_back(vXi[iterXi]);
                        }

                        tmpXi_recomb[0].SetMomentum(3, vLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                        tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        tmpXi_recomb[3].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // set full Lambda
                        tmpXi_recomb[3].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // set full Lambda

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            hInvMassXi_nothing_shared->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                               tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                               tmpXi_recomb[j].GetMomentum(1), 211));
                            hInvMassXi_total_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                             tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                             tmpXi_recomb[j].GetMomentum(1), 211));
                        }
                    }
                }
            }
            vLambda_recomb.clear();

            //###########################################
            // ANTI Lambda - ANTI Lambda recombinations
            //###########################################
            tmpLambda_recomb.clear();

            // ein lambda mit allen höheren kombinieren (siehe zweite schleife)
            for (size_t iterLamb = 0; iterLamb + 1 < vAntiLambda.size(); iterLamb++) // schleife läuft nur bis zum vorletzten lambda
            {
                if (vAntiLambda.size() == 1)
                    break; // abbrechen wenn Lambda nur ein Teilchen enthält oder

                // recombiniere lambda[iterLamb] mit den darauf folgenden Lambdas
                // - dadurch werden nicht doppelt Lambdas aber im moment noch doppelt Tracks wenn sie sich zwei Lambdas teilen
                // tausche nur den Impuls der für die invariante Masse benötigt wird
                //
                // GetMomentum(0) - Lambda
                // GetMomentum(1) - Pion
                // GetMomentum(2) - Proton

                for (size_t iterUpwards = iterLamb + 1; iterUpwards < vAntiLambda.size(); iterUpwards++)
                {
                    tmpLambda_recomb.clear();
                    // check for shared tracks
                    if (vAntiLambda[iterLamb].GetIDTracks().size() < 2 || vAntiLambda[iterUpwards].GetIDTracks().size() < 2)
                    {
                        continue; // failsafe if the Lambda has no 2 tracks
                    }

                    if (vAntiLambda[iterLamb].GetIDTracks()[0] == vAntiLambda[iterUpwards].GetIDTracks()[0]) // ## shared Pion
                    {
                        tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                        tmpLambda_recomb[0].SetMomentum(2, vAntiLambda[iterUpwards].GetMomentum(2));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassAntiLambda_shared_pion_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                               211,
                                                                                               vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                               2212));
                            hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                         211,
                                                                                         vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                         2212));
                        }
                    }
                    else if (vAntiLambda[iterLamb].GetIDTracks()[1] == vAntiLambda[iterUpwards].GetIDTracks()[1]) // ## shared Proton
                    {
                        tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                        tmpLambda_recomb[0].SetMomentum(1, vAntiLambda[iterUpwards].GetMomentum(1));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassAntiLambda_shared_proton_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                                 211,
                                                                                                 vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                                 2212));
                            hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                         211,
                                                                                         vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                         2212));
                        }
                    }
                    else
                    {
                        // save recombination lambda twice for each for manipulation of each track
                        tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                        tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                        // take next lambdas (iterUpwards) and manipulate the two lambdas before
                        tmpLambda_recomb[0].SetMomentum(1, vAntiLambda[iterUpwards].GetMomentum(1));
                        tmpLambda_recomb[1].SetMomentum(2, vAntiLambda[iterUpwards].GetMomentum(2));
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        vLambda_recomb.push_back(tmpLambda_recomb[1]);
                        fEvtCounterBefore->Fill(6);
                        fEvtCounterBefore->Fill(6);
                        for (size_t iterLamb_recomb = 0; iterLamb_recomb < vLambda_recomb.size(); iterLamb_recomb++)
                        {
                            hInvMassAntiLambda_total_before->Fill(CalculateInvMassLambda(vLambda_recomb[iterLamb_recomb].GetMomentum(1),
                                                                                         211,
                                                                                         vLambda_recomb[iterLamb_recomb].GetMomentum(2),
                                                                                         2212));
                        }
                    }
                }
            }

            vLambda_recomb.clear();

            //###########################################
            // ANTI Lambda - ANTI Xi recombinations
            //##########################################

            for (size_t iterLamb = 0; iterLamb < vAntiLambda.size(); iterLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
            {
                if (!vAntiLambda.size() || !vAntiXi.size())
                    break; // abbrechen wenn lambda oder Xi leer ist/sind

                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                if (vAntiLambda[iterLamb].GetIDTracks().size() < 2)
                {
                    continue; // failsafe if the Lambda has no 2 tracks
                }

                // recombiniere vAntiLambda[iterLamb] mit jeder Tochter der Xi's
                // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
                // ## XI
                // GetMomentum(0) - Xi
                // GetMomentum(1) - Pi-Daughter
                // GetMomentum(2) - Proton-Daughter
                // GetMomentum(3) - Pi-Bachelor
                // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                // [2] - Bachelor
                for (size_t iterXi = 0; iterXi < vAntiXi.size(); iterXi++)
                {
                    if (vAntiXi[iterXi].GetMomenta().size() < 4)
                    {
                        continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                    }
                    // reset temporary recombination vectors
                    tmpLambda_recomb.clear();
                    tmpXi_recomb.clear();

                    // safe recombination lambda three times for each following lambda
                    // - for all combinations - Xi_1pi-Lambda_prot ; Xi_2pi-Lambda_prot ; Xi_prot-Lambda_pi
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vAntiLambda[iterLamb]);

                    if (tmpLambda_recomb.size() >= 3 && vAntiXi[iterXi].GetMomenta().size() >= 3)
                    {
                        // take Xi's constituents and manipulate the three lambdas before
                        tmpLambda_recomb[0].SetMomentum(1, vAntiXi[iterXi].GetMomentum(0)); // Bachelor Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[1].SetMomentum(1, vAntiXi[iterXi].GetMomentum(2)); // Daughter Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[2].SetMomentum(2, vAntiXi[iterXi].GetMomentum(3)); // Daughter Xi-Proton mit Lambda-Pion
                        vLambda_recomb.push_back(tmpLambda_recomb[0]);
                        vLambda_recomb.push_back(tmpLambda_recomb[1]);
                        vLambda_recomb.push_back(tmpLambda_recomb[2]);
                    }
                    // ## Xi pairing
                    if (vAntiXi[iterXi].GetIDTracks()[2] == vAntiLambda[iterLamb].GetIDTracks()[0]) // ## ## Bachelor shared ## ##
                    {
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                        tmpXi_recomb[1].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        tmpXi_recomb[2].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set full Lambda
                        tmpXi_recomb[2].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set full Lambda

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            float invMassToStore = CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                      tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                      tmpXi_recomb[j].GetMomentum(1), 211);
                            hInvMassAntiXi_shared_bach_before->Fill(invMassToStore);
                            hInvMassAntiXi_total_before->Fill(invMassToStore);
                        }
                    }
                    else if (vAntiXi[iterXi].GetIDTracks()[0] == vAntiLambda[iterLamb].GetIDTracks()[0]) // ## ## pion daughter shared ## ##
                    {
                        if (vAntiXi[iterXi].GetIDTracks()[1] == vAntiLambda[iterLamb].GetIDTracks()[1]) // ## ## and daughter proton shared -> full lambda shared ## ##
                        {
                            tmpXi_recomb.push_back(vAntiXi[iterXi]);
                            tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set only Bachelor

                            hInvMassAntiXi_shared_Lambda_before->Fill(CalculateInvMassXi(tmpXi_recomb[0].GetMomentum(3), 211,
                                                                                         tmpXi_recomb[0].GetMomentum(2), 2212,
                                                                                         tmpXi_recomb[0].GetMomentum(1), 211));
                        }
                        else // ## ## only daughter pion shared ## ##
                        {
                            tmpXi_recomb.push_back(vAntiXi[iterXi]);
                            tmpXi_recomb.push_back(vAntiXi[iterXi]);
                            tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                            tmpXi_recomb[1].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter

                            for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                            {
                                float invMassToStore = CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                          tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                          tmpXi_recomb[j].GetMomentum(1), 211);

                                hInvMassAntiXi_shared_pi_daugh_before->Fill(invMassToStore);
                                hInvMassAntiXi_total_before->Fill(invMassToStore);
                            }
                        }
                    }
                    else if (vAntiXi[iterXi].GetIDTracks()[1] == vAntiLambda[iterLamb].GetIDTracks()[1] && vAntiXi[iterXi].GetIDTracks()[0] != vAntiLambda[iterLamb].GetIDTracks()[0]) // ## ## only daughter proton shared ## ##
                    {
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            hInvMassAntiXi_shared_prot_daugh_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                                             tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                                             tmpXi_recomb[j].GetMomentum(1), 211));
                            hInvMassAntiXi_total_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                                 tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                                 tmpXi_recomb[j].GetMomentum(1), 211));
                        }
                    }
                    else // ## ## nothing shared ## ##
                    {
                        // get the Xi and manipulate the Bachelor and Daughters
                        for (int j = 0; j < 4; j++)
                        {
                            tmpXi_recomb.push_back(vAntiXi[iterXi]);
                        }

                        tmpXi_recomb[0].SetMomentum(3, vAntiLambda[iterLamb].GetMomentum(1)); // set Bachelor
                        tmpXi_recomb[1].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set Pi-Daughter
                        tmpXi_recomb[2].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set Proton-Daughter
                        tmpXi_recomb[3].SetMomentum(1, vAntiLambda[iterLamb].GetMomentum(1)); // set full Lambda
                        tmpXi_recomb[3].SetMomentum(2, vAntiLambda[iterLamb].GetMomentum(2)); // set full Lambda

                        for (size_t j = 0; j < tmpXi_recomb.size(); j++)
                        {
                            hInvMassAntiXi_nothing_shared->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                                   tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                                   tmpXi_recomb[j].GetMomentum(1), 211));
                            hInvMassAntiXi_total_before->Fill(CalculateInvMassXi(tmpXi_recomb[j].GetMomentum(3), 211,
                                                                                 tmpXi_recomb[j].GetMomentum(2), 2212,
                                                                                 tmpXi_recomb[j].GetMomentum(1), 211));
                        }
                    }
                }
            }
            vLambda_recomb.clear();
        }
        //###########################################
        // Cleanup and Postdata
        //##########################################

        // remove double-matched tracks
        fPairCleaner ->ResetArray();
        fPairCleaner2->ResetArray();

        if(!bPCinvMass)
        {
            // #1 Normal PairCleaner
            fPairCleaner->CleanDecayAndDecay(&vXi, &vLambda, 0);
            fPairCleaner->CleanDecayAndDecay(&vAntiXi, &vAntiLambda, 1);
            fPairCleaner->CleanDecay(&vLambda, 2);
            fPairCleaner->CleanDecay(&vAntiLambda, 3);

            fPairCleaner->CleanDecay(&vXi, 0);
            fPairCleaner->CleanDecay(&vAntiXi, 1);
        }
        if(bPCinvMass)
        {
            // #1   Invariant Mass Paircleaner
            CleanDecayXi(&vXi);

            // yet normal
            fPairCleaner->CleanDecayAndDecay(&vXi, &vLambda, 0);
            fPairCleaner->CleanDecayAndDecay(&vAntiXi, &vAntiLambda, 1);
            fPairCleaner->CleanDecay(&vLambda, 2);
            fPairCleaner->CleanDecay(&vAntiLambda, 3);

            fPairCleaner->CleanDecay(&vAntiXi, 1);
        }
        
        fPairCleaner->StoreParticle(vLambda);
        fPairCleaner->StoreParticle(vAntiLambda);
        fPairCleaner->StoreParticle(vXi);
        fPairCleaner->StoreParticle(vAntiXi);

        if (!bPCinvMass)
        {
            // #2
            fPairCleaner2->CleanDecayAndDecay(&vXi2, &vLambda2, 0);
            fPairCleaner2->CleanDecayAndDecay(&vAntiXi2, &vAntiLambda2, 1);
            fPairCleaner2->CleanDecay(&vLambda2, 2);
            fPairCleaner2->CleanDecay(&vAntiLambda2, 3);
        }
        fPairCleaner2->StoreParticle(vLambda2);
        fPairCleaner2->StoreParticle(vAntiLambda2);
        fPairCleaner2->StoreParticle(vXi2);
        fPairCleaner2->StoreParticle(vAntiXi2);

        fPartColl->SetEvent(fPairCleaner->GetCleanParticles(), fEvent->GetZVertex(), fEvent->GetRefMult08(), fEvent->GetV0MCentrality()); 
        fPartColl2->SetEvent(fPairCleaner2->GetCleanParticles(), fEvent->GetZVertex(), fEvent->GetRefMult08(), fEvent->GetV0MCentrality()); 
        // soweit ich das richtig verstanden habe wird pairQA mit den teilchen gemacht die im pairCleaner
        // sind und pdgCodes in der richtigen Reihenfolge vorhanden sind.


        // std::cout << "dimensions of cleanParticles: " << fPairCleaner->GetCleanParticles().size() << "x" << fPairCleaner->GetCleanParticles()[0].size() << std::endl;        ### makes particleTypeXparticleNumber
        // if(fPairCleaner->GetCleanParticles()[0].size() || fPairCleaner->GetCleanParticles()[1].size() || fPairCleaner->GetCleanParticles()[2].size() || fPairCleaner->GetCleanParticles()[3].size())
        // {
        //     std::cout << "### New EVENT ###" << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[0].size()==0) std::cout << "Lambdas: " << fPairCleaner->GetCleanParticles()[0].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[1].size()==0)std::cout << "AntiLambdas: " << fPairCleaner->GetCleanParticles()[1].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[2].size()==0)std::cout << "Xi: " << fPairCleaner->GetCleanParticles()[2].size() << std::endl;
        //     if(!fPairCleaner->GetCleanParticles()[3].size()==0)std::cout << "AntiXi: " << fPairCleaner->GetCleanParticles()[3].size() << std::endl;
        // }
        // if(vLambda.size() > 0 && vXi.size() > 0)
        // {
        //     std::cout << "after paircleaner vLambda und vXi größe: " << vLambda.size() << " und " << vXi.size() << std::endl;
        // }

        if (bIsMixing)
        {
            //###########################################
            // Lambda - Xi recombinations
            //#########################################
            for (size_t iterLamb = 0; iterLamb < vLambda.size(); iterLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
            {
                if (!vLambda.size() || !vXi.size()) // abbrechen wenn lambda oder Xi leer ist/sind
                {
                    break;
                }

                if (!vLambda[iterLamb].UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }

                // recombiniere vLambda[iterLamb] mit jeder Tochter der Xi's
                // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
                // ## XI
                // GetMomentum(0) - Xi
                // GetMomentum(1) - Pi-Daughter
                // GetMomentum(2) - Proton-Daughter
                // GetMomentum(3) - Pi-Bachelor
                // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                // [2] - Bachelor
                for (size_t iterXi = 0; iterXi < vXi.size(); iterXi++)
                {
                    if (!vXi[iterXi].UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                    {
                        continue;
                    }
                    if (vXi[iterXi].GetMomenta().size() < 4)
                    {
                        continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                    }
                    // reset temporary recombination vectors
                    tmpLambda_recomb.clear();
                    tmpXi_recomb.clear();

                    // ## Lambda pairing
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);
                    tmpLambda_recomb.push_back(vLambda[iterLamb]);

                    if (tmpLambda_recomb.size() >= 3 && vXi[iterXi].GetMomenta().size() >= 3)
                    {
                        // take Xi's constituents and manipulate the three lambdas before
                        tmpLambda_recomb[0].SetMomentum(1, vXi[iterXi].GetMomentum(0)); // [0] Bachelor Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[1].SetMomentum(1, vXi[iterXi].GetMomentum(2)); // [1] Daughter Xi-Pion mit Lambda-Proton
                        tmpLambda_recomb[2].SetMomentum(2, vXi[iterXi].GetMomentum(3)); // [2] Daughter Xi-Proton mit Lambda-Pion

                        hInvMassLambda_pi_bach_Xi_after ->Fill(CalculateInvMassLambda(tmpLambda_recomb[0].GetMomentum(1), 211, tmpLambda_recomb[0].GetMomentum(2), 2212));
                        hInvMassLambda_pi_daugh_Xi_after->Fill(CalculateInvMassLambda(tmpLambda_recomb[1].GetMomentum(1), 211, tmpLambda_recomb[1].GetMomentum(2), 2212));
                        hInvMassLambda_prot_Xi_after    ->Fill(CalculateInvMassLambda(tmpLambda_recomb[2].GetMomentum(1), 211, tmpLambda_recomb[2].GetMomentum(2), 2212));
                    }

                    // ## Xi pairing ###################################### Xi STARTS HERE ################
                    for (size_t mixCombinations = 0; mixCombinations < 5; mixCombinations++)
                    {
                        tmpXi_recomb.push_back(vXi[iterXi]);
                    }
                    if (tmpXi_recomb.size() > 4)
                    {
                        tmpXi_recomb[0].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // [0] set Pi-Daughter
                        tmpXi_recomb[1].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [1] set Proton-Daughter
                        tmpXi_recomb[2].SetMomentum(1, vLambda[iterLamb].GetMomentum(1)); // [2] set full Lambda
                        tmpXi_recomb[2].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [2] set full Lambda
                        tmpXi_recomb[3].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [3] set Pi-Bachelor
                        tmpXi_recomb[4].SetMomentum(2, vLambda[iterLamb].GetMomentum(2)); // [4] set Pi-Bachelor and Proton-Daughter

                        hInvMassXi_Lamda_pi_daugh_after          ->Fill(CalculateInvMassXi(tmpXi_recomb[0].GetMomentum(3), 211, tmpXi_recomb[0].GetMomentum(2), 2212, tmpXi_recomb[0].GetMomentum(1), 211));
                        hInvMassXi_Lamda_prot_daugh_after        ->Fill(CalculateInvMassXi(tmpXi_recomb[1].GetMomentum(3), 211, tmpXi_recomb[1].GetMomentum(2), 2212, tmpXi_recomb[1].GetMomentum(1), 211));
                        hInvMassXi_Lamda_full_after              ->Fill(CalculateInvMassXi(tmpXi_recomb[2].GetMomentum(3), 211, tmpXi_recomb[2].GetMomentum(2), 2212, tmpXi_recomb[2].GetMomentum(1), 211));
                        hInvMassXi_Lamda_pi_bach_after           ->Fill(CalculateInvMassXi(tmpXi_recomb[3].GetMomentum(3), 211, tmpXi_recomb[3].GetMomentum(2), 2212, tmpXi_recomb[3].GetMomentum(1), 211));
                        hInvMassXi_Lamda_pi_bach_prot_daugh_after->Fill(CalculateInvMassXi(tmpXi_recomb[4].GetMomentum(3), 211, tmpXi_recomb[4].GetMomentum(2), 2212, tmpXi_recomb[4].GetMomentum(1), 211));
                    }
                }
            }

            //###########################################
            // Anti-Lambda - Anti-Xi recombinations
            //#########################################
            std::vector<AliFemtoDreamBasePart> tmpAntiLambda_recomb(0); // recombination Vector for the loop
            std::vector<AliFemtoDreamBasePart> tmpAntiXi_recomb(0);     // temporary recombination vector to calculate new invMasses

            for (size_t iterAntiLamb = 0; iterAntiLamb < vAntiLambda.size(); iterAntiLamb++) // ein lambda mit allen Xi's kombinieren (siehe zweite schleife)
            {
                if (!vAntiLambda.size() || !vAntiXi.size()) // abbrechen wenn lambda oder Xi leer ist/sind
                {
                    break;
                }

                if (!vAntiLambda[iterAntiLamb].UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }

                // recombiniere vAntiLambda[iterAntiLamb] mit jeder Tochter der Xi's
                // - nur Impuls manipulation damit invariante Masse ausgerechnet werden kann
                // ## XI
                // GetMomentum(0) - Xi
                // GetMomentum(1) - Pi-Daughter
                // GetMomentum(2) - Proton-Daughter
                // GetMomentum(3) - Pi-Bachelor
                // Hinweis>>Cascade initialisiert AliFemtoBasePart.fP mit 4. d.h. es sollte sich beim Impulsvektor um alle Zerfallsprodukte handeln
                // GetIDTracks()
                // [0] - negativeDaughter
                // [1] - positiveDaughter
                // [2] - Bachelor
                for (size_t iterAntiXi = 0; iterAntiXi < vAntiXi.size(); iterAntiXi++)
                {
                    if (!vAntiXi[iterAntiXi].UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                    {
                        continue;
                    }
                    if (vAntiXi[iterAntiXi].GetMomenta().size() < 4)
                    {
                        continue; // failsafe, falls gespeichertes Xi keine 4 Momenta besitzt
                    }
                    // reset temporary recombination vectors
                    tmpAntiLambda_recomb.clear();
                    tmpAntiXi_recomb.clear();

                    // ## Anti-Lambda pairing
                    for (size_t antiLambdaSize = 0; antiLambdaSize < 4; antiLambdaSize++)
                    {
                        tmpAntiLambda_recomb.push_back(vAntiLambda[iterAntiLamb]);
                    }

                    if (tmpAntiLambda_recomb.size() >= 4 && vAntiXi[iterAntiXi].GetMomenta().size() >= 3)
                    {
                        // take Xi's constituents and manipulate the three lambdas before
                        tmpAntiLambda_recomb[0].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(0)); // [0] Bachelor Xi-Pion mit Lambda-Proton
                        tmpAntiLambda_recomb[1].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(2)); // [1] Daughter Xi-Pion mit Lambda-Proton
                        tmpAntiLambda_recomb[2].SetMomentum(2, vAntiXi[iterAntiXi].GetMomentum(3)); // [2] Daughter Xi-Proton mit Lambda-Pion
                        tmpAntiLambda_recomb[3].SetMomentum(1, vAntiXi[iterAntiXi].GetMomentum(2)); // [3] Full Lambda from Xi sharing
                        tmpAntiLambda_recomb[3].SetMomentum(2, vAntiXi[iterAntiXi].GetMomentum(3)); // [3] Full Lambda from Xi sharing

                        hInvMassAntiLambda_pi_bach_Xi_after->Fill(CalculateInvMassLambda(tmpAntiLambda_recomb[0].GetMomentum(1), 2212, tmpAntiLambda_recomb[0].GetMomentum(2), 211));
                        hInvMassAntiLambda_pi_daugh_Xi_after->Fill(CalculateInvMassLambda(tmpAntiLambda_recomb[1].GetMomentum(1), 2212, tmpAntiLambda_recomb[1].GetMomentum(2), 211));
                        hInvMassAntiLambda_prot_Xi_after->Fill(CalculateInvMassLambda(tmpAntiLambda_recomb[2].GetMomentum(1), 2212, tmpAntiLambda_recomb[2].GetMomentum(2), 211));
                        hInvMassAntiLambda_full_lambda_from_Xi_after->Fill(CalculateInvMassLambda(tmpAntiLambda_recomb[3].GetMomentum(1), 2212, tmpAntiLambda_recomb[3].GetMomentum(2), 211));
                    }

                    // ## Anti-Xi pairing ###################################### Anti-Xi STARTS HERE ################
                    for (size_t mixCombinations = 0; mixCombinations < 5; mixCombinations++)
                    {
                        tmpAntiXi_recomb.push_back(vAntiXi[iterAntiXi]);
                    }
                    if (tmpAntiXi_recomb.size() > 4)
                    {
                        tmpAntiXi_recomb[0].SetMomentum(1, vAntiLambda[iterAntiLamb].GetMomentum(1)); // [0] set Pi-Daughter
                        tmpAntiXi_recomb[1].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [1] set Proton-Daughter
                        tmpAntiXi_recomb[2].SetMomentum(1, vAntiLambda[iterAntiLamb].GetMomentum(1)); // [2] set full Lambda
                        tmpAntiXi_recomb[2].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [2] set full Lambda
                        tmpAntiXi_recomb[3].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [3] set Pi-Bachelor
                        tmpAntiXi_recomb[4].SetMomentum(2, vAntiLambda[iterAntiLamb].GetMomentum(2)); // [4] set Pi-Bachelor and Proton-Daughter

                        hInvMassAntiXi_AntiLamda_antipi_daugh_after              ->Fill(CalculateInvMassXi(tmpAntiXi_recomb[0].GetMomentum(3), 211, tmpAntiXi_recomb[0].GetMomentum(2), 211, tmpAntiXi_recomb[0].GetMomentum(1), 2212));
                        hInvMassAntiXi_AntiLamda_antiprot_daugh_after            ->Fill(CalculateInvMassXi(tmpAntiXi_recomb[1].GetMomentum(3), 211, tmpAntiXi_recomb[1].GetMomentum(2), 211, tmpAntiXi_recomb[1].GetMomentum(1), 2212));
                        hInvMassAntiXi_AntiLamda_full_after                      ->Fill(CalculateInvMassXi(tmpAntiXi_recomb[2].GetMomentum(3), 211, tmpAntiXi_recomb[2].GetMomentum(2), 211, tmpAntiXi_recomb[2].GetMomentum(1), 2212));
                        hInvMassAntiXi_AntiLamda_antipi_bach_after               ->Fill(CalculateInvMassXi(tmpAntiXi_recomb[3].GetMomentum(3), 211, tmpAntiXi_recomb[3].GetMomentum(2), 211, tmpAntiXi_recomb[3].GetMomentum(1), 2212));
                        hInvMassAntiXi_AntiLamda_antipi_bach_antiprot_daugh_after->Fill(CalculateInvMassXi(tmpAntiXi_recomb[4].GetMomentum(3), 211, tmpAntiXi_recomb[4].GetMomentum(2), 211, tmpAntiXi_recomb[4].GetMomentum(1), 2212));
                    }
                }
            }

            for (auto it : vLambda)
            {
                if (!it.UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassLambda_sanityCheck_after->Fill(CalculateInvMassLambda(momP, 211, momN, 2212));
            }
            for (auto it : vAntiLambda)
            {
                if (!it.UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassXi_sanityCheck_after->Fill(CalculateInvMassLambda(momN, 2212, momP, 211));
            }
            for (auto it : vXi)
            {
                if (!it.UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                TVector3 momB = it.GetMomentum(3);
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassXi_sanityCheck_after->Fill(CalculateInvMassXi(momB, 211, momP, 2212, momN, 211));
            }
            for (auto it : vAntiXi)
            {
                if (!it.UseParticle()) // continue wenn der Paircleaner sie aussortiert hat
                {
                    continue;
                }
                TVector3 momB = it.GetMomentum(3);
                TVector3 momP = it.GetMomentum(1);
                TVector3 momN = it.GetMomentum(2);
                hInvMassAntiXi_sanityCheck_after->Fill(CalculateInvMassXi(momB, 211, momP, 211, momN, 2212));
            }
        }
        
        PostData(1, tlEventCuts);
        PostData(2, tlLambdaList);
        PostData(3, tlAntiLambdaList);
        PostData(4, tlCascadeCutsXi);
        PostData(5, tlAntiCascadeCutsXi);
        PostData(6, tlResults);
        PostData(7, tlResultsQA);

        PostData(8, tlEventCuts2);
        PostData(9, tlLambdaList2);
        PostData(10, tlAntiLambdaList2);
        PostData(11, tlCascadeCutsXi2);
        PostData(12, tlAntiCascadeCutsXi2);
        PostData(13, tlResults2);
        PostData(14, tlResultsQA2);

        PostData(15, tlRecombination_before); // reconstruction from daugthers histograms
        PostData(16, tlRecombination_after);  // reconstruction from daugthers histograms

        if (fIsMC)
        {
            PostData(17, tlLambdaMC);

            PostData(18, tlAntiLambdaMC);
        }
    }   
}

void AliAnalysisTaskPOmegaPenne::ResetGlobalTrackReference()
{
    //This method was inherited form H. Beck analysis
    for (UShort_t i = 0; i < fTrackBufferSize; i++)
    {
        fGTI[i] = nullptr;
        // std::fill(fGTI.begin(),fGTI.end(), nullptr);
    }
}

//  Stores TrackID in Global Track Reference Array 'fGTI' if ID > 0
//
void AliAnalysisTaskPOmegaPenne::StoreGlobalTrackReference(AliVTrack *vTrack)
{
    //This method was inherited form H. Beck analysis
    AliNanoAODTrack *nanoTrack = dynamic_cast<AliNanoAODTrack*>(vTrack);
    const int trackID = vTrack->GetID();
    if (trackID < 0)
    {
        return;
    }
    if (trackID >= fTrackBufferSize)
    {
        printf("Warning: track ID too big for buffer: ID: %d, buffer %d\n", trackID, fTrackBufferSize);
        return;
    }

    if (fGTI[trackID])
    {
        if ((!nanoTrack->GetFilterMap()) && (!vTrack->GetTPCNcls()))
        {
            return;
        }
        if (dynamic_cast<AliNanoAODTrack *>(fGTI[trackID])->GetFilterMap() || fGTI[trackID]->GetTPCNcls())
        {
            printf("WARNING! global track info already there!");
            printf("    ###     TPCNcls track1 %u Track2 %u", (fGTI[trackID])->GetTPCNcls(), vTrack->GetTPCNcls());
            printf("   ###     FilterMap Track1 %u track2 %u\n", dynamic_cast<AliNanoAODTrack *>(fGTI[trackID])->GetFilterMap(), nanoTrack->GetFilterMap());
        }
    }
    fGTI[trackID] = vTrack;

}
float AliAnalysisTaskPOmegaPenne::CalculateInvMassLambda(TVector3 momNegDaughter, int PDGnegDaughter, TVector3 momPosDaughter, int PDGposDaughter)
{
    float invMass = 0;
    
    float massDP = TDatabasePDG::Instance()->GetParticle(PDGposDaughter)->Mass(); // Proton
    float massDN = TDatabasePDG::Instance()->GetParticle(PDGnegDaughter)->Mass();  // Pion
    float EDaugP = TMath::Sqrt(
        massDP * massDP + 
        momPosDaughter.X() * momPosDaughter.X() + 
        momPosDaughter.Y() * momPosDaughter.Y() + 
        momPosDaughter.Z() * momPosDaughter.Z()
    );
    float EDaugN = TMath::Sqrt(
        massDN * massDN + 
        momNegDaughter.X() * momNegDaughter.X() + 
        momNegDaughter.Y() * momNegDaughter.Y() + 
        momNegDaughter.Z() * momNegDaughter.Z()
    );
    float energysum = EDaugP + EDaugN;
    float pSum2 = 
        ( momNegDaughter.X() + momPosDaughter.X() ) * 
        ( momNegDaughter.X() + momPosDaughter.X() ) 
        +
        ( momNegDaughter.Y() + momPosDaughter.Y() ) * 
        ( momNegDaughter.Y() + momPosDaughter.Y() ) 
        + 
        ( momNegDaughter.Z() + momPosDaughter.Z() ) * 
        ( momNegDaughter.Z() + momPosDaughter.Z() )
    ;
    invMass = TMath::Sqrt(energysum * energysum - pSum2);
    return invMass;
}

float AliAnalysisTaskPOmegaPenne::CalculateInvMassXi(TVector3 momBach, int PGGbach, TVector3 momPosDaughter, int PDGposDaughter, TVector3 momNegDaughter, int PDGnegDaughter)
{
    float massPosDaugh = TDatabasePDG::Instance()->GetParticle(PDGposDaughter)->Mass();  // Proton 2212 or antiPion 211
    float massNegDaugh = TDatabasePDG::Instance()->GetParticle(PDGnegDaughter)->Mass();   // Pion 211 or antiProton 2212
    float massBach = TDatabasePDG::Instance()->GetParticle(PGGbach)->Mass();            // Pion 211 or antiPion 211
    float massV0 = CalculateInvMassLambda(momNegDaughter, PDGnegDaughter, momPosDaughter, PDGposDaughter);                 // Lambda
    
    TVector3 PtotV0 = (momPosDaughter + momNegDaughter);
    float Ev0 = ::sqrt(massV0 * massV0 + PtotV0.Mag2());

    float EBach = ::sqrt(massBach + momBach.Mag2());

    float Ptot2Casc = (PtotV0 + momBach).Mag2();

    return ::sqrt(pow(Ev0 + EBach,2) - Ptot2Casc);
}

float AliAnalysisTaskPOmegaPenne::CalculateInvMassHere(AliFemtoDreamv0 *v0, int PDGPosDaug, int PDGNegDaug)     // copied from AliFemtoDreamv0Cuts
{
    Double_t invMass = 0;
    
    float massDP = TDatabasePDG::Instance()->GetParticle(PDGPosDaug)->Mass();
    float massDN = TDatabasePDG::Instance()->GetParticle(PDGNegDaug)->Mass();
    float EDaugP = TMath::Sqrt(
        massDP * massDP + 
        v0->GetPosDaughter()->GetMomentum().X() * v0->GetPosDaughter()->GetMomentum().X() + 
        v0->GetPosDaughter()->GetMomentum().Y() * v0->GetPosDaughter()->GetMomentum().Y() + 
        v0->GetPosDaughter()->GetMomentum().Z() * v0->GetPosDaughter()->GetMomentum().Z()
    );
    float EDaugN = TMath::Sqrt(
        massDN * massDN + 
        v0->GetNegDaughter()->GetMomentum().X() * v0->GetNegDaughter()->GetMomentum().X() + 
        v0->GetNegDaughter()->GetMomentum().Y() * v0->GetNegDaughter()->GetMomentum().Y() + 
        v0->GetNegDaughter()->GetMomentum().Z() * v0->GetNegDaughter()->GetMomentum().Z())
    ;
    float energysum = EDaugP + EDaugN;
    float pSum2 = 
        (v0->GetNegDaughter()->GetMomentum().X() + v0->GetPosDaughter()->GetMomentum().X()) * 
        (v0->GetNegDaughter()->GetMomentum().X() + v0->GetPosDaughter()->GetMomentum().X()) +

        (v0->GetNegDaughter()->GetMomentum().Y() + v0->GetPosDaughter()->GetMomentum().Y()) * 
        (v0->GetNegDaughter()->GetMomentum().Y() + v0->GetPosDaughter()->GetMomentum().Y()) + 

        (v0->GetNegDaughter()->GetMomentum().Z() + v0->GetPosDaughter()->GetMomentum().Z()) * 
        (v0->GetNegDaughter()->GetMomentum().Z() + v0->GetPosDaughter()->GetMomentum().Z())
        ;
    invMass = TMath::Sqrt(energysum * energysum - pSum2);
    return invMass;
}

void AliAnalysisTaskPOmegaPenne::CleanDecayAndDecayLambdaXiInvMass(std::vector<AliFemtoDreamBasePart> *Decay1, 
                                                                   std::vector<AliFemtoDreamBasePart> *Decay2) 
{
//   int counter = 0;
  for (auto itDecay1 = Decay1->begin(); itDecay1 != Decay1->end(); ++itDecay1) {
    if (itDecay1->UseParticle()) {
      for (auto itDecay2 = Decay2->begin(); itDecay2 != Decay2->end();
          ++itDecay2) {
        if (itDecay2->UseParticle()) {
          std::vector<int> IDDaug1 = itDecay1->GetIDTracks();
          std::vector<int> IDDaug2 = itDecay2->GetIDTracks();
          for (auto itID1s = IDDaug1.begin(); itID1s != IDDaug1.end();
              ++itID1s) {
            for (auto itID2s = IDDaug2.begin(); itID2s != IDDaug2.end();
                ++itID2s) {
              if (*itID1s == *itID2s) {
                if (itDecay1->GetInvMass() < itDecay2->GetInvMass()) {
                  itDecay1->SetUse(false);
                //   counter++;
                } else {
                  itDecay2->SetUse(false);
                //   counter++;
                }
              }
            }
          }
        } else {
          continue;
        }
      }
    } else {
      continue;
    }
  }
}
void AliAnalysisTaskPOmegaPenne::CleanDecayXi(std::vector<AliFemtoDreamBasePart> *Decay)
{
    
    //   int counter = 0;
    for (std::vector<AliFemtoDreamBasePart>::iterator itDecay1 = Decay->begin();
         itDecay1 != Decay->end(); ++itDecay1)
    {
        if (itDecay1->UseParticle())
        {
            for (auto itDecay2 = itDecay1 + 1; itDecay2 != Decay->end(); ++itDecay2)
            {
                if (itDecay2->UseParticle())
                {
                    std::vector<int> IDDaug1 = itDecay1->GetIDTracks();
                    std::vector<int> IDDaug2 = itDecay2->GetIDTracks();
                    for (auto itID1s = IDDaug1.begin(); itID1s != IDDaug1.end();
                         ++itID1s)
                    {
                        for (auto itID2s = IDDaug2.begin(); itID2s != IDDaug2.end();
                             ++itID2s)
                        {
                            if (*itID1s == *itID2s)
                            {
                                // PDG 3312 - Xi
                                if ( ::abs(itDecay1->GetInvMass() * weightXi(itDecay1->GetPt()) - TDatabasePDG::Instance()->GetParticle(3312)->Mass()) < ::abs(itDecay2->GetInvMass() * weightXi(itDecay2->GetPt()) - TDatabasePDG::Instance()->GetParticle(3312)->Mass()) )
                                {
                                    itDecay1->SetUse(false);
                                }
                                else
                                {
                                    itDecay2->SetUse(false);
                                }
                            }
                        }
                    }
                }
                else
                    continue;
            }
        }
        else
            continue;
    }
    //   if (!fMinimalBooking)
    //     fHists->FillDaughtersSharedDaughter(histnumber, counter);
}
float weightXi(float pT)
{
    return (0.00015173453992 * ::pow(pT,5) - 0.00288299053804 * ::pow(pT,4) + 0.020665050728464 * ::pow(pT,3) - 0.070564072487045 * ::pow(pT,2) + 0.127893861180294*pT + 0.825506424694561);
}