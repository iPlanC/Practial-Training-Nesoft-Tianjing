/*
 * @Author: PlanC
 * @Date: 2020-09-04 15:06:57
 * @LastEditTime: 2020-09-04 15:13:32
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\3.c
 */

#include <stdio.h>

int main() {
    int i = 0;
    int sum = 0;
    for (i = 0; i < 10; i++) {
        sum = sum + i;
        printf("when i = %d, then sum = %d.\n", i, sum);
    }
    return 0;
}
