#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin definitions
#define oneWireBus D2
#define mosfetPin D1

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// OneWire instance
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// Web server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(mosfetPin, OUTPUT);
  
  // Start the DS18B20 sensor
  sensors.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check for clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        currentLine += c;

        // Check for end of client request
        if (c == '\n') {
          // Function to handle GET requests
          if (currentLine.length() == 0) {
            sensors.requestTemperatures(); // Get temperature
            float temperature = sensors.getTempCByIndex(0);
            // Control PWM based on temperature
            int pwmValue = map(temperature, 20, 30, 0, 255);
            pwmValue = constrain(pwmValue, 0, 255);
            analogWrite(mosfetPin, pwmValue);

            // Send response to client
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
            client.print("Temperature: ");
            client.print(temperature);
            client.println(" °C");
            client.print("Fan speed (PWM): ");
            client.print(pwmValue);
            client.println("<br><a href='/'>Refresh</a>");
            break;
          } else {
            currentLine = ""; // Clear the current line
          }
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}