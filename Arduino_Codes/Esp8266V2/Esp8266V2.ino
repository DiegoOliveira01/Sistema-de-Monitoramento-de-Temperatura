// ===== Código do ESP8266 =====
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// --- Configuração WiFi ---
const char* ssid = "SEM SINAL";
const char* password = "887091vi";

// --- Configuração ThingSpeak ---
unsigned long channelID = 3098401;
const char* writeAPIKey = "XKL5MNLM8JVJSUDC";

WiFiClient client;

void setup() {
  Serial.begin(9600); // mesma taxa do Arduino
  WiFi.begin(ssid, password);

  Serial.println("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  
  ThingSpeak.begin(client);
}

void loop() {
  while(Serial.available()) Serial.read(); // limpa buffer

  if (Serial.available() > 0) {
    String leitura = Serial.readStringUntil('\n');
    leitura.trim();

    if (leitura.length() > 0) {
      float temperatura = leitura.toFloat();


      Serial.print("Enviando temperatura: ");
      Serial.println(temperatura);

      int resposta = ThingSpeak.writeField(channelID, 1, temperatura, writeAPIKey);

      if (resposta == 200) {
        Serial.println("Temperatura enviada com sucesso!");
      } else {
        Serial.print("Erro ao enviar. Código HTTP: ");
        Serial.println(resposta);
      }

      delay(20000); // ThingSpeak requer intervalo mínimo de 15 s
    }
  }
}
