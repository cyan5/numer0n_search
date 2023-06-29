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
    lst_t *cand_lst
);

// 質問、質問履歴のペアからタイプを決定する
int node_settype(int call[DI], int depth, int call_hist[HIST*DI], int parent_type);

// 次の質問を格納する
void node_setcall(node_t *ptr);

// ジャッジリストを作成
void node_judgelst(node_t *ptr);

// 質問と解答のペアをジャッジする
int node_setjudge(int call[3], int cand[3]);

// ジャッジ結果をenumに変換する
int judge_enum(int eat, int bite);

/* ジャッジノードを作成する
 * メモリ動的確保等
 * */
judge_t* judge_create(int judge, int cand[DI]);

// ノードにジャッジをプッシュして木構造にする
void node_push(node_t *ptr, judge_t *child);

// ジャッジにノードをプッシュして木構造にする
void judge_push(judge_t *ptr, node_t *child);

// lst_t型マネージャ
lst_t* lst_init(void);
// num_t型リストマネージャ
num_t* num_init(int num[DI]);

// void lst_push(num_t **head, num_t **tail, num_t *ptr);
void lst_push(lst_t *lst, num_t *num);

void lst_clear(lst_t *ptr);

// // 探索木のメモリを解放する
void node_clear(node_t *ptr);
void branch_clear(judge_t *ptr);

#endif