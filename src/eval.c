/* eval.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "eval.h"
#include "data.h"

#include "print.h"

#define SQ(x) ((x)*(x))

void node_eval(node_t *node_ptr, int depth){
    /**
     * node_evalとjudge_evalを交互に呼び出す再帰関数
     * node_evalではjudge_evalの
    */

    double sum = 0;

    for(judge_t *judge_ptr=node_ptr->head; judge_ptr!=NULL; judge_ptr=judge_ptr->next){
        if(depth == 0){
            sum += SQ(judge_ptr->cand_lst->len);
        }else{
            judge_eval(judge_ptr, depth);
            sum += judge_ptr->cand_lst->len * judge_ptr->score;
        }
    }

    node_ptr->score = 1 + sum / node_ptr->cand_lst->len;
}

void judge_eval(judge_t *judge_ptr, int depth){

    double min = DBL_MAX;

    if(judge_ptr->judge == J3_0){
        judge_ptr->score = 0;
    }else if(judge_ptr->cand_lst->len == 1){
        judge_ptr->score = 1;
    }else if(judge_ptr->cand_lst->len == 2){
        judge_ptr->score = 1.5;
    }else{

        // WIP
        // 並べ替えをして先頭のスコアを取得するように変更
        // ついでに評価値の悪いものは探索を行わないようにする

        // while(node_ptr != NULL){
        //     node_eval(node_ptr, depth-1);
        //     node_ptr = node_ptr->next;
        // }
        // printf("%d\n", judge_ptr->cand_len);

        // if(node_ptr != NULL){
        //     node_sort(judge_ptr);
        //     judge_ptr->score = judge_ptr->head->score;
        // }else{
        //     judge_ptr->score = DBL_MAX;
        // }

        // node_t *tmp = judge_ptr->head;
        // while(tmp != NULL){
        //     tmp = tmp->next;



        // for(node_t *node_ptr=judge_ptr->head; node_ptr!=NULL; node_ptr=node_ptr->next){
        //     node_eval(node_ptr, depth-1);
        //     if(node_ptr->score < min){
        //         min = node_ptr->score;
        //     }
        // }


        for(node_t *node_ptr=judge_ptr->head; node_ptr!=NULL; node_ptr=node_ptr->next){
            node_eval(node_ptr, depth-1);
            if(node_ptr->score < min){
                min = node_ptr->score;
            }
            // node_sort(judge_ptr);
        }



        judge_ptr->score = min;
    }
}

void node_sort(judge_t *judge_ptr){
    /**
     * judge_t からnode_tポインタをスタックに移す
     * insertion sortでjudge_tに付け替える
    */

    node_t *ptr_now, *ptr_next, *ptr_idx;

    // スタックに全てプッシュ
    stk *stack = stack_init();
    for(node_t *node_ptr=judge_ptr->head; node_ptr!=NULL; node_ptr=node_ptr->next){

        stack_push(stack, node_ptr);
    }
    // ptr_now = judge_ptr->head;
    // while(ptr_now != NULL){
    //     ptr_next = ptr_now->next;
    //     ptr_now->next = NULL;
    //     stack_push(stack, ptr_now);
    //     ptr_now = ptr_next;
    // }

    // 挿入ソートで並べ替え
    // 最初のノード
    ptr_now = stack_pop(stack);
    judge_ptr->head = ptr_now;
    // 2個目以降のノード
    while(stack->len != 0){
        ptr_now = stack_pop(stack);
        // 先頭のとき
        if(isbetter(ptr_now, judge_ptr->head, 0)){
            ptr_now->next = judge_ptr->head;
            judge_ptr->head = ptr_now;
        }else{ // 先頭ではないとき
            ptr_idx = judge_ptr->head;
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
