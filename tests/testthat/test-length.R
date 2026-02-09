# length.tstr ==================================================================
expect_length_tstr <- function(input) {
  output <- length(input)

  expect_length(output, 1)
  expect_type(output, "integer")
  expect_equal(
    output,
    tstr_unpack(input) |>
      length()
  )
}

## Get length ------------------------------------------------------------------
test_that("works for 1 string", {
  expect_length_tstr(
    tstr_pack("pamjjs")
  )
})

test_that("works for multiple strings", {
  expect_length_tstr(
    tstr_pack(c("pamjjs", "sbp", "suy"))
  )
})

test_that("works for 0 strings", {
  expect_length_tstr(
    tstr_pack(character())
  )
})
