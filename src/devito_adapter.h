#ifndef DEVITO_STENCIL_ADAPTER
#define DEVITO_STENCIL_ADAPTER

#include "tensor.h"
#include "devito_stencil.h"

extern struct tensor* devito_stencil_kernel_adapter(struct tensor* tensor);
extern void init_vector(struct dataobj *restrict vect, int order, int dim);
extern void destroy_vector(struct dataobj *restrict vect);
#endif