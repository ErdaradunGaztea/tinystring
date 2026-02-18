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

## `collapse` parameter --------------------------------------------------------
test_that("empty `collapse` is the default behaviour", {
  expect_identical(
    tstr_pack(c("pamjjs", "sbp", "suy")) |>
      tstr_flatten(collapse = character()) |>
      tstr_unpack(),
    tstr_pack(c("pamjjs", "sbp", "suy")) |>
      tstr_flatten() |>
      tstr_unpack()
  )
})

test_that("`collapse` with a single element is equal to it being added between all elements", {
  expect_identical(
    tstr_pack(c("pamjjs", "sbp", "suy")) |>
      tstr_flatten(collapse = "x") |>
      tstr_unpack(),
    tstr_pack(c("pamjjs", "x", "sbp", "x", "suy")) |>
      tstr_flatten() |>
      tstr_unpack()
  )
})

test_that("`collapse` with multiple elements is equal to them all being added between all elements as substring", {
  expect_identical(
    tstr_pack(c("pamjjs", "sbp", "suy")) |>
      tstr_flatten(collapse = c("x", "f", "x")) |>
      tstr_unpack(),
    tstr_pack(c("pamjjs", "xfx", "sbp", "xfx", "suy")) |>
      tstr_flatten() |>
      tstr_unpack()
  )
})

test_that("`collapse` isn't applied with a single TinyString", {
  expect_identical(
    tstr_pack("pamjjs") |>
      tstr_flatten(collapse = "x") |>
      tstr_unpack(),
    tstr_pack("pamjjs") |>
      tstr_flatten() |>
      tstr_unpack()
  )
})

test_that("`collapse` isn't applied with a length 0 TinyString", {
  expect_identical(
    tstr_pack(character()) |>
      tstr_flatten(collapse = "x") |>
      tstr_unpack(),
    tstr_pack(character()) |>
      tstr_flatten() |>
      tstr_unpack()
  )
})

# TODO: Test handling `NA` and letters outside of alphabet
