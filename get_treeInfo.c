#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "searchFunctions.h"

int get_treeInfo(char * inputPath, char * locationsPath, char * forestsPath,struct treeData ** returnTrees, int * returnNTrees, struct forest ** returnForests, int * returnNForests) {


	// open the locations.dat file so that we get information
	// about the trees
	char filename[200];
	sprintf(filename, "%s",locationsPath);
	FILE * file;
	file=fopen(filename,"r");
	if(file==0) {
		printf("Could not find file %s\n", filename);
		return 1;
	}
	printf("Locations file is %s\n",filename);

	char line[800];
	// count the lines in the locations file
	int nLines = 0;
	while( fgets(line,sizeof(line),file) !=NULL)  {
		nLines++;	
	}
	printf("There are %i lines in file %s\n", nLines, filename);
	rewind(file);

	// the number of lines minus the one header file
	// is the number of trees
	int nTrees = nLines-1;

	// make the array for the trees
	struct treeData * trees = malloc(nTrees*sizeof(struct treeData));

	// read the contents of the file
	
	// skip first header line
	fgets(line,800,file);
	char * pch;
	long int treeRootId;
	int fileId;
	long int offset;
	long int forestId;
	char treeFileName[800];

	int cnt = 0;

	while( fgets(line,sizeof(line),file) !=NULL)  {
		pch = strtok(line," ");
		trees[cnt].treeRootId =atoll(pch);
		pch = strtok(NULL," ");
		trees[cnt].fileId = atoi(pch);
		pch = strtok(NULL," ");
		trees[cnt].offset = atoll(pch);
		pch = strtok(NULL,"\n");
		strcpy(trees[cnt].treeFileName,pch);
		cnt++;
	}
	
	// test
	//int i;
	//for(i=0;i<nTrees;i++) {
	//	printf("%ld %i %ld %s", trees[i].treeRootId, trees[i].fileId, trees[i].offset, trees[i].treeFileName);
	//}
	fclose(file);

	// open the forest.list to assign the forest ids to the trees
	sprintf(filename, "%s",forestsPath);
	file=fopen(filename,"r");
	if(file==0) {
		printf("Could not find file %s\n", filename);
		return 1;
	}
	printf("Forests list file is %s\n",filename);
	// count the lines
	nLines = 0;
	while( fgets(line,sizeof(line),file) !=NULL)  {
		nLines++;	
	}
	if ( nLines-1 != nTrees) {
		printf("Error: forests.list and locations.dat have different length\n");
		return -1;
	}
	rewind(file);



	struct forestListElement * forestList = malloc(nTrees*sizeof(struct forestListElement));
	// skip first line
	fgets(line,800,file);
	cnt = 0;
	while( fgets(line,sizeof(line),file) !=NULL)  {
		pch = strtok(line," ");
		forestList[cnt].treeRootId =atoll(pch);
		pch = strtok(NULL," ");
		forestList[cnt].forestId = atoll(pch);
		cnt++;
	}

	//int i;
	//for(i=0;i<nTrees;i++) {
	//	printf("%ld %ld \n", forestList[i].treeRootId, forestList[i].forestId);
	//}
	//fclose(file);

	// search the forest list

	// first sort the forestList
	qsort(forestList,nTrees, sizeof(struct forestListElement),compareForestTreeRootId);
	// for every tree, get the forestId
	struct forestListElement * tmpFLE;
	long int searchId;
	int i;
	for(i=0;i<nTrees;i++) {
		searchId = trees[i].treeRootId;
		tmpFLE = bsearch(&searchId, forestList, nTrees, sizeof(struct forestListElement), searchForestTreeRootId);
		if (tmpFLE ==NULL) {
			printf("Error: No matching treeRootId found in forests.list\n");
			return -1;
		}
		trees[i].forestId = (*(struct forestListElement *)tmpFLE).forestId;
	}

	//for(i=0;i<nTrees;i++) {
	//	printf("%ld %i %ld %ld %s", trees[i].treeRootId, trees[i].fileId,
	//		 trees[i].offset, trees[i].forestId, trees[i].treeFileName);
	//}

	// search for unique forests
	qsort(forestList,nTrees, sizeof(struct forestListElement),compareForestForestId);
	int nForests = 1;
	for(i=0;i<nTrees-1;i++) {
		if(forestList[i].forestId == forestList[i+1].forestId)
			continue;
		else
			nForests++;
	}

	printf("There are %i forests\n",nForests);

	// count how many trees are there per forest
	struct forest * forests = malloc(nForests*sizeof(struct forest));

	for(i=0;i<nForests;i++) {
		forests[i].nTrees = 1;
	}

	int cntForest = 0;
	forests[cntForest].forestId = forestList[0].forestId;
	for(i=0;i<nTrees-1;i++) {
		if(forestList[i].forestId == forestList[i+1].forestId)
			forests[cntForest].nTrees++;
		else {
			cntForest++;
			// also set the forestId
			forests[cntForest].forestId = forestList[i+1].forestId;
		}
	}
	for(i=0;i<nForests;i++) {
		forests[i].treeRootIds = malloc(forests[i].nTrees*sizeof(long int));
		forests[i].cnt = 0;
	}

	// Fill the treeRootIds array of the forests
	qsort(forests,nForests, sizeof(struct forest),compareForest);
	struct forest * tmpForest;

	int tmpCnt;
	for(i=0;i<nTrees;i++) {

		searchId = trees[i].forestId;

		tmpForest = bsearch(&searchId, forests, nForests, sizeof(struct forest), searchForestForestId);
		if (tmpForest ==NULL) {
				printf("Error: No matching forestId found in locations.list\n");
				return -1;
		}

		tmpCnt = tmpForest->cnt;
		tmpForest->treeRootIds[tmpCnt] = trees[i].treeRootId;
		tmpForest->cnt += 1;
	}
	

	int check = 0;
	for(i=0;i<nForests;i++) {
		//printf("%ld %i \n", forests[i].forestId, forests[i].nTrees);
		check += forests[i].nTrees;
	}
	printf("Number of trees in forests: %i\n",check);

	// sort the trees again after the treeRootId
	qsort(trees,nTrees, sizeof(struct treeData),compareTreeTreeRootId);

	// get the number of halos for the trees by counting the
	// lines until the next tree
	for(i=0;i<nTrees;i++) {
		sprintf(filename, "%s%s",inputPath,trees[i].treeFileName);
		file=fopen(filename,"r");
		if(file==0) {
			printf("Could not find file %s\n", filename);
			return 1;
		}
		fseek(file,trees[i].offset,SEEK_SET);
		cnt = 0;
		while( fgets(line,sizeof(line),file) !=NULL)  {
			if(line[0]=='#') {
				break;
			}
			cnt++;
		}
		trees[i].nHalos = cnt;
		fclose(file);
	}
	// check
	long int lcnt = 0;
	for(i=0;i<nTrees;i++) {
		lcnt+=trees[i].nHalos;
	}	
	printf("Total halo number from trees %ld\n",lcnt);


	// get total halo number for the forests
	struct treeData * tmpTree;
	int ntcnt = 0;
	int j;
	for(i=0;i<nForests;i++) {
		forests[i].nHalos = 0;
		//printf("Forest: %ld\n",forests[i].forestId);
		for(j=0;j<forests[i].nTrees;j++){
			ntcnt++;
			searchId = forests[i].treeRootIds[j];
			tmpTree = bsearch(&searchId, trees, nTrees, sizeof(struct treeData), searchTreeTreeRootId);
			if (tmpTree ==NULL) {
				printf("Error: No matching treeRootId found in locations.list\n");
				return -1;
			}
			//printf("  SearchId: %ld\n",searchId);
			//printf("  Found   : %ld\n",tmpTree->treeRootId);
			//printf("  Forest  : %ld\n",tmpTree->forestId);
			//printf("  nHalos  : %i\n",tmpTree->nHalos);
			forests[i].nHalos += tmpTree->nHalos;
		}
	}
	printf("Total number of trees %i\n",ntcnt);
	// sort the forests according to their halo number
	qsort(forests,nForests, sizeof(struct forest),compareForestNHalos);
	lcnt = 0;
	for(i=0;i<nForests;i++) {
		lcnt+=forests[i].nHalos;
	}	
	printf("Total halo number from forests %i\n",lcnt);

	// set the return Pointers
	*returnTrees         = trees;
	*returnNTrees        = nTrees;
	*returnForests       = forests;
	*returnNForests      = nForests;

	return 0;
}


