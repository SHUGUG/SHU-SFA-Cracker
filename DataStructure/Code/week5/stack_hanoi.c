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
        GetTop(&S, &t);
        if (t.n == 1) {
//            如果栈顶元素n=1，move并出栈
            move(t.n, t.A, t.C);
            Pop(&S, &t);
//            检测出栈后栈顶的元素是否已move，若未move，move后将move值设置为1
//            若已move，将其出栈，并设置循环flag is_loop=1，让其继续检测上一个栈的move情况
            do {
                is_loop = 0;
                if (!StackEmpty(S)) {
                    GetTop(&S, &t);
                    if (t.move == 0) {
                        move(t.n, t.A, t.C);
                        (S.top - 1)->move = 1;
                    } else {
                        Pop(&S, &t);
                        is_loop = 1;
                    }
                }
            } while (is_loop);
        } else if (t.move == 0) {
//            栈顶元素n!=1，move=0的，压入(n-1 A C B 0)
            hanoi k = {t.n - 1, t.A, t.C, t.B, 0};
            Push(&S, k);
        } else {
//            move=1的，压入(n-1 B A C 0)
            hanoi k = {t.n - 1, t.B, t.A, t.C, 0};
            Push(&S, k);
        }
    }
}
