// Learning Arduino
// 2026/07/11
//
//
//

void setup() {
	Serial.begin(9600); // bps: 9600
	Serial.println("Setup done");
}

void loop() {
	if (Serial.available()) {
		char c = Serial.read();
		Serial.print("Received:");
		Serial.println(c);
	}
}
