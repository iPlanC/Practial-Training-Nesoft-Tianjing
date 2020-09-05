/*
 * @Author: PlanC
 * @Date: 2020-09-05 16:24:23
 * @LastEditTime: 2020-09-05 16:37:33
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.5\7.c
 */

#include <stdio.h>

int main() {
    int index = 0;
    unsigned int array[10] = {0};
    while (1) {
        printf("input index \n");
        scanf("%d", &index);
        printf("index = %d\n", index);
        if (index >= 10) {
            printf("index out of bound\n");
        }
        else {
            printf("array[%d] = ", index);
            scanf("%d", array + index);
            printf("array[%d] = %d\n", index, *(array + index));
        }
    }
    return 0;
}
