
#include "motor_control.h"
#include "servo_control.h"

void setup() {
  Serial.begin(115200);
  initMotors();          // Từ motors.h
  setupPS2controller();  // Từ PS2_controller.h
  
  setupServos(); 

  Serial.println("Done setup!");
}

void loop() {
  // 1. Đọc dữ liệu từ tay cầm
  ps2x.read_gamepad(0, 0);
  
  // 2. Xử lý Cụm Motor
  handlePS2Input();
  
  // 3. Xử lý Cụm Servo
  handleServoInput();

  delay(50);
}