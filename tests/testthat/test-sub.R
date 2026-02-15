# tstr_sub() ===================================================================
expect_sub <- function(input, start, end) {
  output <- tstr_sub(input, start = start, end = end)

  expect_length(output, length(input))
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_sub(start = start, end = end)
  )
}

## Positive indices ------------------------------------------------------------
test_that("works for 1 string w/ positive indices", {
  expect_sub(
    tstr_pack("iguana"),
    start = 2, end = 4
  )
})

test_that("works for multiple strings w/ positive indices", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 2, end = 4
  )
})

test_that("works for 0 strings w/ positive indices", {
  expect_sub(
    tstr_pack(character()),
    start = 2, end = 4
  )
})

test_that("end index past string length returns string till its end", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 4, end = 8
  )
})

test_that("start index past string length results in an empty string", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 8, end = 11
  )
})

## Negative indices ------------------------------------------------------------
test_that("works for 1 string w/ positive indices", {
  expect_sub(
    tstr_pack("iguana"),
    start = -4, end = -2
  )
})

test_that("works for multiple strings w/ positive indices", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -4, end = -2
  )
})

test_that("works for 0 strings w/ positive indices", {
  expect_sub(
    tstr_pack(character()),
    start = -4, end = -2
  )
})

test_that("negative start index past string length returns string from its start", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -8, end = -4
  )
})

test_that("negative end index past string length results in an empty string", {
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -11, end = -8
  )
})

## Mixed indices ---------------------------------------------------------------
test_that("negative start w/ positive end", {
  # start always before end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -5, end = 5
  )
  # start always after end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -2, end = 2
  )
  # start sometimes after end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = -3, end = 4
  )
})

test_that("positive start w/ negative end", {
  # start always before end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 2, end = -2
  )
  # start always after end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 5, end = -5
  )
  # start sometimes after end
  expect_sub(
    tstr_pack(c("iguana", "sloth", "chameleon")),
    start = 3, end = -4
  )
})
