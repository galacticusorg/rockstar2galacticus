#include <stdlib.h>
#include <string.h>

#include "hdf5.h"
#include "node.h"
#include "parameter.h"

int write_attributes(char * filename, const struct parameter * parameters, int nparams) {

	hid_t file_id;
	hid_t group_id;
	hid_t attribute_id;
	hid_t atype;

	hid_t dataspace_id = H5Screate(H5S_SCALAR);

	file_id = H5Fopen(filename , H5F_ACC_RDWR, H5P_DEFAULT);

	int i;

	// Write format version number
	int formatVersion = 2;
	//group_id = H5Gopen(file_id, "/");
	attribute_id = H5Acreate(file_id,"formatVersion",
				 H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
	H5Awrite(attribute_id, H5T_STD_I32LE,&formatVersion);
	H5Aclose(attribute_id);
	
	// create the attributes in the forestTrees group
	group_id = H5Gopen(file_id, "/forestTrees");

	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].group,"/forestTrees")==0) {
			if(parameters[i].dtype==INT) {
				attribute_id = H5Acreate(group_id,parameters[i].name,
					 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_STD_I32LE, &parameters[i].i_val);
				H5Aclose(attribute_id);
			}
			else if(parameters[i].dtype==DOUBLE) {
				attribute_id = H5Acreate(group_id,parameters[i].name, H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_IEEE_F64LE, &parameters[i].d_val);
				H5Aclose(attribute_id);

			}
			else if(parameters[i].dtype==STRING) {
				atype = H5Tcopy(H5T_C_S1);
				H5Tset_strpad(atype,H5T_STR_SPACEPAD);
				H5Tset_size(atype,30);
				attribute_id = H5Acreate(group_id,parameters[i].name, atype,
											dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, atype, parameters[i].s_val);
				H5Aclose(attribute_id);
				H5Tclose(atype);
			}
		}
	}



	H5Gclose(group_id);

	// create the units group and its attributes
	group_id = H5Gcreate(file_id, "/units", H5P_DEFAULT);

	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].group,"/units")==0) {
			if(parameters[i].dtype==INT) {
				attribute_id = H5Acreate(group_id,parameters[i].name,
					 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_STD_I32LE, &parameters[i].i_val);
				H5Aclose(attribute_id);
			}
			else if(parameters[i].dtype==DOUBLE) {
				attribute_id = H5Acreate(group_id,parameters[i].name, H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_IEEE_F64LE, &parameters[i].d_val);
				H5Aclose(attribute_id);

			}
			else if(parameters[i].dtype==STRING) {
				atype = H5Tcopy(H5T_C_S1);
				H5Tset_strpad(atype,H5T_STR_SPACEPAD);
				H5Tset_size(atype,30);
				attribute_id = H5Acreate(group_id,parameters[i].name, atype,
											dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, atype, parameters[i].s_val);
				H5Aclose(attribute_id);
				H5Tclose(atype);
			}
		}
	}



	H5Gclose(group_id);

	// create the cosmology group and its attributes
	group_id = H5Gcreate(file_id, "/cosmology", H5P_DEFAULT);

	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].group,"/cosmology")==0) {
			if(parameters[i].dtype==INT) {
				attribute_id = H5Acreate(group_id,parameters[i].name,
					 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_STD_I32LE, &parameters[i].i_val);
				H5Aclose(attribute_id);
			}
			else if(parameters[i].dtype==DOUBLE) {
				attribute_id = H5Acreate(group_id,parameters[i].name, H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_IEEE_F64LE, &parameters[i].d_val);
				H5Aclose(attribute_id);

			}
			else if(parameters[i].dtype==STRING) {
				atype = H5Tcopy(H5T_C_S1);
				H5Tset_strpad(atype,H5T_STR_SPACEPAD);
				H5Tset_size(atype,30);
				attribute_id = H5Acreate(group_id,parameters[i].name, atype,
											dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, atype, parameters[i].s_val);
				H5Aclose(attribute_id);
				H5Tclose(atype);
			}
		}
	}

	

	H5Gclose(group_id);

	// create the group-finder group and its attributes
	group_id = H5Gcreate(file_id, "/groupFinder", H5P_DEFAULT);

	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].group,"/groupFinder")==0) {
			if(parameters[i].dtype==INT) {
				attribute_id = H5Acreate(group_id,parameters[i].name,
					 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_STD_I32LE, &parameters[i].i_val);
				H5Aclose(attribute_id);
			}
			else if(parameters[i].dtype==DOUBLE) {
				attribute_id = H5Acreate(group_id,parameters[i].name, H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_IEEE_F64LE, &parameters[i].d_val);
				H5Aclose(attribute_id);

			}
			else if(parameters[i].dtype==STRING) {
				atype = H5Tcopy(H5T_C_S1);
				H5Tset_strpad(atype,H5T_STR_SPACEPAD);
				H5Tset_size(atype,30);
				attribute_id = H5Acreate(group_id,parameters[i].name, atype,
											dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, atype, parameters[i].s_val);
				H5Aclose(attribute_id);
				H5Tclose(atype);
			}
		}
	}

	H5Gclose(group_id);

	// create the simulation group and its attributes
	group_id = H5Gcreate(file_id, "/simulation", H5P_DEFAULT);


	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].group,"/simulation")==0) {
			if(parameters[i].dtype==INT) {
				attribute_id = H5Acreate(group_id,parameters[i].name,
					 						H5T_STD_I32LE, dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_STD_I32LE, &parameters[i].i_val);
				H5Aclose(attribute_id);
			}
			else if(parameters[i].dtype==DOUBLE) {
				attribute_id = H5Acreate(group_id,parameters[i].name, H5T_IEEE_F64LE,
								dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, H5T_IEEE_F64LE, &parameters[i].d_val);
				H5Aclose(attribute_id);

			}
			else if(parameters[i].dtype==STRING) {
				atype = H5Tcopy(H5T_C_S1);
				H5Tset_strpad(atype,H5T_STR_SPACEPAD);
				H5Tset_size(atype,30);
				attribute_id = H5Acreate(group_id,parameters[i].name, atype,
											dataspace_id,H5P_DEFAULT);
				H5Awrite(attribute_id, atype, parameters[i].s_val);
				H5Aclose(attribute_id);
				H5Tclose(atype);
			}
		}
	}



	H5Gclose(group_id);
	
	H5Fclose(file_id);
	H5Sclose(dataspace_id);

	return 0;

}
