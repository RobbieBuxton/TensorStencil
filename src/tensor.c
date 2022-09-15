#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor.h"
#include "util.h"

#define PRINT_MAX 15
#define DEBUG 1

struct tensor *init_tensor(int dimension, int order)
{
	struct tensor *tensor = malloc(sizeof(struct tensor));
	tensor->dimension = dimension;
	tensor->order = order;
	tensor->array = calloc(sizeof(float), pow(order, dimension));
	return tensor;
}

struct tensor *pad_tensor(struct tensor *tensor, int padding)
{
	//Rewrite this recursively at some point as a general function
	struct tensor *result = init_tensor(tensor->dimension, tensor->order + 2 * padding);
	switch (tensor->dimension)
	{
	case 1:
		for (int i = 0; i < tensor->order; i++)
		{
			result->array[i + padding] = tensor->array[i];
		}
		break;
	case 2:
		for (int j = 0; j < tensor->order; j++)
		{
			for (int i = 0; i < tensor->order; i++)
			{
				result->array[i + padding + j*(tensor->order+2*padding) + (tensor->order+2*padding)] = tensor->array[i+j*tensor->order];
			}
		}
		break;
	case 3:
		for (int k = 0; k < tensor->order; k++)
		{
			for (int j = 0; j < tensor->order; j++)
			{
				for (int i = 0; i < tensor->order; i++)
				{
					result->array[
						i + padding + 
						j*(tensor->order+2*padding) + tensor->order+2*padding + 
						k*(int) pow(tensor->order+2*padding,2) + (int) pow(tensor->order+2*padding,2)] = tensor->array[i+j*tensor->order+k* (int) pow(tensor->order,2)];
				}
			}	
		}
		break;
	default:
		error_print("padding in this tensor dimension is not supported\n");
		break;
	}
	return result;
}

void destroy_tensor(struct tensor *target)
{
	free(target->array);
	free(target);
}

struct tensor *add_tensors(struct tensor *a, struct tensor *b)
{
	if (a->dimension != b->dimension || a->order != b->order)
	{
		error_print("these tensors cannot be added as they do not share the same dim and order");
		return 0;
	}
	struct tensor *result = init_tensor(a->dimension, b->order);
	for (int i = 0; i < pow(a->order, a->dimension); i++)
	{
		result->array[i] = a->array[i] + b->array[i];
	}
	return result;
}

void print_tensor(struct tensor *tensor)
{
	int n = tensor->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	switch (tensor->dimension)
	{
	case 0:
		printf("| ");
		float_print(tensor->array[0]);
		printf("|\n\n");
		;
		break;
	case 1:
		printf("| ");
		for (int i = 0; i < n; i++)
		{
			float_print(tensor->array[i]);
		}
		printf("|\n\n");
		break;

	case 2:
		for (int j = 0; j < n; j++)
		{
			printf("| ");
			for (int i = 0; i < n; i++)
			{
				float_print(tensor->array[i + n * j]);
			}
			printf("|\n");
		}
		printf("\n");
		break;

	case 3:;
		char edge = '|';
		for (int k = 0; k < n; k++)
		{
			if (k == 0 || k == n - 1)
			{
				edge = '|';
			}
			else
			{
				edge = ':';
			}
			for (int j = 0; j < n; j++)
			{
				printf("%c ", edge);
				for (int i = 0; i < n; i++)
				{
					float_print(tensor->array[i + n * j + n * n * k]);
				}
				printf("%c\n", edge);
			}
			printf("\n");
		}
		printf("\n");
		break;

	default:
		error_print("printing in this tensor dimension is not supported\n");
		break;
	}
}