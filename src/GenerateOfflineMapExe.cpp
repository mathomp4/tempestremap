///////////////////////////////////////////////////////////////////////////////
///
///	\file    GenerateOfflineMapExe.cpp
///	\author  Paul Ullrich
///	\version June 29, 2015
///
///	<remarks>
///		Copyright 2000-2014 Paul Ullrich
///
///		This file is distributed as part of the Tempest source code package.
///		Permission is granted to use, copy, modify and distribute this
///		source code and its documentation under the terms of the GNU General
///		Public License.  This software is provided "as is" without express
///		or implied warranty.
///	</remarks>

#include "Announce.h"
#include "CommandLine.h"
#include "Exception.h"
#include "GridElements.h"
#include "OfflineMap.h"

#include "TempestRemapAPI.h"


///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

	// Input mesh file
	std::string strInputMesh;

	// Overlap mesh file
	std::string strOverlapMesh;

	// Input metadata file
	std::string strInputMeta;

	// Output metadata file
	std::string strOutputMeta;

	// Input data type
	std::string strInputType;

	// Output data type
	std::string strOutputType;

	// Output mesh file
	std::string strOutputMesh;

	// Order of polynomial in each element
	int nPin;

	// Order of polynomial in each output element
	int nPout;

	// Use bubble on interior of spectral element nodes
	bool fBubble;

	// Enforce monotonicity
	bool fMonotoneType1;

	// Enforce monotonicity
	bool fMonotoneType2;

	// Enforce monotonicity
	bool fMonotoneType3;

	// Volumetric remapping
	bool fVolumetric;

	// No conservation
	bool fNoConservation;

	// Turn off checking for conservation / consistency
	bool fNoCheck;

	// Variable list
	std::string strVariables;

	// Output map file
	std::string strOutputMap;

	// Input data file
	std::string strInputData;

	// Output data file
	std::string strOutputData;

	// Name of the ncol variable
	std::string strNColName;

	// Output as double
	bool fOutputDouble;

	// List of variables to preserve
	std::string strPreserveVariables;

	// Preserve all non-remapped variables
	bool fPreserveAll;

	// Fill value override
	double dFillValueOverride;

	// Input mesh contains concave elements
	bool fInputConcave;

	// Output mesh contains concave elements
	bool fOutputConcave;

	// Parse the command line
	BeginCommandLine()
		CommandLineString(strInputMesh, "in_mesh", "");
		CommandLineString(strOutputMesh, "out_mesh", "");
		CommandLineString(strOverlapMesh, "ov_mesh", "");
		CommandLineString(strInputMeta, "in_meta", "");
		CommandLineString(strOutputMeta, "out_meta", "");
		CommandLineStringD(strInputType, "in_type", "fv", "[fv|cgll|dgll]");
		CommandLineStringD(strOutputType, "out_type", "fv", "[fv|cgll|dgll]");

		// Optional arguments
		CommandLineInt(nPin, "in_np", 4);
		CommandLineInt(nPout, "out_np", 4);
		CommandLineBool(fBubble, "bubble");
		CommandLineBool(fMonotoneType1, "mono");
		CommandLineBool(fMonotoneType2, "mono2");
		CommandLineBool(fMonotoneType3, "mono3");
		CommandLineBool(fVolumetric, "volumetric");
		CommandLineBool(fNoConservation, "noconserve");
		CommandLineBool(fNoCheck, "nocheck");
		CommandLineString(strVariables, "var", "");
		CommandLineString(strOutputMap, "out_map", "");
		CommandLineString(strInputData, "in_data", "");
		CommandLineString(strOutputData, "out_data", "");
		CommandLineString(strNColName, "ncol_name", "ncol");
		CommandLineBool(fOutputDouble, "out_double");
		CommandLineString(strPreserveVariables, "preserve", "");
		CommandLineBool(fPreserveAll, "preserveall");
		CommandLineDouble(dFillValueOverride, "fillvalue", 0.0);
		CommandLineBool(fInputConcave, "in_concave");
		CommandLineBool(fOutputConcave, "out_concave");

		ParseCommandLine(argc, argv);
	EndCommandLine(argv)

	AnnounceBanner();

	int fMonotoneTypeID=0;
	if (fMonotoneType1) fMonotoneTypeID=1;
	if (fMonotoneType2) fMonotoneTypeID=2;
	if (fMonotoneType3) fMonotoneTypeID=3;

	// Call the actual mesh generator
    OfflineMap mapRemap;
	int err = GenerateOfflineMap(  mapRemap, strInputMesh, strOutputMesh, strOverlapMesh,
                                    strInputMeta, strOutputMeta,
                                    strInputType, strOutputType,
                                    nPin, nPout,
                                    fBubble, fMonotoneTypeID,
                                    fVolumetric, fNoConservation, fNoCheck,
                                    strVariables, strOutputMap, strInputData, strOutputData,
                                    strNColName, fOutputDouble, strPreserveVariables, fPreserveAll, dFillValueOverride,
                                    fInputConcave, fOutputConcave );

	if (err) exit(err);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
