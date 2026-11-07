# lyra_project

ARAMR プロジェクトで使用する C++ 共通ライブラリを管理するディレクトリです。

現在は、PID 制御、逐次最小二乗法、ボタン入力など、ロボット制御で共通して利用する処理を [`lyra_lib`](./lyra_lib/) にまとめています。

機能ごとの詳しい説明は [`Docs/`](./Docs/) を参照してください。

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
| [`pid.hpp`](./lyra_lib/include/lyra_lib/pid.hpp) | PID 制御 |
| [`rls.hpp`](./lyra_lib/include/lyra_lib/rls.hpp) | float/double対応・動的サイズの逐次最小二乗法 |
| [`button.hpp`](./lyra_lib/include/lyra_lib/button.hpp) | ボタン入力状態とエッジ検出 |
| [`visibility_control.h`](./lyra_lib/include/lyra_lib/visibility_control.h) | シンボル公開範囲の制御 |

ライブラリのターゲット名は `lyra_general_lib` です。C++ 標準は C++17 を使用します。

機能別のドキュメント:

- [PID 制御](./Docs/pid.md)
- [RLS（逐次最小二乗法）](./Docs/rls.md)
- [ボタン入力](./Docs/button.md)
- [シンボル公開制御](./Docs/visibility_control.md)

## 必要な環境

- CMake 3.10 以上
- C++17 に対応したコンパイラ
- Eigen3
- ROS 2 で使用する場合は `ament_cmake`

Eigen3 は、まず CMake の `Eigen3::Eigen` ターゲットを検索します。見つからない場合は、
リポジトリ内の `modules/eigen`、さらに `/usr/include/eigen3` を確認します。

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
#include "lyra_lib/pid.hpp"

pos_pid_controller<float> controller;
controller.set_gains(1.0f, 0.0f, 0.1f);
controller.set_dt(0.01f);
const float value = 0.0f;
const float target = 1.0f;
const float output = controller.update(value, target);
```

`lyra_lib` の公開ヘッダを利用する場合は、ビルドシステムで `lyra_general_lib` をリンクし、`include` ディレクトリをインクルードパスに追加してください。

## ライセンス

ライセンスについては [`LICENSE`](./LICENSE) を参照してください。
