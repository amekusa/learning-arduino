#include <Arduino.h>

class Button {
public:
	using EventHandler = void (*)();

	Button(int pin, unsigned long debounce) {
		_pin = pin;
		_debounce = debounce;
	}

	void update() {
		unsigned long now = millis();
		if (now - _lastChanged >= _debounce) {
			bool isDown = digitalRead(_pin) == LOW;
			if (isDown != _isDown) {
				_isDown = isDown;
				_lastChanged = now;
				if (isDown) press();
				else release();
			}
		}

	}

	void press() {
		if (_onPressed) _onPressed();
	}

	void release() {
		if (_onReleased) _onReleased();
	}

	void onPressed(EventHandler fn) {
		_onPressed = fn;
	}

	void onReleased(EventHandler fn) {
		_onReleased = fn;
	}

private:
	int _pin;
	unsigned long _debounce;
	unsigned long _lastChanged = 0;
	bool _isDown = false;
	EventHandler _onPressed = nullptr;
	EventHandler _onReleased = nullptr;
};
