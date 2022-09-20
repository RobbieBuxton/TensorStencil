#include <math.h>
#include <stdio.h>

#include "eigen_scale.h"
#include "tensor.h"
#include "stencil.h"

struct tensor *eigen_scale(struct tensor *target, struct star_stencil *stencil, int iterations)
{
	int n = target->size;
	int dim = target->dimension;

	struct tensor *result = init_tensor(dim, n);

	float *eigenvalues;
	// Assign eigenvalues to correct element
	for (int k = 0; k < dim; k++)
	{
		for (int i = 0; i < (int) pow(n, dim); i++)
		{
			result->array[i] += stencil->eigenvalues[k*target->size + i/(int)pow(n, k)%n];
		}
	}

	// printf("Eigenvalue map\n");
	// print_tensor(result);
	
	for (int i = 0; i < pow(n, dim); i++)
	{
		result->array[i] = target->array[i]*pow(result->array[i],iterations);
	}
	return result;
}