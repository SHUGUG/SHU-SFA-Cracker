#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct poly {
    int index;
    double data;
    struct poly *next;
} poly;

void creat_poly(poly *object);

void insert_poly(poly *object, int index, double data, int merge);

int get_int(int start, int end);

double get_float(double start, double end);

int is_float(const char n[]);

void output_poly(poly *object);

void merge_poly(poly *object1, poly *object2);

int main() {
    poly *poly1, *poly2;
    poly1 = (poly *) malloc(sizeof(poly));
    poly2 = (poly *) malloc(sizeof(poly));

    creat_poly(poly1);
    creat_poly(poly2);

//    poly poly1, poly2;
//    creat_poly(&poly1);
//    creat_poly(&poly2);
    int index;
    double data, FLOAT_MAX = pow(2, 128);
    printf("----------多项式合并程序（链表版）----------\n");
    int i = 1;
    while (i < 3) {
        printf("\n-----输入第%d个多项式-----\n定义某项的次数，", i);
        index = get_int(0, INT_MAX);
        while (index != -1) {
            printf("\n定义次数为%d的项的系数，", index);
            data = get_float(-FLOAT_MAX, FLOAT_MAX);
            if (i == 1) {
                insert_poly(poly1, index, data, 0);
            } else {
                insert_poly(poly2, index, data, 0);
            }
            printf("该项已设置为%g*x^%d\n", data, index);
            printf("\n继续确定其中某项的次数，或输入-1退出输入，");
            index = get_int(-1, INT_MAX);
        }
        printf("该多项式已设置为：\n");
        if (i == 1) {
            output_poly(poly1);
        } else {
            output_poly(poly2);
        }
        i++;
    }
    if (poly1->data >= poly2->data) {
        merge_poly(poly1,poly2);
    } else {
        merge_poly(poly2,poly1);
    }
    merge_poly(poly1, poly2);
    printf("\n\n这两个多项式合并的结果为：\n");
    output_poly(poly1);
    return 0;
}

void creat_poly(poly *object) {
//    把头指针的值定义为0，index作为记录该多项式的最大次数,data记录个数
    object->index = 0;
    object->data = 0;
//    创建一个为0的常数项
    object->next = (poly *) malloc(sizeof(poly));
    object->next->index = 0;
    object->next->data = 0;
    object->next->next = NULL;
}

void insert_poly(poly *object, int index, double data, int merge) {
    poly *p, *q;

    if (object->index < index) {
        q = (poly *) malloc(sizeof(poly));
        q->index = index;
        q->data = data;
        q->next = object->next;
        object->next = q;
        object->index = index;
        object->data = object->data + 1;
    } else {
        p = object->next;
        while (!(p == NULL || p->index == index || p->next->index < index)) {
            p = p->next;
        }
//        printf("p->index=%d\n", p->index);
//        printf("p->next->index=%d\n",p->next->index);

        if (p->index == index) {
            if (merge == 0) {
                p->data = data;
            } else {
                p->data += data;
            }
        } else {
            q = (poly *) malloc(sizeof(poly));
            q->index = index;
            q->data = data;
            q->next = p->next;
            p->next = q;
            object->data = object->data + 1;
        }
    }
}

void output_poly(poly *object) {
    poly *result;
    result = object->next;
    while (result != NULL) {
        if (result->data < 0) {
            if (result->index != 0) {
                printf(" %g*x^%d", result->data, result->index);
            } else {
                printf(" %g", result->data);
            }
        } else if (result->data > 0) {
            if (result->index != 0) {
                printf(" +%g*x^%d", result->data, result->index);
            } else {
                printf(" +%g", result->data);
            }
        }
        result = result->next;
    }
}

void merge_poly(poly *object1, poly *object2) {
//    将多项式n合并到m中
    poly *max, *min;
    max = object1->next;
    min = object2->next;

    while (max != NULL) {
        while (min != NULL) {
            insert_poly(object1, max->index, max->data, 1);
            max = max->next;
        }
        min=min->next;
    }
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

