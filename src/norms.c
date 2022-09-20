#include "tensor.h"
#include "math.h"

float euclidean_norm(struct tensor *tensor) {
	long double cum = 0; 
	for (int i = 0; i < pow(tensor->size,tensor->dimension); i++) {
		cum += ((long double) tensor->array[i])*((long double) tensor->array[i]);
	}
	return (float) sqrtl(cum);
} 