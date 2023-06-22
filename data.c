/* data.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "data.h"

que* queue_init(void){

    que *new = (que*)malloc(sizeof(que));
    if(new == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    new->head = NULL;
    new->tail = NULL;
    return new;
}

void queue_push(que *queue, node_t *ptr){

    if(queue->head == NULL){
        queue->head = ptr;
    }else{
        queue->head->next = ptr;
    }
    queue->tail = ptr;
}

node_t* queue_pop(que *queue){

    if(queue->head == NULL){
        fprintf(stderr, "queue underflow.\n");
        exit(1);
    }

    node_t *ptr = queue->head;

    queue->head = ptr->next;
    if(ptr->next == NULL){
        queue->tail = NULL;
    }

    return ptr;
}

void queue_clear(que *queue){

    free(queue);
}


stk* stack_init(void){

    stk *new = (stk*)malloc(sizeof(stk));
    if(new == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    return new;
}

void stack_push(stk *stack, node_t *ptr){

    ptr->next = stack->tail;
    stack->tail = ptr;
}

node_t* stack_pop(stk *stack){

    if(stack->tail == NULL){
        fprintf(stderr, "stack underflow.\n");
        exit(1);
    }
    
    node_t *ptr = stack->tail;
    stack->tail = ptr->next;

    return ptr;
}

void stack_clear(stk *stack){
    free(stack);
}