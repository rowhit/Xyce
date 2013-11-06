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

//-------------------------------------------------------------------------
// Filename       : $RCSfile: N_LAS_HBBlockJacobiEpetraOperator.h,v $
//
// Purpose        : This is an HB specific class that derives off of
// Epetra_Operator and supports the matrix-free block Jacobi preconditioner
// that we need for HB.  It takes a pointer to the HB loader so that it can 
// correctly do the apply function.
//
// Creator        : Heidi Thornquist, 1437
//
// Creation Date  : 11/12/08
//
// Revision Information:
// ---------------------
//
// Revision Number: $Revision: 1.1.2.2 $
//
// Revision Date  : $Date: 2013/10/03 17:23:44 $
//
// Current Owner  : $Author: tvrusso $
//-------------------------------------------------------------------------

#ifndef Xyce_N_LAS_HBBlockJacobiEpetraOperator_h
#define Xyce_N_LAS_HBBlockJacobiEpetraOperator_h

// ---------- Standard Includes ----------

#include <vector>

// ---------- Trilinos Includes ----------

#include <Teuchos_RCP.hpp>
#include <Epetra_Operator.h>

// ----------   Xyce Includes   ----------

class Epetra_LinearProblem;
class Epetra_MultiVector;
class Epetra_Comm;
class Epetra_Map;
class Amesos_BaseSolver;
class N_LAS_HBBuilder;
class N_LAS_MultiVector;

//-----------------------------------------------------------------------------
// Class         : N_LAS_HBBlockJacobiEpetraOperator
// Purpose       : Matrix Free Epetra Operator concrete class
// Special Notes : 
// Creator       : Heidi Thornquist, 1437
// Creation Date : 12/22/08
//-----------------------------------------------------------------------------

class N_LAS_HBBlockJacobiEpetraOperator : virtual public Epetra_Operator
{

public:

  N_LAS_HBBlockJacobiEpetraOperator();

  virtual ~N_LAS_HBBlockJacobiEpetraOperator();

  void initialize(
      const std::vector<Teuchos::RCP<Epetra_LinearProblem> >& epetraProblems,
      const std::vector<Teuchos::RCP<Amesos_BaseSolver> >& amesosSolvers,
      const Teuchos::RCP<N_LAS_HBBuilder>& hbBuilder
      );

    //! If set true, transpose of this operator will be applied.
    /*! This flag allows the transpose of the given operator to be used implicitly.  Setting this flag
        affects only the Apply() and ApplyInverse() methods.  If the implementation of this interface 
	does not support transpose use, this method should return a value of -1.
      
    \param In
	   UseTranspose -If true, multiply by the transpose of operator, otherwise just use operator.

    \return Integer error code, set to 0 if successful.  Set to -1 if this implementation does not support transpose.
    */
  int SetUseTranspose(bool UseTranspose);

    //! Returns the result of a Epetra_Operator applied to a Epetra_MultiVector X in Y.
    /*
    \param In
	   X - A Epetra_MultiVector of dimension NumVectors to multiply with matrix.
    \param Out
	   Y -A Epetra_MultiVector of dimension NumVectors containing result.

    \return Integer error code, set to 0 if successful.
    */
  int Apply(const Epetra_MultiVector& X, Epetra_MultiVector& Y) const;
  int Apply(const N_LAS_MultiVector& X, N_LAS_MultiVector& Y) const;

    //! Returns the result of a Epetra_Operator inverse applied to an Epetra_MultiVector X in Y.
    /*
    \param In
	   X - A Epetra_MultiVector of dimension NumVectors to solve for.
    \param Out
	   Y -A Epetra_MultiVector of dimension NumVectors containing result.

    \return Integer error code, set to 0 if successful.

    \warning In order to work with AztecOO, any implementation of this method must 
              support the case where X and Y are the same object.
    */
  int ApplyInverse(const Epetra_MultiVector& X, Epetra_MultiVector& Y) const;
  int ApplyInverse(const N_LAS_MultiVector& X, N_LAS_MultiVector& Y) const;

    //! Returns the infinity norm of the global matrix.
    /* Returns the quantity \f$ \| A \|_\infty\f$ such that
       \f[\| A \|_\infty = \max_{1\lei\lem} \sum_{j=1}^n |a_{ij}| \f].

       \warning This method must not be called unless HasNormInf() returns true.
    */ 
  double NormInf() const;

  //! Returns a character string describing the operator
  const char * Label() const;

  //! Returns the current UseTranspose setting.
  bool UseTranspose() const;

  //! Returns true if the \e this object can provide an approximate Inf-norm, false otherwise.
  bool HasNormInf() const;

  //! Returns a pointer to the Epetra_Comm communicator associated with this operator.
  const Epetra_Comm & Comm() const;

  //! Returns the Epetra_Map object associated with the domain of this operator.
  const Epetra_Map & OperatorDomainMap() const;

  //! Returns the Epetra_Map object associated with the range of this operator.
  const Epetra_Map & OperatorRangeMap() const;

private:
  bool isInitialized_;
  int N_, M_;
  std::vector<Teuchos::RCP<Epetra_LinearProblem> > epetraProblems_;
  std::vector<Teuchos::RCP<Amesos_BaseSolver> > amesosSolvers_;
  Teuchos::RCP<N_LAS_HBBuilder> hbBuilder_;
};

// Non-member constructor
RCP<N_LAS_HBBlockJacobiEpetraOperator> blockJacobiOperator(
    const std::vector<Teuchos::RCP<Epetra_LinearProblem> >& epetraProblems,
    const std::vector<Teuchos::RCP<Amesos_BaseSolver> >& amesosSolvers,
    const Teuchos::RCP<N_LAS_HBBuilder>& hbBuilder
    );

#endif // Xyce_N_LAS_HBBlockJacobiEpetraOperator_h

