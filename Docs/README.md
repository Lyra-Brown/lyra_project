# lyra_lib 詳細ドキュメント

このディレクトリでは、[`lyra_lib`](../lyra_lib/) に含まれるヘッダと実装の詳細を説明します。

## ドキュメント一覧

- [PID 制御](./PID.md)
- [オムニドライブ運動学](./omni_drive_kinematics.md)
- [数学ユーティリティ](./math_utils.md)
- [CAN データ型](./CAN_tool.md)
- [ボタン入力](./button.md)
- [共通ユーティリティ](./utils.md)
- [設定値](./config.md)
- [シンボル公開制御](./visibility_control.md)

## 共通事項

### ビルド

ライブラリのターゲット名は `lyra_general_lib` です。C++ 標準は C++17 で、オムニドライブ運動学などでは Eigen3 を使用します。CMake は、まず `Eigen3::Eigen`、次に `lyra_project/modules/eigen`、最後に `/usr/include/eigen3` を検索します。

システムに Eigen3 がない場合は、Eigen のリポジトリを次の場所に clone してください。

```text
lyra_project/modules/eigen/
```

```bash
cmake -S lyra_lib -B build
cmake --build build
```

ROS 2 ワークスペースでは、次のようにビルドできます。

```bash
colcon build --packages-select lyra_lib
```

### ヘッダの利用

公開ヘッダは `lyra_lib` の include ディレクトリから、次の形式でインクルードします。

```cpp
#include "lyra_lib/PID.hpp"
#include "lyra_lib/math_utils.hpp"
```

### データの単位

- 角度は、関数名に `Degree` が含まれない限りラジアンを使用します。
- 角速度は rad/s、速度は m/s を想定します。
- 時間周期は [`config.hpp`](../lyra_lib/include/lyra_lib/config.hpp) の `cycle_time` で定義され、現在は 10 ms です。
