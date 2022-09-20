#include <stdio.h>
#include "math.h"

#include "contraction.h"
#include "tensor.h"
#include "util.h"

struct tensor *multi_basis_contraction(struct tensor *target, struct tensor **basis_changes, int dimension)
{
	struct tensor *temp[2];
	temp[0] = target;

	for (int i = 0; i < dimension; i++)
	{
		// This stops seg faulting on the first case where no temp has been assigned
		if (i > 1)
		{
			destroy_tensor(temp[(i + 1) % 2]);
		}
		temp[(i + 1) % 2] = tensor_contraction(
				basis_changes[i],
				1, 
				temp[i % 2],
				1);
	}
	if (dimension > 1)
	{
		destroy_tensor(temp[(dimension + 1) % 2]);
	}
	return temp[(dimension) % 2];
}

struct tensor *tensor_contraction(struct tensor *tensor_a, int index_a, struct tensor *tensor_b, int index_b)
{
	if (tensor_a->size != tensor_b->size)
	{
		error_print("these tensors do not share the same size\n");
		return 0;
	}
	if (index_a > tensor_a->dimension || index_b > tensor_b->dimension)
	{
		error_print("you cannot contract on a index outside the dimension of the tensor\n");
		return 0;
	}
	int n = tensor_a->size;
	int new_dimension = tensor_a->dimension + tensor_b->dimension - 2;
	struct tensor *result = init_tensor(new_dimension, n);

	int spacing_a = pow(n, index_a - 1);
	int spacing_b = pow(n, index_b - 1);

	int array_size = pow(n, new_dimension);

	for (int i = 0; i < array_size; i++)
	{
		result->array[i] =sdot_(&n,
				&tensor_a->array[gen_index(n, index_a, i / (int)pow(n, tensor_b->dimension - 1))],
				&spacing_a,
				&tensor_b->array[gen_index(n, index_b, i % (int)pow(n, tensor_b->dimension - 1))],
				&spacing_b);
	}
	return result;
}

int gen_index(int n, int index, int i)
{
	return i % ((int)pow(n, index - 1)) + (i / (int)pow(n, index - 1)) * (int)pow(n, index);
}