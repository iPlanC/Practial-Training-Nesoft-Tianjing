/*
 * @Author: PlanC
 * @Date: 2020-09-04 17:28:50
 * @LastEditTime: 2020-09-04 17:38:44
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\hw1.c
 */

#include <stdio.h>

int main() {
    float edge1 = 0.0;
    float edge2 = 0.0;
    float edge3 = 0.0;
    scanf("%f %f %f", &edge1, &edge2, &edge3);
    printf("triangle with %f %f %f, ", edge1, edge2, edge3);
    if ((edge1 + edge2 > edge3) && (edge1 + edge3 > edge2) & (edge2 + edge3 > edge1)) {
        printf("is a ");
        if (edge1 * edge1 + edge2 * edge2 < edge3 * edge3) {
            printf("acute");
        }
        if (edge1 * edge1 + edge2 * edge2 == edge3 * edge3) {
            printf("right");
        }
        if (edge1 * edge1 + edge2 * edge2 > edge3 * edge3) {
            printf("obtuse");
        }
        printf(" triangle.\n");
    }
    else {
        printf("is NOT a triangle.\n");
    }
    return 0;
}
