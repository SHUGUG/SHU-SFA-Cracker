#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100

typedef struct ArcNode {
    int adj_vex;
    struct ArcNode *next_arc;
//        float info;
} ArcNode;

typedef struct VNode {
    char data;
    ArcNode *first_arc;
} VNode;

typedef struct {
    VNode vertices[MAX_NUM];
    int vex_num, arc_num;
//        int kind;
} ALGraph;

void CreatGraph(ALGraph *G);

int LocateVex(ALGraph G, char u);

char GetVex(ALGraph G, int v);

ArcNode *newArcNodePtr(int adj_vex, ArcNode *next_arc);

int InsertArc(ALGraph *G, char v1, char v2);

void PrintGraph(ALGraph G);

void DFSTraverse(ALGraph G);

void DFS(ALGraph G, int v);

void BFSTraverse(ALGraph G);

int main() {

    ALGraph G;
    CreatGraph(&G);
    PrintGraph(G);
    DFSTraverse(G);
    BFSTraverse(G);

    return 0;
}

void CreatGraph(ALGraph *G) {
    int vex_num, arc_num;

    (*G).arc_num = 0;
    (*G).vex_num = 0;

    printf("输入有向图的顶点数：");
    scanf("%d", &vex_num);

    printf("输入有向图的弧数：");
    scanf("%d", &arc_num);

    printf("请录入 %d 个顶点，不同顶点之间用空格隔开：", vex_num);
    for (int i = 0; i < vex_num; i++) {
        char data;
        do {
            data = getchar();
        } while (data == '\n' || data == ' ');

        (*G).vertices[i].data = data;
        (*G).vertices[i].first_arc = NULL;
        (*G).vex_num++;
    }

    printf("请为有向图依次录入 %d 条弧的信息，顶点之间用空格隔开：\n", arc_num);
    for (int i = 0; i < arc_num; i++) {
        int insert_result = 0;
        do {
            char v1, v2;

            printf("第 %d 条弧：", i + 1);
            do {
                v1 = getchar();
            } while (v1 == '\n' || v1 == ' ');
            do {
                v2 = getchar();
            } while (v2 == '\n' || v2 == ' ');

            // 插入弧<v1, v2>
            insert_result = InsertArc(G, v1, v2);
        } while (insert_result == -1);
    }
}

// 查找,返回顶点u在图中的位置
int LocateVex(ALGraph G, char u) {
    for (int i = 0; i < G.vex_num; i++) {
        if (G.vertices[i].data == u) {
            return i;
        }
    }
//    不存在顶点
    return -1;
}

// 取值 返回索引v处的顶点值
char GetVex(ALGraph G, int v) {
    if (v < 0 || v >= G.vex_num) {
//        指定的顶点不存在
        return '\0';
    }
    return G.vertices[v].data;
}

// 构造一个弧结点
ArcNode *newArcNodePtr(int adj_vex, ArcNode *next_arc) {
    ArcNode *p = (ArcNode *) malloc(sizeof(ArcNode));
    p->adj_vex = adj_vex;
    p->next_arc = next_arc;
    return p;
}

// 插入弧
int InsertArc(ALGraph *G, char v1, char v2) {
    int tail, head;
    ArcNode *r;
    ArcNode *pre;

    tail = LocateVex(*G, v1);
    head = LocateVex(*G, v2);
    if (tail == -1 || head == -1) {
        printf("顶点不存在");
        return -1;
    }
    if (tail == head) {
        printf("弧头与弧尾不能相同");
        return -1;
    }

    pre = NULL;
    // 指向以tail为尾的首条弧
    r = G->vertices[tail].first_arc;
    while (r != NULL && r->adj_vex < head) {
        pre = r;
        r = r->next_arc;
    }

    if (r != NULL && r->adj_vex == head) {
        printf("已存储相同的弧");
        return -1;
    } else {
        if (pre == NULL) {
            G->vertices[tail].first_arc = newArcNodePtr(head, r);
        } else {
            pre->next_arc = newArcNodePtr(head, r);
        }
        (*G).arc_num++;
    }

    return 0;
}

void PrintGraph(ALGraph G) {
    int i;
    ArcNode *p;

    if (G.vex_num == 0) {
        printf("空图\n");
        return;
    }

    printf("当前图包含 %d 个顶点， %d 条弧\n", G.vex_num, G.arc_num);

    for (i = 0; i < G.vex_num; i++) {
        printf("%c ===> ", G.vertices[i].data);

        p = G.vertices[i].first_arc;
        while (p != NULL) {
            printf("%c ", G.vertices[p->adj_vex].data);

            p = p->next_arc;

            if (p != NULL) {
                printf("- ");
            }
        }

        printf("\n");
    }
}

// 返回顶点v的首个邻接点
int FirstAdjVex(ALGraph G, char v) {
    int k;
    ArcNode *r;

    // 首先需要判断该顶点是否存在
    k = LocateVex(G, v);
    if (k == -1) {
        return -1;    // 指定的顶点不存在
    }

    r = G.vertices[k].first_arc;
    if (r == NULL) {
        return -1;
    } else {
        return r->adj_vex;
    }
}

// 返回顶点v的(相对于w的)下一个邻接点
int NextAdjVex(ALGraph G, char v, char w) {
    int kv, kw;
    ArcNode *r;

    // 首先需要判断该顶点是否存在
    kv = LocateVex(G, v);
    if (kv == -1) {
        return -1;    // 指定的顶点不存在
    }

    // 首先需要判断该顶点是否存在
    kw = LocateVex(G, w);
    if (kw == -1) {
        return -1;    // 指定的顶点不存在
    }

    r = G.vertices[kv].first_arc;
    if (r == NULL) {
        return -1;  // 链表为空
    }

    // 在链表中查找w
    while (r != NULL && r->adj_vex < kw) {
        r = r->next_arc;
    }

    // 如果没找到w
    if (r == NULL) {
        return -1;
    }

    // 如果找到了w，但是w后面没有别的顶点，那么也无法返回邻接点
    if (r->adj_vex == kw && r->next_arc != NULL) {
        return r->next_arc->adj_vex;
    }

    return -1;
}

int visited[MAX_NUM];

void DFSTraverse(ALGraph G) {
    printf("深度优先遍历(DFS)结果如下: \n");
    // 访问标志数组初始化
    for (int i = 0; i < G.vex_num; i++) {
        visited[i] = 0;
    }

    // 此处需要遍历的原因是并不能保证所有顶点都连接在了一起
    for (int i = 0; i < G.vex_num; i++) {
        if (!visited[i]) {
            DFS(G, i);  // 对尚未访问的顶点调用DFS
        }
    }
}

void DFS(ALGraph G, int v) {
    // 从第v个顶点出发递归地深度优先遍历图G
    visited[v] = 1;

    // 访问第v个顶点
    printf("%c", G.vertices[v].data);

    for (int i = FirstAdjVex(G, G.vertices[v].data);
         i >= 0;
         i = NextAdjVex(G, G.vertices[v].data, G.vertices[i].data)) {
        if (!visited[i]) {
            DFS(G, i);  // 对尚未访问的顶点调用DFS
        }
    }
}

void BFSTraverse(ALGraph G){

}
