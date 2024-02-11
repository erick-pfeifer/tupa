package(default_visibility = ["//visibility:public"])

platform(
    name = "host",
    constraint_values = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
)

platform(
    name = "device",
    constraint_values = [
        "@platforms//cpu:armv7e-m",
        "@platforms//os:none",
        # Target the cortex-m4. Bazel selects the right toolchain based on
        # this.
        "@pw_toolchain//constraints/arm_mcpu:cortex-m4",
    ],
)
