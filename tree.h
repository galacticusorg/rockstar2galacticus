#ifndef TREE_H
#define TREE_H

// struct for the data in locations.dat
struct treeData {
	long int treeRootId;
	int fileId;
	long int offset; // offset in bytes in treeFileName
	long int forestId;
	char treeFileName[200];
	int nHalos;
	long int galacticusOffset; // array index in the global node array in galacticus
};

// struct for the data in forests.list
struct forestListElement {
  long int treeRootId;
  long int forestId;
  int forestWeight;   
};

struct forest {
  long int forestId;  
  int nTrees;
  int nHalos;
  int forestWeight;
  long int * treeRootIds;
  long int galacticusOffset; // index of the first node in the global node array
  int cnt; // counter which is only used for the index of treeRootIds
};

#endif
