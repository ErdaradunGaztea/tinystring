#' Collapse letters into manually defined groups
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  TinyString to modify.
#' @param ... \[`character()`\]\cr
#'  Groups to collapse. All elements of each vector are replaced with parameter name.
#' @param .unmentioned \[`character(1)`\]\cr
#'  What to do with letters not listed in `...`. If `NULL`, they are kept as-is. If `NA`, they are dropped and replaced
#'  with missing letter. If a single string, they are all replaced with this string.
#'
#' @return Modified TinyString.
#'
#' @export
tstr_gather <- function(x, ..., .unmentioned = NULL) {
  checkmate::assert_class(x, "tstr")

  stop("`tstr_gather()` not implemented")
  # rcpp_gather(x)
}
