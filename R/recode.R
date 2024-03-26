#' Recode letters
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  TinyString to modify.
#' @param ... \[`character(1)`\]\cr
#'  Letters to recode; parameter names define target letters.
#'
#' @examples
#' tstr_pack(c("rllssllsrr", "slllsrssl"), alphabet = c("s", "l", "r")) |>
#'   tstr_recode("u" = "s") |>
#'   tstr_unpack()
#'
#' @export
tstr_recode <- function(x, ...) {
  stopifnot(inherits(x, "tstr"))
  dots <- list(...)
  stopifnot(
    # All dots are strings
    all(vapply(dots, is.character, logical(1))),
    # All strings are atomic
    all(lengths(dots) == 1),
    # All names exist
    !is.null(names(dots)),
    all(names(dots) != "")
  )

  rcpp_recode(x, dots)
}
