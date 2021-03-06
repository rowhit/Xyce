//-----------------------------------------------------------------------------
// Copyright Notice
//
//   Copyright 2002 Sandia Corporation. Under the terms
//   of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
//   Government retains certain rights in this software.
//
//    Xyce(TM) Parallel Electrical Simulator
//    Copyright (C) 2002-2014 Sandia Corporation
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Filename      : $RCSfile: N_IO_MeasureDuty.C,v $
// Purpose       : Transient analysis functions.
// Special Notes :
// Creator       : Richard Schiek, SNL, Electrical and Microsystem Modeling
// Creation Date : 03/10/2009
//
// Revision Information:
// ---------------------
// Revision Number: $Revision: 1.12 $
// Revision Date  : $Date: 2014/02/24 23:49:20 $
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#include <Xyce_config.h>

#include <N_IO_MeasureDuty.h>
#include <N_ERH_ErrorMgr.h>

namespace Xyce {
namespace IO {
namespace Measure {

//-----------------------------------------------------------------------------
// Function      : Duty::Duty()
// Purpose       :
// Special Notes :
// Scope         : public
// Creator       : Rich Schiek, Electrical and Microsystems Modeling
// Creation Date : 3/10/2009
//-----------------------------------------------------------------------------
Duty::Duty( const Util::OptionBlock & measureBlock, N_IO_OutputMgr &outputMgr ):
  Base(measureBlock, outputMgr),
  totalAveragingWindow_(0.0),
  totalOnTime_(0.0),
  lastTimeValue_(0.0),
  initialized_(false),
  inOnState_(false)
{
  // indicate that this measure type is supported and should be processed in simulation
  typeSupported_ = true;

}

void Duty::prepareOutputVariables() 
{
  // this measurement should have only one dependent variable.
  // Error for now if it doesn't
  numOutVars_ = outputVars_.size();
  if ( numOutVars_ > 1 )
  {
    std::string msg = "Too many dependent variables for statistical measure, \"" + name_ + "\" Exiting.";
    N_ERH_ErrorMgr::report( N_ERH_ErrorMgr::USR_FATAL, msg);
  }

  outVarValues_.resize( numOutVars_, 0.0 );
}


//-----------------------------------------------------------------------------
// Function      : Duty::updateTran()
// Purpose       :
// Special Notes :
// Scope         : public
// Creator       : Rich Schiek, Electrical and Microsystems Modeling
// Creation Date : 3/10/2009
//-----------------------------------------------------------------------------
void Duty::updateTran( const double circuitTime, const N_LAS_Vector *solnVec, const N_LAS_Vector *stateVec, const N_LAS_Vector *storeVec)
{
  if( !calculationDone_ && withinFromToWindow( circuitTime ) )
  {
    // we're in the transient window, now we need to calculate
    // the value of this measure

    // update our outVarValues_ vector
    for( int i=0; i< numOutVars_; i++ )
    {
      outVarValues_[i] = getOutputValue(outputVars_[i], solnVec, stateVec, storeVec, 0);
    }

    if( initialized_  )
    {
      if( ( (outVarValues_[0] + minval_) > onValue_ ) || ( inOnState_ && ( (outVarValues_[0] + minval_) > offValue_ )) )
      {
        // add to On duty time
        totalOnTime_ += (circuitTime - lastTimeValue_);
        inOnState_=true;
      }
      else
      {
        inOnState_=false;
      }

      // Calculating an average of outVarValues_[0];
      totalAveragingWindow_ += (circuitTime - lastTimeValue_);
    }

    lastTimeValue_ = circuitTime;
    initialized_=true;
  }
}


//-----------------------------------------------------------------------------
// Function      : Duty::updateDC()
// Purpose       :
// Special Notes :
// Scope         : public
// Creator       : Rich Schiek, Electrical and Microsystems Modeling
// Creation Date : 3/10/2009
//-----------------------------------------------------------------------------
void Duty::updateDC( const std::vector<N_ANP_SweepParam> & dcParamsVec, const N_LAS_Vector *solnVec, const N_LAS_Vector *stateVec, const N_LAS_Vector *storeVec)
{

}


//-----------------------------------------------------------------------------
// Function      : Duty::getMeasureResult()
// Purpose       :
// Special Notes :
// Scope         : public
// Creator       : Rich Schiek, Electrical and Microsystems Modeling
// Creation Date : 3/10/2009
//-----------------------------------------------------------------------------
double Duty::getMeasureResult()
{
  if( initialized_ )
  {
    calculationResult_ =  totalOnTime_ / totalAveragingWindow_;
  }
  return calculationResult_;
}

} // namespace Measure
} // namespace IO
} // namespace Xyce
