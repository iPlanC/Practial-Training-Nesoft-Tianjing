/*
 * @Author: PlanC
 * @Date: 2020-09-05 10:09:37
 * @LastEditTime: 2020-09-05 10:24:06
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\2.c
 */

#include <stdio.h>

int main() {
    int a = 0;
    long b = 0;
    while (1) {
        printf("input a nd b:\n");
        scanf("%d %l", &a, &b);
        printf("%d %d %d\n", sizeof(a), sizeof((long)a), sizeof(b));
    }
    return 0;
}
