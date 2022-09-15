#define _POSIX_C_SOURCE 200809L
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define START_TIMER(S)               \
	struct timeval start_##S, end_##S; \
	gettimeofday(&start_##S, NULL);
#define STOP_TIMER(S, T)        \
	gettimeofday(&end_##S, NULL); \
	T->S += (double)(end_##S.tv_sec - start_##S.tv_sec) + (double)(end_##S.tv_usec - start_##S.tv_usec) / 1000000;

#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "xmmintrin.h"
#include "pmmintrin.h"
#include "devito_stencil.h"

int devito_stencil_kernel(struct dataobj *restrict u_vec, const int time_M, const int time_m, const int x0_blk0_size, const int x_M, const int x_m, const int y0_blk0_size, const int y_M, const int y_m, const int z_M, const int z_m, struct profiler *timers)
{

	float(*restrict u)[u_vec->size[1]][u_vec->size[2]][u_vec->size[3]] __attribute__((aligned(64))) = (float(*)[u_vec->size[1]][u_vec->size[2]][u_vec->size[3]])u_vec->data;

	/* Flush denormal numbers to zero in hardware */
	_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

	for (int time = time_m, t0 = (time) % (2), t1 = (time + 1) % (2); time <= time_M; time += 1, t0 = (time) % (2), t1 = (time + 1) % (2))
	{
		/* Begin section0 */
		START_TIMER(section0)
		for (int x0_blk0 = x_m; x0_blk0 <= x_M; x0_blk0 += x0_blk0_size)
		{
			for (int y0_blk0 = y_m; y0_blk0 <= y_M; y0_blk0 += y0_blk0_size)
			{
				for (int x = x0_blk0; x <= MIN(x0_blk0 + x0_blk0_size - 1, x_M); x += 1)
				{
					for (int y = y0_blk0; y <= MIN(y0_blk0 + y0_blk0_size - 1, y_M); y += 1)
					{
#pragma omp simd aligned(u : 32)
						for (int z = z_m; z <= z_M; z += 1)
						{
							// printf("x: %d, y: %d z: %d\n", x + 1, y + 1, z + 1);
							u[t1][x + 1][y + 1][z + 1] =
									0.1*u[t0][x + 0][y + 1][z + 1] +
									0.1*u[t0][x + 2][y + 1][z + 1] +
									0.1*u[t0][x + 1][y + 0][z + 1] +
									0.1*u[t0][x + 1][y + 2][z + 1] +
									0.1*u[t0][x + 1][y + 1][z + 0] +
									0.1*u[t0][x + 1][y + 1][z + 2] +
									0.9*u[t0][x + 1][y + 1][z + 1];
						}
					}
				}
			}
		}
		STOP_TIMER(section0, timers)
		/* End section0 */
	}

	return 0;
}
