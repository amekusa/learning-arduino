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

const int LED_BR_MAX = 255;
const int LED_BR_MIN = 0;

int led_br = LED_BR_MAX;
bool led_on = true;

enum Mode {
	NORMAL,
	FADE,
};

Mode mode = Mode::NORMAL;

CommandParser cli;

void setup() {
	pinMode(LED_PIN, OUTPUT);
	Serial.begin(9600); // bps: 9600

	cli.addCommand("led", [](const TokenList& args) {
		const char* a1 = args.get(1);
		if (a1 == nullptr) {
			Serial.println("[ERROR] Missing argument.");
			return;
		}
		if (strcmp(a1, "on") == 0) {
			led_on = true;

		} else if (strcmp(a1, "off") == 0) {
			led_on = false;

		} else if (strcmp(a1, "normal") == 0) {
			mode = NORMAL;

		} else if (strcmp(a1, "fade") == 0) {
			mode = FADE;

		} else if (strcmp(a1, "brightness") == 0 || strcmp(a1, "br") == 0) {
			const char* a2 = args.get(2); // assuming 0 - 100
			if (a2 == nullptr) {
				Serial.println("[ERROR] Invalid argument");
				return;
			}
			led_br = constrainedMap(atoi(a2), 0, 100, LED_BR_MIN, LED_BR_MAX);
			Serial.print("led_br: ");
			Serial.println(led_br);

		} else {
			Serial.println("[ERROR] Invalid argument.");
			return;
		}
	});
}

void loop() {
	cli.update();
	updateLed();
	delay(5);
}

long constrainedMap(long x, long min1, long max1, long min2, long max2) {
	return constrain(map(x, min1, max1, min2, max2), min2, max2);
}

void updateLed() {
	if (led_on) {
		switch (mode) {
		case Mode::NORMAL:
			analogWrite(LED_PIN, led_br);
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

	analogWrite(LED_PIN, constrainedMap(sin(angle) * 50, -50, 50, LED_BR_MIN, led_br));

	angle += angle_dlt;
	if (angle >= angle_max) angle -= angle_max;
}

