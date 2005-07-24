#include "tseriesChaos.h"

#define output(i, j) out_hist[(i)*partitions + (j)]

void mutual(double *in_series, int *in_length, int *in_lag, 
int *in_partitions, double *out_hist) {
	int partitions, length, lag;
	int ix, iy, binx, biny, i, j;
	double *series;

	series = in_series;
	length = *in_length;
	lag =*in_lag;
	partitions=*in_partitions;

	for(i =0; i<partitions; i++) 
		for(j=0; j<partitions; j++)
			output(i, j) = 0.0;

	for(ix = 0; ix < (length-lag); ix++) {
		iy = ix + lag;
		binx = MIN((int)(series[ix]*partitions),partitions-1);
		biny = MIN((int)(series[iy]*partitions),partitions-1);
		output(binx, biny) ++;
	}
}
