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
  # TODO: Consider importing {rlang} for list2() with extra features
  dots <- list(...)
  # All names exist and are not duplicated
  checkmate::assert_named(dots, type = "unique")
  for (el in dots) {
    # All dots are scalar strings
    checkmate::assert_string(el)
  }

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
