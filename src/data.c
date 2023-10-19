/* data.c
 * cyan5   */

#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "data.h"

queue_t* queue_init(void){

    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
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

void queue_push(queue_t *queue, node_t *node){

    data_t *data = (data_t*)malloc(sizeof(data_t));
    if(data == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    data->ptr = node;
    data->next = NULL;

    if(queue->head == NULL){
        queue->head = data;
    }else{
        queue->tail->next = data;
    }
    queue->tail = data;
    queue->len++;
    queue->push_count++;
}

node_t* queue_pop(queue_t *queue){

    if(queue->head == NULL){
        fprintf(stderr, "queue underflow.\n");
        exit(1);
    }

    data_t *tmp = queue->head;
    node_t *ptr = tmp->ptr;

    queue->head = tmp->next;
    if(tmp->next == NULL){
        queue->tail = NULL;
    }
    free(tmp);

    queue->len--;
    queue->pop_count++;

    return ptr;
}

void queue_print(queue_t *queue){
    printf("\rlen: %7d\tpush: %7d\tpop: %7d", 
        queue->len, 
        queue->push_count, 
        queue->pop_count);
    }

void queue_clear(queue_t *queue){
    data_t *tmp1 = queue->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        // node_t型
        free(tmp1->ptr);
        free(tmp1);
        tmp1 = tmp2;
    }
    free(queue);
}


stack_t* stack_init(void){

    stack_t *new = (stack_t*)malloc(sizeof(stack_t));
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

void stack_push(stack_t *stack, node_t *node){

    data_t *data = (data_t*)malloc(sizeof(data_t));
    if(data == NULL){
        fprintf(stderr, "memoly allocation error.\n");
        exit(1);
    }
    data->ptr = node;

    data->next = stack->head;
    stack->head = data;

    stack->len++;
    stack->push_count++;
}

node_t* stack_pop(stack_t *stack){

    if(stack->head == NULL){
        fprintf(stderr, "stack underflow.\n");
        exit(1);
    }

    data_t *tmp = stack->head;
    node_t *ptr = tmp->ptr;

    stack->head = tmp->next;
    free(tmp);

    stack->len--;
    stack->pop_count++;

    return ptr;
}

void stack_print(stack_t *stack){
    printf("\rlen: %7d\tpush: %7d\tpop: %7d", 
    stack->len, 
    stack->push_count, 
    stack->pop_count);
}

void stack_clear(stack_t *stack){
    data_t *tmp1 = stack->head, *tmp2;
    while(tmp1 != NULL){
        tmp2 = tmp1->next;
        // node_t型
        free(tmp1);
        tmp1 = tmp2;
    }
    free(stack);
}