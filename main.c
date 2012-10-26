#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "node.h"
#include "parameter.h"


int read_param(const char *, struct inputParameters *);
int get_treeInfo(char *, struct cTree **, int *);
int create_galacticusFile(char *, int, int, const struct inputParameters);
int get_nodeData(char *, fpos_t, int, struct node **);
int write_nodeData(char *, struct node **, int , int );
int write_treeData(char *, struct nshTree **, int );
int write_attributes(char *, const struct inputParameters);

int main(int argc, char const *argv[]) {


	if( argc != 2) {
		printf("Usage: ./convert <parameter file>\n");
		return 1;
	}
	int err;  

	struct inputParameters param;
	err = read_param(argv[1], &param);
	if (err !=0) {
		printf("Encountered error in read_param.c\n");
		return 1;
	}

	char * filename = param.inputFile;

	// get information about the trees in the input file
	struct cTree * cTrees;
	int nTrees;
	get_treeInfo(filename, &cTrees, &nTrees);

	// determine the total number of nodes
	int nNodes = 0;
	int i;
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
	for (i=0;i<nTrees;i++) {
		for(j=0;j<nNonSubhaloTrees;j++) {
			if(cTrees[i].upmostId==nshTrees[j].mainNodeId) {
				//temporary offset, firstNode has to be added when known
				cTrees[i].offset=nshTrees[j].numberOfNodes;
				nshTrees[j].numberOfNodes+=cTrees[i].nNodes;

				break;
			}
		}
	}

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
	char * gFilename = param.galacticusOutputFile;
	create_galacticusFile(gFilename,nNodes,nNonSubhaloTrees,param);

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
	write_attributes(gFilename, param);
	printf("  Finished conversion.\n");

	free(nshTrees);
	free(cTrees);

	return 0;
}

