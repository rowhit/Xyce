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
// Filename       : $RCSfile: N_ANP_AC.h,v $
//
// Purpose        : AC analysis class
//
// Special Notes  : Specify any "hidden" or subtle details of the class here.
//                  Portability details, error handling information, etc.
//
// Creator        : Ting Mei   
//
// Creation Date  : 01/11
//
// Revision Information:
// ---------------------
//
// Revision Number: $Revision: 1.6.2.2 $
// Revision Date  : $Date: 2013/10/03 17:23:30 $
// Current Owner  : $Author: tvrusso $
//-----------------------------------------------------------------------------

#ifndef Xyce_N_ANP_AC_h
#define Xyce_N_ANP_AC_h

#include <Teuchos_RCP.hpp>
using Teuchos::RCP;
using Teuchos::rcp;


// ----------   Xyce Includes   ----------
#include <N_ANP_AnalysisBase.h>
#include <N_UTL_FixedQueue.h>

// ---------- Forward Declarations ----------
class N_ANP_AnalysisManager;
class N_UTL_ExpressionData;
class N_LAS_Matrix;
class N_LAS_Vector;
class N_LAS_BlockMatrix;
class N_LAS_BlockVector;
class Amesos_BaseSolver;
class Epetra_LinearProblem;

//-------------------------------------------------------------------------
// Class         : N_ANP_AC 
// Purpose       : AC analysis class
// Special Notes : 
// Creator       : Ting Mei
// Creation Date : 05/24/11
//-------------------------------------------------------------------------
class N_ANP_AC: public N_ANP_AnalysisBase 
{
  public:
    N_ANP_AC( N_ANP_AnalysisManager * anaManagerPtr );

    ~N_ANP_AC();
    
    bool setAnalysisParams(const N_UTL_OptionBlock & paramsBlock);

    bool run();
    bool init();
    bool loopProcess();
//    bool processSuccessfulDCOP();
//    bool processFailedDCOP();
    bool processSuccessfulStep();
    bool processFailedStep();
    bool finish();
    bool handlePredictor();
    bool resetForStepAnalysis();
//    void outputQueuedData();
//    bool finalVerboseOutput();

//    void printStepHeader();
//    void printProgress();


    // mixed-signal specific
//    void preStepDetails (double maxTimeStepFromHabanero);
//    bool mixedSignalStep();
//    bool finalizeStep ();

    // Two Level specific
//    bool twoLevelStep();

    void setDCOPFlag(bool flag) { dcopFlag_ = flag; }
    bool getDCOPFlag() { return dcopFlag_; }

  private:
    
    bool dcopFlag_;               // true if this is a DCOP calculation.
    
    N_LAS_Vector * bVecRealPtr; 
    N_LAS_Vector * bVecImagPtr;  
//    double startDCOPtime, endTRANtime; // startTRANtime
    int acLoopSize_;
    
    list < int > acSweepFailures_; 
 
    double stepMult_;
    double fstep_;
    
    double currentFreq_; 

    int setupSweepParam_();

    bool updateCurrentFreq_(int stepNumber);
 
    bool createLinearSystem_();
    
    bool updateLinearSystemFreq_();

    bool solveLinearSystem_();

    RCP<N_LAS_Matrix> CPtr_;
    RCP<N_LAS_Matrix> GPtr_;
    RCP<N_LAS_BlockMatrix> ACMatrixPtr_;
    RCP<N_LAS_BlockVector> BPtr_;
    RCP<N_LAS_BlockVector> XPtr_;

    RCP<Amesos_BaseSolver> blockSolver;
   
    RCP<Epetra_LinearProblem> blockProblem;
 
};

#endif
