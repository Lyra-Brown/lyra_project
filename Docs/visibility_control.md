# シンボル公開制御

対象ファイル:

- [`visibility_control.h`](../lyra_lib/include/lyra_lib/visibility_control.h)

## 目的

共有ライブラリ（Linux の `.so`、Windows の `.dll`）から、外部へ公開するクラスや関数を指定するためのマクロを定義しています。

## 主なマクロ

- `LYRA_LIB_PUBLIC`: 外部から利用するクラスや関数
- `LYRA_LIB_PUBLIC_TYPE`: 外部から利用する enum などの型
- `LYRA_LIB_LOCAL`: ライブラリ内部だけで使う実装
- `LYRA_LIB_EXPORT` / `LYRA_LIB_IMPORT`: プラットフォームごとの公開・インポート指定

使用例:

```cpp
class LYRA_LIB_PUBLIC Controller
{
};

enum class LYRA_LIB_PUBLIC_TYPE Mode
{
    DEFAULT
};
```

## プラットフォームごとの動作

Windows では、ライブラリをビルドするときに `LYRA_LIB_BUILDING_LIBRARY` が定義されていると `dllexport` 相当、利用側では `dllimport` 相当になります。

GCC 系の環境では、公開シンボルに `visibility("default")`、内部シンボルに `visibility("hidden")` を指定します。GCC 4 未満では空のマクロになります。

公開ヘッダの型・関数にマクロを付けることで、不要なシンボルの公開を抑え、ライブラリの API 境界を明確にできます。
