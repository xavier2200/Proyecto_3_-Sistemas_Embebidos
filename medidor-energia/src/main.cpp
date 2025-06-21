#include <EmonLib.h>     // Include EmonLib
#include <Arduino.h>

EnergyMonitor emon1;



void powerMonitorTask(void *pvParameters);

void powerMonitorTask(void *pvParameters){
  // Setup emon1 inside task
  emon1.voltage(36, 85.714, 1.7);  // Voltage: pin, calibration, phase_shift
  emon1.current(39, 5.8);          // Current: pin, calibration

  for(;;) {
    emon1.calcVI(20, 2000);        // Perform measurement
   // emon1.serialprint();           // Optional debug output

    // Example of extracting values
    float supplyVoltage = emon1.Vrms;
    float Irms = emon1.Irms;
    float realPower = emon1.realPower;
    float apparentPower = emon1.apparentPower;
    float powerFactor = emon1.powerFactor;

    // Print values or send to another task/queue
    Serial.printf("Vrms: %.2f V | Irms: %.2f A | P: %.2f W | S: %.2f VA | PF: %.2f\n",
                  supplyVoltage, Irms, realPower, apparentPower, powerFactor);

    vTaskDelay(pdMS_TO_TICKS(1000));  // Wait 1 second
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);  // Give time for Serial to start

  // Create the FreeRTOS task
  xTaskCreate(
    powerMonitorTask,      // Function to run
    "PowerMonitorTask",    // Name of task
    8192,                  // Stack size
    NULL,                  // Task input
    1,                     // Priority                   
    NULL// Run on core 1
  );
}

void loop() {
  // Nothing here; everything is handled in the task
}
