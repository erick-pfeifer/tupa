cc_library(
    name = "base_headers",
    hdrs = [
        "definitions.h",
        "device.h",
        "device_cache.h",
        "interrupts.h",
        "toolchain_specifics.h",
    ],
    includes = ["."],
    deps = ["@atsame54_device_pack//:same54n20a_deps"],
)

cc_library(
    name = "peripheral",
    srcs = [
        "peripheral/clock/plib_clock.c",
        "peripheral/cmcc/plib_cmcc.c",
        "peripheral/evsys/plib_evsys.c",
        "peripheral/nvic/plib_nvic.c",
        "peripheral/nvmctrl/plib_nvmctrl.c",
        "peripheral/port/plib_port.c",
        "peripheral/sercom/usart/plib_sercom2_usart.c",
        "peripheral/systick/plib_systick.c",
        "peripheral/tcc/plib_tcc0.c",
    ],
    hdrs = [
        "peripheral/clock/plib_clock.h",
        "peripheral/cmcc/plib_cmcc.h",
        "peripheral/evsys/plib_evsys.h",
        "peripheral/nvic/plib_nvic.h",
        "peripheral/nvmctrl/plib_nvmctrl.h",
        "peripheral/port/plib_port.h",
        "peripheral/sercom/usart/plib_sercom2_usart.h",
        "peripheral/sercom/usart/plib_sercom_usart_common.h",
        "peripheral/systick/plib_systick.h",
        "peripheral/tcc/plib_tcc0.h",
        "peripheral/tcc/plib_tcc_common.h",
    ],
    copts = [
        "-Wno-old-style-declaration",
    ],
    includes = ["peripheral"],
    visibility = ["//visibility:public"],
    deps = [
        ":base_headers",
        "@atsame54_device_pack//:same54n20a_deps",
    ],
)

cc_library(
    name = "init",
    srcs = [
        "exceptions.c",
        "initialization.c",
        "interrupts.c",
    ],
    copts = [
        "-Wno-unknown-pragmas",
        "-Wno-unused-parameter",
        "-Wno-missing-attributes",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
    deps = [
        ":base_headers",
        ":peripheral",
        "@atsame54_device_pack//:same54n20a_deps",
    ],
    alwayslink = 1,
)
