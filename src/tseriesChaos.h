#ifndef tseriesChaos_h
#define tseriesChaos_h

#include <math.h>
#include <R.h>

#define BOX 100
#define sqr(a) (a)*(a)
#define MIN(a,b) (a)<(b) ? (a) : (b)
#define MAX(a,b) (a)>(b) ? (a) : (b)

/*Converts [a][b] matrix notation to vector-type single index notation,
as used in R.
a: row number; b: col. number; nr: total number of rows*/
#define INDEX(a, b, nr) ( (b)*(nr) + (a))

/*Copy matrix 'mat' contents in vector 'vec'*/
int MVCONV_i, MVCONV_j;
#define MATRIX2VEC(mat, vec, nr, nc) \
	for(MVCONV_i=0; MVCONV_i<(nr); MVCONV_i++) \
		for(MVCONV_j=0; MVCONV_j<(nc); MVCONV_j++) \
			(vec)[INDEX(MVCONV_i, MVCONV_j, (nr))] = (mat)[MVCONV_i][MVCONV_j];

/*Copy vector 'vec' contents in matrix 'mat'*/
#define VEC2MATRIX(vec, mat, nr, nc) \
	for(MVCONV_i=0; MVCONV_i<(nr); MVCONV_i++) \
		for(MVCONV_j=0; MVCONV_j<(nc); MVCONV_j++) \
			(mat)[MVCONV_i][MVCONV_j] = (vec)[INDEX(MVCONV_i, MVCONV_j, (nr))];

int DIST2_i;
/*Squared euclidean distance between points 'a' and 'b',
in the time delay embedding space of time series 'x', with time delay
'd', embedding dimension*time-delay 'md'.
Result in 'out'.
*/
#define DIST2(x, a, b, md, d, out) \
	(out)=0.0; \
	for(DIST2_i=0; (DIST2_i<(md)); DIST2_i+=(d)) \
		(out)+=sqr(x[(a)+DIST2_i] - x[(b)+DIST2_i]);

/*Same as DIST2, but stops computation if result exceeds 'eps'
Result in 'out'.
*/
#define DIST2EPS(x, a, b, md, d, eps, out) \
	(out)=0.0; \
	for(DIST2_i=0; (DIST2_i<(md)) && ((out)<(eps)); DIST2_i+=(d)) \
		(out)+=sqr(x[(a)+DIST2_i] - x[(b)+DIST2_i]);


extern void fill_boxes(double *, int, int, int, double, int **, int *);
extern void find_nearests(double *, int, int, int, int, int **, int *,
	 int, double, int *, double *, int *);

#endif
