#include <math.h>
#include <stdio.h>

#include "eigen_scale.h"
#include "tensor.h"
#include "stencil.h"

struct tensor *eigen_scale(struct tensor *target, struct star_stencil *stencil, int time_steps)
{
	int n = target->size;
	int dim = target->dimension;

	struct tensor *result = init_tensor(dim, n);

	float *eigenvalues;
	// Assign eigenvalues to correct element
	int array_size = pow(n, dim);
	// #pragma omp parallel num_threads(4)
	// {
	// 	#pragma omp for collapse(1) schedule(static,1)
		for (int k = 0; k < dim; k++)
		{
			for (int i = 0; i < array_size; i++)
			{
				result->array[i] += stencil->eigenvalues[k*target->size + i/(int)pow(n, k)%n];
			}
		}
	// }

	// #pragma omp parallel num_threads(4)
	// {
	// 	#pragma omp for collapse(1) schedule(static,1)
		for (int i = 0; i < array_size; i++)
		{
			result->array[i] = target->array[i]*pow(result->array[i],time_steps);
		}
	// }
	return result;
}