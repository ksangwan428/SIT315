const int motor = 13;
const int Led = 12;
int percentValue = 0;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(Led, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
  delay(2000);
}

void loop() {
  int value = analogRead(A0);
  float Moisture = value * 500.0 / 1023.0;

  Serial.print("Moisture Value: ");
  Serial.println(Moisture);

  if (Moisture < 220) {
    digitalWrite(motor, HIGH);
    digitalWrite(Led, HIGH);
  } else {
    digitalWrite(motor, LOW);
    digitalWrite(Led, LOW);
  }
}
