load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "device_application",
    srcs = ["main.cc"],
    malloc = select({
        "@platforms//cpu:armv7e-m": "@pigweed//pw_malloc",
        "//conditions:default": "@bazel_tools//tools/cpp:malloc",
    }),
    visibility = ["//:__pkg__"],
    deps = [
        "//src/app/button",
        "//src/app/piston_control",
        "@pigweed//pw_chrono:system_clock",
        "@pigweed//pw_log",
        "@pigweed//targets:pw_assert_backend_impl",
    ] + select({
        "@platforms//cpu:armv7e-m": [
            "//targets/atsame54n20a:linker_script",
            "//targets/atsame54n20a:pre_init",
            "//src/bsp/atsame54n20a:init",
            "//src/bsp/atsame54n20a:peripheral",
            "//src/bsp/wrapper/sqr_wave:sqr_wave_same54",
            # Resolves dependencies to lib nano (_write, _read, etc) with stubs.
            "@pigweed//pw_toolchain/arm_gcc:arm_none_eabi_gcc_support",
        ],
    }),
)
