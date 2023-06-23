/* func.h
 * cyan5   */

#ifndef PRINT
#define PRINT

#include "symbol.h"

/* ノードを確認する関数 */
void node_print(node_t *ptr);

// 探索木を出力する
void tree_print(node_t *ptr);
void branch_print(judge_t *ptr, int depth);

// 探索木をファイル出力する
void tree_file(node_t *root, FILE *fp);
void branch_file(judge_t *root, int depth, FILE *fp);

// enumを参照しジャッジを出力する
void judge_print(int judge);

#endif