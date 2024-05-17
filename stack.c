#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>



void StackNew(Stack* s, void (*freefn)(void*)) {
    s->allocLen = 4;
    s->logicalLen = 0;
    printf (" size of void *  %lu ", sizeof(void*)) ;
    s->elems = malloc(4 * sizeof(void*));
    assert(s->elems != NULL);
    s->freefn = freefn;
}

void StackDispose(Stack* s) {
    if (s->freefn != NULL) {
        for (int i = 0; i < s->logicalLen; i++) {
            s->freefn((char*)s->elems + i * sizeof(void*));
            
        }
    }
    free(s->elems);
}

void StackPush(Stack* s, void* elem) {
    if (s->logicalLen == s->allocLen) {
        s->allocLen *= 2;
        s->elems = realloc(s->elems, s->allocLen * sizeof(void*));
        assert(s->elems != NULL);
    }
    s->elems[s->logicalLen++] = elem;
}

void* StackPop(Stack* s) {
    assert(s->logicalLen > 0);
    void* elem = s->elems[--s->logicalLen];
   
    return elem;
}

bool StackIsEmpty(const Stack* s) {
    return s->logicalLen == 0;
}

void FreeString(void* elem) {
    free(*(char**)elem);
}

int main() {
    Stack stringStack;
    StackNew(&stringStack, FreeString);
    char* str1 = strdup("Hello");
    char* str2 = strdup("World");
    char* str3 = strdup("!");
    StackPush(&stringStack, &str1);
    StackPush(&stringStack, &str2);
    StackPush(&stringStack, &str3);
    while (!StackIsEmpty(&stringStack)) {
        printf("Popping: ");
        char* str = *(char**)StackPop(&stringStack);
        printf("Popped: %s\n", str);
    }
    printf("\n");
    StackDispose(&stringStack);
    return 0;
}