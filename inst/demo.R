demo_strings <- tstr_pack(c("aix", "bix", "xai"))

demo_strings |>
  tstr_recode("c" = "a", "v" = "x") |>
  tstr_unpack()

demo_strings |>
  length()

length(demo_strings) <- 2
demo_strings |>
  tstr_unpack()

length(demo_strings) <- 4
demo_strings |>
  tstr_unpack()

c("vaiixaix", "bix", "?", "xai") |>
  tstr_pack() |>
  tstr_length()

c("vaiixaix", "bix.", "@?", "xai") |>
  tstr_pack() |>
  tstr_unpack()

c("vaiixaix", "bix", "?", "xai") |>
  tstr_pack(alphabet = c("i", "v", "x")) |>
  tstr_unpack()

demo_strings |>
  tstr_flatten() |>
  tstr_unpack()
