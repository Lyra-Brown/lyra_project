# ボタン入力

対象ファイル:

- [`button.hpp`](../lyra_lib/include/lyra_lib/button.hpp)

## 概要

`Button` は、ボタン入力の現在値と前回値を保持し、押下状態および状態変化（エッジ）を判定します。

## 使い方

```cpp
#include "lyra_lib/button.hpp"

lura::input::Button button;

button.update(read_button());
if (button.isPressed(lura::input::ButtonState::DOWN_EDGE)) {
    // 押された瞬間の処理
}
```

`update()` は周期的に 1 回ずつ呼び出してください。`isPressed()` は、通常は `update()` の直後に呼び出します。

## `ButtonState`

| 状態 | 判定 |
| --- | --- |
| `DEFAULT` | 現在押されている |
| `UP_EDGE` | 前回は押下、現在は未押下 |
| `DOWN_EDGE` | 前回は未押下、現在は押下 |
| `EDGE` | 押下状態が変化した |
| `BUTTON_STATE_COUNT` | 状態数を表す番兵値。判定には使用しない |

`isPressed()` の引数を省略すると `DEFAULT` として扱われ、現在の押下状態を返します。

## 注意点

- 最初の `update()` 前は、現在値・前回値とも未押下です。
- `Button` は入力値を保持するだけで、GPIO やスイッチのチャタリング除去は行いません。
- `update()` を呼ばない間は、エッジ判定の状態も更新されません。
