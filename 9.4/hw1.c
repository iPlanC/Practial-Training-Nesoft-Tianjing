/*
 * @Author: PlanC
 * @Date: 2020-09-04 17:28:50
 * @LastEditTime: 2020-09-04 18:22:17
 * @FilePath: \Practical-Training-Neusoft-Tianjin\9.4\hw1.c
 */

#include <stdio.h>

float max(float *num) {
    int i = 0;
    int flag = 0;
    float max = 0;
    for (i = 0; i < 3; i++) {
        if (max < num[i]) {
            max = num[i];
            flag = i;
        }
    }
    num[flag] = 0;
    return max;
}

int validate(float *num) {
    float maxEdge = max(num);
    if (num[0] * num[0] + num[1] * num[1] + num[2] * num[2] > maxEdge * maxEdge) {
        printf("acute");
    }
    if (num[0] * num[0] + num[1] * num[1] + num[2] * num[2] == maxEdge * maxEdge) {
        printf("right");
    }
    if (num[0] * num[0] + num[1] * num[1] + num[2] * num[2] < maxEdge * maxEdge) {
        printf("obtuse");
    }
}

int main() {
    float edge[2] = {0.0};
    scanf("%f %f %f", &edge[0], &edge[1], &edge[2]);
    printf("triangle with %f %f %f, ", edge[0], edge[1], edge[2]);
    if ((edge[0] + edge[1] > edge[2]) && (edge[0] + edge[2] > edge[1]) & (edge[1] + edge[2] > edge[0])) {
        printf("is a ");
        validate(edge);
        printf(" triangle.\n");
    }
    else {
        printf("is NOT a triangle.\n");
    }
    return 0;
}
