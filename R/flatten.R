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
#' @examples
#' tstr_pack(c("rllssllsrrlr", "slllsr"), alphabet = c("s", "l", "r")) |>
#'   tstr_flatten() |>
#'   tstr_unpack()
#'
#' @export
tstr_flatten <- function(x, collapse = character()) {
  checkmate::assert_class(x, "tstr")
  checkmate::assert_character(collapse)

  if (!identical(collapse, character())) {
    stop("Custom `collapse` parameter not yet supported")
  }

  structure(
    rcpp_flatten(x),
    # rcpp_flatten(x, collapse)
    class = "tstr"
  )
}
