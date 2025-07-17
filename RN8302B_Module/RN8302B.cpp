// RN8302B.cpp - Implementação da biblioteca RN8302B para ESP32

#include "RN8302B.h"

// Construtor: armazena pinos e instancia SPI
RN8302B::RN8302B(uint8_t cs, uint8_t sck, uint8_t miso, uint8_t mosi)
    : _cs(cs), _sck(sck), _miso(miso), _mosi(mosi)
{
    _spi = new SPIClass(VSPI);
}

// Inicialização: configura pinos e SPI
bool RN8302B::begin() {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    _spi->begin(_sck, _miso, _mosi, _cs);
    // Opcional: verificar comunicação lendo ChipID
    return true;
}

// Leitura genérica de registrador de 24 bits
uint32_t RN8302B::readRegister(uint16_t reg) {
    uint32_t value = 0;
    digitalWrite(_cs, LOW);
    _spi->transfer16((reg & 0x7FFF) | 0x8000); // Leitura (bit 15 = 1)
    value  = ((uint32_t)_spi->transfer(0)) << 16;
    value |= ((uint32_t)_spi->transfer(0)) << 8;
    value |= ((uint32_t)_spi->transfer(0));
    digitalWrite(_cs, HIGH);
    return value;
}

// Escrita genérica de registrador de 24 bits
void RN8302B::writeRegister(uint16_t reg, uint32_t value) {
    digitalWrite(_cs, LOW);
    _spi->transfer16(reg & 0x7FFF); // Escrita (bit 15 = 0)
    _spi->transfer((value >> 16) & 0xFF);
    _spi->transfer((value >> 8) & 0xFF);
    _spi->transfer(value & 0xFF);
    digitalWrite(_cs, HIGH);
}

// Funções de leitura das grandezas elétricas (endereços de exemplo!)
float RN8302B::getVoltage(RN8302B_PHASE phase) {
    uint16_t reg = 0x2000 + phase; // Ajuste conforme tabela
    return (float)readRegister(reg) * 0.01; // Fator exemplo
}
float RN8302B::getCurrent(RN8302B_PHASE phase) {
    uint16_t reg = 0x2010 + phase;
    return (float)readRegister(reg) * 0.001;
}
float RN8302B::getActivePower(RN8302B_PHASE phase) {
    uint16_t reg = 0x2020 + phase;
    return (float)readRegister(reg) * 0.01;
}
float RN8302B::getReactivePower(RN8302B_PHASE phase) {
    uint16_t reg = 0x2030 + phase;
    return (float)readRegister(reg) * 0.01;
}
float RN8302B::getApparentPower(RN8302B_PHASE phase) {
    uint16_t reg = 0x2040 + phase;
    return (float)readRegister(reg) * 0.01;
}
float RN8302B::getPowerFactor(RN8302B_PHASE phase) {
    uint16_t reg = 0x2050 + phase;
    return ((float)readRegister(reg)) / 1000.0;
}
float RN8302B::getEnergy(RN8302B_PHASE phase) {
    uint16_t reg = 0x2060 + phase;
    return ((float)readRegister(reg)) * 0.001;
}

// Leituras totais (soma das fases)
float RN8302B::getTotalActivePower() {
    return getActivePower(RN8302B_PHASE_A) + getActivePower(RN8302B_PHASE_B) + getActivePower(RN8302B_PHASE_C);
}
float RN8302B::getTotalReactivePower() {
    return getReactivePower(RN8302B_PHASE_A) + getReactivePower(RN8302B_PHASE_B) + getReactivePower(RN8302B_PHASE_C);
}
float RN8302B::getTotalApparentPower() {
    return getApparentPower(RN8302B_PHASE_A) + getApparentPower(RN8302B_PHASE_B) + getApparentPower(RN8302B_PHASE_C);
}
float RN8302B::getTotalEnergy() {
    return getEnergy(RN8302B_PHASE_A) + getEnergy(RN8302B_PHASE_B) + getEnergy(RN8302B_PHASE_C);
}
float RN8302B::getFrequency() {
    uint16_t reg = 0x2100; // Exemplo
    return ((float)readRegister(reg)) * 0.01;
}

// Leitura dos alarmes e interrupções
uint32_t RN8302B::getAlarmStatus() {
    uint16_t reg = 0x4000; // Exemplo
    return readRegister(reg);
}
uint32_t RN8302B::getInterruptStatus() {
    uint16_t reg = 0x4010; // Exemplo
    return readRegister(reg);
}

// Reset do chip
void RN8302B::reset() {
    writeRegister(0x0000, 0x123456); // Ajuste conforme datasheet
}

// Leitura do ChipID (exemplo)
uint32_t RN8302B::getChipID() {
    uint16_t reg = 0x7000; // Exemplo
    return readRegister(reg);
}