#pragma once

#include <cstdint>

#include "systick/plib_systick.h"

namespace tupa::sys_tick {

using IsrCallbackType = void (*)(uintptr_t);

/**
 * @brief Get the Systick Freq in Hertz.
 *
 * @return Frequency in Hertz.
 */
constexpr uint32_t GetSysTickFreqHz() {
  return 1e6 / SYSTICK_INTERRUPT_PERIOD_IN_US;
}

/**
 * @brief Get System Tick counter.
 *
 * @return int64_t Count.
 */
int64_t GetSysTickCount();

class SysTickWrapper {
 public:
  /**
   * @brief Factory method for SysTickWrapper, uses a singleton pattern.
   *
   * @return Reference to SysTickWrapper.
   */
  static SysTickWrapper& GetInstance() {
    static SysTickWrapper instance;
    return instance;
  }

  SysTickWrapper(IsrCallbackType isr_callback =
                     reinterpret_cast<IsrCallbackType>(&IsrCallback)) {
    SYSTICK_TimerCallbackSet(isr_callback, reinterpret_cast<uintptr_t>(this));
    SYSTICK_TimerStart();
  }

  ~SysTickWrapper() { SYSTICK_TimerStop(); }

  /**
   * @brief Increments tick counter.
   */
  void IncrementCount() { tick_count_++; }

  /**
   * @brief Gets current count.
   *
   * @return int64_t Count.
   */
  int64_t GetCount() { return tick_count_; }

 private:
  static void IsrCallback(uintptr_t obj);
  int64_t tick_count_ = 0;
};

}  // namespace tupa::sys_tick