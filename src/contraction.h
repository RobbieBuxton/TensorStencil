#ifndef CONTRACTION
#define CONTRACTION
extern struct tensor *multi_basis_contraction(struct tensor* target, struct tensor** basis_changes, int dimension);
extern struct tensor *tensor_contraction(struct tensor *tensor_a, int index_a, struct tensor *tensor_b, int index_b);
extern float contract_dimension(float *start_a, int spacing_a, float *start_b, int spacing_b, int n);
extern int gen_index(int order, int index_b, int i);
#endif