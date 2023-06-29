/* eval.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "eval.h"
#include "data.h"

#include "print.h"

#define SQ(x) ((x)*(x))

void node_eval(node_t *ptr, int depth){
    /**
     * node_evalとjudge_evalを交互に呼び出す再帰関数
     * node_evalではjudge_evalの
    */

    judge_t *tmp = ptr->head;
    double sum = 0;

    while(tmp != NULL){
        if(depth == 0){
            // sum += SQ(tmp->cand_len);
            sum += SQ(tmp->cand_lst->len);
        }else{
            // debug
            // printf("check\n");
            judge_eval(tmp, depth);
            printf("judge finish\n");
            sum += tmp->cand_lst->len * tmp->score;
        }

        tmp = tmp->next;
    }

    ptr->score = 1 + sum / ptr->cand_len;
}

void judge_eval(judge_t *ptr, int depth){

    node_t *tmp = ptr->head;
    double min = DBL_MAX;

    if(ptr->judge == J3_0){
        ptr->score = 0;
    }else if(ptr->cand_lst->len == 1){
    // }else if(ptr->cand_len == 1){
        ptr->score = 1;
    }else if(ptr->cand_lst->len == 2){
        ptr->score = 1.5;
    }else{

        // WIP
        // 並べ替えをして先頭のスコアを取得するように変更
        // ついでに評価値の悪いものは探索を行わないようにする

        // while(tmp != NULL){
        //     node_eval(tmp, depth-1);
        //     tmp = tmp->next;
        // }
        // printf("%d\n", ptr->cand_len);

        // if(tmp != NULL){
        //     node_sort(ptr);
        //     ptr->score = ptr->head->score;
        // }else{
        //     ptr->score = DBL_MAX;
        // }

        while(tmp != NULL){
            node_eval(tmp, depth-1);
            printf("node finish\n");
            if(tmp->score < min){
                min = tmp->score;
            }
            tmp = tmp->next;
        }
        ptr->score = min;


    }
}

void node_sort(judge_t *ptr){
    /**
     * judge_t からnode_tポインタをスタックに移す
     * insertion sortでjudge_tに付け替える
    */

    // branch_print(ptr, 0);
    if(ptr->head == NULL){
        printf("NULL\n");
    }

    node_t *ptr_now, *ptr_next, *ptr_idx;

    // スタックに全てプッシュ
    stk *stack = stack_init();
    ptr_now = ptr->head;
    while(ptr_now != NULL){
        ptr_next = ptr_now->next;
        ptr_now->next = NULL;
        stack_push(stack, ptr_now);
        ptr_now = ptr_next;
    }

    // 挿入ソートで並べ替え
    // 最初のノード
    ptr_now = stack_pop(stack);
    // breakpoint();
    ptr->head = ptr_now;
    // 2個目以降のノード
    while(stack->len != 0){
        ptr_now = stack_pop(stack);
        // 先頭のとき
        if(isbetter(ptr_now, ptr->head, 0)){
            ptr_now->next = ptr->head;
            ptr->head = ptr_now;
        }else{ // 先頭ではないとき
            ptr_idx = ptr->head;
            while(1){
                if(ptr_idx->next == NULL){
                    ptr_idx->next = ptr_now;
                    break;
                }else if(isbetter(ptr_now, ptr_idx->next, 0)){
                    ptr_idx->next = ptr_now;
                    break;
                }else{
                    ptr_idx = ptr_idx->next;
                    break;
                }
            }
        }
    }

    stack_clear(stack);
}

int isbetter(node_t *ptr_x, node_t *ptr_y, int cmprule){
    
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
