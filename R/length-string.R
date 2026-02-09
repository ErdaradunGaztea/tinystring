#' Compute the length
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  A TinyString object.
#'
#' @return A numeric vector the same length as `x`.
#'
#' @examples
#' tstr_pack(c("rllssllsrrlr", "slllsr"), alphabet = c("s", "l", "r")) |>
#'   tstr_length()
#'
#' @export
tstr_length <- function(x) {
  checkmate::assert_class(x, "tstr")

  rcpp_length(x)
}
