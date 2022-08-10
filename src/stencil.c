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
	stencil->tensors = malloc(sizeof(struct tensor*)*dim);

	int start_row;
	int finish_row;
	// for a 3 wide it's 1, for a 5 wide it's 2 ect. 
	int stencil_rad = (w-1)/2;
	for (int k = 0; k < dim; k++)
	{
		stencil->tensors[k] = init_tensor(2, n);
		for (int i = 0; i < w; i++)
		{
			start_row = 0;
			finish_row = n;
			if ((i - stencil_rad) < 0) {
				start_row = stencil_rad - i;
			} 
			if ((i - stencil_rad) > 0) {
				finish_row = n - (i - stencil_rad);
			} 
			// printf("Val %f, Start row: %d, finish row: %d\n",stencil->axis[w*k + i],start_row,finish_row);
			for (int j = start_row; j < finish_row; j++)
			{
				(stencil->tensors[k])->array[(j*n+j) + i - stencil_rad] = stencil->axis[w*k + i];
			}
		}
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
