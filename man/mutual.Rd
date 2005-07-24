\name{mutual}
\alias{mutual}
\title{Mutual information index}
\description{
Estimates the mutual information index a given time series for a specified number of lags
}
\usage{
mutual(series, partitions = 16, lag.max = 20)
}

\arguments{
  \item{series}{time series}
  \item{partitions}{number of bins}
  \item{lag.max}{largest lag}
}
\details{
Estimates the mutual information index for a specified lag.
The joint probability distribution function is estimated with a simple bi-dimensional density histogram.
}
\value{
The estimated mutual information index for each lag between 0 and \code{lag.max}.
}
\examples{
plot(0:20, mutual(lorenz.ts), type="b", xlab="lag", ylab="I", main="Mutual information Index", sub="Lorenz simulated time series")
}
\references{
Hegger, R., Kantz, H., Schreiber, T., Practical implementation of nonlinear time series methods: The TISEAN package; CHAOS 9, 413-435 (1999)
}
\author{ Antonio, Fabio Di Narzo }
\keyword{ts}
