load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("//:platform_transition.bzl", "device_cc_binary")

package(default_visibility = ["//visibility:public"])

device_cc_binary(
    name = "app.elf",
    binary = "//src:device_application",
)

refresh_compile_commands(
    name = "compile_commands_device",
    targets = {
        "//:app.elf": "--cpu=armv7e-m",
        "//src/app/piston_control:piston_control_test": "",
        "//src/app/buttons:buttons_test": "",
    },
)
