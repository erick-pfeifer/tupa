cc_library(
  name = "same54n20a_deps",
  deps = [ "@cmsis//:core", ],
  includes = [ "include", ],
  hdrs = glob(["include/*.h"]) +
         glob(["include/component/*.h"]) +
         glob(["include/instance/*.h"]) +
         glob(["include/pio/*.h"]),
  srcs = [ "gcc/gcc/startup_same54n20a.c" ],
  visibility = ["//visibility:public"],
  alwayslink = 1,
)

exports_files(["gcc/gcc/same54n20a_flash.ld"])