#include <IRremote.h>

const int motor = 13;
const int Led = 12;
const int SOIL_MOISTURE_PIN = A0;
const int RECV_PIN = 2;

int percentValue = 0;
volatile bool interruptFlag = false;
bool powerOn = true; // Global variable to track power state

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(SOIL_MOISTURE_PIN, INPUT);

  irrecv.enableIRIn();

  attachInterrupt(digitalPinToInterrupt(RECV_PIN), IR_trigger, FALLING); // Change to FALLING
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  if (interruptFlag) {
    Serial.println("IR signal received! Toggle motor and LED.");
    toggleMotorAndLed();
    interruptFlag = false;  // Reset the flag
  }

  if (powerOn) {  // Only execute if power is on
    int value = analogRead(SOIL_MOISTURE_PIN);
    float Moisture = value * 500.0 / 1023.0;

    Serial.print("Moisture Level: ");
    Serial.println(Moisture);

    if (Moisture < 220) {
      Serial.println("Moisture is low. Turning on motor and LED.");
      digitalWrite(motor, HIGH);
      digitalWrite(Led, HIGH);
    } else {
      Serial.println("Moisture is sufficient. Turning off motor and LED.");
      digitalWrite(motor, LOW);
      digitalWrite(Led, LOW);
    }
  }

  delay(1000);
}

void toggleMotorAndLed() {
  if (digitalRead(motor) == HIGH) {
    digitalWrite(motor, LOW);
    digitalWrite(Led, LOW);
  } else {
    digitalWrite(motor, HIGH);
    digitalWrite(Led, HIGH);
  }
}

void toggleMotorAndLedOFF() {
  digitalWrite(motor, LOW);
  digitalWrite(Led, LOW);
  powerOn = false;  // Turn off power
}

void IR_trigger() {
  if (irrecv.decode(&results)) {
    Serial.println("Program Interrupted.");
    Serial.print("IR Code: ");
    Serial.println(results.value, HEX);

    if (results.value == 16580863) {  
      Serial.println("Power button pressed. Toggling motor and LED.");
      toggleMotorAndLedOFF();
    } else {
      Serial.println("Unknown IR code received.");
      toggleMotorAndLedOFF();
    }

    irrecv.resume();
  }
}
