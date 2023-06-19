/* symbol.h
 * cy_an   */

#ifndef SYMBOL
#define SYMBOL

#define USENUM 10  // 使用する数字の数
// #define DI 3       // 桁数
#define SIZE 720   // 初期の候補数 C(USENUM, DI)
#define HIST 10    // 質問記録数

typedef struct node{
    int depth;                /* 質問の回数      */
    int call_hist[HIST*3];    /* 質問履歴        */
    int type;                 /* 候補タイプ      */
    int cand_len;             /* 解答候補長さ    */
    int cand_lst[SIZE*3];     /* 解答候補リスト  */
    double score;             /* 評価値          */
    double var;               /* 評価値の分散    */
    struct node *next;
    int node2_len;
    struct node2 *head; /*                 */
    struct node2 *tail; /*                 */
}node;

typedef struct node2{
    int judge;             /*  */
    int judge_hist[HIST];  /*  */
    struct node2 *next;    /*  */
    int node_len;
    struct node *head;     /*  */
    struct node *tail;     /*  */
}node2;

enum type {
    DV,   /* 全てを区別する。notを返す */
    NU,   /* 全て区別しない            */
    LM,   /* LとMは区別しない          */
    LR,   /* LとRは区別しない          */
    MR    /* MとRは区別しない          */
};

enum judge {
    J3_0, 
    J2_0, 
    J1_2, 
    J1_1, 
    J1_0, 
    J0_3, 
    J0_2, 
    J0_1, 
    J0_0
};

/* デバッグ用関数 */
/* プログラムを一時停止する */
void stop(void);

/* checkを出力する */
void check(void);

#endif