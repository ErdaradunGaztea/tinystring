## Input length ----------------------------------------------------------------
test_that("works for 1 string", {
  input <- tstr_pack("pamjjs")
  output <- tstr_length(input)

  expect_length(output, length(input))
  expect_equal(output, 6)
})

test_that("works for multiple strings", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  output <- tstr_length(input)

  expect_length(output, length(input))
  expect_equal(output, c(6, 3, 3))
})

test_that("works for 0 strings", {
  input <- tstr_pack(character())
  output <- tstr_length(input)

  expect_length(output, length(input))
  expect_equal(output, integer())
})
