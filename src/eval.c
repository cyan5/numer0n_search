/* eval.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "eval.h"
#include "data.h"

#include "print.h"

#define SQ(x) ((x)*(x))

void node_eval(node_t *node, int depth){
    /**
     * node_evalとedge_evalを交互に呼び出す再帰関数
     * node_evalではedge_evalの
    */

    double sum = 0;

    for(edge_t *edge=node->head; edge!=NULL; edge=edge->next){
        if(depth == 0){
            sum += SQ(edge->cand_lst->len);
        }else{
            edge_eval(edge, depth);
            sum += edge->cand_lst->len * edge->score;
        }
    }

    node->score = 1 + sum / node->cand_lst->len;
}

void edge_eval(edge_t *edge, int depth){

    if(edge->judge == J3_0){
        edge->evaluated = 1;
        edge->score = 0;
    }else if(edge->cand_lst->len == 1){
        edge->evaluated = 1;
        edge->score = 1;
    }else if(edge->cand_lst->len == 2){
        edge->evaluated = 1;
        edge->score = 1.5;
    }else if(edge->head == NULL){
        edge->evaluated = 1;
        edge->score = DBL_MAX;
    }else if(depth == 0){
        edge->score = edge->cand_lst->len;
    }else{

        for(node_t *node=edge->head; node!=NULL; node=node->next){
            node_eval(node, depth-1);
        }

        node_sort(edge);
        edge->score = edge->head->score;
    }
}

void node_sort(edge_t *edge){
    /**
     * edge_tからnode_tポインタをスタックに移す
     * insertion sortでedge_tに付け替える
    */

    node_t *node_pop;
    stack_t *stack = stack_init();

    // スタックに全てプッシュ
    for(node_t *node=edge->head; node!=NULL; node=node->next){
        stack_push(stack, node);
    }
    edge->head = NULL;

    // スタックのノードを全て取り出す
    while(stack->len != 0){

        // ポップし、一度nextポインタをNULLにする
        node_pop = stack_pop(stack);
        node_pop->next = NULL;

        if(edge->head == NULL){
            // 空の場合
            node_pop->next = NULL;
            edge->head = node_pop;
            edge->tail = node_pop;
        }else if(isbetter(node_pop, edge->head, 0)){
            // 先頭に挿入する場合
            node_pop->next = edge->head;
            edge->head = node_pop;
        }else{
            // 先頭以外に挿入される場合
            for(node_t *node=edge->head; node!=NULL; node=node->next){

                // 最後まで比較したとき
                if(node->next == NULL){
                    node_pop->next = NULL;
                    node->next = node_pop;
                    edge->tail = node_pop;
                    break;
                }
                // 場所が見つかったとき
                if(isbetter(node_pop, node->next, 0)){
                    node_pop->next = node->next;
                    node->next = node_pop;
                    break;
                }
            }
        }
    }
    stack_clear(stack);
}

int isbetter(node_t *ptr_x, node_t *ptr_y, int cmprule){

    // check();
    
    int flag;
    // score
    if      (ptr_x->score < ptr_y->score){
        flag = 1;
    }else if(ptr_x->score > ptr_y->score){
        flag = 0;
    }else{
        // var
        if      (ptr_x->var < ptr_y->var){
            flag = 1;
        }else if(ptr_x->var > ptr_y->var){
            flag = 0;
        }else{
            // call_hist[DI*depth]
            if      (ptr_x->call_hist[ptr_x->depth*DI] < 
                     ptr_y->call_hist[ptr_y->depth*DI]){
                flag = 1;
            }else if(ptr_x->call_hist[ptr_x->depth*DI] > 
                     ptr_y->call_hist[ptr_y->depth*DI]){
                flag = 0;
            }else{
                // call_hist[DI*depth+1]
                if      (ptr_x->call_hist[ptr_x->depth*DI+1] < 
                        ptr_y->call_hist[ptr_y->depth*DI+1]){
                    flag = 1;
                }else if(ptr_x->call_hist[ptr_x->depth*DI+1] > 
                        ptr_y->call_hist[ptr_y->depth*DI+1]){
                    flag = 0;
                }else{
                    // call_hist[DI*depth+2]
                    if      (ptr_x->call_hist[ptr_x->depth*DI+2] < 
                            ptr_y->call_hist[ptr_y->depth*DI+2]){
                        flag = 1;
                    }else if(ptr_x->call_hist[ptr_x->depth*DI+2] > 
                            ptr_y->call_hist[ptr_y->depth*DI+2]){
                        flag = 0;
                    }else{
                        printf("%lf, %lf\n", ptr_x->score, ptr_y->score);
                        printf("%d%d%d %d%d%d\n", 
                        ptr_x->call_hist[ptr_x->depth*DI], 
                        ptr_x->call_hist[ptr_x->depth*DI+1], 
                        ptr_x->call_hist[ptr_x->depth*DI+2], 
                        ptr_y->call_hist[ptr_y->depth*DI], 
                        ptr_y->call_hist[ptr_y->depth*DI+1], 
                        ptr_y->call_hist[ptr_y->depth*DI+2]
                        );
                        fprintf(stderr, "comp error\n");
                        exit(1);
                    }
                }
            }
        }
    }

    return flag;
}
