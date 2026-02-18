test_that("returned alphabet is correct", {
  expect_identical(
    c("iguana", "sloth", "chameleon") |>
      tstr_pack(alphabet = letters) |>
      alphabet(),
    letters
  )

  expect_identical(
    c("rllssllsrr", "slllsrssl") |>
      tstr_pack(alphabet = c("s", "l", "r")) |>
      tstr_recode("u" = "s") |>
      alphabet(),
    c("u", "l", "r")
  )
})
