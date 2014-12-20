#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sbox.h"

struct maxl{
    short n;
    short x;
    short y;
};

struct maxl max10[11];

short insert_max(short max, short x, short y)
{
    short i;

    for(i=0; i<10; i++){
        if(max10[i+1].n < max){
            max10[i] = max10[i+1];
        }else{
            max10[i].n = max;
            max10[i].x = x;
            max10[i].y = y;
            break;
        }
    }
    return max10[0].n;
}

int main()
{
    short a=0x00;
    short b=0x00;
    short ci=0x00;
    short di=0x00;
    char c,d;
    short result[256][256] = {{0}};
    int statistics[33] = {0};
    char bit_xor[256]; // n = bit_xor[a]; a = 0ba7 a6 a5 a4 a3 a2 a1 a0, n=a7^a6^a5^a4^a3^a2^a1^a0
    unsigned char bit=0x01;
    char count = 0;
    int max = 0;
    int tmp = 0;

    // 初始化 max10
    for(ci=0; ci<10; ci++){
        max10[ci].n = 0;
    } 
    max10[10].n = 257;
    
   // 初始化 bit_xor
    for(a=0; a<256; a++){
        bit = 0x01;
        count = 0;
        while(bit){
            if(bit&a)
                count++;
            bit = bit << 1;
        }
        bit_xor[a] = count % 2;
    }

    // 线性分析
    for(a=0; a<256; a++){
        b = sbox[a];
        for(ci=0; ci<256; ci++){
            c = bit_xor[a&ci];
            for(di=0; di<256; di++){
                d = bit_xor[b&di];
                if(c==d)
                    result[ci][di]++;
            }
        }
    }

    // 找出前十个最大的线性相关
    max = 0;
    for(ci=1; ci<256; ci++){
        for(di=0; di<256; di++){
            statistics[result[ci][di]-112]++;
            tmp = abs(result[ci][di] - 128);
            if(tmp>max){
                max = insert_max(tmp, ci, di);
            }
        }
    }


    // 输出结果
    for(ci=9; ci>=0; ci--){
        printf("i %2d ci %#x di %#x max %d diff %d\n",
                10-ci, max10[ci].x, max10[ci].y, result[max10[ci].x][max10[ci].y], max10[ci].n);
    }

    return 0;
}
