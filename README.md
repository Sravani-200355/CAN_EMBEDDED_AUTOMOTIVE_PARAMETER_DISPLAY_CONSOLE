# 🚗 CANTRACK - Embedded Automotive Parameter Display Console

## 📖 Overview

CANTRACK is an Embedded Automotive Parameter Display Console designed to monitor and display essential vehicle parameters in real time using the Controller Area Network (CAN) protocol. The system reads, decodes, and displays vehicle information such as door status, engine temperature, and warning indicators on an LCD display.

The project demonstrates the implementation of automotive communication systems using CAN Bus technology and LPC2129 ARM7 microcontrollers.

---

## 🎯 Aim

To develop an embedded automotive console that reads, decodes, and displays essential vehicle parameters from the CAN bus, enabling real-time monitoring of:

- Door Status
- Engine Temperature
- Vehicle Warning Indicators

through a user-friendly display interface.

---

## ✨ Features

- Real-time vehicle parameter monitoring
- CAN Bus communication between multiple nodes
- Engine temperature sensing using DS18B20
- Door status monitoring
- Indicator control and status display
- LCD-based parameter visualization
- Interrupt-driven event handling
- Modular node architecture

---

## 🛠 Hardware Requirements

- LPC2129 ARM7 Microcontroller
- MCP2551 CAN Transceiver
- LCD Display
- DS18B20 Temperature Sensor
- LEDs
- Push Switches
- USB to UART Converter

---

## 💻 Software Requirements

- Embedded C
- Keil µVision IDE
- Flash Magic
- CAN Driver Libraries

---

## 🏗 System Architecture

The project consists of three CAN nodes:

### 1. Main Node
- Reads engine temperature.
- Displays temperature on LCD.
- Receives door status from Door Node.
- Sends indicator control commands to Indicator Node.
- Displays overall vehicle status.

### 2. Door Node
- Monitors four active-low switches.
- Determines door open/closed status.
- Transmits door information through CAN Bus.

### 3. Indicator Node
- Receives CAN messages from Main Node.
- Controls indicator LEDs.
- Displays indicator status.

---

## 🔄 Working Principle

1. Door switches continuously monitor door status.
2. Door Node transmits status to Main Node via CAN.
3. Temperature sensor measures engine temperature.
4. Main Node processes received information.
5. Vehicle parameters are displayed on LCD.
6. Indicator commands are transmitted through CAN.
7. Indicator Node activates corresponding LEDs.

---

## 📊 Communication Protocol

**Protocol Used:** Controller Area Network (CAN)

### CAN Advantages
- Reliable communication
- Error detection and handling
- High-speed data transfer
- Reduced wiring complexity
- Widely used in automotive systems

---

## 📁 Project Structure


CANTRACK/
│
├── main_node.c
├── door_node.c
├── indicator_node.c
├── can.c
├── can.h
├── lcd.c
├── lcd.h
├── ds18b20.c
├── ds18b20.h
├── interrupt.c
├── README.md


---

## 🚀 Implementation Steps

1. Interface and test LCD.
2. Interface active-low switches.
3. Read temperature using DS18B20.
4. Test external interrupts (EINT0 & EINT1).
5. Configure and test CAN communication.
6. Develop Door Node logic.
7. Develop Indicator Node logic.
8. Develop Main Node logic.
9. Integrate all modules.
10. Validate complete system functionality.

---

## 🎓 Learning Outcomes

Through this project, the following concepts were learned:

- Embedded C Programming
- LPC2129 Architecture
- GPIO Programming
- CAN Protocol Implementation
- Sensor Interfacing
- Interrupt Handling
- Real-Time Embedded Systems Design
- Automotive Communication Networks

---

## 🔮 Future Enhancements

- Vehicle speed monitoring
- Fuel level monitoring
- Mobile application integration
- GPS tracking
- Data logging and diagnostics
- IoT-based vehicle monitoring

---

## 👨‍💻 Author

**SRAVANI TATA**

Bachelor of Technology (Electronics and Communication Engineering)
