#include <WiFi.h>
#include "WiFiServer6.h"

const char* ssid = "ssid";
const char* password = "pass";

WiFiServer6 server6(80);

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("STA Connected");
            WiFi.enableIpV6();
            delay(0.5);
            WiFi.enableIpV6();
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP6:
            Serial.print("STA IPv6: ");
            Serial.println(WiFi.localIPv6());
            Serial.println(WiFi.globalIPv6());
            break;
        default:
            break;
    }
}

void setup() {
  Serial.begin(115200);

  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");

  server6.begin();
  Serial.println("Server started");
}

void loop() {
 WiFiClient client6 = server6.available();

 if (client6) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client6.connected()) {            // loop while the client's connected
      if (client6.available()) {             // if there's bytes to read from the client,
        char c = client6.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client6.println("HTTP/1.1 200 OK");
            client6.println("Content-type:text/html");
            client6.println();

            // the content of the HTTP response follows the header:
            client6.print("<h1>Hello ESP32 Running on IPv6!</h1>");
            client6.print("<h3>Greetings to new age of internet</h3>");

            // The HTTP response ends with another blank line:
            client6.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client6.stop();
    Serial.println("Client Disconnected.");
  }
}
