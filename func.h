/* func.h
 * cyan5   */

#ifndef FUNC
#define FUNC

#include "symbol.h"

/* ノードを生成 */
node_t* node_create(
    int depth, 
    int call[DI], 
    int call_hist[HIST*DI], 
    int parent_type, 
    int cand_len, 
    int cand_lst[SIZE*DI]
);

int node_settype(int call[3], int depth, int call_hist[3], int parent_type);

void node_setcall(node_t *ptr);

int node_setjudge(int call[3], int cand[3]);

int judge_enum(int eat, int bite);

judge_t* judge_create(int judge);

void node_push(node_t *ptr, judge_t *child);

void judge_push(judge_t *ptr, node_t *child);

/* ノードを確認する関数 */
void node_print(node_t *ptr);

#endif