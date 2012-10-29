#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "parameter.h"


int read_param(const char *, struct parameter *, int *);
int get_treeInfo(char *, struct cTree **, int *);
int create_galacticusFile(char *, int, int, struct parameter *, int);
int get_nodeData(char *, fpos_t, int, struct node **);
int write_nodeData(char *, struct node **, int , int );
int write_treeData(char *, struct nshTree **, int );
int write_attributes(char *, struct   parameter *, int);

int main(int argc, char const *argv[]) {


	if( argc != 2) {
		printf("Usage: ./convert <parameter file>\n");
		return 1;
	}
	int err;  

	const int maxpars = 100;
	struct parameter parameters[maxpars]; 
	int nparams;

	err = read_param(argv[1], parameters, &nparams);
	if (err !=0) {
		printf("Encountered error in read_param.c\n");
		return 1;
	}

	// search the input filename in the parameters list:
	int i;
	char filename[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"inputFile")==0) {
			strcpy(filename,parameters[i].s_val);
			break;
		}
	}


	// get information about the trees in the input file
	struct cTree * cTrees;
	int nTrees;
	get_treeInfo(filename, &cTrees, &nTrees);

	// determine the total number of nodes
	int nNodes = 0;

	for(i=0;i<nTrees;i++) {
		nNodes+=cTrees[i].nNodes;
	}
	printf("  There are %i nodes in the input file.\n", nNodes);

	// determine the number of non subhalo trees
	int nNonSubhaloTrees = 0;
	for(i=0;i<nTrees;i++) {
		if(cTrees[i].parentId==-1) {
			nNonSubhaloTrees++;
		}
	}
	printf("  There are %i non-subhalo trees in the input file.\n", nNonSubhaloTrees);

	// information about the non subhalo trees
	struct nshTree * nshTrees = malloc(nNonSubhaloTrees*sizeof(struct nshTree));
	for (i=0;i<nNonSubhaloTrees;i++) {
		nshTrees[i].treeIndex=i;
	}
	int cnt = 0;
	for (i=0;i<nTrees;i++) {
		if(cTrees[i].parentId==-1) {
			nshTrees[cnt].mainNodeId=cTrees[i].mainNodeId;
			nshTrees[cnt].numberOfNodes=cTrees[i].nNodes;
			cnt++;
		}
	}

	// if cTree belongs to the right non-subhalo tree add its nNodes
	// to the nshTree
	int j;
	for (i=0;i<nTrees;i++) {
		cTrees[i].offset=0;
	}

	int missing=0;
	for (i=0;i<nTrees;i++) {
		for(j=0;j<nNonSubhaloTrees;j++) {
			if(cTrees[i].upmostId==nshTrees[j].mainNodeId) {
				//temporary offset, firstNode has to be added when known
				cTrees[i].offset=nshTrees[j].numberOfNodes;
				nshTrees[j].numberOfNodes+=cTrees[i].nNodes;
				break;
			}
			if(cTrees[i].parentId!=-1 && j==nNonSubhaloTrees-1) {
				printf(" There is a problem in tree: mainnode: %lli upid: %lli upmostid: %lli nNodes %lli\n",cTrees[i].mainNodeId,cTrees[i].upmostId,cTrees[i].upmostId,cTrees[i].nNodes);
				missing++;
			}
		}

	}

	printf("  There are %i trees which refer to an upid which is not present in the file\n",missing);
	printf("  The converter does not handle this situation correctly at the moment\n");

	// debugging for missing halo trees
	// int cnt33=0;
	// for (i=0;i<nNonSubhaloTrees;i++) {
	// 	cnt33+=nshTrees[i].numberOfNodes;
	// }
	// printf("  Consistency check: Number of nodes nonsubhalotees: %i\n",cnt33);

	// fill firstNode field
	nshTrees[0].firstNode=0;
	for (i=1;i<nNonSubhaloTrees;i++) {
		nshTrees[i].firstNode = nshTrees[i-1].firstNode+nshTrees[i-1].numberOfNodes;
	}

	// fill offsets in the original trees
	printf("  Calculating offsets for output\n");
	for (i=0;i<nTrees;i++) {
		for(j=0;j<nNonSubhaloTrees;j++) {
			if(cTrees[i].mainNodeId==nshTrees[j].mainNodeId) {
				cTrees[i].offset=nshTrees[j].firstNode;
				break;				
			}
		}
	}
	for (i=0;i<nTrees;i++) {
		for(j=0;j<nNonSubhaloTrees;j++) {
			if(cTrees[i].upmostId==nshTrees[j].mainNodeId) {
				cTrees[i].offset+=nshTrees[j].firstNode;
				break;				
			}
		}
	
	}
	
	// initialise the galacticus hdf5 file
	char gFilename[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"galacticusOutputFile")==0) {
			strcpy(gFilename,parameters[i].s_val);
		}
	}
	create_galacticusFile(gFilename,nNodes,nNonSubhaloTrees,parameters,nparams);

	struct node * nodeData;
	printf("  Reading and writing the data\n");
	for (i = 0; i < nTrees; ++i)
	{
		nodeData = malloc(cTrees[i].nNodes*sizeof(struct node));
		get_nodeData(filename, cTrees[i].startPos, cTrees[i].nNodes, &nodeData);
		// write the nodeData into the galacticus hdf5file
		write_nodeData(gFilename, &nodeData, cTrees[i].nNodes,cTrees[i].offset);
		free(nodeData);
	}
	write_treeData(gFilename, &nshTrees, nNonSubhaloTrees);
	printf("  Writing attributes\n");
	write_attributes(gFilename, parameters,nparams);
	printf("  Finished conversion.\n");

	free(nshTrees);
	//free(cTrees);

	return 0;
}

