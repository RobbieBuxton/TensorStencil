#include "eigen_decomposition.h"
#include "tensor.h"
#include "stencil.h"
#include "util.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cblas.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct eigen_decomposition *eigen_decompose_toeplitz(float *axis, int stencil_order, int tensor_order)
{
	if (stencil_order != 3)
	{
		error_print("Eigen_decomposition has not be implimented for non 3 order toeplitzs yet");
	}
	struct eigen_decomposition *result = init_eigen_decomposition(tensor_order);
	float pwr;
	float trig;
	float ratio = axis[0] / axis[2];
	for (int i = 0; i < tensor_order; i++)
	{
		result->eigenvalues[i] = (axis[1] + 2 * sqrtf(axis[0] * axis[2]) * cosf(((i + 1) * M_PI) / (tensor_order + 1)));
		for (int j = 0; j < tensor_order; j++)
		{
			pwr = ((i)) / 2.0;
			trig = sinf(((i + 1) * (j + 1) * M_PI) / (tensor_order + 1));
			result->left->array[i + j * tensor_order] = trig * powf(ratio, pwr - (tensor_order / 2.0) + 0.5);
			result->right->array[i + j * tensor_order] = trig * powf(ratio, -pwr);
		}
	}
	float *p = calloc(sizeof(float), tensor_order);

	// scalling - refactor this later because it always seems to be the same term
	for (int i = 0; i < tensor_order; i++)
	{
		p[i] = 1 / sdot_(&tensor_order, result->left->array + i, &tensor_order, result->right->array + i, &tensor_order);
	}

	for (int i = 0; i < tensor_order; i++)
	{
		for (int k = 0; k < tensor_order; k++)
		{
			result->left->array[i + k * tensor_order] *= sqrtf(p[i]);
			result->right->array[i + k * tensor_order] *= sqrtf(p[i]);
		}
	}
	// End refactor 
	return result;
}

struct eigen_decomposition *init_eigen_decomposition(int tensor_order)
{
	struct eigen_decomposition *result = calloc(sizeof(struct eigen_decomposition), 1);
	result->order = tensor_order;
	result->left = init_tensor(2, tensor_order);
	result->eigenvalues = calloc(sizeof(float), tensor_order);
	result->right = init_tensor(2, tensor_order);
	return result;
}

void print_eigen_decomposition(struct eigen_decomposition *eigen_decomposition)
{
	printf("Left\n");
	print_tensor(eigen_decomposition->left);
	printf("Eigenvalues\n| ");
	for (int i = 0; i < eigen_decomposition->order; i++)
	{
		float_print(eigen_decomposition->eigenvalues[i]);
	}
	printf("|\n\nRight\n");
	print_tensor(eigen_decomposition->right);
}