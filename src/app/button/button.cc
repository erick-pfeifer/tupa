
#include "button/button.h"

#include "pw_status/status.h"
namespace tupa::button {
namespace {

constexpr bool kPinStateWhenButtonIsReleased = true;
}  // namespace

pw::Status Button::Process() {
  // If pin is released, reset everything and return early.
  if (get_pin_func_() == kPinStateWhenButtonIsReleased) {
    instant_press_state_ = false;
    state_.is_pressed = false;
    state_.pressed_duration = TimeDuration(0);
    return pw::OkStatus();
  }

  // If we arrive here and instant pin press is false, it means we are in
  // the first pass of Process() where the pin is pressed, start debounce.
  if (instant_press_state_ == false) {
    debounce_start_time_point_ = clock_.now();
    instant_press_state_ = true;
  }

  TimeDuration current_duration = clock_.now() - debounce_start_time_point_;

  if (current_duration > debounce_duration_) {
    state_.is_pressed = true;
    state_.pressed_duration = current_duration;
  }

  return pw::OkStatus();
}

}  // namespace tupa::button