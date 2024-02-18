#include "gpio/gpio_wrapper.h"
#include "same54n20a.h"

namespace tupa::gpio {

bool GetTCC0PinState() {
  PORT_REGS->GROUP[2].PORT_PINCFG[4] |= 0x02;
  return (((PORT_REGS->GROUP[2].PORT_IN >> 4U)) & 0x01U);
}

}  // namespace tupa::gpio