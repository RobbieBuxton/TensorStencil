#include "tensor.h"
#include "math.h"

float euclidean_norm(struct tensor *tensor) {
	float cum = 0; 
	for (int i = 0; i < pow(tensor->order,tensor->dimension); i++) {
		cum += tensor->array[i]*tensor->array[i];
	}
	return sqrtf(cum);
} 