load(
    "@pigweed//pw_build:pigweed.bzl",
    "pw_cc_test",
)

cc_library(
    name = "buttons",
    srcs = ["buttons.cc"],
    hdrs = ["public/buttons/buttons.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        "@pigweed//pw_chrono:system_clock",
        "@pigweed//pw_function",
        "@pigweed//pw_status",
    ],
)

pw_cc_test(
    name = "buttons_test",
    srcs = ["buttons_test.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":buttons",
        "//src/bsp/wrapper/gpio:fake_gpio",
        "@pigweed//pw_chrono:simulated_system_clock",
        "@pigweed//pw_unit_test:light",
    ],
)
