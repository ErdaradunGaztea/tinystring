# tstr_c() =====================================================================
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
test_that("works if multiple TinyStrings passed", {
  input_1 <- tstr_pack(c("iguana", "sloth", "chameleon"))
  input_2 <- tstr_pack(c("eats", "sleeps", "sees"))
  input_3 <- tstr_pack(c("worms", "much", "everything"))

  output <- tstr_c(input_1, input_2, input_3)

  expect_length(output, length(input_1))
  expect_equal(
    tstr_length(output),
    tstr_length(input_1) + tstr_length(input_2) + tstr_length(input_3)
  )
  expect_identical(
    tstr_unpack(output),
    stringr::str_c(
      tstr_unpack(input_1),
      tstr_unpack(input_2),
      tstr_unpack(input_3)
    )
  )
})

test_that("passing a single TinyString returns the original value", {
  input_1 <- tstr_pack(c("iguana", "sloth", "chameleon"))
  output <- tstr_c(input_1)

  expect_length(output, length(input_1))
  expect_equal(
    tstr_length(output),
    tstr_length(input_1)
  )
  expect_identical(
    tstr_unpack(output),
    tstr_unpack(input_1)
  )
})

## TinyString sizes ------------------------------------------------------------
test_that("can mix TinyStrings of sizes 1 and more than one (per recycling rules)", {
  input_1 <- tstr_pack(c("iguana", "sloth", "chameleon"))
  input_2 <- tstr_pack("sees")
  input_3 <- tstr_pack(c("worms", "much", "everything"))

  output <- tstr_c(input_1, input_2, input_3)

  expect_length(output, length(input_1))
  expect_equal(
    tstr_length(output),
    tstr_length(input_1) + tstr_length(input_2) + tstr_length(input_3)
  )
  expect_identical(
    tstr_unpack(output),
    stringr::str_c(
      tstr_unpack(input_1),
      tstr_unpack(input_2),
      tstr_unpack(input_3)
    )
  )
})

# TODO: `sep` parameter tests
