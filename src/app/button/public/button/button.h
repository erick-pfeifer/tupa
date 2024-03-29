#pragma once

#include "pw_chrono/system_clock.h"
#include "pw_function/function.h"
#include "pw_status/status.h"

namespace tupa::button {

using PinFunction = pw::Function<bool(void)>;
using TimeDuration = pw::chrono::SystemClock::duration;
using TimePoint = pw::chrono::SystemClock::time_point;

inline constexpr TimeDuration kPinDefaultDebounceDuration =
    TimeDuration(std::chrono::milliseconds(40));

class Button {
 public:
  struct ButtonState {
    bool is_pressed;
    TimeDuration pressed_duration = TimeDuration(0);

    constexpr ButtonState(bool is_pressed_default = false)
        : is_pressed(is_pressed_default) {}

    bool operator==(const ButtonState& lhs) const {
      return lhs.is_pressed == this->is_pressed;
    }
  };

  Button(PinFunction&& get_pin_func,
         pw::chrono::VirtualSystemClock& clock =
             pw::chrono::VirtualSystemClock::RealClock(),
         TimeDuration debounce_duration = kPinDefaultDebounceDuration)
      : get_pin_func_(std::move(get_pin_func)),
        debounce_duration_(debounce_duration),
        clock_(clock) {}
  virtual ~Button() = default;

  /**
   * @brief Main function that runs logic to determine if a button is pressed.
   *
   * @return pw::Status Returns OK if process was successfull, error code
   * otherwise.
   */
  virtual pw::Status Process();

  /**
   * @brief Return button state.
   *
   * This member function will return if the button is pressed and for how
   * long has it been pressed.
   *
   * @return ButtonState struct containing button state.
   */
  virtual const ButtonState& GetButtonState() const { return state_; }

 private:
  pw::chrono::VirtualSystemClock& clock_;
  PinFunction get_pin_func_;
  ButtonState state_;
  bool instant_press_state_ = false;
  TimePoint debounce_start_time_point_;
  TimeDuration debounce_duration_;
};

}  // namespace tupa::button
