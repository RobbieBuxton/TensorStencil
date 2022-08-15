#ifndef EIGEN_SCALE
#define EIGEN_SCALE

#include "tensor.h"
#include "eigen_decomposition.h"

extern struct tensor* eigen_scale(struct tensor* target, struct eigen_decomposition** decompositions, int iterations);
#endif