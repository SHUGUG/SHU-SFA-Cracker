typedef struct link_scanf //字符链表
{
    char elem;  //定义字符元素
    struct link_scanf* next;  //定义尾指针
}link_scanf;

typedef struct link_arc  //弧链表
{
    int headVex;   //弧头顶点
    int tailVex;   //弧尾顶点
    struct link_arc* headLink; //弧头相同的下一条弧
    struct link_arc* tailLink; //弧尾相同的下一条弧
    int weight;    //权重
}link_arc;

typedef struct link_vex  //顶点链表
{
    char elem;    //顶点元素
    link_arc* firstIn;  //指向该顶点的第一条弧
    link_arc* firstOut;  //从该顶点出发的第一条弧
}link_vex;

typedef struct    //有向图
{
    link_vex xList[20];  //顶点表序号
    int vexNum;    //顶点数
    int arcNum;    //弧数
}OLGraph;

typedef struct link_stack //弧表栈
{
    link_arc* point;  //指向弧表
    struct link_stack* next;
}link_stack;