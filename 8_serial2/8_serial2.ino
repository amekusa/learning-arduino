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
			Serial.println(buf);
			// clear buffer
			for (int i = 0; i < bufLength; i++) {
				buf[i] = '\0';
			}
			bufLength = 0;
			break;
		default:
			buf[bufLength++] = c;
		}
	}
}
