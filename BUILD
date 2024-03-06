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
        # Test files are failing to build with these options,
        # need to figure out the proper way to add them here.
        # "//src/app/piston_control:piston_control_test": "--cpu=x86_64",
        # "//src/app/buttons:buttons_test": "--cpu=x86_64",
    },
)
