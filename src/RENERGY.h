#ifndef RENERGY_H
#define RENERGY_H

#include <Arduino.h>
#include <HardwareSerial.h>

// Define phase constants (opcional, dependendo do suporte a fases no módulo RENERGY)
#define RENERGY_PHASE_A 0
#define RENERGY_PHASE_B 1
#define RENERGY_PHASE_C 2

class RENERGY {
public:
    RENERGY(HardwareSerial& serial);
    bool begin(int baud = 9600, uint8_t config = SERIAL_8N1, int rxPin = -1, int txPin = -1);

    void setAddress(uint8_t address);
    bool read();

    // Métodos para obter medições por fase
    float getVoltage(uint8_t phase = RENERGY_PHASE_A);
    float getCurrent(uint8_t phase = RENERGY_PHASE_A);
    float getActivePower(uint8_t phase = RENERGY_PHASE_A);
    float getReactivePower(uint8_t phase = RENERGY_PHASE_A);
    float getApparentPower(uint8_t phase = RENERGY_PHASE_A);
    float getPowerFactor(uint8_t phase = RENERGY_PHASE_A);
    float getEnergy(uint8_t phase = RENERGY_PHASE_A);

    // Métodos para obter medições totais
    float getTotalActivePower();
    float getTotalReactivePower();
    float getTotalApparentPower();
    float getTotalEnergy();
    float getFrequency();

private:
    HardwareSerial& serial;
    uint8_t address;

    // Armazenamento de dados
    float voltages[3];
    float currents[3];
    float activePowers[3];
    float reactivePowers[3];
    float apparentPowers[3];
    float powerFactors[3];
    float energies[3];

    float totalActivePower;
    float totalReactivePower;
    float totalApparentPower;
    float totalEnergy;
    float frequency;

    // Métodos auxiliares para comunicação
    bool sendCommand(uint8_t* buffer, uint8_t length);
    bool receiveResponse(uint8_t* buffer, uint8_t expectedLength);
    uint16_t calculateCRC(uint8_t* buffer, uint8_t length);
    bool parseResponse(uint8_t* buffer, uint8_t length);
};

#endif // RENERGY_H
