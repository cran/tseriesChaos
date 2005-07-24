duffing.syst <- function(t, input, parms){
	x <- input[1]
	y <- input[2]
	z <- input[3]

	c <- parms[1]
	F <- parms[2]
	omega <- parms[3]

	dx <- y
	dy <- x * (1 - x^2) - c*y + F*cos(z)
	dz <- omega

	list(c(dx, dy, dz))
}
