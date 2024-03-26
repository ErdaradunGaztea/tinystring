#' Number of TinyStrings
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  A TinyString object.
#'
#' @return A single integer with the number of strings.
#'
#' @export
length.tstr <- function(x) {
  rcpp_length(x)
}

#' @rdname length.tstr
#' @export
`length<-.tstr` <- function(x, value) {
  stopifnot(rlang::is_scalar_integerish(value, finite = TRUE))

  rcpp_set_length(x, value)
}
