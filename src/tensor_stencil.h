#ifndef TENSOR_STENCIL
#define TENSOR_STENCIL
extern struct data* init_starting_data(int dimension,int order);
extern struct star_stencil* init_star_stencil(int dimension,int order);
extern void print_data(struct data* data);
extern void print_stencil(struct star_stencil* stencil);
#endif