/* symbol.h
 * cy_an   */

#ifndef SYMBOL
#define SYMBOL

#define DEPTH    1  // 探索深さ
#define USENUM  10  // 使用する数字の数
#define DI       3  // 桁数
#define SIZE   720  // 初期の候補数 C(USENUM, DI)
#define SECOND 252  // 2回目の候補数の最大値
#define HIST    10  // 質問記録数

typedef struct node_t{
    int depth;               // 質問の回数
    int call_hist[HIST*DI];  // 質問履歴
    int type;                // 候補タイプ
    int cand_len;            // 解答候補長さ
    int cand_lst[SIZE*DI];   // 解答候補リスト
    int call_len;            // 質問候補長さ
    int call_lst[SIZE*DI];   // 質問候補リスト
    double score;            // 評価値
    double var;              // 評価値の分散
    int judge_len;           //
    struct judge_t *head;    //
    struct judge_t *tail;    //
    struct node_t *next;     // 隣のノードへのポインタ
}node_t;

typedef struct judge_t{
    int judge;               //
    double score;
    double var;
    int cand_len;            // 解答候補長さ
    int cand_lst[SECOND*DI]; // 解答候補リスト
    struct node_t *head;     //
    struct node_t *tail;     //
    struct judge_t *next;    // 隣のノードへのポインタ
}judge_t;

typedef struct num_t{
    int data[DI];
    struct num_t *next;
}num_t;

enum type {
    DV,   // 全てを区別する。notを返す
    NU,   // 全て区別しない
    LM,   // LとMは区別しない
    LR,   // LとRは区別しない
    MR    // MとRは区別しない
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

// デバッグ用関数
// プログラムを一時停止する
void breakpoint(void);

// checkを出力する
void check(void);

#endif