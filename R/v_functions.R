#' @export
tstr_pack <- function(x) {
  stopifnot(is.character(x))
  structure(
    rcpp_vpack(x),
    class = "tstr"
  )
}

#' @export
tstr_unpack <- function(x) {
  stopifnot(inherits(x, "tstr"))
  rcpp_vunpack(x)
}

#' @export
tstr_append_a <- function(x) {
  stopifnot(inherits(x, "tstr"))
  rcpp_append_a(x)
}
