// Define pins
const int ldrPin = A0; // LDR module output connected to A0
const int ledPin = 9;  // LED connected to pin 9

// Threshold value for darkness (adjust based on your environment)
const int threshold = 800;

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Initialize Serial Monitor for debugging
}

void loop() {
  int lightLevel = analogRead(ldrPin); // Read LDR value
  Serial.print("Light Level: ");
  Serial.println(lightLevel);         // Print light level

  if (lightLevel < threshold) {
  Serial.print("Light Level is below threshold (");
  Serial.print(threshold);
  Serial.println("). Darkness detected, LED ON");
  digitalWrite(ledPin, HIGH);
} else {
  Serial.print("Light Level is above threshold (");
  Serial.print(threshold);
  Serial.println("). Brightness detected, LED OFF");
  digitalWrite(ledPin, LOW);
}


  delay(3000); // Delay for stable readings
}

