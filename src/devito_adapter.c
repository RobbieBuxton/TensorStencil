#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "devito_adapter.h"
#include "tensor.h"
#include "devito_stencil.h"
#include "stencil.h"

struct tensor *devito_stencil_kernel_adapter(struct tensor *tensor, struct star_stencil *stencil, int iterations, float a, float dt, float h_x, float h_y, float h_z, float *devito_timer)
{
	int padding = 1 + (stencil->max_order - 1) / 2;
	int padded_order = tensor->order + 2 * padding;
	int unpadded_order = tensor->order;

	struct tensor *padded_tensor = pad_tensor(tensor, padding);

	print_tensor(padded_tensor);

	struct dataobj u_vec;
	init_vector(&u_vec, tensor->dimension, padded_order);

	for (int i = 0; i < pow(padded_order, tensor->dimension)*2; i++)
	{
		((float *)u_vec.data)[i] = padded_tensor->array[i % (int) pow(padded_order, tensor->dimension)];
	}

	struct profiler timer;

	// float a = 1;
	// struct dataobj u_vec
	// float dt = 1;
	// float h_x = 1;
	// float h_y = 1;
	// float h_z = 1;
	int time_M = iterations - 1;
	int time_m = 0;
	// int x0_blk0_size = 1;
	int x_M = unpadded_order - 1;
	int x_m = 0;
	// int y0_blk0_size = 1;
	int y_M = unpadded_order - 1;
	int y_m = 0;
	int z_M = unpadded_order - 1;
	int z_m = 0;
	int nthreads = 6;

	Kernel(a, &u_vec, dt, h_x, h_y, h_z, time_M, time_m, x_M, x_m, y_M, y_m, z_M, z_m, nthreads, &timer);

	*devito_timer = timer.section0;

	struct tensor *result = init_tensor(tensor->dimension, padded_order);

	for (int i = 0; i < pow(padded_order, tensor->dimension); i++)
	{
		result->array[i] = ((float *)u_vec.data)[((time_M + 1) % 2) * (int)pow(padded_order, tensor->dimension) + i];
	}

	struct tensor *unpadded_result = unpad_tensor(result, padding);

	destroy_vector(&u_vec);
	destroy_tensor(result);
	destroy_tensor(padded_tensor);

	return unpadded_result;
}

void init_vector(struct dataobj *restrict vect, int dim, int order)
{
	float *data = calloc(sizeof(float), pow(order, dim) * 2);
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
