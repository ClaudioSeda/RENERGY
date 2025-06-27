// RN8302B.cpp - Implementação da biblioteca RN8302B para ESP32

#include "RN8302B.h"

// Endereços de registradores (ajuste conforme seu datasheet!)
#define BANK_MEAS   0x00
#define REG_UA      0x00
#define REG_UB      0x01
#define REG_UC      0x02
#define REG_IA      0x03
#define REG_IB      0x04
#define REG_IC      0x05
#define REG_PA      0x06
#define REG_PB      0x07
#define REG_PC      0x08
#define REG_QA      0x09
#define REG_QB      0x0A
#define REG_QC      0x0B
#define REG_SA      0x0C
#define REG_SB      0x0D
#define REG_SC      0x0E
#define REG_PFA     0x0F
#define REG_PFB     0x10
#define REG_PFC     0x11
#define REG_EA      0x12
#define REG_EB      0x13
#define REG_EC      0x14
#define REG_SUM_PA  0x15
#define REG_SUM_QA  0x16
#define REG_SUM_SA  0x17
#define REG_SUM_EA  0x18
#define REG_FREQ    0x19

#define BANK_ALARM  0x01
#define REG_ALARM_STATUS 0x00
#define REG_INT_STATUS   0x01
#define REG_INT_ENABLE   0x02
#define REG_INT_CLEAR    0x03

// Fatores de calibração (ajuste conforme seu hardware!)
#define CAL_V   0.1      // Exemplo: cada unidade = 0.1 V
#define CAL_I   0.001    // Exemplo: cada unidade = 1 mA
#define CAL_P   0.1      // Exemplo: cada unidade = 0.1 W
#define CAL_Q   0.1      // Exemplo: cada unidade = 0.1 VAR
#define CAL_S   0.1      // Exemplo: cada unidade = 0.1 VA
#define CAL_E   0.001    // Exemplo: cada unidade = 1 Wh
#define CAL_F   0.01     // Exemplo: cada unidade = 0.01 Hz

// Construtor: define pinos e configura SPI
RN8302B::RN8302B(uint8_t csPin, uint8_t sckPin, uint8_t misoPin, uint8_t mosiPin)
  : _cs(csPin), _sck(sckPin), _miso(misoPin), _mosi(mosiPin), _spiSettings(1000000, MSBFIRST, SPI_MODE3) {}

// Inicialização do CI e do barramento SPI
void RN8302B::begin() {
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);
  SPI.begin(_sck, _miso, _mosi, _cs);
  delay(200);
}

// Leitura de tensão por fase
float RN8302B::getVoltage(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_UA :
                (phase == RN8302B_PHASE_B) ? REG_UB : REG_UC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_V;
}

// Leitura de corrente por fase
float RN8302B::getCurrent(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_IA :
                (phase == RN8302B_PHASE_B) ? REG_IB : REG_IC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_I;
}

// Leitura de potência ativa por fase
float RN8302B::getActivePower(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_PA :
                (phase == RN8302B_PHASE_B) ? REG_PB : REG_PC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_P;
}

// Leitura de potência reativa por fase
float RN8302B::getReactivePower(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_QA :
                (phase == RN8302B_PHASE_B) ? REG_QB : REG_QC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_Q;
}

// Leitura de potência aparente por fase
float RN8302B::getApparentPower(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_SA :
                (phase == RN8302B_PHASE_B) ? REG_SB : REG_SC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_S;
}

// Leitura de fator de potência por fase
float RN8302B::getPowerFactor(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_PFA :
                (phase == RN8302B_PHASE_B) ? REG_PFB : REG_PFC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) / 1000.0;
}

// Leitura de energia acumulada por fase
float RN8302B::getEnergy(RN8302B_PHASE phase) {
  uint8_t reg = (phase == RN8302B_PHASE_A) ? REG_EA :
                (phase == RN8302B_PHASE_B) ? REG_EB : REG_EC;
  return convert24ToSigned(readRegister24(BANK_MEAS, reg)) * CAL_E;
}

// Leituras totais
float RN8302B::getTotalActivePower()   { return convert24ToSigned(readRegister24(BANK_MEAS, REG_SUM_PA)) * CAL_P; }
float RN8302B::getTotalReactivePower() { return convert24ToSigned(readRegister24(BANK_MEAS, REG_SUM_QA)) * CAL_Q; }
float RN8302B::getTotalApparentPower() { return convert24ToSigned(readRegister24(BANK_MEAS, REG_SUM_SA)) * CAL_S; }
float RN8302B::getTotalEnergy()        { return convert24ToSigned(readRegister24(BANK_MEAS, REG_SUM_EA)) * CAL_E; }
float RN8302B::getFrequency()          { return convert24ToSigned(readRegister24(BANK_MEAS, REG_FREQ)) * CAL_F; }

// Alarmes e interrupções
uint32_t RN8302B::getAlarmStatus()    { return readRegister24(BANK_ALARM, REG_ALARM_STATUS); }
uint32_t RN8302B::getInterruptStatus(){ return readRegister24(BANK_ALARM, REG_INT_STATUS); }
void RN8302B::enableInterrupt(uint32_t mask) {
  uint32_t val = readRegister24(BANK_ALARM, REG_INT_ENABLE);
  writeRegister24(BANK_ALARM, REG_INT_ENABLE, val | mask);
}
void RN8302B::disableInterrupt(uint32_t mask) {
  uint32_t val = readRegister24(BANK_ALARM, REG_INT_ENABLE);
  writeRegister24(BANK_ALARM, REG_INT_ENABLE, val & ~mask);
}
void RN8302B::clearInterrupt(uint32_t mask) {
  writeRegister24(BANK_ALARM, REG_INT_CLEAR, mask);
}

// Leitura de registrador 24 bits
uint32_t RN8302B::readRegister24(uint8_t bank, uint8_t reg) {
  digitalWrite(_cs, LOW);
  SPI.beginTransaction(_spiSettings);
  SPI.transfer(bank);
  SPI.transfer(reg & 0x7F); // MSB=0 para leitura
  uint8_t b2 = SPI.transfer(0x00);
  uint8_t b1 = SPI.transfer(0x00);
  uint8_t b0 = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
  delayMicroseconds(100);
  return ((uint32_t)b2 << 16) | ((uint32_t)b1 << 8) | b0;
}

// Escrita de registrador 24 bits
void RN8302B::writeRegister24(uint8_t bank, uint8_t reg, uint32_t value) {
  digitalWrite(_cs, LOW);
  SPI.beginTransaction(_spiSettings);
  SPI.transfer(bank);
  SPI.transfer(reg | 0x80); // MSB=1 para escrita
  SPI.transfer((value >> 16) & 0xFF);
  SPI.transfer((value >> 8) & 0xFF);
  SPI.transfer(value & 0xFF);
  SPI.endTransaction();
  digitalWrite(_cs, HIGH);
  delayMicroseconds(100);
}

// Conversão de 24 bits unsigned para signed
int32_t RN8302B::convert24ToSigned(uint32_t val) {
  if (val & 0x800000)
    return (int32_t)(val | 0xFF000000);
  else
    return (int32_t)val;
}