#include <time.h>
#include <stdio.h>
#include "clock.h"

double take_interval(struct timespec *begin)
{
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC, &end);
	double time_spent;
	time_spent = (double)(end.tv_sec - (*begin).tv_sec);
	time_spent += (double)(end.tv_nsec - (*begin).tv_nsec)/ 1000000000.0;
	clock_gettime(CLOCK_MONOTONIC, begin);
	return time_spent;
}