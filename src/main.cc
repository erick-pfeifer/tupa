#include <chrono>
#include <cinttypes>

#include "definitions.h"
#include "pw_chrono/system_clock.h"
#include "pw_log/shorter.h"
#include "sqr_wave/sqr_wave.h"

int main() {
  SYS_Initialize(nullptr);

  INF("Startup instantiations started.");
  tupa::sqr_wave::SqrWave::GetInstance();
  tupa::sys_tick::SysTickWrapper::GetInstance();
  INF("Startup instantiations done.");

  constexpr auto kDelta = std::chrono::milliseconds(5);
  while (true) {
    DBG_Set();
    pw::chrono::SystemClock::time_point time_start =
        pw::chrono::SystemClock::now();
    pw::chrono::SystemClock::time_point time_curr = time_start;
    while ((time_curr - time_start) < kDelta) {
      time_curr = pw::chrono::SystemClock::now();
    }
    DBG_Clear();
    INF("SystemClock: %06" PRIu32 "ms",
        static_cast<uint32_t>(
            std::chrono::time_point_cast<std::chrono::milliseconds>(time_curr)
                .time_since_epoch()
                .count()));
  }
  return 0;
}
