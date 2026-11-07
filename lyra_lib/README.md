# lyra_lib

`lyra_lib` は、Lyraプロジェクトで使用する汎用C++ライブラリです。

## 構成

- [`include/lyra_lib/PID.hpp`](include/lyra_lib/PID.hpp)
  - `pos_pid_controller<T>`: 位置形式PID制御
  - `vel_pid_controller<T>`: 速度形式PID制御
- [`include/lyra_lib/limiter.hpp`](include/lyra_lib/limiter.hpp)
  - `limiter<T>`: 値の上下限を適用するリミッター

## limiter

```cpp
#include "lyra_lib/limiter.hpp"

limiter<float> output_limiter;
output_limiter.set_limits(-1.0f, 1.0f);

const float output = output_limiter.set_value(1.5f);
// output == 1.0f
```

`set_limits()`、`set_min()`、`set_max()` は設定時に制限を有効化します。
制限の有効・無効は `enable_limits()` または `toggle_limits()` で切り替えられます。

## PID controller

```cpp
#include "lyra_lib/PID.hpp"

pos_pid_controller<float> controller;
controller.set_gains(1.0f, 0.1f, 0.01f);
controller.set_dt(0.01f);
controller.set_limits(-1.0f, 1.0f);

const float output = controller.update(current_value, target_value);
```

`set_dt()` には0より大きい制御周期を指定してください。
`pos_pid_controller<T>` では `set_integral_limits()` によって積分値も制限できます。

## 命名規則

公開されている型名、関数名、変数名はスネークケースを使用します。

## ビルド

プロジェクトのビルドディレクトリから、次のコマンドでライブラリをビルドできます。

```sh
cmake --build build/lyra_lib --target lyra_general_lib
```
