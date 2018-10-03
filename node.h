#ifndef NODE_H
#define NODE_H

struct node {
	// consistent-trees name
	long long int   nodeIndex;		// id;
	float expansionFactor;			// scale;
	long long int   hostIndex;		// pid;
	long long int   descendentIndex;// desc_id;
	float nodeMass;					// mVir;
	float scaleRadius;				// scaleRadius
	float position[3];				// pos[3];
	float velocity[3];				// v[3];
	float angularMomentum[3];		// l[3];
	float spin;						// spin;
  
};


#endif