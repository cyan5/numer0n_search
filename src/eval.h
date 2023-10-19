/* eval.h
 * cy_an   */

#ifndef EVAL
#define EVAL

#include "symbol.h"

void node_eval(node_t *ptr, int seq);
void edge_eval(edge_t *ptr, int seq);
/**
 * 再帰呼び出しによってノードに評価値をつける関数
 * 
 */

void node_sort(edge_t *ptr);
/**
 * edge_tの下の階層のnode_tを評価値順にソートする
 * 要素数が少ないためinsertion sortで十分
 */

int isbetter(node_t *ptr_x, node_t *ptr_y, int cmprule);
/**
 * ptr_xがptr_yよりも良いとき1, 悪いとき0を返す
 * cmpruleは比較ルール:
 * 0 : score, var, digit の順
 * 1 : 未実装
 */

#endif
