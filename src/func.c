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
    lst_t *cand_lst
    ){

    node_t *ptr = (node_t*)malloc(sizeof(node_t));
    if(ptr == NULL){
        fprintf(stderr, "memory allocation error.\n");
        exit(1);
    }

    // データの格納
    ptr->depth = depth;
    // call_hist
    for(int i=0; i<depth*DI; i++){
        ptr->call_hist[i] = call_hist[i];
    }
    ptr->call_hist[depth*DI  ] = call[0];
    ptr->call_hist[depth*DI+1] = call[1];
    ptr->call_hist[depth*DI+2] = call[2];
    // type
    ptr->type = node_settype(call, depth, call_hist, parent_type);
    // cand_lst
    ptr->cand_lst = cand_lst;
    // call_lst
    ptr->call_lst = lst_init();
    node_setcall(ptr);

    // その他データの格納
    ptr->score = -1;
    ptr->var = -1;
    ptr->judge_len = 0;
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->next = NULL;

    // ジャッジリストを作成
    node_judgelst(ptr);

    return ptr;
}

int node_settype(int call[DI], int depth, int call_hist[HIST*DI], int parent_type){

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
}

void node_setcall(node_t *ptr){

    hash *h_lst = NULL;    // ハッシュ値リスト
    int idx_lst[HIST];     // 
    int flag_same;         // 同じ質問はしない
    num_t *num_ptr;

    for(int i=0; i<SIZE; i++){
        flag_same = 1;
        for(int j=0; j<=ptr->depth; j++){
            idx_lst[j] = calc_idx(&CAND_T[i*3], &ptr->call_hist[j*3], ptr->type);
            if(idx_lst[j] == 0){   // 同じ質問
                flag_same = 0;
                break;
            }
        }

        if(flag_same && hash_search(h_lst, idx_lst, ptr->depth)){
            hash_push(&h_lst, idx_lst);

            num_ptr = num_init(&CAND_T[i*DI]);
            if(ptr == NULL){
                printf("NULLa\n");
            }
            lst_push(ptr->call_lst, num_ptr);
        }
    }

    hash_clear(&h_lst);
}

void node_judgelst(node_t *node_ptr){

    int judge, flag = 1;
    judge_t *judge_ptr, *new;

    // ノードptrのcand_lstを走査
    num_t *num_ptr_judge;

    // ジャッジが既に存在するか探索
    for(num_t *num_ptr_node = node_ptr->cand_lst->head; num_ptr_node!=NULL; num_ptr_node=num_ptr_node->next){

        judge_ptr = node_ptr->head;
        judge = node_setjudge(&node_ptr->call_hist[node_ptr->depth*DI], num_ptr_node->data);

        flag = 1;
        while(judge_ptr != NULL){

            // 見つかったとき
            if(judge_ptr->judge == judge){
                flag = 0;
                num_ptr_judge = num_init(num_ptr_node->data);
                lst_push(judge_ptr->cand_lst, num_ptr_judge);
                break;
            }else{
                judge_ptr = judge_ptr->next;
            }
        }

        // 見つからなかったとき
        if(flag){
            node_ptr->judge_len++;
            new = judge_create(judge, num_ptr_node->data);
            node_push(node_ptr, new);
        }
    }
}

int node_setjudge(int call[DI], int cand[DI]){
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
            fprintf(stderr, "judgement error : eat = %d, bite = %d\n", eat, bite);
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
            fprintf(stderr, "judgement error : eat = %d, bite = %d\n", eat, bite);
            exit(1);
        }
    }else if(eat == 2){
        if(bite == 0){
            score = J2_0;
        }else{
            fprintf(stderr, "judgement error : eat = %d, bite = %d\n", eat, bite);
            exit(1);
        }
    }else if(eat == 3){
        if(bite == 0){
            score = J3_0;
        }else{
            fprintf(stderr, "judgement error : eat = %d, bite = %d\n", eat, bite);
            exit(1);
        }
    }else{
        fprintf(stderr, "judgement error : eat = %d, bite = %d\n", eat, bite);
        exit(1);
    }

    return score;
}

judge_t* judge_create(int judge, int cand[DI]){

    judge_t *new = (judge_t*)malloc(sizeof(judge_t));
    if(new == NULL){
        fprintf(stderr, "memory allocation error.\n");
        exit(1);
    }

    new->judge = judge;
    new->score = -1;
    new->var = -1;
    // cand_lst
    new->cand_lst = lst_init();
    num_t *num_ptr = num_init(cand);
    lst_push(new->cand_lst, num_ptr);
    
    new->head = NULL;
    new->tail = NULL;
    new->next = NULL;

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

void node_clear(node_t *ptr){

    judge_t *tmp1 = ptr->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        branch_clear(tmp1);
        tmp1 = tmp2;
    }
    lst_clear(ptr->call_lst);
    free(ptr);
}

void branch_clear(judge_t *ptr){

    node_t *tmp1 = ptr->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        node_clear(tmp1);
        tmp1 = tmp2;
    }
    lst_clear(ptr->cand_lst);
    free(ptr);
}

lst_t* lst_init(void){

    lst_t *ptr = (lst_t*)malloc(sizeof(lst_t));
    if(ptr == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }

    ptr->len = 0;
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->next = NULL;

    return ptr;
}


num_t* num_init(int num[3]){

    num_t *ptr = (num_t*)malloc(sizeof(num_t));
    if(ptr == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }

    ptr->data[0] = num[0];
    ptr->data[1] = num[1];
    ptr->data[2] = num[2];
    ptr->next = NULL;

    return ptr;
}

void lst_push(lst_t *lst, num_t *num){

    lst->len++;
    if(lst->head == NULL){
        lst->head = num;
    }else{
        lst->tail->next = num;
    }
    lst->tail = num;
}

void lst_clear(lst_t *ptr){

    num_t *tmp1 = ptr->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
    free(ptr);
}
