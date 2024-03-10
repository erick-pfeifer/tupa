cc_library(
    name = "sqr_wave",
    hdrs = ["public/sqr_wave/sqr_wave.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        "@pigweed//pw_log",
    ],
)

cc_library(
    name = "sqr_wave_same54",
    srcs = ["sqr_wave_same54.cc"],
    hdrs = ["public/sqr_wave/sqr_wave_same54.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        ":sqr_wave",
        "//src/bsp/atsame54n20a:peripheral",
        "//src/bsp/wrapper/gpio",
        "@pigweed//pw_log",
    ],
)

cc_library(
    name = "fake_sqr_wave",
    hdrs = ["public/sqr_wave/fake_sqr_wave.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        ":sqr_wave",
    ],
)
