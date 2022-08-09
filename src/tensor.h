#ifndef TENSOR
#define TENSOR

struct tensor {
	int dimension;
	int order;
	float* array;
};

extern struct tensor* init_tensor(int dimension,int order);
extern void print_tensor(struct tensor* data);
#endif