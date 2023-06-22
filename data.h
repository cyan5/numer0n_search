/* data.h
 * cyan5   */

#ifndef DATA
#define DATA

#include "symbol.h"

typedef struct que{
    node_t *head;
    node_t *tail;
}que;

typedef struct stk{
    node_t *tail;
}stk;

que* queue_init(void);
void queue_push(que *queue, node_t *ptr);
node_t* queue_pop(que *queue);
void queue_clear(que *queue);

stk* stack_init(void);
void stack_push(stk *stack, node_t *ptr);
node_t* stack_pop(stk *stack);
void stack_clear(stk *stack);

#endif