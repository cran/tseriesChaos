embedd <- function(x, m, d) {
	checkEmbParms(x, m, d)
	n <- length(x) - (m-1)*d
	res <- matrix(0, n, m)
	for(i in 1:m) res[,i] <- x[((i-1)*d+1):(n+(i-1)*d)]
	res
}
