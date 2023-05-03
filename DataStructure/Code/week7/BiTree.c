#include <stdio.h>
#include <stdlib.h>

/* 二叉树结点定义 */
typedef struct BiTNode {
    char data;             // 结点元素
    struct BiTNode *left;     // 左孩子指针
    struct BiTNode *right;     // 右孩子指针
} BiTNode, *BiTree;

void InitBiTree(BiTree *T) {
    *T = NULL;
}

void CreateBiTree(BiTree *T) {
    char data;
    do {
        data = getchar();
    } while (data == '\n');

    if (data == '*') {
        *T = NULL;
    } else {
        *T = (BiTree) malloc(sizeof(BiTNode));
        (*T)->data = data;
        printf("输入节点%c的左子树值：", data);
        CreateBiTree(&((*T)->left));
        printf("输入节点%c的右子树值：", data);
        CreateBiTree(&(*T)->right);
    }
}

void PreTraverse(BiTree T) {
    if (T != NULL) {
        printf("%c", T->data);
        PreTraverse(T->left);
        PreTraverse(T->right);
    }
}

void InTraverse(BiTree T) {
    if (T != NULL) {
        InTraverse(T->left);
        printf("%c", T->data);
        InTraverse(T->right);
    }
}

void PostTraverse(BiTree T) {
    if (T != NULL) {
        PostTraverse(T->left);
        PostTraverse(T->right);
        printf("%c", T->data);
    }
}


int is_left[100] = {0};

void PrintTree(BiTree T, int flag) {
    if (flag > 0) {
        for (int i = 0; i < flag - 1; ++i) {
            printf(is_left[i] ? "│   " : "    ");
        }
        printf(is_left[flag - 1] ? "├── " : "└── ");
    }

    if (!T) {
        printf("NULL\n");
        return;
    } else {
        printf("%c\n", T->data);
    }

    if (!T->left && !T->right) {
        return;
    }

    is_left[flag] = 1;
    PrintTree(T->left, flag + 1);
    is_left[flag] = 0;
    PrintTree(T->right, flag + 1);
}

int main() {
    BiTree T;
    InitBiTree(&T);
    printf("+----创建二叉树----+\n");
    printf("+---用 * 表示空---+\n");
    printf("\n输入头结点的值：");
    CreateBiTree(&T);
    printf("\n前序遍历：");
    PreTraverse(T);
    printf("\n中序遍历：");
    InTraverse(T);
    printf("\n后序遍历：");
    PostTraverse(T);
    printf("\n图形化输出：\n");
    PrintTree(T, 0);

    return 0;
}
