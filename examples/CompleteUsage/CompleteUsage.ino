#include <RENERGY.h>

// Instância da classe RENERGY utilizando HardwareSerial
HardwareSerial& serialPort = Serial1; // Exemplo: Serial1 como porta de comunicação
RENERGY renergy(serialPort);

void setup() {
    // Inicializar comunicação serial para monitoramento
    Serial.begin(115200);

    // Inicializar o módulo RENERGY na porta serial configurada
    if (!renergy.begin(9600, SERIAL_8N1)) {
        Serial.println("Falha ao inicializar o módulo RENERGY!");
        while (1); // Trava o sistema em caso de falha
    }

    // Opcional: Configurar endereço do dispositivo, se necessário
    renergy.setAddress(1);
}

void loop() {
    // Ler dados do módulo RENERGY
    if (renergy.read()) {
        // Obter medições por fase
        float voltageA = renergy.getVoltage(RENERGY_PHASE_A);
        float currentA = renergy.getCurrent(RENERGY_PHASE_A);
        float activePowerA = renergy.getActivePower(RENERGY_PHASE_A);
        float reactivePowerA = renergy.getReactivePower(RENERGY_PHASE_A);
        float apparentPowerA = renergy.getApparentPower(RENERGY_PHASE_A);
        float powerFactorA = renergy.getPowerFactor(RENERGY_PHASE_A);
        float energyA = renergy.getEnergy(RENERGY_PHASE_A);

        // Obter medições totais
        float totalActivePower = renergy.getTotalActivePower();
        float totalReactivePower = renergy.getTotalReactivePower();
        float totalApparentPower = renergy.getTotalApparentPower();
        float totalEnergy = renergy.getTotalEnergy();
        float frequency = renergy.getFrequency();

        // Imprimir dados no monitor serial
        Serial.println("=== Medições por Fase (A) ===");
        Serial.print("Tensão: "); Serial.print(voltageA); Serial.println(" V");
        Serial.print("Corrente: "); Serial.print(currentA); Serial.println(" A");
        Serial.print("Potência Ativa: "); Serial.print(activePowerA); Serial.println(" W");
        Serial.print("Potência Reativa: "); Serial.print(reactivePowerA); Serial.println(" VAR");
        Serial.print("Potência Aparente: "); Serial.print(apparentPowerA); Serial.println(" VA");
        Serial.print("Fator de Potência: "); Serial.print(powerFactorA); Serial.println();
        Serial.print("Energia: "); Serial.print(energyA); Serial.println(" kWh");

        Serial.println("=== Medições Totais ===");
        Serial.print("Potência Ativa Total: "); Serial.print(totalActivePower); Serial.println(" W");
        Serial.print("Potência Reativa Total: "); Serial.print(totalReactivePower); Serial.println(" VAR");
        Serial.print("Potência Aparente Total: "); Serial.print(totalApparentPower); Serial.println(" VA");
        Serial.print("Energia Total: "); Serial.print(totalEnergy); Serial.println(" kWh");
        Serial.print("Frequência: "); Serial.print(frequency); Serial.println(" Hz");
    } else {
        Serial.println("Falha ao ler dados do módulo RENERGY!");
    }

    // Intervalo de atualização
    delay(1000); // Atualiza a cada segundo
}
