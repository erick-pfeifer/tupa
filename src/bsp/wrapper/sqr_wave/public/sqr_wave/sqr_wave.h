#pragma once

#include <cstdint>

#include "definitions.h"

namespace tupa::sqr_wave {

inline constexpr uint32_t kFreqHzDefault = 50000;
inline constexpr uint32_t kFreqHzMax = 200000;
inline constexpr bool kIsEnabledDefault = true;

inline constexpr uint32_t kTicksPerSecond = (CPU_CLOCK_FREQUENCY / 4) - 50000;

class SqrWave {
 public:
  SqrWave(uint32_t freq_hz = kFreqHzDefault,
          bool is_enabled = kIsEnabledDefault)
      : freq_hz_(freq_hz), is_enabled_(is_enabled) {
    SetFreqHz(freq_hz_);
    SetEnable(is_enabled);
  }

  ~SqrWave();

  void SetEnable(bool is_enabled);
  bool GetEnable() const { return is_enabled_; }

  void SetFreqHz(uint32_t freq_hz);
  uint32_t GetFreqHz() const { return freq_hz_; }

 private:
  uint32_t freq_hz_;
  bool is_enabled_;
};

}  // namespace tupa::sqr_wave