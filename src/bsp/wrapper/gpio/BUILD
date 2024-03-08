cc_library(
    name = "gpio",
    srcs = ["gpio.cc"],
    hdrs = ["public/gpio/gpio_wrapper.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/bsp/atsame54n20a:peripheral",
    ],
)

cc_library(
    name = "fake_gpio",
    hdrs = ["public/gpio/fake_gpio.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
)
