# オムニドライブ運動学

対象ファイル:

- [`omni_drive_kinematics.hpp`](../lyra_lib/include/lyra_lib/omni_drive_kinematics.hpp)
- [`omni_drive_kinematics.cpp`](../lyra_lib/src/omni_drive_kinematics.cpp)

## 概要

`OmniDriveKinematics` は、4 輪オムニドライブのロボット速度と各輪の角速度を相互変換します。

- `get_wheel_omega()`: ロボットの速度から各車輪の角速度を計算
- `get_robot_vel()`: エンコーダの車輪角速度からロボットのワールド座標系速度を計算
- `get_robot_pose()`: 計算済み速度を使って姿勢を積分

## コンストラクタ

```cpp
OmniDriveKinematics(
    float* wheel_radius,
    float* from_center_distance,
    float& robot_yaw,
    float* wheel_angles,
    float& world_x_vel,
    float& world_y_vel,
    float& robot_rot_vel,
    float* enc_wheel_omega = nullptr,
    Coordinate2d* robot_pose = nullptr
);
```

配列は 4 要素必要です。車輪の順番は呼び出し側で統一してください。

| 引数 | 内容 | 単位 |
| --- | --- | --- |
| `wheel_radius` | 各車輪の半径 | m |
| `from_center_distance` | ロボット中心から各車輪までの距離 | m |
| `robot_yaw` | ロボットの現在のヨー角 | rad |
| `wheel_angles` | 各車輪の向き | rad |
| `world_x_vel`, `world_y_vel` | ワールド座標系の並進速度 | m/s |
| `robot_rot_vel` | ロボットの回転速度 | rad/s |
| `enc_wheel_omega` | エンコーダから得た車輪角速度 | rad/s |
| `robot_pose` | 姿勢の出力先 | m, rad |

ポインタで渡した配列や参照先は、オブジェクトが使用されている間有効である必要があります。

## 速度から車輪角速度を求める

```cpp
float omega = kinematics.get_wheel_omega(wheel_id);
```

`world_x_vel`、`world_y_vel`、`robot_rot_vel`、`robot_yaw` を使い、指定した車輪の角速度を返します。無効な車輪番号、null の車輪半径、0 以下の車輪半径の場合は 0 を返します。

## 車輪速度からロボット速度を求める

```cpp
kinematics.get_robot_vel();
```

車輪半径とエンコーダ角速度からロボット座標系の速度を求め、`robot_yaw` でワールド座標系へ回転します。結果は内部の速度状態に保存されます。

エンコーダ配列または車輪半径が null の場合は何も行いません。

## 姿勢を更新する

```cpp
kinematics.get_robot_vel();
kinematics.get_robot_pose();
```

`get_robot_pose()` は、直前に `get_robot_vel()` で計算された速度を `cycle_time` の間積分して `robot_pose` を更新します。姿勢ポインタが null の場合は何も行いません。

## 前提と注意点

- 現在の実装は `WHEEL_COUNT = 4` を前提にしています。
- `wheel_angles`、`from_center_distance`、`enc_wheel_omega` の要素数は 4 にしてください。
- Eigen3 の擬似逆行列を使って速度変換を行います。
- `get_robot_pose()` の積分周期は固定値 `cycle_time` です。実際の呼び出し周期と一致させてください。
- コンストラクタに渡す配列の null 検査は十分ではないため、呼び出し側で有効性を保証してください。
