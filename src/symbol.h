/* symbol.h
 * cy_an   */

#ifndef SYMBOL
#define SYMBOL

#define TIMES    1  // 質問回数 < HIST
#define SEQ      3  // 探索深さ < HIST
#define USENUM   8  // 使用する数字の数
#define DI       3  // 桁数
#define SIZE (USENUM*(USENUM-1)*(USENUM-2))  // 初期の候補数 nPr(USENUM, DI)
#define HIST    10  // 質問記録数

typedef struct node_t{
    int evaluated;           // 評価完了フラグ
    int depth;               // 質問の回数
    int call_hist[HIST*DI];  // 質問履歴
    int type;                // 候補タイプ
    struct list_t *cand_lst; // 解答候補リスト
    struct list_t *call_lst; // 質問候補リスト
    double score;            // 評価値
    double var;              // 評価値の分散
    int edge_len;            //
    struct edge_t *head;     //
    struct edge_t *tail;     //
    struct node_t *next;     // 隣のノードへのポインタ
}node_t;

typedef struct edge_t{
    int evaluated;           // 評価完了フラグ
    int judge;               // ジャッジ(辞書型)
    double score;            // スコア
    double var;              // 分散
    struct list_t *cand_lst; // 解答候補リスト
    struct node_t *head;     //
    struct node_t *tail;     //
    struct edge_t *next;     // 隣のノードへのポインタ
}edge_t;

typedef struct list_t{
    int len;
    struct unit_t *head;
    struct unit_t *tail;
    struct list_t *next;
}list_t;

typedef struct unit_t{
    int data[DI];
    struct unit_t *next;
}unit_t;

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