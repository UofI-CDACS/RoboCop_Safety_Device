# RoboCop: Distance Measurement and Workspace Safety

This project, **RoboCop**, is a real-time distance measurement system for enhancing safety at the workspace. It uses a **Nano ESP32 microcontroller** based on the Xtensa LX7 processor, **HC-SR04 ultrasonic sensor** for measuring distance based on the principle of echolocation, and the **Modbus protocol** to transmit distance readings over Wi-Fi. The system can be integrated with robotics applications and/or monitoring tools.

---

## Table of Contents

1. [Usage](#usage)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Project Structure](#project-structure)
5. [How to Build](#how-to-build) 
<!-- 6. [Contributing](#contributing)
7. [License](#license) -->

---


## Usage

### Overview
The system measures the distance of nearby objects using an ultrasonic sensor, calculates the value, and transmits it over a Wi-Fi network using Modbus TCP. Users can access this data using the Python client or any Modbus-compatible software.

### Key Parameters
- **Wi-Fi**: Connects to the `AirVandalRobot` network with the password `xxxx`.
- **Static IP Address**: The ESP32 is assigned the static IP `129.xx.xx.xx`.
- **Modbus Unsigned Holding Register**: 
  - The measured distance is stored in the unsigned holding register at address **5**.
  - This value is scaled as an integer (distance in cm multiplied by 100).

### How to Use
1. **Power on the Device**:
   - Connect the ESP32 to a power source using the USB Type C terminal.
   - Wait for it to connect to the `AirVandalRobot` Wi-Fi network.

2. **Clone the Repository**:
    -   ```
            git clone https://github.com/UofI-CDACS/RoboCop_Safety_Device.git
        ```

3. **Install project requirements**:
    -   ```
            pip install -r requirements.txt
        ```

4. **Move to Python_Client folder**:
    - ```
            cd Python_Client/
      ```

5. **Client.py**
    - Open the client_distance.py file
    - Edit the Server_IP
        - Replace with the IP address being displayed in the LCD screen of the RoboCop device you want to read
            - Example: <br />
                SERVER_IP = "192.102.98.2"
        
        - Leave the port and holding register unchanged <br />
            SERVER_PORT = 502 <br />
            REGISTER_ADDRESS = 5



    

2. **Access the Data**:
   - Use the provided Python client (`Python_Client/client_distance.py`) to read the distance value from the Modbus server:
     ```bash
     python client_distance.py
     ```
   - Alternatively, use a Modbus-compatible application (e.g., ModScan, QModMaster, Modbus Poll, etc):
     - **IP Address**: `129.xx.xx.xx`
     - **Port**: `502`
     - **Register**: `5` (holding register for the distance)
          - This Register stores 16 bit value of unsigned integers

3. **View on LCD**:
   - The LCD displays the device’s static IP and the measured distance in real time.

4. **Testing**:
   - Place objects in front of the ultrasonic sensor and observe distance changes on the LCD or Python client output.


---

## Features

- **Accurate Distance Measurement**:
  - Measures distances between 2 cm and 400 cm using an ultrasonic sensor.
  
- **Modbus TCP Support**:
  - Transmits real-time distance data over the network.
  
- **LCD Display**:
  - Displays the static IP and the measured distance.
  
- **Python Client**:
  - Reads and interprets the Modbus data.
  
- **3D Printable Enclosure**:
  - Protects the hardware with custom STL files.

---


## Requirements

### Software
- Arduino IDE
- Python 3.x
- Libraries: `pymodbus`, `rgb_lcd`, `WiFi`, `ModbusIP_ESP8266`

### Hardware
- ESP32 microcontroller
- HC-SR04 ultrasonic sensor
- LCD display
- Wi-Fi network



---

## Project Structure
### 1. **Arduino**
Contains the Arduino code (`robo.ino`) to set up the ESP32 microcontroller, manage Wi-Fi and Modbus connectivity, and interface with the HC-SR04 ultrasonic sensor and LCD.

### 2. **Python**
Contains the `distance_reader.py` script to fetch distance readings from the ESP32 Modbus server using the Python Modbus library (`pymodbus`).

### 3. **3D_Models**
Includes STL files for:
- Mounting the ultrasonic sensor.
- Housing the ESP32 and LCD.

### 4. **Images**
Visual documentation:
- `block_diagram.png`: High-level system workflow.
- `wiring_diagram.png`: Connection guide for Arduino, sensors, and peripherals.

### 5. **Docs**
Additional resources:
- Device datasheets (e.g., HC-SR04, ESP32).
- Project report.


---

## How to Build
### Step 1: Hardware Setup
1. **Connect Components**:
   - **HC-SR04 Ultrasonic Sensor**:
     - TRIG pin → ESP32 D6
     - ECHO pin → ESP32 D7
   - **LCD Screen**:
     - Connect via I2C (SDA and SCL pins).
   - **ESP32**:
     - Set up on a static IP for Modbus communication.
2. **3D Print Mounts**:
   - Use the STL files in the `3D_Models` folder to 3D print the sensor and ESP32 mounts.

<!-- 3. **Wiring Diagram**:
   - Refer to `wiring_diagram.png` in the `Images` folder. -->

---

### Step 2: Software Setup
#### **Arduino**
1. Install the following libraries:
   - `rgb_lcd` for LCD.
   - `ModbusIP_ESP8266` for Modbus communication.
   - `WiFi.h` for ESP32 Wi-Fi management.

2. Upload the Arduino code from `Arduino/robo.ino` to the ESP32.

3. Ensure your Wi-Fi credentials and static IP configuration match your network setup:
   ```cpp
   const char* ssid = "SSID";
   const char* password = "PASSWORD";
