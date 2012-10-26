#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"

int countNodes(FILE* file) {	
	int i=0;
	char line [800];
	fpos_t tmp;
	while( fgets(line,sizeof(line),file) !=NULL)  {
		if(line[0]=='#') {
			break;
		}
		i++;
		fgetpos(file, &tmp);
	}
	fsetpos (file,&tmp);
	return i;
}

int get_treeInfo(char * filename, struct cTree ** cTrees, int * nTrees)
{

	int i,j;

	FILE * file;
	file=fopen(filename,"r");
	if(file==0) {
		printf("Could not find file %s\n", filename);
		return 1;
	}

	char line[800];
	// Determine the number of data fields for each node
	// (In the first line of the input file there is a list
	// of the field names)
	fgets(line,800,file);
	strtok(line, " ");
	int nfields = 0;
	printf("  %s contains the following data-fields for each node:\n",filename);
	char * fieldname;
	while( (fieldname=strtok(NULL," ")) )  {
		nfields++;
		printf("	%s\n", fieldname);
	}
	printf("  %s has %i data-fields per node.\n",filename,nfields);

	// Find out the number of trees
	// This is the number below the line starting with the program
	// version name.
	do
	{
		fgets(line,800,file);
	} while (strncmp(line,"#Consistent",10)!=0);
	
	fscanf(file,"%i \n", nTrees);
	printf("  %s contains %i trees.\n",filename,*nTrees);	

	// allocate the vector where each entry corresponds to the info
	// about on tree
    (*cTrees) = malloc(*nTrees*sizeof(struct cTree));

	// Start gathering information about the trees
	int n;
    for(n=0;n<*nTrees;n++) {

		fgets(line,800,file);
		
		char * pch = NULL;
		pch = strtok(line," ");
		pch = strtok(NULL," ");

		(*cTrees)[n].mainNodeId = atoi(pch);
		fgetpos(file, &(*cTrees)[n].startPos);
		fgets(line,800,file);
		pch = strtok(line," ");
		for(i=0;i<6;i++) {
			pch = strtok(NULL," ");
			if(i==4) (*cTrees)[n].parentId = atoi(pch);
			if(i==5) (*cTrees)[n].upId = atoi(pch);
		}
		fsetpos (file,&(*cTrees)[n].startPos);
		(*cTrees)[n].nNodes = countNodes(file);

    }
	
	fclose(file);

	printf("  Correcting upIds\n");
	/* Get upmost Id, because a subhalo can have an upId         */
	/* which is not a distinct halo if the subhalo lies out      */
	/* of the virial radius of the host halo of the upId halo    */
 	/* therefore make a loop to determine the actual upmost halo */
	for(n=0; n<*nTrees;n++) {
		(*cTrees)[n].upmostId=(*cTrees)[n].upId;
	}
	int cnt;
	int cnt2=0;
	do
	{
		cnt = 0;
		for(i=0; i<*nTrees;i++) {
			for(j=0; j<*nTrees;j++) {
				if( (*cTrees)[i].upmostId == (*cTrees)[j].mainNodeId) {
					if((*cTrees)[j].parentId!=-1) {
						(*cTrees)[i].upmostId=(*cTrees)[j].upId;
						cnt += 1;
					}
				}

			}
		}
		cnt2 += 1;
		
	} while (cnt!=0);
	printf("  %i iteration(s) needed to get upmost Halos.\n",cnt2);

	return 0;
}

