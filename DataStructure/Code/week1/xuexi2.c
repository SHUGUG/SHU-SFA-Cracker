#include<stdio.h>
#include<stdlib.h>

//���庯��
int find() {
    int array[3][4] = {{11, 12, 13, 14},
                       {21, 22, 23, 24},
                       {31, 32, 33, 34}};
    int m, n, s, t;
    char ii[10], jj[10];
    int *o, *a, oo, aa;
    int i = atoi(ii), j = atoi(jj);
    //���������һЩ����

    printf("��ʵ���ǲ���ָ����3��4������ĳһԪ���ܱ�Ԫ�ص�ֵ�͵�ַ\n��ʵ��ʹ�õ�����Array[3][4]����Ϊ:\n");
    for (m = 0; m < 3; m++) {
        for (n = 0; n < 4; n++) {
            printf("%d ", array[m][n]);
        }
        printf("\n");
    }
    printf("\n");//�������

//�ж���������Ƿ�����
    int status = 0, inum = 1;//����״̬��
    printf("���������Ԫ�ص�����(1-3)��");
    while (status == 0) {
        scanf("%s", ii);
        for (int ei = 0; ii[ei] != 0; ei++) {
            if (ii[ei] < '1' || ii[ei] > '3') {
                inum = 0;
                break;
            }
        }

        if (inum == 0 || (inum == 1 && (atoi(ii) < 1 || atoi(ii) > 3))) {
            printf("��������������������룺");
            inum = 1;

        } else {
            i = atoi(ii);
            status = 1;
        }
    }

//�ж���������Ƿ�����
    status = 0;
    int jnum = 1;
    printf("���������Ԫ�ص�����(1-4)��");
    while (status == 0) {
        scanf("%s", &jj);
        for (int ej = 0; ii[ej] != 0; ej++) {
            if (jj[ej] < '1' || jj[ej] > '4') {
                jnum = 0;
                break;
            }

        }
        if (jnum == 0 || (jnum == 1 && (atoi(jj) < 1 || atoi(jj) > 4))) {
            printf("��������������������룺");
            jnum = 1;

        } else {
            j = atoi(jj);
            status = 1;
        }
    }

//�������Ԫ�غ����ַ
    oo = array[i - 1][j - 1];
    o = &array[i - 1][j - 1];
    printf("�����%d�е�%d�е�Ԫ����%d\n�����%d�е�%d�еĵ�ַ��%p\n\n", i, j, oo, i, j, o);
    printf("Ԫ���ܱߵ�Ԫ���У�\n");

//����ܱ�Ԫ�ؼ����ַ
    for (s = -1; s <= 1; s = s + 1) {
        for (t = -1; t <= 1; t = t + 1) {
            if (((i + s) >= 1 && (i + s) <= 3) && ((j + t) >= 1 && (j + t) <= 4) && (s != 0 || t != 0)) {
                aa = array[i - 1 + s][j - 1 + t];
                a = &array[i - 1 + s][j - 1 + t];
                printf("�����%d�е�%d�е�Ԫ����%d\n�����%d�е�%d�еĵ�ַ��%p\n\n", i + s, j + t, aa, i + s, j + t, a);
            }
        }
    }
    return 0;
}

int main() {
    find();
    char k[1] = "y";
    printf("����y����������n�������˳�");
    scanf("%s", k);
    while (k[0] == 'y') {
        find();
        printf("����y����������n�������˳�");
        scanf("%s", k);
    }
        return 0;
}
