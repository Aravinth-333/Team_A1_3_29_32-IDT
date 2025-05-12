#include <DHT.h>

// Define pin and type for the DHT sensor
#define DHTPIN 2       // Data pin connected to digital pin 2
#define DHTTYPE DHT11  // Use DHT11 or DHT22 depending on your sensor

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

const int ledPin = 9;      // LED connected to digital pin 9
const int humidityThreshold = 60; // Humidity threshold (in %)

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600);      // Initialize Serial Monitor
  dht.begin();             // Start DHT sensor
  Serial.println("Humidity Monitoring System Initialized");
}

void loop() {
  // Read humidity value
  float humidity = dht.readHumidity();

  // Check if the reading is valid
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Debugging: Print humidity value
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Check humidity threshold
  if (humidity > humidityThreshold) {
    digitalWrite(ledPin, HIGH); // Turn ON LED
    Serial.println("Humidity above threshold! LED ON");
  } else {
    digitalWrite(ledPin, LOW);  // Turn OFF LED
    Serial.println("Humidity below threshold. LED OFF");
  }

  delay(2000); // Wait for 2 seconds before the next reading
}
