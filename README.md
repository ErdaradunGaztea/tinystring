
<!-- README.md is generated from README.Rmd. Please edit that file -->

# tinystring

<!-- badges: start -->

[![R-CMD-check](https://github.com/ErdaradunGaztea/tinystring/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/ErdaradunGaztea/tinystring/actions/workflows/R-CMD-check.yaml)
[![Codecov test
coverage](https://codecov.io/gh/ErdaradunGaztea/tinystring/graph/badge.svg)](https://app.codecov.io/gh/ErdaradunGaztea/tinystring)
<!-- badges: end -->

{tinystring} is an R package focused on optimized string storage. It
uses sub-byte, fixed-width character storage. This is achieved by
specifying an “alphabet” of allowed characters; the best known example
of that is the DNA alphabet of four characters: A, C, T, and G.

## Installation

You can install the development version of tinystring from
[GitHub](https://github.com/) with:

``` r
# install.packages("pak")
pak::pak("ErdaradunGaztea/tinystring")
```
