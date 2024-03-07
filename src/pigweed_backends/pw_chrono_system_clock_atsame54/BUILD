package(default_visibility = ["//visibility:public"])

cc_library(
    name = "impl",
    srcs = [
        "system_clock.cc",
    ],
    hdrs = [
        "public/pw_chrono_atsame54/system_clock_config.h",
        "public/pw_chrono_atsame54/system_clock_constants.h",
        "public_overrides/pw_chrono_backend/system_clock_config.h",
    ],
    includes = [
        "public",
        "public_overrides",
    ],
    target_compatible_with = [
        "@platforms//os:none",
    ],
    deps = [
        ":config_override",
        "//src/bsp/wrapper/sys_tick",
        "@pigweed//pw_chrono:epoch",
        "@pigweed//pw_chrono:system_clock_facade",
    ],
)

label_flag(
    name = "config_override",
    build_setting_default = "@pigweed//pw_build:default_module_config",
)
