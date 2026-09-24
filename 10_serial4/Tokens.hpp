#pragma once
#include <string.h>

class Tokens {
private:
	static constexpr size_t MAX_ITEMS = 8;

	const char* _items[MAX_ITEMS];
	size_t _itemsN = 0;

public:
	Tokens(char* str, const char* sep) {
		char* token = strtok(str, sep);
		while (token != nullptr && _itemsN < MAX_ITEMS) {
			_items[_itemsN++] = token;
			token = strtok(nullptr, sep);
		}
	}

	const char* get(size_t idx) const {
		return (idx >= _itemsN) ? nullptr : _items[idx];
	}

	size_t size() const {
		return _itemsN;
	}
};

