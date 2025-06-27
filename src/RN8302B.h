// RN8302B.h - Cabeçalho da biblioteca para RN8302B no ESP32

#ifndef RN8302B_H
#define RN8302B_H

#include <Arduino.h>
#include <SPI.h>

// Enum para identificar fases
enum RN8302B_PHASE {
  RN8302B_PHASE_A = 0,
  RN8302B_PHASE_B,
  RN8302B_PHASE_C
};

class RN8302B {
  public:
    // Construtor: define pinos CS, SCK, MISO, MOSI
    RN8302B(uint8_t csPin, uint8_t sckPin = 18, uint8_t misoPin = 19, uint8_t mosiPin = 23);

    // Inicializa SPI e CI
    void begin();

    // Leituras por fase
    float getVoltage(RN8302B_PHASE phase);
    float getCurrent(RN8302B_PHASE phase);
    float getActivePower(RN8302B_PHASE phase);
    float getReactivePower(RN8302B_PHASE phase);
    float getApparentPower(RN8302B_PHASE phase);
    float getPowerFactor(RN8302B_PHASE phase);
    float getEnergy(RN8302B_PHASE phase);

    // Leituras totais
    float getTotalActivePower();
    float getTotalReactivePower();
    float getTotalApparentPower();
    float getTotalEnergy();
    float getFrequency();

    // Alarmes e interrupções
    uint32_t getAlarmStatus();
    uint32_t getInterruptStatus();
    void enableInterrupt(uint32_t mask);
    void disableInterrupt(uint32_t mask);
    void clearInterrupt(uint32_t mask);

    // Acesso a registradores (expansível)
    uint32_t readRegister24(uint8_t bank, uint8_t reg);
    void writeRegister24(uint8_t bank, uint8_t reg, uint32_t value);

  private:
    int32_t convert24ToSigned(uint32_t val);
    uint8_t _cs, _sck, _miso, _mosi;
    SPISettings _spiSettings;
};

#endif