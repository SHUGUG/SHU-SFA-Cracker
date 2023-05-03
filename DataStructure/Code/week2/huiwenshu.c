#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_int(int start, int end);

int is_hws(int num);

int main() {
//    printf("%d", is_hws(1031));

    int start, end, temp, count = 0;
    printf("用户输入起始范围，程序输出范围内的回文数\n");
    printf("输入起始值，");
    start = get_int(0, INT_MAX);
    printf("输入结束值，");
    end = get_int(0, INT_MAX);
    if (start > end) {
        temp = end;
        end = start;
        start = temp;
    }
    for (int i = start; i <= end; i++) {
        if (is_hws(i)) {
            printf("%d\n", i);
            count++;
        }
    }
    printf("\n共找到%d个回文数\n", count);

    return 0;
}

//用于获取指定范围内的整数，进行了错误处理
int get_int(int start, int end) {
    char a[1000];
    int status = 0, is_num = 1, num;
    printf("请输入一个范围在[%d,%d]内的整数：", start, end);
    while (status == 0) {
        scanf("%s", a);
//        判断用户输入的数据是否含有除了数字以外的字符
        for (int i = 0; a[i] != 0; i++) {
            if (a[i] < '0' || a[i] > '9') {
                is_num = 0;
                break;
            }
        }
//        只要is_num为0，后面的atoi不会执行。判断是否在范围内
        if (is_num == 0 || (is_num == 1 && (atoi(a) < start || atoi(a) > end))) {
            printf("\n错误，请重新输入一个范围在[%d,%d]内的整数：", start, end);
            is_num = 1;
        } else {
            num = atoi(a);
            status = 1;
        }
    }

    return num;
}

int is_hws(int num) {
    int n, i = 1, num_list[999] = {0};
    while (num != 0) {
        n = num % 10;
        num_list[i] = n;
        num = num / 10;
        i++;
    }
    i--;
    for (int j = 1; j <= i / 2 + 1; j++, i--) {
        if (num_list[i] != num_list[j]) {
            return 0;
        }
    }
    return 1;
}
