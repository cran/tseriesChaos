\name{recurr}
\alias{recurr}
\title{Recurrence plot}
\description{
Recurrence plot
}
\usage{
recurr(series, m, d, end.time, eps, nt=10, ...)
}
\arguments{
  \item{series}{time series}
  \item{m}{embedding dimension}
  \item{d}{time delay}
  \item{end.time}{ending time (as no. of observations)}
  \item{eps}{neighbourhood threshold}
  \item{nt}{observations in each step}
  \item{...}{further parameters to be passed to \code{plot}}
}
\details{
Produces the recurrence plot, as proposed by Eckmann et al. (1987).
To reduce the number of points plotted (especially with highly sampled data), each \code{nt} observations, one single point is plotted.
}
\examples{
recurr(lorenz.ts, m=3, d=2, end.time=800,eps=3, nt=5, pch='.', cex=2)
}
\references{
Eckmann J.P., Oliffson Kamphorst S. and Ruelle D., Recurrence plots of dynamical systems, Europhys. Lett., volume 4, 973 (1987)
}
\author{Antonio, Fabio Di Narzo}
\keyword{ts}
