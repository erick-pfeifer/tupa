#include "sqr_wave/sqr_wave.h"

#include <cstdint>

#include "tcc/plib_tcc0.h"

namespace tupa::sqr_wave {

SqrWave::~SqrWave() { TCC0_CompareStop(); }

void SqrWave::SetFreqHz(uint32_t freq_hz) {

  uint32_t ticks =
      kTicksPerSecond / (freq_hz < kFreqHzMax ? freq_hz : kFreqHzMax);

  TCC0_Compare24bitMatchSet(TCC0_CHANNEL0, ticks);
  freq_hz_ = freq_hz;
}

void SqrWave::SetEnable(bool is_enabled) {
  is_enabled ? TCC0_CompareStart() : TCC0_CompareStop();
  is_enabled_ = is_enabled;
}

}  // namespace tupa::sqr_wave