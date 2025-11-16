Dự án này cho phép điều khiển đồng thời 4 motor DC (thông qua 8 kênh PWM) và nhiều servo (cả loại 180° và 360°).
⚙️ Cấu hình Phần cứng & Pinout
Dự án sử dụng 2 thành phần chính để điều khiển: Tay cầm PS2 (đầu vào) và module PCA9685 (đầu ra).
1. Kết nối Tay cầm PS2 (File: PS2_controller.h 1)
Các chân này được định nghĩa để kết nối trực tiếp với bo mạch ESP32.
Chức năng	Chân ESP32
PS2_DAT (MOSI)	12 2
PS2_CMD (MISO)	13 3
PS2_SEL (SS)	15 4
PS2_CLK (SLK)	14 5
2. Kết nối Module PCA9685 (File: motors.h 6 & servo_control.h)
Module PCA9685 được kết nối qua I2C. Trên hầu hết các bo ESP32, các chân I2C mặc định là:
•	SDA: GPIO 21
•	SCL: GPIO 22
Các kênh trên module PCA9685 được gán như sau:
Kênh (Channel)	Chức năng	Chi tiết (từ code)
Servo 1	Servo 180°	SERVO_180_1 (Kênh 2)
Servo 2	Servo 180°	SERVO_180_2 (Kênh 3)
Servo 3	Servo 180°	SERVO_180_3 (Kênh 4)
Servo 4	Servo 180°	SERVO_180_4 (Kênh 5)
Servo 5	Servo 360°	SERVO_360_1 (Kênh 6)
Servo 6	Servo 360°	SERVO_360_2 (Kênh 7)
Motor 1 (C1/C2)	Motor DC 1	PWM_CHANNEL1 / PWM_CHANNEL2 (Kênh 8, 9) 7
Motor 2 (C3/C4)	Motor DC 2	PWM_CHANNEL3 / PWM_CHANNEL4 (Kênh 10, 11) 8
Motor 3 (C5/C6)	Motor DC 3	PWM_CHANNER1 / PWM_CHANNER2 (Kênh 13, 12) 9
Motor 4 (C7/C8)	Motor DC 4	PWM_CHANNER3 / PWM_CHANNER4 (Kênh 14, 15) 10
________________________________________
🕹️ Sơ đồ Điều khiển (Hiện tại)
Đây là các lệnh điều khiển đang được kích hoạt trong code (các phần không bị comment).
Điều khiển Motor (File: motor_control.h)
Hệ thống truyền động chính sử dụng 2 joystick analog (lái vi sai):
•	Right Joystick (PSS_RX, PSS_RY): Điều khiển Motor 1 và Motor 2.
•	Left Joystick (PSS_LX, PSS_LY): Điều khiển Motor 3 và Motor 4.
•	Nút R2 (Giữ): Kích hoạt tốc độ tối đa (TOP_SPEED - 3500) thay vì tốc độ thường (NORM_SPEED - 2048).
Điều khiển Servo (File: servo_control.h)
•	Nút L3 (Nhấn giữ): SERVO_180_1 (Kênh 2) quay đến vị trí SERVO_180_MAX.
•	Nút L2 (Nhấn giữ): SERVO_180_1 (Kênh 2) quay đến vị trí SERVO_180_MIN.
•	(Khi thả L2/L3): SERVO_180_1 (Kênh 2) tự động quay về SERVO_180_MIN.
•	Nút Tam giác (Triangle): SERVO_360_2 (Kênh 7) quay tới (SERVO_360_FWD).
•	Nút X (Cross): SERVO_360_2 (Kênh 7) quay lùi (SERVO_360_REV).
•	Nút Vuông (Square): SERVO_360_2 (Kênh 7) dừng (SERVO_360_STOP).
Các nút/Servo chưa gán (Mặc định)
•	Nút: D-Pad (Up, Down, Left, Right), L1, R1, R3, Circle.
•	Servo: SERVO_180_2, SERVO_180_3, SERVO_180_4, SERVO_360_1.
________________________________________
🔧 Cách tùy chỉnh Điều khiển
Toàn bộ logic điều khiển nằm trong 2 file: motor_control.h và servo_control.h. Bạn có thể dễ dàng sửa đổi các file này.
1. Thay đổi Điều khiển Motor (File: motor_control.h)
Trong hàm handlePS2Input(), bạn sẽ thấy một khối if-else lớn.
•	Để kích hoạt D-Pad (Nút điều hướng):
Tìm và bỏ comment (uncomment) các khối else if cho PSB_PAD_UP, PSB_PAD_DOWN, PSB_PAD_LEFT, PSB_PAD_RIGHT.
// Bỏ comment dòng này
// else if (ps2x.Button(PSB_PAD_LEFT)) {
//   c2 = TURN_SPEED;
//   c3 = TURN_SPEED;
// }
•	Để gán chức năng cho các nút vai (L1, R1...):
Tương tự, hãy bỏ comment các khối else if cho PSB_L1, PSB_L2, PSB_R1, v.v. và gán tốc độ (ví dụ: c5 = NORM_SPEED;) cho motor bạn muốn.
•	Thay đổi tốc độ:
Bạn có thể điều chỉnh các giá trị #define ở đầu file:
o	TOP_SPEED: Tốc độ tối đa (khi giữ R2).
o	NORM_SPEED: Tốc độ chuẩn cho các nút.
o	TURN_SPEED: Tốc độ khi rẽ (dùng cho D-Pad).
2. Thay đổi Điều khiển Servo (File: servo_control.h)
Trong hàm handleServoInput().
•	Thay đổi logic Nhấn-giữ sang Nhấn-thả:
Code hiện tại dùng ps2x.Button() (nhấn giữ) cho servo 180°. Nếu bạn muốn nhấn 1 lần để đi đến vị trí, nhấn lần nữa để về, hãy sử dụng logic trong khối bị comment:
// // Logic nhấn 1 lần (ButtonPressed)
// if (ps2x.ButtonPressed(PSB_L1)) {
//   servo_180_1_pos = SERVO_180_MAX;
// }
// if (ps2x.ButtonPressed(PSB_L2)) {
//   servo_180_1_pos = SERVO_180_MIN;
// }
// // Đừng quên gọi setServo ở cuối
// setServo(SERVO_180_1, servo_180_1_pos);
•	Gán chức năng cho các Servo khác:
Chỉ cần sao chép logic và áp dụng cho các biến servo_180_2_pos, servo_360_1_state, v.v.. Ví dụ, gán R1 và R3 cho SERVO_180_2:
// Thêm logic này vào handleServoInput()
if (ps2x.Button(PSB_R1)) {
  setServo(SERVO_180_2, SERVO_180_MAX);
} else if (ps2x.Button(PSB_R3)) {
  setServo(SERVO_180_2, SERVO_180_MIN);
} else {
  // Quyết định vị trí mặc định khi không nhấn
  setServo(SERVO_180_2, SERVO_180_MIN);
}
•	Hiệu chỉnh góc Servo 180°:
Nếu servo không quay đúng 0° hoặc 180°, hãy điều chỉnh các giá trị #define ở đầu file:
o	SERVO_180_MIN
o	SERVO_180_MAX
________________________________________
🚀 Hướng dẫn Sử dụng
1.	Thư viện: Đảm bảo bạn đã cài đặt các thư viện cần thiết:
o	PS2X_lib (cho tay cầm PS2) 11
o	Adafruit_PWMServoDriver (cho module PCA9685) 12
o	Wire (Thường có sẵn trong Arduino/PlatformIO) 13
2.	Kết nối: Kết nối phần cứng theo sơ đồ Pinout ở trên.
3.	Biên dịch & Nạp code: Mở file code_PS2_Control.ino 14 bằng Arduino IDE hoặc PlatformIO và nạp code vào ESP32.
4.	Debug: Mở Serial Monitor ở baudrate 11520015. Bạn sẽ thấy các giá trị PWM của motor được in ra màn hình khi bạn điều khiển (Drive: ... | Aux: ...).

