#ifndef EIGEN_DECOMPOSITON 
#define EIGEN_DECOMPOSITON 

struct eigen_decomposition {
	//Left should be transposed before used.
	int order;
	struct tensor* in; 
	float* eigenvalues; 
	struct tensor* out; 
};

extern void destroy_eigen_decomposition(struct eigen_decomposition *target);
extern struct eigen_decomposition* eigen_decompose_toeplitz(float *axis, int stencil_order, int tensor_order);
extern struct eigen_decomposition* init_eigen_decomposition(int tensor_order);
extern void print_eigen_decomposition(struct eigen_decomposition* eigen_decomposition);
extern float sdot_(int *, float *, int *, float *, int *);
#endif