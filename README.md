# lyra_project

ARAMR プロジェクトで使用する C++ 共通ライブラリを管理するディレクトリです。

現在は、PID 制御、オムニホイールの運動学計算、数学ユーティリティ、CAN データ変換など、ロボット制御で共通して利用する処理を [`lyra_lib`](./lyra_lib/) にまとめています。

各ファイルの詳しい説明は [`Docs/README.md`](./Docs/README.md) を参照してください。

## ディレクトリ構成

```text
lyra_project/
├── LICENSE
├── README.md
├── Docs/
└── lyra_lib/
    ├── CMakeLists.txt
    ├── package.xml
    ├── include/lyra_lib/
    └── src/
```

## `lyra_lib` の主な機能

| ヘッダ | 内容 |
| --- | --- |
| [`PID.hpp`](./lyra_lib/include/lyra_lib/PID.hpp) | PID 制御 |
| [`omni_drive_kinematics.hpp`](./lyra_lib/include/lyra_lib/omni_drive_kinematics.hpp) | オムニドライブの速度・姿勢計算 |
| [`math_utils.hpp`](./lyra_lib/include/lyra_lib/math_utils.hpp) | 座標変換、角度変換、角度の正規化、数学ユーティリティ |
| [`CAN_tool.hpp`](./lyra_lib/include/lyra_lib/CAN_tool.hpp) | CAN 通信用データの型変換 |
| [`button.hpp`](./lyra_lib/include/lyra_lib/button.hpp) | ボタン入力状態とエッジ検出 |
| [`utils.hpp`](./lyra_lib/include/lyra_lib/utils.hpp) | デバッグ出力などの共通処理 |
| [`config.hpp`](./lyra_lib/include/lyra_lib/config.hpp) | ライブラリの設定値 |

ライブラリのターゲット名は `lyra_general_lib` です。C++ 標準は C++17 を使用します。

## 必要な環境

- CMake 3.10 以上
- C++17 に対応したコンパイラ
- Eigen3
- ROS 2 で使用する場合は `ament_cmake`

Eigen3 は、まず CMake の `Eigen3::Eigen` ターゲットを検索します。見つからない場合は `/usr/include/eigen3` も確認します。

## ROS 2 パッケージとしてビルドする

ワークスペースのルートから、次のコマンドを実行します。

```bash
colcon build --packages-select lyra_lib
source install/setup.bash
```

ROS 2 でビルドした場合、ヘッダは `include` に、ライブラリは `lib` にインストールされます。

## 通常の CMake プロジェクトとしてビルドする

ROS 2 を使用しない環境では、`lyra_lib` を通常の CMake プロジェクトとしてビルドできます。

```bash
cd lyra_lib
cmake -S . -B build
cmake --build build
```

`ament_cmake` が見つからない場合は、ROS 2 用のインストール処理を行わず、通常の CMake ビルドとして処理されます。

## 利用例

```cpp
#include "lyra_lib/PID.hpp"

PID controller(1.0, 0.0, 0.1);
controller.Input(target, value);
const double output = controller.Output();
```

`lyra_lib` の公開ヘッダを利用する場合は、ビルドシステムで `lyra_general_lib` をリンクし、`include` ディレクトリをインクルードパスに追加してください。

## ライセンス

ライセンスについては [`LICENSE`](./LICENSE) を参照してください。
