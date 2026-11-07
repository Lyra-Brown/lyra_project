# PID 制御

対象ファイル:

- [`pid.hpp`](../lyra_lib/include/lyra_lib/pid.hpp)
- [`pid.cpp`](../lyra_lib/src/pid.cpp)

## 概要

`pid_controller_base<T>` は、目標値と現在値の差から制御出力を計算する基底クラスです。
実際に使用する場合は、位置形式の [`pos_pid_controller<T>`](../lyra_lib/include/lyra_lib/pid.hpp)
または速度形式の [`vel_pid_controller<T>`](../lyra_lib/include/lyra_lib/pid.hpp) を使用します。
入力は `update(value, target)` に渡し、更新後の出力を取得します。

## 使い方

```cpp
#include "lyra_lib/pid.hpp"

pos_pid_controller<float> controller;
controller.set_gains(1.0f, 0.1f, 0.01f);
controller.set_dt(0.01f);
controller.set_limits(-1.0f, 1.0f);

const float value = 0.0f;
const float target = 1.0f;
const float command = controller.update(value, target);
```

`set_gains()` の引数は順に比例ゲイン `Kp`、積分ゲイン `Ki`、微分ゲイン `Kd` です。
`update()` の前に `set_dt()` で制御周期 `dt`（秒）を設定してください。

## 計算式

両形式で使用する内部誤差は次のとおりです。

```text
e[0] = target - value
e[1] = 1回前の誤差
e[2] = 2回前の誤差
```

### `pos_pid_controller`

位置形式では、積分値を台形積分して出力を計算します。

```text
de = (e[0] - e[1]) / dt
ie += (e[0] + e[1]) * dt / 2
u = Kp * e[0] + Ki * ie + Kd * de
```

`set_integral_limits(min, max)` で積分値の上下限を設定できます。

### `vel_pid_controller`

速度形式では、出力を前回の出力から更新します。

```text
u += Kp * (e[0] - e[1])
   + Ki * e[0]
   + Kd * (e[0] - 2 * e[1] + e[2]) / dt
```

どちらの形式も、`update()` を呼ぶ周期と `dt` を一致させてください。
出力制限を有効にした場合、出力は設定した範囲に収められます。

## メンバ関数

### `update(T value, T target)`

`input(value, target)` を呼び出してから、更新後の出力を返します。

### `input(T value, T target)`

派生クラスが制御計算を実装するための内部フックです。
利用時は公開メソッドの `update(value, target)` を使用してください。

### `output_value()`

現在の制御出力を返します。`update()` を一度も呼んでいない場合は 0 です。

### `refresh()`

過去の誤差と出力を 0 に戻します。`Pos_PIDController` では積分値も 0 に戻ります。
制御対象や目標値を切り替えるときに使用します。

### `set_limits(T min, T max)`

出力の最小値と最大値を設定し、出力制限を有効にします。

`limits_enabled(false)` または `toggle_limits()` で出力制限を無効化できます。

## 注意点

- `min` は `max` 以下になるように設定してください。
- `pos_pid_controller` では積分値にも `set_integral_limits()` で上下限を設定できます。
- `dt` は 0 にしないでください。
- コントローラはスレッドセーフではありません。
