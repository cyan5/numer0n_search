/* cand.c
 * cyan5   */

#include "symbol.h"
#include "cand.h"

int CAND_T[SIZE*DI];

void setCAND_T(void){
    int idx = 0;
    for(int i=0; i<USENUM; i++){
        for(int j=0; j<USENUM; j++){
            if(i != j){
                for(int k=0; k<USENUM; k++){
                    if(i != k && j != k){
                        CAND_T[idx*DI  ] = i;
                        CAND_T[idx*DI+1] = j;
                        CAND_T[idx*DI+2] = k;
                        idx++;
                    }
                }
            }
        }
    }
}
