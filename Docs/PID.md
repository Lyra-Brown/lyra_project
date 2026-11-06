# PID 制御

対象ファイル:

- [`PID.hpp`](../lyra_lib/include/lyra_lib/PID.hpp)
- [`PID.cpp`](../lyra_lib/src/PID.cpp)

## 概要

`PID` クラスは、目標値と現在値の差から制御出力を計算します。差分を `Input()` で入力し、`Output()` で現在の出力を取得します。

## 使い方

```cpp
#include "lyra_lib/PID.hpp"

PID controller(1.0, 0.1, 0.01);
controller.set_limits(-1.0f, 1.0f);

controller.Input(target, current);
double command = controller.Output();
```

コンストラクタの引数は順に比例ゲイン `Kp`、積分ゲイン `Ki`、微分ゲイン `Kd` です。

## 計算式

内部誤差は次のように更新されます。

```text
e[0] = target - value
e[1] = 1回前の誤差
e[2] = 2回前の誤差
```

出力の更新式は次のとおりです。

```text
u += Kp * (e[0] - e[1])
   + Ki * e[0]
   + Kd * (e[0] - 2 * e[1] + e[2])
```

一般的な位置形式 PID ではなく、誤差の差分を使う速度形式に近い実装です。`Input()` を呼ぶ周期によって実際の制御特性が変わるため、ゲインは使用周期に合わせて調整してください。

## メンバ関数

### `Input(double target, double value)`

目標値と現在値を受け取り、内部誤差と出力を更新します。出力制限を有効にしている場合は、更新後の出力を指定範囲に収めます。

### `Output()`

現在の制御出力を返します。`Input()` を一度も呼んでいない場合は 0 です。

### `refresh()`

過去の誤差と出力をすべて 0 に戻します。制御対象や目標値を切り替えるときに使用します。

### `set_limits(float min, float max)`

出力の最小値と最大値を設定し、出力制限を有効にします。現在の実装では、設定後に制限を無効化する関数はありません。

## 注意点

- `min` は `max` 以下になるように設定してください。
- 積分項の蓄積に相当する出力 `u` に対して、設定した上下限で飽和が適用されます。
- `PID` はスレッドセーフではありません。
