
#include "piston_control/piston_control.h"

#include "pw_log/shorter.h"
#include "pw_status/status.h"
namespace tupa::piston_control {

pw::Status PistonControl::Process() {
  switch (state_) {
    case StateMachine::kInit: {
      // If the piston is not in low limit, any button press will cause it to
      // drive to low limit.
      if ((left_btn_.GetButtonState().is_pressed ||
           right_btn_.GetButtonState().is_pressed) &&
          !low_limit_btn_.GetButtonState().is_pressed) {
        INF("StateMachine: Piston will drive to low limit.");

        MotorDirectionDown();
        MotorEnable();
        motor_sqr_wave_.StopBurst();
        motor_sqr_wave_.SetFreqHz(kMotorSpeedFast);
        motor_sqr_wave_.SetEnable(true);
        state_ = StateMachine::kDriveToLowLimit;
        break;
      }

      // If the piston is in low limit, and the right buttons is pressd,
      // drive to 1st press position.
      if (low_limit_btn_.GetButtonState().is_pressed &&
          right_btn_.GetButtonState().is_pressed) {
        INF("StateMachine: Piston is in low limit rest and will drive"
            " to press position.");
        MotorDirectionUp();
        MotorEnable();
        motor_sqr_wave_.SetFreqHz(kMotorSpeedFast);
        motor_sqr_wave_.RunBurst(kBurstCountToPressPosition);
        state_ = StateMachine::kDriveToPressPostion;
        break;
      }
      break;
    }

    case StateMachine::kDriveToLowLimit: {
      if (low_limit_btn_.GetButtonState().is_pressed) {
        MotorDisable();
        motor_sqr_wave_.StopBurst();
        motor_sqr_wave_.SetEnable(false);
        INF("StateMachine: Drive to low limit done.");
        state_ = StateMachine::kInit;
      }
      break;
    }

    case StateMachine::kDriveToPressPostion: {
      if (!motor_sqr_wave_.IsBurstRunning()) {
        INF("StateMachine: Press is done, Wait for a bit.");
        wait_time_point_begin_ = clock_.now();
        state_ = StateMachine::kWaitBeforeRelease;
      }
      break;
    }

    case StateMachine::kWaitBeforeRelease: {
      if (clock_.now() - wait_time_point_begin_ >
          kTimeToWaitOnPressedPosition) {
        INF("StateMachine: Done Waiting, moving to released.");
        MotorDirectionDown();
        MotorEnable();
        motor_sqr_wave_.StopBurst();
        motor_sqr_wave_.SetFreqHz(kMotorSpeedFast);
        motor_sqr_wave_.SetEnable(true);
        state_ = StateMachine::kDriveToReleasePostion;
      }
      break;
    }

    case StateMachine::kDriveToReleasePostion: {
      if (low_limit_btn_.GetButtonState().is_pressed) {
        MotorDisable();
        motor_sqr_wave_.SetEnable(false);
        INF("StateMachine: In release position.");
        state_ = StateMachine::kWaitingOnReleasePostion;
      }
      break;
    }

    case StateMachine::kWaitingOnReleasePostion: {

      if (right_btn_.GetButtonState().is_pressed) {
        INF("StateMachine: Moving to extract position.");
        MotorDirectionUp();
        MotorEnable();
        motor_sqr_wave_.SetFreqHz(kMotorSpeedFast);
        motor_sqr_wave_.SetEnable(false);
        motor_sqr_wave_.RunBurst(kBurstCountFromReleaseToExtractPosition);
        state_ = StateMachine::kDriveToExtractPostion;
        break;
      }
      break;
    }

    case StateMachine::kDriveToExtractPostion: {
      if (!motor_sqr_wave_.IsBurstRunning()) {
        MotorDisable();
        if (left_btn_.GetButtonState().is_pressed) {
          INF("StateMachine: Reset, going to init state.");
          state_ = StateMachine::kInit;
          break;
        }
      }
      break;
    }

    default:
      MotorDisable();
      ERR("Bad Piston Control state.");
  }
  return pw::OkStatus();
}

}  // namespace tupa::piston_control
