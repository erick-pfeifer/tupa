#pragma once

#include "button/button.h"
#include "gpio/fake_gpio.h"
#include "pw_status/status.h"

namespace tupa::button {

class FakeButton : Button {
 public:
  FakeButton(ButtonState initial_state)
      : state_(initial_state),
        Button([this]() { return fake_pin_.GetState(); }) {}
  ~FakeButton() override = default;

  pw::Status Process() override { return pw::OkStatus(); };

  const ButtonState& GetButtonState() const override { return state_; }

  /**
   * @brief Set the Fake Button State.
   *
   * This function is used to manipulate fake states of a button for unit tests.
   *
   * @param is_pressed force a pin to be pressed or not.
   * @param pressed_duration force a pin duration.
   */
  void SetFakeButtonState(bool is_pressed,
                          TimeDuration pressed_duration = TimeDuration{0}) {
    state_.is_pressed = is_pressed;
    state_.pressed_duration =
        state_.is_pressed ? pressed_duration : TimeDuration{0};
  }

 private:
  gpio::FakeDigitalInput fake_pin_{true};
  ButtonState state_;
};

}  // namespace tupa::button