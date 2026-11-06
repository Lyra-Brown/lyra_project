# CAN データ型

対象ファイル:

- [`CAN_tool.hpp`](../lyra_lib/include/lyra_lib/CAN_tool.hpp)
- [`CAN_tool.cpp`](../lyra_lib/src/CAN_tool.cpp)

## `CAN_UNION`

`CAN_UNION` は、CAN フレームの 8 バイトデータを複数の型として参照するための union です。

```cpp
CAN_tool::CAN_UNION frame{};
frame.u8[0] = 0x01;
frame.u8[1] = 0x02;
```

利用できるメンバは次のとおりです。

| メンバ | 型 |
| --- | --- |
| `data` | `uint8_t[8]` |
| `d` | `double` |
| `f` | `float[2]` |
| `i64`, `u64` | 64 bit 整数 |
| `i32`, `u32` | 32 bit 整数 2 個 |
| `i16`, `u16` | 16 bit 整数 4 個 |
| `i8`, `u8` | 8 bit 整数 8 個 |

## 使用例

```cpp
CAN_tool::CAN_UNION payload{};
payload.f[0] = 1.5f;
payload.f[1] = -2.0f;

send_can_bytes(payload.data, sizeof(payload.data));
```

## 注意点

- `union` の値は同じ 8 バイト領域を共有します。
- 通信相手とエンディアン、浮動小数点形式、整数幅を一致させてください。
- CAN フレームの実データ長が 8 バイト未満の場合、未使用領域を送信しないようにしてください。
- `CAN_tool.cpp` は現在、ヘッダをインクルードするだけです。
