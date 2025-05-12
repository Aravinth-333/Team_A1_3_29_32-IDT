// Pin Definitions
const int ldrPin = A0;       // LDR sensor connected to A0
const int radarPin = 2;      // RCWL-0516 OUT connected to pin 2
const int ledPin = 9;        // LED connected to pin 9

// Threshold for light intensity (adjust as needed)
const int lightThreshold = 500;

void setup() {
  pinMode(radarPin, INPUT);  // Set radar sensor pin as input
  pinMode(ledPin, OUTPUT);   // Set LED pin as output
  Serial.begin(9600);        // Initialize Serial Monitor for debugging
}

void loop() {
  // Read values from LDR and Radar sensor
  int lightLevel = analogRead(ldrPin);  // Get light intensity
  int motionDetected = digitalRead(radarPin); // Check for motion

  // Print readings to Serial Monitor for debugging
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.print(" | Motion Detected: ");
  Serial.println(motionDetected);

  // Decision logic for LED
  if (motionDetected == HIGH && lightLevel < lightThreshold) {
    // Motion detected and it's dark
    Serial.println("Conditions met: Turning LED ON");
    digitalWrite(ledPin, HIGH);
  } else {
    // Either no motion or sufficient brightness
    Serial.println("Conditions not met: Turning LED OFF");
    digitalWrite(ledPin, LOW);
  }

  delay(3000); // Small delay for stable readings
}
