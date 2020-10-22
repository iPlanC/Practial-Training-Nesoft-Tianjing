#include "Led_Key.h"
#include "bsp_exti.h"
#include "bsp_SysTick.h"
#include "bsp_iwdg.h"
#include "bsp_wwdg.h"
#include "bsp_uart.h"
#include "bsp_dma.h"
#include "bsp_adc.h"
#include "bsp_tim.h"
#include "bsp_rtc.h"
#include "music.h"
#include "bsp_hcsr04.h"
#include "bsp_spi_max6675.h"
#include "bsp_digital_tube.h"
#include "bsp_74HC595.h"
#include "bsp_lcd1602.h"
#include "bsp_ds18b20.h"
#include "bsp_iic_at24c02.h"
#include "bsp_iic.h"
#include "bsp_iic_bh1750.h"
#include "bsp_uln2003.h"
#include "bsp_tcs3200.h"
#include "bsp_dht11.h"
#include "bsp_oled.h"
#include "bmp.h"

unsigned int count = 0;

int main(void)
{
	int i = 0;
	Led_Configuration();
	TIM2_Count_Configuration();
	HCSR04_GPIO_Configuration();
	SysTick_Configuration();
	OLED_Init();

	OLED_DrawBMP(0, 0, 3, 0, gImage_number[0]);    // 0
	OLED_DrawBMP(4, 0, 7, 0, gImage_number[1]);    // 1
	OLED_DrawBMP(8, 0, 11, 0, gImage_number[2]);   // 2
	OLED_DrawBMP(12, 0, 15, 0, gImage_number[3]);  // 3
	OLED_DrawBMP(16, 0, 19, 0, gImage_number[4]);  // 4
	OLED_DrawBMP(20, 0, 23, 0, gImage_number[5]);  // 5
	OLED_DrawBMP(24, 0, 27, 0, gImage_number[6]);  // 6
	OLED_DrawBMP(28, 0, 31, 0, gImage_number[7]);  // 7
	OLED_DrawBMP(32, 0, 35, 0, gImage_number[8]);  // 8
	OLED_DrawBMP(36, 0, 39, 0, gImage_number[9]);  // 9
	OLED_DrawBMP(0, 2, 15, 2, gImage_Word);        // DES:
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	while(1)
	{	
		// wait for response
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == RESET) {
			// send Trigger signal
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			Delay_us(15);
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
		
		// turn on timer(2)
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE);
		while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == SET);
		TIM_Cmd(TIM2, DISABLE);
		
		// show distance
		i = 127;
		count = (TIM_GetCounter(TIM2) - 1);
		do {
			OLED_DrawBMP(i - 3, 2, i, 2, gImage_number[count % 10]);
			count = count / 10;
			i = i - 4;
		} while (count > 10);
		Delay_us(60000);
		LED_TOGGLE;
	}
}

