#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "contraction.h"
#include "eigen_decomposition.h"
#include "eigen_scale.h"
#include "clock.h"
#include "norms.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	clock_t begin = clock();
	double time_spent[3];

	int iterations = 0;
	int dimension = 3;
	int data_order = 3;
	// Must be odd
	int stencil_order = 3;

	struct tensor *starting_tensor = init_tensor(dimension, data_order);

	// Initing the starting data to arb thing
	for (int i = 0; i < pow(data_order, dimension); i++)
	{
		starting_tensor->array[i] = 1.0;
	}
	starting_tensor->array[data_order + 1] = 2;
	starting_tensor->array[data_order + 2] = 2;
	starting_tensor->array[2 * data_order + 1] = 2;
	starting_tensor->array[2 * data_order + 2] = 2;
	// Finished

	struct star_stencil *stencil = init_stencil(dimension, stencil_order);

	//X
	stencil->axis[0] = 0.1;
	stencil->axis[1] = 0.3;
	stencil->axis[2] = 0.1;

	//Y
	stencil->axis[3] = 0.1;
	stencil->axis[4] = 0.3;
	stencil->axis[5] = 0.1;

	//Z
	// stencil->axis[6] = 0.1;
	// stencil->axis[7] = 0.3;
	// stencil->axis[8] = 0.1;
	
	print_tensor(starting_tensor);

	init_stencil_tensors(stencil, starting_tensor);

	// print_stencil(stencil)

	time_spent[0] = take_interval(&begin);

	struct tensor *t = multi_basis_contraction(starting_tensor,stencil->out,dimension);
	// printf("Post first basis change\n");
	// print_tensor(t);

	time_spent[1] = take_interval(&begin);

	struct tensor *c = eigen_scale(t, stencil, iterations);
	// printf("Post Eigenscale\n");
	// print_tensor(c);

	time_spent[2] = take_interval(&begin);

	struct tensor *result = multi_basis_contraction(c, stencil->in, dimension);

	time_spent[3] = take_interval(&begin);

	printf("Result\n");
	print_tensor(result);

	printf("Euclidean norm\n%f\n\n",euclidean_norm(result));

	printf("###Time spent###\n");
	printf("Init data        %fs\n",time_spent[0]);
	printf("1st basis contr: %fs\n",time_spent[1]);
	printf("Eigen scale:     %fs\n",time_spent[2]);
	printf("2st basis contr: %fs\n\n",time_spent[3]);
	printf("Total:           %fs\n\n",time_spent[0]+time_spent[1]+time_spent[2]+time_spent[3]);
	destroy_tensor(starting_tensor);
	destroy_tensor(t);
	destroy_tensor(c);
	destroy_tensor(result);
	destroy_stencil(stencil);
}
