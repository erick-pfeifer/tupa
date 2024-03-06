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
    ],
)

pw_cc_test(
    name = "buttons_test",
    srcs = ["buttons_test.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":buttons",
        "@pigweed//pw_unit_test:light",
    ],
)
