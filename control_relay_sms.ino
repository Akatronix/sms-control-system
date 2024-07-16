#include <SoftwareSerial.h>


SoftwareSerial sim800lSerial(6,7); // RX, TX pins

//relay pin here 
#define LED_PIN 10

void setup() {
  Serial.begin(9600); 
  sim800lSerial.begin(9600); 

  // Initialize SIM800L
  delay(1000);
  sim800lSerial.println("AT");
  delay(1000);
  sim800lSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  Serial.println("Setup complete.");
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);
}

void loop() {
  if (sim800lSerial.available()) {
    String message = sim800lSerial.readString();
    Serial.print("Received message: ");
    Serial.println(message);

    // Check if the received message contains a specific command
    if (message.indexOf("LIGHT ON") != -1) {
      // Turn on LED or perform desired action
      Serial.println("Turning LED on...");
      digitalWrite(LED_PIN, LOW);
      sim800lSerial.println("AT+CMGD=1,4"); 
    }
    else if (message.indexOf("LIGHT OFF") != -1) {
      // Turn off LED or perform desired action
      Serial.println("Turning LED off...");
      digitalWrite(LED_PIN, HIGH);
      sim800lSerial.println("AT+CMGD=1,4");
    }
    

    delay(1000);
  }
}
