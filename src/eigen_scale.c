#include <math.h>
#include <stdio.h>

#include "eigen_scale.h"
#include "tensor.h"
#include "eigen_decomposition.h"

struct tensor *eigen_scale(struct tensor *target, struct eigen_decomposition **decompositions, int iterations)
{
	int n = target->order;
	int dim = target->dimension;

	struct tensor *result = init_tensor(dim, n);

	float *eigenvalues;
	// Assign eigenvalues to correct element
	for (int k = 0; k < dim; k++)
	{
		eigenvalues = decompositions[k]->eigenvalues;
		for (int i = 0; i < (int) pow(n, dim); i++)
		{
			result->array[i] += eigenvalues[i/(int)pow(n, k)%n];
		}
	}
	
	for (int i = 0; i < pow(n, dim); i++)
	{
		result->array[i] = target->array[i]*pow(result->array[i],iterations);
	}
	return result;
}