test_that("works for a single substitution", {
  input <- tstr_pack(c("pamjjs", "sbp", "suy"))
  output <- tstr_recode(input, "c" = "s")

  expect_length(output, length(input))
  expect_equal(
    tstr_length(output),
    tstr_length(input)
  )
  expect_equal(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_replace_all("s", "c")
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
  expect_equal(
    tstr_unpack(output),
    tstr_unpack(input) |>
      stringr::str_replace_all(c("s" = "c", "d" = "$", "p" = "%"))
  )
})
