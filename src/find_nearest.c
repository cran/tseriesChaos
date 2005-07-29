#include "tseriesChaos.h"

#define BIN(x, id, eps) ( (int) ( (x)[(id)]/(eps)) % BOX )
#define output(a,b) out[INDEX(a, b, ref)]

/*
Fill boxes for fast neighborhood search.
x: time series (scaled between 0 and 1)
m, d: embedding dimension and time delay
blength: total number of points in the embedding space
eps: neighborhood size
jh: a BOX*BOX array, i.e., the boxes histogram
jpntr: the boxes pointers
*/
void fill_boxes(double *x, int m, int d, int blength, double eps, int **jh, int *jpntr) {
	int i, j, binx, biny, offset;
	int next;

	offset = (m-1)*d;
	for (i=0; i<BOX; i++)
		for (j=0; j<BOX; j++)
			jh[i][j]=0;
	for (i=0; i<blength; i++) {
		binx = BIN(x, i, eps);
		biny = BIN(x, i+offset, eps);
		jh[binx][biny] ++;
	}
	for (i=0; i<(BOX*BOX-1); i++) {
		next = i+1;
		jh[(next - (next % BOX)) / BOX ][next % BOX] += 
			jh[(i - (i % BOX) ) / BOX ][i % BOX];
	}

	for (i=0; i<blength; i++) {
		binx = BIN(x, i, eps);
		biny = BIN(x, i+offset, eps);
		jpntr[--jh[binx][biny]] = i;
	}
}

/*
Find all neighbours of a specific point.
x: time series (scaled between 0 and 1)
m, d, t: embedding dimension, time delay and theiler window
n: considered point
jh: the boxes histogram as computed by fill_boxes
jpntr: the boxes pointers as computed by fill_boxes
blength: total number of points in the embedding space
eps: neighborhood size
founds: indexes of found points
dists: euclidean distances of found points
nfounds: total number of neighbours found
*/
void find_nearests(double *x, int m, int d, int t, int n, 
int **jh, int *jpntr, int blength,
double eps, int *founds, double *dists, int *nfounds) {
	int i, j, id, currx, start, end;
	int xbox, ybox;
	double tmpd;
	int md;

	xbox = BIN(x,n,eps);
	ybox = BIN(x, n+(m-1)*d, eps);
	md = m*d;
	(*nfounds)=0;
	eps = sqr(eps);

	for(i=xbox-1; i<(xbox+2); i++) {
	if ((i<0)||(i>=BOX)) continue;
	for(j=ybox-1; j<(ybox+2); j++) {
		if((j<0)||(j>=BOX)) continue;
		start= jh[i][j];
		end  = ((j+1)==BOX) ? (blength-1): jh[i][j+1];
		for(id=start; id<end; id++) {
			currx = jpntr[id];
			if (abs(currx-n)<=t) continue;
			DIST2EPS(x, n, currx, md, d, eps, tmpd);
			if (tmpd<eps) {
				dists[(*nfounds)++] = sqrt(tmpd);
				founds[(*nfounds)-1]= currx;
			}
		}
	}
	}

}

/*
Find k nearest neighbours of all points of a time series.
in_series: time series (scaled between 0 and 1)
m, d, t: embedding dimension, time delay and theiler window
length: length of the time series
eps: neighborhood size
ref: number of points to consider
in_k: max number of neighbours to search for each point
in_s: number of unit times to omit from the end
out: matrix of nearest neighbours
*/
void find_knearests(double *in_series, int *in_m, int *in_d, int *in_t,
	int *in_length, double *in_eps, int *in_ref, int *in_k, int *in_s, int *out) {
double eps, *series; 
int m,d, t, s, ref, k, length, blength;
int i,j,md;
double *dsts;
int id; int *ids;
int **jh, *jpntr;

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
/*
INIT VARIABLES
*/
	blength = length - (m-1)*d - s;
	md = m*d;
	for(i = 0; i<ref; i++) 
		for(j=0; j<k; j++) 
			output(i,j) = -1;
	dsts = (double*) R_alloc(blength, sizeof(double));
	ids = (int*) R_alloc(blength, sizeof(int));
	jpntr = (int*) R_alloc(blength, sizeof(int));
	jh = (int**) R_alloc(BOX, sizeof(int*));
	for(i=0; i<BOX; i++)
		jh[i] = (int*) R_alloc(BOX, sizeof(int));
	fill_boxes(series, m, d, blength, eps, jh, jpntr);
/**/

	for(i = 0; i<ref; i++) { /*for each reference point...*/
		find_nearests(series, m, d, t, i, jh, jpntr, blength, 	eps, ids, dsts, &id);
		R_qsort_I(dsts, ids, 1, id);
		for(j=0; (j<k) && (j<id); j++)
			output(i, j) = ids[j]+1;
	}/*end for each reference point*/
}
