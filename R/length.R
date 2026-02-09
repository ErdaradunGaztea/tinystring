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
  rcpp_num_strings(x)
}

#' @rdname length.tstr
#' @export
`length<-.tstr` <- function(x, value) {
  checkmate::assert_count(value)

  rcpp_set_length(x, value)
}
