#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include<Windows.h>

//����һ�������������Χ2048-4095
long Jishu() {
    int p = 0;
    do {
        srand(time(NULL));
        p = rand() % 2048 + 2048;
    } while (p % 2 == 0);
    return p;
}

//�����ܷ�����100������
long Sushu(p) {
    int a[24] = { 3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };//100������
    int t = 0;
    int i;
    for (i = 0; p % a[i] != 0 && i < 24; i++);
    if (i != 24) {
        t = 1;
    }
    return t;
}

//�÷���С�������Ƿ�Ϊ����
long RM(p) {
    int s = 0;
    int a = 0;
    int b = 0;
    int i = 0;
    for (i = 0; i < 5 && s == 0; i++) {
        srand(time(NULL));
        a = rand() % 15 + 1;
        b = pow(a, p - 1);
        if (b % p != 1) {
            s = 1;
        }
    }
    return s;
}

//�����˷���ȡ��
long Cheng(g, b, p) {
    int a[100000] = { 1 };
    int i = 0;
    int j = 0;
    int y = 0;//����

    for (i = 1; i <= b; i++) {
        for (j = 0; j < 100000; j++) {
            if (j > 0) {
                a[j] = a[j] * g + a[j - 1] / 10;
                a[j - 1] = a[j - 1] % 10;
            }
            else if (j == 0) {
                a[j] = a[j] * g;
            }
        }
    }

    i = 99999;
    while (i > 0 && a[i] == 0) {
        i--;
    }

    for (i; i > 0; i--) {
        y = (a[i] * 10 + a[i - 1]) % p;
    }

    return y;
}

int main() {
    int p = 0;//һ��������
    int t = 0;//t=1ʱ��p������100������
    int s = 0;//s=0ʱ��p������

    int a = 0;//Alice�������a
    int b = 0;//Bob�������b
    int g = 2;//Լ��������Ԫ
    int A = 0;//Alice����Bob�Ĺ�Կ
    int B = 0;//Bob����Alice�Ĺ�Կ

    int ka = 0;//Alice��˽Կ
    int kb = 0;//Bob��˽Կ
    char str1[10] = { 0 };//����������
    char str2[10] = { 0 };//���ܺ�����
    char str3[10] = { 0 };//���ܺ�����
    int d = 0;//���ܴ���

    printf("Լ������Ԫg = 2\n");
    printf("��������������ݣ�������10����ĸ����\n");
    scanf("%s", str1);
    printf("����������Ϊ��%s\n", str1);

    printf("��������ܴ�����\n");
    scanf("%d", &d);
    printf("���ܴ���d = %d\n\n", d);

    for (int j = 1; j <= d; j++) {//���е�j�μ���
        printf("���ڽ��е�%d�μ���\n", j);
        do {
            p = Jishu();//�����������
            t = Sushu(p);//����p�ܷ�����100������
            s = RM(p);//RM�㷨����p�Ƿ�Ϊ����
        } while (t == 1 || s == 1);
        printf("������p = %d\n", p);

        srand(GetTickCount());
        a = rand() % (p - 2) + 1;//1 <= a <= p-1
        printf("Alice˽�е������a = %d\n", a);
        
        A = Cheng(g, a, p);//����Alice����Bob�Ĺ�Կ
        printf("Alice����Bob�Ĺ�ԿA = %d\n", A);

        srand(GetTickCount());
        b = rand() % (p - 2) + 1;//1 <= b <= p-1
        printf("Bob˽�е������b = %d\n", b);
        
        B = Cheng(g, b, p);//����Bob����Alice�Ĺ�Կ
        printf("Bob����Alice�Ĺ�ԿB = %d\n", B);

        ka = Cheng(B, a, p);//Alice�����˽Կ
        kb = Cheng(A, b, p);//Bob�����˽Կ
        printf("Alice�����˽Կka = %d\n", ka);
        printf("Bob�����˽Կkb = %d\n", kb);

        //��Alice��˽Կka���м���
        for (int i = 0; str1[i] != 0; i++) {
            if ('A' <= str1[i] && str1[i] <= 'Z') {//����Ǵ�д��ĸ
                if (str1[i] + ka % 26 > 90) {
                    str2[i] = str1[i] - (26 - ka % 26);
                }
                else {
                    str2[i] = str1[i] + ka % 26;
                }
            }
            else if ('a' <= str1[i] && str1[i] <= 'z') {//�����Сд��ĸ
                if (str1[i] + ka % 26 > 122) {
                    str2[i] = str1[i] - (26 - ka % 26);
                }
                else {
                    str2[i] = str1[i] + ka % 26;
                }
            }
        }
        printf("��%d�μ��ܺ�����Ϊ��%s\n", j, str2);

        //��Bob��˽Կkb���н���
        for (int i = 0; str2[i] != 0; i++) {
            if ('A' <= str2[i] && str2[i] <= 'Z') {//����Ǵ�д��ĸ
                if (str2[i] - kb % 26 < 65) {
                    str3[i] = str2[i] + (26 - kb % 26);
                }
                else {
                    str3[i] = str2[i] - kb % 26;
                }
            }
            else if ('a' <= str2[i] && str2[i] <= 'z') {//�����Сд��ĸ
                if (str2[i] - kb % 26 < 97) {
                    str3[i] = str2[i] + (26 - kb % 26);
                }
                else {
                    str3[i] = str2[i] - kb % 26;
                }
            }
        }
        printf("��%d�ν��ܺ�����Ϊ��%s\n\n", j, str3);
    }
    
    return 0;
}