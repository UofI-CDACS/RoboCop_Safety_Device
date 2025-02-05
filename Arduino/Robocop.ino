#include <rgb_lcd.h>
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>

#define TRIG_PIN D6 // Ultrasonic Sensor TRIG pin
#define ECHO_PIN D7 // Ultrasonic Sensor ECHO pin

// Replace with your network credentials
const char* ssid = "AirVandalRobot";
const char* password = "xxxx";

rgb_lcd lcd;

// Static IP configuration
// Change to your network configuration
IPAddress local_IP(129,101,98,2); // Desired static IP
IPAddress gateway(129,101,98,198);    // Router's IP
IPAddress subnet(255,255,255,0);   // Subnet mask
IPAddress primaryDNS(8,8,8,8);     // Optional: Primary DNS
IPAddress secondaryDNS(8,8,4,4);   // Optional: Secondary DNS

String ip_add = "129.101.98.2";
String dist_st = "cm";

float duration_us, distance_cm;

// Modbus configuration
ModbusIP mb;  // Create ModbusIP instance
const int REGISTER_ADDRESS = 5;  // Modbus register to store distanceng to WiFi...

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Configure pins for the ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0); // Set LCD background to green
  // lcd.print(" Countdown Timer ");
  lcd.setCursor(0, 0);
  lcd.print("ROBOTICS");
  lcd.setCursor(8, 2);
  lcd.print("PROJECT");
  delay(2000);
  lcd.clear();

  // Configure static IP
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Failed to configure static IP");
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("Static IP Address: ");
  Serial.println(WiFi.localIP());

  // Modbus setup
  mb.server();  // Start Modbus server
  mb.addHreg(REGISTER_ADDRESS);  // Add a holding register
}

void loop() {
  // Produce a 10-microsecond pulse to the TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration from the ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm
  distance_cm = 0.017 * duration_us;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Update Modbus register with the distance
  int scaled_distance = (int)(distance_cm * 100);  // Scale to avoid float
  mb.Hreg(REGISTER_ADDRESS, scaled_distance);      // Update register value
  Serial.print("Updated Modbus register ");
  Serial.print(REGISTER_ADDRESS);
  Serial.print(" with value: ");
  Serial.println(scaled_distance);

  lcd.setCursor(0, 0);
  lcd.print(ip_add);
  delay(500);
  lcd.setCursor(0, 2);
  lcd.print(distance_cm);
  lcd.setCursor(6, 2);
  lcd.print(dist_st);

  // Process Modbus requests
  mb.task();  // Process Modbus requests

  delay(500);  // Wait 500 ms before persistence
}

