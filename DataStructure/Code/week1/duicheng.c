#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main() {
//����
    printf("##����������ָ����Χ�ڵĶԳ�����1-9999999999��##\n\n");
    char aa[10], bb[10];
    int a, b;

//����1
    printf("���������ɶԳ����ķ�Χ����Сֵ��");
    int status = 0, inum = 1;//����״̬��
    while (status == 0) {
        scanf("%s", aa);
        for (int i = 0; aa[i] != 0; i++) {
            if (aa[i] < '0' || aa[i] > '9') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(aa) > 9999999999))) {
            printf("��ʽ�����������������ɶԳ����ķ�Χ����Сֵ��");
            inum = 1;

        } else {
            a = atoi(aa);
            status = 1;
        }
    }

//����2
    printf("���������ɶԳ����ķ�Χ�����ֵ��");
    status = 0, inum = 1;//����״̬��
    while (status == 0) {
        scanf("%s", bb);
        for (int j = 0; bb[j] != 0; j++) {
            if (bb[j] < '0' || bb[j] > '9') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(bb) > 9999999999))) {
            printf("��ʽ�����������������ɶԳ����ķ�Χ�����ֵ��");
            inum = 1;

        } else {
            b = atoi(bb);
            status = 1;
        }
    }
    printf("%d\n%d", a, b);
//////////

//����ȷ����ת�����ַ���������
    int k = 0;
    int z = 0;
    int y = 0;
    for (; a + k > b; k++) {
        //printf("%d",k);//shiyan
        char str[10];
        int d = a + k;//����Գ���
        itoa(d, str, 10);//��תΪ�ַ�����
        int len = strlen(str);
        //printf("%d\n",len);//shiyan

        if (len % 2 == 1)//����
        {
            int ji = (len + 1) / 2;
            for (int ji1 = 1; ji - ji1 < 1; ji1++) {
                if (str[ji - ji1] == str[ji + ji1])
                    z++;
            }
            printf("%d", d);//shiyan
            if (z == (len - 1) / 2)
                printf("%10d\n", d);
        }

        if (len % 2 == 0)//ż��
        {
            int ou = (len / 2) - 1;
            for (int ou1 = 0; ou - ou1 < 1; ou1++) {
                if (str[ou - ou1] == str[ou + 1 + ou1])
                    y++;
            }
            if (y == len / 2)
                printf("%10d\n", d);
        }
    }
    return 0;
}
