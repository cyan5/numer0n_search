/* search.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "data.h"
#include "func.h"

void create_tree(queue_t *queue, int depth){
    /**
     * depthは相対値ではなく絶対値
     * depth = 0ならdepth=0(012のedge)まで作成する
     * depth = 1なら(013-345のedge)まで作成する
     */

    node_t *node_pop, *node_new;

    while(queue->len != 0){
        node_pop = queue_pop(queue);
        queue_print(queue);

        if(node_pop->evaluated){
            // 評価済み
            // no process
        }else{
            // 未評価
            // エッジポインタを作成
            for(edge_t *edge=node_pop->head; edge!=NULL; edge=edge->next){

                // エッジの候補長だけループ
                for(unit_t *unit=node_pop->call_lst->head; unit!=NULL; unit=unit->next){

                    // ノードを作らない条件
                    if(edge->cand_lst->len <= 2){
                        // check();
                    }else if(node_pop->depth >= depth){
                        // check();
                    }else{  // ノード作成

                        node_new = node_create(
                            node_pop->depth+1,
                            unit->data, 
                            node_pop->call_hist, 
                            node_pop->type, 
                            edge->cand_lst
                        );

                        if(node_new->cand_lst->len == node_pop->cand_lst->len){
                            node_clear(node_new);
                        }else{
                            edge_push(edge, node_new);
                            queue_push(queue, node_new);
                        }
                    }
                }
            }
        }
    }
}

queue_t* fetch_tree(queue_t *queue, node_t *root, int depth){
    /**
     * 空のキューを受け取る
     * ルートをキューにプッシュ
     * 子ノードをプッシュしていく
     * 先頭ポインタがdepthと同じになったらbreak
     */

    if(queue->len != 0){
        fprintf(stderr, "debug queue not empty.\n");
        exit(1);
    }

    queue_push(queue, root);
    node_t *node_pop;
    while(queue->head->ptr->depth != depth){

        // ポップ
        node_pop = queue_pop(queue);

        // 子ノードをキューにプッシュ
        for(edge_t *edge=node_pop->head; edge!=NULL; edge=edge->next){
            for(node_t *node=edge->head; node!=NULL; node=node->next){
                queue_push(queue, node);
            }
        }
    }

    return queue;
}
