// 求和，分别用递归和堆栈实现

#include <stdio.h>
#include "stack.c"

int sum=0;

long sum_by_recursion(long n) {
    if (n == 1) {
        return 1;
    } else {
        printf("\n%d",++sum);
        return n + sum_by_recursion(n - 1);
    }
}

long stack_sum(long n) {
//    定义并初始化一个栈
    Stack S;
    InitStack(&S);
//    当n>=1时，不断压栈
    while (n >= 1) {
        Sum e = {n, n};
        Push(&S, e);
        n--;
    }

    Sum t;
    while (!StackEmpty(S)) {
        Pop(&S, &t);
        (S.top - 1)->sum += t.sum;
    }
    return S.bottom->sum;
}

int main() {
    long n = 200000;
    long result = stack_sum(n);
//    long result2 = sum_by_recursion(n);
    printf("s: %ld\n", result);
//    printf("r: %ld", result2);
    return 0;
}
