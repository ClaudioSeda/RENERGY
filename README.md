# RENERGY

## Description

RENERGY is a library for managing and monitoring renewable energy systems. It provides functionalities to interface with various sensors and devices to collect data and control energy systems.

## Installation

To install the RENERGY library in the Arduino IDE, follow these steps:

1. Download the RENERGY library from the [GitHub repository](https://github.com/ClaudioSeda/RENERGY).
2. Open the Arduino IDE.
3. Go to `Sketch` -> `Include Library` -> `Add .ZIP Library...`.
4. Select the downloaded RENERGY library ZIP file.
5. The library is now installed and ready to use.

## Usage with ESP32

To use the RENERGY library with ESP32, follow these steps:

1. Connect the sensors and devices to the appropriate pins on the ESP32 board.
2. Include the RENERGY library in your sketch:
    ```cpp
    #include <RENERGY.h>
    ```
3. Create an instance of the RENERGY class:
    ```cpp
    RENERGY renergy;
    ```
4. Initialize the RENERGY library in the `setup` function:
    ```cpp
    void setup() {
        Serial.begin(115200);
        renergy.begin();
    }
    ```
5. Use the library functions to collect data and control the energy system in the `loop` function:
    ```cpp
    void loop() {
        float voltage = renergy.getVoltage();
        float current = renergy.getCurrent();

        Serial.print("Voltage: ");
        Serial.print(voltage);
        Serial.print(" V");
        Serial.print("Current: ");
        Serial.print(current);
        Serial.println(" A");

        // Add your custom code to control the energy system
    }
    ```

For more detailed examples, refer to the `examples` folder in the repository.
