#include <stdlib.h>

#define OK 1
#define ERROR 0
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct {
    long *top;
    long *bottom;
    int stack_size;
} HanoiStack;



int InitStack(HanoiStack *S) {
    S->bottom = (long *) malloc(STACK_INIT_SIZE * sizeof(long));
    if (!S->bottom) {
        exit(0);
    }
    S->top = S->bottom;
    S->stack_size = STACK_INIT_SIZE;
    return OK;
}

// 获取栈顶的元素，若栈不空，则用e 返回S 的栈顶元素，并返回OK; 否则返回ERROR
int GetTop(HanoiStack *S, long *e) {
    if (S->top == S->bottom) {
        return ERROR;
    }
    *e = *((S->top - 1));
    return OK;
}

int Push(HanoiStack *S, long e) {
    //插人元素e 为新的栈顶元素
    if (S->top - S->bottom >= S->stack_size) { //栈满，追加存储空间
        S->bottom = (long *) realloc(S->bottom, (S->stack_size + STACK_INCREMENT) * sizeof(long));
        if (!S->bottom) {
            exit(0);
        } //存储分配失败
        S->top = S->bottom + S->stack_size;
        S->stack_size += STACK_INCREMENT;
    }
    *S->top = e;
    *S->top++;
    return OK;
}

int Pop(HanoiStack *S, long *e) {
    //若栈不空，则删除S 的栈顶元素，用e 返回其值， 并返回OK; 否则返回ERROR
    if (S->top == S->bottom) {
        return ERROR;
    }
    S->top = S->top - 1;
    *e = *S->top;
    return OK;
}

void ClearStack(HanoiStack *S) {
    S->top = S->bottom;
}

long StackLength(HanoiStack S) {
    long length = S.top - S.bottom;
    return length;
}

void DestroyStack(HanoiStack *S) {
    long len;
    len = S->stack_size;
    for (int j = 0; j < len; ++j) {
        free(S->bottom);
        S->bottom++;
    }
    S->bottom = S->top = NULL;
    S->stack_size = 0;
}

long StackEmpty(HanoiStack S) {
    if (S.bottom == S.top)
        return OK;
    else
        return ERROR;
}

