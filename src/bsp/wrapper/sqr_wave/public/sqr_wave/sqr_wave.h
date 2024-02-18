#pragma once

#include <cstdint>

#include "definitions.h"
#include "tcc/plib_tcc0.h"

namespace tupa::sqr_wave {

using IsrCallbackType = void (*)(long unsigned int, unsigned int);
using GetStateStateFunction = bool (*)(void);

inline constexpr uint32_t kFreqHzDefault = 1000;
inline constexpr uint32_t kFreqHzMax = 6000;
inline constexpr bool kIsEnabledDefault = true;

inline constexpr uint32_t kTicksPerSecond = (CPU_CLOCK_FREQUENCY / 4) - 50000;

void IsrCallback(uint32_t, uintptr_t obj);

class SqrWave {
 public:
  SqrWave(GetStateStateFunction get_pin_state,
          bool is_enabled = kIsEnabledDefault,
          uint32_t freq_hz = kFreqHzDefault,
          IsrCallbackType isr_callback =
              reinterpret_cast<IsrCallbackType>(&IsrCallback))
      : freq_hz_(freq_hz),
        is_enabled_(is_enabled),
        get_pin_state_(get_pin_state) {
    SetFreqHz(freq_hz_);
    SetEnable(is_enabled);

    TCC0_CompareCallbackRegister(isr_callback,
                                 reinterpret_cast<uintptr_t>(this));
  }

  ~SqrWave() { TCC0_CompareStop(); }

  void SetEnable(const bool is_enabled);
  inline bool GetEnable() const { return is_enabled_; }

  void SetFreqHz(const uint32_t freq_hz);
  inline uint32_t GetFreqHz() const { return freq_hz_; }

  bool RunBurst(const size_t count);
  inline bool IsBurstRunning() const { return is_burst_enabled_; }
  void StopBurst();
  inline size_t GetBurstCount() const { return burst_count_; }

 private:
  friend void IsrCallback(uint32_t, uintptr_t obj);

  uint32_t freq_hz_;
  bool is_enabled_;
  size_t burst_count_ = 0u;
  bool is_burst_enabled_ = false;
  GetStateStateFunction get_pin_state_;
};

}  // namespace tupa::sqr_wave