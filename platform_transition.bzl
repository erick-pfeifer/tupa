def _device_transition_impl(settings, attr):
    # buildifier: disable=unused-variable
    _ignore = attr
    return {
        "//command_line_option:platforms": "//platforms:device",
        "@pigweed//targets:pw_malloc_backend": "//src/pigweed_backends/malloc:impl",
        "@pigweed//targets:pw_sys_io_backend": "//src/pigweed_backends/pw_sys_io_baremetal:impl",
        "@pigweed//targets:pw_log_backend": "@pigweed//pw_log_basic",
        "@pigweed//targets:pw_assert_backend": "@pigweed//pw_assert_basic",
    }

_device_transition = transition(
    implementation = _device_transition_impl,
    inputs = [],
    outputs = [
        "//command_line_option:platforms",
        "@pigweed//targets:pw_malloc_backend",
        "@pigweed//targets:pw_sys_io_backend",
        "@pigweed//targets:pw_log_backend",
        "@pigweed//targets:pw_assert_backend",
    ],
)

def _binary_impl(ctx):
    out = ctx.actions.declare_file(ctx.label.name)
    ctx.actions.symlink(output = out, target_file = ctx.executable.binary)
    return [DefaultInfo(files = depset([out]), executable = out)]

device_cc_binary = rule(
    _binary_impl,
    attrs = {
        "binary": attr.label(
            doc = "cc_binary to build for device target",
            cfg = _device_transition,
            executable = True,
            mandatory = True,
        ),
        "_allowlist_function_transition": attr.label(default = "@bazel_tools//tools/allowlists/function_transition_allowlist"),
    },
)
