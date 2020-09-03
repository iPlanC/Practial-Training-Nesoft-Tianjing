/*
 * @Author: PlanC
 * @Date: 2020-09-03 16:34:50
 * @LastEditTime: 2020-09-03 16:36:56
 * @FilePath: \Practical-Training-Neusoft-Tianjing\9.3\2.c
 */

#include <stdio.h>

int main() {
    unsigned int i = 0;
    unsigned int sum = 0;
    for (i = 0; i <= 100; i++) {
        sum = sum + i;
        printf("i = %d, sum = %d\n", i, sum);
    }
    return 0;
}
