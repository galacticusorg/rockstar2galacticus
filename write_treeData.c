#include <stdlib.h>

#include "hdf5.h"
#include "tree.h"

int write_treeData(char * filename, struct forest ** forests, int nForests) {

	hid_t file_id;
	hid_t group_id;
	hid_t dataspace_id;
	hid_t dataset_id;

	
	int i;
	long int * buf = malloc(nForests*sizeof(long int));

	file_id = H5Fopen(filename , H5F_ACC_RDWR, H5P_DEFAULT);

	group_id = H5Gopen(file_id, "/forestIndex");

	dataset_id = H5Dopen(file_id,"/forestIndex/firstNode");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nForests;i++) {
		buf[i] = (*forests)[i].galacticusOffset;
	}
	// was native_llong before
	H5Dwrite(dataset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	dataset_id = H5Dopen(file_id,"/forestIndex/numberOfNodes");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nForests;i++) {
		buf[i] = (*forests)[i].nHalos;
	}
	H5Dwrite(dataset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	dataset_id = H5Dopen(file_id,"/forestIndex/treeIndex");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nForests;i++) {
		buf[i] = (*forests)[i].forestId;
	}
	H5Dwrite(dataset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	H5Gclose(group_id);

  	free(buf);

	H5Fclose(file_id);

	return 0;

}
