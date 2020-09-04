/*
 * @Author: PlanC
 * @Date: 2020-09-04 14:00:55
 * @LastEditTime: 2020-09-04 14:20:44
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\2.c
 */

#include <stdio.h>

int main() {
    int light = 0;
    while (1) {
        scanf("%d", &light);
        switch (light) {
            case 0: // red
                printf("STOP");
                break;
            case 1: // green
                printf("PASS");
                break;
            case 2: // yellow
                printf("WAIT");
                break;
            default:
                printf("ON_ERROR");
                break;
        }
        printf("\n");
    }
    return 0;
}
