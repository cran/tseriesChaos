\name{embedd}
\alias{embedd}
\title{Embedding of a time series}
\description{
Embedding of a time series with provided time delay and embedding dimension parameters.
}
\usage{
embedd(x, m, d)
}
\arguments{
\item{x}{ time series}
\item{m}{ embedding dimension }
\item{d}{ time delay }
}
\details{
Embedding of a time series with provided delay and dimension parameters.
}
\value{
Matrix with columns corresponding to lagged time series.
}
\examples{
library(scatterplot3d)
xyz <- embedd(rossler.ts, m=3, d=8)
colnames(xyz) <- c("x","y","z")
scatterplot3d(xyz, type="l", xlab=expression(x[t]), ylab=expression(x[t+tau]), zlab=expression(x[t+2*tau]))
}
\author{ Antonio, Fabio Di Narzo }
\keyword{ manip }
