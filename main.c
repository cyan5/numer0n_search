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
    // stk *stack = stack_init();
    que *queue = queue_init();

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
    // stack_push(stack, root);
    queue_push(queue, root);

    // 探索
    node_t *node_ptr, *new;
    judge_t *judge_ptr;
    // for(int i=0; i<6; i++){
    // while(stack->head != NULL){
    while(queue->head != NULL){

        // node_ptr = stack_pop(stack);
        node_ptr = queue_pop(queue);
        // node_print(node_ptr);
        queue_print(queue);
        // breakpoint();

        judge_ptr = node_ptr->head;
        while(judge_ptr != NULL){

            for(int j=0; j<node_ptr->call_len; j++){

                // ノードを作る条件をここに書き込む
                if(
                    judge_ptr->cand_len >= 2 &&
                    node_ptr->depth < 1
                ){

                    new = node_create(
                        node_ptr->depth+1, 
                        &node_ptr->call_lst[j*DI], 
                        node_ptr->call_hist, 
                        node_ptr->type, 
                        judge_ptr->cand_len, 
                        judge_ptr->cand_lst);
                    judge_push(judge_ptr, new);

                    // stack_push(stack, new);
                    // stack_print(stack);
                    queue_push(queue, new);
                    // node_print(new);
                    // breakpoint();
                    // queue_print(queue);

                }
            }
            judge_ptr = judge_ptr->next;
        }
    }

    // 時間計測
    double clock_2 = clock();


    // 探索木の出力
    tree_print(root);
    // tree_file(root, fp);
    char str[256] = "test";
    fputs(str, fp);


    printf("Processing time = %.4lf sec.\n", (clock_2-clock_1)/1000000);

    queue_print(queue);
    // stack_print(stack);
    queue_clear(queue);
    // stack_clear(stack);
    

    // 入力
    // printf("print evaluate value ? y:1 n:0 > ");
    // scanf("%d", &flag_printeval);

    printf("Game Start!\n");

    // ループ回数だけゲームをプレイ
    // for(i=0; i<SIZE; i++){

    //     // ゲーム回数を表示
    //     printf("--< Game %d >--\n", i+1);

    //     // ゲームiで使用する答え
    //     set_answer[0] = CAND_T[i][0];
    //     set_answer[1] = CAND_T[i][1];
    //     set_answer[2] = CAND_T[i][2];

    //     // 3 EAT するまでループ
    //     // while(1){
    //     for(j=0; j<0; j++){

    //         eat = 0;
    //         bite = 0;

    //         // コールの決定
    //         // call_tree
    //     }
    // }


    // 探索木のメモリ解放
    tree_clear(root);

    // ファイル処理
    fclose(fp);

    return 0;
}
