/* func.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "call.h"

void queue_init(que *queue){
    queue->len = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

void queue_push(que *queue, node *ptr){
    queue->len++;
    if(queue->head == NULL){
        queue->head = ptr;
    }else{
        queue->tail->child = ptr;
    }
    queue->tail = ptr;
}

node* queue_pop(que *queue){
    node *ptr = queue->head;
    if(ptr == NULL){
        fprintf(stderr, "queue underflow.\n");
        exit(1);
    }
    queue->head = ptr->child;
    queue->len--;
    return ptr;
}

void stack_push(node **stack, node *ptr){

    ptr->child = *stack;
    *stack = ptr;
}

node* stack_pop(node **stack){

    if(*stack == NULL){
        fprintf(stderr, "stack underflow.\n");
        exit(1);
    }
    node *ptr = *stack;
    *stack = ptr->child;
    return ptr;
}

node* node_create(int call[3], int cand[3], int depth, int type, int call_hist[HIST*3]){

    // メモリの動的確保
    node *ptr = (node*)malloc(sizeof(node));

    // int call[3]
    ptr->call[0] = call[0];
    ptr->call[1] = call[1];
    ptr->call[2] = call[2];

    // int cand[3]
    ptr->cand[0] = cand[0];
    ptr->cand[1] = cand[1];
    ptr->cand[2] = cand[2];

    // eat bite

    // int depth
    ptr->depth = depth;

    // int type
    ptr->type = type;

    // int call_hist[HIST*3]
    for(int i=0; i<HIST; i++){
        if(i < depth){
            ptr->call_hist[i*3  ] = call_hist[i*3  ];
            ptr->call_hist[i*3+1] = call_hist[i*3+1];
            ptr->call_hist[i*3+2] = call_hist[i*3+2];
        }else if(i == depth){
            ptr->call_hist[i*3  ] = call[0];
            ptr->call_hist[i*3+1] = call[1];
            ptr->call_hist[i*3+2] = call[2];
        }else{
            ptr->call_hist[i*3] = -1;
        }
    }

    // set call_len and call_lst
    // node_setcall(ptr, cand_oridin);

    // double score, var
    ptr->score = -1;
    ptr->var = -1;

    // struct node *next_row, *next_col, *child
    ptr->next_row = NULL;
    ptr->next_col = NULL;
    ptr->child = NULL;

    return ptr;
}

void node_setjudge(node *ptr){
    int eat = 0, bite = 0;
    if(ptr->call[0] == ptr->cand[0]){eat++;}
    if(ptr->call[0] == ptr->cand[1]){bite++;}
    if(ptr->call[0] == ptr->cand[2]){bite++;}
    if(ptr->call[1] == ptr->cand[0]){bite++;}
    if(ptr->call[1] == ptr->cand[1]){eat++;}
    if(ptr->call[1] == ptr->cand[2]){bite++;}
    if(ptr->call[2] == ptr->cand[0]){bite++;}
    if(ptr->call[2] == ptr->cand[1]){bite++;}
    if(ptr->call[2] == ptr->cand[2]){eat++;}
    ptr->eat = eat;
    ptr->bite = bite;
}

void node_settype(node *ptr){
    if(ptr->type){
        for(int i=0; i<ptr->depth; i++){
            ptr->type = calc_type(&ptr->call_hist[ptr->depth*3], &ptr->call_hist[i*3], ptr->type);
            if(ptr->type == DV){
                break;
            }
        }
    }
}

void node_setcand(node *ptr, int cand_len, int cand_lst[SIZE*3]){

    int idx = 0, eat, bite;
    for(int i=0; i<cand_len; i++){

        // ジャッジ
        eat = 0;
        bite = 0;

        if(ptr->call[0] == cand_lst[i*3  ]){eat++;}
        if(ptr->call[0] == cand_lst[i*3+1]){bite++;}
        if(ptr->call[0] == cand_lst[i*3+2]){bite++;}
        if(ptr->call[1] == cand_lst[i*3  ]){bite++;}
        if(ptr->call[1] == cand_lst[i*3+1]){eat++;}
        if(ptr->call[1] == cand_lst[i*3+2]){bite++;}
        if(ptr->call[2] == cand_lst[i*3  ]){bite++;}
        if(ptr->call[2] == cand_lst[i*3+1]){bite++;}
        if(ptr->call[2] == cand_lst[i*3+2]){eat++;}

        if(ptr->eat == eat && ptr->bite == bite){
            ptr->cand_lst[idx*3  ] = cand_lst[i*3  ];
            ptr->cand_lst[idx*3+1] = cand_lst[i*3+1];
            ptr->cand_lst[idx*3+2] = cand_lst[i*3+2];
            idx++;
        }
    }
    ptr->cand_len = idx;
}

void node_setcall(node *ptr, int depth){
// void node_setcall(node *ptr, int cand_oridin[SIZE*3], int depth){

    hash *h_lst = NULL;
    int idx_lst[HIST];
    int flag_zero;

    int idx = 0;
    for(int i=0; i<SIZE; i++){

        flag_zero = 1;
        for(int j=0; j<=depth; j++){
            idx_lst[j] = calc_idx(&CAND_T[i*3], &ptr->call_hist[j*3], ptr->type);
            // idx_lst[j] = calc_idx(&cand_oridin[i*3], &ptr->call_hist[j*3], ptr->type);
            if(idx_lst[j] == 0){
                flag_zero = 0;
                break;
            }
        }

        if(flag_zero && hash_search(h_lst, idx_lst, depth)){
            hash_push(&h_lst, idx_lst);
            ptr->call_lst[idx*3  ] = CAND_T[i*3  ];
            ptr->call_lst[idx*3+1] = CAND_T[i*3+1];
            ptr->call_lst[idx*3+2] = CAND_T[i*3+2];
            // ptr->call_lst[idx*3  ] = cand_oridin[i*3  ];
            // ptr->call_lst[idx*3+1] = cand_oridin[i*3+1];
            // ptr->call_lst[idx*3+2] = cand_oridin[i*3+2];
            idx++;
        }
    }

    ptr->call_len = idx;
    hash_clear(&h_lst);
}

void node_print(node* ptr){
    printf("call[3] \t= %d%d%d\tcand[3] = %d%d%d\n", 
        ptr->call[0], ptr->call[1], ptr->call[2], 
        ptr->cand[0], ptr->cand[1], ptr->cand[2]);
    printf("eat bite \t= %d-%d\n", ptr->eat, ptr->bite);
    printf("depth   \t= %d\n", ptr->depth);
    printf("call_hist[%d] \t= [", ptr->depth+1);
    for(int i=0; i<=ptr->depth; i++){
        printf("%d%d%d", ptr->call_hist[i*3], ptr->call_hist[i*3+1], ptr->call_hist[i*3+2]);
        if(i != ptr->depth){printf(" ");}
    }
    printf("]\n");
    printf("cand_lst[%d] \t= [", ptr->cand_len);
    for(int i=0; i<ptr->cand_len; i++){
        printf("%d%d%d", ptr->cand_lst[i*3], ptr->cand_lst[i*3+1], ptr->cand_lst[i*3+2]);
        if(i >= 20){
            printf(" ... ");
            break;
        }else if(i != ptr->cand_len-1){
            printf(" ");
        }
    }
    printf("]\n");
    printf("call_lst[%d] \t= [", ptr->call_len);
    for(int i=0; i<ptr->call_len; i++){
        printf("%d%d%d", ptr->call_lst[i*3], ptr->call_lst[i*3+1], ptr->call_lst[i*3+2]);
        if(i >= 20){
            printf(" ... ");
            break;
        }else if(i != ptr->call_len-1){
            printf(" ");
        }
    }
    printf("]\n");
    printf("score   \t= %lf\n", ptr->score);
    printf("var     \t= %lf\n", ptr->var);
    printf("\n");
}

// void queue_restore(que *queue){

//     node *ptr = queue_pop(&queue);
//     for(int i=0; i<ptr->cand_len; i++){
//         for(int j=0; j<ptr->call_len; j++){
//             node *new = node_create(ptr->call, ptr->call_hist, ptr->depth+1, ptr->call_hist);

//         }
//     }
// }

