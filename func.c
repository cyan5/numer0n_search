/* func.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "call.h"

extern int CAND_T[SIZE*DI];

node_t* node_create(
    int depth, 
    int call[DI], 
    int call_hist[HIST*DI], 
    int parent_type, 
    int cand_len, 
    int cand_lst[SIZE*DI]){

    // メモリの動的確保
    node_t *ptr = (node_t*)malloc(sizeof(node_t));
    if(ptr == NULL){
        fprintf(stderr, "memory allocation error.\n");
        exit(1);
    }

    // 引数データの格納
    ptr->depth = depth;
    for(int i=0; i<depth*DI; i++){
        ptr->call_hist[i] = call_hist[i];
    }
    for(int i=0; i<DI; i++){
        ptr->call_hist[depth*DI+i] = call[i];
    }
    ptr->type = node_settype(call, depth, call_hist, parent_type);
    ptr->cand_len = cand_len;
    for(int i=0; i<cand_len*DI; i++){
        ptr->cand_lst[i] = cand_lst[i];
    }

    // 固定データの格納
    ptr->score = -1;
    ptr->var = -1;
    ptr->next = NULL;
    ptr->judge_len = 0;
    ptr->head = NULL;
    ptr->tail = NULL;

    // 次の質問候補リストを作成
    node_setcall(ptr);

    // ジャッジリストを作成
    int judge, flag = 1;
    judge_t *tmp, *new;

    // ジャッジが既に存在するか探索
    for(int i=0; i<ptr->cand_len; i++){

        tmp = ptr->head;
        judge = node_setjudge(call, &cand_lst[i]);

        flag = 1;
        while(tmp != NULL){

            // 見つかったとき
            if(tmp->judge == judge){
                flag = 0;
                for(int j=0; j<DI; j++){
                    tmp->cand_lst[tmp->cand_len*DI+j] = cand_lst[i+j];
                }
                break;
            }else{
                tmp = tmp->next;
            }
        }

        // 見つからなかったとき
        if(flag){
            ptr->judge_len++;
            new = judge_create(judge);
            node_push(ptr, new);
        }
    }

    return ptr;
}

int node_settype(int call[3], int depth, int call_hist[3], int parent_type){

    int type = parent_type;
    if(type != DV){
        for(int i=0; i<depth; i++){
            type = calc_type(call, &call_hist[depth*DI], parent_type);
            if(type == DV){
                break;
            }
        }
    }

    return type;
// void node_settype(int depth, int call_hist[HIST*DI]){
//     if(ptr->type){
//         for(int i=0; i<depth; i++){
//             ptr->type = calc_type(&ptr->call_hist[ptr->depth*3], &ptr->call_hist[i*3], ptr->type);
//             if(ptr->type == DV){
//                 break;
//             }
//         }
//     }
// }
}

void node_setcall(node_t *ptr){

    hash *h_lst = NULL;
    int idx_lst[HIST];
    int flag_zero;

    int idx = 0;
    for(int i=0; i<SIZE; i++){

        flag_zero = 1;
        for(int j=0; j<=ptr->depth; j++){
            idx_lst[j] = calc_idx(&CAND_T[i*3], &ptr->call_hist[j*3], ptr->type);
            if(idx_lst[j] == 0){
                flag_zero = 0;
                break;
            }
        }

        if(flag_zero && hash_search(h_lst, idx_lst, ptr->depth)){
            hash_push(&h_lst, idx_lst);
            ptr->call_lst[idx*3  ] = CAND_T[i*3  ];
            ptr->call_lst[idx*3+1] = CAND_T[i*3+1];
            ptr->call_lst[idx*3+2] = CAND_T[i*3+2];
            idx++;
        }
    }

    ptr->call_len = idx;
    printf("%d\n", idx);
    hash_clear(&h_lst);
}

int node_setjudge(int call[3], int cand[3]){
    int eat = 0, bite = 0;
    if(call[0] == cand[0]){eat++;}
    if(call[0] == cand[1]){bite++;}
    if(call[0] == cand[2]){bite++;}
    if(call[1] == cand[0]){bite++;}
    if(call[1] == cand[1]){eat++;}
    if(call[1] == cand[2]){bite++;}
    if(call[2] == cand[0]){bite++;}
    if(call[2] == cand[1]){bite++;}
    if(call[2] == cand[2]){eat++;}

    return judge_enum(eat, bite);
}

int judge_enum(int eat, int bite){

    int score;
    if(      eat == 0){
        if(      bite == 0){
            score = J0_0;
        }else if(bite == 1){
            score = J0_1;
        }else if(bite == 2){
            score = J0_2;
        }else if(bite == 3){
            score = J0_3;
        }else{
            fprintf(stderr, "judgement error\n");
            exit(1);
        }
    }else if(eat == 1){
        if(      bite == 0){
            score = J1_0;
        }else if(bite == 1){
            score = J1_1;
        }else if(bite == 2){
            score = J1_2;
        }else{
            fprintf(stderr, "judgement error\n");
            exit(1);
        }
    }else if(eat == 2){
        if(bite == 0){
            score = J2_0;
        }else{
            fprintf(stderr, "judgement error\n");
            exit(1);
        }
    }else if(eat == 3){
        if(bite == 0){
            score = J3_0;
        }else{
            fprintf(stderr, "judgement error\n");
            exit(1);
        }
    }else{
        fprintf(stderr, "judgement error\n");
        exit(1);
    }

    return score;
}

// ジャッジリスト作成関数をここにつくる

judge_t* judge_create(int judge){

    // メモリの動的確保
    judge_t *new = (judge_t*)malloc(sizeof(judge_t));
    if(new == NULL){
        fprintf(stderr, "memory allocation error.\n");
        exit(1);
    }

    // 引数データの格納
    new->judge = judge;

    // 固定データの格納
    new->next = NULL;
    new->cand_len = 0;
    new->head = NULL;
    new->tail = NULL;

    // cand_lstの格納

    return new;
}

void node_push(node_t *ptr, judge_t *child){

    if(ptr->head == NULL){
        ptr->head = child;
    }else{
        ptr->tail->next = child;
    }
    ptr->tail = child;
}

void judge_push(judge_t *ptr, node_t *child){

    if(ptr->head == NULL){
        ptr->head = child;
    }else{
        ptr->tail->next = child;
    }
    ptr->tail = child;
}

void node_print(node_t *ptr){
    printf("depth   \t= %d\n", ptr->depth);
    printf("call_hist[%d] \t= [", ptr->depth+1);
    for(int i=0; i<=ptr->depth; i++){
        printf("%d%d%d", ptr->call_hist[i*3], ptr->call_hist[i*3+1], ptr->call_hist[i*3+2]);
        if(i != ptr->depth){printf(" ");}
    }
    printf("]\n");
    printf("cand_lst[%d] \t= [", ptr->cand_len);
    for(int i=0; i<ptr->cand_len; i++){
        printf("%d%d%d", ptr->cand_lst[i*3], ptr->cand_lst[i*3+1], ptr->cand_lst[i*3+2]);
        if(i >= 20){
            printf(" ... ");
            break;
        }else if(i != ptr->cand_len-1){
            printf(" ");
        }
    }
    printf("]\n");
    printf("call_lst[%d] \t= [", ptr->call_len);
    for(int i=0; i<ptr->call_len; i++){
        printf("%d%d%d", ptr->call_lst[i*3], ptr->call_lst[i*3+1], ptr->call_lst[i*3+2]);
        if(i >= 20){
            printf(" ... ");
            break;
        }else if(i != ptr->call_len-1){
            printf(" ");
        }
    }
    printf("]\n");
    
    int count = 0;
    judge_t *judge_ptr = ptr->head;
    while(judge_ptr != NULL){
        printf("%d\n", judge_ptr->judge);
        judge_ptr = judge_ptr->next;
        count++;
    }
    printf("count = %d\n", count);

}
