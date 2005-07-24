mutual <- function(series, partitions=16, lag.max=20) {
	series <- (series-min(series))/(diff(range(series)))
	corr <- numeric(lag.max+1)
	for(i in 0:lag.max) {
		hist <- matrix(0, partitions, partitions)
		hist <- .C("mutual", series=as.double(series), length=as.integer(length(series)), lag=as.integer(i), partitions=as.integer(partitions), hist=as.double(hist), PACKAGE="tseriesChaos")[["hist"]]
		hist <- matrix(hist, partitions, partitions)/sum(hist)
		histx <- apply(hist, 1, sum)
		hist <- hist[hist!=0]
		histx<- histx[histx!=0]
		corr[i+1] <- sum(hist*log(hist)) - 2*sum(histx*log(histx))
	}
	names(corr) <- paste(0:lag.max)
	corr
}
