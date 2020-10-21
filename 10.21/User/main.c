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
	SysTick_Configuration();
	PA0_EXTI0_Configuration();
	PA5_EXTI5_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	while(1)
	{
		//for (i = 0; i < 10; i++) {
			LED_TOGGLE;
			Delay_us(100000);
		//}
		//__WFI();
		//PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
	}
}

