#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "contraction.h"

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

	stencil->axis[3] = 0.1;
	stencil->axis[4] = 0.3;
	stencil->axis[5] = 0.1;
	
	print_tensor(starting_tensor);
	print_stencil(stencil);

	init_stencil_tensors(stencil, starting_tensor);

	for (int i = 0; i < dimension; i++) {
		print_tensor(stencil->tensors[i]);
	}

	struct tensor* a = init_tensor(3,3);
	a->array[0] = 1;
	a->array[1] = 2;
	a->array[2] = 3;
	a->array[3] = 4;
	a->array[4] = 5;
	a->array[5] = 6;
	a->array[6] = 7;
	a->array[7] = 8;
	a->array[8] = 9;
	a->array[9] = 10;
	a->array[10] = 11;
	a->array[11] = 12;
	a->array[12] = 13;
	a->array[13] = 14;
	a->array[14] = 15;
	a->array[15] = 16;
	a->array[16] = 17;
	a->array[17] = 18;
	a->array[18] = 19;
	a->array[19] = 20;
	a->array[20] = 21;
	a->array[21] = 22;
	a->array[22] = 23;
	a->array[23] = 24;
	a->array[24] = 25;
	a->array[25] = 26;
	a->array[26] = 27;
	print_tensor(a);
	struct tensor* b = init_tensor(2,3);
	b->array[0] = 1;
	b->array[1] = 0;
	b->array[2] = 0;
	b->array[3] = 0;
	b->array[4] = 1;
	b->array[5] = 0;
	b->array[6] = 0;
	b->array[7] = 0;
	b->array[8] = 1;
	print_tensor(b);
	struct tensor* c = tensor_contraction(a,2,b,1);
	printf("dim %d\n",c->dimension);
	print_tensor(c);
}



