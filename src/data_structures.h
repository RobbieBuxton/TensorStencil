#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES
struct data {
	int dimension;
	int order;
	float* array;
};

struct star_stencil {
	int dimension;
	int order;
	float* axis; 
};
#endif