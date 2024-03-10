load(
    "@pw_toolchain//cc_toolchain:defs.bzl",
    "pw_cc_flag_set",
    "pw_cc_toolchain",
)

pw_cc_flag_set(
    name = "o1",
    actions = [
        "@pw_toolchain//actions:all_c_compiler_actions",
        "@pw_toolchain//actions:all_cpp_compiler_actions",
        "@pw_toolchain//actions:all_link_actions",
    ],
    flags = ["-O0"],
)

pw_cc_flag_set(
    name = "warnings",
    actions = [
        "@pw_toolchain//actions:all_c_compiler_actions",
        "@pw_toolchain//actions:all_cpp_compiler_actions",
    ],
    flags = [
        "-Wall",
        "-Wextra",
        # Make all warnings errors, except for the exemptions below.
        "-Werror",
        "-Wno-error=cpp",  # preprocessor #warning statement
        "-Wno-error=deprecated-declarations",  # [[deprecated]] attribute
        "-Wno-psabi",  # Silence the really verbose ARM warnings.
    ],
)

pw_cc_flag_set(
    name = "thumb_abi",
    actions = [
        "@pw_toolchain//actions:all_asm_actions",
        "@pw_toolchain//actions:all_c_compiler_actions",
        "@pw_toolchain//actions:all_cpp_compiler_actions",
        "@pw_toolchain//actions:all_link_actions",
    ],
    flags = [
        "-mabi=aapcs",
        "-mthumb",
    ],
)

pw_cc_flag_set(
    name = "cortex_common",
    actions = [
        "@pw_toolchain//actions:all_c_compiler_actions",
        "@pw_toolchain//actions:all_cpp_compiler_actions",
    ],
    flags = [
        "-ffreestanding",
        "-specs=nano.specs",
        "-specs=nosys.specs",
    ],
)

pw_cc_flag_set(
    name = "cortex_common_link",
    actions = [
        "@pw_toolchain//actions:all_link_actions",
    ],
    flags = [
        "-Wl,--gc-sections",
        "-specs=nano.specs",
        "-specs=nosys.specs",
        "-lstdc++",
        "-lnosys",
        "-lc",
        "-lm",
        "-Wl,--no-warn-rwx-segment",
        "-Wl,-print-memory-usage",
    ],
)

pw_cc_flag_set(
    name = "cortex-m4",
    actions = [
        "@pw_toolchain//actions:all_asm_actions",
        "@pw_toolchain//actions:all_c_compiler_actions",
        "@pw_toolchain//actions:all_cpp_compiler_actions",
        "@pw_toolchain//actions:all_link_actions",
    ],
    flags = [
        "-mcpu=cortex-m4",
        "-mfloat-abi=hard",
    ],
)

pw_cc_toolchain(
    name = "arm_gcc_toolchain_cortex-m",
    action_config_flag_sets = [
        ":o1",
        "@pw_toolchain//flag_sets:c++17",
        "@pw_toolchain//flag_sets:debugging",
        "@pw_toolchain//flag_sets:reduced_size",
        "@pw_toolchain//flag_sets:no_canonical_prefixes",
        "@pw_toolchain//flag_sets:no_rtti",
        "@pw_toolchain//flag_sets:wno_register",
        "@pw_toolchain//flag_sets:wnon_virtual_dtor",
    ] + select({
        "@pw_toolchain//constraints/arm_mcpu:cortex-m4": [":cortex-m4"],
        "@pw_toolchain//constraints/arm_mcpu:none": ["@platforms//:incompatible"],
    }) + [
        ":thumb_abi",
        ":cortex_common",
        ":cortex_common_link",
        ":warnings",
    ],
    action_configs = [
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-ar",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-gcc",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-g++",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-gcov",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-ld",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-objcopy",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-objdump",
        "@gcc_arm_none_eabi_toolchain//:arm-none-eabi-strip",
    ],
    builtin_sysroot = "external/gcc_arm_none_eabi_toolchain",
    cxx_builtin_include_directories = [
        "%sysroot%/arm-none-eabi/include/newlib-nano",
        "%sysroot%/arm-none-eabi/include/c++/12.2.1",
        "%sysroot%/arm-none-eabi/include/c++/12.2.1/arm-none-eabi",
        "%sysroot%/arm-none-eabi/include/c++/12.2.1/backward",
        "%sysroot%/lib/gcc/arm-none-eabi/12.2.1/include",
        "%sysroot%/lib/gcc/arm-none-eabi/12.2.1/include-fixed",
        "%sysroot%/arm-none-eabi/include",
    ],
    supports_param_files = 0,
    target_compatible_with = select({
        "@pw_toolchain//constraints/arm_mcpu:cortex-m4": [],
        "@pw_toolchain//constraints/arm_mcpu:none": ["@platforms//:incompatible"],
    }),
    toolchain_identifier = "arm-gcc-toolchain",
)

toolchain(
    name = "gcc_device",
    target_compatible_with = [
        "@pw_toolchain//constraints/arm_mcpu:cortex-m4",
    ],
    toolchain = ":arm_gcc_toolchain_cortex-m",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
