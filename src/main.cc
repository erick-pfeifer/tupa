#include "definitions.h"
#include "gpio/gpio_wrapper.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  INF("Startup instantiations started.");
  tupa::sqr_wave::SqrWave wave(tupa::gpio::GetTCC0PinState);

  INF("Startup instantiations done.");

  while (true) {
  }
  return 0;
}
