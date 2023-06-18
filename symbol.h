/* symbol.h
 * cy_an   */

#ifndef SYMBOL
#define SYMBOL

#define USENUM 10  // 使用する数字の数
// #define DI 3       // 桁数
#define SIZE 720   // 初期の候補数 C(USENUM, DI)
#define HIST 10    // 質問記録数

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