#include <stdio.h>
#include "stack.c"


void check_brackets(void);

int main() {
//    int status;
    printf("字符串括号匹配检查器\n");
//    while (1){
    printf("\n请输入字符串：");
    check_brackets();
//        fflush(stdin);
//    }
    return 0;
}

void check_brackets(void) {
    long str, e;
    HanoiStack S;
    InitStack(&S);
    do {
        str = getchar();
        if (str == '(' || str == '[' || str == '{') {
            Push(&S, str);
        } else if (str == ')' || str == ']' || str == '}') {
            Pop(&S, &e);
            if (str == ')' && e != '(' || str == ']' && e != '[' || str == '}' && e != '{') {
                printf("括号不匹配");
                return;
            }
        }
    } while (str != '\n');
    if (!StackEmpty(S)) {
        printf("括号数量不匹配");
        return;
    }
    printf("所有括号都匹配");
}
