#include <cstddef>
#include <string_view>

#include "definitions.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  tupa::sqr_wave::SqrWave wave(500, true);
  while (true) {
    INF("Print from Sys IO.");
    while (++cnt % kCntMax != 0) {
    }
  }
  return 0;
}