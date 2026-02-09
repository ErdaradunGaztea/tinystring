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

## Input length ----------------------------------------------------------------
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

# length<-.tstr ================================================================

## New length ------------------------------------------------------------------
test_that("works if new length smaller", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  new_length <- 2
  output <- input
  length(output) <- new_length

  expect_length(output, new_length)
  expect_identical(
    tstr_unpack(output),
    c("pamjjs", "sbp")
  )
})

test_that("works if new length larger", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  new_length <- 4
  output <- input
  length(output) <- new_length

  expect_length(output, new_length)
  expect_identical(
    tstr_unpack(output),
    c("pamjjs", "sbp", "suy", "")
  )
})

test_that("works if new length equal", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  new_length <- length(input)
  output <- input
  length(output) <- new_length

  expect_length(output, new_length)
  expect_identical(
    tstr_unpack(output),
    c("pamjjs", "sbp", "suy")
  )
})

## Input length ----------------------------------------------------------------
test_that("works if length was 0", {
  input <- tstr_pack(character())
  new_length <- 3
  output <- input
  length(output) <- new_length

  expect_length(output, new_length)
  expect_identical(
    tstr_unpack(output),
    rep("", times = new_length)
  )
})