// compare functions
int compareForestTreeRootId (const void * p1, const void * p2) {
	if ( (*(struct forestListElement*)p1).treeRootId <  (*(struct forestListElement*)p2).treeRootId) return -1;
	if ( (*(struct forestListElement*)p1).treeRootId == (*(struct forestListElement*)p2).treeRootId) return 0;
	if ( (*(struct forestListElement*)p1).treeRootId >  (*(struct forestListElement*)p2).treeRootId) return 1;
}

int compareForestNHalos (const void * p1, const void * p2) {
	if ( (*(struct forest*)p1).nHalos <  (*(struct forest*)p2).nHalos) return 1;
	if ( (*(struct forest*)p1).nHalos == (*(struct forest*)p2).nHalos) return 0;
	if ( (*(struct forest*)p1).nHalos >  (*(struct forest*)p2).nHalos) return -1;
}

int compareTreeForestId (const void * p1, const void * p2) {
	if ( (*(struct treeData*)p1).forestId <  (*(struct treeData*)p2).forestId) return -1;
	if ( (*(struct treeData*)p1).forestId == (*(struct treeData*)p2).forestId) return 0;
	if ( (*(struct treeData*)p1).forestId >  (*(struct treeData*)p2).forestId) return 1;
}

int compareTreeTreeRootId (const void * p1, const void * p2) {
	if ( (*(struct treeData*)p1).treeRootId <  (*(struct treeData*)p2).treeRootId) return -1;
	if ( (*(struct treeData*)p1).treeRootId == (*(struct treeData*)p2).treeRootId) return 0;
	if ( (*(struct treeData*)p1).treeRootId >  (*(struct treeData*)p2).treeRootId) return 1;
}

