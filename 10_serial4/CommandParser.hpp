#pragma once
#include <Arduino.h>
#include "Command.hpp"

class CommandParser {
private:
	static constexpr size_t BUF_SIZE = 64;
	static constexpr size_t MAX_COMMANDS = 16;

	char _buf[BUF_SIZE];
	size_t _bufN = 0;

	Command _cmds[MAX_COMMANDS];
	size_t _cmdsN = 0;

public:
	CommandParser() {}

	void update() {
		while (Serial.available()) {
			char c = Serial.read();
			switch (c) {
			case '\r': // ignore
				break;
			case '\n': // linebreak = submit
				_buf[_bufN] = '\0'; // end of string
				_bufN = 0; // clear buffer
				{
					TokenList tokens(_buf, " "); // split the line into tokens
					for (size_t i = 0; i < _cmdsN; i++) {
						if (_cmds[i].feed(tokens)) return; // execute
					}
				}
				// invalid command
				break;
			default:
				if (_bufN < sizeof(_buf) - 1) { // -1 is the room for `\0`
					_buf[_bufN++] = c; // store character to buffer
				}
			}
		}
	}

	bool addCommand(const char* name, CommandHandler handler) {
		if (_cmdsN >= MAX_COMMANDS) return false;
		_cmds[_cmdsN++] = Command(name, handler);
		return true;
	}

};
