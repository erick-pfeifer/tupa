# tupa

Control of a stepper motor for a press machine as an excercise to use
Pigweed and Bazel.

## Setup

1. Make sure submodules have been cloned: `git submodule update`.
1. Bootstrap Pigweed with `source bootstrap.sh` (from the project root dir).
1. Install presubmit git-hooks with `pw presubmit --install`.
1. Modify `pw_malloc_freelist` to always link (check `Current Issues` section).
1. To build the application code: `bazel build //:app.elf`.
1. To run unit tests on app modules: `bazel test //src/app/...`.
1. To run clang-tidy from pw plugins: `pw tidy`.
1. To run clang-tidy manually:
   1. Update compile commands: `bazel run //:compile_commands_devices`.
   2. Run clang-tidy for a single file (currently failing):
  `run-clang-tidy -use-color=1 src/main.cc`.

## Current Issues

- Code won't link without adding `alwayslink = 1` to the `pw_malloc_freelist`
rule in `third_party/pigweed/pw_malloc_freelist/BUILD.bazel`.
  - The link errors flag undefined references to `__wrap__malloc_r`,
  `__wrap__realloc_r` and `__wrap__free_r`

- clang-tidy is not working properly.
  - `pw tidy` plugin command runs bazel for `//:compile_commands_device` to
   generate compile commands and runs `run-clang-tidy` for those files, but
   `compile_commands.json` list is missing references to system include paths,
   causing system includes to not be found.

## Feedback for the Pigweed Team

- Bootstrapping configuration to enable Pigweed environment is very cumbersome
  and difficult to get right without many iterations over python exceptions.
  There are no simple examples online on how to do so.
- No clear guidance on how to create pw plugins.
- No native support for clang-tidy (similar to what is available on GN).
- No pw watch in Bazel.
