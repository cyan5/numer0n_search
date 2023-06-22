/* main.c
 * cyan5   */

#include <stdio.h>    // printf, scanf
#include <stdlib.h>   // malloc
#include <time.h>     // clock
#include <unistd.h>   // sleep
#include "data.h"
#include "func.h"

extern int CAND_T[SIZE*DI];

int main(void){

    // 探索開始
    printf("search start!\n");
    sleep(0.5);
    double clock_1 = clock();

    // スタックorキューを生成
    que *queue = queue_init();
    // stk *stack = stack_init(void);

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

    // ルートをキューにプッシュ
    queue_push(queue, root);
    // printf("queue_push\n");

    // 探索
    node_t *node_ptr, *new;
    judge_t *judge_ptr;
    // for(int i=0; i<1; i++){
    while(queue->head != NULL){

        node_ptr = queue_pop(queue);
        node_print(node_ptr);

        judge_ptr = node_ptr->head;
        while(judge_ptr != NULL){

            for(int j=0; j<node_ptr->call_len; j++){

                if(judge_ptr->cand_len >= 2){

                    new = node_create(
                        node_ptr->depth+1, 
                        &node_ptr->call_lst[j*DI], 
                        node_ptr->call_hist, 
                        node_ptr->type, 
                        judge_ptr->cand_len, 
                        judge_ptr->cand_lst);
                    judge_push(judge_ptr, new);

                    queue_push(queue, new);
                }
            }
            judge_ptr = judge_ptr->next;
        }
    }

    // 探索木の出力
    tree_print(root);


    double clock_2 = clock();

    printf("Processing time = %.4lf sec.\n", (clock_2-clock_1)/1000000);

    queue_print(queue);
    queue_clear(queue);
    

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

    return 0;
}
