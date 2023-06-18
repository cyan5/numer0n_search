/* debug.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"

/* 一時停止する */
void stop(void){
    printf("breakpoint\n");
    int tmp;
    if(scanf("%d", &tmp) != 1){
        tmp++;
        exit(1);
    }
}

/* checkを出力する */
void check(void){
    printf("check\n");
}
