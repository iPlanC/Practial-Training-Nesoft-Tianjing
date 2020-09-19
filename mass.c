/*
 * @Author: PlanC
 * @Date: 2020-09-09 09:13:06
 * @LastEditTime: 2020-09-09 10:26:21
 * @FilePath: \Practical-Training-Neusoft-Tianjin\mass.c
 */

#include <stdio.h>

int main() {
    // int num1;
    // int num2;
    int num1 = 10;
    int num2 = 8;
    for (   /* scanf("%d %d", &num1, &num2),  */
            printf("%d.", num1 / num2);
            num1 != 0;
            num1 = num1 * 10 % num2, printf("%d", num1 * 10 / num2)
    );
}
