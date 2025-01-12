demo_strings <- tstr_pack(c("aixpabsj", "bixxyi", "xai"))

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

tstr_c(
  demo_strings, tstr_pack(c("aix"))
)

demo_strings |>
  tstr_sub(start = 1, end = 4) |>
  tstr_unpack()

c("vaiixaix", "bixvvx") |>
  tstr_pack(alphabet = c("i", "v", "x")) |>
  tstr_unpack()

c("vaiixaix", "bixvvx") |>
  tstr_pack(alphabet = c("i", "v", "x")) |>
  tstr_sub(start = 3, end = 5) |>
  tstr_unpack()
