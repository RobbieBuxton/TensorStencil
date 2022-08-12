#ifndef STENCIL
#define STENCIL

struct star_stencil {
	int dimension;
	int order;
	float* axis; 
	struct tensor** tensors; 
	struct eigen_decomposition** decompositions;
};

extern struct star_stencil* init_stencil(int dimension,int order);
extern void print_stencil(struct star_stencil* stencil);
extern void init_stencil_tensors(struct star_stencil *stencil, struct tensor *data);
extern struct tensor *generate_toeplitz(float *axis, int axis_order, int tensor_order);
#endif