/* data.h
 * cyan5   */

#ifndef DATA
#define DATA

#include "symbol.h"

typedef struct que{
    node *head;
    node *tail;
}que;

typedef struct stk{
    node *tail;
}stk;

que* queue_init(void);
void queue_push(que *queue, node *ptr);
node* queue_pop(que *queue);
void queue_clear(que *queue);

stk* stack_init(void);
void stack_push(stk *stack, node *ptr);
node* stack_pop(stk *stack);
void stack_clear(stk *stack);

#endif