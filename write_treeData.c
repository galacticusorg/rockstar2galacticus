#include <stdlib.h>

#include "hdf5.h"
#include "tree.h"

int write_treeData(char * filename, struct nshTree ** nshTrees, int nTrees) {

	hid_t file_id;
	hid_t group_id;
	hid_t dataspace_id;
	hid_t dataset_id;

	
	int i;
	long long int * buf = malloc(nTrees*sizeof(long long int));

	file_id = H5Fopen(filename , H5F_ACC_RDWR, H5P_DEFAULT);

	group_id = H5Gopen(file_id, "/treeIndex");

	dataset_id = H5Dopen(file_id,"/treeIndex/firstNode");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nTrees;i++) {
		buf[i] = (*nshTrees)[i].firstNode;
	}
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	dataset_id = H5Dopen(file_id,"/treeIndex/numberOfNodes");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nTrees;i++) {
		buf[i] = (*nshTrees)[i].numberOfNodes;
	}
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	dataset_id = H5Dopen(file_id,"/treeIndex/treeIndex");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nTrees;i++) {
		buf[i] = (*nshTrees)[i].treeIndex;
	}
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	H5Gclose(group_id);

  	free(buf);

	H5Fclose(file_id);

	return 0;

}