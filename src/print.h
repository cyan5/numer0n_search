/* func.h
 * cyan5   */

#ifndef PRINT
#define PRINT

#include "symbol.h"

/* ノードを確認する関数 */
void node_print(node_t *ptr);

// 探索木を出力する
void tree_print(node_t *ptr);
void branch_print(edge_t *ptr, int depth);
// enumを参照しジャッジを出力する
void judge_print(int judge);

// 探索木をファイル出力する
void tree_fprint(FILE *fp, node_t *root);
void branch_fprint(FILE *fp, edge_t *root, int depth);
// enumを参照しジャッジをファイル出力する
void judge_fprint(FILE *fp, int judge);


#endif