# VIA Board Template - Training STEM FPTU 2025

Template dieu khien robot dung ESP32, PS2 Controller va PCA9685.

Ho tro dieu khien dong thoi 4 DC Motor va 6 Servo.  
Code duoc tach file ro rang, de mo rong, phu hop cho giang day, nghien cuu va CLB STEM.

---

## Gioi thieu

Template mau dieu khien robot voi cac thanh phan:
- ESP32 lam vi dieu khien trung tam
- PS2 Controller lam thiet bi dieu khien
- PCA9685 mo rong PWM qua I2C
- 4 DC Motor va 6 Servo (180 va 360)
- Code tach file .h va .cpp theo cau truc chuyen nghiep

---

## Tinh nang

### Dieu khien Motor
- Joystick trai va phai dieu khien 4 motor
- Nut R2 bat Turbo Mode (toc do toi da)
- Co the mo rong D-Pad, L1, R1

### Dieu khien Servo
- Ho tro 6 servo (180 va 360)
- Nut L2, L3, TRIANGLE, X, SQUARE da duoc gan san
- De mo rong trong file servo_control.cpp

---

## Phan cung can co

| Thiet bi | Vai tro |
|--------|--------|
| ESP32 | MCU chinh |
| PS2 Controller + Adapter | Dieu khien |
| PCA9685 | Xuat PWM |
| L298N / TB6612 | Driver DC Motor |
| 4 DC Motor | Truyen dong |
| 6 Servo | Dieu khien co cau |

---

## Ket noi phan cung

### PS2 Controller ket noi ESP32

| PS2 | ESP32 GPIO |
|----|------------|
| DAT | 12 |
| CMD | 13 |
| SEL | 15 |
| CLK | 14 |

### PCA9685 ket noi ESP32

| PCA9685 | ESP32 GPIO |
|--------|------------|
| SDA | 21 |
| SCL | 22 |

---

## Mapping kenh PCA9685

| Channel | Thiet bi | Bien trong code |
|--------|---------|----------------|
| 2 | Servo 1 (180) | SERVO_180_1 |
| 3 | Servo 2 (180) | SERVO_180_2 |
| 4 | Servo 3 (180) | SERVO_180_3 |
| 5 | Servo 4 (180) | SERVO_180_4 |
| 6 | Servo 5 (360) | SERVO_360_1 |
| 7 | Servo 6 (360) | SERVO_360_2 |
| 8-9 | Motor 1 | PWM 1-2 |
| 10-11 | Motor 2 | PWM 3-4 |
| 12-13 | Motor 3 | PWM 5-6 |
| 14-15 | Motor 4 | PWM 7-8 |

---

## Dieu khien

### Motor Control

| Nut | Chuc nang |
|----|-----------|
| Joystick phai | Motor 1 va 2 |
| Joystick trai | Motor 3 va 4 |
| R2 | Turbo Mode |
| D-Pad Up | Motor 1 tien |
| D-Pad Down | Motor 2 lui |

### Servo Control

| Nut | Chuc nang |
|----|-----------|
| L3 (giu) | Servo 1 ve MAX |
| L2 (giu) | Servo 1 ve MIN |
| TRIANGLE | Servo 6 tien |
| X | Servo 6 lui |
| SQUARE | Servo 6 dung |

---

## Cau truc thu muc



\`\`\`
📁 TTemplate_VIA
    │   LICENSE
    │   README.md
    │
    ├───code_PS2_Control
    │       PS2_Controller.ino
    │
    ├───include
    │       motors.h
    │       motor_control.h
    │       PS2_controller.h
    │       servo_control.h
    │
\`\`\`

---

## Cai dat thu vien

Cai dat bang Arduino Library Manager:
- PS2X_lib
- Adafruit PWM Servo Driver
- Wire (mac dinh)

---
## Hướng dẫn thiết lập (Quan trọng)
Để biên dịch thành công trên Arduino IDE, bạn cần thực hiện các bước sau:

1. Khởi tạo dự án: Mở file PS2_controller.ino.

2. Tạo thư mục: Khi Arduino IDE yêu cầu tạo thư mục, nhấn OK. IDE sẽ tạo thư mục tên PS2_controller.

3. Di chuyển thư viện: Sao chép/Di chuyển toàn bộ các file .h từ thư mục include vào trong thư mục PS2_controller vừa được tạo.

---
## Chay thu

1. Upload code vao ESP32
2. Mo Serial Monitor
3. Nhan nut PS2 de kiem tra ket noi
4. Test joystick de dieu khien motor
5. Test servo bang L2, L3, TRIANGLE, X, SQUARE

---

## Tuy chinh

### Chinh goc Servo 180

```cpp
#define SERVO_180_MIN 110
#define SERVO_180_MAX 500

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
