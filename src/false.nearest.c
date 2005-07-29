#include "tseriesChaos.h"

/*
False nearest neighbours algorithm.
in_series: input time series (scaled between 0 and 1)
in_length: time series length
in_m, in_d, in_t: embedding dimension, time delay, theiler window
in_eps: neighbourhood size
in_rt: escape factor
out: fraction of false nearests
out2: total number of nearests
*/
void falseNearest(double *in_series, int *in_length, int *in_m, int *in_d, int *in_t, double *in_eps, double *in_rt, double *out, int *out2) {

double eps, *series; 
double dst;
double *dsts;
int *ids, *jpntr, **jh;
int m,d, t, length, blength;
int num, denum;
int i,j,md;
double rt;
int id;

/*
BIND PARAMETERS
*/
	m = *in_m;
	d = *in_d;
	t = *in_t;
	rt = *in_rt;
	eps=*in_eps;
	series=in_series;
	length=*in_length;
/**/
/*
INIT VARIABLES
*/
	blength = length - m*d - t;
	md = m*d;
	num=denum=0;
	ids = (int*) R_alloc(blength, sizeof(int));
	dsts = (double*) R_alloc(blength, sizeof(double));
	jpntr = (int*) R_alloc(blength, sizeof(int));
	jh = (int**) R_alloc(BOX, sizeof(int*));
	for(i=0; i<BOX; i++)
		jh[i] = (int*) R_alloc(BOX, sizeof(int));
	fill_boxes(series, m, d, blength, eps, jh, jpntr);
/**/
	
	for(i = 0; i<blength; i++) { /*for each point...*/
		find_nearests(series, m, d, t, i, jh, jpntr, blength, 	eps, ids, dsts, &id); /*fill list of neighbours*/
		for(j=0; j<id; j++) { /*for each neighbour...*/
			dst = sqr(dsts[j]); /*take (quadratic) distance*/
			dst = (  dst + sqr(series[i+md] - series[ids[j]+md]) )/ dst; /*compute ratio*/
			if (dst>rt) num++; /*if ratio > rt, we have another false neighbour*/
		} /*end for each neighbour*/
		denum+=id; /*add no. of neighbours founds to total no.  of neighbours*/
	} /*end for each point*/
	(*out) = (denum!=0) ? (double)num/(double)denum : (-1); /*this is the fraction of false neighbours*/
	(*out2)= denum; /*this is the total number of neighbours*/
}