int compareForestForestId (const void * p1, const void * p2) {
	if ( (*(struct forestListElement*)p1).forestId <  (*(struct forestListElement*)p2).forestId) return -1;
	if ( (*(struct forestListElement*)p1).forestId == (*(struct forestListElement*)p2).forestId) return 0;
	if ( (*(struct forestListElement*)p1).forestId >  (*(struct forestListElement*)p2).forestId) return 1;
}

int compareForest (const void * p1, const void * p2) {
	if ( (*(struct forest*)p1).forestId <  (*(struct forest*)p2).forestId) return -1;
	if ( (*(struct forest*)p1).forestId == (*(struct forest*)p2).forestId) return 0;
	if ( (*(struct forest*)p1).forestId >  (*(struct forest*)p2).forestId) return 1;
}

int searchForestTreeRootId (const void * searchId, const void * p) {
	if ( (*(long int*)searchId) < (*(struct forestListElement*)p).treeRootId) return -1;
	if ( (*(long int*)searchId) == (*(struct forestListElement*)p).treeRootId) return 0;
	if ( (*(long int*)searchId) > (*(struct forestListElement*)p).treeRootId) return 1;
}

int searchForestForestId (const void * searchId, const void * p) {
	if ( (*(long int*)searchId) < (*(struct forest*)p).forestId) return -1;
	if ( (*(long int*)searchId) == (*(struct forest*)p).forestId) return 0;
	if ( (*(long int*)searchId) > (*(struct forest*)p).forestId) return 1;
}

int searchTreeForestId (const void * searchId, const void * p) {
	if ( (*(long int*)searchId) < (*(struct treeData*)p).forestId) return -1;
	if ( (*(long int*)searchId) == (*(struct treeData*)p).forestId) return 0;
	if ( (*(long int*)searchId) > (*(struct treeData*)p).forestId) return 1;
}

int searchTreeTreeRootId (const void * searchId, const void * p) {
	if ( (*(long int*)searchId) < (*(struct treeData*)p).treeRootId) return -1;
	if ( (*(long int*)searchId) == (*(struct treeData*)p).treeRootId) return 0;
	if ( (*(long int*)searchId) > (*(struct treeData*)p).treeRootId) return 1;
}
