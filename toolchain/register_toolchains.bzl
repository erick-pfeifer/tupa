"""Dependency registration helpers for users of Pigweed.

Before loading this bzl file, you must first:

* Declare the Pigweed repository.
* Declare the pw_toolchain repository.
* Initialize the CIPD client repository.
"""

load(
    "@pigweed//pw_env_setup/bazel/cipd_setup:cipd_rules.bzl",
    "cipd_repository",
)
load(
    "@pw_toolchain//features/macos:generate_xcode_repository.bzl",
    "pw_xcode_command_line_tools_repository",
)

# buildifier: disable=unnamed-macro
def register_cxx_toolchains():
    """This function registers toolchains."""

    # Generate xcode repository on macOS.
    pw_xcode_command_line_tools_repository()

    # Fetch llvm toolchain.
    cipd_repository(
        name = "llvm_toolchain",
        build_file = "@pw_toolchain//build_external:llvm_clang.BUILD",
        path = "fuchsia/third_party/clang/${os}-${arch}",
        tag = "git_revision:8475d0a2b853f6184948b428ec679edf84ed2688",
    )

    # Fetch linux sysroot for host builds.
    cipd_repository(
        name = "linux_sysroot",
        path = "fuchsia/third_party/sysroot/linux",
        tag = "git_revision:d342388843734b6c5c50fb7e18cd3a76476b93aa",
    )

    # Fetch gcc-arm-none-eabi toolchain.
    cipd_repository(
        name = "gcc_arm_none_eabi_toolchain",
        build_file = "@pw_toolchain//build_external:gcc_arm_none_eabi.BUILD",
        path = "fuchsia/third_party/armgcc/${os}-${arch}",
        tag = "version:2@12.2.MPACBTI-Rel1.1",
    )

    native.register_toolchains(
        "//toolchain:gcc_device",
        "@pigweed//pw_toolchain/host_clang:host_cc_toolchain_linux",
        "@pigweed//pw_toolchain/host_clang:host_cc_toolchain_macos",
    )
