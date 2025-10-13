const int pinNTC = A2;     // pino (A2)
const float R_FIXED = 10000.0; // resistor fixo 10k
const float BETA = 3950.0;     // valor típico MF58
const float R0 = 10000.0;      // resistência do NTC a 25°C
const float T0 = 25.0 + 273.15; // 25°C em Kelvin

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(pinNTC);
  float Vout = raw * 5.0 / 1023.0;
  // proteção contra divisão por zero
  if (Vout <= 0.0001) Vout = 0.0001;
  float Rntc = R_FIXED * (5.0 / Vout - 1.0);
  // fórmula Beta
  float tempK = 1.0 / (1.0/T0 + (1.0/BETA) * log(Rntc / R0));
  float tempC = tempK - 273.15;

  Serial.print("raw=");
  Serial.print(raw);
  Serial.print("  Rntc=");
  Serial.print(Rntc, 1);
  Serial.print(" ohm  T=");
  Serial.print(tempC, 2);
  Serial.println(" C");
  delay(1000);
}