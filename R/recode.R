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

  UseMethod("tstr_recode")
}

#' @rdname tstr_recode
#' @export
tstr_recode.tstr <- function(x, ...) {
  dots <- list(...)

  structure(
    rcpp_recode(x, dots),
    class = "tstr"
  )
}

#' @rdname tstr_recode
#' @export
tstr_recode.tstr_modifiable <- function(x, ...) {
  dots <- list(...)

  rcpp_ip_recode(x, dots)
}
