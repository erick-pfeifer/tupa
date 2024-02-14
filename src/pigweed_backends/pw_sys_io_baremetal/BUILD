package(default_visibility = ["//visibility:public"])

cc_library(
    name = "impl",
    srcs = ["sys_io_baremetal.cc"],
    target_compatible_with = [
        "@platforms//os:none",
    ],
    deps = [
        "//src/bsp/atsame54n20a:peripheral",
        "@pigweed//pw_sys_io:facade",
    ],
)
