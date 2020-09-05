/*
 * @Author: PlanC
 * @Date: 2020-09-05 10:41:41
 * @LastEditTime: 2020-09-05 14:08:40
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\3.c
 */

#include <stdio.h>

int main() {
    int a = 0;
    int b = 0;
    while (1) {
        printf("input and b\n");
        scanf("%d %d", &a, &b);
        printf("bigger in %d and %d is %d.\n", a, b, (a > b) ? a : b);
    }
    return 0;
}
