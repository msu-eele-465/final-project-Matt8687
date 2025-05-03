/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>
#include "web_server.h"
#include "led_array_control.h"

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;

void web_server_setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…\n");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  // IPAddress local_IP(192, 168, 1, 184);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void web_server_loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /1") >= 0) {
              Serial.println("mode 1");
              LAC_update_mode(0);
            } else if (header.indexOf("GET /2") >= 0) {
              Serial.println("mode 2");
              LAC_update_mode(1);
            } else if (header.indexOf("GET /3") >= 0) {
              Serial.println("mode 2");
              LAC_update_mode(2);
            } else if (header.indexOf("GET /string_submit") >= 0){
              Serial.println("Working!");
              String message = "";
              for(int i = 27; i<1000; i++){
                if(header[i+1] == 'H' && header[i+2] == 'T' && header[i+3] == 'T')
                  break;
                Serial.print(header[i]);
                message+=header[i];
              }
              Serial.println("\nMessage: " + message);
              LAC_update_string(message, sizeof(message));
            }
            
            // Display the HTML web page
            client.println(
            "<!DOCTYPE html><html>\n"
            "<head>\n"
            "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            "  <link rel=\"icon\" href=\"data:,\">\n"
            "  <style>\n"
            "    html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"
            "    .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;\n"
            "    text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n"
            "  </style>\n"
            "</head>");
            
            // Web Page Heading
            client.println(
            "<body>\n"
            "  <h1>ESP32 Web Server</h1>\n");

            client.println("<p><a href=\"/1\"><button class=\"button\">Off</button></a></p>");
            client.println("<p><a href=\"/2\"><button class=\"button\">Scroll Text</button></a></p>");
            client.println("<p><a href=\"/3\"><button class=\"button\">Time/Temp</button></a></p>");

            client.println(
              "<form action='/string_submit'>"
              "  <label for='string'> Message Input: </label><br>"
              "  <input type='text' id='message' name='message'><br>"
              "  <input type='submit' id='submit'>"
              "</form>");

            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}