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
    ],
)

pw_cc_test(
    name = "piston_control_test",
    srcs = ["piston_control_test.cc"],
    visibility = ["//visibility:public"],
    deps = [":piston_control"],
)
