#include "definitions.h"
#include "gpio/gpio_wrapper.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  tupa::sqr_wave::SqrWave wave(tupa::gpio::GetTCC0PinState);

  INF("Main loop...");
  MOTOR_ENABLE_Set();  // Motor is disabled.

  while (true) {
    LED_Toggle();

    // Left button is pressed, right is not.
    if(!BTN_LEFT_Get() && BTN_RIGHT_Get())  {
      if(LOW_LIMIT_SENSOR_Get()) {
        MOTOR_ENABLE_Clear();  // Motor is enabled.
        MOTOR_DIR_Set();  // Goes Down.
        wave.SetEnable(true);
      } else {
        wave.SetEnable(false);
        MOTOR_ENABLE_Set();  // Motor is disabled.
      }
    } else if (BTN_LEFT_Get() && !BTN_RIGHT_Get()) {
      MOTOR_ENABLE_Clear();  // Motor is enabled.
      MOTOR_DIR_Clear();  // Goes Up.
      wave.SetEnable(true);
    } else {
      wave.SetEnable(false);
      MOTOR_ENABLE_Set();  // Motor is disabled.
    }
  }
  return 0;
}
