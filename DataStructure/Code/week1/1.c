#include<stdio.h>
int find()
{
    int array[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    int i,j,s,t;
    int *o,*a,oo,aa;
    printf("�������ǲ���ָ������ĳһԪ���ܱ�Ԫ�ص�ֵ�͵�ַ\n���������Ԫ�ص�������");
    scanf("%d",&i);
    if(i>=1&&i<=3)
    {
        printf("���������Ԫ�ص�������");
        scanf("%d",&j);
        if((i>=1&&i<=3)&&(j>=1&&j<=4))
        {
            oo=array[i-1][j-1];
            o=&array[i-1][j-1];
            printf("�����%d�е�%d�е�Ԫ����%d\n�����%d�е�%d�еĵ�ַ��%p\n\n",i,j,oo,i,j,o);
            for(s=-1;s<=1;s=s+1)
            {
                for(t=-1;t<=1;t=t+1)
                {
                    if(((i+s)>=1&&(i+s)<=3)&&((j+t)>=1&&(j+t)<=4))
                    {
                        aa=array[i-1+s][j-1+t];
                        a=&array[i-1+s][j-1+t];
                        printf("�����%d�е�%d�е�Ԫ����%d\n�����%d�е�%d�еĵ�ַ��%p\n\n",i+s,j+t,aa,i+s,j+t,a);
                    }
                }
            }
        }
        else
        {
            printf("������������\n\n");
        }
    }
    else
    {
        printf("������������\n\n");
    }
    return 0;
}

int main()
{
    int k=1;
    for(k=1;k<=100;k++)
    {
        find();
    }
    return 0;
}
