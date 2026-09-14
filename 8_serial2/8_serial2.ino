char buf[64];
int bufLength = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	if (Serial.available()) {
		char c = Serial.read();
		switch (c) {
		case '\r':
			break; // ignore
		case '\n':
			buf[bufLength] = '\0'; // end of string
			Serial.println(buf);
			bufLength = 0;
			break;
		default:
			if (bufLength < sizeof(buf) - 1) { // -1 is the room for `\0`
				buf[bufLength++] = c;
			}
		}
	}
}
