
#include "piston_control/piston_control.h"

#include "button/button.h"
#include "button/fake_button.h"
#include "pw_chrono/simulated_system_clock.h"
#include "pw_unit_test/framework_backend.h"
#include "sqr_wave/fake_sqr_wave.h"

namespace tupa::piston_control {
namespace {

class PistonControlTest : public ::testing::Test {
 public:
 protected:
  button::FakeButton fake_low_limit_{button::Button::ButtonState{false}};
  button::FakeButton fake_left_btn_{button::Button::ButtonState{false}};
  button::FakeButton fake_right_btn_{button::Button::ButtonState{false}};
  sqr_wave::FakeSqrWave fake_sqr_wave_;
  pw::chrono::SimulatedSystemClock clock_;
  PistonControl piston_{fake_low_limit_,
                        fake_right_btn_,
                        fake_right_btn_,
                        [](bool) {},
                        // [](bool){ },
                        fake_sqr_wave_,
                        clock_};
};

TEST_F(PistonControlTest, Trivial) {
  piston_.Process();
  EXPECT_TRUE(true);
}
}  // namespace
}  // namespace tupa::piston_control