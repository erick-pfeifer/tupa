cc_library(
  name = "base_headers",
  hdrs = [
    "definitions.h",
    "device_cache.h",
    "device.h",
    "interrupts.h",
    "toolchain_specifics.h",
  ],
  deps = ["@atsame54_device_pack//:same54n20a_deps"],
  includes = [ "." ],
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
    "peripheral/tcc/plib_tcc0.c",
    "peripheral/systick/plib_systick.c",
  ],

  copts = [
    "-Wno-old-style-declaration",
  ],
  hdrs = [
    "peripheral/systick/plib_systick.h",
    "peripheral/clock/plib_clock.h",
    "peripheral/cmcc/plib_cmcc.h",
    "peripheral/evsys/plib_evsys.h",
    "peripheral/nvic/plib_nvic.h",
    "peripheral/nvmctrl/plib_nvmctrl.h",
    "peripheral/port/plib_port.h",
    "peripheral/tcc/plib_tcc0.h",
    "peripheral/tcc/plib_tcc_common.h",
    "peripheral/sercom/usart/plib_sercom2_usart.h",
    "peripheral/sercom/usart/plib_sercom_usart_common.h",
  ],
  includes = [ "peripheral" ],
  deps = [
    ":base_headers",
    "@atsame54_device_pack//:same54n20a_deps",
  ],
  visibility = ["//visibility:public"],
)

cc_library(
    name = "init",
    srcs = [
      "initialization.c",
      "interrupts.c",
      "exceptions.c",
    ],
    copts = [
      "-Wno-unknown-pragmas",
      "-Wno-unused-parameter",
      "-Wno-missing-attributes",
    ],
    deps = [
      ":peripheral",
      ":base_headers",
      "@atsame54_device_pack//:same54n20a_deps",
    ],
    includes = [ "." ],
    visibility = ["//visibility:public"],
    alwayslink = 1,
)