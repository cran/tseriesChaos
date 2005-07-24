#include "tseriesChaos.h"

void C2(double *in_series, int *in_m, int *in_d, int *in_length, 
	int *in_t, double *in_eps, double *out) {
	double *series; 
	double eps, tmp;
	int m, d, length;
	long blength;
	int i, j, w, t, md;
	
	series = in_series; 
	m = *in_m;
	d = *in_d; 
	t = *in_t;
	eps = *in_eps; 
	eps = sqr(eps);
	length = *in_length;
	blength = length - (m-1)*d;
	
	md = m*d; *out=0;
	for(i=0; i<blength-t; i++) for(j=i+t; j<blength; j++) {
	  tmp=0.0;
	  for(w=0; (w<md) && (tmp<eps); w+=d) 
		tmp+=sqr(series[i+w]-series[j+w]);
	  *out += (tmp<eps);
	}
	*out /= ( ((double)blength-t+1)*((double)blength-t)/2.0 );
}
