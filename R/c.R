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
#' @return TinyString with as many elements as [the common size][vctrs::vec_size()] of the input.
#'
#' @export
tstr_c <- function(..., sep = character()) {
  dots <- list(...)
  dot_lengths <- lengths(dots)

  # All dots are TinyStrings
  # TODO: Should this function allow passing characters that would be then coerced to TinyStrings?
  checkmate::assert_list(dots, types = "tstr")
  checkmate::assert_subset(dot_lengths, c(1, max(dot_lengths)))
  checkmate::assert_character(sep)

  stop("`tstr_c()` not implemented")
  # structure(
  #   rcpp_c(dots, sep),
  #   class = "tstr"
  # )
}
