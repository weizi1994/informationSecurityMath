#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "field28.h"


field28 add(field28 a, field28 b){
    return a^b;
}

field28 xtime(field28 a){
    if(a&0x80){
        return (a<<1)^mx; // return add(a<<1, mx)
    }else{
        return a << 1;
    }
}

//用于生成 mult[256][256] 或计算
field28 multi2(field28 a, field28 b){
    static field28 mul[256][256]; //用于保存已经计算过的结果
    field28 bit=0x01;
    field28 result=0x00;
    field28 tmp = a;

    if((a==0x00) || (b==0x00))
        return 0x00;
    else if(mul[a][b] != 0x00)
        return mul[a][b];
    else{
        while(bit){
            if(b&bit)
                result ^= tmp; // result = add(result, tmp)
            bit = bit << 1;
            tmp = xtime(tmp);
        }
        mul[b][a] = mul[a][b] = result;
        return result;
    }
}

field28 multi(field28 a, field28 b){
    return mult[a][b];
}


//用于生成 inve[256] 或计算
field28 inverse2(field28 a){   
    static field28 inv[256];//用于保存已经计算过的结果
    field28 i=0x01;

    if(a==0x00)
        return 0x00;
    else if(inv[a] != 0x00)
        return inv[a];
    else{
        while(1){
            if(multi(a,i)==0x01){
                inv[a] = i;
                inv[i] =a;
                return i;
            }
            i++;
        }
    }
}


field28 inverse(field28 a){
    return inve[a];
}

int main()
{
    int start, end;
    field28 a=0x57, b=0x00;
    field28 randarr[100000];
    int i;

    srand(time(NULL));
    for(i=0; i<100000; i++)
        randarr[i] = (field28)rand();

    //multi2  函数计算
    start = clock();
    for(i=0; i<100000; i++){
        a = randarr[i];
        b = multi2(a,inverse(a));
    }
    printf("0x%hhx * 0x%hhx = 0x%hhx\n", a, inverse(a), b);
    end = clock();
    printf("multi2 计算次数:%d, 用时:%fs\n",i, (double)(end-start)/CLOCKS_PER_SEC);

    //multi 函数查表
    start = clock();
    for(i=0; i<100000; i++){
        a = randarr[i];
        b = multi(a,inverse(a));
    }
    printf("0x%hhx * 0x%hhx = 0x%hhx\n", a, inverse(a), b);
    end = clock();
    printf("multi 计算次数:%d, 用时:%fs\n",i, (double)(end-start)/CLOCKS_PER_SEC);

    //mult 不调用函数，直接查表
    start = clock();
    for(i=0; i<100000; i++){
        a = randarr[i];
        b = mult[a][inve[a]];
    }
    printf("0x%hhx * 0x%hhx = 0x%hhx\n", a, inverse(a), b);
    end = clock();

    printf("mult[256][256] 计算次数:%d, 用时:%fs\n",i, (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
