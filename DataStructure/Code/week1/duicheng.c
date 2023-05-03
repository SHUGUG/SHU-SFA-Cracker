#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main() {
//定义
    printf("##本程序生成指定范围内的对称数（1-9999999999）##\n\n");
    char aa[10], bb[10];
    int a, b;

//勘误1
    printf("请输入生成对称数的范围的最小值：");
    int status = 0, inum = 1;//定义状态量
    while (status == 0) {
        scanf("%s", aa);
        for (int i = 0; aa[i] != 0; i++) {
            if (aa[i] < '0' || aa[i] > '9') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(aa) > 9999999999))) {
            printf("格式错误，请重新输入生成对称数的范围的最小值：");
            inum = 1;

        } else {
            a = atoi(aa);
            status = 1;
        }
    }

//勘误2
    printf("请输入生成对称数的范围的最大值：");
    status = 0, inum = 1;//定义状态量
    while (status == 0) {
        scanf("%s", bb);
        for (int j = 0; bb[j] != 0; j++) {
            if (bb[j] < '0' || bb[j] > '9') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(bb) > 9999999999))) {
            printf("格式错误，请重新输入生成对称数的范围的最大值：");
            inum = 1;

        } else {
            b = atoi(bb);
            status = 1;
        }
    }
    printf("%d\n%d", a, b);
//////////

//将正确数字转换成字符数组类型
    int k = 0;
    int z = 0;
    int y = 0;
    for (; a + k > b; k++) {
        //printf("%d",k);//shiyan
        char str[10];
        int d = a + k;//定义对称数
        itoa(d, str, 10);//数转为字符数组
        int len = strlen(str);
        //printf("%d\n",len);//shiyan

        if (len % 2 == 1)//奇数
        {
            int ji = (len + 1) / 2;
            for (int ji1 = 1; ji - ji1 < 1; ji1++) {
                if (str[ji - ji1] == str[ji + ji1])
                    z++;
            }
            printf("%d", d);//shiyan
            if (z == (len - 1) / 2)
                printf("%10d\n", d);
        }

        if (len % 2 == 0)//偶数
        {
            int ou = (len / 2) - 1;
            for (int ou1 = 0; ou - ou1 < 1; ou1++) {
                if (str[ou - ou1] == str[ou + 1 + ou1])
                    y++;
            }
            if (y == len / 2)
                printf("%10d\n", d);
        }
    }
    return 0;
}
