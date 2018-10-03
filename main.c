#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "node.h"
#include "parameter.h"
#include "searchFunctions.h"


int read_param(const char *, struct parameter *, int *);

int get_treeInfo(char * , char * , char * , struct treeData ** , int *, struct forest **, int *);
int create_galacticusFile(char *, int, int, struct parameter *, int);
int get_nodeData(char *, long int, int, struct node **);
int write_nodeData(char *, struct node **, int , int );
int write_treeData(char *, struct forest **, int );
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

	// search the inputPath in the parameters list:
	int i;
	char inputPath[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"inputPath")==0) {
			strcpy(inputPath,parameters[i].s_val);
			break;
		}
	}
	char forestsPath[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"forestsPath")==0) {
			strcpy(forestsPath,parameters[i].s_val);
			break;
		}
	}
	char locationsPath[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"locationsPath")==0) {
			strcpy(locationsPath,parameters[i].s_val);
			break;
		}
	}


	// get information about the trees in the input file
	struct treeData * trees;
	struct forest * forests;
	int nTrees;
	int nForests;
	get_treeInfo(inputPath, locationsPath, forestsPath, &trees, &nTrees, &forests, &nForests);

	// determine the total number of nodes
	int nHalos = 0;
	for(i=0;i<nTrees;i++) {
		nHalos+=trees[i].nHalos;
	}
	printf("  There are %i halos in the input file.\n", nHalos);


	//calculate the offset of the trees in the global
 	//node array in the galacticus file
 	int j;
 	long int searchId;
 	long int offsetCnt = 0;
 	struct treeData * tmpTree;
	for(i=0;i<nForests;i++) {
		for(j=0;j<forests[i].nTrees;j++) {
			searchId = forests[i].treeRootIds[j];
			tmpTree = bsearch(&searchId, trees, nTrees, sizeof(struct treeData),searchTreeTreeRootId);
			if (tmpTree ==NULL) {
				printf("Error: treeRootId %ld not found for forest %ld\n",searchId,forests[i].forestId);
				return -1;
			}
			tmpTree->galacticusOffset = offsetCnt;
			// also set the first node index in every tree
			if(j==0) {
				forests[i].galacticusOffset = offsetCnt;
			}
			offsetCnt += tmpTree->nHalos;
		}
	}

	// initialise the galacticus hdf5 file
	char gFilename[300];
	for(i=0;i<nparams;i++) {
		if(strcmp(parameters[i].name,"galacticusOutputFile")==0) {
			strcpy(gFilename,parameters[i].s_val);
		}
	}
	create_galacticusFile(gFilename,nHalos,nForests,parameters,nparams);

	struct node * nodeData;
	printf("  Reading and writing the data\n");
	char treeFilename[400];
	for (i=0; i<nForests; ++i) {
		for (j=0; j<forests[i].nTrees;j++) {
			// get the right tree
			searchId = forests[i].treeRootIds[j];
			tmpTree = bsearch(&searchId, trees, nTrees, sizeof(struct treeData),searchTreeTreeRootId);
			nodeData = malloc(tmpTree->nHalos*sizeof(struct node));	
			sprintf(treeFilename, "%s%s",inputPath,tmpTree->treeFileName);		
			get_nodeData(treeFilename, tmpTree->offset, tmpTree->nHalos, &nodeData);
			// write the nodeData into the galacticus hdf5file
			write_nodeData(gFilename, &nodeData, tmpTree->nHalos,tmpTree->galacticusOffset);
			free(nodeData);
		}
	}
	// change!!!
	write_treeData(gFilename, &forests, nForests);
	printf("  Writing attributes\n");
	write_attributes(gFilename, parameters,nparams);
	printf("  Finished conversion.\n");


	// free memory
	free(trees);
	for (i=0;i<nForests;i++) {
		free(forests[i].treeRootIds);
	}
	free(forests);

	return 0;
}


