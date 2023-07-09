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
    list_t *cand_lst
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
    ptr->call_lst = list_init();
    node_setcall(ptr);

    // その他データの格納
    ptr->score = -1;
    ptr->var = -1;
    ptr->edge_len = 0;
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->next = NULL;

    // ジャッジリストを作成
    node_edgelst(ptr);

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

    hash_t *h_lst = NULL;    // ハッシュ値リスト
    int idx_lst[HIST];     // 
    int flag_same;         // 同じ質問はしない
    unit_t *unit;

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

            unit = unit_init(&CAND_T[i*DI]);
            if(ptr == NULL){
                printf("NULLa\n");
            }
            list_push(ptr->call_lst, unit);
        }
    }

    hash_clear(&h_lst);
}

void node_edgelst(node_t *node_ptr){

    int judge, flag = 1;
    edge_t *edge_ptr, *new;

    // ノードptrのcand_lstを走査
    unit_t *unit_judge;

    // ジャッジが既に存在するか探索
    for(unit_t *unit_node = node_ptr->cand_lst->head; unit_node!=NULL; unit_node=unit_node->next){

        edge_ptr = node_ptr->head;
        judge = node_setjudge(&node_ptr->call_hist[node_ptr->depth*DI], unit_node->data);

        flag = 1;
        while(edge_ptr != NULL){

            // 見つかったとき
            if(edge_ptr->judge == judge){
                flag = 0;
                unit_judge = unit_init(unit_node->data);
                list_push(edge_ptr->cand_lst, unit_judge);
                break;
            }else{
                edge_ptr = edge_ptr->next;
            }
        }

        // 見つからなかったとき
        if(flag){
            node_ptr->edge_len++;
            new = edge_create(judge, unit_node->data);
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

edge_t* edge_create(int judge, int cand[DI]){

    edge_t *new = (edge_t*)malloc(sizeof(edge_t));
    if(new == NULL){
        fprintf(stderr, "memory allocation error.\n");
        exit(1);
    }

    new->judge = judge;
    new->score = -1;
    new->var = -1;
    // cand_lst
    new->cand_lst = list_init();
    unit_t *unit = unit_init(cand);
    list_push(new->cand_lst, unit);
    
    new->head = NULL;
    new->tail = NULL;
    new->next = NULL;

    return new;
}

void node_push(node_t *ptr, edge_t *child){

    if(ptr->head == NULL){
        ptr->head = child;
    }else{
        ptr->tail->next = child;
    }
    ptr->tail = child;
}

void edge_push(edge_t *ptr, node_t *child){

    if(ptr->head == NULL){
        ptr->head = child;
    }else{
        ptr->tail->next = child;
    }
    ptr->tail = child;
}

void node_clear(node_t *ptr){

    edge_t *tmp1 = ptr->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        branch_clear(tmp1);
        tmp1 = tmp2;
    }
    list_clear(ptr->call_lst);
    free(ptr);
}

void branch_clear(edge_t *edge){

    node_t *tmp1 = edge->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        node_clear(tmp1);
        tmp1 = tmp2;
    }
    list_clear(edge->cand_lst);
    free(edge);
}

list_t* list_init(void){

    list_t *list = (list_t*)malloc(sizeof(list_t));
    if(list == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }

    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
    list->next = NULL;

    return list;
}


unit_t* unit_init(int num[3]){

    unit_t *unit = (unit_t*)malloc(sizeof(unit_t));
    if(unit == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }

    unit->data[0] = num[0];
    unit->data[1] = num[1];
    unit->data[2] = num[2];
    unit->next = NULL;

    return unit;
}

void list_push(list_t *list, unit_t *unit){

    list->len++;
    if(list->head == NULL){
        list->head = unit;
    }else{
        list->tail->next = unit;
    }
    list->tail = unit;
}

void list_clear(list_t *list){

    unit_t *tmp1 = list->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
    free(list);
}
