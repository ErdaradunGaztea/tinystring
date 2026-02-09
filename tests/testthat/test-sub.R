# tstr_sub() ===================================================================
expect_sub <- function(input, start, end) {
  output <- tstr_sub(input, start = start, end = end)

  expect_length(output, length(input))
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_sub(start = start, end = end)
  )

  output
}

expect_sub_positive <- function(input) {
  output <- expect_sub(input, start = 2, end = 4)
  expect_all_equal(
    tstr_length(output),
    4 - 2 + 1
  )
}

## Positive indices ------------------------------------------------------------
test_that("works for 1 string w/ positive indices", {
  expect_sub_positive(
    tstr_pack("pamjjs")
  )
})

test_that("works for multiple strings w/ positive indices", {
  expect_sub_positive(
    tstr_pack(c("pamjjs", "sbpaa", "suyvpsnna"))
  )
})

test_that("works for 0 strings w/ positive indices", {
  expect_sub(
    tstr_pack(character()),
    start = 2,
    end = 4
  )
})
