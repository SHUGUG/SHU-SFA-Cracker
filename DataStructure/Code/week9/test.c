#include<stdio.h>

#include<windows.h>

#include<math.h>

#include<string.h>

#include<time.h>

int main()

{

    Beep(1661, 1400);/*使系统发出蜂鸣声，意为闹得挺大*/

    time_t timep;/*获取当前的年月日时分秒*/

    struct tm* p;

    time(&timep);

    p = gmtime(&timep);

    printf("%d年%d月%d日%d时%d分%d秒\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday,8 + p->tm_hour, p->tm_min, p->tm_sec);

    char nowgrade[] = "高二";/*介绍人物*/

    printf("%s\n", nowgrade);

    char pastme[] = "二刺螈", nowme[] = "正常人";

    printf("%s\n", nowme);

    char* friend = pastme;

    printf("%s\n", friend);

    char* sillyman = friend;

    printf("%s\n", sillyman);

    char time[10];/*给时间赋值*/

    scanf("%s", time);

    if (strcmp(time, "上课时间") == 0)/*故事开始*/

    {

        printf("%s\n", sillyman);

        printf("看动漫玩游戏买手办\n");

    }

    else

    {

        printf("%s\n", sillyman);

        printf("玩原神-30000的**\n");

    }

    char stealmoney[5];/*偷钱事件*/

    scanf("%s", stealmoney);

    if (strcmp(stealmoney, "成功") == 0)

    {

        printf("哦，那没事了。嘻嘻^^_\n");

    }

    else

    {

        char father[10] = "他爹";

        printf("%s和%s打了起来，这也太好孝了⑧！\n", father, sillyman);

        printf("+50000\n");

    }

    int mon, day;/*炼铜biss!*/

    mon = 10;

    day = 30;

    printf("%d月%d日\n", mon, day);

    char* sister = sillyman;

    printf("已经变成他的形状惹！\n");

    char sisterage[10] = "12";

    printf("%s岁\n", sisterage);

    printf("%d年%d月%d日\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday - 10);/*尾声*/

    char school[10] = "学校";

    char father[10] = "他爹";

    printf("%s来到了%s\n", father, school);

    printf("-1腿\n");

    printf("-1%s\n", sillyman);

    printf("good ending!");

    return 0;

}