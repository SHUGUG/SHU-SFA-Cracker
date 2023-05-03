#include <stdio.h>
#include <stdlib.h>

typedef struct OLNode {
    int row;
    int col;
    double val;
    struct OLNode *down;
    struct OLNode *right;
} OLNode;

void creat_node(OLNode *node, int row, int col, double val, OLNode *down, OLNode *right);

void add_node(OLNode *node, OLNode *new_node);

void get_elem_by_index(OLNode *node, int row, int col, double *val);

int main() {
    OLNode MAT1;
    int row, col, height, width;
    double val;
    printf("请输入稀疏矩阵MAT总的行，列：");
    scanf("%d%d", &height, &width);
    creat_node(&MAT1, 0, 0, 0, &MAT1, &MAT1);
    do {
        printf("请输入MAT中的非0元素。格式为 行 列 元素：");
        scanf("%d%d%lf", &row, &col, &val);
        if (row > 0 && col > 0) {
            if (height < row) {
                height = row;
                printf("输入的行值大于原设定值，已将MAT的行重新设置为%d\n", row);
            }
            if (width < col) {
                width = col;
                printf("输入的列值大于原设定值，已将MAT的列重新设置为%d\n", col);
            }
            if (val != 0) {
                OLNode *new_node = (OLNode *) malloc(sizeof(OLNode));
                creat_node(new_node, row, col, val, NULL, NULL);
                add_node(&MAT1, new_node);
                printf("设置成功。可输入0 0 0结束输入。\n");
            } else {
                printf("输入的值为0，不存储本次输入\n");
            }
        } else if (row != 0 || col != 0 || val != 0) {
            printf("输入数据有误，请重新输入或输入0 0 0结束输入。\n");
        }
    } while (!(row == 0 && col == 0 && val == 0));

//    do {
//        printf("输入：");
//        scanf("%d%d", &row, &col);
//        get_elem_by_index(&MAT1, row, col, &val);
//        printf("%g\n", val);
//    } while (!(row == 0 && col == 0));

    printf("输入的矩阵为：\n");
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            get_elem_by_index(&MAT1, i, j, &val);
            printf("%6g ", val);
        }
        printf("\n");
    }
    return 0;
}

void creat_node(OLNode *node, int row, int col, double val, OLNode *down, OLNode *right) {
    node->row = row;
    node->col = col;
    node->val = val;
    node->down = down;
    node->right = right;
}

void add_node(OLNode *node, OLNode *new_node) {
//    获取新node数据
    int row = new_node->row;
    int col = new_node->col;
    double val = new_node->val;

//    遍历down head，若行不存在则新建并移至该node，否则直接移至该node
    OLNode *down = node;
    while (down->down != node && down->down->row < row) {
        down = down->down;
    }
    if (down->down->row != row) {
        OLNode *new_down = (OLNode *) malloc(sizeof(OLNode));
        new_down->row = row;
        new_down->col = 0;
        new_down->val = 0;
        new_down->down = down->down;
        new_down->right = new_down;
        down->down = new_down;
    }
    down = down->down;

//    遍历right head，若列不存在则新建并移至该node，否则直接移至该node
    OLNode *right = node;
    while (right->right != node && right->right->col < col) {
        right = right->right;
    }
    if (right->right->col != col) {
        OLNode *new_right = (OLNode *) malloc(sizeof(OLNode));
        new_right->row = 0;
        new_right->col = col;
        new_right->val = 0;
        new_right->down = new_right;
        new_right->right = right->right;
        right->right = new_right;
    }
    right = right->right;

//    右移down，下移right至要插入的node位置前
    OLNode *p_down = down;
    while (down->right != p_down && down->right->col < col) {
        down = down->right;
    }

    OLNode *p_right = right;
    while (right->down != p_right && right->down->row < row) {
        right = right->down;
    }

    if (down->right == right->down) {
//        如果down的右node与right的下node一致，说明输入的row与col已存在，直接修改其值
        down->right->val = val;
        free(new_node);
    } else {
//        否则进行插入操作
        new_node->down = right->down;
        new_node->right = down->right;
        right->down = new_node;
        down->right = new_node;
//        p_down->val++;
//        p_right->val++;
//        node->val++;
    }
}

void get_elem_by_index(OLNode *node, int row, int col, double *val) {
    OLNode *p = node;
    do {
        if (p->row < row && p->down->row > row) {
            *val = 0;
            return;
        }
        p = p->down;
    } while (p->row != row && p != node);
    OLNode *q = p;
    do {
        if (q->col < col && q->right->col > col) {
            *val = 0;
            return;
        }
        q = q->right;
    } while (q->col != col && q != p);
    *val = q->val;
}
