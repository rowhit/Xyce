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
// Filename       : $RCSfile: N_TOP_CktGraphCreator.h,v $
//
// Purpose        :
//
// Special Notes  :
//
// Creator        : Robert J. Hoekstra, SNL, Parallel Computational Sciences
//
// Creation Date  : 03/20/00
//
// Revision Information:
// ---------------------
//
// Revision Number: $Revision: 1.12 $
//
// Revision Date  : $Date: 2014/02/24 23:49:27 $
//
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef N_TOP_CktGraphCreator_h
#define N_TOP_CktGraphCreator_h 1

#include <string>
#include <list>

#include <N_TOP_fwd.h>
#include <N_TOP_Misc.h>

namespace Xyce {
namespace Topo {

//-----------------------------------------------------------------------------
// Class         : CktGraphCreator
// Purpose       :
// Special Notes :
// Creator       : Rob Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 5/16/00
//-----------------------------------------------------------------------------
class CktGraphCreator
{

public:

  // Default constructor.
  CktGraphCreator() { }

  // Copy constructor.
  CktGraphCreator(const CktGraphCreator & right) { }

  // Destructor
  virtual ~CktGraphCreator() { }

  // Method to create a new circuit graph (abstract).
  virtual CktGraph * create(const std::string & cgID) = 0;

  // Method to create a new circuit graph (abstract).
  virtual CktGraph * create(const std::string & cgID, const std::list<NodeID> & nodeList) = 0;

};

} // namespace Topo
} // namespace Xyce

typedef Xyce::Topo::CktGraphCreator N_TOP_CktGraphCreator;

#endif
