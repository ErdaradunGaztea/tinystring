#' @export
new_alphabet <- function(letters) {
  stopifnot(is.character(letters))
  alphabet_ptr <- rcpp_alphabet(letters)
  structure(
    alphabet_ptr,
    class = "tstr_alphabet"
  )
}

#' @export
alphabet_width <- function(alphabet) {
  stopifnot(inherits(alphabet, "tstr_alphabet"))
  rcpp_get_alph_width(alphabet)
}
