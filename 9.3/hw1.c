/*
 * @Author: PlanC
 * @Date: 2020-09-03 16:44:47
 * @LastEditTime: 2020-09-03 17:01:11
 * @FilePath: \Practical-Training-Neusoft-Tianjing\9.3\hw1.c
 */

#include <math.h>
#include <stdio.h>

int main() {
    int edge1 = 3;
    int edge2 = 4;
    int edge3 = 5;
    int P = (edge1 + edge2 + edge3) / 2;
    printf("D = %d\n", edge1 + edge2 + edge3);
    printf("S = %lf\n", sqrt((double)(P * (P - edge1) * (P - edge2) * (P - edge3))));
    return 0;
}
