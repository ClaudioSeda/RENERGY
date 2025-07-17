// RN8302B.h - Biblioteca para RN8302B em ESP32 (Arduino IDE)
// Desenvolvido com base em exemplos e datasheet RN8302B
// Endereços e fatores de escala são exemplos, ajuste conforme sua tabela!

#pragma once
#include <Arduino.h>
#include <SPI.h>

// Enum para identificar as fases
typedef enum {
    RN8302B_PHASE_A = 0,
    RN8302B_PHASE_B = 1,
    RN8302B_PHASE_C = 2
} RN8302B_PHASE;

// Classe principal do driver RN8302B
class RN8302B {
public:
    // Construtor: define os pinos do SPI (CS, SCK, MISO, MOSI)
    RN8302B(uint8_t csPin, uint8_t sckPin, uint8_t misoPin, uint8_t mosiPin);

    // Inicialização do barramento e do chip
    bool begin();

    // Leituras principais por fase
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

    // Acesso genérico a registradores
    uint32_t readRegister(uint16_t reg);
    void writeRegister(uint16_t reg, uint32_t value);

    // Utilidades
    void reset();
    uint32_t getChipID();

private:
    uint8_t _cs, _sck, _miso, _mosi;
    SPIClass *_spi;

    // Auxiliares para comunicação SPI
    void spiWrite(uint16_t reg, uint32_t value);
    uint32_t spiRead(uint16_t reg);
};