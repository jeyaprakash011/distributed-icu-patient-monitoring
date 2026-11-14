# distributed-icu-patient-monitoring
Embedded C-based distributed ICU patient monitoring system using LPC2129 ARM7, CAN communication, ADC, I2C, UART, and MAX30102 for patient vital monitoring.
# Distributed ICU Patient Monitoring Network

## Overview
The Distributed ICU Patient Monitoring Network is an embedded monitoring project developed using the LPC2129 ARM7 microcontroller.

The system collects patient monitoring parameters using sensors and transmits the sensor data between embedded nodes through CAN communication. The receiver node processes the received information and displays the monitoring values through UART serial communication.

## Features
- Temperature monitoring using an analog temperature sensor
- Light intensity monitoring using an LDR
- SpO2 monitoring using the MAX30102 sensor
- ADC interfacing with LPC2129
- I2C communication for MAX30102
- CAN communication between transmitter and receiver nodes
- UART-based serial monitoring
- Modular Embedded C drivers

## Hardware
- LPC2129 ARM7 microcontrollers
- Temperature sensor
- Light Dependent Resistor (LDR)
- MAX30102 SpO2 sensor
- CAN communication interface
- UART serial interface

## Software
- Embedded C
- Keil µVision
- LPC2129 microcontroller
- UART, I2C, CAN protocols
- ADC peripheral programming

## Project Architecture

### Transmitter Node
1. Reads temperature and LDR sensor values using ADC.
2. Reads Red and IR samples from MAX30102 through I2C.
3. Calculates an SpO2 estimate.
4. Packs sensor values into a CAN data frame.
5. Transmits monitoring data to the receiver node.

### Receiver Node
1. Receives sensor data through CAN.
2. Extracts the received sensor values.
3. Converts ADC readings into temperature and light values.
4. Displays monitoring information through UART serial communication.

## Repository Structure
- `tx_main.c` – Transmitter application
- `rx_main.c` – Receiver application
- `adc_driver.c` – ADC driver
- `can1_driver.c` – CAN1 driver
- `i2c_driver.c` – I2C driver
- `max30102.c` – MAX30102 sensor driver
- `spo2_sample.c` – SpO2 calculation
- `uart0_driver.c` – UART0 driver
- `delay.c` – Delay implementation
- `header.h` – Common header and definitions

## Learning Outcomes
- LPC2129 peripheral programming
- Embedded C driver development
- Sensor interfacing
- CAN-based communication between embedded nodes
- I2C sensor communication
- UART debugging and monitoring
- Embedded system integration

## Disclaimer
This project is intended for educational and embedded systems development purposes. It is not a certified medical device and must not be used for clinical diagnosis or patient treatment.
