const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, 0);
  delay(1000);

  analogWrite(LED_PIN, 64);
  delay(1000);

  analogWrite(LED_PIN, 128);
  delay(1000);

  analogWrite(LED_PIN, 192);
  delay(1000);

  analogWrite(LED_PIN, 255);
  delay(1000);

  // fade in
  for (int i = 0; i <= 255; i++) {
    analogWrite(LED_PIN, i);
    delay(5);
  }
  // fade out
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED_PIN, i);
    delay(5);
  }
}
