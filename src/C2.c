#include "tseriesChaos.h"

/*
Sample correlation integral.
in_series: input time series
in_m, in_d, in_t: embedding dimension, time delay and theiler window
in_length: time series length
in_eps: length scale
out: the computed sample correlation integral
*/
void C2(double *in_series, int *in_m, int *in_d, int *in_length, 
	int *in_t, double *in_eps, double *out) {
	double *series; 
	double eps, tmp;
	int m, d, length;
	long blength;
	int i, j, t, md;
	
	series = in_series; 
	m = *in_m;
	d = *in_d; 
	t = *in_t;
	eps = *in_eps; 
	eps = sqr(eps);
	length = *in_length;
	blength = length - (m-1)*d;
	md = m*d;
	*out=0;

	for(i=0; i<blength-t; i++) for(j=i+t; j<blength; j++) { /*for each pair of points...*/
		DIST2EPS(series, i, j, md, d, eps, tmp);
		*out += (tmp<eps);
	} /*end for each pair*/
	*out /= ( ((double)blength-t+1)*((double)blength-t)/2.0 );
}
