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
    node_t *root;
    root = node_create(
        0,           // depth
        call,        // call
        call_hist,   // call_hist
        NU,          // parent type
        SIZE,        // cand_len
        CAND_T);     // cand_lst

    // ルートをキューにプッシュ
    queue_push(queue, root);
    printf("queue_push\n");

    // 探索
    int node_idx;
    node_t *node_ptr, *new;
    judge_t *judge_ptr;
    // while(queue->head != NULL){
    for(int i=0; i<1; i++){

        node_ptr = queue_pop(queue);
        printf("queue_pop\n");
        node_print(node_ptr);
        stop();

        node_idx = 0;
        judge_ptr = node_ptr->head;
        while(judge_ptr != NULL){

            new = node_create(
                node_ptr->depth+1, 
                &node_ptr->call_lst[node_idx*DI], 
                node_ptr->call_hist, 
                node_ptr->type, 
                judge_ptr->cand_len, 
                judge_ptr->cand_lst);
            judge_push(judge_ptr, new);
            queue_push(queue, new);
            printf("queue push\n");

            node_idx++;
            judge_ptr = judge_ptr->next;
        }
    }



    // ノードに質問とジャッジを追加
    
    
    
    /*
    node_setjudge(new);                // eat, bite
    node_setcall(new, 0);              // 
    node_setcand(new, SIZE, CAND_T);   // 

    node_print(new);
    */
    

    
    /*
    new = node_create();

    queue_push(que, new);

    while(queue->head != NULL){

        ptr = queue_pop()

        for(i=0; i<ptr->cand_len; i++){

        }
        queue_push(que, new);
    }
    
    
    
    */

    // for(i=0; i<SIZE; i++){

        
    // }

    // ルートノードをスタックorキューにプッシュ
    // queue_push(queue, new);
    // stack_push(&stack, new);


    // check function
    // while(queue->head != NULL){

    //     ptr = queue_pop(queue);
    //     // node_print(ptr);

    // }

    // 
    #if 0
    while(0){
    // while(queue->head != NULL){
    // while(stack != NULL){

        // キューからポップ
        ptr = queue_pop(queue);
        // ptr = stack_pop(&stack);
        node_print(ptr);

        // ノード判定
        if(ptr->cand_len == 1){
            ptr->score = 1;
            ptr->var = 0;
        }else if(ptr->cand_len == 2){
            ptr->score = 1.5;
            ptr->var = 0.25;
        }else if(ptr->depth == 2){
            ptr->score = -1;
        }else{
            // 子ノードをキューにプッシュ
            // for(i=0; i<1; i++){
            for(i=0; i<ptr->call_len; i++){
                for(j=0; j<1; j++){
                // for(j=0; j<ptr->cand_len; j++){

                    // nodeを作成
                    call[0] = ptr->call_lst[i*3  ];
                    call[1] = ptr->call_lst[i*3+1];
                    call[2] = ptr->call_lst[i*3+2];
                    cand[0] = ptr->cand_lst[j*3  ];
                    cand[1] = ptr->cand_lst[j*3+1];
                    cand[2] = ptr->cand_lst[j*3+2];
                    new = node_create(call, cand, ptr->depth+1, ptr->type, ptr->call_hist);

                    // ノードに情報を追加
                    node_setjudge(new);
                    node_settype(new);
                    node_setcand(new, ptr->cand_len, ptr->cand_lst);
                    node_setcall(new, ptr->depth);

                    // ルートノードをキューにプッシュ
                    queue_push(queue, new);
                    // stack_push(&stack, new);
                }
            }
        }

        // 親ノードをヒープにプッシュ
        // heap_push(ptr);
    }

    free(queue);

    #endif




    /*
    node_create, queue_pushを最初に720回行うプログラムに変更
    node要素の先頭に、回答候補、eat, biteを追加
    */

    // node *new;
    // node *new;
    // {
    //     // キューの先頭をポップ
    //     new = queue_pop(&queue);

    //     for(i=0; i<new->cand_len; i++){
    //         for(j=0; j<new->call_len; j++){
    //             call[0] = 
    //             new = node_create()
    //         }
    //     }
    // }


    // 
    // while(1){
    //     // キューからポップ
        
    //     // キューに補充
    //     queue_restore(&queue);
    // }

    // queue_push(&queue, &new);
    
    // while(queue != NULL){
    //     queue_to_heap();
    // }

    // while()

    // while(queue != NULL){
    //     queue_to_heap(queue, heap);
    // }

    double clock_2 = clock();
    printf("Processing time = %.4lf sec.\n", (clock_2-clock_1)/1000000);
    

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

    return 0;
}
