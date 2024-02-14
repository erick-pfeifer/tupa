#include <cstddef>
#include <string_view>

#include "definitions.h"
#include "port/plib_port.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);
  constexpr size_t kCntMax = 1000000;
  size_t cnt = 0;
  std::string_view buf = "Minimal print.\n";
  tupa::sqr_wave::SqrWave wave(20000, true);
  while (true) {
    SERCOM2_USART_Write(const_cast<char*>(buf.data()), buf.size());
    while (++cnt % kCntMax != 0) {
    }
  }
  return 0;
}