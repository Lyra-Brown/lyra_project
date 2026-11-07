# RLS（逐次最小二乗法）

対象ファイル:

- [`rls.hpp`](../lyra_lib/include/lyra_lib/rls.hpp)
- [`rls.cpp`](../lyra_lib/src/rls.cpp)

## 概要

`rls_vel<T>` は、動的なパラメータ数に対応した逐次最小二乗法
(Recursive Least Squares) のクラスです。

`T` には `float` または `double` を指定できます。デフォルトは `double` で、
ベクトル・共分散行列・内部計算はすべて指定した型で行われます。

## 使い方

```cpp
#include "lyra_lib/rls.hpp"

Eigen::VectorXf initial_params(3);
initial_params << 0.0f, 0.0f, 0.0f;

rls_vel<float> rls(initial_params);

Eigen::VectorXf labels(3);
labels << 1.0f, 2.0f, 3.0f;

rls.update(1.0f, labels);
const Eigen::VectorXf parameters = rls.get_parameters();
```

`double` を使う場合は `Eigen::VectorXd` と `rls_vel<double>` を使用します。

```cpp
Eigen::VectorXd initial_params(3);
initial_params << 0.0, 0.0, 0.0;

rls_vel<double> rls(initial_params);
```

初期パラメータの配列と要素数を指定するコンストラクタも使用できます。

```cpp
const float initial_params[] = {0.0f, 0.0f, 0.0f};
rls_vel<float> rls(initial_params, 3);
```

## コンストラクタ

### `rls_vel(const vector& initial_params, T forgetting_factor, T initial_covariance)`

- `initial_params`: 推定するパラメータの初期値
- `forgetting_factor`: 忘却係数。`1.0e-6` から `1.0` の範囲に制限されます
- `initial_covariance`: 共分散行列の対角成分の初期値

`initial_params` の要素数が、そのままパラメータ数と共分散行列のサイズになります。
空のベクトルを渡すと `std::invalid_argument` が送出されます。

## メンバ関数

### `update(T actual_value, const vector& true_value_labels)`

観測値 `actual_value` と説明変数ベクトル `true_value_labels` を使って、
パラメータと共分散行列を更新します。

説明変数ベクトルの要素数は、初期パラメータの要素数と一致している必要があります。
一致しない場合は `std::invalid_argument` が送出されます。

### `get_parameters()`

現在の推定パラメータを返します。戻り値の型は `rls_vel<T>::vector` です。

### `set_clipping_threshold(T threshold)`

共分散行列の対角成分に適用するクリッピング閾値を設定します。
負の値を渡した場合は絶対値が使用されます。

### `set_covariance_reset_flag(bool flag)`

- `true`: 共分散行列の対角成分を閾値内にクリップします
- `false`: 対角成分が閾値を超えた場合、共分散行列を初期状態に戻します

## 注意点

- `float` と `double` を混在させず、初期パラメータと説明変数には同じ型を使用してください。
- `actual_value` と `true_value_labels` は、`rls_vel<T>` の `T` と同じ型を使用してください。
- `initial_covariance` は正の値を指定してください。
- 推定器はスレッドセーフではありません。
