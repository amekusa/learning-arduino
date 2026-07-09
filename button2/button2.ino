const int LED_PIN = 9;
const int BTN_PIN = 2;

enum Mode {
	NORMAL,
	FADE,
	OFF,
};

Mode mode = Mode::OFF;

bool btnDown = false;
bool btnDownPrev = false;

void setup() {
	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT_PULLUP);
	Serial.begin(9600); // bps: 9600
	Serial.println("Setup done");
}

void loop() {
	btnDown = digitalRead(BTN_PIN) == LOW;
	if (btnDown != btnDownPrev) {
		if (btnDown) btnPressed();
		else btnReleased();
		btnDownPrev = btnDown;
	}
	switch (mode) {
	case Mode::NORMAL:
		analogWrite(LED_PIN, 255);
		break;
	case Mode::FADE:
		fade();
		break;
	case Mode::OFF:
		analogWrite(LED_PIN, 0);
		break;
	}
	delay(5);
}

void fade() {
	static float angle = .0f;
	static const float angle_dlt = .005f;
	static const float angle_max = 2.0f * PI;

	analogWrite(LED_PIN, round((sin(angle) + 1.0f) * 127.5f));

	angle += angle_dlt;
	if (angle >= angle_max) angle -= angle_max;
}

void btnPressed() {
	Serial.println("btnPressed");
	switch (mode) {
	case Mode::NORMAL:
		mode = FADE;
		break;
	case Mode::FADE:
		mode = OFF;
		break;
	case Mode::OFF:
		mode = NORMAL;
		break;
	}
}

void btnReleased() {
	Serial.println("btnReleased");

}
