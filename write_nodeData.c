#include <stdlib.h>

#include "hdf5.h"
#include "node.h"

int write_nodeData(char * filename, struct node ** nodeData, int nNodes, int doffset) {

	hid_t file_id;
	hid_t group_id;
	hid_t dataspace_id;
	hid_t dataset_id;

	hsize_t offset = doffset;
	hsize_t stride = 1;
	hsize_t count = nNodes;
	hid_t memspace_id = H5Screate_simple(1,&count,NULL);

	// hsize_t variables for 3d quantities like position
	hsize_t offset3D[2];
	offset3D[0] = doffset;
	hsize_t count3D[2] = {nNodes,1};

	int i;
	
	// open the hdf5 file and fill it
	file_id = H5Fopen(filename , H5F_ACC_RDWR, H5P_DEFAULT);
	
	group_id = H5Gopen(file_id, "/forestTrees");

	float * buf_f = malloc(nNodes*sizeof(float));
	long long int * buf_i = malloc(nNodes*sizeof(long long int));

	// descendentIndex
	dataset_id = H5Dopen(file_id,"/forestTrees/descendentIndex");
	dataspace_id = H5Dget_space(dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_i[i] = (*nodeData)[i].descendentIndex;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, memspace_id, dataspace_id, H5P_DEFAULT, buf_i);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	// expansionFactor
	dataset_id = H5Dopen(file_id,"/forestTrees/expansionFactor");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].expansionFactor;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	// scaleRadius
	dataset_id = H5Dopen(file_id,"/forestTrees/scaleRadius");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].scaleRadius;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

	// hostIndex
	dataset_id = H5Dopen(file_id,"/forestTrees/hostIndex");
	dataspace_id = H5Dget_space(dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_i[i] = (*nodeData)[i].hostIndex;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, memspace_id, dataspace_id, H5P_DEFAULT, buf_i);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

	// nodeIndex
	dataset_id = H5Dopen(file_id,"/forestTrees/nodeIndex");
	dataspace_id = H5Dget_space(dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_i[i] = (*nodeData)[i].nodeIndex;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_LLONG, memspace_id, dataspace_id, H5P_DEFAULT, buf_i);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	// nodeMass
	dataset_id = H5Dopen(file_id,"/forestTrees/nodeMass");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].nodeMass;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

  	// spin
	dataset_id = H5Dopen(file_id,"/forestTrees/spin");
	dataspace_id = H5Dget_space (dataset_id);
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].spin;
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, &offset, &stride, &count, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

	// position
	dataset_id = H5Dopen(file_id,"/forestTrees/position");
	dataspace_id = H5Dget_space (dataset_id);
	// fill x
	offset3D[1] = 0;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].position[0];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill y
	offset3D[1] = 1;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].position[1];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill z
	offset3D[1] = 2;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].position[2];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
  	H5Dclose(dataset_id);

	// velocity
	dataset_id = H5Dopen(file_id,"/forestTrees/velocity");
	dataspace_id = H5Dget_space (dataset_id);
	// fill x
	offset3D[1] = 0;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].velocity[0];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill y
	offset3D[1] = 1;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].velocity[1];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill z
	offset3D[1] = 2;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].velocity[2];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
	H5Dclose(dataset_id);

	// angularMomentum
	dataset_id = H5Dopen(file_id,"/forestTrees/angularMomentum");
	dataspace_id = H5Dget_space (dataset_id);
	// fill x
	offset3D[1] = 0;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].angularMomentum[0];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill y
	offset3D[1] = 1;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].angularMomentum[1];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	// fill z
	offset3D[1] = 2;
	for(i=0;i<nNodes;i++) {
		buf_f[i] = (*nodeData)[i].angularMomentum[2];
	}
	H5Sselect_hyperslab(dataspace_id,H5S_SELECT_SET, offset3D, NULL, count3D, NULL);
	H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, memspace_id, dataspace_id, H5P_DEFAULT, buf_f);
	H5Sclose(dataspace_id);
	H5Dclose(dataset_id);




  	free(buf_f);
  	free(buf_i);



  	H5Gclose(group_id);
	H5Fclose(file_id);

	return 0;

}
