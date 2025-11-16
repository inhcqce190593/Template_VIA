Hướng dẫn sử dụng Template cho mạch VIA

## Các thông thông số điều khiển

* Điều khiển 4 motor DC độc lập (lái vi sai) bằng 2 joystick.
* Chế độ "Turbo" (Nút R2) để tăng tốc độ.
* Điều khiển 6 servo (bao gồm cả loại 180° và 360°) bằng các nút bấm.
* Giao tiếp qua Serial Monitor để debug.
* Cấu trúc code C++ sạch sẽ, tách biệt file Header (.h) và Source (.cpp).

---

## ⚙️ Cấu hình Phần cứng & Pinout

### 1. Thành phần
* **Vi điều khiển:** ESP32 (hoặc tương đương).
* **Đầu vào:** Tay cầm PlayStation 2 (PS2) và mạch chuyển.
* **Điều khiển:** Module 16 kênh PWM PCA9685 (điều khiển motor & servo).
* **Driver Motor:** Cần 2-4 driver (ví dụ: L298N, TB6612) để điều khiển 4 motor DC.
* **Đầu ra:** 4 Motor DC và 6 Servo.

### 2. Sơ đồ Kết nối

#### Kết nối Tay cầm PS2 (File: `PS2_controller.h`)
| Chức năng | Chân ESP32 |
| :--- | :--- |
| PS2_DAT (MOSI) | 12 |
| PS2_CMD (MISO) | 13 |
| PS2_SEL (SS) | 15 |
| PS2_CLK (SLK) | 14 |

#### Kết nối Module PCA9685 (I2C)
* **SDA**: GPIO 21
* **SCL**: GPIO 22

#### Sơ đồ Kênh PCA9685
| Kênh (Channel) | Chức năng | Chi tiết (từ code) |
| :--- | :--- | :--- |
| 2 | Servo 1 (180°) | `SERVO_180_1` |
| 3 | Servo 2 (180°) | `SERVO_180_2` |
| 4 | Servo 3 (180°) | `SERVO_180_3` |
| 5 | Servo 4 (180°) | `SERVO_180_4` |
| 6 | Servo 5 (360°) | `SERVO_360_1` |
| 7 | Servo 6 (360°) | `SERVO_360_2` |
| 8, 9 | Motor 1 (DC) | `PWM_CHANNEL1`, `PWM_CHANNEL2` |
| 10, 11 | Motor 2 (DC) | `PWM_CHANNEL3`, `PWM_CHANNEL4` |
| 13, 12 | Motor 3 (DC) | `PWM_CHANNER1`, `PWM_CHANNER2` |
| 14, 15 | Motor 4 (DC) | `PWM_CHANNER3`, `PWM_CHANNER4` |

---

## 🕹️ Sơ đồ Điều khiển

### Điều khiển Motor (`motor_control.h`)
* **Joystick Phải**: Điều khiển **Motor 1** và **Motor 2**.
* **Joystick Trái**: Điều khiển **Motor 3** và **Motor 4**.
* **Giữ R2**: Kích hoạt "Turbo" (`TOP_SPEED`).
* **Giữ D-Pad Lên**: Chạy Motor 1 tới.
* **Giữ D-Pad Xuống**: Chạy Motor 2 lùi.
* *(Các nút D-Pad, L1, R1... khác cho motor hiện đang bị vô hiệu hóa (comment) trong `motor_control.cpp`).*

### Điều khiển Servo (`servo_control.h`)
* **Giữ L3**: Servo 1 (Kênh 2) quay ra MAX.
* **Giữ L2**: Servo 1 (Kênh 2) quay về MIN.
* **Thả L2/L3**: Servo 1 (Kênh 2) tự động về MIN.
* **Nhấn Tam Giác**: Servo 6 (Kênh 7) quay tới.
* **Nhấn X**: Servo 6 (Kênh 7) quay lùi.
* **Nhấn Vuông**: Servo 6 (Kênh 7) dừng.
* **Servo 2, 3, 4, 5**: Hiện chưa được gán nút điều khiển.

---

## 🔧 Cài đặt & Tùy chỉnh

### 1. Thư viện cần thiết
Đảm bảo bạn đã cài đặt các thư viện sau qua Library Manager:
* `PS2X_lib`
* `Adafruit_PWMServoDriver`
* `Wire` (Thường có sẵn)

### 2. Tùy chỉnh Điều khiển
* **Để thêm nút cho Motor:** Mở `motor_control.cpp` và bỏ comment (uncomment) các khối `else if` cho `PSB_PAD_LEFT`, `PSB_L1`, v.v.
* **Để thêm nút cho Servo:** Mở `servo_control.cpp` và thêm logic cho các biến `servo_180_2_pos`, `servo_360_1_state`, v.v. bên trong hàm `handleServoInput()`.
* **Hiệu chỉnh Servo:** Mở `servo_control.h` và điều chỉnh các giá trị `SERVO_180_MIN`, `SERVO_180_MAX` cho đến khi servo quay đúng góc 0-180.

## 📄 Giấy phép (License)
Dự án này được phát hành dưới Giấy phép MIT. Xem tệp `LICENSE` để biết chi tiết.
