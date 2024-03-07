
#include "sys_tick/sys_tick.h"

#include <cstdint>

namespace tupa::sys_tick {

int64_t GetSysTickCount() { return SysTickWrapper::GetInstance().GetCount(); }

void SysTickWrapper::IsrCallback(uintptr_t obj) {
  SysTickWrapper* sys_tick = reinterpret_cast<SysTickWrapper*>(obj);
  if (sys_tick == nullptr) {
    return;
  }
  sys_tick->IncrementCount();
}

}  // namespace tupa::sys_tick