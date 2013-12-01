#include "hdf5.h"
#include "parameter.h"

int create_galacticusFile(char * filename, int numberNodes, int numberOfForests, const struct parameter * parameters, int nparams) {

  	hid_t file_id;
  	hid_t group_id;
  	hid_t dataspace_id;
	hid_t dataset_id;

	hsize_t nNodes = numberNodes;
	hsize_t nForests = numberOfForests;
	// hsize_t for vector data like position
	hsize_t nNodes_3D[2] = {numberNodes, 3};
	
	int i;
	file_id = H5Fcreate(filename , H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

	group_id = H5Gcreate(file_id, "/haloTrees", H5P_DEFAULT);

	// node datasets

	// descendentIndex
	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"descendentIndex",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // expansionFactor
	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"expansionFactor",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // scaleRadius
	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"scaleRadius",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // hostIndex
	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"hostIndex",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // nodeIndex
	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"nodeIndex",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

	dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"nodeMass",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // position
    dataspace_id = H5Screate_simple(2,nNodes_3D,NULL);
    dataset_id = H5Dcreate(group_id,"position",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // spin
    dataspace_id = H5Screate_simple(1,&nNodes,NULL);
    dataset_id = H5Dcreate(group_id,"spin",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // velocity
    dataspace_id = H5Screate_simple(2,nNodes_3D,NULL);
    dataset_id = H5Dcreate(group_id,"velocity",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // angular momentum
    dataspace_id = H5Screate_simple(2,nNodes_3D,NULL);
    dataset_id = H5Dcreate(group_id,"angularMomentum",H5T_IEEE_F64LE,
					dataspace_id, H5P_DEFAULT);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);



	// if makeEnvironmentarrays in parameter.cfg is set to 1
	// make the datasets for the icm environment
	int makeEnvironmentArrays=0;
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"makeEnvironmentArrays")==0) {
			makeEnvironmentArrays=parameters[i].i_val;
		}
	}

	if (makeEnvironmentArrays == 1) {
		dataspace_id = H5Screate_simple(1,&nNodes,NULL);
		dataset_id = H5Dcreate(group_id,"icmDensity",H5T_IEEE_F64LE,
			dataspace_id, H5P_DEFAULT);
		H5Dclose(dataset_id);
		H5Sclose(dataspace_id);

		dataspace_id = H5Screate_simple(2,nNodes_3D,NULL);
		dataset_id = H5Dcreate(group_id,"icmVelocity",H5T_IEEE_F64LE,
			dataspace_id, H5P_DEFAULT);
		H5Dclose(dataset_id);
		H5Sclose(dataspace_id);
	}

	H5Gclose(group_id);

	// tree datasets
	group_id = H5Gcreate(file_id, "/treeIndex", H5P_DEFAULT);

	dataspace_id = H5Screate_simple(1,&nForests,NULL);
	dataset_id = H5Dcreate(group_id,"firstNode",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
	H5Dclose(dataset_id);
	H5Sclose(dataspace_id);

	dataspace_id = H5Screate_simple(1,&nForests,NULL);
	dataset_id = H5Dcreate(group_id,"numberOfNodes",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
	H5Dclose(dataset_id);
	H5Sclose(dataspace_id);

	dataspace_id = H5Screate_simple(1,&nForests,NULL);
	dataset_id = H5Dcreate(group_id,"treeIndex",H5T_STD_I64LE,
					dataspace_id, H5P_DEFAULT);
	H5Dclose(dataset_id);
	H5Sclose(dataspace_id);

	H5Gclose(group_id);

	H5Fclose(file_id);
	return 0;
}