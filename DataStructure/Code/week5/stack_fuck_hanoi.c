#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*全局定义域-----------------------------------------------------------------------------*/

//错误代码CODE
#define empty_scanf 0		//CODE:0 输入为空
#define wrong_scanf 1		//CODE:1 格式错误
typedef struct link_scanf		//字符链表
{
    char elem;						//定义字符元素
    struct link_scanf* next;		//定义尾指针
}link_scanf;
typedef struct link_num			//数字链表
{
    int elem;					//定义数字元素
    struct link_num* next;		//定义尾指针
}link_num;
typedef struct link_point		//双指针链表
{
    char elem;						//定义字符元素
    struct link_num* stack;			//定义指向栈的指针
    struct link_point* next;		//定义尾指针
}link_point;

/*函数定义域-----------------------------------------------------------------------------------*/

link_scanf* get_scanf();				//输入字符
int restart();							//重启程序检测
void print_error(int code);				//报错
link_num* push(link_num* top);		//压栈
link_num* pop(link_num* top);		//出栈
link_point* create_point(link_num* stack_x, link_num* stack_y, link_num* stack_z);		//循环指针链

/*函数域---------------------------------------------------------------------------------------*/

int main()
{
    clock_t start_time, end_time;
    int round = 0;		//程序循环判断器
//    printf(" 汉 诺 塔 （堆栈）\n\n");
//    printf("从 X 移到 Z \n");
//    printf("         X          Y          Z   \n");
//    printf("                                   \n");
//    printf("         |          |          |   \n");
//    printf("         |          |          |   \n");
//    printf("        _|_         |          |   \n");
//    printf("      _|_1_|_       |          |   \n");
//    printf("    _|___2___|_     |          |   \n");
//    printf("___|_____3_____|____|__________|_____\n");
    do
    {
        //初始化数据域-----------
        link_scanf* head;		//定义字符链表节点
        int flag = 0;			//循环判断器
        int num_hanoi = 0;		//定义汉诺塔个数
        //-----------------------
        printf("\n请输入汉诺塔个数（正整数）：\n");
        //输入
        do
        {
            //初始化数据域-----------
            flag = 0;				//循环判断器
            link_scanf* p;			//定义遍历节点
            num_hanoi = 0;			//汉诺塔个数
            //-----------------------
            head = get_scanf();		//输入并获取头指针
            for (p = head; p != NULL; p = p->next)		//遍历输入的字符
            {
                if (p->elem >= '0' && p->elem <= '9')		//若为数字，存储
                {
                    num_hanoi = p->elem - 48 + num_hanoi * 10;		//循环进位存数
                }
                else										//若不为数字，报错，重输
                {
                    print_error(wrong_scanf);
                    flag = 1;
                    break;
                }
            }
            if (num_hanoi < 1 && !flag)			//若输入数字小于1，报错，重输
            {
                printf("输入数字太小！请重新输入：\n");
                flag = 1;
            }
        } while (flag);
        printf("\n");

        start_time = clock();

        link_num* bottom_x, * top_x;		//定义 X 柱的栈
        link_num* bottom_y, * top_y;		//定义 Y 柱的栈
        link_num* bottom_z, * top_z;		//定义 Z 柱的栈
        link_num* temp1, * temp0;			//定义临时节点
        link_point* top_1, * bottom_1, * top_other, * bottom_other;		//定义移位指针
        link_point* top_temp, * top_exchange;		//临时节点
        top_x = bottom_x = (link_num*)malloc(sizeof(link_num));		//创建 X 柱的栈底
        top_y = bottom_y = (link_num*)malloc(sizeof(link_num));		//创建 Y 柱的栈底
        top_z = bottom_z = (link_num*)malloc(sizeof(link_num));		//创建 Z 柱的栈底
        top_temp = (link_point*)malloc(sizeof(link_point));
        top_exchange = (link_point*)malloc(sizeof(link_point));
        int num_th = num_hanoi;			//定义临时汉诺塔个数
        int count = 0;		//步骤计数器
        int end = 1;		//终点记录器
        int ex = 0;			//节点交换记录器
        char from;		//移位起点柱
        char to;			//移位终点柱
        for (; num_th != 0; )		//压栈 X 柱
        {
            top_x->elem = num_th--;
            top_x = push(top_x);
        }
        top_1 = top_other = create_point(top_x, top_y, top_z);						//栈顶链
        bottom_1 = bottom_other = create_point(bottom_x, bottom_y, bottom_z);		//栈底链
        if (num_hanoi % 2 != 0)			//若个数为奇，交换 X 和 Y
        {
            bottom_1->next->elem = 'Z';
            bottom_1->next->next->elem = 'Y';
            bottom_other->next->elem = 'Z';
            bottom_other->next->next->elem = 'Y';
        }
        for (; end; )
        {
            //1号移位
            {
                temp0 = top_1->stack;
                from = bottom_1->elem;
                temp1 = top_1->next->stack;
                to = bottom_1->next->elem;
                temp1->elem = temp0->next->elem;		//1号移位
                count++;
//                printf("第 %2d 步：%2d 号  %c --> %c\n", count, temp1->elem, from, to);
                switch (top_1->elem)		//出栈和压栈
                {
                    case('X'):
                    {
                        top_x = pop(top_x);
                        top_1->stack = top_x;
                        top_y = push(top_y);
                        top_1->next->stack = top_y;
                        break;
                    }
                    case('Y'):
                    {
                        top_y = pop(top_y);
                        top_1->stack = top_y;
                        top_z = push(top_z);
                        top_1->next->stack = top_z;
                        break;
                    }
                    case('Z'):
                    {
                        top_z = pop(top_z);
                        top_1->stack = top_z;
                        top_x = push(top_x);
                        top_1->next->stack = top_x;
                        break;
                    }
                    default:
                        break;
                }
                top_1 = top_1->next;		//1号指针顺移
                bottom_1 = bottom_1->next;
            }
            //其他号移位
            {
                flag = 1;
                end = 0;
                ex = 0;
                for (int i = 0; i < 3; i++)		//是否有空栈
                {
                    if (top_other->stack == bottom_other->stack &&
                        top_other->next->stack != bottom_other->next->stack &&
                        top_other->next->next->stack != bottom_other->next->next->stack)		//若为空栈，且有且仅有一个
                    {
                        to = bottom_other->elem;
                        temp1 = top_other->stack;
                        top_temp = top_other;		//top_temp为压栈
                        do
                        {
                            top_other = top_other->next;
                            bottom_other = bottom_other->next;
                            temp0 = top_other->stack;
                            if (temp0->next->elem != 1)		//若不为1号
                            {
                                temp1->elem = temp0->next->elem;		//other号移位
                                from = bottom_other->elem;
                                count++;
//                                printf("第 %2d 步：%2d 号  %c --> %c\n", count, temp1->elem, from, to);
                                flag = 0;
                                end = 1;
                            }
                        } while (flag);
                        break;
                    }
                    top_other = top_other->next;
                    bottom_other = bottom_other->next;
                }
                if (flag && top_x != bottom_x && top_y != bottom_y && top_z != bottom_z)		//若无空栈，小移大
                {

                    for (int i = 0; i < 3; i++)
                    {
                        temp0 = top_other->stack;
                        if (temp0->next->elem != 1)		//若不为1号的第一个,temp0,top_temp
                        {
                            to = bottom_other->elem;
                            top_temp = top_other;
                            break;
                        }
                        top_other = top_other->next;
                        bottom_other = bottom_other->next;
                    }
                    for (int i = 0; i < 3; i++)
                    {
                        top_other = top_other->next;
                        bottom_other = bottom_other->next;
                        temp1 = top_other->stack;
                        if (temp1->next->elem != 1)		//若不为1号的第二个,temp1,top_other
                        {
                            from = bottom_other->elem;
                            break;
                        }
                    }
                    count++;
                    if (temp0->next->elem > temp1->next->elem)			//若temp0比temp1大，移动小的temp1
                    {
                        temp0->elem = temp1->next->elem;		//other移位1->0,top_other->top_temp
                        end = 1;
                        flag = 0;
//                        printf("第 %2d 步：%2d 号  %c --> %c\n", count, temp0->elem, from, to);
                    }
                    else if (temp0->next->elem < temp1->next->elem)		//若temp0比temp1小，移动小的temp0
                    {
                        temp1->elem = temp0->next->elem;		//other移位0->1,top_temp->top_other
                        end = 1;
                        flag = 0;
//                        printf("第 %2d 步：%2d 号  %c --> %c\n", count, temp1->elem, to, from);
                        top_exchange = top_other;		//交换top_other和top_temp
                        top_other = top_temp;
                        top_temp = top_exchange;
                        ex = 1;			//交换记录器
                    }
                }
                if (!flag)
                {
                    switch (top_temp->elem)		//压栈
                    {
                        case('X'):
                        {
                            top_x = push(top_x);
                            top_temp->stack = top_x;
                            break;
                        }
                        case('Y'):
                        {
                            top_y = push(top_y);
                            top_temp->stack = top_y;
                            break;
                        }
                        case('Z'):
                        {
                            top_z = push(top_z);
                            top_temp->stack = top_z;
                            break;
                        }
                        default:
                            break;
                    }
                    switch (top_other->elem)		//出栈
                    {
                        case('X'):
                        {
                            top_x = pop(top_x);
                            top_other->stack = top_x;
                            break;
                        }
                        case('Y'):
                        {
                            top_y = pop(top_y);
                            top_other->stack = top_y;
                            break;
                        }
                        case('Z'):
                        {
                            top_z = pop(top_z);
                            top_other->stack = top_z;
                            break;
                        }
                        default:
                            break;
                    }
                }
                if (ex)			//如果交换过，换回top_other和top_temp
                {
                    top_exchange = top_other;
                    top_other = top_temp;
                    top_temp = top_exchange;
                }
            }
        }
        printf("\n移动结束！%2d 个汉诺塔，共 %d 步\n", num_hanoi, count);

        end_time = clock();
        printf("\nTime: %lu", (end_time - start_time));

        printf("\n重新计算请输入1，或输入任意内容结束程序\n");
        round = restart();
    } while (round);
    return 0;
}

