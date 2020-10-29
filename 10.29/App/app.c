#include "app.h"
#include "dht11.h"
#include <stdio.h>
#include <string.h>

extern OS_SEM DHT11_sem;
extern DHT11_TypeDef DHT11_data;

void Task1(void *p_arg) {
	OS_ERR err;
	while (1) {
		if (DHT_read(&DHT11_data) == 1) {
			OSSemPost(&DHT11_sem, OS_OPT_POST_ALL, &err);
			printf("task1 post sem\n");
		}
		printf("task1 complete\n");
		OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

void Task2(void *p_arg) {
	OS_ERR err;
	while (1) {
		OSSemPend(&DHT11_sem, 1, OS_OPT_PEND_NON_BLOCKING, (CPU_TS*)0, &err);
		printf("Hum: %d, Tem:%d.\n", DHT11_data.humidity, DHT11_data.temperature);
		printf("task2 complete\n");
		OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
	}
}

int fputc (int c, FILE *fp) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	return 0;
}
