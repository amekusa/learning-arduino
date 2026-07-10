# Arduino / C++ メモ by ChatGPT

## 1. `new` はなるべく使わない

現在

```cpp
Button* btn = nullptr;

void setup() {
    btn = new Button(BTN_PIN, 20);
}
```

Arduinoでは動的メモリ確保 (`new`, `delete`) は基本的に避ける。

理由

- RAMが少ない
- ヒープ断片化の原因になる
- `delete` を忘れやすい

推奨

```cpp
Button btn(BTN_PIN, 20);

void setup() {
    btn.begin();
}

void loop() {
    btn.update();
}
```

---

## 2. コンストラクタは初期化リストを使う

現在

```cpp
Button(int pin, long debounce) {
    _pin = pin;
    _debounce = debounce;
}
```

推奨

```cpp
Button(int pin, unsigned long debounce)
    : _pin(pin)
    , _debounce(debounce)
{
}
```

メンバーは代入ではなく生成時に初期化する。

---

## 3. `begin()` を用意する

現在

```cpp
pinMode(BTN_PIN, INPUT_PULLUP);
```

を `setup()` に書いている。

推奨

```cpp
class Button {
public:
    void begin() {
        pinMode(_pin, INPUT_PULLUP);
    }
};
```

使う側

```cpp
Button btn(BTN_PIN, 20);

void setup() {
    btn.begin();
}
```

部品ごとに初期化処理を隠蔽できる。

---

## 4. `millis()` の比較方法

現在

```cpp
if (now > _lastChanged + _debounce)
```

推奨

```cpp
if (now - _lastChanged >= _debounce)
```

理由

`millis()` は約49日でオーバーフローする。

差分で比較すればオーバーフロー後も正しく動作する。

---

## 5. `millis()` は `unsigned long`

現在

```cpp
long now;
long _lastChanged;
```

推奨

```cpp
unsigned long now;
unsigned long _lastChanged;
unsigned long _debounce;
```

`millis()` の戻り値も `unsigned long`。

---

## 6. `enum class` を使う

現在

```cpp
enum Mode {
    NORMAL,
    FADE,
    OFF,
};
```

推奨

```cpp
enum class Mode {
    Normal,
    Fade,
    Off,
};
```

使用例

```cpp
Mode mode = Mode::Off;

switch (mode) {
case Mode::Normal:
    ...
    break;
}
```

名前空間を汚さず型安全になる。

---

## 7. クラスはヘッダと実装に分ける

```
Button.h
Button.cpp
```

`Button.h`

```cpp
class Button {
public:
    ...
};
```

`Button.cpp`

```cpp
#include "Button.h"

void Button::update() {
    ...
}
```

スケッチ

```cpp
#include "Button.h"

Button btn(BTN_PIN, 20);
```

規模が大きくなっても管理しやすい。

---

## 8. 部品 = クラス

目標

```cpp
Button button(2, 20);
Led led(9);
RgbLed rgb(3, 5, 6);

void setup() {
    button.begin();
    led.begin();
    rgb.begin();
}

void loop() {
    button.update();
    led.update();
    rgb.update();
}
```

Arduinoライブラリもこの設計思想で作られている。
