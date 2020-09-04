/*
 * @Author: PlanC
 * @Date: 2020-09-04 08:57:37
 * @LastEditTime: 2020-09-04 10:34:18
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\1.c
 */

#include <stdio.h>

int main() {
    float edge1 = 0.0;
    float edge2 = 0.0;
    float edge3 = 0.0;
    printf("input 3 edges length:\n");
    scanf("%f %f %f", &edge1, &edge2, &edge3);
    printf("3 edge with %f %f %f, ", edge1, edge2, edge3);
    if ((edge1 + edge2 > edge3) && (edge1 + edge3 > edge2) && (edge2 + edge3 > edge1)) {
        printf("is triangle.\n");
    }
    else {
        printf("is NOT triangle.\n");
    }

    return 0;
}
