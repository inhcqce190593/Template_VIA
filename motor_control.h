/**
Template:
c1, c2 điều khiển 2 chiều quay của Motor 1 (Kênh 8, 9)
c3, c4 điều khiển 2 chiều quay của Motor 2 (Kênh 10, 11)
c5, c6 điều khiển 2 chiều quay của Motor 3 (Kênh 13, 12)
c7, c8 điều khiển 2 chiều quay của Motor 4 (Kênh 14, 15)
*/



#pragma once
#include "motors.h"
#include "PS2_controller.h"  // Bao gồm đối tượng ps2x

// Các định nghĩa logic
#define TOP_SPEED 3500
#define NORM_SPEED 2048  // Tốc độ chuẩn cho các nút
#define TURN_SPEED 2500  // Tốc độ khi rẽ bằng D-Pad
#define DEADZONE 15

/**
*/

// === SỬA LỖI Ở ĐÂY: Thêm lại dòng định nghĩa hàm ===
void handlePS2Input() {
  int speed = NORM_SPEED;  // Tốc độ mặc định

  if (ps2x.Button(PSB_R2)) {
    speed = TOP_SPEED;
  }

  int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;

  if (ps2x.Button(PSB_PAD_UP)) {
    c1 = NORM_SPEED;
    // c3 = NORM_SPEED;
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    // c2 = NORM_SPEED;
    c4 = NORM_SPEED;
  }
  // else if (ps2x.Button(PSB_PAD_LEFT)) {
  //   c2 = TURN_SPEED;
  //   c3 = TURN_SPEED;
  // }
  // else if (ps2x.Button(PSB_PAD_RIGHT)) {
  //   c1 = TURN_SPEED;
  //   c4 = TURN_SPEED;
  // }
  // else if (ps2x.Button(PSB_L1)) {
  //   c5 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_L2)) {
  //   c6 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_R1)) {
  //   c7 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_TRIANGLE)) {
  //   c5 = NORM_SPEED;
  //   c7 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_CROSS)) {
  //   c6 = NORM_SPEED;
  //   c8 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_SQUARE)) {
  //   c5 = NORM_SPEED;
  // }
  // else if (ps2x.Button(PSB_CIRCLE)) {
  //   c7 = NORM_SPEED;
  // }


  else {
    /**
    Hàm này dùng để điều chỉnh cụm joystick phải, có control tốc độ motor
    */
    int nJoyX = X_JOY_CALIB - ps2x.Analog(PSS_RX);
    int nJoyY = Y_JOY_CALIB - ps2x.Analog(PSS_RY);
    int nMotMixL;
    int nMotMixR;

    if (nJoyX == -1 && nJoyY == 0) { /* c1-c8 đã là 0 */
    } else {
      bool temp = (nJoyY * nJoyX > 0);
      if (nJoyX) {
        nMotMixL = -nJoyX + (nJoyY * temp);
        nMotMixR = nJoyX + (nJoyY * !temp);
      } else {
        nMotMixL = nJoyY;
        nMotMixR = nJoyY;
      }

      if (nMotMixR > DEADZONE) {
        c3 = map(nMotMixR, DEADZONE, 128, 0, speed);
      } else if (nMotMixR < -DEADZONE) {
        c4 = map(abs(nMotMixR), DEADZONE, 128, 0, speed);
      }
      if (nMotMixL > DEADZONE) {
        c1 = map(nMotMixL, DEADZONE, 128, 0, speed);
      } else if (nMotMixL < -DEADZONE) {
        c2 = map(abs(nMotMixL), DEADZONE, 128, 0, speed);
      }
      /**
    Hàm này dùng để điều chỉnh cụm joystick trái, có control tốc độ motor
    */
      int nJoyLX = X_JOY_CALIB - ps2x.Analog(PSS_LX);
      int nJoyLY = Y_JOY_CALIB - ps2x.Analog(PSS_LY);
      int nMotMixL_Aux;
      int nMotMixR_Aux;

      bool temp_Aux = (nJoyLY * nJoyLX > 0);
      if (nJoyLX) {
        nMotMixL_Aux = -nJoyLX + (nJoyLY * temp_Aux);
        nMotMixR_Aux = nJoyLX + (nJoyLY * !temp_Aux);
      } else {
        nMotMixL_Aux = nJoyLY;
        nMotMixR_Aux = nJoyLY;
      }

      if (nMotMixR_Aux > DEADZONE) {
        c7 = map(nMotMixR_Aux, DEADZONE, 128, 0, speed);
      } else if (nMotMixR_Aux < -DEADZONE) {
        c8 = map(abs(nMotMixR_Aux), DEADZONE, 128, 0, speed);
      }
      if (nMotMixL_Aux > DEADZONE) {
        c5 = map(nMotMixL_Aux, DEADZONE, 128, 0, speed);
      } else if (nMotMixL_Aux < -DEADZONE) {
        c6 = map(abs(nMotMixL_Aux), DEADZONE, 128, 0, speed);
      }
    }
  }


  setPWMMotors(c1, c2, c3, c4, c5, c6, c7, c8);

  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    Serial.println("Nút Tam giác vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_SQUARE)) {
    Serial.println("Nút Vuông vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_CIRCLE)) {
    Serial.println("Nút Tròn vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_CROSS)) {
    Serial.println("Nút X vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_PAD_UP)) {
    Serial.println("D-Pad Lên!");
  }
  if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
    Serial.println("D-Pad Xuống!");
  }
  if (ps2x.ButtonPressed(PSB_PAD_LEFT)) {
    Serial.println("D-Pad Trái!");
  }
  if (ps2x.ButtonPressed(PSB_PAD_RIGHT)) {
    Serial.println("D-Pad Phải!");
  }
  if (ps2x.ButtonPressed(PSB_L1)) {
    Serial.println("L1 vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_R1)) {
    Serial.println("R1 vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_L2)) {
    Serial.println("L2 vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_R2)) {
    Serial.println("R2 vùa nhấn (Bắt đầu tăng tốc)!");
  }
  if (ps2x.ButtonPressed(PSB_START)) {
    Serial.println("Start vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_L3))  // Nhấn joystick trái
  {
    Serial.println("L3 vùa nhấn!");
  }
  if (ps2x.ButtonPressed(PSB_R3))  // Nhấn joystick phải
  {
    Serial.println("R3 vùa nhấn!");
  }
}