#Author: Antonio, Fabio Di Narzo. Last Modified $Date: 2005/12/02 16:15:39 $
C2 <- function(series, m, d, t, eps){
	checkEmbParms(series, m, d, t)
	if(eps<=0) stop("eps must be positive")
	res <- numeric(1)
	.C("C2", series=as.double(series), m=as.integer(m), d=as.integer(d),
	length=as.integer(length(series)), t=as.integer(t), 
	eps=as.double(eps), res=as.double(res), PACKAGE="tseriesChaos")[["res"]]
}
