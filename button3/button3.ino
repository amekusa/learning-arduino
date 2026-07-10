// Learning Arduino
// 2026/07/10
// Show necessary info:
//   arduino-cli board list
// Monitor logs:
//   arduino-cli monitor -p /dev/cu.usbmodemXXXX -c baudrate=9600
// Compile & Upload:
//   arduino-cli compile --fqbn arduino:renesas_uno:minima
//   arduino-cli upload -p /dev/cu.usbmodemXXXX --fqbn arduino:renesas_uno:minima
//
// Goal:
//   Switching LED lighting patterns with a button.
//   The button must be chatter-proof with 20ms debounce time.

#include "Button.hpp";

const int LED_PIN = 9;
const int BTN_PIN = 2;

enum Mode {
	NORMAL,
	FADE,
	OFF,
};

Mode mode = Mode::OFF;

Button* btn = nullptr;

void setup() {
	pinMode(LED_PIN, OUTPUT);
	pinMode(BTN_PIN, INPUT_PULLUP);

	btn = new Button(BTN_PIN, 20);
	btn->onPressed(btnPressed);
	btn->onReleased(btnReleased);

	Serial.begin(9600); // bps: 9600
	Serial.println("Setup done");
}

void loop() {
	btn->update();
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

