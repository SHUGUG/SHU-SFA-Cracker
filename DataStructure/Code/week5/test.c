// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <malloc.h>
//#include <stdlib.h>

typedef struct OLNode {
    int row, col;
    int value;
    struct OLNode *right, *down;
} OLNode, *OLink;

int main() {
    //创建非零元素结点

    //指向非零行列的数组指针
    typedef struct {
        OLink rowhead[100], colhead[100];
        int rows, cols, nums;
    } *CrossList;

    //输入链表
    int m, n;
    printf("请输入最大行数与列数并用“，”隔开\n");
    scanf("%d,%d", &m, &n);
    OLink q;
    CrossList CL;
    CL = (CrossList) malloc(sizeof(CrossList));
    //初始化行
    CL->rows = m;
    //初始化列
    CL->cols = n;
    //记录非零个数
    CL->nums = 0;
    for (int i = 0; i < 100; i++) {
        CL->rowhead[i] = CL->colhead[i] = NULL;
    }

    static int A[100][100];
    int x, y, num;
    do {
        while (getchar() != '\n');//清空缓冲区
        printf("请输入行数,列数,数值并用“，”隔开,如要终止输入请数值输入0\n");
        scanf("%d,%d,%d", &x, &y, &num);
        A[x][y] = num;//从1,1开始
    } while (num);

    //测试
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            printf("%d", A[i][j]);
        }
        printf("\n");
    }

    //建立链表
    //CL->colhead = (OLink)malloc(n * sizeof(OLink));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (A[i + 1][j + 1] != 0)//判断是否非零
            {
                OLNode p;

                //填入所在行数
                p.row = i + 1;
                //填入所在列数
                p.col = j + 1;
                //填入数字
                p.value = A[i + 1][j + 1];
                p.right = NULL;
                p.down = NULL;
                CL->nums++;
                //判断是否是这一行的第一个非零元素
                if (CL->rowhead[i] != NULL) {
                    //从本行头遍历
                    q = CL->rowhead[i];
                    while (q->right != NULL &&
                           q->col < j + 1) {
                        q = q->right;
                    }
                    //遍历到本行最后一个非零元素
                    p.right = q->right;//尾插法
                    q->right = &p;
                }
                    //如果是本行第一个非零元素则行头直接是新创造的结点
                else CL->rowhead[i] = &p;
                //与行操作类似
                if (CL->colhead[j] != NULL) {
                    q = CL->colhead[j];
                    while (q->down != NULL && q->row < i + 1) q = q->down;
                    //遍历到本列最后一个非零元素
                    p.down = q->down;
                    q->down = &p;
                } else CL->colhead[j] = &p;
            }
        }
    //输出链表

//    OLink q ;
    for (int i = 0; i < m; i++) {
        q = CL->rowhead[i];
        while (q) {
            printf("%d行%d列值为%d\n", q->row, q->col, q->value);
            q = q->right;
        }
    }
}
