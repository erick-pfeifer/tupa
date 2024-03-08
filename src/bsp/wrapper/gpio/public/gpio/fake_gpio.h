#pragma once

namespace tupa::gpio {

/**
 * @brief Fake GPIO class for unit tests.
 */
class FakeDigitalInput {
 public:
  FakeDigitalInput(bool initial_state = false) : state_(initial_state) {}

  bool GetState() { return state_; }
  void SetState(bool new_state) { state_ = new_state; }

 private:
  bool state_;
};

}  // namespace tupa::gpio
