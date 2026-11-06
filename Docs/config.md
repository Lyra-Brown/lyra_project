# 設定値

対象ファイル:

- [`config.hpp`](../lyra_lib/include/lyra_lib/config.hpp)

## `WHEEL_COUNT`

```cpp
constexpr uint8_t WHEEL_COUNT = 4;
```

オムニドライブの車輪数を表します。`OmniDriveKinematics` は現在、この値を使って 4 輪の行列を構成します。

## `cycle_time`

```cpp
constexpr float cycle_time = static_cast<float>(10.0 * MILLI);
```

姿勢積分に使用する制御周期です。現在の値は 10 ms（0.01 s）です。

`get_robot_pose()` は実際の経過時間を測定せず、この固定値を使って速度を積分します。そのため、運動学計算の呼び出し周期を 10 ms に合わせる必要があります。

## 変更時の注意

- `WHEEL_COUNT` を変更する場合は、行列のサイズ、入力配列、車輪配置、呼び出し側も合わせて変更してください。
- `cycle_time` を変更する場合は、制御ループの実周期と整合しているか確認してください。
