alphabet <- function(x) {
  checkmate::assert_class(x, "tstr")

  rcpp_alphabet(x)
}
