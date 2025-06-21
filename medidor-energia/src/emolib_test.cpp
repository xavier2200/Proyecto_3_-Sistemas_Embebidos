// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <EmonLib.h>

// // Dirección por defecto del LCD I2C. Cambia si es distinta (0x27 o 0x3F suelen ser comunes)
// LiquidCrystal_I2C lcd(0x27, 16, 2); 

// void setup() {
//   // Configura pines SDA y SCL en el ESP32
//   Wire.begin(22, 23);

//   lcd.init();           // Inicializa el LCD
//   lcd.backlight();      // Enciende la luz de fondo

//   lcd.setCursor(0, 0);  // Coloca el cursor en la columna 0, fila 0
//   lcd.print("Hola Xavier!");

//   lcd.setCursor(0, 1);  // Coloca el cursor en la fila 1
//   lcd.print("LCD I2C listo");
// }

// void loop() {
//   // No hace nada en el loop
// }

// #include "EmonLib.h"             // Include Emon Library
// EnergyMonitor emon1;             // Create an instance

// void setup()
// {  
//   Serial.begin(9600);
  
//   emon1.voltage(36, 85.714, 1.7);  // Voltage: input pin, calibration, phase_shift
//   emon1.current(39, 5.8);       // Current: input pin, calibration.
// }

// void loop()
// {
//   emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//   emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
//   // float realPower       = emon1.realPower;        //extract Real Power into variable
//   // float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
//   // float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
//   float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
//   float Irms            = emon1.Irms;             //extract Irms into Variable
// }