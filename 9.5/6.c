/*
 * @Author: PlanC
 * @Date: 2020-09-05 15:42:18
 * @LastEditTime: 2020-09-05 16:00:22
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\6.c
 */

#include <stdio.h>

int main() {
    int i = 0;
    int j = 0;
    int array[10][10] = {0};
    for (i = 0; i < 10; i++) {
        for (j =0; j < 10; j++) {
            array[i][j] = i * 10 + j;
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("array[%d][%d] = %d, ", i, j, array[i][j]);
        }
        printf("\n");
    }
    return 0;
}
