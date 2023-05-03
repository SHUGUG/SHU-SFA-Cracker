#include<stdio.h>
#include <time.h>

#define MAX_N 20    //测试点3 的N最大，达到20
#define MAX_SIZE (2*(MAX_N)-1)  //恰好能够解决问题的栈容量。
//如N=4时， 栈S最满时的INFO.n分别为[3,1,2,1,1,1,1 ] ；以此类推 N=n时为：[n-1,1,n-2,1,n-3,1,...,3,1,2,1,1,1,1]
typedef char ELE;
typedef struct {
    ELE n, id;
} INFO;
const char T[6][8] = {    //6种id对应的操作
        "a -> c",  // abc    000
        "a -> b",  // acb    001
        "b -> a",  // bca    010
        "b -> c",  // bac    011
        "c -> b",  // cab    100
        "c -> a"   // cba    101
};//正则：查找目标" (([abc])[abc]([abc]) )"，替换为'\"$2 -> $3\\n\",  // $1'
/*
分析：每一步都是讲盘子从 a,b,c中的一根柱移到另一根上，所以有3*2=6种（排列数3选2），所以必然可以用6个编码代表6种移动方案。
关键是如何排列才能很方便地计算分解步骤的状态编码！
以初始状态为"a -> c"为例，第一步需要的是"a -> b"，第二步不变还是"a -> c"，第三步是"b -> c"。
先考虑第一步，起点不变只改变终点，可以将相同起点编码为相邻id，只需改变最低位(异或0x01)即可映射到第一步所需id；
第二步不变直接照抄；
至于第三步，终点不变换起点，同样是两种状态循环，那一共6种状态，不妨试试循环后移3格，abc变为bac则把bac设为id=3，类似格雷码，
相邻两个id对应的排列都只交换两个字母（格雷码是改变其中1bit的0或1），很巧妙的发现，其对应id不过是循环后移（前移）3格。
*/
INFO S[MAX_SIZE];   //栈
int top = -1; //栈顶指针
void push(ELE n, ELE id) {
    S[++top].n = n;
    S[top].id = id;
}

int main() {
    int sum = 0;
    int N;
    scanf("%d", &N);
    clock_t start, end;
    start = clock();
    push(N, 0);  //abc
    while (top >= 0) {
        int n = S[top].n;
        int id = S[top].id;
        --top; //pop
        if (1 == n) {   //可以直接移动
            ++sum;
//            printf("%d.", sum);
//            puts(T[id]);
        } else {
            push(n - 1, (id + 3) % 6);//第三步 1~n-1号盘，从b柱移到c柱的n号盘上
            push(1, id);       //第二步 直接将n号盘，从a柱移到c柱上
            push(n - 1, (1 ^ id));  //第一步 1~n-1号盘，从a柱移到b柱上
        }
    }
    end = clock();
    printf("\nTime: %lu", (end - start));
    return 0;
}
