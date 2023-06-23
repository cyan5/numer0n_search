/* func.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "print.h"

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
    printf("judge_len \t= %d\n", ptr->judge_len);

    printf("\n");
}

void tree_print(node_t *ptr){

    for(int i=0; i<ptr->depth*2; i++){
        printf("    ");
    }
    printf("%d%d%d (%d)\n", 
        ptr->call_hist[ptr->depth*DI], 
        ptr->call_hist[ptr->depth*DI+1], 
        ptr->call_hist[ptr->depth*DI+2], 
        ptr->judge_len);

    judge_t *tmp = ptr->head;
    while(tmp != NULL){
        branch_print(tmp, ptr->depth);
        tmp = tmp->next;
    }
}

void branch_print(judge_t *ptr, int depth){

    for(int i=0; i<depth*2+1; i++){
        printf("    ");
    }
    judge_print(ptr->judge);
    printf(" (%d)\n", ptr->cand_len);

    node_t *tmp = ptr->head;
    while(tmp != NULL){
        tree_print(tmp);
        tmp = tmp->next;
    }
}

void tree_file(node_t *ptr, FILE *fp){

    for(int i=0; i<ptr->depth*2; i++){
        printf("    ");
    }
    printf("%d%d%d (%d)\n", 
        ptr->call_hist[ptr->depth*DI], 
        ptr->call_hist[ptr->depth*DI+1], 
        ptr->call_hist[ptr->depth*DI+2], 
        ptr->judge_len);

    judge_t *tmp = ptr->head;
    while(tmp != NULL){
        branch_print(tmp, ptr->depth);
        tmp = tmp->next;
    }
}

void branch_file(judge_t *ptr, int depth, FILE *fp){

    for(int i=0; i<depth*2+1; i++){
        printf("    ");
    }
    judge_print(ptr->judge);
    printf(" (%d)\n", ptr->cand_len);

    node_t *tmp = ptr->head;
    while(tmp != NULL){
        tree_print(tmp);
        tmp = tmp->next;
    }
}

void judge_print(int judge){

    switch(judge){
        case J3_0:
            printf("3 - 0"); break;
        case J2_0:
            printf("2 - 0"); break;
        case J1_2:
            printf("1 - 2"); break;
        case J1_1:
            printf("1 - 1"); break;
        case J1_0:
            printf("1 - 0"); break;
        case J0_3:
            printf("0 - 3"); break;
        case J0_2:
            printf("0 - 2"); break;
        case J0_1:
            printf("0 - 1"); break;
        case J0_0:
            printf("0 - 0"); break;
        default:
            fprintf(stderr, "judge print error : %d\n", judge);
            exit(1);
    }
}
