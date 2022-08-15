#ifndef TENSOR
#define TENSOR

struct tensor {
	int dimension;
	int order;
	float* array;
};

extern struct tensor* init_tensor(int dimension,int order);
extern void print_tensor(struct tensor* data);
extern struct tensor *add_tensors(struct tensor *a, struct tensor *b);
extern void destroy_tensor(struct tensor* target);
#endif