d2 <- function(series, m, d, t, eps.min, neps=100) {
	checkEmbParms(series, m, d, t)
	if(eps.min<=0) stop("eps.min must be positive")
	neps <- as.integer(neps)
	if(neps<=0) neps <- 100
	res <- numeric(neps*m)
	eps.max <- diff(range(series))*sqrt(m)
	res <- .C("d2", series=as.double(series), length=as.integer(length(series)), m=as.integer(m), d=as.integer(d), t=as.integer(t), neps=as.integer(neps), eps.max=as.double(eps.max), eps.min=as.double(eps.min), res=as.double(res), 
	PACKAGE="tseriesChaos")[["res"]]
	res <- matrix(res, neps, m)
	res <- res[neps:1,]
	denom <- length(series) - (m-1)*d
	denom <- (denom-t+1)*(denom-t)/2
	res <- apply(res, 2, cumsum)/denom
	a <- -log(eps.min/eps.max)/(neps-1)
	eps <- eps.max*exp((1-1:neps)*a)
	eps <- eps[neps:1]
	res <- cbind(eps, res)
	colnames(res) <- c("eps",paste("m", 1:m,sep=""))
	plot(res[,c(1,m+1)], type="l", log="xy", main="Sample correlation integral", xlab=expression(epsilon), ylab=expression(C(epsilon)))
	for(i in m:2) lines(res[,c(1,i)])
	invisible(res)
}
