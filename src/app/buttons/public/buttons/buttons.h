#pragma once

#include "pw_chrono/system_clock.h"
#include "pw_function/function.h"
#include "pw_status/status.h"

namespace tupa::buttons {

using PinFunction = pw::Function<bool(void)>;
using TimeDuration = pw::chrono::SystemClock::duration;

inline constexpr TimeDuration kPinDebounceDuration =
    TimeDuration(std::chrono::milliseconds(5));

class Buttons {
 public:
  struct ButtonState {
   public:
    constexpr ButtonState(bool is_pressed_default = false)
        : is_pressed(is_pressed_default) {}

    bool is_pressed;
    TimeDuration pressed_duration = TimeDuration(0);

    bool operator==(const ButtonState& lhs) const {
      return lhs.is_pressed == this->is_pressed;
    }

   private:
    friend Buttons;
    TimeDuration debounce_counter_ = TimeDuration(0);
  };

  Buttons(PinFunction&& pin_left_button,
          PinFunction&& pin_right_button,
          pw::chrono::VirtualSystemClock& clock)
      : pin_left_button_(std::move(pin_left_button)),
        pin_right_button_(std::move(pin_right_button)),
        clock_(clock) {}
  ~Buttons() = default;

  /**
   * @brief Main function that runs logic to determine if a button is pressed.
   *
   * @return pw::Status Returns OK if process was successfull, error code
   * otherwise.
   */
  pw::Status Process();

  /**
   * @brief Return right button state.
   *
   * This member function will return if the button is pressed and for how
   * long has it been pressed.
   *
   * @return ButtonState struct containing button state.
   */
  const ButtonState& GetLeftButtonState() const { return left_button_; }

  /**
   * @brief Return right button state.
   *
   * This member function will return if the button is pressed and for how
   * long has it been pressed.
   *
   * @return ButtonState struct containing button state.
   */
  const ButtonState& GetRightButtonState() const { return right_button_; }

 private:
  PinFunction pin_left_button_;
  PinFunction pin_right_button_;
  pw::chrono::VirtualSystemClock& clock_;

  ButtonState left_button_;
  ButtonState right_button_;
};

}  // namespace tupa::buttons