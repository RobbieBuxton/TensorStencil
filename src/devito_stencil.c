#define _POSIX_C_SOURCE 200809L
#define START_TIMER(S) struct timeval start_ ## S , end_ ## S ; gettimeofday(&start_ ## S , NULL);
#define STOP_TIMER(S,T) gettimeofday(&end_ ## S, NULL); T->S += (double)(end_ ## S .tv_sec-start_ ## S.tv_sec)+(double)(end_ ## S .tv_usec-start_ ## S .tv_usec)/1000000;

#include "stdlib.h"
#include "math.h"
#include "sys/time.h"
#include "omp.h"

struct dataobj
{
  void *restrict data;
  unsigned long * size;
  unsigned long * npsize;
  unsigned long * dsize;
  int * hsize;
  int * hofs;
  int * oofs;
} ;

struct profiler
{
  double section0;
} ;


int Kernel(const float a, struct dataobj *restrict u_vec, const float dt, const float h_x, const float h_y, const float h_z, const int time_M, const int time_m, const int x_M, const int x_m, const int y_M, const int y_m, const int z_M, const int z_m, const int nthreads, struct profiler * timers)
{
  float (*restrict u)[u_vec->size[1]][u_vec->size[2]][u_vec->size[3]] __attribute__ ((aligned (64))) = (float (*)[u_vec->size[1]][u_vec->size[2]][u_vec->size[3]]) u_vec->data;

  for (int time = time_m, t0 = (time)%(2), t1 = (time + 1)%(2); time <= time_M; time += 1, t0 = (time)%(2), t1 = (time + 1)%(2))
  {
    /* Begin section0 */
    START_TIMER(section0)
    #pragma omp parallel num_threads(nthreads)
    {
      #pragma omp for collapse(3) schedule(dynamic,1)
      for (int x = x_m; x <= x_M; x += 1)
      {
        for (int y = y_m; y <= y_M; y += 1)
        {
          for (int z = z_m; z <= z_M; z += 1)
          {
						u[t1][x + 2][y + 2][z + 2] = dt*(a*(u[t0][x + 1][y + 2][z + 2]/pow(h_x, 2) - 2.0F*u[t0][x + 2][y + 2][z + 2]/pow(h_x, 2) + u[t0][x + 3][y + 2][z + 2]/pow(h_x, 2) + u[t0][x + 2][y + 1][z + 2]/pow(h_y, 2) - 2.0F*u[t0][x + 2][y + 2][z + 2]/pow(h_y, 2) + u[t0][x + 2][y + 3][z + 2]/pow(h_y, 2) + u[t0][x + 2][y + 2][z + 1]/pow(h_z, 2) - 2.0F*u[t0][x + 2][y + 2][z + 2]/pow(h_z, 2) + u[t0][x + 2][y + 2][z + 3]/pow(h_z, 2)) + u[t0][x + 2][y + 2][z + 2]/dt);
					}
        }
      }
    }
    STOP_TIMER(section0,timers)
    /* End section0 */
  }

  return 0;
}

