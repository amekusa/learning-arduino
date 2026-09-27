#pragma once
#include "TokenList.hpp"

using CommandHandler = void (*)(const TokenList&);
// NOTE: CommandHandler は関数ポインタ型。

class Command {
private:
	const char* _name = nullptr;
	CommandHandler _handler = nullptr;

public:

	// NOTE:
	// - デフォルトコンストラクタ
	// - インスタンスを配列の要素にするにはこれが必要
	Command() {}

	// NOTE:
	// - 引数有りコンストラクタ
	// - name は文字列リテラルを受け取れるように const char*
	// - handler は CommandHandler がポインタ型なので * は不要（= ポインタの値渡し）
	Command(const char* name, CommandHandler handler) :
	_name(name), _handler(handler) {}

	bool feed(const TokenList& tokens) const {
		const char* t = tokens.get(0);
		if (t == nullptr) return false;
		if (strcmp(_name, t) == 0) {
			_handler(tokens);
			return true;
		}
		return false;
	}

	const char* name() const {
		return _name;
	}
};
