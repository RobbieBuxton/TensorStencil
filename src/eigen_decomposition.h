#ifndef EIGEN_DECOMPOSITON 
#define EIGEN_DECOMPOSITON 

struct eigen_decomposition {
	struct tensor* left; 
	float* eigenvalues; 
	struct tensor* right; 
};

#endif