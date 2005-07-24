#include "tseriesChaos.h"

void falseNearest(double *in_series, int *in_length, int *in_m, int *in_d, int *in_t, double *in_eps, double *in_rt, double *out, int *out2) {

double eps, *series; 
double dst;
int m,d, t, length, blength;
int num, denum;
int i,j,w,md;
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
	blength = length - m*d - t;
	md = m*d;
	eps = sqr(eps);
	num=denum=0;
	
	for(i = 0; i<blength; i++) {
		id=0;
		for(j=0; j<blength; j++) {
			if(((i-t)<=j) && (j<=(i+t))) continue;
			dst=0.0;			
			for(w=0; (w<md) && (dst<eps); w+=d)
				dst += sqr(series[i+w] - series[j+w]);
			if(dst>=eps) continue;
			id++;
			dst = ( dst + sqr(series[i+w+d] - series[j+w+d]) )/ dst;
			if (dst>rt) num++;
		}
		denum+=id;		
	}
	(*out) = (double)num/(double)denum;
	(*out2)= denum;
}
