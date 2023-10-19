/* cand_func.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "call.h"

int calc_idx(int cand[DI], int call_hist[DI], int type){

    int score;
    if(cand[0] == call_hist[0]){
        if(cand[1] == call_hist[1]){
            if(cand[2] == call_hist[2]){        /* 012 */
                score = 0;
            }else{                              /* 013 */
                score = 1;
            }
        }else if(cand[1] == call_hist[2]){
            if(cand[2] == call_hist[1]){        /* 021 */
                score = 2;
            }else{                              /* 023 */
                score = 3;
            }
        }else{
            if(cand[2] == call_hist[1]){        /* 031 */
                if(type == NU || type == MR){
                    score = 3;
                }else{
                    score = 4;
                }
            }else if(cand[2] == call_hist[2]){  /* 032 */
                if(type == NU || type == MR){
                    score = 1;
                }else{
                    score = 5;
                }
            }else{                              /* 034 */
                score = 6;
            }
        }
    }else if(cand[0] == call_hist[1]){
        if(cand[1] == call_hist[0]){
            if(cand[2] == call_hist[2]){        /* 102 */
                if(type == NU || type == LR){
                    score = 2;
                }else{
                    score = 7;
                }
            }else{                              /* 103 */
                score = 8;
            }
        }else if(cand[1] == call_hist[2]){
            if(cand[2] == call_hist[0]){        /* 120 */
                score = 9;
            }else{                              /* 123 */
                score = 10;
            }
        }else{
            if(cand[2] == call_hist[0]){        /* 130 */
                if(type == NU){
                    score = 10;
                }else{
                    score = 11;
                }
            }else if(cand[2] == call_hist[2]){  /* 132 */
                if(type == NU){
                    score = 3;
                }else if(type == LR){
                    score = 4;
                }else{
                    score = 12;
                }
            }else{                              /* 134 */
                score = 13;
            }
        }
    }else if(cand[0] == call_hist[2]){
        if(cand[1] == call_hist[0]){
            if(cand[2] == call_hist[1]){        /* 201 */
                if(type == NU){
                    score = 9;
                }else{
                    score = 14;
                }
            }else{                              /* 203 */
                if(type == NU || type == LM){
                    score = 10;
                }else if(type == MR){
                    score = 11;
                }else{
                    score = 15;
                }
            }
        }else if(cand[1] == call_hist[1]){
            if(cand[2] == call_hist[0]){        /* 210 */
                if(type == NU || type == LM){
                    score = 2;
                }else if(type == MR){
                    score = 7;
                }else{
                    score = 16;
                }
            }else{                              /* 213 */
                if(type == NU || type == LM){
                    score = 3;
                }else if(type == MR){
                    score = 12;
                }else{
                    score = 17;
                }
            }
        }else{
            if(cand[2] == call_hist[0]){        /* 230 */
                if(type == NU || type == MR){
                    score = 8;
                }else{
                    score = 18;
                }
            }else if(cand[2] == call_hist[1]){  /* 231 */
                if(type == NU || type == MR){
                    score = 10;
                }else if(type == LR){
                    score = 11;
                }else{
                    score = 19;
                }
            }else{                              /* 234 */
                if(type == NU || type == MR){
                    score = 13;
                }else{
                    score = 20;
                }
            }
        }
    }else{
        if(cand[1] == call_hist[0]){
            if(cand[2] == call_hist[1]){        /* 301 */
                if(type == NU || type == LR){
                    score = 10;
                }else if(type == LM){
                    score = 11;
                }else{
                    score = 21;
                }
            }else if(cand[2] == call_hist[2]){  /* 302 */
                if(type == NU || type == LR){
                    score = 3;
                }else if(type == LM){
                    score = 12;
                }else{
                    score = 22;
                }
            }else{                              /* 304 */
                if(type == NU || type == LM){
                    score = 13;
                }else{
                    score = 23;
                }
            }
        }else if(cand[1] == call_hist[1]){
            if(cand[2] == call_hist[0]){        /* 310 */
                if(type == NU){
                    score = 3;
                }else if(type == LM){
                    score = 4;
                }else if(type == LR){
                    score = 17;
                }else if(type == MR){
                    score = 22;
                }else{
                    score = 24;
                }
            }else if(cand[2] == call_hist[2]){  /* 312 */
                if(type == NU || type == LR){
                    score = 1;
                }else if(type == LM){
                    score = 5;
                }else{
                    score = 25;
                }
            }else{                              /* 314 */
                if(type == NU || type == LM){
                    score = 6;
                }else{
                    score = 26;
                }
            }
        }else if(cand[1] == call_hist[2]){
            if(cand[2] == call_hist[0]){        /* 320 */
                if(type == NU){
                    score = 10;
                }else if(type == LM){
                    score = 19;
                }else if(type == LR){
                    score = 15;
                }else if(type == MR){
                    score = 21;
                }else{
                    score = 27;
                }
            }else if(cand[2] == call_hist[1]){  /* 321 */
                if(type == NU || type == LR){
                    score = 8;
                }else if(type == LM){
                    score = 18;
                }else{
                    score = 28;
                }
            }else{                              /* 324 */
                if(type == NU){
                    score = 13;
                }else if(type == LM){
                    score = 20;
                }else if(type == LR){
                    score = 23;
                }else{
                    score = 29;
                }
            }
        }else{
            if(cand[2] == call_hist[0]){        /* 340 */
                if(type == NU){
                    score = 13;
                }else if(type == LR){
                    score = 20;
                }else if(type == MR){
                    score = 23;
                }else{
                    score = 30;
                }
            }else if(cand[2] == call_hist[1]){  /* 341 */
                if(type == NU){
                    score = 13;
                }else if(type == LM){
                    score = 30;
                }else if(type == LR){
                    score = 13;
                }else if(type == MR){
                    score = 29;
                }else{
                    score = 31;
                }
            }else if(cand[2] == call_hist[2]){  /* 342 */
                if(type == NU || type == LR){
                    score = 6;
                }else if(type == MR){
                    score = 26;
                }else{
                    score = 32;
                }
            }else{                              /* 345 */
                score = 33;
            }
        }
    }
    return score;
}

