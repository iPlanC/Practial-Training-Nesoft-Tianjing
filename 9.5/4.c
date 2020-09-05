/*
 * @Author: PlanC
 * @Date: 2020-09-05 14:21:22
 * @LastEditTime: 2020-09-05 14:38:54
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\4.c
 */

#include <stdio.h>

int main() {
    int a = 0;
    int b = 0;
    while (1) {
        printf("input a and b\n");
        scanf("%d %d", &a, &b);
        printf("a = %d, b = %d\n", a << 2, b >> 2);
        printf("a | b = %d, a & b = %d\n", a | b, a & b);
        printf("~a = %d, ~b = %d\n", ~a, ~b);
    }
    return 0;
}
