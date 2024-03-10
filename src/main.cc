#include <chrono>

#include "button/button.h"
#include "definitions.h"
#include "pw_chrono/system_clock.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave_same54.h"

int main() {
  SYS_Initialize(nullptr);

  INF("Startup instantiations started.");
  tupa::sqr_wave::SqrWaveSamE54::GetInstance();
  tupa::sys_tick::SysTickWrapper::GetInstance();
  tupa::button::Button left_btn(tupa::gpio::GetBtnLeftPinState);
  tupa::button::Button right_btn(tupa::gpio::GetBtnRightPinState);
  tupa::button::Button low_limit_btn(
      tupa::gpio::GetLowLimitSensorPinState,
      pw::chrono::VirtualSystemClock::RealClock(),
      std::chrono::milliseconds(1));
  INF("Startup instantiations done.");

  constexpr auto kDelta = std::chrono::milliseconds(5);
  while (true) {
    DBG_Toggle();
    left_btn.Process();
    right_btn.Process();
  }
  return 0;
}
