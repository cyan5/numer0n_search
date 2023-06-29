/* data.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "data.h"

que* queue_init(void){

    que *queue = (que*)malloc(sizeof(que));
    if(queue == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    queue->len = 0;
    queue->push_count = 0;
    queue->pop_count = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
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
        queue->tail->next = dat;
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
    printf("\rlen: %7d\tpush: %7d\tpop: %7d", 
        queue->len, 
        queue->push_count, 
        queue->pop_count);
    }

void queue_clear(que *queue){
    data *tmp1 = queue->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        // node_t型
        free(tmp1->ptr);
        free(tmp1);
        tmp1 = tmp2;
    }
    free(queue);
}


stk* stack_init(void){

    stk *new = (stk*)malloc(sizeof(stk));
    if(new == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    new->len = 0;
    new->push_count = 0;
    new->pop_count = 0;
    new->head = NULL;
    return new;
}

void stack_push(stk *stack, node_t *ptr){

    data *dat = (data*)malloc(sizeof(data));
    if(dat == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    dat->ptr = ptr;

    dat->next = stack->head;
    stack->head = dat;

    stack->len++;
    stack->push_count++;
}

node_t* stack_pop(stk *stack){

    if(stack->head == NULL){
        fprintf(stderr, "stack underflow.\n");
        exit(1);
    }
    
    data *tmp = stack->head;
    node_t *ptr = tmp->ptr;

    stack->head = tmp->next;

    stack->len--;
    stack->pop_count++;

    return ptr;
}

void stack_print(stk *stack){
    printf("\rlen: %7d\tpush: %7d\tpop: %7d", 
    stack->len, 
    stack->push_count, 
    stack->pop_count);
}

void stack_clear(stk *stack){
    data *tmp1 = stack->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        // node_t型
        // free(tmp1->ptr);
        free(tmp1);
        tmp1 = tmp2;
    }
    free(stack);
}