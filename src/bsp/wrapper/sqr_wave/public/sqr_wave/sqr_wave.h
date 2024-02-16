#pragma once

#include <cstdint>

#include "definitions.h"
#include "tcc/plib_tcc0.h"
#include "tcc/plib_tcc_common.h"

namespace tupa::sqr_wave {

using IsrCallbackType = void (*)(long unsigned int, unsigned int);

inline constexpr uint32_t kFreqHzDefault = 1000;
inline constexpr uint32_t kFreqHzMax = 7000;
inline constexpr bool kIsEnabledDefault = true;

inline constexpr uint32_t kTicksPerSecond = (CPU_CLOCK_FREQUENCY / 4) - 50000;

class SqrWave {
 public:
  SqrWave(bool is_enabled = kIsEnabledDefault,
          uint32_t freq_hz = kFreqHzDefault,
          IsrCallbackType isr_callback = (IsrCallbackType)&SqrWave::IsrCallback)
      : freq_hz_(freq_hz), is_enabled_(is_enabled)  {
    SetFreqHz(freq_hz_);
    SetEnable(is_enabled);
    TCC0_CompareCallbackRegister(isr_callback,0);
  }

  ~SqrWave();

  void SetEnable(const bool is_enabled);
  bool GetEnable() const { return is_enabled_; }

  void SetFreqHz(const uint32_t freq_hz);
  uint32_t GetFreqHz() const { return freq_hz_; }

  bool RunBurst(const size_t count);
  void StopBurst();
  size_t GetBurstCount() const { return burst_count_; }

 private:

  void IsrCallback(uint32_t, uintptr_t);

  uint32_t freq_hz_;
  bool is_enabled_;
  size_t burst_count_ = 0u;
};

}  // namespace tupa::sqr_wave