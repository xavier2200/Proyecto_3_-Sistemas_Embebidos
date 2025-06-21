// #include <Arduino.h>
// #include <EmonLib.h>
// #include "tasks_power.h"

// // Global objects (or put in a shared struct with mutex if needed)
// EnergyMonitor emonVoltage;
// EnergyMonitor emonCurrent;

// float globalCurrent = 0.0;
// float globalVoltage = 0.0;
// float globalPower = 0.0;

// // Mutex for shared variables (optional but recommended)
// SemaphoreHandle_t powerMutex;

// void taskCurrentSense(void* pvParameters) {
//   emonCurrent.current(34, 111.1);  // A0 or GPIO 34
//   for (;;) {
//     float current = emonCurrent.calcIrms(1480);
//     xSemaphoreTake(powerMutex, portMAX_DELAY);
//     globalCurrent = current;
//     xSemaphoreGive(powerMutex);
//     vTaskDelay(pdMS_TO_TICKS(500));
//   }
// }

// void taskVoltageSense(void* pvParameters) {
//   emonVoltage.voltage(35, 234.26, 1.7);  // Adjust calibration
//   for (;;) {
//     float voltage = emonVoltage.calcVrms(1480);
//     xSemaphoreTake(powerMutex, portMAX_DELAY);
//     globalVoltage = voltage;
//     xSemaphoreGive(powerMutex);
//     vTaskDelay(pdMS_TO_TICKS(500));
//   }
// }

// void taskPowerCalc(void* pvParameters) {
//   for (;;) {
//     xSemaphoreTake(powerMutex, portMAX_DELAY);
//     float current = globalCurrent;
//     float voltage = globalVoltage;
//     xSemaphoreGive(powerMutex);

//     globalPower = voltage * current;

//     Serial.printf("V: %.2f V | I: %.2f A | P: %.2f W\n", voltage, current, globalPower);
//     vTaskDelay(pdMS_TO_TICKS(1000));
//   }
// }

// void createPowerTask() {
//   powerMutex = xSemaphoreCreateMutex();

//   xTaskCreatePinnedToCore(taskCurrentSense, "CurrentSense", 2048, NULL, 1, NULL, 1);
//   xTaskCreatePinnedToCore(taskVoltageSense, "VoltageSense", 2048, NULL, 1, NULL, 1);
//   xTaskCreatePinnedToCore(taskPowerCalc,   "PowerCalc",    2048, NULL, 1, NULL, 1);
// }
