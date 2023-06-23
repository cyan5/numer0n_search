# numer0n-search
numer0n search project
numer0n戦略全探索プロジェクト
最強質問戦略を作るためにc言語を用いて質問候補の探索を行う。

### コマンド一覧
Linux環境推奨
* `make queue` キューを使った探索（`make`のみで実行可）
* `make stack` スタックを使った探索
* `./a.out` プログラムの実行
* `make clean` 一時ファイルと実行ファイルの削除

### 更新履歴


### 改善履歴
* 展開ノード数削減

| 更新内容   | depth 2 | depth 3 | depth 4 |
| ---------- | ------- | ------- | ------- |
| 最初のファイル                 | 11308 | (400k over) | (400k over) |
| 解答を絞り込めない質問を枝刈り | 11123 | (400k over) | (400k over) |