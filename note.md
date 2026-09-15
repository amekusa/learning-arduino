## LED
長い方: アノード (+)
短い方: カソード (-)
繋ぐ順番: 電源 -> 抵抗 -> アノード -> カソード -> GND


## PWM
PWM = パルス幅変調。
周期が一定で、オンの時間とオフの時間を可変できるパルス。
周期に対するオン時間の比を **デューティ比** と呼ぶ。


## C++

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

### ポインタ
```c
char* msg
```
`*` はポインタであることを表す。

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

### array-to-pointer decay
配列変数を式に使うと、「先頭要素へのポインタ」に暗黙的に変換される。

```c
int nums[] = {1, 2, 3};
int* ptrA = nums;      // nums は &nums[0] に変換される
int* ptrB = &nums[0];  // ptrA と同じ意味
```

式の中で `&X` と書くと「`X` へのポインタ」という意味になる。
`&` を使っているが参照ではないことに注意。

### struct vs class
struct と class はほぼ同じ。違いの第一歩は「デフォルトが public か private か」。

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

### 集成初期化（aggregate initialization） 
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

## Arduino APIs

### Serial
```c
char c = Serial.read();  //  1 バイト読み込む
```

