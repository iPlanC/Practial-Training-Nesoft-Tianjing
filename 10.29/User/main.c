#include "includes.h"
#include "bmp.h"
#include <stdio.h>

OS_SEM  DHT11_sem;
OS_TCB  task1_TCB;
OS_TCB  task2_TCB;
CPU_STK	task1_Stk[128];
CPU_STK	task2_Stk[128];

DHT11_TypeDef DHT11_data;

void step_motor(void);

int main(void) {
	int i = 0;
	float lx = 0;
//	OS_ERR err;	
	BSP_Init();
	
//	OSInit(&err);
//	OSSchedRoundRobinCfg(ENABLE, 1, &err);
//	OSSemCreate(&DHT11_sem, "DHT11_SEM", 0, &err);
//	
//	printf("started!\n");
//	
//	OSTaskCreate((OS_TCB     *)&task1_TCB,   
//				(CPU_CHAR   *)"Task1",
//				(OS_TASK_PTR )Task1,
//				(void       *)0,
//				(OS_PRIO     )2,
//				(CPU_STK    *)&task1_Stk[0],
//				(CPU_STK_SIZE)12,
//				(CPU_STK_SIZE)128,
//				(OS_MSG_QTY  )0,
//				(OS_TICK     )0,
//				(void       *)0,
//				(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//				(OS_ERR     *)&err);
//	
//	OSTaskCreate((OS_TCB     *)&task2_TCB,
//				(CPU_CHAR   *)"Task2",
//				(OS_TASK_PTR )Task2,
//				(void       *)0,
//				(OS_PRIO     )3,
//				(CPU_STK    *)&task2_Stk[0],
//				(CPU_STK_SIZE)12,
//				(CPU_STK_SIZE)128,
//				(OS_MSG_QTY  )0,
//				(OS_TICK     )0,
//				(void       *)0,
//				(OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
//				(OS_ERR     *)&err);
//	
//	OSStart(&err);

	// draw "HUM:  %"
	OLED_DrawBMP(0, 0, 7, 1, char_H);
	OLED_DrawBMP(8, 0, 15, 1, char_U);
	OLED_DrawBMP(16, 0, 23, 1, char_M);
	OLED_DrawBMP(24, 0, 31, 1, char_colon);
	OLED_DrawBMP(48, 0, 55, 1, char_percent);
	
	// draw "TEM:  c"
	OLED_DrawBMP(0, 2, 7, 3, char_T);
	OLED_DrawBMP(8, 2, 15, 3, char_E);
	OLED_DrawBMP(16, 2, 23, 3, char_M);
	OLED_DrawBMP(24, 2, 31, 3, char_colon);
	OLED_DrawBMP(48, 2, 55, 3, char_celsius);

	// draw "LMX:    lx"
	OLED_DrawBMP(0, 4, 7, 5, char_L);
	OLED_DrawBMP(8, 4, 15, 5, char_U);
	OLED_DrawBMP(16, 4, 23, 5, char_X);
	OLED_DrawBMP(24, 4, 31, 5, char_colon);
	OLED_DrawBMP(72, 4, 79, 5, char_lux);

	// draw "0123456789"
	for (i = 0; i < 10; i++) {
		OLED_DrawBMP(i * 8, 6, i * 8 + 7, 7, gImage_number[i]);
	}
	
	while (1) {
		DHT_read(&DHT11_data);
		lx = LIght_Intensity();
		
		OLED_DrawBMP(32, 0, 39, 1, gImage_number[DHT11_data.humidity / 10]);
		OLED_DrawBMP(40, 0, 47, 1, gImage_number[DHT11_data.humidity % 10]);
		
		OLED_DrawBMP(32, 2, 39, 3, gImage_number[DHT11_data.temperature / 10]);
		OLED_DrawBMP(40, 2, 47, 3, gImage_number[DHT11_data.temperature % 10]);
		
		OLED_DrawBMP(32, 4, 39, 5, gImage_number[(int)lx / 10000 % 10]);
		OLED_DrawBMP(40, 4, 47, 5, gImage_number[(int)lx / 1000 % 10]);
		OLED_DrawBMP(48, 4, 55, 5, gImage_number[(int)lx / 100 % 10]);
		OLED_DrawBMP(56, 4, 63, 5, gImage_number[(int)lx / 10 % 10]);
		OLED_DrawBMP(64, 4, 71, 5, gImage_number[(int)lx / 1 % 10]);
		
		//printf("Hum: %d, Tem:%d, ", DHT11_data.humidity, DHT11_data.temperature);
		//printf("PRE: %d.\n", pressure);
		if (DHT11_data.humidity > 60 || DHT11_data.temperature > 30)
			for (i = 0; i < 64; i++) step_motor();
		if ((int)lx < 10000) {
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
			GPIO_SetBits(GPIOA, GPIO_Pin_2);
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
		}
		else {
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}
			
		delay_ms(500);
	}
}

void step_motor() {
//	GPIO_SetBits(GPIOA, GPIO_Pin_1);
//	GPIO_SetBits(GPIOA, GPIO_Pin_2);
//	GPIO_SetBits(GPIOA, GPIO_Pin_3);
//	GPIO_SetBits(GPIOA, GPIO_Pin_4);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
//	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	
	int i = 0;
	for (i = 0; i < 64; i++) {
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
		
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		Delay_us(1000);
	}
}

/*********************************************END OF FILE**********************/
