#pragma once
#include "FGMRESSolver.h"
#include "SchurPreconditioner.h"

//-----------------------------------------------------------------------------
class FGMRES_Schur_Solver : public FGMRESSolver
{
public:
	//! constructor
	FGMRES_Schur_Solver(FEModel* fem);

	//! Return a sparse matrix compatible with this solver
	SparseMatrix* CreateSparseMatrix(Matrix_Type ntype) override;

	// this is used to build the preconditioner
	bool Factor() override;

	void ZeroDBlock(bool b);

private:
	SchurPreconditioner*	m_PC;		//!< the preconditioner
};
