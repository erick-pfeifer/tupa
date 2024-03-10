load(
    "@pigweed//pw_build:pigweed.bzl",
    "pw_cc_test",
)

cc_library(
    name = "piston_control",
    srcs = ["piston_control.cc"],
    hdrs = ["public/piston_control/piston_control.h"],
    includes = ["public/"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/app/button",
        "//src/bsp/wrapper/sqr_wave",
        "@pigweed//pw_chrono:system_clock",
        "@pigweed//pw_function",
        "@pigweed//pw_log",
        "@pigweed//pw_status",
    ],
)

pw_cc_test(
    name = "piston_control_test",
    srcs = ["piston_control_test.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":piston_control",
        "//src/app/button",
        "//src/app/button:fake_button",
        "//src/bsp/wrapper/sqr_wave:fake_sqr_wave",
        "@pigweed//pw_chrono:simulated_system_clock",
        "@pigweed//pw_unit_test:light",
    ],
)
