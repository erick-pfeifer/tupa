#pragma once

#include <cstdint>

#include "sqr_wave/sqr_wave.h"

namespace tupa::sqr_wave {
class FakeSqrWave : public SqrWave {
 public:
  FakeSqrWave() = default;
  ~FakeSqrWave() override = default;

  void SetEnable(const bool is_enabled) override { is_enabled_ = is_enabled; }
  inline bool GetEnable() const override { return is_enabled_; }

  void SetFreqHz(const uint32_t) override { /* Do nothing. */ }
  inline uint32_t GetFreqHz() const override { return 0; }

  bool RunBurst(const size_t) override { return is_burst_enabled_ = true; }
  inline bool IsBurstRunning() const override { return is_burst_enabled_; }
  void StopBurst() override {
    is_burst_enabled_ = false;
    is_enabled_ = false;
  };
  inline size_t GetBurstCount() const override { return 0; }

 private:
  bool is_enabled_ = false;
  bool is_burst_enabled_ = false;
};

}  // namespace tupa::sqr_wave