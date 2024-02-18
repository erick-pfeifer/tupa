#include <cstddef>

#include "definitions.h"
#include "gpio/gpio_wrapper.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  tupa::sqr_wave::SqrWave wave(tupa::gpio::GetTCC0PinState, false, 6000);
  INF("Main loop...");
  int state = 0;
  while (true) {
    LED_Toggle();
    switch (state) {
      case 0: {
        static size_t btn_debounce = 0;
        // false => btn pressed.
        if (!BTN_1_Get() && ++btn_debounce >= 10000) {
          INF("Button Pressed.");
          state = 1;
        } else if (BTN_1_Get()) {
          btn_debounce = 0;
        }
        break;
      }
      case 1: {
        INF("Burst Started.");
        if (wave.RunBurst(1000)) {
          DBG_Set();
          state = 2;
        } else {
          DBG_Clear();
          ERR("Not able to run Burst.");
        }
        break;
      }
      case 2: {
        if (!wave.IsBurstRunning()) {
          INF("Burst Done.");
          DBG_Clear();
          state = 3;
        }
        break;
      }
      case 3: {
        if (BTN_1_Get()) {
          INF("Button Released.");
          state = 0;
        }
        break;
      }
      default: {
        ERR("Bad State");
        break;
      }
    }
  }
  return 0;
}