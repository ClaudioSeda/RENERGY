#include <RENERGY.h>

// Create an instance of the RENERGY class
RENERGY renergy;

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize RENERGY library
    renergy.begin();
}

void loop() {
    // Collect data from sensors
    float voltage = renergy.getVoltage();
    float current = renergy.getCurrent();
    float realPower = renergy.getRealPower();
    float apparentPower = renergy.getApparentPower();
    float energyKwh = renergy.getEnergyKwh();
    float powerFactor = renergy.getPowerFactor();
    float frequency = renergy.getFrequency();

    // Print data to serial monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V");
    Serial.print("Current: ");
    Serial.print(current);
    Serial.print(" A");
    Serial.print("Real Power: ");
    Serial.print(realPower);
    Serial.print(" W");
    Serial.print("Apparent Power: ");
    Serial.print(apparentPower);
    Serial.print(" VA");
    Serial.print("Energy: ");
    Serial.print(energyKwh);
    Serial.print(" kWh");
    Serial.print("Power Factor: ");
    Serial.print(powerFactor);
    Serial.print(" ");
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Check for voltage alarm
    if (voltage > 14.0) {
        Serial.println("Voltage alarm: High voltage detected!");
    } else if (voltage < 10.0) {
        Serial.println("Voltage alarm: Low voltage detected!");
    }

    // Check for current alarm
    if (current > 10.0) {
        Serial.println("Current alarm: High current detected!");
    } else if (current < 1.0) {
        Serial.println("Current alarm: Low current detected!");
    }

    // Add your custom code to control the energy system
}
