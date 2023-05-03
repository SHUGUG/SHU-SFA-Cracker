#include<stdio.h>
#include<stdlib.h>

//定义函数
int find() {
    int array[3][4] = {{11, 12, 13, 14},
                       {21, 22, 23, 24},
                       {31, 32, 33, 34}};
    int m, n, s, t;
    char ii[10], jj[10];
    int *o, *a, oo, aa;
    int i = atoi(ii), j = atoi(jj);
    //定义数组和一些变量

    printf("本实验是查找指定的3行4列数组某一元素周边元素的值和地址\n本实验使用的数组Array[3][4]数组为:\n");
    for (m = 0; m < 3; m++) {
        for (n = 0; n < 4; n++) {
            printf("%d ", array[m][n]);
        }
        printf("\n");
    }
    printf("\n");//输出数组

//判断行数输出是否有误
    int status = 0, inum = 1;//定义状态量
    printf("请输入查找元素的行数(1-3)：");
    while (status == 0) {
        scanf("%s", ii);
        for (int ei = 0; ii[ei] != 0; ei++) {
            if (ii[ei] < '1' || ii[ei] > '3') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(ii) < 1 || atoi(ii) > 3))) {
            printf("行数输出有误，请重新输入：");
            inum = 1;

        } else {
            i = atoi(ii);
            status = 1;
        }
    }

//判断列数输出是否有误
    status = 0;
    int jnum = 1;
    printf("请输入查找元素的列数(1-4)：");
    while (status == 0) {
        scanf("%s", &jj);
        for (int ej = 0; ii[ej] != 0; ej++) {
            if (jj[ej] < '1' || jj[ej] > '4') {
                jnum = 0;
                break;
            }

        }
        if (jnum == 0 || (jnum == 1 && (atoi(jj) < 1 || atoi(jj) > 4))) {
            printf("行数输出有误，请重新输入：");
            jnum = 1;

        } else {
            j = atoi(jj);
            status = 1;
        }
    }

//输出自身元素和其地址
    oo = array[i - 1][j - 1];
    o = &array[i - 1][j - 1];
    printf("数组第%d行第%d列的元素是%d\n数组第%d行第%d列的地址是%p\n\n", i, j, oo, i, j, o);
    printf("元素周边的元素有：\n");

//输出周边元素及其地址
    for (s = -1; s <= 1; s = s + 1) {
        for (t = -1; t <= 1; t = t + 1) {
            if (((i + s) >= 1 && (i + s) <= 3) && ((j + t) >= 1 && (j + t) <= 4) && (s != 0 || t != 0)) {
                aa = array[i - 1 + s][j - 1 + t];
                a = &array[i - 1 + s][j - 1 + t];
                printf("数组第%d行第%d列的元素是%d\n数组第%d行第%d列的地址是%p\n\n", i + s, j + t, aa, i + s, j + t, a);
            }
        }
    }
    return 0;
}

int main() {
    find();
    char k[1] = "y";
    printf("输入y继续，输入n或其它退出");
    scanf("%s", k);
    while (k[0] == 'y') {
        find();
        printf("输入y继续，输入n或其它退出");
        scanf("%s", k);
    }
        return 0;
}
