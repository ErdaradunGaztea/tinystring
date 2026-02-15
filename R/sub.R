#' Get substrings using their positions
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  A TinyString object.
#' @param start,end \[`integer(1)`\]\cr
#'  Indices defining the range of characters to extract (inclusive).
#'
#' @return A TinyString object the same length as `x`.
#'
#' @examples
#' tstr_pack(c("rllssllsrrlr", "slllsr"), alphabet = c("s", "l", "r")) |>
#'   tstr_sub(3, 6)
#'
#' @export
tstr_sub <- function(x, start = 1L, end = min(tstr_length(x))) {
  checkmate::assert_class(x, "tstr")
  checkmate::assert_int(start)
  checkmate::assert_int(end)

  structure(
    rcpp_sub(x, start, end),
    class = "tstr"
  )
}
