#include <chrono>

#include "button/button.h"
#include "definitions.h"
#include "piston_control/piston_control.h"
#include "pw_chrono/system_clock.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave_same54.h"

int main() {
  SYS_Initialize(nullptr);

  INF("Startup instantiations started.");
  tupa::sqr_wave::SqrWave& sqr_wave =
      tupa::sqr_wave::SqrWaveSamE54::GetInstance();
  tupa::sys_tick::SysTickWrapper::GetInstance();
  tupa::button::Button left_btn(tupa::gpio::GetBtnLeftPinState);
  tupa::button::Button right_btn(tupa::gpio::GetBtnRightPinState);
  tupa::button::Button low_limit_btn(
      tupa::gpio::GetLowLimitSensorPinState,
      pw::chrono::VirtualSystemClock::RealClock(),
      std::chrono::milliseconds(1));
  tupa::button::Button high_limit_btn(
      tupa::gpio::GetHighLimitSensorPinState,
      pw::chrono::VirtualSystemClock::RealClock(),
      std::chrono::milliseconds(1));

  tupa::piston_control::PistonControl piston_control(
      low_limit_btn,
      high_limit_btn,
      left_btn,
      right_btn,
      tupa::gpio::SetMotorEnablePin,
      tupa::gpio::SetMotorDiretionPin,
      sqr_wave);

  INF("Startup instantiations done.");

  // If the board pin is pressed at startup, enter manual mode.
  // In this mode the left pin moves the piston down, and the right button moves
  // the piston up.
  bool run_in_manual_mode = !tupa::gpio::GetBoardPinState();

  while (true) {
    DBG_Toggle();
    left_btn.Process();
    right_btn.Process();
    low_limit_btn.Process();
    high_limit_btn.Process();

    if(!run_in_manual_mode) {
      LED_Clear();
      piston_control.Process();
    } else {
      LED_Set();
      if(left_btn.GetButtonState().is_pressed && !low_limit_btn.GetButtonState().is_pressed) {
        sqr_wave.SetEnable(true);
        sqr_wave.SetFreqHz(3000);
        tupa::gpio::SetMotorDiretionPin(true);
        tupa::gpio::SetMotorEnablePin(false);
      } else if(right_btn.GetButtonState().is_pressed && !high_limit_btn.GetButtonState().is_pressed) {
        sqr_wave.SetEnable(true);
        sqr_wave.SetFreqHz(3000);
        tupa::gpio::SetMotorDiretionPin(false);
        tupa::gpio::SetMotorEnablePin(false);
      } else {
        tupa::gpio::SetMotorEnablePin(true);
      }
    }
  }
  return 0;
}
