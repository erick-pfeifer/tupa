#include <cstddef>
#include <string_view>

#include <same54p20a.h>

// LED functions


void pb31_init(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[1].PORT_PINCFG[31] = PORT_PINCFG_PULLEN_Msk | PORT_PINCFG_INEN_Msk;
  port_regs->GROUP[1].PORT_OUTSET = PORT_OUTSET_OUTSET(PORT_PB31);
  port_regs->GROUP[1].PORT_DIRSET = PORT_DIRCLR_DIRCLR(PORT_PB31);
}

bool pb31_read(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  return (port_regs->GROUP[1].PORT_IN & PORT_IN_IN(PORT_PB31)) != 0;
}

void pc18_init(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTSET = PORT_OUTSET_OUTSET(PORT_PC18);
  port_regs->GROUP[2].PORT_DIRSET = PORT_DIRSET_DIRSET(PORT_PC18);
}

void pc18_LED_on(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTCLR = PORT_OUTCLR_OUTCLR(PORT_PC18);
}

void pc18_LED_off(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTSET = PORT_OUTSET_OUTSET(PORT_PC18);
}

void pc18_LED_toggle(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTTGL = PORT_OUTTGL_OUTTGL(PORT_PC18);
}

void pc06_init(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTSET = PORT_OUTSET_OUTSET(PORT_PC06);
  port_regs->GROUP[2].PORT_DIRSET = PORT_DIRSET_DIRSET(PORT_PC06);
}

void pc06_LED_on(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTCLR = PORT_OUTCLR_OUTCLR(PORT_PC06);
}

void pc06_LED_off(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTSET = PORT_OUTSET_OUTSET(PORT_PC06);
}

void pc06_LED_toggle(void) {
  port_registers_t* port_regs = (port_registers_t*)PORT_REGS;
  port_regs->GROUP[2].PORT_OUTTGL = PORT_OUTTGL_OUTTGL(PORT_PC06);
}

int main() {
  pc18_init();
  pc06_init();
  pb31_init();
  constexpr size_t kCntPeriod = 27500;
  // 1000us = 2300
  size_t duty_35 = 2450;
  size_t duty_30 = 2600;
  while (1) {
    if(pb31_read()) {
      pc18_LED_off();
    } else {
      pc18_LED_on();
    }

    for (size_t i = 0; i<kCntPeriod; i++) {
      size_t duty = pb31_read() ? duty_35 : duty_30;
      if (i > duty) {
        pc06_LED_on();
      } else {
        pc06_LED_off();
      }
    }
  }
  return 0;
}