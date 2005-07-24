find_nearest <- function(series, m, d, t, eps, ref, k, s){
	res <- numeric(ref*k)
	res <- .C("find_nearest", series=as.double(series), m=as.integer(m), d=as.integer(d), t=as.integer(t), length=as.integer(length(series)), eps=as.double(eps),ref=as.integer(ref), k=as.integer(k), s=as.integer(s), 
res=as.integer(res), PACKAGE="tseriesChaos")[["res"]]
	res[res==-1] <- NA;
	matrix(res, ref, k)
}
