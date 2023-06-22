/* debug.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"

/* 一時停止する */
void breakpoint(void){
    printf("breakpoint : ");
    int tmp;
    if(scanf("%d", &tmp) != 1){
        exit(1);
    }
}

/* checkを出力する */
void check(void){
    printf("check\n");
}
