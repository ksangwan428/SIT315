const int motor = 13;
const int Led = 12;
int percentValue = 0;  
volatile bool interruptFlag = false;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(2, INPUT_PULLUP);  // Assuming the push button is connected to pin 2
  attachInterrupt(digitalPinToInterrupt(2), buttonInterrupt, FALLING);  // Attach interrupt on falling edge
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  if (interruptFlag) {
    Serial.println("Button pressed! Toggle motor and LED.");
    toggleMotorAndLed();
    interruptFlag = false;  // Reset the flag
  }

  int value = analogRead(A0);
  float Moisture = value * 500.0 / 1023.0;

  Serial.print("Moisture Level: ");
  Serial.println(Moisture);

  if (Moisture < 220){
    Serial.println("Moisture is low. Turning on motor and LED.");
    digitalWrite(motor, HIGH);
    digitalWrite(Led, HIGH);
  }
  else {
    Serial.println("Moisture is sufficient. Turning off motor and LED.");
    digitalWrite(motor, LOW);
    digitalWrite(Led, LOW);
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

void buttonInterrupt() {
  Serial.println("Interrupt occurred! Button pressed.");
  interruptFlag = true;
}
