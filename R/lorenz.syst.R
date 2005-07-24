lorenz.syst <- function(t, input, parms){
	x <- input[1]
	y <- input[2]
	z <- input[3]

	a <- parms[1]
	b <- parms[2]
	c <- parms[3]

	dx <- a * (y - x)
	dy <- x * (b - z) - y
	dz <- x * y + c * z

	list(c(dx, dy, dz))
}
