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

void print_tensor(struct tensor *tensor)
{
	int n = tensor->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	switch (tensor->dimension)
	{
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

	case 3: ;
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
				printf("%c ",edge);
				for (int i = 0; i < n; i++)
				{
					float_print(tensor->array[i + n * j + n * n * k]);
				}
				printf("%c\n",edge);
			}
			printf("\n");
		}
		printf("\n");
		break;

	default:
		printf("Error: printing in this tensor dimension is not supported\n");
		break;
	}
}