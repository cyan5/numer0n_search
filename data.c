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
    new->len = 0;
    new->push_count = 0;
    new->pop_count = 0;
    new->head = NULL;
    new->tail = NULL;
    return new;
}

void queue_push(que *queue, node_t *ptr){

    data *dat = (data*)malloc(sizeof(data));
    if(dat == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    dat->ptr = ptr;
    dat->next = NULL;

    if(queue->head == NULL){
        queue->head = dat;
    }else{
        queue->head->next = dat;
    }
    queue->tail = dat;
    queue->len++;
    queue->push_count++;
}

node_t* queue_pop(que *queue){

    if(queue->head == NULL){
        fprintf(stderr, "queue underflow.\n");
        exit(1);
    }

    data *tmp = queue->head;
    node_t *ptr = tmp->ptr;

    queue->head = tmp->next;
    if(tmp->next == NULL){
        queue->tail = NULL;
    }
    queue->len--;
    queue->pop_count++;

    free(tmp);
    return ptr;
}

void queue_print(que *queue){
    printf("queue_len = %d\n", queue->len);
    printf("push : %d\n", queue->push_count);
    printf("pop  : %d\n", queue->pop_count);
}

void queue_clear(que *queue){
    data *ptr = queue->head, *tmp;
    while(ptr != NULL){
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
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