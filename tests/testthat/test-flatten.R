## Input length -------------------------------------------------------------------------------------------------------
test_that("works for 1 string", {
  input <- tstr_pack("pamjjs")
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_unpack(output),
    tstr_unpack(input)
  )
})

test_that("works for multiple strings", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_unpack(output),
    "pamjjssbpsuy"
  )
})

test_that("works for 0 strings", {
  input <- tstr_pack(character())
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(tstr_unpack(output), "")
})

## Empty values -------------------------------------------------------------------------------------------------------
test_that("ignores empty strings in the middle", {
  input <- tstr_pack(c("pamjjs", "", "sbp", "", "suy"))
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_unpack(output),
    "pamjjssbpsuy"
  )
})

test_that("ignores empty strings at the beginning", {
  input <- tstr_pack(c("", "", "pamjjs", "suy"))
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_unpack(output),
    "pamjjssuy"
  )
})

test_that("ignores empty strings at the end", {
  input <- tstr_pack(c("pamjjs", "suy", "", ""))
  output <- tstr_flatten(input)

  expect_length(output, 1)
  expect_equal(
    tstr_unpack(output),
    "pamjjssuy"
  )
})
