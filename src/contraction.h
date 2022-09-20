#ifndef CONTRACTION
#define CONTRACTION
extern struct tensor *multi_basis_contraction(struct tensor* target, struct tensor** basis_changes, int dimension);
extern struct tensor *tensor_contraction(struct tensor *tensor_a, int index_a, struct tensor *tensor_b, int index_b);
extern float contract_dimension(int n, float *start_a, int spacing_a, float *start_b, int spacing_b);
extern int gen_index(int order, int index_b, int i);
extern float sdot_(int *, float *, int *, float *, int *);
#endif