#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "SEM SINAL";
const char* password = "887091vi";
unsigned long channelID = 3098401;
const char* writeAPIKey = "BKEGMQX8PTOLAWO7";

WiFiClient client;
unsigned long lastSendTime = 0;
const unsigned long SEND_INTERVAL = 20000; // 20 segundos

void setup() {
  Serial.begin(115200);
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
  if (Serial.available() > 0) {
    String leitura = Serial.readStringUntil('\n');
    leitura.trim();

    if (leitura.length() > 0) {
      float temperatura = leitura.toFloat();
      
      // VALIDAÇÃO CRÍTICA - Verificar se está dentro de range razoável
      if (temperatura >= -10.0 && temperatura <= 60.0) {
        
        Serial.print("Temperatura válida: ");
        Serial.println(temperatura);

        // Verificar intervalo mínimo do ThingSpeak
        if (millis() - lastSendTime >= SEND_INTERVAL) {
          int resposta = ThingSpeak.writeField(channelID, 5, temperatura, writeAPIKey);

          if (resposta == 200) {
            Serial.println("Temperatura enviada com sucesso!");
            lastSendTime = millis();
          } else {
            Serial.print("Erro ao enviar. Código HTTP: ");
            Serial.println(resposta);
          }
        } else {
          Serial.println("Aguardando intervalo do ThingSpeak...");
        }
      } else {
        Serial.print("Temperatura inválida ignorada: ");
        Serial.println(temperatura);
      }
    }
  }
}