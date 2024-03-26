#' Compute the length
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  A TinyString object.
#'
#' @return A numeric vector the same length as `x`.
#'
#' @export
tstr_length <- function(x) {
  stopifnot(inherits(x, "tstr"))

  rcpp_length(x)
}
