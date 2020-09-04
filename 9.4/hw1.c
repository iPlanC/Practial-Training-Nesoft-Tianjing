/*
 * @Author: PlanC
 * @Date: 2020-09-04 17:28:50
 * @LastEditTime: 2020-09-04 17:58:26
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\hw1.c
 */

#include <stdio.h>

float max(float num1, float num2) {
    return (num1 > num2) ? num1 : num2;
}

float min(float num1, float num2) {
    return (num1 < num2) ? num1 : num2;
}

int validate(float edge1, float edge2, float edge3) {
    float maxedge = max(max(edge1, edge2), max(edge2, edge3));
    float minedge1 = min(edge1, edge2);
    float minedge2 = min(edge2, edge3);
    if (minedge1 * minedge1 + minedge2 * minedge2 > maxedge * maxedge) {
        printf("acute");
    }
    if (minedge1 * minedge1 + minedge2 * minedge2 == maxedge * maxedge) {
        printf("right");
    }
    if (minedge1 * minedge1 + minedge2 * minedge2 < maxedge * maxedge) {
        printf("obtuse");
    }
}

int main() {
    float edge1 = 0.0;
    float edge2 = 0.0;
    float edge3 = 0.0;
    scanf("%f %f %f", &edge1, &edge2, &edge3);
    printf("triangle with %f %f %f, ", edge1, edge2, edge3);
    if ((edge1 + edge2 > edge3) && (edge1 + edge3 > edge2) & (edge2 + edge3 > edge1)) {
        printf("is a ");
        validate(edge1, edge2, edge3);
        printf(" triangle.\n");
    }
    else {
        printf("is NOT a triangle.\n");
    }
    return 0;
}
