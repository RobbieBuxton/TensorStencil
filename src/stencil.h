#ifndef STENCIL
#define STENCIL

struct star_stencil {
	int dimension;
	int max_order;
	float* axis; 
	//Axis transformation tensors 
	struct tensor** tensors; 
	struct tensor** in; 
	float *eigenvalues; 
	struct tensor** out;
};

extern int get_axis_order(float *axis, int max_order); 
extern void destroy_stencil(struct star_stencil* target);
extern struct star_stencil* init_stencil(int dimension,int order);
extern void print_stencil(struct star_stencil* stencil);
extern void init_stencil_tensors(struct star_stencil *stencil, struct tensor *data);
extern struct tensor *generate_toeplitz(float *axis, int axis_order, int tensor_order);
#endif