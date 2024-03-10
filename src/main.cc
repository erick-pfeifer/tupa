#include <chrono>

#include "button/button.h"
#include "definitions.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);

  INF("Startup instantiations started.");
  tupa::sqr_wave::SqrWave::GetInstance();
  tupa::sys_tick::SysTickWrapper::GetInstance();
  tupa::button::Button left_btn(tupa::gpio::GetBtnLeftPinState);
  tupa::button::Button right_btn(tupa::gpio::GetBtnRightPinState);
  INF("Startup instantiations done.");

  constexpr auto kDelta = std::chrono::milliseconds(5);
  while (true) {
    DBG_Toggle();
    left_btn.Process();
    right_btn.Process();
  }
  return 0;
}
