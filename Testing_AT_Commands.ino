#include <SoftwareSerial.h>
SoftwareSerial SIM800L(0, 1); // (RX,TX)

// String to store readable serial
String buff;

void setup() {
  // Initialize Serial Communication with Arduino IDE
  Serial.begin(9600);

  // Initialize communication of SIM800L with Arduino
  SIM800L.begin(9600);

  // Enable user to print AT commands
  Serial.println("Print AT commands........");

}

void loop() {
  while (Serial.available()) {
    buff = Serial.readString();
    SIM800L.println(buff);
  }

  while (SIM800L.available()) {
    buff = SIM800L.readString();
    Serial.println(buff);
  }
  Serial.print("");
}
