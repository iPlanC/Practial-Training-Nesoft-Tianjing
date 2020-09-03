/*
 * @Author: PlanC
 * @Date: 2020-09-03 17:00:03
 * @LastEditTime: 2020-09-03 18:04:46
 * @FilePath: \Practical-Training-Neusoft-Tianjing\9.3\hw3.c
 * @Encode: GB2312
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    size_t i = 0;
    char *str = "ÁãÒ¼·¡ÈşËÁÎéÂ½Æâ°Æ¾ÁÊ°°ÛÇªÍòÒÚÔ²½Ç·Ö";
    for (i = 0; i < strlen(str); i+=2) {
        printf("%c%c", str[i], str[i + 1]);
    }
}
