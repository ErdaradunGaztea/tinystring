# tstr_length() ================================================================
expect_string_length <- function(input) {
  output <- tstr_length(input)

  expect_length(output, length(input))
  expect_type(output, "integer")
  expect_equal(
    output,
    tstr_unpack(input) |>
      stringr::str_length()
  )
}

## Input length ----------------------------------------------------------------
test_that("works for 1 string", {
  expect_string_length(
    tstr_pack("pamjjs")
  )
})

test_that("works for multiple strings", {
  expect_string_length(
    tstr_pack(c("pamjjs", "sbp", "suy"))
  )
})

test_that("works for 0 strings", {
  expect_string_length(
    tstr_pack(character())
  )
})
