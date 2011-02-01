// FEMaterial.cpp: implementation of the FEMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include <stdarg.h>
#include "FEMaterial.h"

//-----------------------------------------------------------------------------
MaterialError::MaterialError(const char* szfmt, ...)
{
	// get a pointer to the argument list
	va_list	args;

	// print to file
	va_start(args, szfmt);
	vsprintf(m_szerr, szfmt, args);
	va_end(args);
}

//-----------------------------------------------------------------------------
FEMaterial::FEMaterial()
{
	static int n = 1;
	m_szname[0] = 0;
	m_nID = -1;
}

//-----------------------------------------------------------------------------
FEParameterList* FEMaterial::GetParameterList()
{
	FEParameterList* pl = new FEParameterList;
	return pl;
}

const char* FEMaterial::GetTypeString() { return "material base"; }

//-----------------------------------------------------------------------------
// Derivative of stress w.r.t. solute concentration at material point
// Set this to zero by default because elasticity problems do not require it
mat3ds FESolidMaterial::Tangent_Concentration(FEMaterialPoint& pt)
{
	return mat3ds(0,0,0,0,0,0);
}

//-----------------------------------------------------------------------------
// Material parameters for FEElasticMaterial
BEGIN_PARAMETER_LIST(FEElasticMaterial, FEMaterial)
	ADD_PARAMETER(m_density, FE_PARAM_DOUBLE, "density");
END_PARAMETER_LIST();

void FEElasticMaterial::Init()
{
	FEMaterial::Init();

	if (m_density <= 0) throw MaterialError("Invalid material density");
}

//-----------------------------------------------------------------------------
// Material parameters for the FENestedMaterial
BEGIN_PARAMETER_LIST(FENestedMaterial, FEMaterial)
	ADD_PARAMETER(m_nBaseMat, FE_PARAM_INT, "solid_id");
END_PARAMETER_LIST();

//-----------------------------------------------------------------------------
// Material parameters for FEHydraulicPermeability
BEGIN_PARAMETER_LIST(FEHydraulicPermeability, FEMaterial)
	ADD_PARAMETER(m_phi0, FE_PARAM_DOUBLE, "phi0");
END_PARAMETER_LIST();

void FEHydraulicPermeability::Init()
{
	FEMaterial::Init();
	
	if (!INRANGE(m_phi0, 0.0, 1.0)) throw MaterialError("phi0 must be in the range 0 < phi0 <= 1");
}

//-----------------------------------------------------------------------------
// Derivative of permeability w.r.t. solute concentration at material point
// Set this to zero by default because poroelasticity problems do not require it
mat3ds FEHydraulicPermeability::Tangent_Permeability_Concentration(FEMaterialPoint& pt)
{
	return mat3ds(0,0,0,0,0,0);
}
