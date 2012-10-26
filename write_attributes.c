#include <stdlib.h>

#include "hdf5.h"
#include "node.h"
#include "parameter.h"

int write_attributes(char * filename, const struct inputParameters param) {

	hid_t file_id;
	hid_t group_id;
	hid_t attribute_id;
	hid_t atype;

	hid_t dataspace_id = H5Screate(H5S_SCALAR);

	file_id = H5Fopen(filename , H5F_ACC_RDWR, H5P_DEFAULT);

	// create the attributes in the haloTrees group
	group_id = H5Gopen(file_id, "/haloTrees");

	attribute_id = H5Acreate(group_id,"haloMassesIncludeSubhalos",
		 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.haloMassesIncludeSubhalos);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"treesAreSelfContained",
		 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.treesAreSelfContained);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"treesHaveSubhalos",
		 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.treesHaveSubhalos);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"velocitiesIncludeHubbleFlow",
		 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.velocitiesIncludeHubbleFlow);
	H5Aclose(attribute_id);

	H5Gclose(group_id);

	// create the units group and its attributes
	group_id = H5Gcreate(file_id, "/units", H5P_DEFAULT);

	attribute_id = H5Acreate(group_id,"lengthUnitsInSI", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.lengthUnitsInSI);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"lengthHubbleExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.lengthHubbleExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"lengthScaleFactorExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.lengthScaleFactorExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"massUnitsInSI", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.massUnitsInSI);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"massHubbleExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.massHubbleExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"massScaleFactorExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.massScaleFactorExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"timeUnitsInSI", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.timeUnitsInSI);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"timeHubbleExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.timeHubbleExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"timeScaleFactorExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.timeScaleFactorExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"velocityUnitsInSI", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.velocityUnitsInSI);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"velocityHubbleExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.velocityHubbleExponent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"velocityScaleFactorExponent", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.velocityScaleFactorExponent);
	H5Aclose(attribute_id);

	H5Gclose(group_id);

	// create the cosmology group and its attributes
	group_id = H5Gcreate(file_id, "/cosmology", H5P_DEFAULT);

	attribute_id = H5Acreate(group_id,"HubbleParam", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.H);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"Omega0", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.Omega0);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"OmegaLambda", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.OmegaLambda);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"OmegaBaryon", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.OmegaBaryon);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"powerSpectrumIndex", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.powerSpectrumIndex);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"sigma_8", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.sigma_8);
	H5Aclose(attribute_id);
	atype = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(atype,H5T_STR_SPACEPAD);
	H5Tset_size(atype,7);
	attribute_id = H5Acreate(group_id,"transferFunction", atype,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, atype, param.transferFunction);
	H5Aclose(attribute_id);
	H5Tclose(atype);

	H5Gclose(group_id);

	// create the group-finder group and its attributes
	group_id = H5Gcreate(file_id, "/groupFinder", H5P_DEFAULT);

	atype = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(atype,H5T_STR_SPACEPAD);
	H5Tset_size(atype,8);
	attribute_id = H5Acreate(group_id,"code", atype, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, atype, param.groupFinderCode);
	H5Aclose(attribute_id);
	H5Tclose(atype);

	attribute_id = H5Acreate(group_id,"linkingLength", H5T_IEEE_F64LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.linkingLength);
	H5Aclose(attribute_id);
	 
	attribute_id = H5Acreate(group_id,"minimumParticleNumber", H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.minimumParticleNumber);
	H5Aclose(attribute_id);
	H5Gclose(group_id);

	// create the simulation group and its attributes
	group_id = H5Gcreate(file_id, "/simulation", H5P_DEFAULT);

	attribute_id = H5Acreate(group_id,"ErrTolIntAccuracy", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.errTolIntAccuracy);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"TypeOfTimestepCriterion", H5T_STD_I32LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE, &param.typeOfTimestepCriterion);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"boxSize", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.boxSize);
	H5Aclose(attribute_id);
	atype = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(atype,H5T_STR_SPACEPAD);
	H5Tset_size(atype,8);
	attribute_id = H5Acreate(group_id,"code", atype,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, atype, param.simulationCode);
	H5Aclose(attribute_id);
	H5Tclose(atype);
	atype = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(atype,H5T_STR_SPACEPAD);
	H5Tset_size(atype,8);
	attribute_id = H5Acreate(group_id,"initialConditions", atype,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, atype,param.simulationICs);
	H5Aclose(attribute_id);
	H5Tclose(atype);
	atype = H5Tcopy(H5T_C_S1);
	H5Tset_strpad(atype,H5T_STR_SPACEPAD);
	H5Tset_size(atype,8);
	attribute_id = H5Acreate(group_id,"softeningKernel", atype,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, atype,param.softeningKernel);
	H5Aclose(attribute_id);
	H5Tclose(atype);
	attribute_id = H5Acreate(group_id,"softeningPlummerEquivalent", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.softeningPlummerEquivalent);
	H5Aclose(attribute_id);
	attribute_id = H5Acreate(group_id,"startRedshift", H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_IEEE_F64LE, &param.startRedshift);
	H5Aclose(attribute_id);

	H5Gclose(group_id);
	
	H5Fclose(file_id);
	H5Sclose(dataspace_id);

	return 0;

}