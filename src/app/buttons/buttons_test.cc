
#include "buttons/buttons.h"

#include <cstddef>

#include "gpio/fake_gpio.h"
#include "pw_chrono/simulated_system_clock.h"
#include "pw_chrono/system_clock.h"
#include "pw_status/status.h"
#include "pw_unit_test/framework_backend.h"

namespace tupa::buttons {
namespace {

constexpr Buttons::ButtonState kButtonReleased(false);
constexpr Buttons::ButtonState kButtonPressed(true);

// A short time duration is used to advance the simulated clock short of the
// minimun debounce time, using the debounce duration as reference, and dividing
// by 10 to make it shorter.
constexpr TimeDuration kShortTimeDuration = kPinDebounceDuration / 10;

// A long time duration is used to advance the simulated clock enough to
// trigger a button to be pressed.
constexpr TimeDuration kLongTimeDuration = kPinDebounceDuration * 2;

constexpr size_t kBouncingCounts = 200;

class ButtonsTest : public ::testing::Test {
 public:
  void PressLeftButton() {
    // Button pressed translates to pin being low.
    left_btn_.SetState(false);
  }

  void ReleaseLeftButton() {
    // Button released translates to pin being high.
    left_btn_.SetState(true);
  }

  void PressRightButton() {
    // Button pressed translates to pin being low.
    right_btn_.SetState(false);
  }

  void ReleaseRightButton() {
    // Button released translates to pin being high.
    right_btn_.SetState(true);
  }

 protected:
  // Defaults for the pins are true because the pins are setup as pull-ups to
  // switches which will close to GND (pressed means the pin will drive low).
  gpio::FakeDigitalInput left_btn_{true};
  gpio::FakeDigitalInput right_btn_{true};
  pw::chrono::SimulatedSystemClock clock_;

  // Buttons test object created with fake GPIOs and fake clock.
  Buttons buttons_{[this]() -> bool { return left_btn_.GetState(); },
                   [this]() -> bool { return right_btn_.GetState(); },
                   clock_};
};

TEST_F(ButtonsTest, ButtonsNotPressedOnStart) {
  // Check if buttons are released to begin with.
  ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);
  ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);
}

TEST_F(ButtonsTest, ShortPressWontTriggerButton) {
  // This scenario will press the left button.
  {
    PressLeftButton();

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);

    // Simulated clock will advance small amount of time.
    clock_.AdvanceTime(kShortTimeDuration);

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);

    ReleaseLeftButton();
  }

  // This scenario will press the Right button.
  {
    PressRightButton();

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);

    // Simulated clock will advance small amount of time.
    clock_.AdvanceTime(kShortTimeDuration);

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);

    ReleaseRightButton();
  }
}

TEST_F(ButtonsTest, LongPressWillTriggerButton) {
  // This scenario will press the left button.
  {
    PressLeftButton();

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);

    // Simulated clock will advance a long amount of time.
    clock_.AdvanceTime(kLongTimeDuration);

    // Since the time advance enough for the debouncing logic to finish,
    // the button will be marked as pressed.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonPressed);

    // Advancing the time even further, won't change the button state.
    clock_.AdvanceTime(kLongTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonPressed);

    ReleaseLeftButton();

    // After the button being released, we expect the Button to be marked as
    // released.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);
  }

  // This scenario will press the Right button.
  {
    PressRightButton();

    // Running the main process function will cause the identification of
    // the button being pressed, but won't mark it as pressed before the
    // debouncing logic isn't done.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);

    // Simulated clock will advance a long amount of time.
    clock_.AdvanceTime(kLongTimeDuration);

    // Since the time advance enough for the debouncing logic to finish,
    // the button will be marked as pressed.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonPressed);

    // Advancing the time even further, won't change the button state.
    clock_.AdvanceTime(kLongTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonPressed);

    ReleaseRightButton();

    // After the button being released, we expect the Button to be marked as
    // released.
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);
  }
}

TEST_F(ButtonsTest, ManyShortPressesWontTriggerButton) {
  // This scenario will press the left button.
  {
    // Running the logic an arbitrary long amount of times to emulate the
    // pin bouncing on/off.
    for (size_t i = 0; i < kBouncingCounts; i++) {
      // This ternary will alternate between Press/Release on every loop
      // iteration.
      (i % 1 == 0) ? PressLeftButton() : ReleaseLeftButton();

      clock_.AdvanceTime(kShortTimeDuration);
      ASSERT_EQ(buttons_.Process(), pw::OkStatus());
      ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);
    }

    ReleaseLeftButton();
  }

  // This scenario will press the Right button.
  {
    // Running the logic an arbitrary long amount of times to emulate the
    // pin bouncing on/off.
    for (size_t i = 0; i < kBouncingCounts; i++) {
      // This ternary will alternate between Press/Release on every loop
      // iteration.
      (i % 1 == 0) ? PressRightButton() : ReleaseRightButton();

      clock_.AdvanceTime(kShortTimeDuration);
      ASSERT_EQ(buttons_.Process(), pw::OkStatus());
      ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);
    }

    ReleaseRightButton();
  }
}

TEST_F(ButtonsTest, LongPressWillOututCorrectPressTime) {
  // This scenario will press the left button.
  {
    // Strating with two sort time durations to emulate a short bouncing
    // period.
    PressLeftButton();
    clock_.AdvanceTime(kShortTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);

    ReleaseLeftButton();
    clock_.AdvanceTime(kShortTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonReleased);

    // After that bounce, button is pressed for a long duration.
    PressLeftButton();
    clock_.AdvanceTime(kLongTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetLeftButtonState(), kButtonPressed);

    // Finally, checks that the pin has been pressed for the right duration,
    // which discards the previous bounce time.
    ASSERT_EQ(buttons_.GetLeftButtonState().pressed_duration.count(),
              kLongTimeDuration.count());

    ReleaseLeftButton();
  }

  // This scenario will press the Right button.
  {
    // Strating with two sort time durations to emulate a short bouncing
    // period.
    PressRightButton();
    clock_.AdvanceTime(kShortTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);

    ReleaseRightButton();
    clock_.AdvanceTime(kShortTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonReleased);

    // After that bounce, button is pressed for a long duration.
    PressRightButton();
    clock_.AdvanceTime(kLongTimeDuration);
    ASSERT_EQ(buttons_.Process(), pw::OkStatus());
    ASSERT_EQ(buttons_.GetRightButtonState(), kButtonPressed);

    // Finally, checks that the pin has been pressed for the right duration,
    // which discards the previous bounce time.
    ASSERT_EQ(buttons_.GetRightButtonState().pressed_duration.count(),
              kLongTimeDuration.count());

    ReleaseRightButton();
  }
}

}  // namespace
}  // namespace tupa::buttons