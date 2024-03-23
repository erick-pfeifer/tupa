#pragma once

#include <cstdint>

#include "button/button.h"
#include "pw_chrono/system_clock.h"
#include "pw_status/status.h"
#include "sqr_wave/sqr_wave.h"

namespace tupa::piston_control {

using OutputPinFunction = void (*)(bool);
using TimeDuration = pw::chrono::SystemClock::duration;
using TimePoint = pw::chrono::SystemClock::time_point;

inline constexpr uint32_t kMotorSpeedFast = 5000u;
inline constexpr uint32_t kMotorSpeedSlow = 2000u;

inline constexpr uint32_t kBurstCountToPressPosition1 = 16000;
inline constexpr uint32_t kBurstCountToPressPosition2 = 5000;
inline constexpr uint32_t kBurstCountToPressPosition3 = 2000;
inline constexpr uint32_t kBurstCountFromPressToReleasePosition = 1000;

inline constexpr TimeDuration kTimeToWaitOnPressedPosition =
    TimeDuration(std::chrono::milliseconds(500));

enum class StateMachine : uint8_t {
  kInit,
  kLowLimitIsPressed,
  kDriveToLowLimit,
  kDriveToPressPosition1,
  kDriveToPressPosition2,
  kDriveToPressPosition3,
  kWaitBeforeRelease,
  kDriveToReleasePostion,
  kWaitingOnReleasePostion,
  kDriveToExtractPostion,
};

class PistonControl {
 public:
  PistonControl(button::Button& low_limit_btn,
                button::Button& high_limit_btn,
                button::Button& left_btn,
                button::Button& right_btn,
                OutputPinFunction motor_enable_pin_set_func,
                OutputPinFunction motor_direction_pin_set_func,
                sqr_wave::SqrWave& motor_sqr_wave,
                pw::chrono::VirtualSystemClock& clock =
                    pw::chrono::VirtualSystemClock::RealClock())
      : low_limit_btn_(low_limit_btn),
        high_limit_btn_(high_limit_btn),
        left_btn_(left_btn),
        right_btn_(right_btn),
        motor_enable_pin_set_func_(motor_enable_pin_set_func),
        motor_direction_pin_set_func_(motor_direction_pin_set_func),
        motor_sqr_wave_(motor_sqr_wave),
        clock_(clock) {
    MotorDisable();
    motor_sqr_wave_.StopBurst();
    motor_sqr_wave_.SetEnable(false);
  }
  ~PistonControl() = default;

  /**
   * @brief Main process algorithm, runs most of the logic.
   *
   * @return pw::Status OK if no errors.
   */
  pw::Status Process();

  /**
   * @brief Manual piston control with buttons.
   *
   */
  void ManualControl();

  /**
   * @brief Get the state machine current state
   *
   * @return StateMachine state.
   */
  inline StateMachine GetState() const { return state_; }

 private:
  button::Button& low_limit_btn_;
  button::Button& high_limit_btn_;
  button::Button& left_btn_;
  button::Button& right_btn_;
  OutputPinFunction motor_enable_pin_set_func_;
  OutputPinFunction motor_direction_pin_set_func_;
  sqr_wave::SqrWave& motor_sqr_wave_;
  pw::chrono::VirtualSystemClock& clock_;
  TimePoint wait_time_point_begin_;
  StateMachine state_ = StateMachine::kInit;

  void MotorEnable() { motor_enable_pin_set_func_(false); }
  void MotorDisable() { motor_enable_pin_set_func_(true); }

  void MotorDirectionUp() { motor_direction_pin_set_func_(false); }
  void MotorDirectionDown() { motor_direction_pin_set_func_(true); }
};

}  // namespace tupa::piston_control
