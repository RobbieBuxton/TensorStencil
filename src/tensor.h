#ifndef TENSOR
#define TENSOR

struct tensor {
	int dimension;
	int size;
	float* array;
};

extern struct tensor* init_tensor(int dimension,int size);
extern void print_tensor(struct tensor* data);
extern struct tensor *add_tensors(struct tensor *a, struct tensor *b);
extern void destroy_tensor(struct tensor* target);
extern struct tensor *pad_tensor(struct tensor* tensor, int padding);
extern struct tensor *unpad_tensor(struct tensor *tensor, int padding);
#endif