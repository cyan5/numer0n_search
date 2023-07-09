/* func.h
 * cyan5   */

#ifndef FUNC
#define FUNC

#include "symbol.h"

/* ノードを生成する
 * メモリ動的確保、引数初期化、ジャッジ結果格納
 * ジャッジメモリ動的確保
 * */
node_t* node_create(
    int depth, 
    int call[DI], 
    int call_hist[HIST*DI], 
    int parent_type, 
    list_t *cand_lst
);

// 質問、質問履歴のペアからタイプを決定する
int node_settype(int call[DI], int depth, int call_hist[HIST*DI], int parent_type);

// 次の質問を格納する
void node_setcall(node_t *ptr);

// ジャッジリストを作成
void node_edgelst(node_t *ptr);

// 質問と解答のペアをジャッジする
int node_setjudge(int call[DI], int cand[DI]);

// ジャッジ結果をenumに変換する
int judge_enum(int eat, int bite);

/* ジャッジノードを作成する
 * メモリ動的確保等
 * */
edge_t* edge_create(int judge, int cand[DI]);

// ノードにジャッジをプッシュして木構造にする
void node_push(node_t *ptr, edge_t *child);

// ジャッジにノードをプッシュして木構造にする
void edge_push(edge_t *ptr, node_t *child);

// list_t型マネージャ
list_t* list_init(void);
// unit_t型リストマネージャ
unit_t* unit_init(int num[DI]);

// void list_push(unit_t **head, unit_t **tail, unit_t *ptr);
void list_push(list_t *lst, unit_t *unit);

void list_clear(list_t *ptr);

// // 探索木のメモリを解放する
void node_clear(node_t *ptr);
void branch_clear(edge_t *ptr);

#endif