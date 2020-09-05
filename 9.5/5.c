/*
 * @Author: PlanC
 * @Date: 2020-09-05 15:30:34
 * @LastEditTime: 2020-09-05 15:36:59
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\5.c
 */

#include <stdio.h>

int main() {
    int i = 0;
    int array[10] = {0, 1, 2, 3, 4, 5, 6 ,7 ,8 ,9};
    for (i = 0; i < 10; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
    return 0;
}
