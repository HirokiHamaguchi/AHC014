# Index

- [Index](#index)
  - [Usage](#usage)
    - [Requirements](#requirements)
    - [Input Generation](#input-generation)
    - [Visualization](#visualization)
  - [使い方](#使い方)
    - [実行環境](#実行環境)
    - [入力生成](#入力生成)
    - [ビジュアライザ](#ビジュアライザ)

## Usage

### Requirements

Please install a compiler for Rust language (see <https://www.rust-lang.org>).
If a compile error occurs, the compiler version may be old.
You can update to the latest compiler by executing the following command.

```bash
rustup update
```

For those who are not familiar with the Rust language environment, we have prepared a [pre-compiled binary for Windows](https://img.atcoder.jp/ahc014/a3c240f5b1_windows.zip).
The following examples assume that you will be working in the directory where this README is located.

### Input Generation

The `in` directory contains pre-generated input files for seed=0-99.
If you want more inputs, prepare `seeds.txt` which contains a list of random seeds (unsigned 64bit integers) and execute the following command.

```bash
cargo run --release --bin gen seeds.txt
```

When using the precompiled binary for Windows,

```bash
./gen.exe seeds.txt
```

This will output input files into `in` directory.

By putting two numbers $n$ $m$ at the end of the command, the values of $N$ and $M$ in the generated input can be fixed to $n$ and $m$, respectively.
For example, the following command generates inputs with $N=33$ and $M=58$.

```bash
cargo run --release --bin gen seeds.txt 33 58
```

To fix only one of $N$ and $M$, set the value of the other to 0.

### Visualization

Let `in.txt` be an input file and `out.txt` be an output file.
You can visualize the output by executing the following command.

```bash
cargo run --release --bin vis in.txt out.txt
```

When using the precompiled binary for Windows,

```bash
./vis.exe in.txt out.txt
```

The above command writes a visualization result to `vis.html`.
It also outputs the score to standard output.

You can also use a [web visualizer](https://img.atcoder.jp/ahc014/a3c240f5b1.html?lang=en) which is more rich in features.

## 使い方

### 実行環境

Rust言語のコンパイル環境が必要です。
<https://www.rust-lang.org/ja> を参考に各自インストールして下さい。
コンパイルエラーになった場合、コンパイラのバージョンが古い可能性があります。
以下のコマンド実行することで最新のコンパイラに更新が可能です。

```bash
rustup update
```

Rust言語の環境構築が面倒な方向けに、[Windows用のコンパイル済みバイナリ](https://img.atcoder.jp/ahc014/a3c240f5b1_windows.zip)も用意してあります。
以下の実行例では、このREADMEが置かれているディレクトリに移動して作業することを想定しています。

### 入力生成

`in` ディレクトリに予め生成された seed=0~99 に対する入力ファイルが置かれています。
より多くの入力が欲しい場合は、`seeds.txt` に欲しい入力ファイルの数だけ乱数seed値(符号なし64bit整数値)を記入し、以下のコマンドを実行します。

```bash
cargo run --release --bin gen seeds.txt
```

Windows用のコンパイル済バイナリを使用する場合は以下のようにします。

```bash
./gen.exe seeds.txt
```

生成された入力ファイルは `in` ディレクトリに出力されます。

コマンドの末尾に2つの数字 $n$ $m$ を続けることで、生成する入力の $N$ と $M$ の値をそれぞれ $n$、$m$ に固定することが出来ます。
例えば以下のように実行すると、$N=33$、$M=58$ の入力が生成されます。

```bash
cargo run --release --bin gen seeds.txt 33 58
```

片方のみを固定したい場合は他方の値を 0 として実行します。

### ビジュアライザ

入力ファイル名を`in.txt`、出力ファイル名を`out.txt`としたとき、以下のコマンドを実行します。

```bash
cargo run --release --bin vis in.txt out.txt
```

Windows用のコンパイル済バイナリを使用する場合は以下のようにします。

```bash
./vis.exe in.txt out.txt
```

出力のビジュアライズ結果は `vis.html` というファイルに書き出されます。
標準出力にはスコアを出力します。

より機能が豊富な[ウェブ版のビジュアライザ](https://img.atcoder.jp/ahc014/a3c240f5b1.html?lang=ja)も利用可能です。
