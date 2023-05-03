#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int get_int(int start, int end);

double get_float(double start, double end);

int is_float(const char n[]);

int output_poly(const double p[], int max_times);

int main() {
//    while (1) {
//        double a = get_float(-8000, 8000);
//        printf("%g\n", a);
//    }

    double FLOAT_MAX = pow(2, 128);
    int max_times, times;
    double factors;
    printf("多项式合并程序\n");
    printf("首先确定两个多项式的最高次数，");
    max_times = get_int(0, INT_MAX);

    printf("多项式的最高次数已确定为%d\n", max_times);
    double p1[max_times + 1], p2[max_times + 1], p_result[max_times + 1];
    for (int i = 0; i <= max_times; i++) {
        p1[i] = 0;
        p2[i] = 0;
    }
    int j = 1;
    while (j < 3) {
        printf("\n-----输入第%d个多项式-----\n定义某项的次数，", j);
        times = get_int(0, max_times);
        while (times != -1) {
            printf("\n定义次数为%d的项的系数，", times);
            factors = get_float(-FLOAT_MAX, FLOAT_MAX);
            if (j == 1) {
                p1[times] = factors;
            } else if (j == 2) {
                p2[times] = factors;
            }
            printf("该项已设置为%g*x^%d\n", factors, times);
            printf("\n继续确定其中某项的次数，或输入-1退出输入，");
            times = get_int(-1, max_times);
        }
        printf("该多项式已设置为：\n");
        if (j == 1) {
            output_poly(p1, max_times);
        } else if (j == 2) {
            output_poly(p2, max_times);
        }
        j++;
    }
    for (int i = 0; i <= max_times; i++) {
        p_result[i] = p1[i] + p2[i];
    }
    printf("\n\n这两个多项式合并的结果为：\n");
    output_poly(p_result, max_times);

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
            if ((a[i] == '-' || a[i] == '+') && i != 0) {
                is_num = 0;
                break;
            } else if ((a[i] < '0' || a[i] > '9') && a[i] != '-' && a[i] != '+') {
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

double get_float(double start, double end) {
    char n[1000];
    int success = 0;
    double num;
    printf("输入范围在[%g,%g]内的数：", start, end);
    while (success == 0) {
        scanf("%s", n);
        if (is_float(n)) {
            num = strtod(n, NULL);
            if (start <= num && num <= end) {
                success++;
            } else {
                printf("\n输入有误，请输入范围在[%g,%g]内的数：", start, end);
            }
        } else {
            printf("\n输入有误，请输入范围在[%g,%g]内的数：", start, end);
        }
    }
    return num;
}

int is_float(const char n[]) {
    int dot_count = 0, e_count = 0, is_num = 0;
    for (int i = 0; n[i] != 0; i++) {
        if (n[i] == '-' || n[i] == '+') {
            if (i != 0 && n[i - 1] != 'e' && n[i - 1] != 'E') {
                return 0;
            }
        } else if (n[i] == 'e' || n[i] == 'E') {
            if (i != 0 && n[i + 1] != 0 && e_count == 0 && '0' <= n[i - 1] && n[i - 1] <= '9') {
                e_count++;
            } else {
                return 0;
            }
        } else if (n[i] == '.') {
            if (dot_count == 0 && e_count == 0) {
                dot_count++;
            } else {
                return 0;
            }
        } else if ((n[i] < '0' || n[i] > '9') && n[i] != '-' && n[i] != '+' && n[i] != '.' && n[i] != 'e' &&
                   n[i] != 'E') {
            return 0;
        } else {
            is_num = 1;
        }
    }
    if (is_num) {
        return 1;
    } else {
        return 0;
    }
}

int output_poly(const double p[], int max_times) {
    for (int i = max_times; i >= 0; i--) {
        if (p[i] < 0) {
            if (i != 0) {
                printf(" %g*x^%d", p[i], i);
            } else {
                printf(" %g", p[i]);
            }
        } else if (p[i] > 0) {
            if (i != 0) {
                printf(" +%g*x^%d", p[i], i);
            } else {
                printf(" +%g", p[i]);
            }
        }
    }
    return 0;
}