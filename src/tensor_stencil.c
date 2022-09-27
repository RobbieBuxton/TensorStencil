#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "tensor_stencil.h"
#include "stencil.h"
#include "tensor.h"
#include "util.h"
#include "contraction.h"
#include "eigen_decomposition.h"
#include "eigen_scale.h"
#include "clock.h"
#include "norms.h"
#include "devito_adapter.h"

#define DEBUG 1

int main(int argc, char *argv[])
{
	int iterations = 1;
	int size_start = 500;
	int size_step = 25;
	int time_steps_start = 500;
	int time_steps_step = 0;
	float *times = malloc(sizeof(float) * 2 * iterations);
	float *norm_error = malloc(sizeof(float) * iterations);


	FILE *fp1 = fopen("results.csv", "w");
	if (fp1 == NULL)
	{
		printf("Error while opening the file.\n");
		return;
	}

	for (int i = 0; i < iterations; i ++) 
	{
		test(times + 2*i, norm_error + i, size_start + size_step * i, time_steps_start + time_steps_step * i);
		fprintf(fp1, "%d, %f, %f, %f\n",size_start+size_step*i, times[2*i], times[2*i+1], norm_error[i]);
	}

	fclose(fp1);
	
}

int test(float *times, float* norm_error, int data_size, int time_steps)
{


	struct timespec begin;

	clock_gettime(CLOCK_MONOTONIC, &begin);

	double time_spent[3];

	int dimension = 3;
	// Must be odd (only 3 supported atm)
	int stencil_size = 3;

	int enable_devito = 0;

	printf("\n######################\nNEW TEST\nDim: %d Size %d Time Steps %d\n\n",dimension, data_size, time_steps);

	struct tensor *starting_tensor = init_tensor(dimension, data_size);

	// Initing the starting data to arb thing
	for (int i = 0; i < pow(data_size, dimension); i++)
	{
		starting_tensor->array[i] = 6.5;
	}

	struct star_stencil *stencil = init_stencil(dimension, stencil_size);

	// Vars

	float nu = .5;
	float dx = 2. / (data_size - 1);
	float dy = 2. / (data_size - 1);
	float dz = 2. / (data_size - 1);
	float sigma = .25;
	float dt = sigma * dx * dz * dy / nu;

	float h_x = 1. / (data_size - 1);
	float h_y = 1. / (data_size - 1);
	float h_z = 1. / (data_size - 1);

	float a = 0.1;
	float centre = (dt * (a * (-2.0 / pow(h_x, 2) - 2.0 / pow(h_y, 2) - 2.0 / pow(h_z, 2)))) + 1;

	// X
	if (dimension >= 1)
	{
		stencil->axis[0] = (dt * a) / pow(h_x, 2);
		stencil->axis[1] = centre / dimension;
		stencil->axis[2] = (dt * a) / pow(h_x, 2);
	}

	// Y
	if (dimension >= 2)
	{
		stencil->axis[3] = (dt * a) / pow(h_y, 2);
		stencil->axis[4] = centre / dimension;
		stencil->axis[5] = (dt * a) / pow(h_y, 2);
	}
	// Z
	if (dimension >= 3)
	{
		stencil->axis[6] = (dt * a) / pow(h_z, 2);
		stencil->axis[7] = centre / dimension;
		stencil->axis[8] = (dt * a) / pow(h_z, 2);
	}

	printf("Starting Tensor\n\n");
	print_tensor(starting_tensor);

	init_stencil_tensors(stencil, starting_tensor);

	// print_stencil(stencil);

	time_spent[0] = take_interval(&begin);

	struct tensor *t = multi_basis_contraction(starting_tensor, stencil->out, dimension);
	// printf("Post first basis change\n");
	// print_tensor(t);

	time_spent[1] = take_interval(&begin);

	struct tensor *c = eigen_scale(t, stencil, time_steps);
	destroy_tensor(t);

	// printf("Post Eigenscale\n");
	// print_tensor(c);

	time_spent[2] = take_interval(&begin);

	struct tensor *result = multi_basis_contraction(c, stencil->in, dimension);
	destroy_tensor(c);

	time_spent[3] = take_interval(&begin);

	// Tensor Stencil
	printf("TensorStencil Result\n\n");
	print_tensor(result);

	float tensor_stencil_norm = euclidean_norm(result);

	times[0] = time_spent[0] + time_spent[1] + time_spent[2] + time_spent[3];

	printf("###Tensor Stencil Time Spent###\n");
	printf("Init data        %fs\n", time_spent[0]);
	printf("1st basis contr: %fs\n", time_spent[1]);
	printf("Eigen scale:     %fs\n", time_spent[2]);
	printf("2st basis contr: %fs\n\n", time_spent[3]);
	printf("Total:           %fs\n\n", time_spent[0] + time_spent[1] + time_spent[2] + time_spent[3]);

	// Devito only runs in 3d
	if (dimension == 3 && stencil_size == 3 && enable_devito)
	{
		float devito_timer = 0;
		struct tensor *devito_result = devito_stencil_kernel_adapter(starting_tensor, stencil, time_steps, dt, h_x, h_y, h_z, &devito_timer);

		printf("Devito Result\n\n");
		print_tensor(devito_result);

		float devito_stencil_norm = euclidean_norm(devito_result);

		times[1] = devito_timer;

		printf("###Devito Spent###\n\n");
		printf("Total:           %fs\n\n", devito_timer);

		printf("Euclidean norm\n");
		printf("Tensor Stencil: %f\n", tensor_stencil_norm);
		printf("Devito:         %f\n", devito_stencil_norm);
		printf("Difference:     %f\n", tensor_stencil_norm - devito_stencil_norm);
		printf("Percent Error:  %f\n\n", (tensor_stencil_norm - devito_stencil_norm) / devito_stencil_norm);

		norm_error[0] = (tensor_stencil_norm - devito_stencil_norm) / devito_stencil_norm;

		destroy_tensor(devito_result);
	}

	destroy_tensor(starting_tensor);
	destroy_tensor(result);
	destroy_stencil(stencil);

	return 1;
}
