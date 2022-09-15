#ifndef DEVITO_STENCIL_ADAPTER
#define DEVITO_STENCIL_ADAPTER

#include "tensor.h"
#include "devito_stencil.h"
#include "stencil.h"

extern struct tensor* devito_stencil_kernel_adapter(struct tensor* tensor, struct star_stencil* stencil, int iterations);
extern void init_vector(struct dataobj *restrict vect, int dim, int order);
extern void destroy_vector(struct dataobj *restrict vect);
#endif