// Learning Arduino
// 2026/09/20
//
// Commands:
//   Show necessary info:
//     arduino-cli board list
//   Monitor logs:
//     arduino-cli monitor -p /dev/cu.usbmodemXXXX -c baudrate=9600
//   Compile & Upload:
//     arduino-cli compile --fqbn arduino:renesas_uno:minima
//     arduino-cli upload -p /dev/cu.usbmodemXXXX --fqbn arduino:renesas_uno:minima
//
// Goal:
//   Controlling LED via serial commands.
//
// Circuit:
//   D9 - R220 - LED - GND

#include "CommandParser.hpp"

const int LED_PIN = 9;

CommandParser cli;

enum Mode {
	NORMAL,
	FADE,
};

Mode mode = Mode::NORMAL;
bool on = true;


void setup() {
	pinMode(LED_PIN, OUTPUT);
	Serial.begin(9600); // bps: 9600

	cli.addCommand("led", [](const TokenList& args) {
		const char* a1 = args.get(1);
		if (strcmp(a1, "on") == 0) {
			on = true;
		} else if (strcmp(a1, "off") == 0) {
			on = false;
		} else if (strcmp(a1, "normal") == 0) {
			mode = NORMAL;
		} else if (strcmp(a1, "fade") == 0) {
			mode = FADE;
		}
	});
}

void loop() {
	cli.update();
	updateLED();
	delay(5);
}

void updateLED() {
	if (on) {
		switch (mode) {
		case Mode::NORMAL:
			analogWrite(LED_PIN, 255);
			break;
		case Mode::FADE:
			fade();
			break;
		}
	} else {
		analogWrite(LED_PIN, 0);
	}
}

void fade() {
	static float angle = .0f;
	static const float angle_dlt = .01f;
	static const float angle_max = 2.0f * PI;

	analogWrite(LED_PIN, round((sin(angle) + 1.0f) * 127.5f));

	angle += angle_dlt;
	if (angle >= angle_max) angle -= angle_max;
}

