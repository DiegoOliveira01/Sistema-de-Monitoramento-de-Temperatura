#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// Configuração WiFi
const char* ssid = "SEM SINAL";
const char* password = "887091vi";

// Configuração ThingSpeak
unsigned long channelID = 3098401; // coloque aqui seu Channel ID
const char* writeAPIKey = "XKL5MNLM8JVJSUDC";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");

  ThingSpeak.begin(client); // Inicializa ThingSpeak
}

void loop() {
  float temperaturaFixa = 25.5; // valor fixo para teste

  // Envia valor para Field 1
  int resposta = ThingSpeak.writeField(channelID, 1, temperaturaFixa, writeAPIKey);

  if (resposta == 200) {
    Serial.println("Temperatura enviada com sucesso!");
  } else {
    Serial.print("Erro ao enviar. Código HTTP: ");
    Serial.println(resposta);
  }

  delay(20000); // intervalo de 20 segundos (ThingSpeak exige >=15s)
}