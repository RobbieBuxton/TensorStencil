#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define PRINT_SF 3
#define ZERO_COLOUR "\x1B[32m"
#define NORMAL_COLOUR "\x1B[0m" 


void float_print(float a) {
	if (a == 0) {
		printf("%+.*f ",PRINT_SF,a);
	} else {
		printf(ZERO_COLOUR"%+.*f "NORMAL_COLOUR,PRINT_SF,a);
	}
}