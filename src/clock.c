#include <time.h>

#include "clock.h"

double take_interval(clock_t *begin)
{
	clock_t end = clock();
	double time_spent = (double)(end - *begin) / CLOCKS_PER_SEC;
	*begin = clock();
	return time_spent;
}