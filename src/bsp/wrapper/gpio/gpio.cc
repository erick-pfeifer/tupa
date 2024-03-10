#include "gpio/gpio_wrapper.h"
#include "peripheral/port/plib_port.h"
#include "same54p20a.h"

namespace tupa::gpio {

bool GetTCC0PinState() {
  PORT_REGS->GROUP[2].PORT_PINCFG[4] |= 0x02;
  return (((PORT_REGS->GROUP[2].PORT_IN >> 4U)) & 0x01U);
}

bool GetBtnLeftPinState() { return BTN_LEFT_Get() != 0; }

bool GetBtnRightPinState() { return BTN_RIGHT_Get() != 0; }

bool GetLowLimitSensorPinState() { return LOW_LIMIT_SENSOR_Get() != 0; }

void SetDbgPin(bool state) { state ? DBG_Set() : DBG_Clear(); }

void SetMotorEnablePin(bool state) {
  state ? MOTOR_ENABLE_Set() : MOTOR_ENABLE_Clear();
}

void SetMotorDiretionPin(bool state) {
  state ? MOTOR_DIR_Set() : MOTOR_DIR_Clear();
}

void SetBoardLedPin(bool state) { state ? LED_Set() : LED_Clear(); }

}  // namespace tupa::gpio