/* main.c
 * cyan5   */

#include <stdio.h>    // printf, scanf
#include <stdlib.h>   // malloc
#include <time.h>     // clock
#include <unistd.h>   // sleep
#include "data.h"
#include "func.h"
#include "print.h"

#include <string.h>

extern int CAND_T[SIZE*DI];

int main(void){

    // ファイル処理
    FILE *fp;
    fp = fopen("data.md", "w");
    if(fp == NULL){
        fprintf(stderr, "file open error.\n");
        exit(1);
    }

    // 探索開始
    printf("search start!\n");
    sleep(0.5);
    double clock_1 = clock();

    // スタックorキューを生成
    stk *stack = stack_init();

    // ルートノードを生成
    int call[DI];
    for(int i=0; i<DI; i++){
        call[i] = i;
    }
    int call_hist[HIST*DI];
    node_t *root = node_create(
        0,           // depth
        call,        // call
        call_hist,   // call_hist
        NU,          // parent type
        SIZE,        // cand_len
        CAND_T);     // cand_lst

    // ルートをスタックorキューにプッシュ
    stack_push(stack, root);

    // 探索
    node_t *node_ptr, *new;
    judge_t *judge_ptr;
    // for(int i=0; i<6; i++){
    while(stack->head != NULL){

        node_ptr = stack_pop(stack);
        stack_print(stack);

        judge_ptr = node_ptr->head;
        while(judge_ptr != NULL){

            for(int j=0; j<node_ptr->call_len; j++){

                // ノードを作らない条件をここに書き込む
                if(judge_ptr->cand_len <= 2){
                    // check();
                }else if(node_ptr->depth >= 2){
                    // check();
                }else{  // ノードを作成

                    new = node_create(
                        node_ptr->depth+1, 
                        &node_ptr->call_lst[j*DI], 
                        node_ptr->call_hist, 
                        node_ptr->type, 
                        judge_ptr->cand_len, 
                        judge_ptr->cand_lst);

                    // ノードをプッシュしない条件
                    if(node_ptr->cand_len == new->cand_len){
                        node_clear(new);
                        // check();
                    }else{
                        judge_push(judge_ptr, new);
                        stack_push(stack, new);
                    }
                }
            }
            judge_ptr = judge_ptr->next;
        }
    }

    // 時間計測
    double clock_2 = clock();

    // 探索木の出力
    tree_fprint(fp, root); 

    printf("Processing time = %.4lf sec.\n", (clock_2-clock_1)/1000000);

    stack_print(stack);

    // 探索木のメモリ解放
    node_clear(root);
    stack_clear(stack);

    // ファイル処理
    fclose(fp);

    return 0;
}
