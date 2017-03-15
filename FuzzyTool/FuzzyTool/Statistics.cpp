#include "Statistics.h"
#include <stdlib.h>
#include <math.h>

/**** 95% inteval spolahlivosti  ****/
const bool LEFT = true;
const bool RIGHT = false;

double Statistics::my95CI(bool side, double mean, double stDev, int N)
{
	double result;
	if (side) // left
		result = mean - ((stDev * 1.96) / sqrt(double(N - 1)));
	else // right
		result = mean + ((stDev * 1.96) / sqrt(double(N - 1)));
	return result;
}

/**** Vzorec na vypocet rozptylu  *****/
double Statistics::specStDev(unsigned long valPow2, unsigned long val, unsigned long N, unsigned long m)
{
	return sqrt((valPow2 - double(val * val) / N) / ((N - 1) * m * m));
}
