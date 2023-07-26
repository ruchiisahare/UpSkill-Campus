
#include <Wire.h>
#include <RTClib.h> // Make sure to install the RTClib library from the Arduino Library Manager

RTC_DS1307 rtc; // Create an instance of the RTC_DS1307 class

const int ldrPin = A0; // LDR pin connected to analog input A0
const int relayPin = 8; // Relay pin connected to digital pin 8
const int motionSensorPin = 2; // Motion sensor pin connected to digital pin 2

const int thresholdValue = 500; // Threshold value for LDR to detect darkness

// Variables for motion sensor
boolean motionDetected = false;
unsigned long motionTimestamp = 0;
const unsigned long motionTimeout = 5000; // Motion timeout in milliseconds (5 seconds)

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(motionSensorPin, INPUT_PULLUP);
  Wire.begin(); // Initialize I2C bus for RTC module
  rtc.begin(); // Initialize RTC module
  // Uncomment the following line if you want to set the current time on the RTC module
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  // Read LDR value
  int ldrValue = analogRead(ldrPin);

  // Read motion sensor
  boolean currentMotionState = digitalRead(motionSensorPin);

  // Check if motion detected
  if (currentMotionState == HIGH) {
    motionDetected = true;
    motionTimestamp = millis();
  } else {
    if (motionDetected && (millis() - motionTimestamp) >= motionTimeout) {
      motionDetected = false;
    }
  }

  // Get current time from RTC module
  DateTime now = rtc.now();

  // Check if it's dark (LDR value below threshold) and motion is not detected
  if (ldrValue < thresholdValue && !motionDetected) {
    // Switch on street lights
    digitalWrite(relayPin, HIGH);
  } else {
    // Switch off street lights
    digitalWrite(relayPin, LOW);
  }

  // Add code here to adjust light intensity based on LDR value and time of day

  // Add code here for remote monitoring and control

  // Add code here for data logging and energy consumption analytics

  delay(1000); // Wait for 1 second before rechecking
}
