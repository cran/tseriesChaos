false.nearest <- function(series, m, d, t, rt=10, eps=sd(series)/10) {
	res <- numeric(m)
	res2 <- numeric(m)
	for(i in 1:m) {
		a <- .C("falseNearest", series=as.double(series), length=as.integer(length(series)), m=as.integer(i), d=as.integer(d), t=as.integer(t), eps=as.double(eps), rt=as.double(rt), out=as.double(res[i]), out2=as.integer(res2[i]), PACKAGE="tseriesChaos")
		res[i] = a[["out"]]
		res2[i]= a[["out2"]]
	}
	res <- rbind(res, res2)
	rownames(res) <- c("fraction", "total")
	colnames(res) <- paste("m", 1:m, sep="")
	res
}
