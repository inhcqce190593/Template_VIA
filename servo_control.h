#pragma once

#include "motors.h"
#include "PS2_controller.h"

#define SERVO_180_1 2  //servo channel 2
#define SERVO_180_2 3  //servo channel 3
#define SERVO_180_3 4  //servo channel 4
#define SERVO_180_4 5  //servo channel 5
#define SERVO_360_1 6  //servo channel 6
#define SERVO_360_2 7  //servo channel 7

// --- GIÁ TRỊ XUNG CHO SERVO 180° ---
#define SERVO_180_MIN 180
#define SERVO_180_MAX 375
// int servoAngles[6] = { 90, 90, 90, 90, 90, 90 };
// int servoMoveSpeed = 3;
// --- GIÁ TRỊ XUNG CHO SERVO 360° ---
#define SERVO_360_REV 100
#define SERVO_360_STOP 600
#define SERVO_360_FWD 400

// Hàm helper
void setServo(uint8_t channel, uint16_t pulse) {
  pwm.setPin(channel, pulse);
}

// --- Biến "nhớ" cho 6 servo ---
// (THAY ĐỔI: Khởi tạo ở vị trí MIN)
uint16_t servo_180_1_pos = SERVO_180_MIN;
uint16_t servo_180_2_pos = SERVO_180_MIN;
uint16_t servo_180_3_pos = SERVO_180_MIN;
uint16_t servo_180_4_pos = SERVO_180_MIN;

uint16_t servo_360_1_state = SERVO_360_STOP;
uint16_t servo_360_2_state = SERVO_360_STOP;

void setupServos() {
  setServo(SERVO_180_1, servo_180_1_pos);
  setServo(SERVO_180_2, servo_180_2_pos);
  setServo(SERVO_180_3, servo_180_3_pos);
  setServo(SERVO_180_4, servo_180_4_pos);
  setServo(SERVO_360_1, servo_360_1_state);
  setServo(SERVO_360_2, servo_360_2_state);
}

void handleServoInput() {

  /**
  ps2x.ButtonPressed để nhấn 1 lần rồi set góc mặc định
  */

  // if (ps2x.ButtonPressed(PSB_L1)) {
  //   servo_180_1_pos = SERVO_180_MAX;
  // }
  // if (ps2x.ButtonPressed(PSB_L2)) {
  //   servo_180_1_pos = SERVO_180_MIN;
  // }

  // setServo(SERVO_180_1, servo_180_1_pos);
  /**
ps2x.Button để nhấn giữ rồi khi buông ra thì trả về vị trí ban đầu
*/

  if (ps2x.Button(PSB_L3)) {               // Nếu ĐANG GIỮ L1
    setServo(SERVO_180_1, SERVO_180_MAX);  // Trực tiếp quay ra MAX
    // servo_180_1_pos = 180; // Nếu muốn mặc định quay theo vị trí góc mong muốn
  } else if (ps2x.Button(PSB_L2)) {        // Nếu ĐANG GIỮ L2
    setServo(SERVO_180_1, SERVO_180_MIN);  // Trực tiếp quay về MIN
    // servo_180_1_pos = 0;
  } else {
    setServo(SERVO_180_1, SERVO_180_MIN);
    //   servo_180_1_pos = SERVO_180_MIN;
  }

  // Logic cho Servo 360 Kênh 7 (Tam Giác, X, Vuông)
  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {  // Nhấn Tam Giác
    servo_360_2_state = SERVO_360_FWD;     // Cập nhật biến nhớ -> Quay Tới
  }
  if (ps2x.ButtonPressed(PSB_CROSS)) {  // Nhấn X
    servo_360_2_state = SERVO_360_REV;  // Cập nhật biến nhớ -> Quay Lùi
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) {  // Nhấn Vuông
    servo_360_2_state = SERVO_360_STOP;  // Cập nhật biến nhớ -> Dừng
  }

  setServo(SERVO_180_2, servo_180_2_pos);
  setServo(SERVO_180_3, servo_180_3_pos);
  setServo(SERVO_180_4, servo_180_4_pos);

  setServo(SERVO_360_1, servo_360_1_state);
  setServo(SERVO_360_2, servo_360_2_state);
}