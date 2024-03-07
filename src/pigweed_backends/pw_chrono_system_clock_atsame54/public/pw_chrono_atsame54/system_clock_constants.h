#pragma once

#include "pw_chrono/system_clock.h"

namespace pw::chrono::atsame54 {

inline constexpr SystemClock::duration kMaxTimeout =
    SystemClock::duration(0x7FFFFFFF / 3);

}  // namespace pw::chrono::atsame54
