const int sensorPin = A2;
const float SERIES_RESISTOR = 10000.0;
const float NOMINAL_RESISTANCE = 10000.0;
const float NOMINAL_TEMPERATURE = 25.0;
const float BETA_COEFFICIENT = 3950.0;

// Adicionar filtro de média
const int NUM_READINGS = 10;
float readings[NUM_READINGS];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  // Inicializar array de leituras
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Fazer múltiplas leituras e calcular média
  total = total - readings[readIndex];
  
  int adcValue = analogRead(sensorPin);
  float voltage = adcValue / 1023.0 * 5.0;
  float resistance = SERIES_RESISTOR * (5.0 / voltage - 1.0);

  // Cálculo da temperatura
  float steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= BETA_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  float temperatureC = steinhart - 273.15;

  // Atualizar filtro de média
  readings[readIndex] = temperatureC;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % NUM_READINGS;
  
  average = total / NUM_READINGS;

  // Enviar apenas a temperatura filtrada
  Serial.println(average, 2); // 2 casas decimais

  delay(2000); // Reduzir delay entre leituras
}