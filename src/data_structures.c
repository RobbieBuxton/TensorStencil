#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "data_structures.h"

#define PRINT_MAX 15
#define PRINT_SF 3
#define DEBUG 1

struct data* init_starting_data(int dimension,int order) {
	struct data* starting_data = malloc(sizeof(struct data));
	starting_data->dimension = dimension;
	starting_data->order = order;
	starting_data->array = calloc(sizeof(float),pow(order,dimension));
	return starting_data;
}

struct star_stencil* init_star_stencil(int dimension,int order) {
	struct star_stencil* stencil = malloc(sizeof(struct star_stencil));
	stencil->dimension = dimension;
	stencil->order = order;
	stencil->axis = calloc(sizeof(float),order*dimension);
	return stencil;
}

void print_stencil(struct star_stencil* stencil) {
	int n = stencil->order;
	if (n > PRINT_MAX || !DEBUG) {
		return;
	}
	switch (stencil->dimension) {
		case 1:
			for (int i = 0; i < n; i++) {
				printf("%+.*f ",PRINT_SF,stencil->axis[i]);
			}
			printf("\n\n");
			break;

		case 2:
			for(int j = 0; j < stencil->dimension; j++)
			{ 
				printf("Dim %d: ",j);
				for (int i = 0; i < n; i++) {
					printf("%+.*f ",PRINT_SF,stencil->axis[i + n*j]);
				}
				printf("\n");
			}
			printf("\n");
			break;  
		
		default: 
			printf("Error: printing in this stencil dimension is not supported");
			break;
	}

}

void print_data(struct data* data) {
	int n = data->order;
	if (n > PRINT_MAX || !DEBUG) {
		return;
	}
	switch (data->dimension) {
		case 1:
			printf("| ");
			for (int i = 0; i < n; i++) {
				printf("%+.*f ",PRINT_SF,data->array[i]);
			}
			printf("|\n\n");
			break;

		case 2:
			for(int j = 0; j < n; j++)
			{
				printf("| ");
				for (int i = 0; i < n; i++) {
					printf("%+.*f ",PRINT_SF,data->array[i + n*j]);
				}
				printf("|\n");
			}
			printf("\n");
			break;  
		
		default: 
			printf("Error: printing in this data dimension is not supported");
			break;
	}
}