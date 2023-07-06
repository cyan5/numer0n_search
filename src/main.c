/* main.c
 * cyan5   */

#include <stdio.h>    // printf, scanf
#include <stdlib.h>   // malloc
#include <time.h>     // clock
#include <unistd.h>   // sleep
#include "data.h"
#include "func.h"
#include "print.h"
#include "eval.h"
#include "cand.h"

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

    // 解答候補を作成
    setCAND_T();

    // スタックorキューを生成
    stk *stack_search_now = stack_init();
    stk *stack_search_next;
    stk *stack_eval = stack_init();

    // ルートノードを生成
    int call[DI];
    call[0] = 0;
    call[1] = 1;
    call[2] = 2;
    lst_t *lst_ptr = lst_init();
    num_t *num_ptr;
    for(int i=0; i<SIZE; i++){
        num_ptr = num_init(&CAND_T[i*DI]);
        lst_push(lst_ptr, num_ptr);
    }
    int call_hist[HIST*DI];
    // 引数 depth, call, call_hist, parent_type, cand_lst
    node_t *root = node_create(0, call, call_hist, NU, lst_ptr);

    // ルートをスタックorキューにプッシュ
    stack_push(stack_search_now, root);

    // 探索
    node_t *node_ptr; 
    node_t *node_new;
    // judge_t *judge_ptr;
    // 質問回数
    for(int i=0; i<TIMES; i++){

        // 探索木を作る
        // ポップするスタック stack_search
        // depth 0(012) depth1(013-345)

        // search関数の仕様
        // 引数はルートノードポインタ、探索済みdepth, 探索するdpeth
        // depth 0までツリー作成
        // (depth -1の評価)
        // (depth -1を枝刈り)
        // depth 1までツリー作成
        // (depth 0の評価)
        // (depth 0を枝刈り)
        // depth 2までツリーを作成
        // depth 1の評価
        // depth 1を枝刈り
        // depth 3までツリーを作成
        // depth 2の評価
        // depth 2を枝刈り
        // depth 4までツリーを作成
        // depth 3の評価
        // depth 3を枝刈り
        // depth 5までツリーを作成
        // depth 4の評価
        // depth 4を枝刈り
        // depth 6までツリーを作成
        // depth 5の評価
        // depth 5を枝刈り

        // プッシュするスタック stack_search_next
        // ルート root


        stack_search_next = stack_init();
        while(stack_search_now->head != NULL){

            // ポップ
            node_ptr = stack_pop(stack_search_now);
            // node_print(node_ptr);
            // breakpoint();
            stack_print(stack_search_now);

            // ジャッジポインタを作成
            for(judge_t *judge_ptr=node_ptr->head; judge_ptr!=NULL; judge_ptr=judge_ptr->next){

                // ジャッジポインタの候補の長さだけループ
                for(num_ptr=node_ptr->call_lst->head; num_ptr!=NULL; num_ptr=num_ptr->next){


                    // ノードを作らない条件をここに書き込む
                    if(judge_ptr->cand_lst->len <= 2){
                        // check();
                    }else if(node_ptr->depth >= i+DEPTH){
                        // check();
                    }else{  // ノードを作成

                        node_new = node_create(
                            node_ptr->depth+1, 
                            num_ptr->data, 
                            node_ptr->call_hist, 
                            node_ptr->type, 
                            judge_ptr->cand_lst
                            );

                        // ノードをプッシュしない条件
                        if(node_ptr->cand_lst->len == node_new->cand_lst->len){
                            node_clear(node_new);
                            // check();
                        }else{
                            // ジャッジにプッシュ
                            judge_push(judge_ptr, node_new);
                            // キューにプッシュ
                            stack_push(stack_search_now, node_new);
                            // // 次の探索キューにプッシュ
                            // printf("check %d == %d\n", node_new->depth, i+1);
                            // if(node_new->depth == i+1){
                            //     stack_push(stack_search_next, node_new);
                            // }

                            // 評価値スタックへ送る
                            // if(node_ptr->depth == i){
                            //     stack_push(stack_eval, node_new);
                            // }
                        }
                    }
                }
            }

            // 評価値スタックorキューにプッシュ
            if(node_ptr->depth == i){
                stack_push(stack_eval, node_ptr);
            }

            // 次の探索キューにプッシュ
            if(node_ptr->depth == i+1){
                stack_push(stack_search_next, node_ptr);
            }
        }

        // 探索木に評価値をつける
        while(stack_eval->head != NULL){
            node_ptr = stack_pop(stack_eval);
            node_eval(node_ptr, DEPTH);
        }

        // 並べ替え & 候補

        // 枝刈りをする
        // WIP

        // 再び探索木を作る
        stack_search_next->push_count = stack_search_now->push_count;
        stack_search_next->pop_count = stack_search_now->pop_count;

        if(stack_search_now->len != 0){
            printf("debug stacklen noteq 0: %d\n", stack_search_now->len);
            exit(1);
        }
        free(stack_search_now);
        stack_search_now = stack_search_next;
    }

    // 時間計測
    double clock_2 = clock();

    // 探索木の出力
    printf("\n");
    tree_print(root);
    tree_fprint(fp, root);

    printf("\nProcessing time = %.4lf sec.\n", (clock_2-clock_1)/1000000);

    stack_print(stack_search_now);
    printf("\n");

    // 探索木のメモリ解放
    stack_clear(stack_search_now);
    stack_clear(stack_eval);
    node_clear(root);

    // ファイル処理
    fclose(fp);

    // 正常に終了したことを出力
    printf("program finished.\n");

    return 0;
}
