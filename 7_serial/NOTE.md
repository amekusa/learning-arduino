
```cpp
// 受信データがあるかを確認
Serial.available();

// 一文字読む
char c = Serial.read();

```

## String を使わず Buffer を使う
String は内部で動的メモリを使うのであまり良くない。

```cpp
char buffer[64];

// バッファに受信データを蓄積
buffer[index++] = c;
```

## 汎用クラス化する

```cpp
// 実装例
class Console {
public:
    void update();

private:
    char buffer[64];
    int length = 0;
};
```
