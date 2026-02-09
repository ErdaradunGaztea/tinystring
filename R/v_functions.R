#' @export
tstr_pack <- function(x, alphabet = letters) {
  checkmate::assert_character(x)
  checkmate::assert_character(alphabet, max.len = 2^8 - 1)

  structure(
    rcpp_pack(x, alphabet),
    class = "tstr"
  )
}

#' @export
tstr_unpack <- function(x) {
  checkmate::assert_class(x, "tstr")

  rcpp_unpack(x)
}
