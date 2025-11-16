#pragma once
#include <PS2X_lib.h>

PS2X ps2x; // Tạo đối tượng PS2 Controller Class
#define BEBUG_CTRL

// Hiệu chuẩn cho tay cầm PS2
#define X_JOY_CALIB 127
#define Y_JOY_CALIB 128

// Định nghĩa chân
#define PS2_DAT 12 // MOSI
#define PS2_CMD 13 // MISO
#define PS2_SEL 15 // SS
#define PS2_CLK 14 // SLK

// Hàm thiết lập tay cầm PS2
void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    // Cấu hình gamepad
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}