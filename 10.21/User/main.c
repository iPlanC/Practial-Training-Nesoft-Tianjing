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
#include "bsp_bkp.h"
#include "bmp.h"

unsigned int count = 0;

int main(void) {
	int i = 0;
	
	Led_Configuration();
	IIC1_Configuration();
	Uart1_NVIC_Init();
	Uart1_Configuration();
	SysTick_Configuration();
	
	//IIC_Write_Byte(0x0, 10);
	
	while (1) {
		for (i = 0; i < IIC_Read_Byte(0x0); i++) {
			LED_TOGGLE;
			Delay_us(100000);
		}
		while (1);
	}
}
