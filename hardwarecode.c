#include <LiquidCrystal.h>
#include <DHT.h>

#define DHT_PIN   D3
#define DHT_TYPE  DHT11
#define LDR_PIN   A0
#define GAS_PIN   A1
#define RAIN_A    A2
#define RAIN_D    D2
DHT dht(DHT_PIN, DHT_TYPE);

// STM32 ADC properties (12-bit)
const float ADC_MAX = 4095.0;
const float VREF = 3.3;

// timing
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 2000;

void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.print("Weather Station");
  delay(1500);
  Serial.clear();

  pinMode(RAIN_D, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  pinMode(RAIN_A, INPUT);
}

float readVoltage(int pin) {
  return (analogRead(pin) / ADC_MAX) * VREF;
}

float ldrToPercent(int raw) {
  float percent = (1.0 - (raw / ADC_MAX)) * 100.0;
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  return percent;
}

void loop() {
  if (millis() - lastUpdate < UPDATE_INTERVAL) return;
  lastUpdate = millis();

  // Read DHT11
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  // Read analog sensors
  int ldrRaw = analogRead(LDR_PIN);
  float ldrPercent = ldrToPercent(ldrRaw);

  int rainA = analogRead(RAIN_A);
  float rainVolt = (rainA / ADC_MAX) * VREF;
  int rainD = digitalRead(RAIN_D);

  int gasRaw = analogRead(GAS_PIN);
  float gasVolt = (gasRaw / ADC_MAX) * VREF;

  //Serial monitor
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print("%, ");
  Serial.print("LDR: "); Serial.print(ldrPercent); Serial.print("%, ");
  Serial.print("Rain(V): "); Serial.print(rainVolt, 2); Serial.print(", ");
  Serial.print("Gas(V): "); Serial.println(gasVolt, 2);

  // SERIAL display
  Serial.clear();

  // Line 1: Temp & Humidity
  Serial.print("T:");
  if (!isnan(temp)) {
    Serial.print(temp, 1);
    Serial.print("C ");
  } else Serial.print("Err ");
  Serial.print("H:");
  if (!isnan(hum)) Serial.print(hum, 0);
  else Serial.print("--");
  Serial.print("%");

  // Line 2: LDR & Rain/Gas
  Serial.print("L:");
  Serial.print((int)ldrPercent);
  Serial.print("% ");

  if (rainD == LOW) Serial.print("Dry ");
  else Serial.print("Wet ");

  Serial.print("G:");
  Serial.print(gasVolt, 1);
  Serial.print("V");
}
 
