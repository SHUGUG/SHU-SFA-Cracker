#include <stdio.h>
#include "stack.c"

int d;//记录步数
//d表示进行到的步数，将编号为n的盘子由from柱移动到to柱（目标柱）
void move(char from, int n, char to) {
    printf("第%d步：将%d号盘子%C---->%C\n", d++, n, from, to);
}

//汉诺塔递归 函数
//n表示要将多少个“圆盘”从起始柱子移动至目标柱子
//start_pos表示起始柱子，tran_pos表示过渡柱子，end_pos表示目标柱子
void Hanoi(int n, char start_pos, char tran_pos, char end_pos) {
    if (n == 1)//当n==1的时候，只要直接将圆盘从起始柱子移至目标柱子即可
        move(start_pos, n, end_pos);
    else {
        //递归处理，一开始的时候，先将n-1个盘子移至过渡柱上
        Hanoi(n - 1, start_pos, end_pos, tran_pos);
        //然后再将底下大盘子直接移至目标柱子即可
        move(start_pos, n, end_pos);
        //然后重复以上步骤，递归处理放在过渡柱子上的n-1个盘子
        //此时借助原来的起始柱作为过渡柱（因为起始柱已经空了）
        Hanoi(n - 1, tran_pos, start_pos, end_pos);
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        d = 1;//全局变量赋初值
        Hanoi(n, 'a', 'b', 'c');
        printf("最后总的步数为%d\n", d - 1);
    }
    return 0;
}