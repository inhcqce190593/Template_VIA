#pragma once
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8 //motor 1
#define PWM_CHANNEL2 9 //motor 1
#define PWM_CHANNEL3 10 //motor 2
#define PWM_CHANNEL4 11 //motor 2
#define PWM_CHANNER1 13 //motor 3
#define PWM_CHANNER2 12 //motor 3
#define PWM_CHANNER3 14 //motor 4
#define PWM_CHANNER4 15 //motor 4

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWMMotors(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8) {
  char dbg_str[60];
  sprintf(dbg_str, "Drive: %d,%d,%d,%d | Aux: %d,%d,%d,%d", c1, c2, c3, c4, c5, c6, c7, c8);
  Serial.println(dbg_str);

  pwm.setPin(PWM_CHANNEL1, c1); //C1_motor1 
  pwm.setPin(PWM_CHANNEL2, c2); //C2_motor1
  pwm.setPin(PWM_CHANNEL3, c3); //C3_motor2
  pwm.setPin(PWM_CHANNEL4, c4); //C4_motor2

  pwm.setPin(PWM_CHANNER1, c5); //C5_motor3
  pwm.setPin(PWM_CHANNER2, c6); //C6_motor3
  pwm.setPin(PWM_CHANNER3, c7); //C7_motor4
  pwm.setPin(PWM_CHANNER4, c8); //C8_motor4
}

void initMotors() {
  Wire.begin();  // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);

  setPWMMotors(0, 0, 0, 0, 0, 0, 0, 0);
}
