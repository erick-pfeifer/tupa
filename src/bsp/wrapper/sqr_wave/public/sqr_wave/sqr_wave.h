#pragma once

#include <cstdint>

#include "definitions.h"
#include "tcc/plib_tcc0.h"
#include "port/plib_port.h"
#include "tcc/plib_tcc_common.h"

namespace tupa::sqr_wave {

using WavePortGroupType = PORT_GROUP;
using WavePortPinOffsetType = uint32_t;
using IsrCallbackType = void (*)(long unsigned int, unsigned int);

namespace {

// TODO: Need a better way to represent this from dependency instead of literal.
// Port group for squrewave
constexpr WavePortGroupType kPinGroup = 2;
constexpr WavePortPinOffsetType kPinOffset = 4;

}  // namespace


inline constexpr uint32_t kFreqHzDefault = 1000;
inline constexpr uint32_t kFreqHzMax = 7000;
inline constexpr bool kIsEnabledDefault = true;

inline constexpr uint32_t kTicksPerSecond = (CPU_CLOCK_FREQUENCY / 4) - 50000;

void IsrCallback(uint32_t, uintptr_t obj);

class SqrWave {
 public:
  SqrWave(bool is_enabled = kIsEnabledDefault,
          uint32_t freq_hz = kFreqHzDefault,
          IsrCallbackType isr_callback = (IsrCallbackType)&IsrCallback,
          WavePortGroupType pin_group = kPinGroup,
          WavePortGroupType pin_offset = kPinOffset)
      : freq_hz_(freq_hz),
        is_enabled_(is_enabled),
        pin_group_(pin_group),
        pin_offset_(pin_offset)  {
    SetFreqHz(freq_hz_);
    SetEnable(is_enabled);
    TCC0_CompareCallbackRegister(isr_callback,
                                 reinterpret_cast<uintptr_t>(this));
  }

  ~SqrWave();

  void SetEnable(const bool is_enabled);
  inline bool GetEnable() const { return is_enabled_; }

  void SetFreqHz(const uint32_t freq_hz);
  inline uint32_t GetFreqHz() const { return freq_hz_; }

  bool RunBurst(const size_t count);
  void StopBurst();
  inline size_t GetBurstCount() const { return burst_count_; }

  bool GetPinState() const {
    return 0x01 & (PORT_GroupRead(pin_group_)>>pin_offset_);
  }

 private:

  friend void IsrCallback(uint32_t, uintptr_t obj);

  uint32_t freq_hz_;
  bool is_enabled_;
  size_t burst_count_ = 0u;
  bool is_burst_enabled_ = false;
  WavePortGroupType pin_group_;
  WavePortGroupType pin_offset_;
};

}  // namespace tupa::sqr_wave