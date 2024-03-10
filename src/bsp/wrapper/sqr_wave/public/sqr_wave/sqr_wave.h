#pragma once

#include <cstddef>
#include <cstdint>

namespace tupa::sqr_wave {
class SqrWave {
 public:
  virtual ~SqrWave() = default;

  virtual void SetEnable(const bool is_enabled) = 0;
  virtual inline bool GetEnable() const = 0;

  virtual void SetFreqHz(const uint32_t freq_hz) = 0;
  virtual inline uint32_t GetFreqHz() const = 0;

  virtual bool RunBurst(const size_t count) = 0;
  virtual inline bool IsBurstRunning() const = 0;
  virtual void StopBurst() = 0;
  virtual inline size_t GetBurstCount() const = 0;
};
}  // namespace tupa::sqr_wave