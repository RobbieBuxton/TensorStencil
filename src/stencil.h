#ifndef STENCIL
#define STENCIL

struct star_stencil {
	int dimension;
	int order;
	float* axis; 
	struct tensor* tensors; 
};

extern struct star_stencil* init_stencil(int dimension,int order);
extern void print_stencil(struct star_stencil* stencil);
#endif