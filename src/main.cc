#include <cstddef>
#include <string_view>

#include "definitions.h"
#include "pw_sys_io/sys_io.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  tupa::sqr_wave::SqrWave wave(20000, true);
  while (true) {
    pw::sys_io::WriteLine("Print from Sys IO.");
    while (++cnt % kCntMax != 0) {
    }
  }
  return 0;
}