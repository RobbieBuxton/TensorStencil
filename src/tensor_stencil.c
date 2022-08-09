#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	int dimension = 3;
	int data_order = 3;
	int stencil_order = 3;

	struct tensor* starting_tensor = init_tensor(dimension,data_order);
	struct star_stencil* stencil = init_stencil(dimension,stencil_order);
	
	print_tensor(starting_tensor);
	print_stencil(stencil);

}



