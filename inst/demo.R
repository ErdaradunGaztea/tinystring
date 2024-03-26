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

tstr_pack(c("vaiixaix", "bix", "?", "xai")) |>
  tstr_length()

tstr_pack(c("vaiixaix", "bix.", "@?", "xai")) |>
  tstr_unpack()
