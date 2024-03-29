#include "sqr_wave/sqr_wave_same54.h"

#include <cstddef>
#include <cstdint>

#include "pw_log/shorter.h"
#include "tcc/plib_tcc0.h"

namespace tupa::sqr_wave {

void SqrWaveSamE54::IsrCallback(uint32_t, uintptr_t obj) {
  SqrWaveSamE54* wave = reinterpret_cast<SqrWaveSamE54*>(obj);
  if (wave == nullptr) {
    return;
  }

  if ((wave->is_burst_enabled_) &&
      ((!wave->get_pin_state_()) && (--wave->burst_count_ == 0u))) {
    wave->StopBurst();
  }
}

void SqrWaveSamE54::SetFreqHz(const uint32_t freq_hz) {
  uint32_t ticks =
      kTicksPerSecond / (freq_hz < kFreqHzMax ? freq_hz : kFreqHzMax);

  if (TCC0_Compare24bitMatchSet(TCC0_CHANNEL0, ticks)) {
    freq_hz_ = freq_hz;
  }
}

void SqrWaveSamE54::SetEnable(const bool is_enabled) {
  if (is_enabled && (!is_enabled_)) {
    TCC0_Compare24bitCounterSet(0);
    TCC0_CompareStart();
  } else if (!is_enabled) {
    TCC0_CompareStop();
    TCC0_Compare24bitCounterSet(0);
  }
  is_enabled_ = is_enabled;
}

bool SqrWaveSamE54::RunBurst(const size_t count) {
  if (is_burst_enabled_) {
    INF("Burst is already running, cancelling.");
    return false;
  }

  if (is_enabled_) {
    INF("Frequency mode is already running, cancelling.");
    return false;
  }

  SetEnable(false);
  burst_count_ = count;
  is_burst_enabled_ = true;
  SetEnable(true);
  return true;
}

void SqrWaveSamE54::StopBurst() {
  SetEnable(false);
  burst_count_ = 0;
  is_burst_enabled_ = false;
}

}  // namespace tupa::sqr_wave