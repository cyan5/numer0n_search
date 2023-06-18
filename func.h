/* func.h
 * cyan5   */

#ifndef FUNC
#define FUNC

#include "symbol.h"

// extern int CAND_T[2160];

typedef struct node{
    int call[3];              /* 質問            */
    int cand[3];              /* 解答            */
    int eat;                  /* eat             */
    int bite;                 /* bite            */
    int depth;                /* 質問の回数      */
    int type;                 /* 候補タイプ      */
    int call_hist[HIST*3];    /* 質問履歴        */
    int call_len;             /* 質問候補長さ    */
    int call_lst[SIZE*3];     /* 質問候補リスト  */
    int cand_len;             /* 解答候補長さ    */
    int cand_lst[SIZE*3];     /* 解答候補リスト  */
    double score;             /* 評価値          */
    double var;               /* 評価値の分散    */
    struct node *next_row;    /*                 */
    struct node *next_col;    /*                 */
    struct node *child;       /*                 */
}node;
/* node型はツリー構造を想定しているが単方向リストとしても使える。
 * 単方向リストはque関数を用いて制御する。
 * ツリーは？
 * */

typedef struct que{
    int len;
    node *head;
    node *tail;
}que;
/* node型を単方向リストとして制御するための構造体
 * ポップすることはないのでまとめてclearする
 * */

/* ノードをキューにする関数群 */
void queue_init(que *queue);
/* キュー管理構造体を初期化 
 * node型は*/

void queue_push(que *queue, node *ptr);
/* キューにプッシュ */

node* queue_pop(que *queue);
/* キューからポップ */

/* ノードをスタックにする関数群 */
void stack_push(node **stack, node *ptr);
/* キューにプッシュ */

node* stack_pop(node **stack);
/* キューからポップ */

/* ノードを確認する関数 */
void node_print(node *ptr);

/* ノードを生成 */
node* node_create(int call[3], int cand[3], int depth, int type, int call_hist[HIST*3]);

/* ノードに情報を追加 */
void node_setjudge(node *ptr);                   /* ジャッジ */
void node_settype(node *ptr);
void node_setcand(node *ptr, int cand_len, int cand_lst[SIZE*3]);
void node_setcall(node *ptr, int depth);  /* 質問候補 */
// void node_setcall(node *ptr, int cand_oridin[SIZE*3], int depth);  /* 質問候補 */

// void queue_restore(que *queue);          /* キューに補充 */


/*  */







#endif