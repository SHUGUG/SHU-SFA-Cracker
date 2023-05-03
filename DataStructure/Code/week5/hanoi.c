#include <stdio.h>
#include <time.h>

int sum = 0;

void move(int n, char from, char to){
    sum++;
//    printf("Step %d, Move disk %d %c --> %c\n", sum, n, from, to);
}

void hanoi(int n, char A, char B, char C) {
//    若只有一个元素，直接把这个元素移动到C
    if (n == 1) {
        move(n, A, C);
    } else {
//        否则把前n-1个元素，借助C移动到B
        hanoi(n - 1, A, C, B);
//        再把A最下面的元素移动到C
        move(n, A, C);
//        最后把B上的元素借助A移动到C
        hanoi(n - 1, B, A, C);
    }
}

int main() {
    int n;
    clock_t start, end;
    printf("Input disks: ");
    scanf("%d", &n);
    start = clock();
    hanoi(n, 'A', 'B', 'C');
    printf("\nTotal steps: %d", sum);
    end = clock();
    printf("\nTime: %lu", (end - start));
    return 0;
}
