/* eval.h
 * cy_an   */

#ifndef EVAL
#define EVAL

#include "symbol.h"

// ノードに評価値をつける
void node_eval(node_t *ptr, int depth);
void judge_eval(judge_t *ptr, int depth);

/**
 * judge_tの下の階層のnode_tを評価値順にソートする
 * 要素数が少ないためinsertion sort
 */
void node_sort(judge_t *ptr);

/**
 * ptr_xがptr_yよりも良いとき1, 悪いとき-1
 * 比較優先順位
 * score
 * var
 * call_hist[DI*depth]
 * call_hist[DI*depth+1]
 * call_hist[DI*depth+2]
*/
int isbetter(node_t *ptr_x, node_t *ptr_y, int cmprule);

#endif
