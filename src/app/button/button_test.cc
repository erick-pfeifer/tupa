
#include "button/button.h"

#include <cstddef>

#include "gpio/fake_gpio.h"
#include "pw_chrono/simulated_system_clock.h"
#include "pw_status/status.h"
#include "pw_unit_test/framework_backend.h"

namespace tupa::button {
namespace {

Button::ButtonState kButtonReleased(false);
Button::ButtonState kButtonPressed(true);

// A short time duration is used to advance the simulated clock short of the
// minimun debounce time, using the debounce duration as reference, and dividing
// by 10 to make it shorter.
constexpr TimeDuration kShortTimeDuration = kPinDefaultDebounceDuration / 10;

// A long time duration is used to advance the simulated clock enough to
// trigger a button to be pressed.
constexpr TimeDuration kLongTimeDuration = kPinDefaultDebounceDuration * 2;

constexpr size_t kBouncingCounts = 200;

class ButtonTest : public ::testing::Test {
 public:
  void PressButton() {
    // Button pressed translates to pin being low.
    btn_.SetState(false);
  }

  void ReleaseButton() {
    // Button released translates to pin being high.
    btn_.SetState(true);
  }

 protected:
  // Defaults for the pins are true because the pins are setup as pull-ups to
  // switches which will close to GND (pressed means the pin will drive low).
  gpio::FakeDigitalInput btn_{true};
  pw::chrono::SimulatedSystemClock clock_;

  // Button test object created with fake GPIOs and fake clock.
  Button button_{[this]() -> bool { return btn_.GetState(); }, clock_};
};

TEST_F(ButtonTest, ButtonNotPressedOnStart) {
  // Check if button is released to begin with.
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
}

TEST_F(ButtonTest, ShortPressWontTriggerButton) {
  PressButton();

  // Running the main process function will cause the identification of
  // the button being pressed, but won't mark it as pressed before the
  // debouncing logic isn't done
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  // Simulated clock will advance small amount of time.
  clock_.AdvanceTime(kShortTimeDuration);

  // Running the main process function will cause the identification of
  // the button being pressed, but won't mark it as pressed before the
  // debouncing logic isn't done
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  ReleaseButton();

  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
}

TEST_F(ButtonTest, LongPressWillTriggerButton) {
  PressButton();

  // Running the main process function will cause the identification of
  // the button being pressed, but won't mark it as pressed before the
  // debouncing logic isn't done.
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  // Simulated clock will advance a long amount of time.
  clock_.AdvanceTime(kLongTimeDuration);

  // Since the time advance enough for the debouncing logic to finish,
  // the button will be marked as pressed.
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonPressed);

  // Advancing the time even further, won't change the button state.
  clock_.AdvanceTime(kLongTimeDuration);
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonPressed);

  ReleaseButton();

  // After the button being released, we expect the Button to be marked as
  // released.
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
}

TEST_F(ButtonTest, MultipleShortPressesWontTriggerButton) {
  // Running the logic an arbitrary long amount of times to emulate the
  // pin bouncing on/off.
  for (size_t i = 0; i < kBouncingCounts; i++) {
    // This ternary will alternate between Press/Release on every loop
    // iteration.
    (i % 2 == 0) ? PressButton() : ReleaseButton();

    ASSERT_EQ(button_.Process(), pw::OkStatus());
    clock_.AdvanceTime(kShortTimeDuration);
    ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
  }

  ReleaseButton();
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
}

TEST_F(ButtonTest, LongPressWillOututCorrectPressTime) {
  // Strating with two sort time durations to emulate a short bouncing
  // period.
  PressButton();
  clock_.AdvanceTime(kShortTimeDuration);
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  ReleaseButton();
  clock_.AdvanceTime(kShortTimeDuration);
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  // After that bounce, button is pressed for a long duration.
  PressButton();
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);

  clock_.AdvanceTime(kLongTimeDuration);
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonPressed);

  // Finally, checks that the pin has been pressed for the right duration,
  // which discards the previous bounce time.
  ASSERT_EQ(button_.GetButtonState().pressed_duration.count(),
            kLongTimeDuration.count());

  clock_.AdvanceTime(kLongTimeDuration);
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonPressed);

  // If we run the same time again, the elapsed pressed time should double.
  ASSERT_EQ(button_.GetButtonState().pressed_duration.count(),
            kLongTimeDuration.count() * 2);

  ReleaseButton();
  ASSERT_EQ(button_.Process(), pw::OkStatus());
  ASSERT_EQ(button_.GetButtonState(), kButtonReleased);
}

}  // namespace
}  // namespace tupa::button