## LED
長い方: アノード (+)
短い方: カソード (-)
繋ぐ順番: 電源 -> 抵抗 -> アノード -> カソード -> GND


## PWM
PWM = パルス幅変調。
周期が一定で、オンの時間とオフの時間を可変できるパルス。
周期に対するオン時間の比を **デューティ比** と呼ぶ。


## C++

C/C++ の代表的な記憶領域

┌─────────────────────┐
│ 静的記憶域          │ ← プログラム実行中ずっと存在
├─────────────────────┤
│ スタック            │ ← 関数・スコープに応じて増減
├─────────────────────┤
│ ヒープ              │ ← new / malloc などで動的に管理
└─────────────────────┘

| 例                        | 記憶域 | 寿命                   |
| ------------------------- | ------ | ---------------------- |
| `int x;`（関数内）        | 自動   | スコープ終了まで       |
| `Foo obj;`（関数内）      | 自動   | スコープ終了まで       |
| `int a[100];`（関数内）   | 自動   | スコープ終了まで       |
| `static int x;`           | 静的   | プログラム終了まで     |
| グローバル変数            | 静的   | プログラム終了まで     |
| `"abc"`                   | 静的   | プログラム終了まで     |
| `new Foo`                 | 動的   | `delete` まで          |
| `new int[100]`            | 動的   | `delete[]` まで        |

### '' vs ""
```c
char a = 'a';  // OK
char a = "a";  // エラー（"a" は 'a' + '\0' のため）
```

### C 文字列
C 文字列とは終端文字 `'\0'` で終わっている char 配列のこと。

```c
char abc[] = {'a', 'b', 'c', '\0'};  // C 文字列
char def[] = {'d', 'e', 'f'};        // C 文字列ではない
```

C 文字列と文字列リテラルは違うものであることを留意すべきである。

char 配列に文字列リテラルを代入すると C 文字列に変換される:
```c
char abc1[] = {'a', 'b', 'c', '\0'};  // C 文字列
char abc2[] = "abc";  // abc1 と同じ
char* abc3 = "abc";   // 同じではない
```

### const

#### 引数に `const` が必要なケース
文字列リテラルを指すポインタは `const char*` で受け取る必要がある。

```c
void greet(const char* name) { ... }
greet("John"); // OK

void greet(char* name) { ... }
greet("John"); // Error
```


### ポインタ
```c
char* msg
```
`*` はポインタであることを表す。

#### ポインタと const
```c
const char* abc = "abc"; // ポインタ
abc[0] = 'x';            // Error（指す先の値を書き換えられない）
abc = "xyz";             // OK（指す先を変えることはできる）
```

```c
const int* a; // a が指している int を変更できない
int* const b; // b が指す先を変更できない
```

### 参照とポインタの使い分け
「必ず何かを指していて、付け替える必要がない」→ 参照
「何も指さないことがある／指す先を変更したい」→ ポインタ

参照は基本的に、
- nullptr にできない
- 後から別の対象へ付け替えられない
- * や -> を書かなくていい

関数の引数でよく使う:
```c
void printValue(const int& value);
```
これは、
「int をコピーせずに受け取りたい。ただし nullptr のような無効状態は要らない」
という意味合いで自然。

#### 参照を使うかどうかを決める実用ルール
小さい値               → 値渡し
大きな値を読むだけ     → const + 参照
大きな値を書き換える   → 参照
「ない」を表現したい   → ポインタ
所有権を渡したい       → 値渡し / スマートポインタ

### 配列
```c
int nums[] = {1, 2, 3};
nums[0]  // 1
nums[1]  // 2
nums[2]  // 3
```

#### オブジェクト配列
```c
Person people[16];
```
この配列は宣言した時点で 16 個の `Person` インスタンスが生成される。
ゆえに `Person` クラスはデフォルトコンストラクタを持っている必要がある。

#### array-to-pointer decay
配列変数を式に使うと、「先頭要素へのポインタ」に暗黙的に変換される。

```c
int nums[] = {1, 2, 3};
int* ptrA = nums;      // nums は &nums[0] に変換される
int* ptrB = &nums[0];  // ptrA と同じ意味
```

式の中で `&X` と書くと「`X` へのポインタ」という意味になる。
`&` を使っているが参照ではないことに注意。

### const char* const* ???
```c
const char** items; // 文字を変更できない
items = other;      // OK
items[0] = other;   // OK
items[0][0] = 'X';  // Error

const char* const items; // ポインタも変更できない
items = other;           // OK
items[0] = other;        // Error
items[0][0] = 'X';       // Error

const char* const* x // そういうポインタを指す
```

### struct vs class
struct と class はほぼ同じ。違いの第一歩は「デフォルトが public か private か」。

### const の後置
```c
class Hero {
private:
	int _level = 1;
public:
	void levelUp() {
		_level++;
	}
	int getLevel() const { // このメソッドは状態を変更しないので const
		return _level;
	}
}
```

### プリプロセッサ
```c
#include "Foo.hpp"  // 別のソースを読み込む
#pragma once        // これを書いたソースは一度しか #include されない
```

### for
配列をイテレートする:
```c
for (int num : nums) {
	...
}
```
これは JS における以下と同じ:
```js
for (let num of nums) {
	...
}
```
型を書きたくない場合は `auto` を使う:
```c
for (auto item : items) {
```

### 集成体初期化（aggregate initialization） 
```c
struct Person {
	const char* name;
	int age;
};

Person person = {"Alice", 7};

person.name  // "Alice"
person.age   // 7
```

`{ }` 内に列挙した値が、`struct / class` の `public` メンバにマッピングされて初期化される。
マッピングはメンバの宣言の順番に従う。

```c
struct Person {
	const char* name;
	int age;
};

Person people[] = {
	{"Alice",    7},
	{"Bob",     14},
	{"Charlie", 28},
};

people[1].name  // "Bob"
people[1].age   // 14
```
このように書くこともできる。

集成体初期化を行う `struct / class` は「集成体 (aggregate)」でなくてはならない。
`private / protected` メンバを一つでも持っている `struct / class` は集成体とはみなされない。

## Arduino APIs

### Serial
```c
char c = Serial.read();  //  1 バイト読み込む
```

