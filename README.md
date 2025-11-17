# VIA Board Template – Training STEM FPTU 2025

**Template điều khiển Robot dùng ESP32 + PS2 + PCA9685**
Điều khiển đồng thời **4 motor DC** và **6 servo**, code tách file rõ ràng, dễ mở rộng, phù hợp cho giảng dạy – nghiên cứu – CLB STEM.

---


# Giới thiệu
Template mẫu điều khiển robot:
- ESP32 làm vi điều khiển
- Điều khiển bằng tay cầm PS2
- PCA9685 điều khiển nhiều PWM
- 4 Motor DC + 6 Servo hoạt động độc lập
- Code tách `*.h` và `*.cpp` kiểu chuyên nghiệp

---

# Tính năng

### Điều khiển Motor
- Joystick trái + phải điều khiển 4 motor
- R2 = bật Turbo (tốc độ tối đa)
- Có thể mở rộng các nút D-Pad, L1, R1

### Điều khiển Servo
- 6 Servo (180° & 360°)
- Nút L2, L3, △, X, □ được gán sẵn
- Dễ dàng thêm nút trong `servo_control.cpp`

---

# Phần cứng cần có

| Thiết bị | Vai trò |
|---------|---------|
| ESP32 | MCU chính |
| PS2 Controller + adapter | Remote điều khiển |
| PCA9685 | Xuất PWM servo/motor |
| L298N / TB6612 | Driver cho 4 Motor DC |
| 4 DC Motor | Drive |
| 6 Servo 180° / 360° | Servo Control |

---

# Kết nối phần cứng

## Kết nối PS2 → ESP32

| PS2 | ESP32 |
|-----|--------|
| DAT | 12 |
| CMD | 13 |
| SEL | 15 |
| CLK | 14 |

---

## Kết nối PCA9685 → ESP32

| PCA9685 | ESP32 |
|----------|--------|
| SDA | 21 |
| SCL | 22 |

---

## Bảng kênh PCA9685 (mapping trong code)

| Channel | Thiết bị | Biến code |
|---------|----------|------------|
| 2 | Servo 1 (180°) | `SERVO_180_1` |
| 3 | Servo 2 (180°) | `SERVO_180_2` |
| 4 | Servo 3 (180°) | `SERVO_180_3` |
| 5 | Servo 4 (180°) | `SERVO_180_4` |
| 6 | Servo 5 (360°) | `SERVO_360_1` |
| 7 | Servo 6 (360°) | `SERVO_360_2` |
| 8–9 | Motor 1 | PWM 1–2 |
| 10–11 | Motor 2 | PWM 3–4 |
| 12–13 | Motor 3 | PWM 5–6 |
| 14–15 | Motor 4 | PWM 7–8 |

---

# Điều khiển Motor & Servo

## Motor Control

| Nút | Chức năng |
|-----|-----------|
| Joystick phải | Motor 1 & 2 |
| Joystick trái | Motor 3 & 4 |
| **R2** | Turbo Mode |
| D-Pad ↑ | Motor 1 tiến |
| D-Pad ↓ | Motor 2 lùi |

---

## Servo Control

| Nút | Chức năng |
|-----|-----------|
| L3 giữ | Servo 1 → MAX |
| L2 giữ | Servo 1 → MIN |
| △ | Servo 6 tiến |
| X | Servo 6 lùi |
| □ | Servo 6 dừng |

---

# Cấu trúc thư mục

\`\`\`
📁 VIA-Template
 ┣ 📁 src
 │   ┣ motor_control.cpp
 │   ┣ motor_control.h
 │   ┣ servo_control.cpp
 │   ┣ servo_control.h
 │   ┣ PS2_controller.h
 │   ┗ main.ino
 ┣ 📁 lib
 ┣ LICENSE
 ┗ README.md
\`\`\`

---

# Cài đặt & Thư viện

### Library cần cài:

- PS2X_lib
- Adafruit PWM Servo Driver
- Wire (có sẵn)

---

# Chạy thử

1. Upload code vào ESP32  
2. Mở Serial Monitor  
3. Nhấn nút PS2 để kiểm tra kết nối  
4. Thử joystick để xem motor chạy  
5. Nhấn L2, L3 hoặc △, X, □ để test servo  

---

# Tùy chỉnh nâng cao

##Chỉnh góc servo
Trong `servo_control.h`:

```cpp
#define SERVO_180_MIN 110
#define SERVO_180_MAX 500
```

## Thêm nút cho motor
Trong `motor_control.cpp`:

```cpp
else if (ps2x.Button(PSB_L1)) { ... }
```

## Thêm nút cho servo
Trong `servo_control.cpp → handleServoInput()`:

```cpp
servo_180_2_pos = ...
servo_360_1_state = ...
```

---

# API Functions

## Motor API
```cpp
void setupMotors();
void setMotorSpeed(int motor, int speed);
void handleMotorInput();
```

## Servo API
```cpp
void setupServo();
void setServoAngle(int channel, int angle);
void handleServoInput();
```

## PS2 API
```cpp
void setupPS2controller();
bool readPS2();
```

---

# Hướng dẫn
- Nguyễn Thành Công  
- Châu Quốc Inh  

---

# License
Phát hành theo **MIT License**.
