# ボタン入力

対象ファイル:

- [`button.hpp`](../lyra_lib/include/lyra_lib/button.hpp)

## 概要

`button` は、ボタン入力の現在値と前回値を保持し、押下状態および状態変化（エッジ）を判定します。

## 使い方

```cpp
#include "lyra_lib/button.hpp"

lura::input::button button;

button.update(read_button());
if (button.is_pressed(lura::input::button_state::down_edge)) {
    // 押された瞬間の処理
}
```

`update()` は周期的に 1 回ずつ呼び出してください。`is_pressed()` は、通常は `update()` の直後に呼び出します。

## `button_state`

| 状態 | 判定 |
| --- | --- |
| `default_state` | 現在押されている |
| `up_edge` | 前回は押下、現在は未押下 |
| `down_edge` | 前回は未押下、現在は押下 |
| `edge` | 押下状態が変化した |
| `button_state_count` | 状態数を表す番兵値。判定には使用しない |

`is_pressed()` の引数を省略すると `default_state` として扱われ、現在の押下状態を返します。

## 注意点

- 最初の `update()` 前は、現在値・前回値とも未押下です。
- `button` は入力値を保持するだけで、GPIO やスイッチのチャタリング除去は行いません。
- `update()` を呼ばない間は、エッジ判定の状態も更新されません。
