//-----------------------------------------------------------------------------
// Copyright Notice
//
//   Copyright 2002 Sandia Corporation. Under the terms
//   of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
//   Government retains certain rights in this software.
//
//    Xyce(TM) Parallel Electrical Simulator
//    Copyright (C) 2002-2013  Sandia Corporation
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

//-----------------------------------------------------------------------------
// Filename       : $RCSfile: N_DEV_Synapse3_Factory.h,v $
//
// Purpose        : Simple Delay Synapse
//
// Special Notes  :
//
// Creator        : Rich Schiek, SNL, Electrical Systems Modeling
//
// Creation Date  : 01/25/2011
//
// Revision Information:
// ---------------------
//
// Revision Number: $Revision: 1.3.2.1 $
//
// Revision Date  : $Date: 2013/10/03 17:23:33 $
//
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef Xyce_N_DEV_Synapse3_Factory_h
#define Xyce_N_DEV_Synapse3_Factory_h

// ----------   Xyce Includes   ----------
#include <N_DEV_DeviceTemplate.h>
#include <N_DEV_Synapse3.h>

//-----------------------------------------------------------------------------
// Class         : N_DEV_Synapse3
// Purpose       : Handles ideal transmission lines
//
// Special Notes :
//
// Creator       : Rich Schiek, SNL, Electrical Systems Modeling
// Creation Date : 01/25/2011
//-----------------------------------------------------------------------------
struct N_DEV_Synapse3
{
  //---------------------------------------------------------------------------
  // Function      : factory
  // Purpose       : This is the factory function for the TRA class.
  //
  // Special Notes : ERK.  10/16/2005.  This used to be a singleton (ie a
  //                 static pointer was returned) but had to be changed
  //                 so that the library version of Xyce would work
  //                 correctly.
  //
  // Scope         : public
  // Creator       : Rich Schiek, SNL, Electrical Systems Modeling
  // Creation Date : 01/25/2011
  //---------------------------------------------------------------------------
  static N_DEV_Device * factory(N_DEV_SolverState & ss1,
                                N_DEV_DeviceOptions & do1)
  {
    const string name("Synapse, Clopath");
    const string className("N_DEV_Synapse3");
    const string defaultModelName ("YSYNAPSE level 3");

    vector< pair<string,double> > nameVec;

    N_DEV_Device * devptr =
      new Xyce::Device::DeviceTemplate<N_DEV_SynapseModel3, N_DEV_SynapseInstance3>
                  ( name,
                    className,
                    defaultModelName,
                    nameVec,
                    true,    // linear
                    true,   // model not required
                    ss1,do1);

    return devptr;
  }
};

#endif