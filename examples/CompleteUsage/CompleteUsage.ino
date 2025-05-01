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
    float apparentPower = renergy.getApparentPower();
    float realPower = renergy.getRealPower();
    float powerFactor = renergy.getPowerFactor();
    float frequency = renergy.getFrequency();

    // Print data to serial monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(" V");
    Serial.print("Current: ");
    Serial.print(current);
    Serial.print(" A");
    Serial.print("Apparent Power: ");
    Serial.print(apparentPower);
    Serial.print(" VA");
    Serial.print("Real Power: ");
    Serial.print(realPower);
    Serial.print(" W");
    Serial.print("Power Factor: ");
    Serial.print(powerFactor);
    Serial.print(" ");
    Serial.print("Frequency: ");
    Serial.print(frequency);
    Serial.println(" Hz");

    // Add your custom code to control the energy system
}
