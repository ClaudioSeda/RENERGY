# RENERGY

## Description
RENERGY is a library for the Arduino IDE and ESP32 that provides functionalities to manage and monitor renewable energy systems. The library allows users to easily interface with various sensors and devices to collect data and control energy systems.

## Installation
To install the RENERGY library in the Arduino IDE, follow these steps:
1. Download the RENERGY library from the GitHub repository.
2. Open the Arduino IDE.
3. Go to `Sketch` -> `Include Library` -> `Add .ZIP Library...`.
4. Select the downloaded RENERGY library ZIP file.
5. The library is now installed and ready to use.

## Usage with ESP32
To use the RENERGY library with ESP32, follow these steps:
1. Include the RENERGY library in your sketch:
   ```cpp
   #include <RENERGY.h>
   ```
2. Initialize the library and configure the necessary settings in the `setup()` function:
   ```cpp
   void setup() {
       // Initialize serial communication
       Serial.begin(115200);

       // Initialize RENERGY library
       RENERGY.begin();
   }
   ```
3. Use the library functions in the `loop()` function to manage and monitor your renewable energy system:
   ```cpp
   void loop() {
       // Collect data from sensors
       float voltage = RENERGY.getVoltage();
       float current = RENERGY.getCurrent();

       // Print data to serial monitor
       Serial.print("Voltage: ");
       Serial.print(voltage);
       Serial.print(" V");
       Serial.print("Current: ");
       Serial.print(current);
       Serial.println(" A");

       // Add your custom code to control the energy system
   }
   ```
