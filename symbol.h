/* symbol.h
 * cy_an   */

#ifndef SYMBOL
#define SYMBOL

#define USENUM 10  // 使用する数字の数
// #define DI 3       // 桁数
#define SIZE 720   // 初期の候補数 C(USENUM, DI)
#define HIST 10    // 質問記録数

extern int CAND_T[2160];

enum type {
    DIV,  /* 全てを区別する。notを返す */
    NEU,  /* 全て区別しない            */
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

// #if DI == 1
//     int CAND_O[SIZE] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// #if DI == 3

// int CAND_O[SIZE];

#endif