#pragma once

#include <cstdint>

#include "definitions.h"
#include "gpio/gpio_wrapper.h"
#include "sqr_wave/sqr_wave.h"
#include "tcc/plib_tcc0.h"

namespace tupa::sqr_wave {

using IsrCallbackType = void (*)(long unsigned int, unsigned int);
using GetStateStateFunction = bool (*)(void);

inline constexpr uint32_t kFreqHzDefault = 4000;
inline constexpr uint32_t kFreqHzMax = 6000;
inline constexpr bool kIsEnabledDefault = false;

inline constexpr uint32_t kTicksPerSecond = (CPU_CLOCK_FREQUENCY / 4) - 50000;

class SqrWaveSamE54 : public SqrWave {
 public:
  /**
   * @brief Factory method for SqrWave, uses a singleton pattern.
   *
   * @return Reference to SqrWave.
   */
  static SqrWave& GetInstance() {
    static SqrWaveSamE54 instance(tupa::gpio::GetTCC0PinState);
    return instance;
  }

  SqrWaveSamE54(GetStateStateFunction get_pin_state,
                bool is_enabled = kIsEnabledDefault,
                uint32_t freq_hz = kFreqHzDefault,
                IsrCallbackType isr_callback =
                    reinterpret_cast<IsrCallbackType>(&IsrCallback))
      : freq_hz_(freq_hz), get_pin_state_(get_pin_state) {
    SetFreqHz(freq_hz_);
    SetEnable(is_enabled);

    TCC0_CompareCallbackRegister(isr_callback,
                                 reinterpret_cast<uintptr_t>(this));
  }

  ~SqrWaveSamE54() override { TCC0_CompareStop(); }

  void SetEnable(const bool is_enabled) override;
  inline bool GetEnable() const override { return is_enabled_; }

  void SetFreqHz(const uint32_t freq_hz) override;
  inline uint32_t GetFreqHz() const override { return freq_hz_; }

  bool RunBurst(const size_t count) override;
  inline bool IsBurstRunning() const override { return is_burst_enabled_; }
  void StopBurst() override;
  inline size_t GetBurstCount() const override { return burst_count_; }

 private:
  static void IsrCallback(uint32_t, uintptr_t obj);

  uint32_t freq_hz_;
  bool is_enabled_ = false;
  size_t burst_count_ = 0u;
  bool is_burst_enabled_ = false;
  GetStateStateFunction get_pin_state_;
};

}  // namespace tupa::sqr_wave