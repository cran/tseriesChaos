#include "tseriesChaos.h"

#define output(a,b) out[(b)*ref + (a)]

void find_nearest(double *in_series, int *in_m, int *in_d, int *in_t,
	int *in_length, double *in_eps, int *in_ref, int *in_k, int *in_s, 
	int *out) {

double eps, *series; 
int m,d, t, s, ref, k, length, blength;

int i,j,w,md;
double *dsts;
int id; int *ids;

/*
BIND PARAMETERS
*/
	m = *in_m;
	d = *in_d;
	t = *in_t;
	s = *in_s;
	ref=*in_ref;
	k = *in_k;
	eps=*in_eps;
	series=in_series;
	length=*in_length;
/**/

	blength = length - (m-1)*d - s;
	md = m*d;
	for(i = 0; i<ref; i++) 
		for(j=0; j<k; j++) 
			output(i,j) = -1;
	dsts = (double*) R_alloc(blength, sizeof(double));
	ids = (int*) R_alloc(blength, sizeof(int));
	eps = sqr(eps);

	for(i = 0; i<ref; i++) {
		id=0;
		for(j=0; j<blength; j++) {
			if(((i-t)<=j) && (j<=(i+t))) continue;
			dsts[id]=0.0;
			for(w=0; (w<md) && (dsts[id]<eps); w+=d)
				dsts[id] += sqr(series[i+w] - series[j+w]);
			if(dsts[id]>=eps) continue;
			ids[id] = j;
			id++;
		}
		R_qsort_I(dsts, ids, 1, id);
		for(j=0; (j<k) && (j<id); j++)
			output(i, j) = ids[j]+1;
	}
}
