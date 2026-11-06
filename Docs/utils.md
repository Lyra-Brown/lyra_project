# 共通ユーティリティ

対象ファイル:

- [`utils.hpp`](../lyra_lib/include/lyra_lib/utils.hpp)
- [`utils.cpp`](../lyra_lib/src/utils.cpp)

## デバッグ出力

### `set_debug_print(bool enable)`

ライブラリ内のデバッグ出力を有効または無効にします。初期状態は無効です。

### `is_debug_print_enabled()`

現在のデバッグ出力設定を返します。

### `DebugPrint(const char* format, ...)`

デバッグ出力が有効な場合に、`printf` と同じ形式で標準出力へ出力します。

```cpp
lyra_lib::set_debug_print(true);
lyra_lib::DebugPrint("speed: %.2f\n", speed);
```

無効の場合は出力せず、`-1` を返します。有効の場合は `vprintf` の戻り値を返します。

## `enum_utils::SteeringMode`

ステアリング方式を表す列挙型です。

- `UNDEFINED`: 未定義
- `OMNIDIRECTIONAL`: オムニ方向移動
- `INDEPENDENT_STEERING`: 独立ステアリング

## 注意点

- デバッグ設定はプロセス内で共有されるグローバル状態です。
- `DebugPrint()` はスレッドセーフではありません。
- フォーマット文字列と引数の型は `printf` の規則に従ってください。
