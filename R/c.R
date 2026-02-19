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
  checkmate::assert_list(dots, types = "tstr", min.len = 1L)
  checkmate::assert_subset(dot_lengths, c(1L, max(dot_lengths)))
  checkmate::assert_character(sep)

  # All TinyStrings must have the same alphabet
  # (might change that in the future)
  alphabets <- lapply(dots, alphabet)
  checkmate::assert_true(
    alphabets[-1] |>
      vapply(function(x) { identical(x, alphabets[[1]]) }, logical(1)) |>
      all()
  )

  structure(
    rcpp_c(dots, sep),
    class = "tstr"
  )
}
