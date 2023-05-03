#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    int data;     /*数据域，保存结点的值 */
    struct Lnode *next;      /*指针域*/
} LNode;        /*结点的类型 */

int main() {
//    create_LinkList();
    /*  头插入法创建单链表,链表的头结点head作为返回值  */
    int data;
    LNode *head, *p, *q;
    head = (LNode *) malloc(sizeof(LNode));
    head->next = NULL;       /*  创建链表的表头结点head  */
    while (1) {
        printf("输入：");
        scanf("%d", &data);
        if (data == 32767) {
            break;
        }
        p = (LNode *) malloc(sizeof(LNode));
        p->data = data;     /*  数据域赋值  */
        p->next = head->next;
        head->next = p;
//        free(p);
        /*  钩链，新创建的结点总是作为第一个结点  */
    }

    int key = 5, e = 23333;
    p = head;
    while (p != NULL && p->next->data != key) {
        p = p->next;
    }
    q = (LNode *) malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    int k;

    return 0;
}