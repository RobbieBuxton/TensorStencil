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
	int iterations = 1;
	int dimension = 2;
	int data_order = 3;
	// Must be odd
	int stencil_order = 3;

	struct tensor *starting_tensor = init_tensor(dimension, data_order);

	// Initing the starting data to arb thing
	for (int i = 0; i < pow(data_order, dimension); i++)
	{
		starting_tensor->array[i] = 1.0;
	}
	// starting_tensor->array[data_order + 1] = 2;
	// starting_tensor->array[data_order + 2] = 2;
	// starting_tensor->array[2 * data_order + 1] = 2;
	// starting_tensor->array[2 * data_order + 2] = 2;
	// Finished

	struct star_stencil *stencil = init_stencil(dimension, stencil_order);

	//X
	stencil->axis[0] = 0.1;
	stencil->axis[1] = 0.3;
	stencil->axis[2] = 0.1;

	//Y
	stencil->axis[3] = 0;
	stencil->axis[4] = 0.3;
	stencil->axis[5] = 0;

	//Z
	// stencil->axis[6] = 0.1;
	// stencil->axis[7] = 0.3;
	// stencil->axis[8] = 0.1;

	print_tensor(starting_tensor);

	init_stencil_tensors(stencil, starting_tensor);

	print_stencil(stencil);


	struct tensor *t = multi_basis_contraction(starting_tensor,stencil->out,dimension);
	printf("Post first basis change\n");
	print_tensor(t);
	struct tensor *c = eigen_scale(t, stencil, iterations);
	printf("Post Eigenscale\n");
	print_tensor(c);

	struct tensor *result = multi_basis_contraction(c, stencil->in, dimension);

	printf("Result\n");
	print_tensor(result);

	destroy_tensor(starting_tensor);
	destroy_tensor(t);
	destroy_tensor(c);
	destroy_tensor(result);
	destroy_stencil(stencil);
}
