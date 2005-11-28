sim.cont <- function(syst, start.time, end.time, dt, start.x, parms=NULL, obs.fun=function(x) x[1] ) {
	times <- seq(start.time, end.time, by=dt)
	series <- lsoda(start.x, times, func=syst, parms=parms)[,-1]
	series <- apply(series, 1, obs.fun)
	series <- ts(series, start=start.time, end=end.time, deltat=dt)
}