int calc_type(int call[DI], int call_hist[DI], int parent_type){
    /* 
     * callとcall_histからタイプを判別する。
     * typeがDVの時は関数そのものを呼び出さない。
     * */

    int score;
    if(call[0] == call_hist[0]){
        if(call[1] == call_hist[1]){
            if(call[2] == call_hist[2]){        /* 012 */
                score = NU;
            }else{                              /* 013 */
                score = LM;
            }
        }else if(call[1] == call_hist[2]){
            if(call[2] == call_hist[1]){        /* 021 */
                score = MR;
            }else{                              /* 023 */
                score = DV;
            }
        }else{
            if(call[2] == call_hist[1]){        /* 031 */
                score = DV;
            }else if(call[2] == call_hist[2]){  /* 032 */
                score = LR;
            }else{                              /* 034 */
                score = MR;
            }
        }
    }else if(call[0] == call_hist[1]){
        if(call[1] == call_hist[0]){
            if(call[2] == call_hist[2]){        /* 102 */
                score = LM;
            }else{                              /* 103 */
                score = LM;
            }
        }else if(call[1] == call_hist[2]){
            if(call[2] == call_hist[0]){        /* 120 */
                score = DV;
            }else{                              /* 123 */
                score = DV;
            }
        }else{
            if(call[2] == call_hist[0]){        /* 130 */
                score = DV;
            }else if(call[2] == call_hist[2]){  /* 132 */
                score = DV;
            }else{                              /* 134 */
                score = DV;
            }
        }
    }else if(call[0] == call_hist[2]){
        if(call[1] == call_hist[0]){
            if(call[2] == call_hist[1]){        /* 201 */
                score = DV;
            }else{                              /* 203 */
                score = DV;
            }
        }else if(call[1] == call_hist[1]){
            if(call[2] == call_hist[0]){        /* 210 */
                score = LR;
            }else{                              /* 213 */
                score = DV;
            }
        }else{
            if(call[2] == call_hist[0]){        /* 230 */
                score = LR;
            }else if(call[2] == call_hist[1]){  /* 231 */
                score = DV;
            }else{                              /* 234 */
                score = DV;
            }
        }
    }else{
        if(call[1] == call_hist[0]){
            if(call[2] == call_hist[1]){        /* 301 */
                score = DV;
            }else if(call[2] == call_hist[2]){  /* 302 */
                score = DV;
            }else{                              /* 304 */
                score = DV;
            }
        }else if(call[1] == call_hist[1]){
            if(call[2] == call_hist[0]){        /* 310 */
                score = DV;
            }else if(call[2] == call_hist[2]){  /* 312 */
                score = MR;
            }else{                              /* 314 */
                score = LR;
            }
        }else if(call[1] == call_hist[2]){
            if(call[2] == call_hist[0]){        /* 320 */
                score = DV;
            }else if(call[2] == call_hist[1]){  /* 321 */
                score = MR;
            }else{                              /* 324 */
                score = DV;
            }
        }else{
            if(call[2] == call_hist[0]){        /* 340 */
                score = DV;
            }else if(call[2] == call_hist[1]){  /* 341 */
                score = DV;
            }else if(call[2] == call_hist[2]){  /* 342 */
                score = LM;
            }else{                              /* 345 */
                score = NU;
            }
        }
    }

    if(parent_type == score){
        return parent_type;
    }else if(parent_type == NU){
        return score;
    }else if(score == NU){
        return parent_type;
    }else if(score == DV){
        return DV;
    }else if(parent_type == LM && score == LR){
        return DV;
    }else if(parent_type == LM && score == MR){
        return DV;
    }else if(parent_type == LR && score == LM){
        return DV;
    }else if(parent_type == LR && score == MR){
        return DV;
    }else if(parent_type == MR && score == LM){
        return DV;
    }else if(parent_type == MR && score == LR){
        return DV;
    }else{
        printf("error case : type=%d, score=%d\n", parent_type, score);
        return DV;
    }
}

