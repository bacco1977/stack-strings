#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    void** elems;
    int logicalLen;
    int allocLen;
    void (*freefn)(void*);
} Stack;

void StackNew(Stack* s, void (*freefn)(void*));
void StackDispose(Stack* s);
void StackPush(Stack* s, void* elem);
void* StackPop(Stack* s);
bool StackIsEmpty(const Stack* s);

#endif // STACK_H
