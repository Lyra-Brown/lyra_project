# 数学ユーティリティ

対象ファイル:

- [`math_utils.hpp`](../lyra_lib/include/lyra_lib/math_utils.hpp)
- [`math_utils.cpp`](../lyra_lib/src/math_utils.cpp)

## `Coordinate2d`

2 次元の位置と角度をまとめる構造体です。

```cpp
Coordinate2d pose;
pose.position = Vector2d(x, y);
pose.angle = yaw;
```

位置は Eigen の `Vector2d`、角度は `double` で保持します。角度の単位はラジアンです。

## 単位接頭辞定数

`TERA` から `PICO` までの SI 接頭辞を `double` の定数として提供します。たとえば `MILLI` は `1.0e-3` です。

```cpp
float cycle_time = 10.0f * MILLI;
```

## `Conversion` 名前空間

### `convertToRadian(double degree)`

度をラジアンへ変換します。

### `convertToDegree(double radian)`

ラジアンを度へ変換します。

### `convertToRobotCoordinate2d(...)`

ワールド座標系の速度ベクトルを、ロボットの向きに合わせたロボット座標系へ変換します。`robot_theta` はラジアンで指定します。

第 3 引数 `out_robot_coordinate_vel` を指定すると、戻り値と同じ結果が出力先にも書き込まれます。入力ポインタは null でない必要があります。

## `Normalization` 名前空間

### `normalizeRadian(double radian)`

角度を `(-π, π]` の範囲に正規化します。

### `normalizeDegree(double degree)`

角度を `(-180, 180]` の範囲に正規化します。

## `MathConstants` 名前空間

次の関数を提供します。

- `get_minimum_float`: `float` 配列の最小値
- `get_minimum_double`: `double` 配列の最小値
- `get_minimum_int`: `int32_t` 配列の最小値
- `get_maximum_int`: `int32_t` 配列の最大値
- `get_polarity_int32`: 整数の符号（`-1`, `0`, `1`）
- `get_polarity_float`: 浮動小数点数の符号（`-1`, `0`, `1`）

配列検索関数は `arr[0]` から処理を開始するため、`size` が 0 の場合や配列ポインタが null の場合には使用しないでください。
