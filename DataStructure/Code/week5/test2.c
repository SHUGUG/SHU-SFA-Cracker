#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

//十字链表的结构类型定义：
typedef struct OLNode
{
    int row,col; //非零元素的行和列下标
    int value; //值
    struct OLNode *right; //非零元素所在行表、列表的后继链域
    struct OLNode *down;
}OLNode, *OLink;

typedef struct
{
    OLink *rhead; //行、列链表的头指针(指向指针的指针)
    OLink *chead;
    int mu,nu,tu; //稀疏矩阵的行数、列数、非零元素的个数
}CrossList;

int CreateSMatrix(CrossList *M)
{
    int m, n, t, i, j, e;
    int k,flag;
    OLNode* p;
    OLNode* q;

//    if(M->rhead) free(M->rhead);//头结点的指针域均为空
//    if(M->chead) free(M->chead);

    do
    {
        flag=1;
        printf("输入需要创建的矩阵的行数、列数以及非零元的个数（以空格间隔）：");
        scanf("%d %d %d", &m,&n,&t); //输入M的行数,列数和非零元素的个数
        if(m<0||n<0||t<0||t>m*n)
            flag=0;
        if(flag==0)
        {printf("输入错误请重新输入!\n");}

    }
    while(!flag);//为头结点赋值
    {
        M->mu=m;
        M->nu=n;
        M->tu=t;
    }
    if(!(M->rhead=(OLink *)malloc((m+1)*sizeof(OLink))))//m+1 n+1是为了下标从1开始
        return 0;
    if(!(M->chead=(OLink * )malloc((n+1)*sizeof(OLink))))
        return 0;
    //初始化行、列头指针，各行、列链表为空的链表
    for( k=1; k<m+1; k++)
    {
        M->rhead[k] = NULL;
    }
    for( k=1; k<n+1; k++)
    {
        M->chead[k] = NULL;
    }
    //插入
    for( k=1;k<t+1;k++)
    {
        do
        {
            flag=1;
            printf("输入第%d个非零元的行号、列号以及值（以空格间隔）：",k);
            scanf("%d %d %d", &i,&j,&e);
            if(i<=0||j<=0||i>m||j>n)
                flag=0;
            if(flag==0)
                printf("输入错误请重新输入!\n");

        }
        while(!flag);
        {
            if(!(p=(OLNode *)malloc(sizeof(OLNode))))
                return 0;
            //创建非零元结点p
            p->row=i;
            p->col=j;
            p->value=e;

            if(M->rhead[i]==NULL||M->rhead[i]->col>j)//此行中没有没有结点或要插入已有结点之前
            {
                p->right=M->rhead[i];
                M->rhead[i]=p;//M->rhead[i]始终指向该行第一个结点
            }
            else
            {
                //从表头开始寻找此行中要插在其后的已有结点
                for(q=M->rhead[i];q->right!=NULL&&q->right->col<j;q=q->right)
                {
                    p->right=q->right;
                    q->right=p;
                }
            }
            //列插入与行类似
            if(M->chead[j]==NULL||M->chead[j]->row>i)
            {
                p->down=M->chead[j];
                M->chead[j]=p;
            }
            else
            {
                //寻找列表中的插入位置
                for(q=M->chead[j];q->down&&q->down->row<i;q=q->down)
                {
                    p->down=q->down;
                    q->down=p;
                }
            }
        }
    }
    return 1;
}

void PrintSMatrix(CrossList *M)
{
    OLNode* p;
    int i,j;
    printf("已创建%d行%d列并且有%d个非零元素的稀疏矩阵\n",M->mu,M->nu,M->tu);
    for(i=1;i<M->mu+1;i++)
    {
        if(M->rhead[i]!=NULL)
        {
            p=M->rhead[i];
            for(j=1;j<M->nu+1;j++)
            {
                if(p->row==i&&p->col==j)
                {
                    printf(" %d ",p->value);
                }
                else printf(" 0 ");
            }
        }

        else
            for(j=1;j<M->nu+1;j++)
                printf(" 0 ");
        printf("\n");
    }
}

int main()
{
    CrossList M;
    CreateSMatrix(&M);
    printf("您输入的稀疏矩阵为：\n");
    PrintSMatrix(&M);
    return 0;
}
