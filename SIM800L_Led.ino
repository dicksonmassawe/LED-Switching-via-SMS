/* This programme switch on and off five led in the interval of two seconds from each
other via SIM800L */

#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3);  // (RX,TX)

// String to store incoming strings
String buff;

// Led Declaration
int led[6] = { 6, 8, 10, 11, 12, 13 };  // red, blue, yellow, green, white, pink


void setup() {
  // Initializing the serial monitor
  Serial.begin(9600);

  // Initializing SIM800L
  SIM800L.begin(9600);

  // Set led pin modes
  for (int i = 0; i <= 5; i++) {
    pinMode(led[i], OUTPUT);
  }

  // Set led default state
  for (int i = 0; i <= 5; i++) {
    digitalWrite(led[i], 0);
  }


  // Testing AT commands in SIM800L
  Test("AT");
  Test("AT+CMGF=1");          // Set SMS to text mode
  Test("AT+CNMI=1,2,0,0,0");  // New SMS message indication
  Serial.print("Done");
  delay(10000);
}

void loop() {
  // Checking for incoming text
  while (SIM800L.available()) {
    buff = SIM800L.readString();
    Serial.print(buff);

    int switch_intserval = 2000;

    if (buff.indexOf("On") > 0) {
      for (int i = 0; i <= 5; i++) {
        digitalWrite(led[i], 1);
        delay(switch_intserval);
      }
    }

    if (buff.indexOf("Off") > 0) {
      for (int i = 0; i <= 5; i++) {
        digitalWrite(led[i], 0);
        delay(switch_intserval);
      }
    }
  }
}

void Test(String command) {
TryAgain:

  SIM800L.println(command);
  delay(1000);

  while (SIM800L.available()) {
    buff = SIM800L.readString();
    Serial.print(buff);
    if (buff.indexOf("OK") > 0) {
      break;
    } else if (buff.indexOf("OK") < 0) {
      goto TryAgain;
    } else {
      goto TryAgain;
    }
  }
  buff = "";
  Serial.println("");
}