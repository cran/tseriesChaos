lyap_k <- function(series, m, d, t, k=1, ref, s, eps) {
	checkEmbParms(series, m, d, t, s, ref)
	series <- as.ts(series)
	n <- length(series) - (m-1)*d - s 
	if(ref<0) ref <- n
	trash <- numeric()
	ref <- 1:ref
	cat("Finding nearests\n")
	nearest <- find_knearests(series, m=m, d=d, t=t, ref=length(ref), s=s, eps=eps, k=k)
	trash <- apply(nearest, 1, function(x) any(is.na(x)))
	ref <- ref[!trash]
	if(length(ref)==0) stop("not enough neighbours found")
	cat("Keeping ", length(ref)," reference points\n")
	cat("Following points\n")
	res <- follow_points(series, m=m, d=d, s=s, ref=ref, nearest=nearest, k=k)
	ts(res, freq=frequency(series), start=0)
}

lyap <- function(dsts, start, end) {
	dsts <- as.ts(dsts)
	sf <- window(dsts,start,end)
	start <- start(sf)[1]+(start(sf)[2]-1)/frequency(sf)
	end <- end(sf)[1]+(end(sf)[2]-1)/frequency(sf)
	lambda <- seq(start, end, by=1/frequency(dsts))
	lm(sf~lambda, data=data.frame(sf = sf, lambda = lambda))$coeff
}
