/* cand_func.h
 * cyan5   */

#ifndef CALL
#define CALL

#include "symbol.h"

extern int CAND_T[2160];

typedef struct hash{
    int data[HIST];
    struct hash *next;
}hash;
/* HIST個のハッシュ値をリストとして保存しておく
 * リストは全て等しい場合のみ、同一の質問候補として扱われる
 * */

// int calc_idx(int cand_oridin, int call_hist[HIST*3], int depth);
int calc_idx(int cand[3], int call_hist[3], int type);
/* 質問履歴から、次の質問候補をハッシュ値で返す
 * 012→013  hash:1  012→014  hash:2  ...  012→345  hash:34 */

// int int_pow(int n, int x);

int calc_type(int call[3], int call_hist[3], int type);
/* 受け取った質問と質問履歴から、タイプを更新する。
   012→013 : type 0→1  
 * type(ポインタ)を受け取り、値を更新する */

// int hash_search(hash *ptr, int data[3]);
int hash_search(hash *ptr, int data[HIST], int depth);
/* ハッシュ値配列 data[HIST] が 単方向リストhashに含まれているか検索
 * 含まれている場合:0  含まれていない場合:1 */

// void hash_push(hash **ptr, int data[3]);
void hash_push(hash **ptr, int data[HIST]);
// void hash_push(hash **ptr, int data[HIST], int type);
/* 単方向リストhashにデータをプッシュ */

// void hash_pop(hash **ptr);
void hash_pop(int *type_stb, int type_tmp);
/* 現在のタイプと新しいタイプからタイプを決定 */

// void hash_clear(hash **ptr);
void hash_clear(hash **ptr);
/* 単方向リストhashを空にする */

#endif