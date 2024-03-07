#pragma once

#include "sys_tick/sys_tick.h"

#define PW_CHRONO_SYSTEM_CLOCK_PERIOD_SECONDS_NUMERATOR 1
#define PW_CHRONO_SYSTEM_CLOCK_PERIOD_SECONDS_DENOMINATOR \
  tupa::sys_tick::GetSysTickFreqHz()

#ifdef __cplusplus

#include "pw_chrono/epoch.h"

namespace pw::chrono::backend {

inline constexpr Epoch kSystemClockEpoch = pw::chrono::Epoch::kTimeSinceBoot;

inline constexpr bool kSystemClockNmiSafe = false;
inline constexpr bool kSystemClockFreeRunning = true;

}  // namespace pw::chrono::backend

#endif  // __cplusplus
