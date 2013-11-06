//-----------------------------------------------------------------------------
// Copyright Notice
//
//   Copyright 2002 Sandia Corporation. Under the terms
//   of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
//   Government retains certain rights in this software.
//
//    Xyce(TM) Parallel Electrical Simulator
//    Copyright (C) 2002-2011  Sandia Corporation
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
// Filename       : $RCSfile: N_DEV_Synapse3.h,v $
//
// Purpose        : Simple delay synapse
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
// Revision Number: $Revision: 1.16.2.1 $
//
// Revision Date  : $Date: 2013/10/03 17:23:33 $
//
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef Xyce_N_DEV_Synapse3_h
#define Xyce_N_DEV_Synapse3_h

// ----------   Xyce Includes   ----------
#include <N_DEV_DeviceTemplate.h>
#include <N_DEV_DeviceBlock.h>
#include <N_DEV_DeviceInstance.h>
#include <N_DEV_DeviceModel.h>

#include <Sacado.hpp>

namespace Xyce {
namespace Device {
namespace Synapse3 {

// ---------- Forward Declarations -------
class Model;
class Instance;

//-----------------------------------------------------------------------------
// Class         : 3
// Purpose       :
//
//	This  is  the  instance class  for Synapse4s.  It
//	contains "unique" Synapse4  information - ie stuff that
//	will be true of only one  Synapse4 in the circuit, such
//	as the nodes to which it is connected.  A Synapse4 is
//	connected to only two circuit nodes.
//
//	This class  does not directly contain information about
//	its node indices. It contains indices into the 3 parts
//	(A, dx, and  b) of the matrix  problem A*dx = b, and
//	also x.  A is the Jacobian  matrix, dx is the update to
//	the solution vector x, and b is the right hand side
//	function vector.  These indices are global, and
//	determined by topology during  the initialization stage
//	of execution.
//
// Special Notes :
// Creator       : Christina Warrender, SNL,
// Creation Date : 10/12/11
//-----------------------------------------------------------------------------
class Instance : public DeviceInstance
{
  friend class ParametricData<Instance>;
  friend class Model;

public:
  static vector< vector<int> > jacStamp;
  static ParametricData<Instance> &getParametricData();

  virtual const ParametricData<void> &getMyParametricData() const {
    return getParametricData();
  }

  Instance(InstanceBlock & IB,
           Model & Riter,
           MatrixLoadData & mlData1,
           SolverState &ss1,
           ExternData  &ed1,
           DeviceOptions & do1);

  ~Instance();

private:
  Instance(const Instance &);
  Instance &operator=(const Instance &);

public:
  void registerLIDs( const vector<int> & intLIDVecRef,
                     const vector<int> & extLIDVecRef );
  void registerStoreLIDs( const vector<int> & storeLIDVecRef );
  map<int,string> & getStoreNameMap ();
  map<int,string> & getIntNameMap ();

  bool processParams (string param = "");

  bool updateTemperature(const double & temp_tmp);

  bool updateIntermediateVars ();
  bool updatePrimaryState ();
  bool updateSecondaryState ();

  const vector< vector<int> > & jacobianStamp() const;
  void registerJacLIDs( const vector< vector<int> > & jacLIDVec );

  // load functions, residual:
  bool loadDAEQVector ();
  bool loadDAEFVector ();

  // load functions, Jacobian:
  bool loadDAEdQdx ();
  bool loadDAEdFdx ();

  // enable the interface to produce plot files. - although we're not
  // actually using this for output
  bool plotfileFlag () {return true;}
  bool outputPlotFiles();

  void setupPointers();

  Model &getModel() {
    return model_;
  }

private:

  Model &       model_;         //< Owning model
  // make this public so that the master-class can potentially
  // access and output these values en-mass rather than
  // on a object by object basis.
  double synapticWeight;
  // user-specified parameters:
  double gMax;
  bool gMaxGiven;
  double transmissionProbability;
  bool transmissionProbabilityValueGiven;

  //Vector local index for Positive Node
  int li_Prev;
  //Vector local index for Negative Node
  int li_Post;

  // store variable quantities
  int li_A0_store;
  int li_B0_store;
  int li_t0_store;
  int li_weight_store;
  int li_VL1_store;
  int li_VL2_store;
  int li_VL3_store;
  int li_store_dev_i;

#ifdef Xyce_FullSynapseJac
  // Offset variables corresponding to the above declared indices.
  int APostEquPostNodeOffset;

  // Pointers for Jacobian
  double *f_PostEquPostNodePtr;
#endif

  // vars used for load calculations
  double ipost;  // post Synapse4 current
  double didVpost;

  bool ready;
  double respondTime;
  int transmissionFactor;  // 0 or 1 depending on random number < transmissionProbability

  // flag to indicate random number generator was initialized
  bool randInitialized;

  // initial weight can be specified on the instance line to override the model value
  double wInitialValue;   // initial value for weighting
  bool wInitialValueGiven; // flag set by parser if this value is given.

  double synapticWeightUpdate; // value calculated to update synaptic weight.
  double vl1Update;
  double vl2Update;
  double vl3Update;
};


//-----------------------------------------------------------------------------
// Class         : Model
// Purpose       :
//
//
// Special Notes :
// Creator       : Christina Warrender, SNL
// Creation Date : 10/12/11
//-----------------------------------------------------------------------------
class Model : public DeviceModel
{
  typedef std::vector<Instance *> InstanceVector;

  friend class ParametricData<Model>;
  friend class Instance;

public:
  static ParametricData<Model> &getParametricData();

  virtual const ParametricData<void> &getMyParametricData() const {
    return getParametricData();
  }

  Model(const ModelBlock & MB,
        SolverState & ss1,
        DeviceOptions & do1);
  ~Model();

private:
  Model();
  Model(const Model &);
  Model &operator=(const Model &);

public:
  virtual std::ostream &printOutInstances(std::ostream &os) const;

  bool processParams (string param = "");
  bool processInstanceParams (string param = "");


public:
  InstanceVector &getInstanceVector() {
    return instanceContainer;
  }

  const InstanceVector &getInstanceVector() const {
    return instanceContainer;
  }

private:
  vector<Instance*> instanceContainer;

private:

  // user-specified parameters
  double vThresh;
  double gMax;
  double delay;
  double eRev;
  double tau1;
  double tau2;
  // parameters for weighting function
  double sParam;          // voltage threshold for a spike event
  double rParam;          // Resting voltage for resting event
  double wMin;            // minimum value for weighting
  double wMax;            // maximum value for weighting
  double wInitialValue;   // initial value for weighting
  double vL1tau1;         // rate for Longterm potentiation factor (LPF) based on post-synaptic voltage (rate 1)
  double vL2tau2;         // rate for Longterm potentiation factor (LPF) based on post-synaptic voltage (rate 2)
  double vL3tau3;         // rate for Longterm potentiation factor (LPF) based on pre-synaptic voltage (rate 3)
  double aLTD;            // long term depression coefficient
  double aLTP;            // long term potentiation coefficient
  double transmissionProbability;

  // derived parameters
  double tp;		// time of EPSP peak, relative to start of postsynaptic response
  double factor;	// used to ensure peak conductance = 1S for weight (gMax) = 1
};

} // namespace Synapse3
} // namespace Device
} // namespace Xyce

typedef Xyce::Device::Synapse3::Instance N_DEV_SynapseInstance3;
typedef Xyce::Device::Synapse3::Model N_DEV_SynapseModel3;


#endif
