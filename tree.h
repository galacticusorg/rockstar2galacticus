#ifndef TREE_H
#define TREE_H

// Structure Containing information about the single trees
// the c stands for consistend tree (as output by consistent trees)
struct cTree {
	long long int nNodes;
	long long int mainNodeId;
	long long int parentId;
	long long int upId;
	long long int upmostId;
	long long int offset;		// offset which tells us position in output file
	fpos_t startPos;// start position of the tree data, used for access
};

struct nshTree {
		long long int mainNodeId;
		long long int firstNode;
		long long int numberOfNodes;
		long long int treeIndex;
};

#endif