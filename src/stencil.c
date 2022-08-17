#include <stdio.h>
#include <stdlib.h>

#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "eigen_decomposition.h"

#define PRINT_MAX 15
#define DEBUG 1

struct star_stencil *init_stencil(int dimension, int order)
{
	struct star_stencil *stencil = malloc(sizeof(struct star_stencil));
	stencil->dimension = dimension;
	stencil->max_order = order;
	stencil->axis = calloc(sizeof(float), order * dimension);
	return stencil;
}

void destroy_stencil(struct star_stencil *target)
{
	free(target->axis);
	for (int i = 0; i < target->dimension; i++)
	{
		destroy_tensor(target->tensors[i]);
		destroy_tensor(target->in[i]);
		destroy_tensor(target->out[i]);
	}
	free(target->tensors);
	free(target->in);
	free(target->out);
	free(target->eigenvalues);
	free(target);
}

void init_stencil_tensors(struct star_stencil *stencil, struct tensor *data)
{

	if (stencil->dimension != data->dimension)
	{
		error_print("stencil and data dimension are not equal\n");
	}

	int dim = stencil->dimension;
	stencil->tensors = malloc(sizeof(struct tensor *) * dim);
	stencil->in = malloc(sizeof(struct tensor *) * dim);
	stencil->eigenvalues = malloc(sizeof(float) * dim * data->order);
	stencil->out = malloc(sizeof(struct tensor *) * dim);
	struct eigen_decomposition *decomposition;
	int axis_order;
	for (int k = 0; k < dim; k++)
	{
		axis_order = get_axis_order(stencil->axis + k * stencil->max_order, stencil->max_order);
		stencil->tensors[k] = generate_toeplitz(
				stencil->axis + k * stencil->max_order,
				stencil->max_order,
				data->order);
		decomposition = eigen_decompose_toeplitz(
				(stencil->max_order - axis_order) / 2 + stencil->axis + k * stencil->max_order,
				axis_order,
				data->order);
		stencil->in[k] = decomposition->in;
		for (int i = 0; i < data->order; i++)
		{
			stencil->eigenvalues[i + (k * data->order)] = decomposition->eigenvalues[i];
		}
		stencil->out[k] = decomposition->out;
		destroy_eigen_decomposition(decomposition);
	}
}

int get_axis_order(float *axis, int max_order)
{
	int order = max_order;
	for (int i = 0; i < (max_order - 1) / 2; i++)
	{
		if (axis[i] == 0 && axis[max_order - 1 - i] == 0)
		{
			order -= 2;
		}
		else
		{
			return order;
		}
	}
	if (axis[(max_order - 1)/2] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

struct tensor *generate_toeplitz(float *axis, int axis_order, int tensor_order)
{
	// for a 3 wide it's 1, for a 5 wide it's 2 ect.
	int stencil_rad = (axis_order - 1) / 2;
	int start_row;
	int finish_row;
	struct tensor *result = init_tensor(2, tensor_order);
	for (int i = 0; i < axis_order; i++)
	{
		start_row = 0;
		finish_row = tensor_order;
		if ((i - stencil_rad) < 0)
		{
			start_row = stencil_rad - i;
		}
		if ((i - stencil_rad) > 0)
		{
			finish_row = tensor_order - (i - stencil_rad);
		}
		// printf("Val %f, Start row: %d, finish row: %d\n",axis[i],start_row,finish_row);
		for (int j = start_row; j < finish_row; j++)
		{
			result->array[(j * tensor_order + j) + i - stencil_rad] = axis[i];
		}
	}
	return result;
}

void print_stencil(struct star_stencil *stencil)
{
	int n = stencil->max_order;
	int data_order = stencil->in[0]->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	for (int j = 0; j < stencil->dimension; j++)
	{
		printf("Dimension %d \n\n", j);
		printf("Axis:\n");
		for (int i = 0; i < n; i++)
		{
			float_print(stencil->axis[i + n * j]);
		}
		printf("\n\nIn:\n");
		print_tensor(stencil->in[j]);
		printf("Eigen Values:\n| ");
		for (int i = 0; i < data_order; i++)
		{
			float_print(stencil->eigenvalues[i + data_order * j]);
		}
		printf("|\n\nOut:\n");
		print_tensor(stencil->out[j]);
	}
	printf("\n");
}
