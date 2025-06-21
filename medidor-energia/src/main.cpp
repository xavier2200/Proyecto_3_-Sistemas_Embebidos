#include <Arduino.h>
#include <EmonLib.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>

// --- INSTANCIAS ---
EnergyMonitor emon1;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Cambia si tu LCD tiene otra dirección

// --- PINES ---
const int DangerLed = 15;
const int WarningLed = 2;   // Cambié a GPIO 2 para evitar problemas con GPIO 0
const int GoodLed = 16;
const int RelayPin = 18;

// --- VARIABLES COMPARTIDAS ---
float realPower = 0;

// --- MUTEX ---
SemaphoreHandle_t powerMutex;

// --- WIFI y MQTT ---
const char* ssid = "pop-os-minitaller";
const char* password = "2356636656";
const char* mqtt_server = "192.168.1.19";

WiFiClient espClient;
PubSubClient client(espClient);

// ---------- FUNCIONES WIFI Y MQTT ----------
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("esp32powermonitor", "esp32powermonitor", "123456")) {
      Serial.println("conectado");
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void mqttPublishPower(float power, float apparent, float pf, float voltage) {
  char msg[100];
  snprintf(msg, sizeof(msg),
           "{\"realPower\":%.2f,\"apparentPower\":%.2f,\"powerFactor\":%.2f,\"voltage\":%.2f}",
           power, apparent, pf, voltage);
  client.publish("home/energy/power", msg);
}

// ---------- TAREA DE MONITOREO ----------
void powerMonitorTask(void *pvParameters) {
  emon1.voltage(36, 85.714, 1.7);
  emon1.current(39, 5.8);

  for (;;) {
    emon1.calcVI(20, 2000);

    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      realPower = emon1.realPower;
      xSemaphoreGive(powerMutex);
    }

    Serial.printf("P: %.2f W | S: %.2f VA | PF: %.2f | V: %.2f V\n",
                  emon1.realPower, emon1.apparentPower,
                  emon1.powerFactor, emon1.Vrms);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// ---------- TAREA LED BUENO ----------
void statusGoodTask(void *pvParameters) {
  for (;;) {
    float power = 0;
    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power = realPower;
      xSemaphoreGive(powerMutex);
    }

    digitalWrite(GoodLed, power < 80 ? HIGH : LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// ---------- TAREA LED ADVERTENCIA ----------
void statusWarningTask(void *pvParameters) {
  for (;;) {
    float power = 0;
    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power = realPower;
      xSemaphoreGive(powerMutex);
    }

    digitalWrite(WarningLed, (power >= 80 && power <= 120) ? HIGH : LOW);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// ---------- TAREA LED PELIGRO ----------
void statusDangerTask(void *pvParameters) {
  for (;;) {
    float power = 0;
    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power = realPower;
      xSemaphoreGive(powerMutex);
    }

    if (power > 120) {
      digitalWrite(DangerLed, HIGH);
      vTaskDelay(pdMS_TO_TICKS(250));
      digitalWrite(DangerLed, LOW);
      vTaskDelay(pdMS_TO_TICKS(250));
    } else {
      digitalWrite(DangerLed, LOW);
      vTaskDelay(pdMS_TO_TICKS(500));
    }
  }
}

// ---------- TAREA RELÉ ----------
void relayControlTask(void *pvParameters) {
  for (;;) {
    float power = 0;
    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power = realPower;
      xSemaphoreGive(powerMutex);
    }

    if (power > 120) {
      digitalWrite(RelayPin, LOW);   // Desconectar
    } else {
      digitalWrite(RelayPin, HIGH);  // Conectar
    }

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// ---------- TAREA LCD ----------
void lcdDisplayTask(void *pvParameters) {
  lcd.init();
  lcd.backlight();

  for (;;) {
    float power = 0, apparent = 0, pf = 0, voltage = 0;

    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power    = emon1.realPower;
      apparent = emon1.apparentPower;
      pf       = emon1.powerFactor;
      voltage  = emon1.Vrms;
      xSemaphoreGive(powerMutex);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("P:");
    lcd.print(power, 0);
    lcd.print("W PF:");
    lcd.print(pf, 1);

    lcd.setCursor(0, 1);
    lcd.print("Vrms:");
    lcd.print(voltage, 0);
    lcd.print(" S:");
    lcd.print(apparent, 0);

    vTaskDelay(pdMS_TO_TICKS(2000));  // Actualiza cada 2 segundos
  }
}

// ---------- TAREA MQTT ----------
void mqttTask(void *pvParameters) {
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  for (;;) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    // Leer valores protegidos
    float power = 0, apparent = 0, pf = 0, voltage = 0;
    if (xSemaphoreTake(powerMutex, pdMS_TO_TICKS(100))) {
      power    = emon1.realPower;
      apparent = emon1.apparentPower;
      pf       = emon1.powerFactor;
      voltage  = emon1.Vrms;
      xSemaphoreGive(powerMutex);
    }

    mqttPublishPower(power, apparent, pf, voltage);

    vTaskDelay(pdMS_TO_TICKS(5000));  // Publica cada 5 segundos
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(GoodLed, OUTPUT);
  pinMode(WarningLed, OUTPUT);
  pinMode(DangerLed, OUTPUT);
  pinMode(RelayPin, OUTPUT);

  digitalWrite(RelayPin, HIGH);  // Relay ON

  powerMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(powerMonitorTask, "PowerMonitor", 8192, NULL, 2, NULL, 0);
  xTaskCreate(statusGoodTask, "GoodLED", 1024, NULL, 1, NULL);
  xTaskCreate(statusWarningTask, "WarningLED", 1024, NULL, 1, NULL);
  xTaskCreate(statusDangerTask, "DangerLED", 1024, NULL, 1, NULL);
  xTaskCreate(relayControlTask, "RelayControl", 1024, NULL, 1, NULL);
  xTaskCreate(lcdDisplayTask, "LCDDisplay", 2048, NULL, 1, NULL);
  xTaskCreate(mqttTask, "MQTTTask", 4096, NULL, 1, NULL);
}

void loop() {
  // Nada aquí
}
