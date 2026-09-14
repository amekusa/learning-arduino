// Learning Arduino
// 2026/09/14
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

const int LED_PIN = 9;

char buf[64];
int bufLength = 0;

enum Mode {
	NORMAL,
	FADE,
};

Mode mode = Mode::NORMAL;
bool on = true;

void setup() {
	pinMode(LED_PIN, OUTPUT);
	Serial.begin(9600); // bps: 9600
}

void loop() {
	updateCLI();
	updateLED();
	delay(5);
}

void updateCLI() {
	if (Serial.available()) {
		char c = Serial.read();
		switch (c) {
		case '\r':
			break; // ignore
		case '\n':
			buf[bufLength] = '\0'; // end of string
			command(buf);
			bufLength = 0;
			break;
		default:
			if (bufLength < sizeof(buf) - 1) { // -1 is the room for `\0`
				buf[bufLength++] = c;
			}
		}
	}
}

void command(const char* cmd) {
	if (strcmp(cmd, "led on") == 0) {
		on = true;
	} else if (strcmp(cmd, "led off") == 0) {
		on = false;
	} else if (strcmp(cmd, "led normal") == 0) {
		mode = NORMAL;
	} else if (strcmp(cmd, "led fade") == 0) {
		mode = FADE;
	} else {
		Serial.print("[ERROR] Invalid command: ");
		Serial.println(cmd);
	}
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

