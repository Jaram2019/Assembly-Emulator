#include <stdio.h>

int main(void){
    int N;
    scanf("%d",&N);
    long x = 0, y = 1, z = 1;
    for (int i = 0; i < N; ++i) {
        z = x + y;
        x = y;
        y = z;
    }
    printf("%ld\n",z);
}

