/* eval.h
 * cy_an   */

#ifndef EVAL
#define EVAL

#include "symbol.h"

// ノードに評価値をつける
void node_eval(node_t *ptr, int depth);
void judge_eval(judge_t *ptr, int depth);

#endif
