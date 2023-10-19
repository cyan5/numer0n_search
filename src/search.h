/* search.h
 * cyan5   */

#ifndef SEARCH
#define SEARCH

#include "symbol.h"
#include "data.h"

void create_tree(queue_t *queue, int depth, int seq);
/**
 * 深さdepthからdepth + seqまでのtreeを作成する関数
 * queueはfetch_tree関数で得たqueueを渡す
 * depth(深さ、相対値ではなく絶対値)を渡す
 */

void eval_tree(queue_t *queue, int seq);
/**
 * queueにあるノードを評価する
 * 暫定的な評価なのか確定の評価なのかがわかるように
 * evaluatedフラグを操作する
 */

queue_t* fetch_tree(queue_t *queue, node_t *root, int depth);
/**
 * 指定のdepthのノードをキューに格納してreturnする関数
 * queue型以外の指定は不可能
 */

#endif
