#include "tseriesChaos.h"
#define MEPS 1000
#define MFRAC 10

void stplot(double *in_series, int *in_length, int *in_m, int *in_d, int *in_steps, int *in_idt, double *in_epsmax, double *out) {
	double tmp, need;
	int i,j, a, b, w, md, is, ieps, length, blength, m, d, steps, idt;
	double epsmax, *series, *hist, **stp;

	series = in_series;
	length = *in_length;
	m = *in_m;
	d = *in_d;
	md = m*d;
	steps = *in_steps;
	idt = *in_idt;
	epsmax = sqr(*in_epsmax);
	blength = length - (m-1)*d;

	stp = (double**) R_alloc(MFRAC, sizeof(double*));
	for(i=0; i<MFRAC; i++) stp[i] = (double*) R_alloc(steps, sizeof(double));
	hist = (double*) R_alloc(MEPS, sizeof(double));

	for(i=0; i<steps; i++) {
		for(j=0; j<MEPS; j++) hist[j] = 0.0;
		for(j=0; j<(blength-i*idt); j++) {
			a = j; b = j+i*idt;
			tmp=0.0;
			for(w=0; w<md; w+=d) tmp += sqr(series[a+w]-series[b+w]);
			hist[MIN((long)(tmp*MEPS/epsmax), MEPS-1)]++;
		}
		for(j=0; j<MFRAC; j++) {
			need = (blength - i*idt)*(j+1)/(double) MFRAC;
			for(is=0, ieps=0; ieps<MEPS && is<need; ieps++)
				is +=hist[ieps];
			stp[j][i] = ieps*(epsmax/(double)MEPS);
		}
	}
	for(i=0; i<steps; i++) for(j=0; j<MFRAC; j++) 
		out[i*MFRAC+j] = sqrt(stp[j][i]);
}
