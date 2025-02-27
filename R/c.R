#' Join multiple strings
#'
#' @description
#' TODO
#'
#' @param ... \[`tstr()`\]\cr
#'  TinyStrings to join.
#' @param sep \[`character()`\]\cr
#'  Separator to insert between strings; each element of the vector is treated as a separate letter. `NA` characters
#'  are allowed.
#'
#' @return TinyString with as many elements as \link[vctrs::vec_size]{the common size} of the input.
#'
#' @export
tstr_c <- function(..., sep = character()) {
  dots <- list(...)
  dot_lengths <- lengths(dots)
  stopifnot(
    # All dots are TinyStrings
    all(vapply(dots, function(x) { inherits(x, "tstr") }, logical(1))),
    all(dot_lengths %in% c(1, max(dot_lengths)))
  )
  stopifnot(is.character(sep))

  stop("`tstr_c()` not implemented")
  # rcpp_c(dots, sep)
}
