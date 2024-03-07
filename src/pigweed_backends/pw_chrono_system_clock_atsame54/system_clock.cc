
#include "sys_tick/sys_tick.h"

namespace pw::chrono::backend {

int64_t GetSystemClockTickCount() { return tupa::sys_tick::GetSysTickCount(); }
}  // namespace pw::chrono::backend
