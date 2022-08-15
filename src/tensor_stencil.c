#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "contraction.h"
#include "eigen_decomposition.h"
#include "eigen_scale.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	int dimension = 2;
	int data_order = 5;
	// Must be odd
	int stencil_order = 3;

	struct tensor *starting_tensor = init_tensor(dimension, data_order);

	//Initing the starting data to arb thing
	for (int i = 0; i < pow(data_order, dimension); i++)
	{
		starting_tensor->array[i] = 1.0;
	}
	starting_tensor->array[data_order + 1] = 2;
	starting_tensor->array[data_order + 2] = 2;
	starting_tensor->array[2 * data_order + 1] = 2;
	starting_tensor->array[2 * data_order + 2] = 2;
	//Finished

	struct star_stencil *stencil = init_stencil(dimension, stencil_order);
	

	stencil->axis[0] = 0.1;
	stencil->axis[1] = 0.3;
	stencil->axis[2] = 0.1;

	stencil->axis[3] = 0.1;
	stencil->axis[4] = 0.3;
	stencil->axis[5] = 0.1;

	print_tensor(starting_tensor);
	print_stencil(stencil);

	init_stencil_tensors(stencil, starting_tensor);

	struct tensor *a = tensor_contraction(
			stencil->decompositions[0]->right,
			2,
			starting_tensor,
			1);
	
	struct tensor *b = tensor_contraction(
			a,
			1,
			stencil->decompositions[1]->left,
			2);

	struct tensor *c = eigen_scale(b,stencil->decompositions,1);

	struct tensor *d = tensor_contraction(
			stencil->decompositions[1]->right,
			2,
			c,
			1);
	
	struct tensor *e = tensor_contraction(
			d,
			1,
			stencil->decompositions[0]->left,
			2);

	print_tensor(b);
	print_tensor(c);
	print_tensor(e);

	destroy_tensor(a);
	destroy_tensor(b);
	destroy_tensor(c);
	destroy_tensor(d);
	destroy_tensor(e);
	destroy_tensor(starting_tensor);
	destroy_stencil(stencil);
}
