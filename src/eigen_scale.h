#ifndef EIGEN_SCALE
#define EIGEN_SCALE

#include "tensor.h"
#include "stencil.h"

extern struct tensor *eigen_scale(struct tensor* target, struct star_stencil *stencil, int iterations);
#endif