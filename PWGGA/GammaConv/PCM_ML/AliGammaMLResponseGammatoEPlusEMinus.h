#ifndef ALIHFMLRESPONSED0TOKPI_H
#define ALIHFMLRESPONSED0TOKPI_H

// Copyright CERN. This software is distributed under the terms of the GNU
// General Public License v3 (GPL Version 3).
//
// See http://www.gnu.org/licenses/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

//**************************************************************************************
// \class AliGammaMLResponseGammatoEPlusEMinus
// \brief helper class to handle application of ML models for D0 analyses trained
// with python libraries
// \authors:
// F. Grosa, fabrizio.grosa@cern.ch
/////////////////////////////////////////////////////////////////////////////////////////

#include "AliGammaMLResponse.h"

class AliGammaMLResponseGammatoEPlusEMinus : public AliGammaMLResponse
{
public:
    AliGammaMLResponseGammatoEPlusEMinus();
    AliGammaMLResponseGammatoEPlusEMinus(const Char_t *name, const Char_t *title, const std::string configfilepath);
    virtual ~AliGammaMLResponseGammatoEPlusEMinus();

    AliGammaMLResponseGammatoEPlusEMinus(const AliGammaMLResponseGammatoEPlusEMinus &source);
    AliGammaMLResponseGammatoEPlusEMinus& operator=(const AliGammaMLResponseGammatoEPlusEMinus& source);

protected:
    virtual void SetMapOfVariablesSetMapOfVariables(AliAODConversionPhoton *cand, AliVEvent* fInputEvent, AliConversionPhotonCuts* fiPhotonCut, AliV0ReaderV1* fV0Reader) ;

    /// \cond CLASSIMP
    ClassDef(AliGammaMLResponseGammatoEPlusEMinus, 1); ///
    /// \endcond
};
#endif