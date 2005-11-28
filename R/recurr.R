recurr <- function(series, m, d, end.time, eps, nt=10, ...) {
	w <- (0:(m-1))*d
	dist <- function(i, j){
		sum((series[i+w]-series[j+w])^2)
	}

	checkEmbParms(series, m, d)
	if(eps <= 0) stop("eps must be positive")
	nt <- as.integer(nt)
	if(nt<=0) nt <- 1
	n <- length(series)-(m-1)*d
	if(end.time>n)  end.time <- n
	eps <- eps^2
	plot(0, xlim=c(0, end.time), ylim=c(0, end.time), type="n", main="recurrence plot", xlab="i", ylab="j")
	
	for(i in seq(1, end.time, by=nt)) 
		for(j in seq(i,end.time, by=nt))
			if(dist(i,j)<eps) points(c(i,j),c(j,i), ...)
}
