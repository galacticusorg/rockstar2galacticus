#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

int get_nodeData(char * filename, long int startPos, int nNodes, struct node ** nodeData)
{

	FILE * file;
	file=fopen(filename,"r");
	if(file==0) {
		printf("Could not find file %s\n", filename);
		return 1;
	}

	// move to the the start of the specified tree
	fseek(file,startPos,SEEK_SET);
	int i,n;
	char * pch;
	char line[800];

	// Read the data
	// field     position in line
	// expansionFactor	0
	// nodeIndex		1
	// descendentIndex	3
	// hostIndex		6
	// nodeMass			9
	// scaleRadius		12
	// position			17-19
	// velocity			20-22
	// angularMomentum	23-25
	// spin				26

	for(n=0;n<nNodes;n++) {
		fgets(line,800,file);
		pch = strtok(line," "); // first data field (index 0)
		(*nodeData)[n].expansionFactor = atof(pch);
		for(i=1;i<27;i++) {
			pch = strtok(NULL," ");
			if(i==1) (*nodeData)[n].nodeIndex = atoll(pch);
			if(i==3) (*nodeData)[n].descendentIndex = atoll(pch);
			if(i==5) (*nodeData)[n].hostIndex = atoll(pch);
			if(i==9) (*nodeData)[n].nodeMass = atof(pch);
			if(i==12)(*nodeData)[n].scaleRadius = atof(pch);
			if(i==17)(*nodeData)[n].position[0] = 1000.0*atof(pch);
			if(i==18)(*nodeData)[n].position[1] = 1000.0*atof(pch);
			if(i==19)(*nodeData)[n].position[2] = 1000.0*atof(pch);
			if(i==20)(*nodeData)[n].velocity[0] = atof(pch);
			if(i==21)(*nodeData)[n].velocity[1] = atof(pch);
			if(i==22)(*nodeData)[n].velocity[2] = atof(pch);
			if(i==23)(*nodeData)[n].angularMomentum[0] = 1000.0*atof(pch);
			if(i==24)(*nodeData)[n].angularMomentum[1] = 1000.0*atof(pch);
			if(i==25)(*nodeData)[n].angularMomentum[2] = 1000.0*atof(pch);
			if(i==26)(*nodeData)[n].spin = atof(pch);
		}

	}

	// In Galacticus, if a node has no parent node, its parentId
	// should be its nodeId. In Rockstar, its parentId would be -1
	// we therefore have to change this
	for(i=0;i<nNodes;i++) {
		if ((*nodeData)[i].hostIndex==-1)
			(*nodeData)[i].hostIndex=(*nodeData)[i].nodeIndex;
	}

	fclose(file);


	return 0;
}