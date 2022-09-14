#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#include<Windows.h>

//生成一个随机奇数，范围2048-4095
long Jishu() {
    int p = 0;
    do {
        srand(time(NULL));
        p = rand() % 2048 + 2048;
    } while (p % 2 == 0);
    return p;
}

//检验能否整除100内素数
long Sushu(p) {
    int a[24] = { 3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };//100内素数
    int t = 0;
    int i;
    for (i = 0; p % a[i] != 0 && i < 24; i++);
    if (i != 24) {
        t = 1;
    }
    return t;
}

//用费马小定理检测是否为素数
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

//大数乘方、取余
long Cheng(g, b, p) {
    int a[100000] = { 1 };
    int i = 0;
    int j = 0;
    int y = 0;//余数

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
    int p = 0;//一个大素数
    int t = 0;//t=1时，p能整除100内素数
    int s = 0;//s=0时，p是素数

    int a = 0;//Alice的随机数a
    int b = 0;//Bob的随机数b
    int g = 2;//约定的生成元
    int A = 0;//Alice发给Bob的公钥
    int B = 0;//Bob发给Alice的公钥

    int ka = 0;//Alice的私钥
    int kb = 0;//Bob的私钥
    char str1[10] = { 0 };//待加密内容
    char str2[10] = { 0 };//加密后内容
    char str3[10] = { 0 };//解密后内容
    int d = 0;//加密次数

    printf("约定生成元g = 2\n");
    printf("请输入待加密内容（不多于10个字母）：\n");
    scanf("%s", str1);
    printf("待加密内容为：%s\n", str1);

    printf("请输入加密次数：\n");
    scanf("%d", &d);
    printf("加密次数d = %d\n\n", d);

    for (int j = 1; j <= d; j++) {//进行第j次加密
        printf("现在进行第%d次加密\n", j);
        do {
            p = Jishu();//生成随机奇数
            t = Sushu(p);//检验p能否整除100内素数
            s = RM(p);//RM算法检验p是否为素数
        } while (t == 1 || s == 1);
        printf("大素数p = %d\n", p);

        srand(GetTickCount());
        a = rand() % (p - 2) + 1;//1 <= a <= p-1
        printf("Alice私有的随机数a = %d\n", a);
        
        A = Cheng(g, a, p);//生成Alice发给Bob的公钥
        printf("Alice发给Bob的公钥A = %d\n", A);

        srand(GetTickCount());
        b = rand() % (p - 2) + 1;//1 <= b <= p-1
        printf("Bob私有的随机数b = %d\n", b);
        
        B = Cheng(g, b, p);//生成Bob发给Alice的公钥
        printf("Bob发给Alice的公钥B = %d\n", B);

        ka = Cheng(B, a, p);//Alice计算出私钥
        kb = Cheng(A, b, p);//Bob计算出私钥
        printf("Alice计算出私钥ka = %d\n", ka);
        printf("Bob计算出私钥kb = %d\n", kb);

        //用Alice的私钥ka进行加密
        for (int i = 0; str1[i] != 0; i++) {
            if ('A' <= str1[i] && str1[i] <= 'Z') {//如果是大写字母
                if (str1[i] + ka % 26 > 90) {
                    str2[i] = str1[i] - (26 - ka % 26);
                }
                else {
                    str2[i] = str1[i] + ka % 26;
                }
            }
            else if ('a' <= str1[i] && str1[i] <= 'z') {//如果是小写字母
                if (str1[i] + ka % 26 > 122) {
                    str2[i] = str1[i] - (26 - ka % 26);
                }
                else {
                    str2[i] = str1[i] + ka % 26;
                }
            }
        }
        printf("第%d次加密后内容为：%s\n", j, str2);

        //用Bob的私钥kb进行解密
        for (int i = 0; str2[i] != 0; i++) {
            if ('A' <= str2[i] && str2[i] <= 'Z') {//如果是大写字母
                if (str2[i] - kb % 26 < 65) {
                    str3[i] = str2[i] + (26 - kb % 26);
                }
                else {
                    str3[i] = str2[i] - kb % 26;
                }
            }
            else if ('a' <= str2[i] && str2[i] <= 'z') {//如果是小写字母
                if (str2[i] - kb % 26 < 97) {
                    str3[i] = str2[i] + (26 - kb % 26);
                }
                else {
                    str3[i] = str2[i] - kb % 26;
                }
            }
        }
        printf("第%d次解密后内容为：%s\n\n", j, str3);
    }
    
    return 0;
}