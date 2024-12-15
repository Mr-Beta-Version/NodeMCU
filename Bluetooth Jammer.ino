#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3); // RX, TX pins for HC-05

void setup() {
  Serial.begin(115200);       // Serial monitor
  bluetooth.begin(9600);      // HC-05 default baud rate
  Serial.println("Bluetooth Disconnector Ready");

  // Put HC-05 in command mode to accept AT commands
  pinMode(9, OUTPUT);         // Key pin of HC-05
  digitalWrite(9, HIGH);      // Set HIGH for command mode
  delay(1000);                // Stabilization time
}

void loop() {
  // Check if there's any command from the Serial Monitor
  if (Serial.available()) {
    String command = Serial.readString();
    if (command.startsWith("disconnect")) {
      disconnectBluetooth();
    }
  }

  // Optionally handle incoming Bluetooth messages
  if (bluetooth.available()) {
    Serial.print("Bluetooth Message: ");
    Serial.println(bluetooth.readString());
  }
}

void disconnectBluetooth() {
  Serial.println("Sending disconnect command to Bluetooth...");
  bluetooth.println("AT+DISC"); // Disconnect command for HC-05
  delay(1000);
  Serial.println("Device disconnected.");
}
