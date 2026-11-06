# PID 制御

対象ファイル:

- [`PID.hpp`](../lyra_lib/include/lyra_lib/PID.hpp)
- [`PID.cpp`](../lyra_lib/src/PID.cpp)

## 概要

`IPIDController<T>` は、目標値と現在値の差から制御出力を計算する基底クラスです。
実際に使用する場合は、位置形式の [`Pos_PIDController<T>`](../lyra_lib/include/lyra_lib/PID.hpp)
または速度形式の [`Vel_PIDController<T>`](../lyra_lib/include/lyra_lib/PID.hpp) を使用します。
入力は `Input(value, target)` に渡し、現在の出力は `Output()` で取得します。

## 使い方

```cpp
#include "lyra_lib/PID.hpp"

Pos_PIDController<float> controller;
controller.setGains(1.0f, 0.1f, 0.01f);
controller.setDt(0.01f);
controller.setLimits(-1.0f, 1.0f);

const float value = 0.0f;
const float target = 1.0f;
controller.Input(value, target);
const float command = controller.Output();
```

`setGains()` の引数は順に比例ゲイン `Kp`、積分ゲイン `Ki`、微分ゲイン `Kd` です。
`Input()` の前に `setDt()` で制御周期 `dt`（秒）を設定してください。

## 計算式

両形式で使用する内部誤差は次のとおりです。

```text
e[0] = target - value
e[1] = 1回前の誤差
e[2] = 2回前の誤差
```

### `Pos_PIDController`

位置形式では、積分値を台形積分して出力を計算します。

```text
de = (e[0] - e[1]) / dt
ie += (e[0] + e[1]) * dt / 2
u = Kp * e[0] + Ki * ie + Kd * de
```

`setIntegralLimits(min, max)` で積分値の上下限を設定できます。

### `Vel_PIDController`

速度形式では、出力を前回の出力から更新します。

```text
u += Kp * (e[0] - e[1])
   + Ki * e[0]
   + Kd * (e[0] - 2 * e[1] + e[2]) / dt
```

どちらの形式も、`Input()` を呼ぶ周期と `dt` を一致させてください。
出力制限を有効にした場合、出力は設定した範囲に収められます。

## メンバ関数

### `update(T value, T target)`

`Input(value, target)` を呼び出してから、更新後の出力を返します。

### `Input(T value, T target)`

現在値と目標値を受け取り、内部誤差と出力を更新します。
引数の順序は `value`、`target` です。

### `Output()`

現在の制御出力を返します。`Input()` を一度も呼んでいない場合は 0 です。

### `refresh()`

過去の誤差と出力を 0 に戻します。`Pos_PIDController` では積分値も 0 に戻ります。
制御対象や目標値を切り替えるときに使用します。

### `setLimits(T min, T max)`

出力の最小値と最大値を設定し、出力制限を有効にします。

`limitsEnabled(false)` または `toggleLimits()` で出力制限を無効化できます。

## 注意点

- `min` は `max` 以下になるように設定してください。
- `Pos_PIDController` では積分値にも `setIntegralLimits()` で上下限を設定できます。
- `dt` は 0 にしないでください。
- コントローラはスレッドセーフではありません。
