#ifndef DEVITO_STENCIL
#define DEVITO_STENCIL

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

extern int Kernel(struct dataobj *restrict u_vec, const float dt, const float h_x, const float h_y, const float h_z, const int time_M, const int time_m, const int x0_blk0_size, const int x_M, const int x_m, const int y0_blk0_size, const int y_M, const int y_m, const int z_M, const int z_m, const int nthreads, struct profiler * timers);

#endif