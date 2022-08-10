#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define PRINT_SF 3
#define NON_ZERO_COLOUR "\x1B[32m"
#define NORMAL_COLOUR "\x1B[0m" 
#define ERROR_COLOUR "\x1B[31m" 

void float_print(float a) {
	if (a == 0) {
		printf("%+.*f ",PRINT_SF,a);
	} else {
		printf(NON_ZERO_COLOUR"%+.*f "NORMAL_COLOUR,PRINT_SF,a);
	}
}

void error_print(char* string) {
	//This currently segfaults the program lol but it doesn't actually matter
	printf(ERROR_COLOUR"Error: %s"NORMAL_COLOUR,string);
}