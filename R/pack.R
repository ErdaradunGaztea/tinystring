#' Create compressed string representation
#'
#' @description
#' TODO
#'
#' @param x \[`character()`\]\cr
#'  A character vector to compress.
#' @param alphabet \[`character()`\]\cr
#'  Set of "letters" to use when compressing `x`.
#'
#' @return A TinyString object the same length as `x`.
#'
#' @export
tstr_pack <- function(x, alphabet = letters) {
  checkmate::assert_character(x)
  checkmate::assert_character(alphabet, max.len = 2^8 - 1)

  structure(
    rcpp_pack(x, alphabet),
    class = "tstr"
  )
}

#' Decompress a TinyString object
#'
#' @description
#' TODO
#'
#' @param x \[`tstr()`\]\cr
#'  A TinyString object.
#'
#' @return A character vector the same length as `x`.
#'
#' @export
tstr_unpack <- function(x) {
  checkmate::assert_class(x, "tstr")

  rcpp_unpack(x)
}