int hash_search(hash_t *ptr, int data[HIST], int depth){
    /* 
     * tmpがNULLまで走査したらscore = 1
     * 途中で値が見つかったらscore = 0 を代入してbreakする。
    */

    hash_t *tmp = ptr;   /* 走査するためのポインタ変数    */
    int score;         /* return score                 */
    int flag;          /* 2重ループを抜けるためのフラグ */
    while(1){

        if(tmp == NULL){  /* 終端に達した時、1を代入して終了 */
            score = 1;
            break;
        }else{
            flag = 1;
            /* すべての要素を比較 */
            for(int i=0; i<=depth; i++){
                /* 一致しない要素が見つかった場合 */
                if(tmp->data[i] != data[i]){
                    flag = 0;
                    tmp = tmp->next;
                    break;
                }
            }
            /* すべてが一致する場合 */
            if(flag){
                score = 0;
                break;
            }
        }
    }
    return score;
}

void hash_push(hash_t **ptr, int data[HIST]){

    hash_t *new = (hash_t*)malloc(sizeof(hash_t));
    if(new == NULL){
        fprintf(stderr, "memory allocation error\n");
        exit(1);
    }

    for(int i=0; i<HIST; i++){
        new->data[i] = data[i];
    }
    new->next = *ptr;
    *ptr = new;
}

void hash_clear(hash_t **ptr){
    hash_t *tmp_1 = *ptr, *tmp_2;
    while(tmp_1->next != NULL){
        tmp_2 = tmp_1->next;
        free(tmp_1);
        tmp_1 = tmp_2;
    }
    *ptr = NULL;
}
