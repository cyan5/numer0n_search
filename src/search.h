/* search.h
 * cyan5   */

#ifndef SEARCH
#define SEARCH

#include "symbol.h"
#include "data.h"

void create_tree(queue_t *queue, int depth);

// void eval_tree(node_t *root, int depth);


queue_t* fetch_tree(queue_t *queue, node_t *root, int depth);
/**
 * 指定のdepthのノードをキューに格納してreturnする関数
 * queue型以外の指定は不可能
 */

#endif
