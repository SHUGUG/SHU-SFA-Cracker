#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct HfTree {
    double weight;    // 权值
    char data;
    struct HfTree *parent;    // 双亲位置
    struct HfTree *left;    // 左孩子位置
    struct HfTree *right;    // 右孩子位置
} HfTree;

typedef struct HfTList {
    struct HfTree *node;
    struct HfTList *next;
} HfTList;

typedef struct HfCode {
    double weight;
    char data;
    char *code;
    double pl;
    struct HfCode *next;
} HfCode;

void init_HfTList(int n, HfTList *list);

void creat_HfTList(int *n, HfTList *list);

void select_two_min(HfTList *list, HfTree **S1, HfTree **S2);

void add_HfTree_to_list(HfTList *list, HfTree *new_tree);

void creat_HfTree(int n, HfTList *list, HfTree **HT);

void init_HfCode(HfCode *HC);

void add_HfCode(HfCode *HC, double weight, char data, char *code, double wpl);

void coding_HfCode(HfTree *HT, HfCode *HC, char *code, double pl);

void calc_HfTree_WPL(HfCode *HC);

void print_HfTree(HfTree *HT, int flag, int *is_left);

void print_HfCode(HfCode *HC);

int main() {
    int n;

    HfTList *list = (struct HfTList *) malloc(sizeof(HfTList));
    creat_HfTList(&n, list);

    HfTree *HT = NULL;
    creat_HfTree(n, list, &HT);

    HfCode *HC = (struct HfCode *) malloc(sizeof(struct HfCode));
    init_HfCode(HC);
    coding_HfCode(HT, HC, "", 0);

    calc_HfTree_WPL(HC);

    int *is_left = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; is_left[i] = 0, ++i);
    printf("\n构造的 Huffman Tree 如下：\n");
    print_HfTree(HT, 0, is_left);

    printf("\n生成的 Huffman Code 如下：\n");
    print_HfCode(HC);

    return 0;
}

void init_HfTList(int n, HfTList *list) {
    HfTList *l = list;
    for (int i = 0; i < n; ++i) {
        l->node = (struct HfTree *) malloc(sizeof(HfTree));
        l->node->weight = 0;
        l->node->data = ' ';
        l->node->parent = NULL;
        l->node->left = NULL;
        l->node->right = NULL;

        if (i + 1 != n) {
            l->next = (HfTList *) malloc(sizeof(HfTList));
            l = l->next;
        } else {
            l->next = NULL;
        }
    }
}

void creat_HfTList(int *n, HfTList *list) {
    char data;
    double weight;
    printf("请输入赫夫曼树叶子结点数量：");
    scanf("%d", n);

    init_HfTList(*n, list);

    printf("请输入 %d 个字符：", *n);
    HfTList *l = list;
    for (int i = 0; i < *n; i++) {
        do {
            scanf("%c", &data);
        } while (data == '\n' || data == ' ');

        l->node->data = data;
        l = l->next;
    }

    printf("请输入上述 %d 个字符对应的权值：", *n);
    l = list;
    for (int i = 0; i < *n; i++) {
        do {
            scanf("%lf", &weight);
        } while (data == '\n' || data == ' ');
        l->node->weight = weight;
        l = l->next;
    }
}

void select_two_min(HfTList *list, HfTree **S1, HfTree **S2) {
    HfTList *l = list;
    double min1 = INT_MAX, min2 = INT_MAX;

    for (; l != NULL; l = l->next) {
        if (l->node->parent == NULL) {
            double weight = l->node->weight;
            if (weight < min1) {
                min2 = min1;
                *S2 = *S1;
                min1 = weight;
                *S1 = l->node;
            } else if (weight < min2 && min1 <= weight) {
                min2 = weight;
                *S2 = l->node;
            }
        }
    }
}

void add_HfTree_to_list(HfTList *list, HfTree *new_tree) {
    HfTList *l = list;
    for (; l->next != NULL; l = l->next);
    HfTList *new_list = (HfTList *) malloc(sizeof(struct HfTList));
    new_list->node = new_tree;
    new_list->next = NULL;
    l->next = new_list;
}

void creat_HfTree(int n, HfTList *list, HfTree **HT) {
    HfTree *S1 = NULL, *S2 = NULL;
    for (; n != 1; n--) {
        select_two_min(list, &S1, &S2);
        HfTree *new_tree = (struct HfTree *) malloc(sizeof(struct HfTree));
        new_tree->weight = S1->weight + S2->weight;
        new_tree->data = ' ';
        new_tree->parent = NULL;
        new_tree->left = S1;
        new_tree->right = S2;

        S1->parent = new_tree;
        S2->parent = new_tree;
        *HT = new_tree;

        add_HfTree_to_list(list, *HT);
    }
}

void init_HfCode(HfCode *HC) {
    HC->weight = 0;
    HC->code = NULL;
    HC->data = ' ';
    HC->pl = 0;
    HC->next = NULL;
}

void add_HfCode(HfCode *HC, double weight, char data, char *code, double wpl) {
    HfCode *c = HC;
    for (; c->next != NULL && strtol(c->next->code, NULL, 2) < strtol(code, NULL, 2) &&
           strlen(c->next->code) <= strlen(code); c = c->next);
    HfCode *new_code = (struct HfCode *) malloc(sizeof(struct HfCode));
    new_code->weight = weight;
    new_code->data = data;
    new_code->code = strdup(code);
    new_code->pl = wpl;
    new_code->next = c->next;
    c->next = new_code;
}

void coding_HfCode(HfTree *HT, HfCode *HC, char *code, double pl) {
    if (HT == NULL) {
        return;
    }

    if (HT->left == NULL && HT->right == NULL) {
        add_HfCode(HC, HT->weight, HT->data, code, pl);
    }

    char *left_code;
    left_code = strdup(code);
    strcat(left_code, "0");
    coding_HfCode(HT->left, HC, left_code, pl + 1);

    char *right_code;
    right_code = strdup(code);
    strcat(right_code, "1");
    coding_HfCode(HT->right, HC, right_code, pl + 1);
}

void calc_HfTree_WPL(HfCode *HC) {
    HfCode *c = HC->next;
    double wpl = 0;
    for (; c != NULL; c = c->next) {
        wpl += c->weight * c->pl;
    }
    HC->pl = wpl;
}

void print_HfTree(HfTree *HT, int flag, int *is_left) {
    if (flag > 0) {
        for (int i = 0; i < flag - 1; ++i) {
            printf(is_left[i] ? "│   " : "    ");
        }
        printf(is_left[flag - 1] ? "├── " : "└── ");
    }

    if (!HT) {
        printf("NULL\n");
        return;
    } else {
        printf("(%g) %c\n", HT->weight, HT->data);
    }

    if (!HT->left && !HT->right) {
        return;
    }

    is_left[flag] = 1;
    print_HfTree(HT->left, flag + 1, is_left);
    is_left[flag] = 0;
    print_HfTree(HT->right, flag + 1, is_left);
}

void print_HfCode(HfCode *HC) {
    HfCode *c = HC->next;
    printf("-------+------+--------+--------+--------------\n");
    printf(" Index | Data | Weight |  P.L.  | Huffman Code \n");
    printf("-------+------+--------+--------+--------------\n");
    for (int i = 1; c != NULL; ++i, c = c->next) {
        printf(" %4d  |   %c  |%6g  |%6g  |  %s\n", i, c->data, c->weight, c->pl, c->code);
    }
    printf("-------+------+--------+--------+--------------\n");
    printf("Weighted Path Length of Tree: %g\n", HC->pl);
}