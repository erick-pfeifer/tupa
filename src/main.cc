#include <cstddef>
#include <string_view>

#include "definitions.h"
#include "port/plib_port.h"
#include "tcc/plib_tcc0.h"

int main() {
  SYS_Initialize(nullptr);
  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  std::string_view buf = "Minimal print.\n";
  TCC0_CompareStart();
  TCC0_Compare24bitMatchSet(TCC0_CHANNEL0, 1000) ? LED_Clear() : DBG_Set();
  while (true) {
    SERCOM2_USART_Write(const_cast<char*>(buf.data()), buf.size());
    while (++cnt % kCntMax != 0) {
    }
  }
  return 0;
}