#include "stdio.h"

int main() {
    char in_str[9999], out_str[9999];
    int len;
    printf("输入字符串，按照字母表顺序排序，非英文字母以外的字符将会被忽略\n");
    printf("请输入任意长度小于9999的字符串：");
//    scanf("%s", in_str);
    fgets(in_str, 9999, stdin);
    for (int i = 0, j = 0; in_str[i] != 0; i++) {
        if (('A' <= in_str[i] && in_str[i] <= 'Z') || ('a' <= in_str[i] && in_str[i] <= 'z')) {
            out_str[j] = in_str[i];
            j++;
        }
    }
    printf("输入的有效字符串为：\n%s\n", out_str);
    for (len = 0; out_str[len] != 0; len++);
    printf("共计%d个字符\n", len);
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            int temp1 = (out_str[j] > 'Z') ? (out_str[j] - ('a' - 'A')) : out_str[j];
            int temp2 = (out_str[j + 1] > 'Z') ? (out_str[j + 1] - ('a' - 'A')) : out_str[j + 1];
//            if (out_str[j] - out_str[j + 1] > 0 && out_str[j] - out_str[j + 1] != 'a' - 'A' &&
//                out_str[j] - out_str[j + 1] != 'A' - 'a') {
            if (temp1 - temp2 > 0) {
                char temp = out_str[j + 1];
                out_str[j + 1] = out_str[j];
                out_str[j] = temp;
            }
        }
    }
    printf("排序后的字符串为：\n%s\n", out_str);

    return 0;
}