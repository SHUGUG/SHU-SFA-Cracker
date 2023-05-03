#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int main() {

    char s[10];
    printf("请输入一个整数，该程序可求出该数的对称数：");
    gets(s);
    int len, i, n;//判断字符串是否是回文,n用于判断
    len = strlen(s);
    for (i = 0; i < (len / 2); i++) {
        if (s[i] == s[len - 1 - i]) {
            n = 1;
        } else {
            n = 0;
            break;
        }
    }
    if (n == 1) {
        printf("该数已经是回文数。");
        return 0;
    }


    if (n == 0) {
        printf("用户输入的数不是回文。需要计算。");
        int num, num1, revnum = 0, temp;
        num = atoi(s);//强制转换为int类型
        do {
            temp = num;//把正的数存一下
            do//把数倒过来
            {
                num1 = num % 10;
                num = num / 10;
                revnum = revnum * 10 + num1;
            } while (num != 0);

            num = temp + revnum;
            if (temp != revnum) {
                revnum = 0;
            } else {
                break;
            }
//        } while (temp != revnum);
        } while (1);
        printf("%d", revnum);
    }
}
