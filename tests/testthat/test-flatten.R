# tstr_flatten() ===============================================================
expect_flatten <- function(input) {
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_length(output),
    sum(tstr_length(input))
  )
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_flatten()
  )
}

## Input length ----------------------------------------------------------------
test_that("works for 1 string", {
  expect_flatten(
    tstr_pack("pamjjs")
  )
})

test_that("works for multiple strings", {
  expect_flatten(
    tstr_pack(c("pamjjs", "sbp", "suy"))
  )
})

test_that("works for 0 strings", {
  expect_flatten(
    tstr_pack(character())
  )
})

## Empty values ----------------------------------------------------------------
test_that("ignores empty strings in the middle", {
  expect_flatten(
    tstr_pack(c("pamjjs", "", "sbp", "", "suy"))
  )
})

test_that("ignores empty strings at the beginning", {
  expect_flatten(
    tstr_pack(c("", "", "pamjjs", "suy"))
  )
})

test_that("ignores empty strings at the end", {
  expect_flatten(
    tstr_pack(c("pamjjs", "suy", "", ""))
  )
})