//输入字符
link_scanf* get_scanf()
{
    int fresh = 0;		//输入为空判断器
    link_scanf* head, * tail, * p;
    do
    {
        //初始化数据域------
        fresh = 0;
        head = tail = NULL;
        int flag = 1;
        char ch;
        //---------------------
        while (flag)		//遍历输入
        {
            scanf("%c", &ch);
            if (ch != '\n')		//若不为Enter且输入不为空
            {
                p = (link_scanf*)malloc(sizeof(link_scanf));
                p->elem = ch;
                p->next = NULL;
                if (head == NULL)		//若头节点为空
                {
                    head = p;
                }
                else		//若头节点不为空
                {
                    tail->next = p;
                }
                tail = p;
            }
            else		//若输入为空
            {
                if (head == NULL)
                {
                    print_error(empty_scanf);
                    fresh = 1;
                }
                flag = 0;
            }
        }
    } while (fresh);
    return head;		//返回头节点
}

//重启程序检测
int restart()
{
    link_scanf* head;
    int round = 0;
    head = get_scanf();		//输入并获取头指针
    if (head->elem == '1' && head->next == NULL)		//若输入‘1’
    {
        round = 1;
    }
    return round;		//返回循环判断器
}

//报错
void print_error(int code)
{
    switch (code)
    {
        case(empty_scanf):		//输入为空
        {
            printf("输入不能为空！请重新输入：\n");
            break;
        }
        case(wrong_scanf):		//格式错误
        {
            printf("输入格式错误！请重新输入：\n");
            break;
        }
        default: printf("ERROR CODE:404\n");
            break;
    }
}

//压栈（数字链表）
link_num* push(link_num* top)
{
    link_num* temp;
    temp = top;
    top = (link_num*)malloc(sizeof(link_num));
    top->next = temp;
    top->elem = 0;
    return top;		//返回栈顶
}

//出栈（数字链表）
link_num* pop(link_num* top)
{
    link_num* temp;
    temp = top;
    top = top->next;
    top->elem = NULL;
    free(temp);
    return top;		//返回栈顶
}

//循环指针链
link_point* create_point(link_num* stack_x, link_num* stack_y, link_num* stack_z)
{
    link_point* point, * head, * tail;
    point = (link_point*)malloc(sizeof(link_point));
    point->elem = 'X';
    point->stack = stack_x;
    head = tail = point;
    point = (link_point*)malloc(sizeof(link_point));
    tail->next = point;
    tail = point;
    point->elem = 'Y';
    point->stack = stack_y;
    point = (link_point*)malloc(sizeof(link_point));
    tail->next = point;
    point->elem = 'Z';
    point->stack = stack_z;
    point->next = head;
    point = head;
    return point;
}