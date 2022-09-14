#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "devito_adapter.h"
#include "tensor.h"
#include "devito_stencil.h"

struct tensor *devito_stencil_kernel_adapter(struct tensor *tensor)
{

	struct dataobj u_vec;
	init_vector(&u_vec, tensor->order, tensor->dimension);

	for (int i = 0; i < pow(tensor->order,tensor->dimension); i++) {
		((float*) u_vec.data)[i] = tensor->array[i];
	}

	struct tensor *result = init_tensor(tensor->dimension, tensor->order);

	// devito_stencil_kernel();

	for (int i = 0; i < pow(tensor->order,tensor->dimension); i++) {
		result->array[i] = ((float*) u_vec.data)[i];
	}

	destroy_vector(&u_vec);

	return result;
}

void init_vector(struct dataobj *restrict vect, int order, int dim)
{
	float *data = calloc(sizeof(float), pow(order, dim));
	vect->data = data;
	vect->size = calloc(sizeof(long), dim + 1);
	vect->size[0] = dim;
	for (int i = 1; i <= dim; i++)
	{
		vect->size[i] = order;
	}
}

void destroy_vector(struct dataobj *restrict vect)
{
	free(vect->data);
	free(vect->size);
}
