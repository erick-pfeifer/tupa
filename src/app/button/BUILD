load(
    "@pigweed//pw_build:pigweed.bzl",
    "pw_cc_test",
)

cc_library(
    name = "button",
    srcs = ["button.cc"],
    hdrs = ["public/button/button.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        "@pigweed//pw_chrono:system_clock",
        "@pigweed//pw_function",
        "@pigweed//pw_status",
    ],
)

cc_library(
    name = "fake_button",
    hdrs = ["public/button/fake_button.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        ":button",
        "//src/bsp/wrapper/gpio:fake_gpio",
        "@pigweed//pw_status",
    ],
)

pw_cc_test(
    name = "button_test",
    srcs = ["button_test.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":button",
        "//src/bsp/wrapper/gpio:fake_gpio",
        "@pigweed//pw_chrono:simulated_system_clock",
        "@pigweed//pw_unit_test:light",
    ],
)
