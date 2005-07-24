#include "tseriesChaos.h"

#define output(i,j) out[(j)+(i)*neps]

void d2(double *in_series, int *in_length, int *in_m, int *in_d, int *in_t, int *in_neps, double *in_epsM, double *in_epsm, double *out){
	double tmpd, **hist;
	int i,j,w;
	int length, m,d,t, neps, blength;
	double *series, epsM, epsm;
	double a, lepsM;

	series = in_series;
	length = *in_length;
	m = *in_m;
	d = *in_d;
	t = *in_t;
	neps = *in_neps;
	epsm = sqr(*in_epsm);
	epsM = sqr(*in_epsM);
	blength = length -(m-1)*d;
	lepsM = log(epsM);
	a = log(epsm/epsM)/(double)(neps-1);
	hist = (double**) R_alloc(m, sizeof(double*));
	for(i=0; i<m; i++) {
		hist[i] = (double*) R_alloc(neps, sizeof(double));
		for(j = 0; j<neps; j++)
			output(i,j) = hist[i][j] = 0.0;
	}

	for(i = 0; i<(blength-t); i++) {
		R_CheckUserInterrupt();
		for(j=i+t; j<blength; j++) {
			tmpd = 0.0;
			for(w=0; w<m; w++) {
				tmpd += sqr(series[i+w*d] - series[j+w*d]);
				hist[w][MIN((long) ( (log(tmpd) - lepsM )/a ), neps-1 )] ++;
			}
		}
	}

	for(i=0; i<m; i++)
		for(j = 0; j<neps; j++)
			output(i,j) = hist[i][j];
}
