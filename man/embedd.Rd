\name{embedd}
\alias{embedd}
\title{Embedding of a time series}
\description{
Embedding of a time series with provided time delay and embedding dimension parameters.
}
\usage{
embedd(x, m, d, lags)
}
\arguments{
\item{x}{ time series}
\item{m}{ embedding dimension (if lags missed) }
\item{d}{ time delay (if lags missed) }
\item{lags}{ vector of lags (if m and d are missed) }
}
\details{
Embedding of a time series with provided delay and dimension parameters.
}
\value{
Matrix with columns corresponding to lagged time series.
}
\examples{
library(scatterplot3d)
x <- window(rossler.ts, start=90)
xyz <- embedd(x, m=3, d=8)
scatterplot3d(xyz, type="l")

## embedding multivariate time series
series <- cbind(seq(1,50),seq(101,150))
head(embedd(series, m=6, d=1))
}
\author{ Antonio, Fabio Di Narzo. Multivariate time series patch by Jonathan Shore.}
\keyword{ manip }
