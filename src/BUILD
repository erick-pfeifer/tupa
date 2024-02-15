load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "device_application",
    srcs = ["main.cc"],
    visibility = ["//:__pkg__"],
    copts = ["-std=c++17"],
    malloc = select({
        "@platforms//cpu:armv7e-m": "@pigweed//pw_malloc",
        "//conditions:default": "@bazel_tools//tools/cpp:malloc",
    }),
    deps = [
        "@pigweed//pw_log",
        "@pigweed//targets:pw_assert_backend_impl",
    ] + select ({
        "@platforms//cpu:armv7e-m": [
            "//targets/atsame54n20a:linker_script",
            "//targets/atsame54n20a:pre_init",
            "//src/bsp/atsame54n20a:init",
            "//src/bsp/atsame54n20a:peripheral",
            "//src/bsp/wrapper/sqr_wave",
            # Resolves dependencies to lib nano (_write, _read, etc) with stubs.
            "@pigweed//pw_toolchain/arm_gcc:arm_none_eabi_gcc_support",
        ]
    }),
)
