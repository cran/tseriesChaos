#include "tseriesChaos.h"

void follow_points(double *in_series, int *in_m, int *in_d, 
	int *in_length, int *in_nref, int *in_totref, int *in_k, 
	int *in_s, int *in_nearest, int *in_ref, double *lyap){

double *series; 
int m,d, s, nref, totref, k, length, *ref;

int i,j,a,b,w, time;
double tmp, res;
int **nearest;

/*
BIND PARAMETERS
*/
	m = *in_m;
	d = *in_d;
	s = *in_s;
	nref=*in_nref;
	totref=*in_totref;
	ref = in_ref;
	k = *in_k;
	series=in_series;
	length=*in_length;
	nearest= (int**) R_alloc(totref, sizeof(int*));
	for(i = 0; i<totref; i++) {
		nearest[i] = (int*) R_alloc(k, sizeof(int));
		for (j=0; j<k; j++) 
			nearest[i][j] = in_nearest[j*totref+i];
	}
	for(j=0; j<s; j++) lyap[j] = 0.0;
/**/

	for(time=0; time<s; time++) {
		for(i=0; i<nref; i++) { 
			tmp = 0.0;
			for(j=0; j<k; j++) {
				a = ref[i]+time-1; 
				b = nearest[ref[i]-1][j]+time-1;
				res=0.0;
				for(w=0; w<m*d; w+=d) res += sqr(series[a+w] - series[b+w]);
				tmp += sqrt(res);
			}
			lyap[time] += log(tmp/(double)k);
		}
		lyap[time] /= (double)nref;
	}
}
