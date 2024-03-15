#pragma once

namespace tupa::gpio {

/**
 * @brief Gets pin state of the TCC0 wave generator.
 *
 * @return true
 * @return false
 */
bool GetTCC0PinState();

/**
 * @brief Get the Btn Left Pin State.
 *
 * @return true
 * @return false
 */
bool GetBtnLeftPinState();

/**
 * @brief Get the Btn Right Pin State.
 *
 * @return true
 * @return false
 */
bool GetBtnRightPinState();

/**
 * @brief Get the Low Limit Sensor Pin State.
 *
 * @return true
 * @return false
 */
bool GetLowLimitSensorPinState();

/**
 * @brief Get the High Limit Sensor Pin State.
 *
 * @return true
 * @return false
 */
bool GetHighLimitSensorPinState();

/**
 * @brief Get the board Pin State.
 *
 * @return true
 * @return false
 */
bool GetBoardPinState();

/**
 * @brief Set the debug pin state
 *
 * @param state True/False for high/low states.
 */
void SetDbgPin(bool state);

/**
 * @brief Set the Motor Enable Pin.
 *
 * @param state True/False for high/low states.
 */
void SetMotorEnablePin(bool state);

/**
 * @brief Set the Motor Direction Pin.
 *
 * @param state True/False for high/low states.
 */
void SetMotorDiretionPin(bool state);

/**
 * @brief Set the Board LED Pin.
 *
 * @param state True/False for high/low states.
 */
void SetBoardLedPin(bool state);

}  // namespace tupa::gpio
