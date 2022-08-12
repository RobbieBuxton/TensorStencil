#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "contraction.h"
#include "eigen_decomposition.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	int dimension = 2;
	int data_order = 5;
	//Must be odd
	int stencil_order = 3;

	struct tensor* starting_tensor = init_tensor(dimension,data_order);
	struct star_stencil* stencil = init_stencil(dimension,stencil_order);

	stencil->axis[0] = 0.1;
	stencil->axis[1] = 0.3;
	stencil->axis[2] = 0.1;

	stencil->axis[3] = 0.2;
	stencil->axis[4] = 0.1;
	stencil->axis[5] = 0.2;
	
	print_tensor(starting_tensor);
	print_stencil(stencil);

	init_stencil_tensors(stencil, starting_tensor);

	for (int i = 0; i < dimension; i++) {
		print_tensor(stencil->tensors[i]);
		print_eigen_decomposition(stencil->decompositions[i]);
		print_tensor(tensor_contraction(stencil->decompositions[i]->left,2,stencil->decompositions[i]->left,1));
	}

}



