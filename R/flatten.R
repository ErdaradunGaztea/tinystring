#' Flatten a string
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  TinyString to modify.
#' @param collapse \[`character()`\]\cr
#'  Separator to insert between strings; each element of the vector is treated as a separate letter. `NA` characters
#'  are allowed.
#'
#' @return TinyString with one element.
#'
#' @export
tstr_flatten <- function(x, collapse = character()) {
  stopifnot(inherits(x, "tstr"))
  stopifnot(is.character(collapse))

  stop("`tstr_flatten()` not implemented")
  # rcpp_flatten(x)
}
