// ===== Código do Arduino (ATmega328 integrado com ESP8266) =====
const int sensorPin = A2; // Pino onde o NTC está ligado

const float SERIES_RESISTOR = 10000.0;       // resistor fixo 10k
const float NOMINAL_RESISTANCE = 10000.0;    // resistência do NTC a 25°C
const float NOMINAL_TEMPERATURE = 25.0;      // temperatura nominal
const float BETA_COEFFICIENT = 3950.0;       // constante Beta do NTC (MF58)

void setup() {
  Serial.begin(9600); // Comunicação serial (com o ESP8266 e com o PC)
  delay(2000);        // pequena pausa para estabilizar
}

void loop() {
  int adcValue = analogRead(sensorPin);
  float voltage = adcValue / 1023.0 * 5.0;
  float resistance = SERIES_RESISTOR * (5.0 / voltage - 1.0);

  // Cálculo da temperatura (Steinhart–Hart)
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= BETA_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  float temperatureC = steinhart - 273.15;

  // Envia temperatura via serial (ESP8266 pode ler isso diretamente)
  Serial.println(temperatureC);

  delay(5000); // aguarda 5 segundos antes da próxima leitura
}
