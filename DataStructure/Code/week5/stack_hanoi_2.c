#include <stdio.h>
#include <time.h>
#include "stack_for_hanoi.c"

int sum = 0;

void solve(int n, char A, char B, char C);

void move(int n, char from, char to);

int main() {
    int n;
    clock_t start, end;
    printf("Input disks: ");
    scanf("%d", &n);
    start = clock();
    solve(n, 'A', 'B', 'C');
    printf("\nTotal steps: %d", sum);
    end = clock();
    printf("\nTime: %lu", (end - start));
    return 0;
}

void move(int n, char from, char to) {
    sum++;
//    printf("Step %d, Move disk %d %c --> %c\n", sum, n, from, to);
}

void solve(int n, char A, char B, char C) {
//    初始化，
    HanoiStack S;
    InitStack(&S);
//    将初始状态入栈
    hanoi t = {n, A, B, C, 0};
    Push(&S, t);
    int is_loop;
    while (!StackEmpty(S)) {
//        获取栈顶元素
        Pop(&S, &t);
        if (t.n == 1) {
            move(t.n, t.A, t.C);
        } else if (t.move == 0) {
//            栈顶元素n!=1，move=0的，压入(n-1 A C B 0)
            hanoi k1 = {t.n - 1, t.A, t.C, t.B, 0};
            Push(&S, k1);

            hanoi k2 = {1, t.A, t.B, t.C, 0};
            Push(&S, k2);
//            move=1的，压入(n-1 B A C 0)
            hanoi k3 = {t.n - 1, t.B, t.A, t.C, 0};
            Push(&S, k3);
        }
    }
}
