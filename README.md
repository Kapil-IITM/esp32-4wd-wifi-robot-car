ESP32 WiFi Robot Car (L298N)

📌 Overview

A WiFi-controlled 4WD robot car built using ESP32 and L298N motor driver. The robot is controlled in real-time through a mobile browser.

---

🚀 Features

- WiFi control using mobile phone
- Forward, backward, left, and right movement
- Real-time response

---

⚙️ Components Used

1. ESP32 Development Board
2. L298N Motor Driver Module
3. 4 × BO DC Gear Motors (300 RPM)
4. 11.1V Battery Pack
5. Robot Chassis with Wheels
6. Buck Converter (for voltage regulation)
7. Jumper wires

---
🧠 Working Principle

The ESP32 connects to a WiFi network and hosts a web server.
A mobile phone connected to the same network can access the robot’s IP address through a browser.

The web interface provides control buttons. When a button is pressed:
A request is sent to the ESP32
ESP32 processes the command
Signals are sent to the motor driver
Motors move accordingly

Speed of the motors is controlled using PWM (Pulse Width Modulation).

---

🚀 How to Use

1. Upload the code to ESP32 using Arduino IDE
2. Connect ESP32 to your WiFi network
3. Open Serial Monitor and note the IP address
4. Connect your phone to the same WiFi
5. Open browser and enter the IP address
6. Control the robot using on-screen buttons

---


⚡ Power System

1. Battery directly powers the motor driver
2. Buck converter steps down voltage for ESP32
3. Common ground is maintained across all components

---

👨‍💻 Author

Kapil