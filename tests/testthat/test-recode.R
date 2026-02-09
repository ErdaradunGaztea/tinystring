# tstr_recode() ================================================================
expect_recode <- function(input) {
  output <- tstr_recode(input, "c" = "s")

  expect_length(output, length(input))
  expect_equal(
    tstr_length(output),
    tstr_length(input)
  )
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_replace_all("s", "c")
  )
}

## Number of substitutions -----------------------------------------------------
test_that("works for a single substitution", {
  expect_recode(
    tstr_pack(c("pamjjs", "sbp", "suy"))
  )
})

test_that("works for multiple substitutions", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  output <- tstr_recode(input, "c" = "s", "$" = "d", "%" = "p")

  expect_length(output, length(input))
  expect_equal(
    tstr_length(output),
    tstr_length(input)
  )
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_replace_all(c("s" = "c", "d" = "$", "p" = "%"))
  )
})

## Input length ----------------------------------------------------------------
test_that("works for 1 string", {
  expect_recode(
    tstr_pack("pamjjs")
  )
})

test_that("works for multiple strings", {
  expect_recode(
    tstr_pack(c("pamjjs", "sbp", "suy"))
  )
})

test_that("works for 0 strings", {
  expect_recode(
    tstr_pack(character())
  )
})
