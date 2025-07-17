// Exemplo de uso completo da biblioteca RN8302B para ESP32
// Ajuste os pinos de acordo com seu hardware!

#include <RN8302B.h>

// Instancia a biblioteca nos pinos desejados (CS, SCK, MISO, MOSI)
RN8302B rn8302b(5, 18, 19, 23); // Exemplo: CS=5, SCK=18, MISO=19, MOSI=23

void setup() {
  // Inicializa serial e RN8302B
  Serial.begin(115200);
  rn8302b.begin();
}

void loop() {
  // Leitura das grandezas das três fases
  for (int f = RN8302B_PHASE_A; f <= RN8302B_PHASE_C; f++) {
    Serial.print("Fase ");
    Serial.println((char)('A' + f));
    Serial.print("Tensão (V): "); Serial.println(rn8302b.getVoltage((RN8302B_PHASE)f), 2);
    Serial.print("Corrente (A): "); Serial.println(rn8302b.getCurrent((RN8302B_PHASE)f), 3);
    Serial.print("P. Ativa (W): "); Serial.println(rn8302b.getActivePower((RN8302B_PHASE)f), 2);
    Serial.print("P. Reativa (VAR): "); Serial.println(rn8302b.getReactivePower((RN8302B_PHASE)f), 2);
    Serial.print("P. Aparente (VA): "); Serial.println(rn8302b.getApparentPower((RN8302B_PHASE)f), 2);
    Serial.print("Fator Potência: "); Serial.println(rn8302b.getPowerFactor((RN8302B_PHASE)f), 3);
    Serial.print("Energia (Wh): "); Serial.println(rn8302b.getEnergy((RN8302B_PHASE)f), 3);
    Serial.println();
  }

  Serial.print("Potência Total (W): "); Serial.println(rn8302b.getTotalActivePower(), 2);
  Serial.print("Potência Total Reativa (VAR): "); Serial.println(rn8302b.getTotalReactivePower(), 2);
  Serial.print("Potência Total Aparente (VA): "); Serial.println(rn8302b.getTotalApparentPower(), 2);
  Serial.print("Energia Total (Wh): "); Serial.println(rn8302b.getTotalEnergy(), 3);
  Serial.print("Frequência (Hz): "); Serial.println(rn8302b.getFrequency(), 2);

  Serial.print("Alarmes (HEX): 0x"); Serial.println(rn8302b.getAlarmStatus(), HEX);
  Serial.print("Interrupções (HEX): 0x"); Serial.println(rn8302b.getInterruptStatus(), HEX);

  Serial.println("-----");
  delay(1000);
}