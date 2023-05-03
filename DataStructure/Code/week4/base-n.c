#include <stdio.h>
#include "stack.c"

void conversion(int n, int base);

int main() {
    int n, base;
    printf("输入待转换数字及目标进制(2/8/16)，如 20 16：");
    scanf("%d%d", &n, &base);
    if (base != 8 && base != 2 && base != 16) {
        printf("进制输入错误");
        return 0;
    }
    printf("将数字%d转换为%d进制的结果为：", n, base);
    conversion(n, base);
    return 0;
}

void conversion(int n, int base) {
    int e;
//    int N;
    HanoiStack S;
    //构造空栈
    InitStack(&S);
    while (n) {
        //取余，压入
        Push(&S, n % base);
        //取整
        n = n / base;
    }
    while (!StackEmpty(S)) {
        Pop(&S, &e);
        printf("%X", e);
    }
}

