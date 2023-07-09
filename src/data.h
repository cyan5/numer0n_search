/* data.h
 * cyan5   */

#ifndef DATA
#define DATA

#include "symbol.h"

typedef struct queue_t{
    int len;
    int push_count;
    int pop_count;
    struct data_t *head;
    struct data_t *tail;
}queue_t;

typedef struct stack_t{
    int len;
    int push_count;
    int pop_count;
    struct data_t *head;
}stack_t;

typedef struct data_t{
    struct node_t *ptr;
    struct data_t *next;
}data_t;

queue_t* queue_init(void);
void queue_push(queue_t *queue, node_t *ptr);
node_t* queue_pop(queue_t *queue);
void queue_print(queue_t *queue);
void queue_clear(queue_t *queue);

stack_t* stack_init(void);
void stack_push(stack_t *stack, node_t *ptr);
node_t* stack_pop(stack_t *stack);
void stack_print(stack_t *stack);
void stack_clear(stack_t *stack);

#endif