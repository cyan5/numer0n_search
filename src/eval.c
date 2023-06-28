/* eval.c
 * cyan5   */

#include <stdlib.h>
#include <float.h>
#include "eval.h"

#define SQ(x) ((x)*(x))

void node_eval(node_t *ptr, int depth){

    judge_t *tmp = ptr->head;
    double sum = 0;

    while(tmp != NULL){

        if(depth == 1){
            sum += SQ(tmp->cand_len);
        }else{
            judge_eval(tmp, depth);
            sum += SQ(tmp->score);
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
    }else if(ptr->cand_len == 1){
        ptr->score = 1;
    }else if(ptr->cand_len == 2){
        ptr->score = 1.5;
    }else{
        while(tmp != NULL){
            node_eval(tmp, depth-1);
            if(tmp->score < min){
                min = tmp->score;
            }
            tmp = tmp->next;
        }

        ptr->score = min;
    }
}
