#include <cstddef>

#include "definitions.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  tupa::sqr_wave::SqrWave wave(false);
  LED_Set();
  while (true) {
    LED_Toggle();
    INF("Main loop...");
    while (++cnt % kCntMax != 0) {
    }
    wave.RunBurst(3);
  }
  return 0;
}