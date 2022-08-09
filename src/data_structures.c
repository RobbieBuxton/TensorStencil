#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "data_structures.h"
#include "util.h"

#define PRINT_MAX 15
#define DEBUG 1

struct data *init_starting_data(int dimension, int order)
{
	struct data *starting_data = malloc(sizeof(struct data));
	starting_data->dimension = dimension;
	starting_data->order = order;
	starting_data->array = calloc(sizeof(float), pow(order, dimension));
	return starting_data;
}

struct star_stencil *init_star_stencil(int dimension, int order)
{
	struct star_stencil *stencil = malloc(sizeof(struct star_stencil));
	stencil->dimension = dimension;
	stencil->order = order;
	stencil->axis = calloc(sizeof(float), order * dimension);
	return stencil;
}

void print_stencil(struct star_stencil *stencil)
{
	int n = stencil->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	for (int j = 0; j < stencil->dimension; j++)
	{
		printf("Dim %d: ", j);
		for (int i = 0; i < n; i++)
		{
			float_print(stencil->axis[i + n * j]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_data(struct data *data)
{
	int n = data->order;
	if (n > PRINT_MAX || !DEBUG)
	{
		return;
	}
	switch (data->dimension)
	{
	case 1:
		printf("| ");
		for (int i = 0; i < n; i++)
		{
			float_print(data->array[i]);
		}
		printf("|\n\n");
		break;

	case 2:
		for (int j = 0; j < n; j++)
		{
			printf("| ");
			for (int i = 0; i < n; i++)
			{
				float_print(data->array[i + n * j]);
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
					float_print(data->array[i + n * j + n * n * k]);
				}
				printf("%c\n",edge);
			}
			printf("\n");
		}
		printf("\n");
		break;

	default:
		printf("Error: printing in this data dimension is not supported\n");
		break;
	}
}