const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  static float angle = .0f;
  static const float angle_dlt = .01f;
  static const float angle_max = 2.0f * PI;
  
  analogWrite(LED_PIN, round((sin(angle) + 1.0f) * 127.5f));

  angle += angle_dlt;
  if (angle >= angle_max) angle -= angle_max;

  delay(5);
}

float toRad(float deg) {
  return deg * PI / 180.0f;
}

float toDeg(float rad) {
  return rad * 180.0f / PI;
}
