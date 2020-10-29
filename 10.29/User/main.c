#include "includes.h"
#include "dht11.h"
#include <stdio.h>

OS_SEM  DHT11_sem;
OS_TCB  task1_TCB;
OS_TCB  task2_TCB;
CPU_STK	task1_Stk[128];
CPU_STK	task2_Stk[128];
DHT11_TypeDef DHT11_data;

int main(void) {
	OS_ERR err;	
	BSP_Init();
	OSInit(&err);
	OSSchedRoundRobinCfg(ENABLE, 1, &err);
	OSSemCreate(&DHT11_sem, "DHT11_SEM", 0, &err);
	
	printf("started!\n");
	
	OSTaskCreate((OS_TCB     *)&task1_TCB,   
				(CPU_CHAR   *)"Task1",
				(OS_TASK_PTR )Task1,
				(void       *)0,
				(OS_PRIO     )2,
				(CPU_STK    *)&task1_Stk[0],
				(CPU_STK_SIZE)12,
				(CPU_STK_SIZE)128,
				(OS_MSG_QTY  )0,
				(OS_TICK     )0,
				(void       *)0,
				(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				(OS_ERR     *)&err);
	
	OSTaskCreate((OS_TCB     *)&task2_TCB,
				(CPU_CHAR   *)"Task2",
				(OS_TASK_PTR )Task2,
				(void       *)0,
				(OS_PRIO     )3,
				(CPU_STK    *)&task2_Stk[0],
				(CPU_STK_SIZE)12,
				(CPU_STK_SIZE)128,
				(OS_MSG_QTY  )0,
				(OS_TICK     )0,
				(void       *)0,
				(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				(OS_ERR     *)&err);
	
	OSStart(&err);
//	while (1) {
//		DHT_read(&DHT11_data);
//		printf("Hum: %d, Tem:%d.\n", DHT11_data.humidity, DHT11_data.temperature);
//	}
}

/*********************************************END OF FILE**********************/
