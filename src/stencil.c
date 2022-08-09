#include <stdio.h>
#include <stdlib.h>

#include "stencil.h"
#include "tensor.h"
#include "util.h"

#define PRINT_MAX 15
#define DEBUG 1

struct star_stencil *init_stencil(int dimension, int order)
{
	struct star_stencil *stencil = malloc(sizeof(struct star_stencil));
	stencil->dimension = dimension;
	stencil->order = order;
	stencil->axis = calloc(sizeof(float), order * dimension);
	return stencil;
}

void init_stencil_tensors(struct star_stencil *stencil, struct tensor *data)
{

	if (stencil->dimension != data->dimension)
	{
		printf("Error: Stencil and data dimension are not equal\n");
	}

	int n = data->order;
	int w = stencil->order;
	int dim = stencil->dimension;
	stencil->tensors = malloc(sizeof(struct tensor) * dim);
	struct tensor *temp_tensor;

	int start_row;
	int finish_row;
	for (int k = 0; k < dim; k++)
	{
		temp_tensor = init_tensor(2, n);
		for (int i = 0; i < w; i++)
		{
			if (i <= (w-1)/2) {
				start_row = ((w-1)/2) - i;
				finish_row = n-1;
			} 
			if (i >= (w+1)/2) {
				start_row = 0;
				finish_row = (n-1) - ((w-1)/2 - i);
			} 

			for (int j = start_row; j <= finish_row; j++)
			{
				temp_tensor->array[(j*n+j) - i] = stencil->axis[w*k + i];
			}
		}
		// Set tensor 
	}
}

void print_stencil(struct star_stencil *stencil)
{
	int n = stencil->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	for (int j = 0; j < stencil->dimension; j++)
	{
		printf("Dim %d: ", j);
		for (int i = 0; i < n; i++)
		{
			float_print(stencil->axis[i + n * j]);
		}
		printf("\n");
	}
	printf("\n");
}
