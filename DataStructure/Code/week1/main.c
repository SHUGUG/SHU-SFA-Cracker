#include <stdio.h>
#include <stdlib.h>

int get_int(int start, int end);

int main() {
    int m, n;
    printf("程序将根据用户输入的行列生成一个二维数组\n");
    printf("随后根据用户指定的元素，打印出其周围元素的值及内存地址\n");
    printf("下面确定数组的行数m，");
    m = get_int(1, 10);
    printf("下面确定数组的列数n，");
    n = get_int(1, 10);
    printf("\n该数组已定义为：\n");
    int a[m][n];

//    填充数组
    int k = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = k;
            printf("%4d", a[i][j]);
            k++;
        }
        printf("\n");
    }

//    16进制的地址和大小
    int add = &a, size = 0X4;
    printf("设数组的首地址为0x%4X，每个元素占用%X字节\n", add, size);

//    element为用户输入元素，pq为其在数组中的索引
    int element, p, q;
    printf("\n选择元素，");
    element = get_int(1, k - 1);
    while (element != 0) {
        p = (element % n == 0) ? element / n - 1 : element / n;
//        p=((element+1)/n)-1;
        q = element - p * n - 1;
//        printf("p:%d q:%d\n", p, q);
        printf("\n┌─周围元素─┬──内存地址──┐\n");
//        printf("┌────────────┬─────────────┐\n");
//        printf("│   周围元素   │   内存地址   │\n");
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
//                同行，相差一列/同列，相差一行/行列均相差1，则为周围元素
                if ((i - p == 0 && abs(j - q) == 1) || (abs(i - p) == 1 && j - q == 0) ||
                    (abs(i - p) == 1 && abs(j - q) == 1)) {
                    printf("│ %5d  │  0x%4X   │\n", a[i][j], add + (a[i][j] - a[0][0]) * size);
                }
            }
        }
        printf("└────────┴───────────┘\n");
        printf("\n选择元素，或输入0退出程序，");
        element = get_int(0, k - 1);
    }

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
