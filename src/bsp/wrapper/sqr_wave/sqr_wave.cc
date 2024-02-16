#include "sqr_wave/sqr_wave.h"

#include <cstdint>

#include "tcc/plib_tcc0.h"
#include "pw_log/shorter.h"

namespace tupa::sqr_wave {

SqrWave::~SqrWave() { TCC0_CompareStop(); }

void SqrWave::SetFreqHz(const uint32_t freq_hz) {

  uint32_t ticks =
      kTicksPerSecond / (freq_hz < kFreqHzMax ? freq_hz : kFreqHzMax);

  TCC0_Compare24bitMatchSet(TCC0_CHANNEL0, ticks);
  freq_hz_ = freq_hz;
}

void SqrWave::SetEnable(const bool is_enabled) {
  if(is_enabled) {
    TCC0_CompareStart();
  } else {
    TCC0_CompareStop();
    TCC0_Compare24bitCounterSet(0);
  }
  is_enabled_ = is_enabled;
}

bool SqrWave::RunBurst(const size_t count) {

  if(burst_count_ > 0u) {
    INF("Burst is already on, cancelling.");
    return false;
  }
  SetEnable(false);
  burst_count_ = count > 0 ? count - 1 : 0;
  INF("Burst count is starting. count: %d.", burst_count_);
  SetEnable(true);
  return true;
}

void SqrWave::StopBurst() {
  SetEnable(false);
  burst_count_ = 0;
}

void SqrWave::IsrCallback(uint32_t, uintptr_t) {
  // if(burst_count_ > 0u) {
  //   burst_count_--;
  // } else {
  //   StopBurst();
  // }
}

}  // namespace tupa::sqr_wave