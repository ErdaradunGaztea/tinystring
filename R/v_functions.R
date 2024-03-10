#' @export
tstr_pack <- function(x, alphabet = letters) {
  stopifnot(is.character(x))
  stopifnot(is.character(alphabet))

  structure(
    rcpp_pack(x, alphabet),
    class = "tstr"
  )
}

#' @export
tstr_unpack <- function(x) {
  stopifnot(inherits(x, "tstr"))
  rcpp_unpack(x)
}
