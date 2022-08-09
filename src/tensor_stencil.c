#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor_stencil.h"
#include "data_structures.h"
#include "util.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	int dimension = 3;
	int data_order = 5;
	int stencil_order = 3;

	struct data* starting_data = init_starting_data(dimension,data_order);
	struct star_stencil* stencil = init_star_stencil(dimension,stencil_order);
	print_data(starting_data);
	print_stencil(stencil);
}

