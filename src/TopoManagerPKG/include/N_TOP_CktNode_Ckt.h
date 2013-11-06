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
// Filename       : $RCSfile: N_TOP_CktNode_Ckt.h,v $
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
// Revision Number: $Revision: 1.14.2.2 $
//
// Revision Date  : $Date: 2013/10/03 17:23:51 $
//
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef N_TOP_CktNode_Ckt_h
#define N_TOP_CktNode_Ckt_h 1

// ---------- Standard Includes ----------

// ----------   Xyce Includes   ----------

#include <N_TOP_CktNode.h>

// ---------- Forward Declarations ----------

class N_TOP_CktGraph;


//-----------------------------------------------------------------------------
// Class         : N_TOP_CktNode_Ckt
// Purpose       :
// Special Notes :
// Creator       : Rob Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 5/16/00
//-----------------------------------------------------------------------------
class N_TOP_CktNode_Ckt : public N_TOP_CktNode
{

private:

  // Default constructor (private).
  N_TOP_CktNode_Ckt() { }

  // Assignment operator (private).
  N_TOP_CktNode_Ckt & operator = (const N_TOP_CktNode_Ckt & right);

public:

  // Constructor
  N_TOP_CktNode_Ckt(N_TOP_CktGraph * grphPtr, const string & ID = string(""),
                    const int & gID = 0,
                    const list < int > & varGIDList = list < int > (),
                    const list < int > & statevarGIDList = list < int > (),
                    const list < int > & storevarGIDList = list < int > (),
                    const int & pNum = 0, const bool & owned = true)
    :
    N_TOP_CktNode(ID, gID, varGIDList, statevarGIDList, storevarGIDList, pNum, owned),
    cktGphPtr_(grphPtr)
    { }

  // Constructor
  N_TOP_CktNode_Ckt(N_TOP_CktGraph * grphPtr, const N_TOP_NodeBlock & nb)
    :
    N_TOP_CktNode(nb), cktGphPtr_(grphPtr)
    { }

  // Destructor
  ~N_TOP_CktNode_Ckt() { }

  int type() const { return _CNODE; }

  bool getNoDCPathVar() {return false;} 

  bool getConnToOneTermVar() {return false;}

  void setTrueNoDCPathVar() {}
  
  void setTrueConnToOneTermVar() {}

private:

  // Pointer to the circuit graph.
  N_TOP_CktGraph * cktGphPtr_;

public:

  ostream & put(ostream & os) const;

};

//-----------------------------------------------------------------------------
// Function      : N_TOP_CktNode_Ckt::operator=
// Purpose       :
// Special Notes :
// Scope         : public
// Creator       : Rob Hoekstra, SNL, Parallel Computational Sciences
// Creation Date : 5/16/00
//-----------------------------------------------------------------------------
inline N_TOP_CktNode_Ckt & N_TOP_CktNode_Ckt::operator = (
  const N_TOP_CktNode_Ckt & right)
{
  return * this;
}

#endif
