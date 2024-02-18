#include <cstddef>

#include "definitions.h"
#include "gpio/gpio_wrapper.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);

  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  tupa::sqr_wave::SqrWave wave(tupa::gpio::GetTCC0PinState, false);
  LED_Set();
  while (true) {
    LED_Toggle();
    INF("Main loop...");
    wave.RunBurst(3);
    while (++cnt % kCntMax != 0) {
    }
  }
  return 0;
}