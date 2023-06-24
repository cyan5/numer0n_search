/* data.h
 * cyan5   */

#ifndef DATA
#define DATA

#include "symbol.h"

typedef struct que{
    int len;
    int push_count;
    int pop_count;
    struct data *head;
    struct data *tail;
}que;

typedef struct stk{
    int len;
    int push_count;
    int pop_count;
    struct data *head;
}stk;

typedef struct data{
    struct node_t *ptr;
    struct data *next;
}data;

que* queue_init(void);
void queue_push(que *queue, node_t *ptr);
node_t* queue_pop(que *queue);
void queue_print(que *queue);
void queue_clear(que *queue);

stk* stack_init(void);
void stack_push(stk *stack, node_t *ptr);
node_t* stack_pop(stk *stack);
void stack_print(stk *stack);
void stack_clear(stk *stack);

#endif